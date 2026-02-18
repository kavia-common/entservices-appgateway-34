#!/usr/bin/env bash
set -euo pipefail

# -----------------------------------------------------------------------------
# appgateway_L1_tests_withoutACT.sh
#
# Purpose:
#   Run the AppGateway L1 workflow steps while keeping repeated executions fast by
#   reusing already-cloned repos and already-built/install artifacts when present.
#
# New behavior (this change):
#   - Detect existing clone/build/install outputs for:
#       Thunder, ThunderTools, googletest, entservices-apis, entservices-appgateway
#     and skip clone/configure/build/install steps when they are already present.
#   - Still allow a clean rebuild when requested (see flags below).
#
# Usage:
#   ./appgateway_L1_tests_withoutACT.sh
#
#   Clean rebuild of EVERYTHING (removes build dirs + install prefix):
#     ./appgateway_L1_tests_withoutACT.sh --clean
#
#   Force rebuild (reconfigure+build+install) but keep installs/build dirs:
#     ./appgateway_L1_tests_withoutACT.sh --rebuild
#
#   Force reclone (deletes and re-clones the git repos):
#     ./appgateway_L1_tests_withoutACT.sh --reclone
#
# Notes:
#   - We do NOT use build_dependencies.sh (all commands live here).
#   - We do NOT implement the "generate external headers" step at this time.
#   - Coverage toolchain file from entservices-testframework appends '--coverage'
#     to CMAKE_CXX_FLAGS; we apply it to builds that should produce coverage data.
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
# Rebuild / reclone controls (new)
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

# -----------------------------------------------------------------------------#
# Git helpers
# -----------------------------------------------------------------------------#
ensure_git_checkout_ref() {
  # Ensure that a git repo at dir is checked out to the requested ref (tag/branch).
  # Best-effort and non-interactive.
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

    # Fetch tags/updates best-effort; do not fail the whole function.
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
  # Ensure a repo exists at dir; if missing clone from url; checkout ref best-effort.
  # If FORCE_RECLONE=1, delete and re-clone.
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
  # Apply a patch to a repo directory in an idempotent, non-interactive way.
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

    # Capture output so we can detect "already applied" cases even if patch exits non-zero.
    set +e
    local out rc
    out="$(patch "${p_level}" --batch --forward < "${patch_file}" 2>&1)"
    rc=$?
    set -e

    if [[ $rc -eq 0 ]]; then
      echo "${out}"
      return 0
    fi

    # Idempotency handling: consider these known messages as success.
    if echo "${out}" | grep -Eqi "(previously applied|Reversed.*previously applied|Skipping patch|already exists)"; then
      warn "Patch appears already applied (or files already present); continuing."
      echo "${out}"
      return 0
    fi

    # Unknown failure: propagate error to caller
    echo "${out}" >&2
    return "${rc}"
  )
}

# -----------------------------------------------------------------------------
# Build helpers (updated: can skip if build/install artifacts exist)
# -----------------------------------------------------------------------------
build_dir_configured() {
  local build_dir="$1"
  [[ -f "${build_dir}/CMakeCache.txt" ]]
}

# PUBLIC_INTERFACE
is_component_installed() {
  # Return 0 if an install prefix appears to contain the given component outputs.
  #
  # This is a heuristic detection used to skip expensive rebuilds in repeated runs.
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
      # This repo installs headers and potentially libs; we key off "apis/" install being present.
      [[ -d "${prefix_usr}/include" && ( -d "${prefix_usr}/include/interfaces" || -d "${prefix_usr}/include/WPEFramework" ) ]]
      ;;
    entservices-appgateway)
      [[ -x "${prefix_usr}/bin/AppGatewayL1Test" || -d "${prefix_usr}/lib/wpeframework/plugins" ]]
      ;;
    *)
      return 1
      ;;
  esac
}

cmake_configure_build_install() {
  # Configure/build/install a cmake project using Ninja if available.
  # If FORCE_REBUILD=0 and build dir looks configured and install outputs exist,
  # skip this step.
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

  local -a gen_args=()
  if have_cmd ninja; then
    gen_args=(-G Ninja)
  fi

  log "${component_name}: CMake configure: -S ${src_dir} -B ${build_dir} -DCMAKE_INSTALL_PREFIX=${install_prefix}"
  cmake "${gen_args[@]}" -S "${src_dir}" -B "${build_dir}" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX="${install_prefix}" \
    "${extra_args[@]}"

  log "${component_name}: CMake build: ${build_dir}"
  cmake --build "${build_dir}" -- -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)"

  log "${component_name}: CMake install: ${build_dir}"
  cmake --install "${build_dir}"
}

# -----------------------------------------------------------------------------#
# Workspace layout (per requirement: ALL clones under this repo directory)
# -----------------------------------------------------------------------------#
WORKSPACE_ROOT_DEFAULT="/home/kavia/workspace/code-generation"
WORKSPACE_ROOT="${WORKSPACE_ROOT:-${WORKSPACE_ROOT_DEFAULT}}"

# Versions per prior workflow guidance
THUNDER_REF_REQUIRED="R4.4.1"
THUNDERTOOLS_REF_REQUIRED="R4.4.3"

# All cloned repos under entservices-appgateway-34/
THUNDER_DIR="${REPO_DIR}/Thunder"
THUNDERTOOLS_DIR="${REPO_DIR}/ThunderTools"
APIS_DIR="${REPO_DIR}/entservices-apis"
GTEST_DIR="${REPO_DIR}/googletest"

# Patches are sourced from this repo (no dependency on entservices-testframework).
PATCHES_DIR="${REPO_DIR}/Tests/patches"

# Install prefix (matches "install/usr" pattern)
INSTALL_ROOT="${INSTALL_ROOT:-${WORKSPACE_ROOT}/install}"
INSTALL_USR="${INSTALL_ROOT}/usr"

# Central build output dir
# IMPORTANT:
#   This defaults to /tmp to avoid permission issues.
BUILD_ROOT="${BUILD_ROOT:-/tmp/entservices-appgateway-build}"

# If --clean requested: remove build dirs + install
if [[ "${CLEAN}" -eq 1 ]]; then
  log "[CLEAN] Removing build outputs under BUILD_ROOT=${BUILD_ROOT} and install under INSTALL_ROOT=${INSTALL_ROOT}"
  rm -rf "${BUILD_ROOT}" || true
  rm -rf "${INSTALL_ROOT}" || true
fi

# -----------------------------------------------------------------------------#
# Step 1: Set up cache (SKIP)
# -----------------------------------------------------------------------------#
log "[Step 1] Set up cache (SKIP)"
log "Reason: GitHub Actions cache only."

# -----------------------------------------------------------------------------#
# Step 2: Set up Python + pip install jsonref
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 3: ACK External Trigger (OPTIONAL echo/log)
# -----------------------------------------------------------------------------#
log "[Step 3] ACK External Trigger (OPTIONAL)"
log "ACK external trigger: N/A in container run. (Non-blocking step.)"

# -----------------------------------------------------------------------------#
# Step 4: Set up CMake (Skip if already installed)
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 5: Install packages
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 6: Build trower-base64
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 7: Checkout Thunder (R4.4.1) - CLONE INTO REPO DIR IF MISSING
# -----------------------------------------------------------------------------#
log "[Step 7] Checkout Thunder (Ensure ${THUNDER_DIR} exists at ${THUNDER_REF_REQUIRED})"
ensure_repo_clone_and_checkout "${THUNDER_DIR}" "https://github.com/rdkcentral/Thunder.git" "${THUNDER_REF_REQUIRED}" || true

# -----------------------------------------------------------------------------#
# Step 8: Checkout ThunderTools (R4.4.3) - CLONE INTO REPO DIR IF MISSING
# -----------------------------------------------------------------------------#
log "[Step 8] Checkout ThunderTools (Ensure ${THUNDERTOOLS_DIR} exists at ${THUNDERTOOLS_REF_REQUIRED})"
ensure_repo_clone_and_checkout "${THUNDERTOOLS_DIR}" "https://github.com/rdkcentral/ThunderTools.git" "${THUNDERTOOLS_REF_REQUIRED}" || true

# -----------------------------------------------------------------------------#
# Step 9: Checkout entservices-testframework (develop) - SKIPPED
# -----------------------------------------------------------------------------#
log "[Step 9] Checkout entservices-testframework (SKIPPED)"
log "Reason: Do not rely on entservices-testframework for patches; patches are sourced from ${PATCHES_DIR}."
log "However, we DO use entservices-testframework as a reference for the coverage toolchain file in Step 20."

# -----------------------------------------------------------------------------#
# Step 10: Checkout entservices-appgateway (this repo)
# -----------------------------------------------------------------------------#
log "[Step 10] Checkout entservices-appgateway (Use local repo checkout)"
echo "This repo: ${REPO_DIR}"
echo "Workspace root: ${WORKSPACE_ROOT}"

# -----------------------------------------------------------------------------#
# Step 11: Checkout googletest (v1.15.0) - CLONE INTO REPO DIR
# -----------------------------------------------------------------------------#
log "[Step 11] Checkout googletest (Ensure exists at v1.15.0)"
ensure_repo_clone_and_checkout "${GTEST_DIR}" "https://github.com/google/googletest.git" "v1.15.0" || true

# -----------------------------------------------------------------------------#
# Step 12: Apply patches ThunderTools
# -----------------------------------------------------------------------------#
log "[Step 12] Apply patches ThunderTools"
if [[ -d "${PATCHES_DIR}" ]]; then
  run_best_effort "ThunderTools patch" apply_patch_dir \
    "${THUNDERTOOLS_DIR}" \
    "${PATCHES_DIR}/00010-R4.4-Add-support-for-project-dir.patch" \
    "-p1"
else
  warn "Patches dir not found at ${PATCHES_DIR}; cannot apply ThunderTools patch."
fi

# -----------------------------------------------------------------------------#
# Step 13: Build ThunderTools (install into install/usr)
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 14: Apply patches Thunder
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 15: Build Thunder (install into install/usr)
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 16: Checkout entservices-apis (develop) - CLONE INTO REPO DIR
# -----------------------------------------------------------------------------#
log "[Step 16] Checkout entservices-apis (Ensure exists)"
ensure_repo_clone_and_checkout "${APIS_DIR}" "https://github.com/rdkcentral/entservices-apis.git" "develop" || true

# Workflow note: remove jsonrpc/DTV.json (best-effort).
if [[ -f "${APIS_DIR}/jsonrpc/DTV.json" ]]; then
  log "Removing ${APIS_DIR}/jsonrpc/DTV.json (workflow parity)"
  rm -f "${APIS_DIR}/jsonrpc/DTV.json" || true
fi

# -----------------------------------------------------------------------------#
# Step 17: Apply patches entservices-apis
# -----------------------------------------------------------------------------#
log "[Step 17] Apply patch RDKEMW-1007.patch to entservices-apis"
if [[ -f "${PATCHES_DIR}/RDKEMW-1007.patch" ]]; then
  run_best_effort "entservices-apis patch RDKEMW-1007.patch" apply_patch_dir \
    "${APIS_DIR}" \
    "${PATCHES_DIR}/RDKEMW-1007.patch" \
    "-p1"
else
  warn "Missing patch ${PATCHES_DIR}/RDKEMW-1007.patch; cannot apply entservices-apis patch."
fi

# -----------------------------------------------------------------------------#
# Step 18: Build entservices-apis (install into install/usr)
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 19: Generate external headers (SKIPPED/COMMENTED for now)
# -----------------------------------------------------------------------------#
log "[Step 19] Generate external headers (SKIPPED)"
log "Per request: do later. (Workflow would create minimal headers under entservices-testframework/Tests/headers.)"

# -----------------------------------------------------------------------------#
# Step 20: Set gcc/with-coverage toolchain
# -----------------------------------------------------------------------------#
log "[Step 20] Set gcc/with-coverage toolchain (wire CMake toolchain file)"
COVERAGE_TOOLCHAIN_FILE_DEFAULT="${WORKSPACE_ROOT}/networkmanager-34/entservices-testframework/Tests/gcc-with-coverage.cmake"
COVERAGE_TOOLCHAIN_FILE="${COVERAGE_TOOLCHAIN_FILE:-${COVERAGE_TOOLCHAIN_FILE_DEFAULT}}"

if [[ -f "${COVERAGE_TOOLCHAIN_FILE}" ]]; then
  log "Coverage toolchain found: ${COVERAGE_TOOLCHAIN_FILE}"
else
  warn "Coverage toolchain file not found at: ${COVERAGE_TOOLCHAIN_FILE}"
  warn "Step 20 will be effectively skipped; coverage flags will not be injected by toolchain."
fi

# -----------------------------------------------------------------------------#
# Step 21: Build googletest (install into install/usr)
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 22: Build mocks (NOT REQUIRED FOR NOW - COMMENTED)
# -----------------------------------------------------------------------------#
log "[Step 22] Build mocks (NOT REQUIRED FOR NOW - SKIPPED)"
log "Per request: step 22 is not required for now."

# -----------------------------------------------------------------------------#
# Step 23: Build entservices-appgateway (REQUIRED)
# -----------------------------------------------------------------------------#
log "[Step 23] Build entservices-appgateway (configure/build/install with coverage flags, RDK_SERVICES_L1_TEST=ON)"

APPGATEWAY_BUILD_DIR="${BUILD_ROOT}/entservices-appgateway"

EXTRA_APPGW_CMAKE_ARGS=(
  -DRDK_SERVICES_L1_TEST=ON

  # Explicitly enable the AppGateway plugin so the script-driven build/install
  # produces the plugin .so consumed by tests/coverage.
  # (The top-level CMakeLists.txt only adds AppGateway/ when PLUGIN_APPGATEWAY is ON.)
  -DPLUGIN_APPGATEWAY=ON
)

if [[ -f "${COVERAGE_TOOLCHAIN_FILE}" ]]; then
  EXTRA_APPGW_CMAKE_ARGS+=(-DCMAKE_TOOLCHAIN_FILE="${COVERAGE_TOOLCHAIN_FILE}")
fi

# Log the FULL configure command line that will be used (including PLUGIN_APPGATEWAY),
# since the build log is used for debugging missing installed plugin .so issues.
(
  # Print a command that mirrors cmake_configure_build_install() as closely as possible.
  # Note: Generator selection (-G Ninja) is handled inside cmake_configure_build_install(),
  # so we log the core configure args that matter for correctness.
  printf '==> %s: Full CMake configure command: ' "entservices-appgateway"
  printf 'cmake -S %q -B %q -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=%q' \
    "${REPO_DIR}" \
    "${APPGATEWAY_BUILD_DIR}" \
    "${INSTALL_USR}"
  for a in "${EXTRA_APPGW_CMAKE_ARGS[@]}"; do
    printf ' %q' "${a}"
  done
  printf '\n'
)

cmake_configure_build_install \
  "entservices-appgateway" \
  "${REPO_DIR}" \
  "${APPGATEWAY_BUILD_DIR}" \
  "${INSTALL_USR}" \
  "${EXTRA_APPGW_CMAKE_ARGS[@]}"

# Locate the installed plugin .so under ${INSTALL_USR}. We do NOT rely on a single
# install destination because the plugin CMake can install either to:
#   - ${INSTALL_USR}/lib/wpeframework/plugins
#   - ${INSTALL_USR}/lib/<storage_directory>/plugins
SYSTEM_PLUGIN_DIR="/usr/lib/wpeframework/plugins"

PLUGIN_CANDIDATES=(
  "${INSTALL_USR}/lib/wpeframework/plugins/libWPEFrameworkAppGateway.so"
  "${INSTALL_USR}/lib/wpeframework/plugins/"*AppGateway*.so
  "${INSTALL_USR}/lib/"*/plugins/libWPEFrameworkAppGateway.so
  "${INSTALL_USR}/lib/"*/plugins/*AppGateway*.so
)

APPGW_PLUGIN_SRC=""
for candidate in "${PLUGIN_CANDIDATES[@]}"; do
  # Expand globs safely; when no match, ls exits non-zero.
  if ls ${candidate} >/dev/null 2>&1; then
    APPGW_PLUGIN_SRC="$(ls -1 ${candidate} 2>/dev/null | head -n 1)"
    break
  fi
done

if [[ -z "${APPGW_PLUGIN_SRC}" || ! -f "${APPGW_PLUGIN_SRC}" ]]; then
  err "Step 23 did not produce/locate an AppGateway plugin .so under: ${INSTALL_USR}"
  err "Searched candidates:"
  printf '  - %s\n' "${PLUGIN_CANDIDATES[@]}" >&2
  err "Expected because -DPLUGIN_APPGATEWAY=ON was set. Check build output under: ${APPGATEWAY_BUILD_DIR}"
  exit 1
fi

log "[OK] Located AppGateway plugin .so at: ${APPGW_PLUGIN_SRC}"
ls -la "${APPGW_PLUGIN_SRC}" || true

# Install/copy into the system plugin directory required by the task.
log "[Step 23] Installing/copying AppGateway plugin into ${SYSTEM_PLUGIN_DIR}"
if [[ "${EUID:-$(id -u)}" -eq 0 ]]; then
  mkdir -p "${SYSTEM_PLUGIN_DIR}"
  cp -f "${APPGW_PLUGIN_SRC}" "${SYSTEM_PLUGIN_DIR}/"
else
  if have_cmd sudo; then
    sudo -n mkdir -p "${SYSTEM_PLUGIN_DIR}"
    sudo -n cp -f "${APPGW_PLUGIN_SRC}" "${SYSTEM_PLUGIN_DIR}/"
  else
    err "Cannot install plugin into ${SYSTEM_PLUGIN_DIR}: need root or sudo."
    err "Plugin is present at: ${APPGW_PLUGIN_SRC}"
    exit 1
  fi
fi

log "[OK] System plugin directory now contains:"
ls -la "${SYSTEM_PLUGIN_DIR}/"*.so 2>/dev/null | grep -i AppGateway || ls -la "${SYSTEM_PLUGIN_DIR}" || true

# -----------------------------------------------------------------------------#
# Step 24: Build entservices-testframework (NOT REQUIRED FOR NOW)
# -----------------------------------------------------------------------------#
log "[Step 24] Build entservices-testframework (NOT REQUIRED FOR NOW - SKIPPED)"
log "Per request: step 24 is not required for now."

log "[DONE] Steps 1–24 completed (as applicable in this container; steps 22 and 24 skipped per request)."

# -----------------------------------------------------------------------------#
# Step 25: Set up files (COMMENTED for now)
# -----------------------------------------------------------------------------#
log "[Step 25] Set up files (COMMENTED - enable if tests require these paths/device nodes)"
log "Per request: commented/skipped for now."

# -----------------------------------------------------------------------------#
# Step 26: Run unit tests without valgrind (REQUIRED)
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 27: Run unit tests with valgrind (NOT REQUIRED for now)
# -----------------------------------------------------------------------------#
log "[Step 27] Run unit tests with valgrind (NOT REQUIRED - skipped; focusing on coverage report)"

# -----------------------------------------------------------------------------#
# Step 28: Generate coverage (REQUIRED)
# -----------------------------------------------------------------------------#
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

# -----------------------------------------------------------------------------#
# Step 29: Upload artifacts (COMMENTED for now)
# -----------------------------------------------------------------------------#
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
