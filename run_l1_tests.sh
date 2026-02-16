#!/usr/bin/env bash
# L1 test runner script (NetworkManager-style)
#
# Goal:
#   Mirror the networkmanager-34 L1 build/test/coverage approach for this repo:
#     - NO Thunder/ThunderTools CMake patches
#     - Build only what's needed to build/run AppGateway L1 tests
#     - Build + run the AppGateway L1 test executable that compiles test_AppGateway.cpp
#     - Generate an AppGateway-only coverage report (lcov/genhtml)
#
# This script is intentionally self-contained and non-interactive.
#
# Expected repository layout (relative to this script directory):
#   ThunderTools/                 (source)
#   Thunder/                      (source)
#   entservices-apis/             (source; required by AppGateway build)
#   googletest/                   (source; optional if already provided by toolchain, but expected)
#   AppGateway/                   (plugin source)
#   Tests/L1Tests/                (L1 tests CMake; includes test_AppGateway.cpp)
#
# Output directories:
#   build_l1/                     (all build artifacts)
#   coverage-appgateway/          (AppGateway-only HTML coverage report)
#
set -euo pipefail

log()  { echo "INFO: $*"; }
warn() { echo "WARN: $*" >&2; }
err()  { echo "ERROR: $*" >&2; }

# PUBLIC_INTERFACE
usage() {
  """Print usage information for this script."""
  cat <<'USAGE'
run_l1_tests.sh [--no-build] [--no-test] [--no-coverage] [--build-type <Debug|Release>]

Environment variables:
  BUILD_TYPE            CMake build type (default: Debug)
  CMAKE_GENERATOR       CMake generator (default: Ninja if available, else Unix Makefiles)
  TOOLCHAIN_FILE        Optional CMake toolchain file
  ENABLE_COVERAGE       1 to generate coverage (default: 1)

Notes:
  - This script does not clone repositories and does not apply any patches.
  - Ensure ThunderTools/Thunder/entservices-apis/googletest exist in the workspace before running.
USAGE
}

# PUBLIC_INTERFACE
require_cmd() {
  """Ensure a required command exists on PATH."""
  local cmd="${1:?cmd required}"
  if ! command -v "$cmd" >/dev/null 2>&1; then
    err "Missing required command: $cmd"
    return 1
  fi
}

# PUBLIC_INTERFACE
detect_cmake_generator() {
  """Select a reasonable default CMake generator if not specified."""
  if [[ -n "${CMAKE_GENERATOR:-}" ]]; then
    log "CMake generator set by user: ${CMAKE_GENERATOR}"
    return 0
  fi
  if command -v ninja >/dev/null 2>&1; then
    export CMAKE_GENERATOR="Ninja"
  else
    export CMAKE_GENERATOR="Unix Makefiles"
  fi
  log "Auto-selected CMake generator: ${CMAKE_GENERATOR}"
}

# PUBLIC_INTERFACE
detect_thunder_cmake_source_dir() {
  """Return the correct Thunder CMake source dir (the one containing CMakeLists.txt)."""
  local thunder_root="${1:?thunder_root required}"

  local candidates=(
    "$thunder_root"
    "$thunder_root/Source"
    "$thunder_root/source"
    "$thunder_root/WPEFramework"
  )

  local c
  for c in "${candidates[@]}"; do
    if [[ -f "$c/CMakeLists.txt" ]]; then
      echo "$c"
      return 0
    fi
  done

  local found
  found="$(find "$thunder_root" -maxdepth 3 -name CMakeLists.txt -print -quit 2>/dev/null || true)"
  if [[ -n "$found" ]]; then
    echo "$(dirname "$found")"
    return 0
  fi

  return 1
}

# PUBLIC_INTERFACE
ensure_python_jsonref() {
  """Ensure python module jsonref exists (needed by ThunderTools JsonGenerator in many environments)."""
  if [[ "${ENSURE_JSONREF:-1}" != "1" ]]; then
    log "Skipping jsonref ensure step (ENSURE_JSONREF=0)."
    return 0
  fi

  if ! command -v python3 >/dev/null 2>&1; then
    err "python3 not found; cannot ensure 'jsonref'. Install python3 or set ENSURE_JSONREF=0."
    return 1
  fi

  if python3 -c "import jsonref" >/dev/null 2>&1; then
    log "Python dependency satisfied: jsonref is already importable."
    return 0
  fi

  log "Python dependency missing: jsonref. Attempting install (user-site)."
  if ! python3 -m pip --version >/dev/null 2>&1; then
    warn "pip not available; attempting bootstrap with: python3 -m ensurepip --upgrade"
    python3 -m ensurepip --upgrade >/dev/null 2>&1 || true
  fi
  if ! python3 -m pip --version >/dev/null 2>&1; then
    err "python3 pip unavailable. Install python3-pip (or set ENSURE_JSONREF=0)."
    return 1
  fi

  python3 -m pip install --user --no-input --disable-pip-version-check -q jsonref
  python3 -c "import jsonref" >/dev/null 2>&1 || {
    err "jsonref still not importable after install; check PYTHONPATH/user-site permissions."
    return 1
  }
  log "Installed/ensured Python dependency: jsonref."
}

# PUBLIC_INTERFACE
cmake_configure() {
  """Run cmake configure with common arguments."""
  local src="${1:?src required}"
  local bld="${2:?build dir required}"
  shift 2
  cmake -G "${CMAKE_GENERATOR}" -S "$src" -B "$bld" "$@"
}

# PUBLIC_INTERFACE
cmake_build() {
  """Run cmake build with parallelism."""
  local bld="${1:?build dir required}"
  cmake --build "$bld" -j"$(nproc)"
}

# PUBLIC_INTERFACE
generate_coverage_appgateway_only() {
  """Generate AppGateway-only coverage report from a given build directory."""
  local repo_root="${1:?repo root required}"
  local build_dir="${2:?build dir required}"

  if [[ "${ENABLE_COVERAGE:-1}" != "1" ]]; then
    log "Coverage disabled (ENABLE_COVERAGE=0)."
    return 0
  fi

  require_cmd lcov
  require_cmd genhtml

  log "Generating coverage (AppGateway-only)"
  local raw_info="$repo_root/coverage.raw.info"
  local filtered_info="$repo_root/coverage-appgateway.info"
  local out_dir="$repo_root/coverage-appgateway"

  rm -rf "$out_dir"
  rm -f "$raw_info" "$filtered_info"

  # Capture from build dir where .gcda/.gcno should be.
  lcov -c -d "$build_dir" -o "$raw_info"

  # Remove obvious noise, then extract only AppGateway sources.
  lcov -r "$raw_info" \
    '/usr/include/*' \
    '*/build*/*' \
    '*/_deps/*' \
    '*/googletest/*' \
    '*/Thunder/*' \
    '*/ThunderTools/*' \
    '*/entservices-apis/*' \
    '*/Tests/*' \
    -o "$filtered_info"

  # Keep only AppGateway plugin sources.
  lcov --extract "$filtered_info" \
    "*/AppGateway/*" \
    "$repo_root/AppGateway/*" \
    -o "$filtered_info"

  genhtml -o "$out_dir" -t "AppGateway L1 coverage" "$filtered_info"

  log "Coverage report: $out_dir/index.html"
}

# PUBLIC_INTERFACE
main() {
  """Script entry point."""
  local do_build=1
  local do_test=1
  local do_cov=1

  export BUILD_TYPE="${BUILD_TYPE:-Debug}"
  export ENABLE_COVERAGE="${ENABLE_COVERAGE:-1}"

  while [[ $# -gt 0 ]]; do
    case "$1" in
      -h|--help) usage; exit 0 ;;
      --no-build) do_build=0; shift ;;
      --no-test) do_test=0; shift ;;
      --no-coverage) do_cov=0; export ENABLE_COVERAGE=0; shift ;;
      --build-type) BUILD_TYPE="${2:?--build-type requires value}"; shift 2 ;;
      *) err "Unknown argument: $1"; usage; exit 2 ;;
    esac
  done

  local repo_root
  repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  cd "$repo_root"

  require_cmd cmake
  require_cmd git
  ensure_python_jsonref
  detect_cmake_generator

  # Validate expected directories exist (no cloning here).
  for d in Thunder ThunderTools entservices-apis googletest; do
    if [[ ! -d "$repo_root/$d" ]]; then
      err "Missing required dependency directory: $repo_root/$d"
      err "This script does not fetch dependencies. Ensure repos exist before running."
      exit 1
    fi
  done

  # Build layout (NetworkManager-style: dedicated build dir, staged installs inside build dir)
  local build_root="$repo_root/build_l1"
  local prefix_root="$build_root/install"
  local tt_prefix="$prefix_root/thundertools"
  local thunder_prefix="$prefix_root/thunder"
  local apis_prefix="$prefix_root/entservices-apis"
  local gtest_prefix="$prefix_root/googletest"

  mkdir -p "$build_root" "$tt_prefix" "$thunder_prefix" "$apis_prefix" "$gtest_prefix"

  # ThunderTools build/install
  local tt_build="$build_root/ThunderTools"
  if [[ "$do_build" == "1" ]]; then
    log "Configuring/building/installing ThunderTools"
    cmake_configure "$repo_root/ThunderTools" "$tt_build" \
      -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
      -DCMAKE_INSTALL_PREFIX="$tt_prefix" \
      -DEXCEPTIONS_ENABLE=ON \
      ${TOOLCHAIN_FILE:+-DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"}
    cmake_build "$tt_build"
    cmake --install "$tt_build"
  fi

  # Thunder build/install (use ThunderTools module path so FindProxyStubGenerator/JsonGenerator work)
  local thunder_src
  thunder_src="$(detect_thunder_cmake_source_dir "$repo_root/Thunder")" || {
    err "Could not find Thunder CMakeLists.txt under $repo_root/Thunder"
    exit 1
  }

  local thunder_build="$build_root/Thunder"
  if [[ "$do_build" == "1" ]]; then
    log "Configuring/building/installing Thunder from: $thunder_src"
    cmake_configure "$thunder_src" "$thunder_build" \
      -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
      -DCMAKE_INSTALL_PREFIX="$thunder_prefix" \
      -DCMAKE_MODULE_PATH="$tt_prefix/../tools/cmake" \
      -DGENERIC_CMAKE_MODULE_PATH="$tt_prefix/../tools/cmake" \
      -DMESSAGING=ON \
      -DBINDING=127.0.0.1 \
      -DPORT=55555 \
      -DEXCEPTIONS_ENABLE=ON \
      ${TOOLCHAIN_FILE:+-DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"}
    cmake_build "$thunder_build"
    cmake --install "$thunder_build"
  fi

  # entservices-apis build/install (so AppGateway links against interfaces if needed)
  local apis_build="$build_root/entservices-apis"
  if [[ "$do_build" == "1" ]]; then
    log "Configuring/building/installing entservices-apis"
    cmake_configure "$repo_root/entservices-apis" "$apis_build" \
      -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
      -DCMAKE_INSTALL_PREFIX="$apis_prefix" \
      -DCMAKE_PREFIX_PATH="$thunder_prefix" \
      -DWPEFramework_DIR="$thunder_prefix/lib/cmake/WPEFramework" \
      -DCMAKE_MODULE_PATH="$tt_prefix/../tools/cmake" \
      -DGENERIC_CMAKE_MODULE_PATH="$tt_prefix/../tools/cmake" \
      -DEXCEPTIONS_ENABLE=ON \
      ${TOOLCHAIN_FILE:+-DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"}
    cmake_build "$apis_build"
    cmake --install "$apis_build"
  fi

  # googletest build/install (some environments prefer using installed config)
  local gtest_build="$build_root/googletest"
  if [[ "$do_build" == "1" ]]; then
    log "Configuring/building/installing googletest"
    cmake_configure "$repo_root/googletest" "$gtest_build" \
      -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
      -DCMAKE_INSTALL_PREFIX="$gtest_prefix" \
      -DBUILD_GMOCK=ON \
      -DBUILD_SHARED_LIBS=OFF \
      -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
      ${TOOLCHAIN_FILE:+-DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"}
    cmake_build "$gtest_build"
    cmake --install "$gtest_build"
  fi

  # AppGateway L1 tests build (must compile test_AppGateway.cpp)
  #
  # We build the L1 tests CMake project under Tests/L1Tests if present.
  # This is the most direct way to ensure test_AppGateway.cpp is built and executed.
  local l1_src="$repo_root/Tests/L1Tests"
  if [[ ! -f "$l1_src/CMakeLists.txt" ]]; then
    err "Missing L1 tests CMakeLists.txt at: $l1_src/CMakeLists.txt"
    exit 1
  fi

  local l1_build="$build_root/L1Tests"
  if [[ "$do_build" == "1" ]]; then
    log "Configuring/building AppGateway L1 tests (should include test_AppGateway.cpp)"
    cmake_configure "$l1_src" "$l1_build" \
      -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
      -DCMAKE_PREFIX_PATH="$thunder_prefix;$apis_prefix;$gtest_prefix" \
      -DWPEFramework_DIR="$thunder_prefix/lib/cmake/WPEFramework" \
      -DCMAKE_MODULE_PATH="$tt_prefix/../tools/cmake" \
      -DGENERIC_CMAKE_MODULE_PATH="$tt_prefix/../tools/cmake" \
      -DRDK_SERVICES_L1_TEST=ON \
      -DUSE_THUNDER_R4=ON \
      -DENABLE_COVERAGE="$ENABLE_COVERAGE" \
      ${TOOLCHAIN_FILE:+-DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE"}
    cmake_build "$l1_build"
  fi

  if [[ "$do_test" == "1" ]]; then
    log "Running AppGateway L1 tests"
    # Prefer ctest so we don't hardcode the binary name; this matches the usual L1 flow.
    (
      export LD_LIBRARY_PATH="$thunder_prefix/lib:$thunder_prefix/lib/wpeframework/plugins:$apis_prefix/lib:${LD_LIBRARY_PATH:-}"
      ctest --test-dir "$l1_build" --output-on-failure
    )
  fi

  if [[ "$do_cov" == "1" ]]; then
    generate_coverage_appgateway_only "$repo_root" "$l1_build"
  fi

  log "Done."
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  main "$@"
fi
