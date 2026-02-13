#!/usr/bin/env bash
# L1 test runner script (host-shell)
#
# Goal:
#   Provide a local, "no act required" runner that mirrors the GitHub Actions
#   workflow `.github/workflows/L1-tests.yml` as closely as reasonable.
#
# It will:
#   - Ensure required repos are present (Thunder/ThunderTools/entservices-apis/googletest/trower-base64)
#   - Apply patches to ThunderTools and Thunder (as CI)
#   - Build dependencies (ThunderTools, Thunder, entservices-apis, googletest)
#   - Build mocks, entservices-appgateway, and entservices-testframework
#   - Run RdkServicesL1Test
#   - Generate coverage report via lcov/genhtml (HTML in ./coverage/)
#
# Notes:
#   - Some CI steps require root (apt install, /dev nodes, various /opt paths).
#     This script exposes flags/env toggles so it can run in a typical dev machine.
#   - This script is intended to be EXECUTED, not sourced.

set -euo pipefail

###############################################################################
# Small utilities
###############################################################################

log() { echo "INFO: $*"; }
warn() { echo "WARN: $*" >&2; }
err() { echo "ERROR: $*" >&2; }

# PUBLIC_INTERFACE
usage() {
  # Print usage information for this script.
  cat <<'USAGE'
run_l1_tests.sh [--no-build] [--no-test] [--no-coverage] [--with-valgrind] [--setup-files] [--install-packages] [--build-type <Debug|Release>]

Environment variables:
  GITHUB_WORKSPACE            Workspace root (default: script directory)
  THUNDER_REF                 Thunder git ref (default: R4.4.1)
  INTERFACES_REF              entservices-apis git ref (default: develop)
  GOOGLETEST_REF              googletest git ref (default: v1.15.0)

  BUILD_TYPE                  CMake build type (default: Debug)
  TOOLCHAIN_FILE              Optional CMake toolchain file (default: empty)

  ENABLE_PACKAGE_INSTALL       If "1", attempt apt install (default: 0)
  ENABLE_SETUP_FILES           If "1", attempt to create CI-like filesystem nodes (default: 0)
  ENABLE_VALGRIND              If "1", run valgrind pass (default: 0)
  ENABLE_COVERAGE              If "1", generate lcov+genhtml report (default: 1)

  CMAKE_GENERATOR              CMake generator (default: Ninja)

Outputs:
  ./rdkL1TestResultsWithoutValgrind.json
  ./rdkL1TestResultsWithValgrind.json (if valgrind run)
  ./coverage/ (if coverage enabled)
  ./valgrind_log (if valgrind run)

Examples:
  ./run_l1_tests.sh
  ENABLE_SETUP_FILES=1 ENABLE_VALGRIND=1 ./run_l1_tests.sh
  ./run_l1_tests.sh --no-coverage
USAGE
}

# PUBLIC_INTERFACE
require_cmd() {
  # Ensure a required command exists on PATH.
  local cmd="${1:?cmd required}"
  if ! command -v "$cmd" >/dev/null 2>&1; then
    err "Missing required command: $cmd"
    return 1
  fi
}

# PUBLIC_INTERFACE
detect_cmake_generator() {
  # Detect a working CMake generator for local builds.
  #
  # Preference order:
  #   1) If CMAKE_GENERATOR is explicitly set by the user, keep it.
  #   2) If ninja is available, use "Ninja".
  #   3) Otherwise, fall back to "Unix Makefiles".
  #
  # This keeps the rest of the script flow unchanged while avoiding a hard
  # dependency on ninja for environments that only have make installed.
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
cmake_configure_build_install() {
  # Configure, build and install a CMake project.
  local src_dir="${1:?src_dir required}"
  local build_dir="${2:?build_dir required}"
  local install_prefix="${3:?install_prefix required}"
  shift 3
  local extra_args=("$@")

  cmake -G "${CMAKE_GENERATOR:-Ninja}" \
    -S "$src_dir" \
    -B "$build_dir" \
    -DCMAKE_INSTALL_PREFIX="$install_prefix" \
    -DCMAKE_MODULE_PATH="$install_prefix/../tools/cmake" \
    -DGENERIC_CMAKE_MODULE_PATH="$install_prefix/../tools/cmake" \
    "${extra_args[@]}"

  cmake --build "$build_dir" -j"$(nproc)"
  cmake --install "$build_dir"
}

###############################################################################
# Repo cloning helpers (mirror .github/workflows/L1-tests.yml)
###############################################################################

# PUBLIC_INTERFACE
ensure_repo_cloned() {
  # Ensure a git repo exists at a given directory, checked out at a specific ref.
  #
  # Args:
  #   $1: target_dir (absolute path)
  #   $2: remote_url
  #   $3: ref (tag/branch/commit)
  local target_dir="${1:?target_dir required}"
  local remote_url="${2:?remote_url required}"
  local ref="${3:?ref required}"

  if [[ -d "$target_dir" && ! -d "$target_dir/.git" ]]; then
    warn "Path exists but is not a git repo; removing so it can be re-cloned: $target_dir"
    rm -rf "$target_dir"
  fi

  if [[ ! -d "$target_dir" ]]; then
    log "Cloning: $remote_url -> $target_dir (ref=$ref)"
    git clone --no-tags --depth 1 --branch "$ref" "$remote_url" "$target_dir" >/dev/null 2>&1 || {
      warn "Shallow clone failed; retrying with full clone for $remote_url"
      git clone "$remote_url" "$target_dir"
      pushd "$target_dir" >/dev/null
      git checkout -f "$ref"
      popd >/dev/null
    }
    return 0
  fi

  log "Repo exists: $target_dir (ensuring ref=$ref)"
  pushd "$target_dir" >/dev/null
  git remote set-url origin "$remote_url" >/dev/null 2>&1 || true
  git fetch --tags --force >/dev/null 2>&1 || true
  git fetch --all --prune >/dev/null 2>&1 || true
  git checkout -f "$ref" >/dev/null 2>&1 || {
    err "Failed to checkout ref '$ref' in $target_dir"
    popd >/dev/null
    return 1
  }
  popd >/dev/null
}

# PUBLIC_INTERFACE
ensure_l1_workflow_repos_present() {
  # Clone repos required by the L1-tests workflow.
  local workspace="${1:?workspace required}"

  local thunder_ref="${THUNDER_REF:-R4.4.1}"
  local interfaces_ref="${INTERFACES_REF:-develop}"
  local googletest_ref="${GOOGLETEST_REF:-v1.15.0}"

  log "Step: Ensure required repos are present (mirror L1-tests.yml)"
  ensure_repo_cloned "$workspace/Thunder" "https://github.com/rdkcentral/Thunder.git" "$thunder_ref"
  ensure_repo_cloned "$workspace/ThunderTools" "https://github.com/rdkcentral/ThunderTools.git" "R4.4.3"
  ensure_repo_cloned "$workspace/entservices-apis" "https://github.com/rdkcentral/entservices-apis.git" "$interfaces_ref"
  ensure_repo_cloned "$workspace/googletest" "https://github.com/google/googletest.git" "$googletest_ref"

  if [[ ! -d "$workspace/trower-base64" ]]; then
    log "Cloning: https://github.com/xmidt-org/trower-base64.git -> $workspace/trower-base64"
    git clone https://github.com/xmidt-org/trower-base64.git "$workspace/trower-base64"
  else
    log "Repo exists: $workspace/trower-base64"
  fi
}

###############################################################################
# Patch steps (mirror .github/workflows/L1-tests.yml)
###############################################################################

# PUBLIC_INTERFACE
apply_patches_thundertools() {
  # Apply ThunderTools patch exactly as CI does.
  local workspace="${1:?workspace required}"

  if [[ -d "$workspace/ThunderTools" && -d "$workspace/entservices-testframework" ]]; then
    log "Step: Apply patches ThunderTools (match L1-tests.yml)"
    pushd "$workspace/ThunderTools" >/dev/null
    patch -p1 <"$workspace/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch"
    popd >/dev/null
  else
    warn "ThunderTools or entservices-testframework missing; skipping ThunderTools patch step."
  fi
}

# PUBLIC_INTERFACE
apply_patches_thunder() {
  # Apply Thunder patches exactly as CI does.
  local workspace="${1:?workspace required}"

  if [[ -d "$workspace/Thunder" && -d "$workspace/entservices-testframework" ]]; then
    log "Step: Apply patches Thunder (match L1-tests.yml)"
    pushd "$workspace/Thunder" >/dev/null
    patch -p1 <"$workspace/entservices-testframework/patches/Use_Legact_Alt_Based_On_ThunderTools_R4.4.3.patch"
    patch -p1 <"$workspace/entservices-testframework/patches/error_code_R4_4.patch"
    patch -p1 <"$workspace/entservices-testframework/patches/1004-Add-support-for-project-dir.patch"
    patch -p1 <"$workspace/entservices-testframework/patches/RDKEMW-733-Add-ENTOS-IDS.patch"
    patch -p1 <"$workspace/entservices-testframework/patches/Jsonrpc_dynamic_error_handling.patch"
    popd >/dev/null
  else
    warn "Thunder or entservices-testframework missing; skipping Thunder patch step."
  fi
}

###############################################################################
# Optional CI parity steps (packages, trower-base64, filesystem nodes)
###############################################################################

# PUBLIC_INTERFACE
install_packages_if_enabled() {
  # Optionally install packages used by CI. Disabled by default.
  if [[ "${ENABLE_PACKAGE_INSTALL:-0}" != "1" ]]; then
    return 0
  fi

  log "Step: Install packages (requires sudo; mirrors CI best-effort)"
  sudo apt update
  sudo apt install -y \
    libsqlite3-dev libcurl4-openssl-dev valgrind lcov clang libsystemd-dev \
    libboost-all-dev libwebsocketpp-dev meson libcunit1 libcunit1-dev curl \
    protobuf-compiler-grpc libgrpc-dev libgrpc++-dev libjsoncpp-dev
}

# PUBLIC_INTERFACE
build_and_install_trower_base64() {
  # Build and install trower-base64 as CI does (meson+ninja).
  local workspace="${1:?workspace required}"
  require_cmd meson
  require_cmd ninja

  log "Step: Build trower-base64"
  pushd "$workspace/trower-base64" >/dev/null
  meson setup --warnlevel 3 --werror build
  ninja -C build
  sudo ninja -C build install
  popd >/dev/null
}

# PUBLIC_INTERFACE
setup_files_if_enabled() {
  # Optionally create CI-like paths and device nodes. Disabled by default.
  if [[ "${ENABLE_SETUP_FILES:-0}" != "1" ]]; then
    return 0
  fi

  log "Step: Set up files (requires sudo; mirrors CI best-effort)"
  sudo mkdir -p -m 777 \
    /tmp/test/testApp/etc/apps \
    /opt/persistent \
    /opt/secure \
    /opt/secure/reboot \
    /opt/secure/persistent \
    /opt/secure/persistent/System \
    /opt/persistent/storageManager \
    /opt/preinstall \
    /opt/logs \
    /lib/rdk \
    /run/media/sda1/logs/PreviousLogs \
    /run/sda1/UsbTestFWUpdate \
    /run/sda1/UsbProdFWUpdate \
    /run/sda2 \
    /var/run/wpa_supplicant \
    /tmp/bus/usb/devices/100-123 \
    /tmp/bus/usb/devices/101-124 \
    /tmp/block/sda/device \
    /tmp/block/sdb/device \
    /dev/disk/by-id \
    /dev

  # CI's workflow has typos around mknod checks; we do a safe best-effort.
  for devnode in /dev/sda /dev/sda1 /dev/sda2 /dev/sdb /dev/sdb1 /dev/sdb2; do
    if [[ ! -e "$devnode" ]]; then
      warn "$devnode missing; attempting mknod (may fail if not permitted)"
      sudo mknod "$devnode" c 240 0 || true
    fi
  done

  sudo touch \
    /tmp/test/testApp/etc/apps/testApp_package.json \
    /opt/rdk_maintenance.conf \
    /opt/persistent/timeZoneDST \
    /opt/standbyReason.txt \
    /opt/tmtryoptout \
    /opt/fwdnldstatus.txt \
    /opt/dcm.properties \
    /etc/device.properties \
    /etc/dcm.properties \
    /etc/authService.conf \
    /version.txt \
    /run/media/sda1/logs/PreviousLogs/logFile.txt \
    /run/sda1/HSTP11MWR_5.11p5s1_VBN_sdy.bin \
    /run/sda1/UsbTestFWUpdate/HSTP11MWR_3.11p5s1_VBN_sdy.bin \
    /run/sda1/UsbProdFWUpdate/HSTP11MWR_4.11p5s1_VBN_sdy.bin \
    /lib/rdk/getMaintenanceStartTime.sh \
    /tmp/opkg.conf \
    /tmp/bus/usb/devices/100-123/serial \
    /tmp/bus/usb/devices/101-124/serial \
    /tmp/block/sda/device/vendor \
    /tmp/block/sda/device/model \
    /tmp/block/sdb/device/vendor \
    /tmp/block/sdb/device/model

  sudo chmod -R 777 \
    /opt/rdk_maintenance.conf \
    /opt/persistent/timeZoneDST \
    /opt/standbyReason.txt \
    /opt/tmtryoptout \
    /opt/fwdnldstatus.txt \
    /opt/dcm.properties \
    /etc/device.properties \
    /etc/dcm.properties \
    /etc/authService.conf \
    /version.txt \
    /lib/rdk/getMaintenanceStartTime.sh \
    /tmp/opkg.conf \
    /tmp/bus/usb/devices/100-123/serial \
    /tmp/bus/usb/devices/101-124/serial \
    /tmp/block/sda/device/vendor \
    /tmp/block/sda/device/model \
    /tmp/block/sdb/device/vendor \
    /tmp/block/sdb/device/model
}

###############################################################################
# Build and test steps (mirror CI)
###############################################################################

# PUBLIC_INTERFACE
generate_external_headers() {
  # Generate empty headers to mute errors, matching CI step.
  local workspace="${1:?workspace required}"
  log "Step: Generate external headers"
  mkdir -p "$workspace/entservices-testframework/Tests/headers/headers/network" \
           "$workspace/entservices-testframework/Tests/headers/headers/proc"
  pushd "$workspace/entservices-testframework/Tests/headers/headers" >/dev/null
  touch rfcapi.h rbus.h pkg.h
  popd >/dev/null
}

# PUBLIC_INTERFACE
build_thunder() {
  # Configure and build Thunder in a dedicated step, printing the build output path.
  #
  # This is intentionally separate from build_all() so the runner's output clearly
  # shows Thunder being configured/built, and so users can locate Thunder build
  # artifacts quickly.
  local workspace="${1:?workspace required}"
  local build_type="${BUILD_TYPE:-Debug}"
  local toolchain="${TOOLCHAIN_FILE:-}"

  detect_cmake_generator
  require_cmd cmake

  local install_prefix="$workspace/install/usr"
  mkdir -p "$install_prefix"

  local thunder_build_dir="$workspace/build/Thunder"
  log "Thunder build directory: $thunder_build_dir"

  cmake -G "${CMAKE_GENERATOR:-Ninja}" \
    -S "$workspace/Thunder" \
    -B "$thunder_build_dir" \
    -DCMAKE_INSTALL_PREFIX="$install_prefix" \
    -DCMAKE_MODULE_PATH="$install_prefix/../tools/cmake" \
    -DGENERIC_CMAKE_MODULE_PATH="$install_prefix/../tools/cmake" \
    -DMESSAGING=ON \
    -DBUILD_TYPE="$build_type" \
    -DBINDING=127.0.0.1 \
    -DPORT=55555 \
    -DEXCEPTIONS_ENABLE=ON \
    ${toolchain:+-DCMAKE_TOOLCHAIN_FILE="$toolchain"}

  cmake --build "$thunder_build_dir" -j"$(nproc)"
}

# PUBLIC_INTERFACE
build_all() {
  # Build dependencies and targets required for L1 tests.
  local workspace="${1:?workspace required}"
  local build_type="${BUILD_TYPE:-Debug}"
  local toolchain="${TOOLCHAIN_FILE:-}"

  # Pick a generator (Ninja if present, else Unix Makefiles) unless user set one.
  detect_cmake_generator
  local generator="${CMAKE_GENERATOR}"

  require_cmd cmake
  require_cmd patch
  require_cmd git

  # CI uses python+jsonref for some tooling; local builds generally don't need it for compilation,
  # but keep here as a hint if missing tools surface.
  # require_cmd python3

  local install_prefix="$workspace/install/usr"
  mkdir -p "$install_prefix"

  log "Build type: $build_type"
  if [[ -n "$toolchain" ]]; then
    log "Toolchain file: $toolchain"
  fi

  # ThunderTools
  log "Step: Build ThunderTools"
  cmake_configure_build_install \
    "$workspace/ThunderTools" \
    "$workspace/build/ThunderTools" \
    "$install_prefix" \
    -DEXCEPTIONS_ENABLE=ON

  # Thunder
  log "Step: Build Thunder"
  cmake_configure_build_install \
    "$workspace/Thunder" \
    "$workspace/build/Thunder" \
    "$install_prefix" \
    -DMESSAGING=ON \
    -DBUILD_TYPE="$build_type" \
    -DBINDING=127.0.0.1 \
    -DPORT=55555 \
    -DEXCEPTIONS_ENABLE=ON

  # entservices-apis (CI applies RDKEMW-1007 patch; we do not do it here because this repo
  # already contains entservices-apis checkout and patch steps may require private repo access.
  # If needed, users can clone entservices-testframework and patches will apply.)
  log "Step: Build entservices-apis"
  cmake_configure_build_install \
    "$workspace/entservices-apis" \
    "$workspace/build/entservices-apis" \
    "$install_prefix" \
    -DEXCEPTIONS_ENABLE=ON

  # googletest
  log "Step: Build googletest"
  cmake_configure_build_install \
    "$workspace/googletest" \
    "$workspace/build/googletest" \
    "$install_prefix" \
    -DBUILD_TYPE="$build_type" \
    -DBUILD_GMOCK=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON

  # headers (needed before mocks/appgateway/testframework builds)
  generate_external_headers "$workspace"

  # Common flags (mirror CI)
  local common_includes=(
    "-I $workspace/entservices-testframework/Tests/headers"
    "-I $workspace/entservices-testframework/Tests"
    "-I $workspace/entservices-appgateway/helpers"
    "-I $workspace/Thunder/Source"
    "-I $workspace/Thunder/Source/core"
    "-I $workspace/install/usr/include"
    "-I $workspace/install/usr/include/WPEFramework"
  )

  local common_defines=(
    "-DEXCEPTIONS_ENABLE=ON"
    "-DUSE_THUNDER_R4=ON"
    "-DTHUNDER_VERSION=4"
    "-DTHUNDER_VERSION_MAJOR=4"
    "-DTHUNDER_VERSION_MINOR=4"
    "-DRDK_SERVICES_L1_TEST"
  )

  local coverage_flags=(
    "-fprofile-arcs"
    "-ftest-coverage"
    "--coverage"
  )

  # mocks
  log "Step: Build mocks"
  cmake -S "$workspace/entservices-testframework/Tests/mocks" \
    -B "$workspace/build/mocks" \
    -DBUILD_SHARED_LIBS=ON \
    -DRDK_SERVICES_L1_TEST=ON \
    -DUSE_THUNDER_R4=ON \
    ${toolchain:+-DCMAKE_TOOLCHAIN_FILE="$toolchain"} \
    -DCMAKE_INSTALL_PREFIX="$install_prefix" \
    -DCMAKE_MODULE_PATH="$workspace/install/tools/cmake" \
    -DCMAKE_BUILD_TYPE="$build_type" \
    -DCMAKE_CXX_FLAGS="
${common_defines[*]}
${common_includes[*]}
-include $workspace/entservices-testframework/Tests/mocks/pkg.h
${coverage_flags[*]}
-Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format=
-Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,-wrap,v_secure_system -Wl,-wrap,v_secure_popen -Wl,-wrap,v_secure_pclose -Wl,-wrap,unlink -Wl,-wrap,v_secure_system -Wl,-wrap,pclose -Wl,-wrap,setmntent -Wl,-wrap,getmntent
"
  cmake --build "$workspace/build/mocks" -j"$(nproc)"
  cmake --install "$workspace/build/mocks"

  # entservices-appgateway
  log "Step: Build entservices-appgateway"
  cmake -G "$generator" \
    -S "$workspace/entservices-appgateway" \
    -B "$workspace/build/entservices-appgateway" \
    -DCMAKE_INSTALL_PREFIX="$install_prefix" \
    -DCMAKE_MODULE_PATH="$workspace/install/tools/cmake" \
    -DCMAKE_BUILD_TYPE="$build_type" \
    -DRDK_SERVICES_L1_TEST=ON \
    -DUSE_THUNDER_R4=ON \
    -DHIDE_NON_EXTERNAL_SYMBOLS=OFF \
    -DENABLE_UNIT_TESTS=ON \
    ${toolchain:+-DCMAKE_TOOLCHAIN_FILE="$toolchain"} \
    -DCMAKE_CXX_FLAGS="
${common_defines[*]}
${common_includes[*]}
-include $workspace/entservices-testframework/Tests/mocks/pkg.h
-include $workspace/entservices-testframework/Tests/mocks/secure_wrappermock.h
${coverage_flags[*]}
-Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format=
-Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,-wrap,v_secure_system -Wl,-wrap,v_secure_popen -Wl,-wrap,v_secure_pclose -Wl,-wrap,unlink
"
  cmake --build "$workspace/build/entservices-appgateway" -j"$(nproc)"
  cmake --install "$workspace/build/entservices-appgateway"

  # entservices-testframework
  log "Step: Build entservices-testframework"
  cmake -G "$generator" \
    -S "$workspace/entservices-testframework" \
    -B "$workspace/build/entservices-testframework" \
    -DCMAKE_INSTALL_PREFIX="$install_prefix" \
    -DCMAKE_MODULE_PATH="$workspace/install/tools/cmake" \
    -DCMAKE_BUILD_TYPE="$build_type" \
    -DRDK_SERVICES_L1_TEST=ON \
    -DUSE_THUNDER_R4=ON \
    -DHIDE_NON_EXTERNAL_SYMBOLS=OFF \
    -DENABLE_UNIT_TESTS=ON \
    ${toolchain:+-DCMAKE_TOOLCHAIN_FILE="$toolchain"} \
    -DCMAKE_CXX_FLAGS="
${common_defines[*]}
${common_includes[*]}
-I ./usr/include/libdrm
-include $workspace/entservices-testframework/Tests/mocks/pkg.h
${coverage_flags[*]}
-Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format=
-Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,--no-as-needed
"
  cmake --build "$workspace/build/entservices-testframework" -j"$(nproc)"
  cmake --install "$workspace/build/entservices-testframework"
}

# PUBLIC_INTERFACE
run_tests() {
  # Run RdkServicesL1Test similarly to CI (optionally with valgrind).
  local workspace="${1:?workspace required}"
  local install_usr="$workspace/install/usr"

  if [[ ! -x "$install_usr/bin/RdkServicesL1Test" && ! -x "$install_usr/bin/RdkServicesL1Testd" ]]; then
    # CI uses RdkServicesL1Test on PATH. We'll rely on PATH but print a helpful message.
    warn "RdkServicesL1Test binary not found in $install_usr/bin (will still attempt to run via PATH)."
  fi

  local env_path="PATH=$install_usr/bin:${PATH}"
  local env_ld="LD_LIBRARY_PATH=$install_usr/lib:$install_usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"

  log "Step: Run unit tests without valgrind"

  # Prefer the canonical L1 runner binary if available (CI parity).
  if command -v RdkServicesL1Test >/dev/null 2>&1; then
    (
      export PATH="$install_usr/bin:${PATH}"
      export LD_LIBRARY_PATH="$install_usr/lib:$install_usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"
      export GTEST_OUTPUT="json:$(pwd)/rdkL1TestResults.json"
      RdkServicesL1Test
    )
    cp -f "$(pwd)/rdkL1TestResults.json" "$workspace/rdkL1TestResultsWithoutValgrind.json"
    rm -f "$(pwd)/rdkL1TestResults.json"
  else
    warn "RdkServicesL1Test not found on PATH; falling back to ctest on build tree."
    (
      export LD_LIBRARY_PATH="$install_usr/lib:$install_usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"
      ctest --test-dir "$workspace/build/entservices-appgateway" --output-on-failure
    )
  fi

  if [[ "${ENABLE_VALGRIND:-0}" == "1" ]]; then
    require_cmd valgrind
    log "Step: Run unit tests with valgrind"
    (
      export PATH="$install_usr/bin:${PATH}"
      export LD_LIBRARY_PATH="$install_usr/lib:$install_usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"
      export GTEST_OUTPUT="json:$(pwd)/rdkL1TestResults.json"
      valgrind \
        --tool=memcheck \
        --log-file=valgrind_log \
        --leak-check=yes \
        --show-reachable=yes \
        --track-fds=yes \
        --fair-sched=try \
        RdkServicesL1Test
    )
    cp -f "$(pwd)/rdkL1TestResults.json" "$workspace/rdkL1TestResultsWithValgrind.json"
    rm -f "$(pwd)/rdkL1TestResults.json"
  else
    log "Valgrind disabled (set ENABLE_VALGRIND=1 or pass --with-valgrind to enable)"
  fi

  log "Test outputs:"
  log "  $workspace/rdkL1TestResultsWithoutValgrind.json"
  if [[ "${ENABLE_VALGRIND:-0}" == "1" ]]; then
    log "  $workspace/rdkL1TestResultsWithValgrind.json"
    log "  $(pwd)/valgrind_log"
  fi

  # Silence unused variable warning (document environment setup).
  : "$env_path" "$env_ld"
}

# PUBLIC_INTERFACE
generate_coverage() {
  # Generate lcov + genhtml report as CI does, outputting ./coverage/.
  local workspace="${1:?workspace required}"

  if [[ "${ENABLE_COVERAGE:-1}" != "1" ]]; then
    log "Coverage disabled (set ENABLE_COVERAGE=1 to enable)"
    return 0
  fi

  require_cmd lcov
  require_cmd genhtml

  local lcovrc="$workspace/entservices-testframework/Tests/L1Tests/.lcovrc_l1"
  if [[ -f "$lcovrc" ]]; then
    log "Using lcovrc from testframework: $lcovrc"
    cp "$lcovrc" "$HOME/.lcovrc"
  else
    warn "lcovrc not found at $lcovrc; continuing without it"
  fi

  log "Step: Generate coverage (lcov + genhtml)"
  # CI uses -d build/entservices-appgateway
  lcov -c -o coverage.info -d "$workspace/build/entservices-appgateway"

  lcov -r coverage.info \
    '/usr/include/*' \
    '*/build/entservices-appgateway/_deps/*' \
    '*/install/usr/include/*' \
    '*/Tests/headers/*' \
    '*/Tests/mocks/*' \
    '*/Tests/L1Tests/tests/*' \
    '*/Thunder/*' \
    -o filtered_coverage.info

  rm -rf "$workspace/coverage"
  genhtml -o "$workspace/coverage" -t "entservices-appgateway coverage" filtered_coverage.info

  log "Coverage HTML generated at: $workspace/coverage/index.html"
}

###############################################################################
# Main
###############################################################################

# PUBLIC_INTERFACE
main() {
  # Entry point for local L1 build/test/coverage runner.
  local do_build=1
  local do_test=1
  local do_cov=1

  # Default toggles (can be overridden by env or flags)
  export ENABLE_PACKAGE_INSTALL="${ENABLE_PACKAGE_INSTALL:-0}"
  export ENABLE_SETUP_FILES="${ENABLE_SETUP_FILES:-0}"
  export ENABLE_VALGRIND="${ENABLE_VALGRIND:-0}"
  export ENABLE_COVERAGE="${ENABLE_COVERAGE:-1}"
  export BUILD_TYPE="${BUILD_TYPE:-Debug}"
  # Do not force a default generator here; we'll auto-detect later (or honor user-provided CMAKE_GENERATOR).
  export CMAKE_GENERATOR="${CMAKE_GENERATOR:-}"

  while [[ $# -gt 0 ]]; do
    case "$1" in
      -h|--help)
        usage
        exit 0
        ;;
      --no-build) do_build=0; shift ;;
      --no-test) do_test=0; shift ;;
      --no-coverage) do_cov=0; export ENABLE_COVERAGE=0; shift ;;
      --with-valgrind) export ENABLE_VALGRIND=1; shift ;;
      --setup-files) export ENABLE_SETUP_FILES=1; shift ;;
      --install-packages) export ENABLE_PACKAGE_INSTALL=1; shift ;;
      --build-type)
        BUILD_TYPE="${2:?--build-type requires value}"
        shift 2
        ;;
      *)
        err "Unknown argument: $1"
        usage
        exit 2
        ;;
    esac
  done

  local workspace
  workspace="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  local GITHUB_WORKSPACE="${GITHUB_WORKSPACE:-$workspace}"

  log "Workspace: $GITHUB_WORKSPACE"
  cd "$GITHUB_WORKSPACE"

  # Base requirements
  require_cmd git
  require_cmd patch
  require_cmd cmake

  # Choose a CMake generator for the build steps (unless user set one).
  detect_cmake_generator

  # Optional steps mirroring CI
  install_packages_if_enabled

  ensure_l1_workflow_repos_present "$GITHUB_WORKSPACE"

  # trower-base64 install is required in CI; locally it may already exist.
  # If meson/ninja/sudo are available, build it; otherwise warn.
  if command -v meson >/dev/null 2>&1 && command -v ninja >/dev/null 2>&1; then
    # This typically requires sudo install.
    if sudo -n true >/dev/null 2>&1; then
      build_and_install_trower_base64 "$GITHUB_WORKSPACE"
    else
      warn "Skipping trower-base64 install (sudo not available without password). Run with sudo privileges if needed."
    fi
  else
    warn "meson/ninja not found; skipping trower-base64 build/install."
  fi

  # Patches require entservices-testframework repo to exist (private token in CI).
  # Locally, users can clone it manually into workspace to enable these steps.
  apply_patches_thundertools "$GITHUB_WORKSPACE"
  apply_patches_thunder "$GITHUB_WORKSPACE"

  setup_files_if_enabled

  if [[ "$do_build" == "1" ]]; then
    log "Step: Configure/build Thunder (dedicated step)"
    build_thunder "$GITHUB_WORKSPACE"
    build_all "$GITHUB_WORKSPACE"
  else
    log "Build disabled (--no-build)"
  fi

  if [[ "$do_test" == "1" ]]; then
    run_tests "$GITHUB_WORKSPACE"
  else
    log "Tests disabled (--no-test)"
  fi

  if [[ "$do_cov" == "1" ]]; then
    generate_coverage "$GITHUB_WORKSPACE"
  else
    log "Coverage disabled (--no-coverage)"
  fi

  log "Done."
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  main "$@"
fi
