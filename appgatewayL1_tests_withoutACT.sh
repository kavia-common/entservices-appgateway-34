#!/usr/bin/env bash
set -euo pipefail

# -----------------------------------------------------------------------------
# appgatewayL1_tests_withoutACT.sh
#
# Purpose:
#   Build prerequisites (Thunder/ThunderTools/entservices-apis/googletest),
#   build entservices-appgateway plugins, build and run AppGateway L1 tests,
#   and generate HTML coverage for AppGateway sources.
#
# Key requirements (authoritative):
#   - Compile AppGateway, AppGatewayCommon, AppNotifications, but L1 testing is
#     currently only for AppGateway.
#   - Ensure coverage flags are applied while compiling/linking, so .gcno/.gcda
#     are generated.
#   - Build and execute the L1 test binary from:
#       Tests/L1Tests/tests/test_AppGateway.cpp
#   - Generate HTML coverage report for AppGateway plugin sources.
#   - Fix install-time failure creating /etc/app-gateway (no root in CI):
#       avoid running install steps that attempt to write to /etc.
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
  WORKSPACE_ROOT           Defaults to /home/kavia/workspace/code-generation
  INSTALL_ROOT             Defaults to \$REPO_DIR/install
  BUILD_ROOT               Defaults to /tmp/entservices-appgateway-build
  COVERAGE_TOOLCHAIN_FILE  Optional CMake toolchain file for coverage (if present)
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

cmake_configure_build_noinstall() {
  # Like cmake_configure_build_install, but does NOT run cmake --install.
  # Used to avoid writing to /etc during install in CI/non-root environments.
  local component_name="$1"
  local src_dir="$2"
  local build_dir="$3"
  shift 3
  local -a extra_args=("$@")

  if [[ ! -d "${src_dir}" ]]; then
    err "CMake source directory not found: ${src_dir}"
    return 1
  fi

  mkdir -p "${build_dir}"

  # Always specify generator explicitly.
  local -a gen_args=()
  if have_cmd ninja; then
    gen_args=(-G Ninja)
  else
    gen_args=(-G "Unix Makefiles")
  fi

  log "${component_name}: CMake configure (NO-INSTALL): cmake ${gen_args[*]} -S ${src_dir} -B ${build_dir} (verbose; log: ${build_dir}/configure_verbose.log)"
  cmake "${gen_args[@]}" -S "${src_dir}" -B "${build_dir}" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_VERBOSE_MAKEFILE=ON \
    -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE \
    --log-level=VERBOSE \
    "${extra_args[@]}" 2>&1 | tee "${build_dir}/configure_verbose.log"

  log "${component_name}: CMake build (NO-INSTALL): ${build_dir}"
  cmake --build "${build_dir}" -- -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)"
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

INSTALL_ROOT="${INSTALL_ROOT:-${REPO_DIR}/install}"
INSTALL_USR="${INSTALL_ROOT}/usr"

BUILD_ROOT="${BUILD_ROOT:-/tmp/entservices-appgateway-build}"

if [[ "${CLEAN}" -eq 1 ]]; then
  log "[CLEAN] Removing build outputs under BUILD_ROOT=${BUILD_ROOT} and install under INSTALL_ROOT=${INSTALL_ROOT}"
  rm -rf "${BUILD_ROOT}" || true
  rm -rf "${INSTALL_ROOT}" || true
fi

mkdir -p "${INSTALL_USR}"

# -----------------------------------------------------------------------------
# Coverage flags (force in addition to any toolchain file)
# -----------------------------------------------------------------------------
# We apply both compile and link flags; this ensures:
#   - .gcno files emitted at compile-time
#   - .gcda files emitted when test binaries are executed
#
# Note: We keep -O0/-g for debug-friendly coverage and avoid aggressive inlining.
COVERAGE_C_FLAGS="-O0 -g --coverage -fprofile-arcs -ftest-coverage"
COVERAGE_CXX_FLAGS="-O0 -g --coverage -fprofile-arcs -ftest-coverage"
COVERAGE_LINKER_FLAGS="--coverage"

# Optional toolchain file (if present).
COVERAGE_TOOLCHAIN_FILE_DEFAULT="${WORKSPACE_ROOT}/networkmanager-34/entservices-testframework/Tests/gcc-with-coverage.cmake"
COVERAGE_TOOLCHAIN_FILE="${COVERAGE_TOOLCHAIN_FILE:-${COVERAGE_TOOLCHAIN_FILE_DEFAULT}}"

# -----------------------------------------------------------------------------
# Steps 1-22 (deps) mostly unchanged
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

log "[Step 20] Coverage toolchain file (optional)"
if [[ -f "${COVERAGE_TOOLCHAIN_FILE}" ]]; then
  log "Coverage toolchain found: ${COVERAGE_TOOLCHAIN_FILE}"
else
  warn "Coverage toolchain file not found at: ${COVERAGE_TOOLCHAIN_FILE}"
  warn "Proceeding with explicit coverage flags via -DCMAKE_{C,CXX}_FLAGS and -DCMAKE_{EXE,SHARED}_LINKER_FLAGS."
fi

log "[Step 21] Build googletest (configure/build/install into install/usr)"
if [[ -d "${GTEST_DIR}" ]]; then
  EXTRA_GTEST_CMAKE_ARGS=(
    -DBUILD_GTEST=ON
    -DBUILD_GMOCK=ON
    -Dgtest_force_shared_crt=OFF
    -DINSTALL_GTEST=ON
    -DCMAKE_C_FLAGS="${COVERAGE_C_FLAGS}"
    -DCMAKE_CXX_FLAGS="${COVERAGE_CXX_FLAGS}"
    -DCMAKE_EXE_LINKER_FLAGS="${COVERAGE_LINKER_FLAGS}"
    -DCMAKE_SHARED_LINKER_FLAGS="${COVERAGE_LINKER_FLAGS}"
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
# Step 23 (single-step replacement for former 23a + 23c):
#   Build AppGatewayL1Test by configuring/building ONLY Tests/L1Tests (no install),
#   and stage the AppGateway plugin .so from the same build tree for runtime.
#
# Why this exists:
#   - A full build + install of entservices-appgateway attempts to write under
#     /etc/app-gateway/, which fails in CI/non-root flows.
#   - Building only Tests/L1Tests avoids install completely, yet still builds:
#       * AppGatewayL1Test (runnable binary)
#       * libWPEFrameworkAppGateway.so (plugin shared library) as a dependency
#   - Coverage is captured from this same build tree in Step 28.
# -----------------------------------------------------------------------------
log "[Step 23] Build AppGatewayL1Test via Tests/L1Tests (NO INSTALL; coverage enabled) + stage AppGateway plugin"

APPGATEWAY_SRC_DIR="${REPO_DIR}"
if have_cmd git && [[ -d "${REPO_DIR}/.git" ]]; then
  APPGATEWAY_SRC_DIR="$(git -C "${REPO_DIR}" rev-parse --show-toplevel 2>/dev/null || echo "${REPO_DIR}")"
fi

if [[ ! -f "${APPGATEWAY_SRC_DIR}/CMakeLists.txt" ]]; then
  err "Step 23 source dir does not contain CMakeLists.txt: ${APPGATEWAY_SRC_DIR}"
  err "This must point at the entservices-appgateway-34 repo root."
  exit 1
fi

APPGATEWAY_BUILD_DIR="${BUILD_ROOT}/entservices-appgateway-l1tests-only"

L1TESTS_ONLY_CMAKE_ARGS=(
  -DCMAKE_PREFIX_PATH="${INSTALL_USR}"
  # Ensure find_package() can locate Thunder plugin package config when building
  # ONLY Tests/L1Tests (no full install of entservices-appgateway).
  -DWPEFrameworkPlugins_DIR="${INSTALL_USR}/lib/cmake/WPEFrameworkPlugins"

  # Avoid SecurityAgent headers (SecurityTokenUtil.h) during L1 test builds.
  -DDISABLE_SECURITY_TOKEN=ON

  # Authoritative fix: compile tests/mocks against Thunder R4 interface headers so
  # MOCK_METHOD(..., override) matches the actual virtual methods.
  -DUSE_THUNDER_R4=ON

  -DRDK_SERVICES_L1_TEST=ON

  # Build the plugin sources so the required .so files are produced
  -DPLUGIN_APPGATEWAY=ON
  -DPLUGIN_APPGATEWAYCOMMON=ON

  # AppNotifications is optional in this L1 flow.
  #
  # Default is OFF, because some L1-only build trees won't generate this target output,
  # and we don't want Step 23 to fail due to an unrelated optional plugin.
  #
  # To enable in CI or locally:
  #   ENABLE_APPNOTIFICATIONS=1 ./appgatewayL1_tests_withoutACT.sh
  -DPLUGIN_APPNOTIFICATIONS=$([[ "${ENABLE_APPNOTIFICATIONS:-0}" == "1" ]] && echo ON || echo OFF)

  -DCMAKE_C_FLAGS="${COVERAGE_C_FLAGS}"
  -DCMAKE_CXX_FLAGS="${COVERAGE_CXX_FLAGS}"
  -DCMAKE_EXE_LINKER_FLAGS="${COVERAGE_LINKER_FLAGS}"
  -DCMAKE_SHARED_LINKER_FLAGS="${COVERAGE_LINKER_FLAGS}"
)

if [[ -f "${COVERAGE_TOOLCHAIN_FILE}" ]]; then
  L1TESTS_ONLY_CMAKE_ARGS+=(-DCMAKE_TOOLCHAIN_FILE="${COVERAGE_TOOLCHAIN_FILE}")
fi

# Configure/build ONLY the Tests/L1Tests subdir so we get AppGatewayL1Test without install-time /etc writes.
cmake_configure_build_noinstall \
  "entservices-appgateway-l1tests-only" \
  "${APPGATEWAY_SRC_DIR}/Tests/L1Tests" \
  "${APPGATEWAY_BUILD_DIR}" \
  "${L1TESTS_ONLY_CMAKE_ARGS[@]}"

# Extra safety: explicitly build the plugin/shared-object targets that the runtime needs.
# Depending on the generator and dependency graph, building only the default target may
# build the test binary but not all plugin .so outputs.
log "Step 23: Ensuring required .so artifacts are built (AppGateway + L1TestsIN)"
cmake --build "${APPGATEWAY_BUILD_DIR}" --target AppGatewayL1Test -- -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)"
# Best-effort: L1TestsIN may be skipped if no legacy sources are enabled; AppGateway plugin should exist.
#
# NOTE:
# In this repository, the AppGateway plugin CMake target name is "AppGateway"
# (MODULE_NAME = ${NAMESPACE}${PLUGIN_NAME}, and NAMESPACE is empty in our L1 build).
# The previous "WPEFrameworkAppGateway" target does not exist here and was only present
# in older/out-of-tree builds; keep any unknown targets best-effort, but ensure we build
# the real in-tree one.
cmake --build "${APPGATEWAY_BUILD_DIR}" --target "AppGateway" -- -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)" 2>/dev/null || true
cmake --build "${APPGATEWAY_BUILD_DIR}" --target "AppGatewayCommon" -- -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)" 2>/dev/null || true
if [[ "${ENABLE_APPNOTIFICATIONS:-0}" == "1" ]]; then
  cmake --build "${APPGATEWAY_BUILD_DIR}" --target "AppNotifications" -- -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)" 2>/dev/null || true
fi
cmake --build "${APPGATEWAY_BUILD_DIR}" --target "L1TestsIN" -- -j"$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 2)" 2>/dev/null || true

# Stage required plugin shared libraries built as part of the L1Tests-only build.
# Runtime loads plugins from: install/usr/lib/wpeframework/plugins
LOCAL_PLUGIN_DIR="${INSTALL_USR}/lib/wpeframework/plugins"
mkdir -p "${LOCAL_PLUGIN_DIR}"

stage_all_plugins_from_dir_best_effort() {
  local src_dir="$1"
  local desc="$2"

  if [[ ! -d "${src_dir}" ]]; then
    warn "No plugin dir found for staging (${desc}): ${src_dir}"
    return 0
  fi

  local count=0
  while IFS= read -r -d '' f; do
    cp -f "${f}" "${LOCAL_PLUGIN_DIR}/"
    count=$((count + 1))
  done < <(find "${src_dir}" -maxdepth 1 -type f -name "*.so*" -print0 2>/dev/null)

  if [[ "${count}" -eq 0 ]]; then
    warn "No .so outputs found to stage from ${src_dir} (${desc})."
  else
    log "[OK] Staged ${count} shared libraries from ${src_dir} (${desc})"
  fi
}

# Build output layout:
#   - <build>/AppGateway/libAppGateway.so
#   - <build>/AppGatewayCommon/libAppGatewayCommon.so
#   - <build>/*.so  (L1TestsIN module, if enabled)
#   - <build>/AppNotifications/... (optional)
#
# Staging is done first (best-effort per-plugin directory), then we validate the
# staged runtime directory. This avoids false failures where the build output
# exists and was staged, but a later build-tree glob check still fails.
stage_all_plugins_from_dir_best_effort "${APPGATEWAY_BUILD_DIR}/AppGateway" "AppGateway"
stage_all_plugins_from_dir_best_effort "${APPGATEWAY_BUILD_DIR}/AppGatewayCommon" "AppGatewayCommon"

# AppNotifications staging is best-effort (never fatal in default flow)
stage_all_plugins_from_dir_best_effort "${APPGATEWAY_BUILD_DIR}/AppNotifications" "AppNotifications"

# Final validation must check what runtime will use: the staged plugin directory.
# Required for L1 tests:
#  - AppGateway plugin:      libAppGateway.so*
#  - AppGatewayCommon plugin libAppGatewayCommon.so*
#
# Also validate the L1TestsIN module if it was produced by the build tree.
if ! ls -1 "${LOCAL_PLUGIN_DIR}/libAppGateway.so"* >/dev/null 2>&1; then
  err "Step 23 validation failed: libAppGateway.so missing from staged plugin directory."
  err "Expected in: ${LOCAL_PLUGIN_DIR}"
  err "Directory listing:"
  ls -la "${LOCAL_PLUGIN_DIR}" || true
  exit 1
fi
if ! ls -1 "${LOCAL_PLUGIN_DIR}/libAppGatewayCommon.so"* >/dev/null 2>&1; then
  err "Step 23 validation failed: libAppGatewayCommon.so missing from staged plugin directory."
  err "Expected in: ${LOCAL_PLUGIN_DIR}"
  err "Directory listing:"
  ls -la "${LOCAL_PLUGIN_DIR}" || true
  exit 1
fi

# L1TestsIN plugin module: validate only if it was built and therefore staged.
# (The module is typically a .so placed directly under the build root.)
if ls -1 "${APPGATEWAY_BUILD_DIR}/"*.so* >/dev/null 2>&1; then
  if ! ls -1 "${LOCAL_PLUGIN_DIR}/"*.so* >/dev/null 2>&1; then
    err "Step 23 validation failed: expected staged .so artifacts but none found in ${LOCAL_PLUGIN_DIR}."
    ls -la "${LOCAL_PLUGIN_DIR}" || true
    exit 1
  fi
else
  warn "No L1TestsIN module .so produced in build root (${APPGATEWAY_BUILD_DIR}); skipping L1TestsIN staging validation."
fi

# Optional: if enabled, ensure we staged *something* for AppNotifications.
if [[ "${ENABLE_APPNOTIFICATIONS:-0}" == "1" ]]; then
  if ! ls -1 "${LOCAL_PLUGIN_DIR}/libAppNotifications.so"* >/dev/null 2>&1; then
    warn "ENABLE_APPNOTIFICATIONS=1 but libAppNotifications.so not found in staged plugin dir (${LOCAL_PLUGIN_DIR})."
    warn "Continuing (non-fatal), since L1 tests only require AppGateway."
  fi
fi

ls -la "${LOCAL_PLUGIN_DIR}/"*.so* 2>/dev/null || true

# The executable is expected in this build tree:
#   <build>/AppGatewayL1Test
if [[ -x "${APPGATEWAY_BUILD_DIR}/AppGatewayL1Test" ]]; then
  log "[OK] Built AppGatewayL1Test at: ${APPGATEWAY_BUILD_DIR}/AppGatewayL1Test"
else
  warn "AppGatewayL1Test not found at expected path: ${APPGATEWAY_BUILD_DIR}/AppGatewayL1Test"
  warn "Step 26 will still attempt other locations, but coverage capture expects this build dir."
fi

# -----------------------------------------------------------------------------
# Step 24: Ensure required mock headers are available via install prefix include
# -----------------------------------------------------------------------------
log "[Step 24] Copy required mock headers into install prefix include/Tests/mocks"
MOCKS_SRC_DIR="${REPO_DIR}/Tests/mocks"
MOCKS_DST_DIR="${INSTALL_USR}/include/Tests/mocks"
mkdir -p "${MOCKS_DST_DIR}"
cp -f "${MOCKS_SRC_DIR}/Module.h" "${MOCKS_DST_DIR}/Module.h"
cp -f "${MOCKS_SRC_DIR}/ServiceMock.h" "${MOCKS_DST_DIR}/ServiceMock.h"
cp -f "${MOCKS_SRC_DIR}/ThunderPortability.h" "${MOCKS_DST_DIR}/ThunderPortability.h"
log "[OK] Mock headers copied to: ${MOCKS_DST_DIR}"

# -----------------------------------------------------------------------------
# Step 25: (kept skipped)
# -----------------------------------------------------------------------------
log "[Step 25] Set up files (COMMENTED - enable if tests require these paths/device nodes)"
log "Per request: commented/skipped for now."

# -----------------------------------------------------------------------------
# Step 25b: Stage AppGateway config root from repo (NO /etc dependency)
#
# AppGatewayImplementation L1 tests may try to open:
#   /etc/app-gateway/resolution.base.json
# when no override config path is provided.
#
# In CI/non-root environments we cannot create /etc/app-gateway, so we stage the
# repo's default file into /tmp and export APPGATEWAY_CONFIG_PATH so the plugin
# can locate it without falling back to /etc.
# -----------------------------------------------------------------------------
log "[Step 25b] Stage AppGateway resolution.base.json from repo into writable config root"

APPGW_CFG_ROOT="/tmp/app-gateway"
APPGW_CFG_FILE_SRC="${REPO_DIR}/AppGateway/resolutions/resolution.base.json"
APPGW_CFG_FILE_DST="${APPGW_CFG_ROOT}/resolution.base.json"

mkdir -p "${APPGW_CFG_ROOT}"
if [[ -f "${APPGW_CFG_FILE_SRC}" ]]; then
  cp -f "${APPGW_CFG_FILE_SRC}" "${APPGW_CFG_FILE_DST}"
  log "[OK] Staged: ${APPGW_CFG_FILE_DST}"
else
  warn "Repo resolution.base.json not found at: ${APPGW_CFG_FILE_SRC}"
  warn "Tests may still fail if they rely on fallback config loading."
fi

# -----------------------------------------------------------------------------
# Step 26: Build and run AppGateway L1 test binary (REQUIRED for .gcda)
# -----------------------------------------------------------------------------
log "[Step 26] Build and run AppGateway L1 tests (REQUIRED - generates .gcda for coverage)"

(
  export PATH="${INSTALL_USR}/bin:${PATH}"

  # Ensure plugin and libraries are discoverable at runtime.
  # Include:
  #  - install/usr/lib (+ lib64 on some distros)
  #  - install/usr/lib/wpeframework/plugins (local plugin staging, real .so names)
  export LD_LIBRARY_PATH="${INSTALL_USR}/lib:${INSTALL_USR}/lib64:${INSTALL_USR}/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"

  # Point AppGatewayImplementation at a non-/etc config root (staged in Step 25b).
  # NOTE: This must be honored by the implementation/test harness; it is the
  # mechanism used by the L1 environment to avoid /etc/app-gateway dependency.
  export APPGATEWAY_CONFIG_PATH="${APPGW_CFG_ROOT}"

  export GTEST_OUTPUT="json:$(pwd)/AppGatewayL1TestResults.json"

  TEST_BIN=""
  if have_cmd AppGatewayL1Test; then
    TEST_BIN="AppGatewayL1Test"
  else
    # Preferred explicit paths (authoritative per attached log):
    #   - install prefix: install/usr/bin/AppGatewayL1Test
    #   - build tree:     <build>/Tests/L1Tests/AppGatewayL1Test
    if [[ -x "${INSTALL_USR}/bin/AppGatewayL1Test" ]]; then
      TEST_BIN="${INSTALL_USR}/bin/AppGatewayL1Test"
    elif [[ -x "${APPGATEWAY_BUILD_DIR}/AppGatewayL1Test" ]]; then
      # Step 23c (Tests/L1Tests-only build dir)
      TEST_BIN="${APPGATEWAY_BUILD_DIR}/AppGatewayL1Test"
    elif [[ -x "${APPGATEWAY_BUILD_DIR}/AppGatewayL1Test.exe" ]]; then
      TEST_BIN="${APPGATEWAY_BUILD_DIR}/AppGatewayL1Test.exe"
    elif [[ -x "${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test" ]]; then
      # Legacy location (full tree build)
      TEST_BIN="${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test"
    elif [[ -x "${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test.exe" ]]; then
      TEST_BIN="${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test.exe"
    fi
  fi

  if [[ -z "${TEST_BIN}" ]]; then
    err "AppGatewayL1Test not found."
    err "Expected it from building Tests/L1Tests (includes Tests/L1Tests/tests/test_AppGateway.cpp)."
    err "Checked:"
    err "  - PATH (${INSTALL_USR}/bin)"
    err "  - ${INSTALL_USR}/bin/AppGatewayL1Test"
    err "  - ${APPGATEWAY_BUILD_DIR}/Tests/L1Tests/AppGatewayL1Test"
    exit 1
  fi

  log "Running L1 test binary: ${TEST_BIN}"
  "${TEST_BIN}"

  cp -f "$(pwd)/AppGatewayL1TestResults.json" "${REPO_DIR}/AppGatewayL1TestResultsWithoutValgrind.json"
  rm -f "$(pwd)/AppGatewayL1TestResults.json"
)
log "[OK] Step 26 complete: ${REPO_DIR}/AppGatewayL1TestResultsWithoutValgrind.json"

# -----------------------------------------------------------------------------
# Step 28: Generate coverage HTML report (AppGateway-only)
# -----------------------------------------------------------------------------
log "[Step 28] Generate coverage HTML report (AppGateway sources only)"

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
APPGW_ONLY_INFO="${REPO_DIR}/appgateway_only_coverage.info"

rm -rf "${COVERAGE_DIR}" "${COVERAGE_INFO}" "${FILTERED_INFO}" "${APPGW_ONLY_INFO}" || true

# Capture from the build tree that produced the test executable and linked objects.
# With Step 23b commented, this is the Step 23c L1Tests-only build dir; it still
# compiles AppGateway sources (with coverage flags) as part of dependency linkage.
lcov -c -o "${COVERAGE_INFO}" -d "${APPGATEWAY_BUILD_DIR}"

# Filter out system and third-party paths.
lcov -r "${COVERAGE_INFO}" \
  '/usr/include/*' \
  "*/${APPGATEWAY_BUILD_DIR##*/}/_deps/*" \
  '*/install/usr/include/*' \
  '*/Tests/headers/*' \
  '*/Tests/mocks/*' \
  '*/Tests/L1Tests/tests/*' \
  '*/Thunder/*' \
  -o "${FILTERED_INFO}"

# Restrict report to AppGateway plugin sources (and its common helpers if desired).
# Authoritative requirement: "coverage html report for all the files in AppGateway plugin source".
lcov -e "${FILTERED_INFO}" \
  '*/AppGateway/*' \
  -o "${APPGW_ONLY_INFO}"

genhtml -o "${COVERAGE_DIR}" -t "entservices-appgateway (AppGateway-only) coverage" "${APPGW_ONLY_INFO}"

log "[OK] Coverage generated at: ${COVERAGE_DIR}/index.html"

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
echo "  COVERAGE_FLAGS(CXX)=${COVERAGE_CXX_FLAGS}"
echo "  APPGATEWAY_BUILD_DIR=${APPGATEWAY_BUILD_DIR}"
echo "  TEST_RUNNER=AppGatewayL1Test"
echo "  COVERAGE_DIR=${COVERAGE_DIR}"
