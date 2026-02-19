#!/usr/bin/env bash
set -euo pipefail

# -----------------------------------------------------------------------------
# appgateway_L1_tests_withoutACT.sh
#
# Purpose:
#   Run the AppGateway L1 workflow steps while keeping repeated executions fast by
#   reusing already-cloned repos and already-built/install artifacts when present.
#
# Required behavior for this task:
#   - Step 23 MUST pass -DPLUGIN_APPGATEWAY=ON so AppGateway plugin .so is built.
#   - Step 23 MUST log the FULL CMake configure command (including generator).
#   - The AppGateway plugin shared object MUST be installed/copied to:
#       /usr/lib/wpeframework/plugins
#   - Tests must link against the installed plugin (handled in Tests/L1Tests CMake).
# -----------------------------------------------------------------------------

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_DIR="$(cd "${SCRIPT_DIR}" && pwd -P)"

log() { echo "==> $*"; }
warn() { echo "WARNING: $*" >&2; }
err() { echo "ERROR: $*" >&2; }

have_cmd() { command -v "$1" >/dev/null 2>&1; }
is_root() { [[ "${EUID:-$(id -u)}" -eq 0 ]]; }

apt_can_run() {
  if is_root; then return 0; fi
  if have_cmd sudo; then return 0; fi
  return 1
}

apt_get() {
  local -a cmd
  if is_root; then
    cmd=(apt-get)
  else
    cmd=(sudo -n apt-get)
  fi

  DEBIAN_FRONTEND=noninteractive "${cmd[@]}" -y \
    -o Dpkg::Options::="--force-confnew" \
    -o Dpkg::Options::="--force-confdef" \
    "$@"
}

run_best_effort() {
  # Usage: run_best_effort "description" command...
  local desc="$1"
  shift
  (
    set +e
    "$@"
  )
  local rc=$?
  if [[ $rc -ne 0 ]]; then
    warn "${desc} failed with exit code ${rc} (non-fatal)."
  fi
  return 0
}

git_noninteractive_env() {
  export GIT_TERMINAL_PROMPT=0
  export GIT_ASKPASS=/bin/false
}

# -----------------------------------------------------------------------------
# Rebuild / reclone controls
# -----------------------------------------------------------------------------
CLEAN=0
FORCE_REBUILD=0
FORCE_RECLONE=0

usage() {
  cat <<EOF
Usage: $(basename "$0") [--clean] [--rebuild] [--reclone] [--help]

  --clean     Remove build dirs under BUILD_ROOT and remove INSTALL_ROOT.
              Then rebuild from scratch (repos are NOT recloned unless --reclone).
  --rebuild   Force (re)configure/build/install steps even if artifacts exist.
  --reclone   Delete and re-clone git repositories (Thunder/ThunderTools/googletest/entservices-apis).
  --help      Show this help.

Environment:
  WORKSPACE_ROOT   Defaults to /home/kavia/workspace/code-generation
  INSTALL_ROOT     Defaults to \$WORKSPACE_ROOT/install
  BUILD_ROOT       Defaults to /tmp/entservices-appgateway-build
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --clean)
      CLEAN=1
      shift
      ;;
    --rebuild)
      FORCE_REBUILD=1
      shift
      ;;
    --reclone)
      FORCE_RECLONE=1
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      err "Unknown argument: $1"
      usage
      exit 2
      ;;
  esac
done

# -----------------------------------------------------------------------------
# Git helpers
# -----------------------------------------------------------------------------
ensure_git_checkout_ref() {
  local dir="$1"
  local ref="$2"

  if [[ ! -d "${dir}/.git" ]]; then
    warn "Not a git repo: ${dir} (cannot checkout ${ref})"
    return 1
  fi
  if ! have_cmd git; then
    warn "git not available; cannot checkout ${ref} in ${dir}"
    return 1
  fi

  git_noninteractive_env

  (
    cd "${dir}"

    git fetch --tags --prune --quiet 2>/dev/null || true

    if git rev-parse -q --verify "refs/tags/${ref}" >/dev/null 2>&1; then
      git checkout -q -f "tags/${ref}" || return 1
      return 0
    fi

    if git show-ref -q --verify "refs/heads/${ref}"; then
      git checkout -q -f "${ref}" || return 1
      return 0
    fi

    if git show-ref -q --verify "refs/remotes/origin/${ref}"; then
      git checkout -q -B "${ref}" "origin/${ref}" || return 1
      return 0
    fi

    warn "Ref '${ref}' not found in ${dir}. Current ref: $(git describe --tags --always --dirty 2>/dev/null || git rev-parse --short HEAD 2>/dev/null || echo unknown)"
    return 1
  )
}

ensure_repo_clone_and_checkout() {
  local dir="$1"
  local url="$2"
  local ref="$3"

  if [[ "${FORCE_RECLONE}" -eq 1 ]]; then
    log "Reclone requested: removing ${dir}"
    rm -rf "${dir}"
  fi

  if [[ -d "${dir}/.git" ]]; then
    log "Repo present: ${dir}"
    run_best_effort "Checkout ${ref} in ${dir}" ensure_git_checkout_ref "${dir}" "${ref}"
    return 0
  fi

  if [[ -e "${dir}" && ! -d "${dir}" ]]; then
    warn "Path exists but is not a directory: ${dir} (cannot clone ${url})"
    return 1
  fi

  if ! have_cmd git; then
    warn "git not available; cannot clone ${url} into ${dir}."
    return 1
  fi

  git_noninteractive_env

  log "Cloning ${url} -> ${dir} (then checkout ref: ${ref})"
  mkdir -p "$(dirname "${dir}")"
  rm -rf "${dir}"

  if ! git clone "${url}" "${dir}"; then
    warn "Clone failed for ${url}."
    return 1
  fi

  run_best_effort "Checkout ${ref} in ${dir}" ensure_git_checkout_ref "${dir}" "${ref}"
  return 0
}

apply_patch_dir() {
  local repo_dir="$1"
  local patch_file="$2"
  local p_level="$3"

  if [[ ! -f "${patch_file}" ]]; then
    warn "Patch file not found: ${patch_file}"
    return 1
  fi
  if [[ ! -d "${repo_dir}" ]]; then
    warn "Repo dir not found for patch: ${repo_dir}"
    return 1
  fi
  if ! have_cmd patch; then
    warn "patch command not available; cannot apply ${patch_file}"
    return 1
  fi

  log "Applying patch (idempotent): ${patch_file} -> ${repo_dir}"
  (
    cd "${repo_dir}"

    set +e
    local out rc
    out="$(patch "${p_level}" --batch --forward < "${patch_file}" 2>&1)"
    rc=$?
    set -e

    if [[ $rc -eq 0 ]]; then
      echo "${out}"
      return 0
    fi

    if echo "${out}" | grep -Eqi "(previously applied|Reversed.*previously applied|Skipping patch|already exists)"; then
      warn "Patch appears already applied (or files already present); continuing."
      echo "${out}"
      return 0
    fi

    echo "${out}" >&2
    return "${rc}"
  )
}

# -----------------------------------------------------------------------------
# Build helpers
# -----------------------------------------------------------------------------
build_dir_configured() {
  local build_dir="$1"
  [[ -f "${build_dir}/CMakeCache.txt" ]]
}

# PUBLIC_INTERFACE
is_component_installed() {
  # Heuristic to skip rebuilds.
  local component="$1"
  local prefix_usr="$2"

  case "${component}" in
    ThunderTools)
      [[ -d "${prefix_usr}/include/WPEFramework" || -x "${prefix_usr}/bin/json2code" || -x "${prefix_usr}/bin/JsonGenerator" ]]
      ;;
    Thunder)
      [[ -d "${prefix_usr}/include/WPEFramework" || -d "${prefix_usr}/lib/wpeframework" || -f "${prefix_usr}/lib/libWPEFrameworkCore.so" || -f "${prefix_usr}/lib/libThunderCore.so" ]]
      ;;
    googletest)
      [[ -f "${prefix_usr}/lib/libgtest.a" || -f "${prefix_usr}/lib/libgtest.so" || -f "${prefix_usr}/lib64/libgtest.a" || -f "${prefix_usr}/lib64/libgtest.so" || -d "${prefix_usr}/include/gtest" ]]
      ;;
    entservices-apis)
      [[ -d "${prefix_usr}/include" && ( -d "${prefix_usr}/include/interfaces" || -d "${prefix_usr}/include/WPEFramework" ) ]]
      ;;
    entservices-appgateway)
      # Consider installed only if both the plugin directory exists and the L1 test runner
      # binary is present. This avoids incorrectly skipping the full build after a
      # plugin-only preinstall step.
      [[ -d "${prefix_usr}/lib/wpeframework/plugins" && -x "${prefix_usr}/bin/AppGatewayL1Test" ]]
      ;;
    *)
      return 1
      ;;
  esac
}

cmake_configure_build_install() {
  local component_name="$1"
  local src_dir="$2"
  local build_dir="$3"
  local install_prefix="$4"
  shift 4
  local -a extra_args=("$@")

  if [[ ! -d "${src_dir}" ]]; then
    err "CMake source directory not found: ${src_dir}"
    return 1
  fi

  mkdir -p "${build_dir}" "${install_prefix}"

  if [[ "${FORCE_REBUILD}" -eq 0 ]] && build_dir_configured "${build_dir}" && is_component_installed "${component_name}" "${install_prefix}"; then
    log "${component_name}: build dir already configured and install outputs detected under ${install_prefix}; skipping configure/build/install."
    return 0
  fi

  # Always specify the generator explicitly so logs and configuration are deterministic.
  # This also ensures "full configure command (including generator)" requirements are met.
  local -a gen_args=()
  if have_cmd ninja; then
    gen_args=(-G Ninja)
  else
    gen_args=(-G "Unix Makefiles")
  fi

  log "${component_name}: CMake configure: cmake ${gen_args[*]} -S ${src_dir} -B ${build_dir} -DCMAKE_INSTALL_PREFIX=${install_prefix} (verbose; log: ${build_dir}/configure_verbose.log)"
  cmake "${gen_args[@]}" -S "${src_dir}" -B "${build_dir}" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX="${install_prefix}" \
    -DCMAKE_VERBOSE_MAKEFILE=ON \
    -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE \
    --log-level=VERBOSE \
    "${extra_args[@]}" 2>&1 | tee "${build_dir}/configure_verbose.log"

  log "${component_name}: CMake build: ${build_dir}"
  cmake --build "${build_dir}" -- -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)"

  log "${component_name}: CMake install: ${build_dir}"
  cmake --install "${build_dir}"
}

# -----------------------------------------------------------------------------
# Workspace layout
# -----------------------------------------------------------------------------
WORKSPACE_ROOT_DEFAULT="/home/kavia/workspace/code-generation"
WORKSPACE_ROOT="${WORKSPACE_ROOT:-${WORKSPACE_ROOT_DEFAULT}}"

THUNDER_REF_REQUIRED="R4.4.1"
THUNDERTOOLS_REF_REQUIRED="R4.4.3"

THUNDER_DIR="${REPO_DIR}/Thunder"
THUNDERTOOLS_DIR="${REPO_DIR}/ThunderTools"
APIS_DIR="${REPO_DIR}/entservices-apis"
GTEST_DIR="${REPO_DIR}/googletest"

PATCHES_DIR="${REPO_DIR}/Tests/patches"

# Default install prefix requested for this workflow:
#   -DCMAKE_INSTALL_PREFIX=/home/kavia/workspace/code-generation/entservices-appgateway-34/install/usr
# (computed from repo root so it also works if the workspace path changes)
INSTALL_ROOT="${INSTALL_ROOT:-${REPO_DIR}/install}"
INSTALL_USR="${INSTALL_ROOT}/usr"

BUILD_ROOT="${BUILD_ROOT:-/tmp/entservices-appgateway-build}"

if [[ "${CLEAN}" -eq 1 ]]; then
  log "[CLEAN] Removing build outputs under BUILD_ROOT=${BUILD_ROOT} and install under INSTALL_ROOT=${INSTALL_ROOT}"
  rm -rf "${BUILD_ROOT}" || true
  rm -rf "${INSTALL_ROOT}" || true
fi

# Ensure the install tree exists under the repo root (requested workflow behavior).
# Note: we intentionally do NOT change the optional/system plugin copy behavior to /usr/lib.
mkdir -p "${INSTALL_USR}"

# -----------------------------------------------------------------------------
# Steps 1-22 are retained as-is (package installs/patching/build dependencies)
# -----------------------------------------------------------------------------
log "[Step 1] Set up cache (SKIP)"
log "Reason: GitHub Actions cache only."

log "[Step 2] Set up Python + pip install jsonref"
if ! have_cmd python3; then
  err "python3 is not available on PATH"
  exit 1
fi
if ! python3 -m pip --version >/dev/null 2>&1; then
  err "pip for python3 is not available (python3 -m pip failed)"
  err "Hint: install python3-pip in the container base image."
  exit 1
fi
echo "Python: $(python3 --version)"
echo "Pip: $(python3 -m pip --version)"
python3 -m pip install --user -q jsonref
python3 -c "import jsonref; print('jsonref', getattr(jsonref, '__version__', 'unknown'))"
log "[OK] Python/pip/jsonref are ready"

log "[Step 3] ACK External Trigger (OPTIONAL)"
log "ACK external trigger: N/A in container run. (Non-blocking step.)"

log "[Step 4] Set up CMake (Skip if already installed)"
if have_cmd cmake; then
  echo "CMake: $(cmake --version | head -n 1)"
else
  warn "cmake not found."
  if apt_can_run; then
    log "Installing cmake via apt-get..."
    apt_get update
    apt_get install cmake
    echo "CMake: $(cmake --version | head -n 1)"
  else
    warn "Cannot install cmake (not root and sudo not available)."
  fi
fi

if have_cmd ninja; then
  echo "Ninja: $(ninja --version)"
else
  warn "ninja not found."
  if apt_can_run; then
    log "Installing ninja-build via apt-get..."
    apt_get update
    apt_get install ninja-build
    echo "Ninja: $(ninja --version)"
  else
    warn "Cannot install ninja-build (not root and sudo not available)."
  fi
fi

log "[Step 5] Install packages"
APT_PACKAGES=(
  libsqlite3-dev
  libcurl4-openssl-dev
  valgrind
  lcov
  clang
  libsystemd-dev
  libboost-all-dev
  libwebsocketpp-dev
  meson
  libcunit1
  libcunit1-dev
  curl
  protobuf-compiler-grpc
  libgrpc-dev
  libgrpc++-dev
  libjsoncpp-dev
  git
  pkg-config
  patch
)

if apt_can_run; then
  log "Updating apt indexes and installing dependencies (non-interactive)..."
  apt_get update
  apt_get install "${APT_PACKAGES[@]}"
  log "[OK] apt packages installed"
else
  warn "Skipping apt package install: not root and sudo not available."
  warn "If compilation fails, ensure these are present:"
  printf '  - %s\n' "${APT_PACKAGES[@]}" >&2
fi

log "[Step 6] Build trower-base64"
(
  set +e

  if ls /usr/local/include 2>/dev/null | grep -qi "base64" || ls /usr/include 2>/dev/null | grep -qi "base64"; then
    log "trower-base64 appears installed already (headers found). Skipping."
    exit 0
  fi

  if ! have_cmd git; then
    warn "git not available; cannot clone trower-base64. Skipping."
    exit 0
  fi
  if ! have_cmd meson || ! have_cmd ninja; then
    warn "meson and/or ninja not available; cannot build trower-base64. Skipping."
    exit 0
  fi

  if ! apt_can_run && ! is_root; then
    warn "Not root and sudo not available; cannot install system-wide. Skipping."
    exit 0
  fi

  TROWER_DIR="${REPO_DIR}/.deps/trower-base64"
  git_noninteractive_env

  if [[ ! -d "${TROWER_DIR}/.git" ]]; then
    log "Cloning trower-base64 -> ${TROWER_DIR}"
    rm -rf "${TROWER_DIR}"
    mkdir -p "$(dirname "${TROWER_DIR}")"
    if ! git clone --depth 1 https://github.com/tdunning/trower-base64.git "${TROWER_DIR}"; then
      warn "Clone failed (non-fatal)."
      exit 0
    fi
  fi

  log "Building trower-base64 with meson/ninja..."
  pushd "${TROWER_DIR}" >/dev/null || exit 0
  if [[ -d build ]]; then
    meson setup build --reconfigure >/dev/null 2>&1 || { warn "meson reconfigure failed"; popd >/dev/null; exit 0; }
  else
    meson setup build >/dev/null 2>&1 || { warn "meson setup failed"; popd >/dev/null; exit 0; }
  fi
  ninja -C build || { warn "ninja build failed"; popd >/dev/null; exit 0; }

  log "Installing trower-base64..."
  if is_root; then
    ninja -C build install || warn "install failed"
  else
    sudo -n ninja -C build install || warn "install via sudo failed"
  fi
  popd >/dev/null
  exit 0
) || true

log "[Step 7] Checkout Thunder (Ensure ${THUNDER_DIR} exists at ${THUNDER_REF_REQUIRED})"
ensure_repo_clone_and_checkout "${THUNDER_DIR}" "https://github.com/rdkcentral/Thunder.git" "${THUNDER_REF_REQUIRED}" || true

log "[Step 8] Checkout ThunderTools (Ensure ${THUNDERTOOLS_DIR} exists at ${THUNDERTOOLS_REF_REQUIRED})"
ensure_repo_clone_and_checkout "${THUNDERTOOLS_DIR}" "https://github.com/rdkcentral/ThunderTools.git" "${THUNDERTOOLS_REF_REQUIRED}" || true

log "[Step 9] Checkout entservices-testframework (SKIPPED)"
log "Reason: Do not rely on entservices-testframework for patches; patches are sourced from ${PATCHES_DIR}."
log "However, we DO use entservices-testframework as a reference for the coverage toolchain file in Step 20."

log "[Step 10] Checkout entservices-appgateway (Use local repo checkout)"
echo "This repo: ${REPO_DIR}"
echo "Workspace root: ${WORKSPACE_ROOT}"

log "[Step 11] Checkout googletest (Ensure exists at v1.15.0)"
ensure_repo_clone_and_checkout "${GTEST_DIR}" "https://github.com/google/googletest.git" "v1.15.0" || true

log "[Step 12] Apply patches ThunderTools"
if [[ -d "${PATCHES_DIR}" ]]; then
  run_best_effort "ThunderTools patch" apply_patch_dir \
    "${THUNDERTOOLS_DIR}" \
    "${PATCHES_DIR}/00010-R4.4-Add-support-for-project-dir.patch" \
    "-p1"
else
  warn "Patches dir not found at ${PATCHES_DIR}; cannot apply ThunderTools patch."
fi

log "[Step 13] Build ThunderTools"
if [[ -d "${THUNDERTOOLS_DIR}" ]]; then
  mkdir -p "${BUILD_ROOT}"
  cmake_configure_build_install \
    "ThunderTools" \
    "${THUNDERTOOLS_DIR}" \
    "${BUILD_ROOT}/ThunderTools" \
    "${INSTALL_USR}" \
    -DPROJECT_DIR="${WORKSPACE_ROOT}"
else
  warn "ThunderTools dir not found at ${THUNDERTOOLS_DIR}; skipping build."
fi

log "[Step 14] Apply patches Thunder"
if [[ -d "${PATCHES_DIR}" ]]; then
  THUNDER_PATCHES=(
    "Use_Legact_Alt_Based_On_ThunderTools_R4.4.3.patch"
    "error_code_R4_4.patch"
    "1004-Add-support-for-project-dir.patch"
    "RDKEMW-733-Add-ENTOS-IDS.patch"
    "Jsonrpc_dynamic_error_handling.patch"
  )

  for p in "${THUNDER_PATCHES[@]}"; do
    if [[ -f "${PATCHES_DIR}/${p}" ]]; then
      run_best_effort "Thunder patch ${p}" apply_patch_dir "${THUNDER_DIR}" "${PATCHES_DIR}/${p}" "-p1"
    else
      warn "Missing Thunder patch in repo patches dir: ${PATCHES_DIR}/${p}"
    fi
  done
else
  warn "Patches dir not found at ${PATCHES_DIR}; cannot apply Thunder patches."
fi

log "[Step 15] Build Thunder"
if [[ -d "${THUNDER_DIR}" ]]; then
  cmake_configure_build_install \
    "Thunder" \
    "${THUNDER_DIR}" \
    "${BUILD_ROOT}/Thunder" \
    "${INSTALL_USR}" \
    -DPROJECT_DIR="${WORKSPACE_ROOT}"
else
  warn "Thunder dir not found at ${THUNDER_DIR}; skipping build."
fi

log "[Step 16] Checkout entservices-apis (Ensure exists)"
ensure_repo_clone_and_checkout "${APIS_DIR}" "https://github.com/rdkcentral/entservices-apis.git" "develop" || true

if [[ -f "${APIS_DIR}/jsonrpc/DTV.json" ]]; then
  log "Removing ${APIS_DIR}/jsonrpc/DTV.json (workflow parity)"
  rm -f "${APIS_DIR}/jsonrpc/DTV.json" || true
fi

log "[Step 17] Apply patch RDKEMW-1007.patch to entservices-apis"
if [[ -f "${PATCHES_DIR}/RDKEMW-1007.patch" ]]; then
  run_best_effort "entservices-apis patch RDKEMW-1007.patch" apply_patch_dir \
    "${APIS_DIR}" \
    "${PATCHES_DIR}/RDKEMW-1007.patch" \
    "-p1"
else
  warn "Missing patch ${PATCHES_DIR}/RDKEMW-1007.patch; cannot apply entservices-apis patch."
fi

log "[Step 18] Build entservices-apis (configure/build/install into install/usr)"
if [[ -d "${APIS_DIR}" ]]; then
  cmake_configure_build_install \
    "entservices-apis" \
    "${APIS_DIR}" \
    "${BUILD_ROOT}/entservices-apis" \
    "${INSTALL_USR}"
else
  warn "entservices-apis dir not found at ${APIS_DIR}; skipping build."
fi

log "[Step 19] Generate external headers (SKIPPED)"
log "Per request: do later."

log "[Step 20] Set gcc/with-coverage toolchain (wire CMake toolchain file)"
COVERAGE_TOOLCHAIN_FILE_DEFAULT="${WORKSPACE_ROOT}/networkmanager-34/entservices-testframework/Tests/gcc-with-coverage.cmake"
COVERAGE_TOOLCHAIN_FILE="${COVERAGE_TOOLCHAIN_FILE:-${COVERAGE_TOOLCHAIN_FILE_DEFAULT}}"

if [[ -f "${COVERAGE_TOOLCHAIN_FILE}" ]]; then
  log "Coverage toolchain found: ${COVERAGE_TOOLCHAIN_FILE}"
else
  warn "Coverage toolchain file not found at: ${COVERAGE_TOOLCHAIN_FILE}"
  warn "Step 20 will be effectively skipped; coverage flags will not be injected by toolchain."
fi

log "[Step 21] Build googletest (configure/build/install into install/usr)"
if [[ -d "${GTEST_DIR}" ]]; then
  EXTRA_GTEST_CMAKE_ARGS=(
    -DBUILD_GTEST=ON
    -DBUILD_GMOCK=ON
    -Dgtest_force_shared_crt=OFF
    -DINSTALL_GTEST=ON
  )

  if [[ -f "${COVERAGE_TOOLCHAIN_FILE}" ]]; then
    EXTRA_GTEST_CMAKE_ARGS+=(-DCMAKE_TOOLCHAIN_FILE="${COVERAGE_TOOLCHAIN_FILE}")
  fi

  cmake_configure_build_install \
    "googletest" \
    "${GTEST_DIR}" \
    "${BUILD_ROOT}/googletest" \
    "${INSTALL_USR}" \
    "${EXTRA_GTEST_CMAKE_ARGS[@]}"
else
  warn "Googletest dir not found at ${GTEST_DIR}; skipping build."
fi

# -----------------------------------------------------------------------------
# [Step 22] Build mocks
# -----------------------------------------------------------------------------
# Per request: Step 22 is commented out (not required for now).
# log "[Step 22] Build mocks (COMMENTED OUT - not required for now)"
# log "Per request: step 22 is not required for now."

# -----------------------------------------------------------------------------
# Step 23: Build entservices-appgateway (configure/build/install; MUST build plugin .so)
# -----------------------------------------------------------------------------
log "[Step 23] Build entservices-appgateway (configure/build/install with -DRDK_SERVICES_L1_TEST=ON -DPLUGIN_APPGATEWAY=ON)"

# IMPORTANT:
# Step 23 MUST configure from the entservices-appgateway-34 repository root (this repo),
# NOT from the overall workspace root.
APPGATEWAY_SRC_DIR="${REPO_DIR}"
if have_cmd git && [[ -d "${REPO_DIR}/.git" ]]; then
  APPGATEWAY_SRC_DIR="$(git -C "${REPO_DIR}" rev-parse --show-toplevel 2>/dev/null || echo "${REPO_DIR}")"
fi

if [[ ! -f "${APPGATEWAY_SRC_DIR}/CMakeLists.txt" ]]; then
  err "Step 23 source dir does not contain CMakeLists.txt: ${APPGATEWAY_SRC_DIR}"
  err "This must point at the entservices-appgateway-34 repo root."
  exit 1
fi

# -----------------------------------------------------------------------------
# Step 23a: Pre-build/install AppGateway plugin ONLY.
#
# Why:
#   The L1Tests CMake currently performs a configure-time search for an *installed*
#   AppGateway plugin .so if it cannot link against an in-build target. In a clean
#   tree, that .so does not exist yet until after build/install. This preinstall
#   ensures /usr/lib/wpeframework/plugins has the plugin before L1 tests configure.
# -----------------------------------------------------------------------------
log "[Step 23a] Pre-build/install AppGateway plugin only (for L1Tests configure-time linkage)"

APPGATEWAY_PLUGINONLY_BUILD_DIR="${BUILD_ROOT}/entservices-appgateway-pluginonly"
cmake_configure_build_install \
  "entservices-appgateway-pluginonly" \
  "${APPGATEWAY_SRC_DIR}" \
  "${APPGATEWAY_PLUGINONLY_BUILD_DIR}" \
  "${INSTALL_USR}" \
  -DCMAKE_PREFIX_PATH="${INSTALL_USR}" \
  -DPLUGIN_APPGATEWAY=ON

SYSTEM_PLUGIN_DIR="/usr/lib/wpeframework/plugins"
PLUGIN_SO=""

for d in "${INSTALL_USR}/lib/wpeframework/plugins" "${INSTALL_USR}/lib64/wpeframework/plugins"; do
  if compgen -G "${d}/*AppGateway*.so*" >/dev/null; then
    PLUGIN_SO="$(ls -1 "${d}/"*AppGateway*.so* 2>/dev/null | head -n 1)"
    break
  fi
done

if [[ -z "${PLUGIN_SO}" || ! -f "${PLUGIN_SO}" ]]; then
  err "Preinstall step failed: AppGateway plugin .so not found under ${INSTALL_USR}/{lib,lib64}/wpeframework/plugins"
  exit 1
fi

log "[Step 23a] Copying AppGateway plugin into ${SYSTEM_PLUGIN_DIR}: ${PLUGIN_SO}"
if is_root; then
  mkdir -p "${SYSTEM_PLUGIN_DIR}"
  cp -f "${PLUGIN_SO}" "${SYSTEM_PLUGIN_DIR}/"
else
  if have_cmd sudo; then
    sudo -n mkdir -p "${SYSTEM_PLUGIN_DIR}"
    sudo -n cp -f "${PLUGIN_SO}" "${SYSTEM_PLUGIN_DIR}/"
  else
    err "Need root/sudo to install plugin into ${SYSTEM_PLUGIN_DIR} for L1 tests."
    exit 1
  fi
fi

log "[Step 23a] System plugin dir listing (AppGateway-related):"
ls -la "${SYSTEM_PLUGIN_DIR}/"*AppGateway*.so* 2>/dev/null || true

# -----------------------------------------------------------------------------
# Step 23b: Full build with L1 tests enabled (now that plugin .so is present).
# -----------------------------------------------------------------------------
APPGATEWAY_BUILD_DIR="${BUILD_ROOT}/entservices-appgateway"

# Generator args (required for: "log FULL CMake configure command (including generator)").
APPGW_CMAKE_GENERATOR_ARGS=()
if have_cmd ninja; then
  APPGW_CMAKE_GENERATOR_ARGS=(-G Ninja)
else
  APPGW_CMAKE_GENERATOR_ARGS=(-G "Unix Makefiles")
fi

EXTRA_APPGW_CMAKE_ARGS=(
  -DRDK_SERVICES_L1_TEST=ON
  -DPLUGIN_APPGATEWAY=ON
  -DCMAKE_PREFIX_PATH="${INSTALL_USR}"
)

if [[ -f "${COVERAGE_TOOLCHAIN_FILE}" ]]; then
  EXTRA_APPGW_CMAKE_ARGS+=(-DCMAKE_TOOLCHAIN_FILE="${COVERAGE_TOOLCHAIN_FILE}")
fi

(
  printf '==> entservices-appgateway: Full CMake configure command: '
  printf 'cmake'
  for a in "${APPGW_CMAKE_GENERATOR_ARGS[@]}"; do
    printf ' %q' "${a}"
  done
  printf ' -S %q -B %q -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=%q' \
    "${APPGATEWAY_SRC_DIR}" \
    "${APPGATEWAY_BUILD_DIR}" \
    "${INSTALL_USR}"
  for a in "${EXTRA_APPGW_CMAKE_ARGS[@]}"; do
    printf ' %q' "${a}"
  done
  printf '\n'
)

cmake_configure_build_install \
  "entservices-appgateway" \
  "${APPGATEWAY_SRC_DIR}" \
  "${APPGATEWAY_BUILD_DIR}" \
  "${INSTALL_USR}" \
  "${EXTRA_APPGW_CMAKE_ARGS[@]}"

# -----------------------------------------------------------------------------
# Step 24: Verify plugin .so is available and install/copy it where L1 tests expect it.
# Also copy required mock headers into install include (so builds can find them via prefix).
# -----------------------------------------------------------------------------
log "[Step 24] Verify AppGateway plugin .so and copy required mocks"

EXPECTED_PLUGIN_NAMES=(
  "AppGateway"
)

INSTALL_PLUGIN_DIR=""
INSTALL_PLUGIN_DIR_CANDIDATES=(
  "${INSTALL_USR}/lib/wpeframework/plugins"
  "${INSTALL_USR}/lib64/wpeframework/plugins"
)

for d in "${INSTALL_PLUGIN_DIR_CANDIDATES[@]}"; do
  if [[ -d "${d}" ]]; then
    INSTALL_PLUGIN_DIR="${d}"
    break
  fi
done

if [[ -z "${INSTALL_PLUGIN_DIR}" ]]; then
  err "No install plugin directory found under install prefix: ${INSTALL_USR}"
  err "Checked:"
  printf '  - %s\n' "${INSTALL_PLUGIN_DIR_CANDIDATES[@]}" >&2
  exit 1
fi

log "[Step 24] Installed plugin directory: ${INSTALL_PLUGIN_DIR}"
log "[Step 24] Installed plugins listing:"
ls -la "${INSTALL_PLUGIN_DIR}" || true

for plugin_name in "${EXPECTED_PLUGIN_NAMES[@]}"; do
  if ! compgen -G "${INSTALL_PLUGIN_DIR}/*${plugin_name}*.so*" >/dev/null; then
    err "Expected plugin .so missing after install: ${plugin_name}"
    err "Expected a match for pattern: ${INSTALL_PLUGIN_DIR}/*${plugin_name}*.so*"
    exit 1
  fi
done

APPGW_PLUGIN_SRC=""
if compgen -G "${INSTALL_PLUGIN_DIR}/*AppGateway*.so*" >/dev/null; then
  APPGW_PLUGIN_SRC="$(ls -1 "${INSTALL_PLUGIN_DIR}/"*AppGateway*.so* 2>/dev/null | head -n 1)"
fi

if [[ -z "${APPGW_PLUGIN_SRC}" || ! -f "${APPGW_PLUGIN_SRC}" ]]; then
  err "Step 24 did not locate an AppGateway plugin .so under: ${INSTALL_PLUGIN_DIR}"
  err "Expected a file matching: ${INSTALL_PLUGIN_DIR}/*AppGateway*.so*"
  err "Check build output under: ${APPGATEWAY_BUILD_DIR}"
  exit 1
fi

log "[OK] Located AppGateway plugin .so at: ${APPGW_PLUGIN_SRC}"
ls -la "${APPGW_PLUGIN_SRC}" || true

# Copy plugin .so into system dir expected by runtime loader in this workflow.
SYSTEM_PLUGIN_DIR="/usr/lib/wpeframework/plugins"
SYSTEM_PLUGIN_SO_PATH="${SYSTEM_PLUGIN_DIR}/$(basename "${APPGW_PLUGIN_SRC}")"

log "[Step 24] Installing/copying AppGateway plugin into ${SYSTEM_PLUGIN_SO_PATH}"
if is_root; then
  mkdir -p "${SYSTEM_PLUGIN_DIR}"
  cp -f "${APPGW_PLUGIN_SRC}" "${SYSTEM_PLUGIN_SO_PATH}"
else
  if have_cmd sudo; then
    sudo -n mkdir -p "${SYSTEM_PLUGIN_DIR}"
    sudo -n cp -f "${APPGW_PLUGIN_SRC}" "${SYSTEM_PLUGIN_SO_PATH}"
  else
    err "Cannot install plugin into ${SYSTEM_PLUGIN_DIR}: need root or sudo."
    err "Plugin is present at: ${APPGW_PLUGIN_SRC}"
    err "Expected final install path for tests: ${SYSTEM_PLUGIN_SO_PATH}"
    exit 1
  fi
fi

if [[ ! -f "${SYSTEM_PLUGIN_SO_PATH}" ]]; then
  err "Plugin copy verification failed; missing: ${SYSTEM_PLUGIN_SO_PATH}"
  exit 1
fi

log "[OK] System plugin dir now contains (AppGateway-related):"
ls -la "${SYSTEM_PLUGIN_DIR}/"*AppGateway*.so* 2>/dev/null || true

# Copy required mock headers into the install prefix (so include discovery works via ${INSTALL_USR}/include).
MOCKS_SRC_DIR="${REPO_DIR}/Tests/mocks"
MOCKS_DST_DIR="${INSTALL_USR}/include/Tests/mocks"
mkdir -p "${MOCKS_DST_DIR}"
cp -f "${MOCKS_SRC_DIR}/Module.h" "${MOCKS_DST_DIR}/Module.h"
cp -f "${MOCKS_SRC_DIR}/ServiceMock.h" "${MOCKS_DST_DIR}/ServiceMock.h"
cp -f "${MOCKS_SRC_DIR}/ThunderPortability.h" "${MOCKS_DST_DIR}/ThunderPortability.h"
log "[OK] Mock headers copied to: ${MOCKS_DST_DIR}"

log "[DONE] Steps 1–24 completed (Step 22 commented out per request)."

log "[Step 25] Set up files (COMMENTED - enable if tests require these paths/device nodes)"
log "Per request: commented/skipped for now."

# -----------------------------------------------------------------------------
# Step 26: Run unit tests without valgrind (REQUIRED)
# -----------------------------------------------------------------------------
log "[Step 26] Run unit tests without valgrind (REQUIRED - generates .gcda for coverage)"

(
  export PATH="${INSTALL_USR}/bin:${PATH}"
  export LD_LIBRARY_PATH="${INSTALL_USR}/lib:${INSTALL_USR}/lib/wpeframework/plugins:/usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"
  export GTEST_OUTPUT="json:$(pwd)/AppGatewayL1TestResults.json"

  TEST_BIN=""

  if have_cmd AppGatewayL1Test; then
    TEST_BIN="AppGatewayL1Test"
  else
    if [[ -x "${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test" ]]; then
      TEST_BIN="${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test"
    elif [[ -x "${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test.exe" ]]; then
      TEST_BIN="${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test.exe"
    fi
  fi

  if [[ -z "${TEST_BIN}" ]]; then
    err "AppGatewayL1Test not found."
    err "Checked PATH (expected: ${INSTALL_USR}/bin) and build tree under: ${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/"
    err "Ensure Step 23 built this repo with -DRDK_SERVICES_L1_TEST=ON and that the target AppGatewayL1Test exists."
    exit 1
  fi

  log "Running L1 test binary: ${TEST_BIN}"
  "${TEST_BIN}"

  cp -f "$(pwd)/AppGatewayL1TestResults.json" "${REPO_DIR}/AppGatewayL1TestResultsWithoutValgrind.json"
  rm -f "$(pwd)/AppGatewayL1TestResults.json"
)
log "[OK] Step 26 complete: ${REPO_DIR}/AppGatewayL1TestResultsWithoutValgrind.json"

log "[Step 27] Run unit tests with valgrind (NOT REQUIRED - skipped; focusing on coverage report)"

# -----------------------------------------------------------------------------
# Step 28: Generate coverage (REQUIRED)
# -----------------------------------------------------------------------------
log "[Step 28] Generate coverage (REQUIRED)"

LCOVRC_SRC_1="${REPO_DIR}/entservices-testframework/Tests/L1Tests/.lcovrc_l1"
LCOVRC_SRC_2="${WORKSPACE_ROOT}/networkmanager-34/entservices-testframework/Tests/L1Tests/.lcovrc_l1"

if [[ -f "${LCOVRC_SRC_1}" ]]; then
  log "Using lcovrc: ${LCOVRC_SRC_1}"
  cp "${LCOVRC_SRC_1}" "${HOME}/.lcovrc"
elif [[ -f "${LCOVRC_SRC_2}" ]]; then
  log "Using lcovrc: ${LCOVRC_SRC_2}"
  cp "${LCOVRC_SRC_2}" "${HOME}/.lcovrc"
else
  warn "lcovrc (.lcovrc_l1) not found; proceeding with default lcov configuration."
fi

if [[ ! -d "${APPGATEWAY_BUILD_DIR}" ]]; then
  err "AppGateway build dir not found for coverage capture: ${APPGATEWAY_BUILD_DIR}"
  err "Step 23 should have built this repo with coverage flags into that directory."
  exit 1
fi

COVERAGE_DIR="${REPO_DIR}/coverage"
COVERAGE_INFO="${REPO_DIR}/coverage.info"
FILTERED_INFO="${REPO_DIR}/filtered_coverage.info"

rm -rf "${COVERAGE_DIR}" "${COVERAGE_INFO}" "${FILTERED_INFO}" || true

lcov -c -o "${COVERAGE_INFO}" -d "${APPGATEWAY_BUILD_DIR}"

lcov -r "${COVERAGE_INFO}" \
  '/usr/include/*' \
  "*/${APPGATEWAY_BUILD_DIR##*/}/_deps/*" \
  '*/install/usr/include/*' \
  '*/Tests/headers/*' \
  '*/Tests/mocks/*' \
  '*/Tests/L1Tests/tests/*' \
  '*/Thunder/*' \
  -o "${FILTERED_INFO}"

APPGW_ONLY_INFO="${REPO_DIR}/appgateway_only_coverage.info"
lcov -e "${FILTERED_INFO}" \
  '*/AppGateway/*' \
  '*/AppGatewayCommon/*' \
  -o "${APPGW_ONLY_INFO}"

genhtml -o "${COVERAGE_DIR}" -t "entservices-appgateway (AppGateway-only) coverage" "${APPGW_ONLY_INFO}"

log "[OK] Coverage generated at: ${COVERAGE_DIR}/index.html"

if ls "${INSTALL_USR}/lib/wpeframework/plugins/"*AppGateway*.so >/dev/null 2>&1; then
  log "[OK] AppGateway plugin .so appears present under ${INSTALL_USR}/lib/wpeframework/plugins"
  ls -la "${INSTALL_USR}/lib/wpeframework/plugins/"*AppGateway*.so || true
else
  warn "AppGateway plugin .so not found under ${INSTALL_USR}/lib/wpeframework/plugins"
  warn "If this is unexpected, check whether the plugin target is enabled in the top-level build/install."
fi

log "[Step 29] Upload artifacts (COMMENTED - not applicable locally)"

echo "Summary:"
echo "  REPO_DIR=${REPO_DIR}"
echo "  WORKSPACE_ROOT=${WORKSPACE_ROOT}"
echo "  Thunder=${THUNDER_DIR}"
echo "  ThunderTools=${THUNDERTOOLS_DIR}"
echo "  Googletest=${GTEST_DIR}"
echo "  Entservices-apis=${APIS_DIR}"
echo "  BUILD_ROOT=${BUILD_ROOT}"
echo "  INSTALL_PREFIX=${INSTALL_USR}"
echo "  CLEAN=${CLEAN} FORCE_REBUILD=${FORCE_REBUILD} FORCE_RECLONE=${FORCE_RECLONE}"
echo "  COVERAGE_TOOLCHAIN_FILE=${COVERAGE_TOOLCHAIN_FILE}"
echo "  APPGATEWAY_BUILD_DIR=${APPGATEWAY_BUILD_DIR}"
echo "  TEST_RUNNER=AppGatewayL1Test (expected at ${INSTALL_USR}/bin/AppGatewayL1Test)"
echo "  COVERAGE_DIR=${COVERAGE_DIR:-}"
