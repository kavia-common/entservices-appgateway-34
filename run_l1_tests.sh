#!/usr/bin/env bash
# L1 test runner script (host-shell)
#
# Goal:
#   Provide a local, "no act required" runner that mirrors the GitHub Actions
#   workflow `.github/workflows/L1-tests.yml` as closely as reasonable.
#
# It will:
#   - Ensure required repos are present (Thunder/ThunderTools/entservices-apis/googletest/trower-base64)
#   - Apply patches to ThunderTools and Thunder (as CI) [only if entservices-testframework is present]
#   - Build dependencies (ThunderTools, Thunder, entservices-apis, googletest)
#   - Build entservices-appgateway (from repo root)
#   - Run RdkServicesL1Test (or fall back to ctest)
#   - Generate coverage report via lcov/genhtml (HTML in ./coverage/)
#
# Minimal AppGateway-only L1 coverage path:
#   This script defaults to MINIMAL_L1=1 and skips:
#     - entservices-testframework build/install
#     - mocks build (often requires host deps like gstreamer/libdrm/curl)
#   This is intentional to keep AppGateway L1 coverage runnable in constrained CI images.
#
# Notes:
#   - Some CI steps require root (apt install, /dev nodes, various /opt paths).
#     This script exposes flags/env toggles so it can run in a typical dev machine.
#   - This script is intended to be EXECUTED, not sourced.
#
# Important local-build note (permission issue):
#   ThunderTools "cmake --install" may fail on some systems with:
#     file INSTALL cannot set permissions .../install/usr/sbin/ProxyStubGenerator
#   when the install prefix is on a filesystem that disallows chmod/chown changes
#   (common in sandboxed/overlay environments).
#
#   To keep local builds unprivileged and robust, this script installs ThunderTools
#   into a user-writable prefix by default, and points subsequent CMake builds to
#   that prefix's CMake Find*.cmake modules and generator binaries.
#
#   If you explicitly want the legacy shared prefix behavior (installing ThunderTools
#   into ./install/usr), set:
#     THUNDERTOOLS_INSTALL_MODE=shared
#
#   Otherwise (default):
#     THUNDERTOOLS_INSTALL_MODE=user

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
run_l1_tests.sh [--no-build] [--no-test] [--no-coverage] [--with-valgrind] [--setup-files] [--install-packages] [--build-type <Debug|Release>] [--full-deps]

Environment variables:
  GITHUB_WORKSPACE             Workspace root (default: script directory)
  THUNDER_REF                  Thunder git ref (default: R4.4.1)
  INTERFACES_REF               entservices-apis git ref (default: develop)
  GOOGLETEST_REF               googletest git ref (default: v1.15.0)

  BUILD_TYPE                   CMake build type (default: Debug)
  TOOLCHAIN_FILE               Optional CMake toolchain file (default: empty)

  ENABLE_PACKAGE_INSTALL        If "1", attempt apt install (default: 0)
  ENABLE_SETUP_FILES            If "1", attempt to create CI-like filesystem nodes (default: 0)
  ENABLE_VALGRIND               If "1", run valgrind pass (default: 0)
  ENABLE_COVERAGE               If "1", generate lcov+genhtml report (default: 1)

  # Minimal/full dependency controls (minimal is default)
  MINIMAL_L1                    If "1" (default), build/run only what is required for AppGateway
                                L1 coverage (AppGateway + L1 tests + coverage), skipping mocks and
                                entservices-testframework build/install.
                                If "0", attempt a fuller CI-like dependency build.
  ENABLE_FETCH_DEPS             If "1", allow cloning/updating external repos from network.
                                Default: 0 (use repos already present in the workspace).
  ENABLE_BUILD_MOCKS            If "1", attempt to build testframework mocks (may require system deps
                                like gstreamer/libdrm/curl). Default: 0.
  ENABLE_BUILD_TESTFRAMEWORK    If "1", build/install entservices-testframework. Default: 0.

  CMAKE_GENERATOR               CMake generator (default: Ninja)

ThunderTools install behavior (local-permission safe):
  THUNDERTOOLS_INSTALL_MODE     "user" (default) or "shared"
                                - user: install ThunderTools into ./install_thundertools/usr
                                        to avoid chmod/chown permission failures.
                                - shared: install ThunderTools into ./install/usr (legacy/CI-like),
                                          may fail in restricted environments.

Thunder install behavior (local-permission safe):
  THUNDER_INSTALL_MODE          "user" (default) or "shared"
                                - user: install Thunder into ./install_thunder/usr (permission-safe)
                                - shared: install Thunder into ./install/usr (legacy/CI-like),
                                          may fail in restricted environments (chmod on cmake package dirs)

  Note: Script exports CMAKE_PREFIX_PATH and WPEFramework_DIR based on the selected Thunder prefix
        so subsequent builds/tests pick up that WPEFramework installation.

Outputs:
  ./rdkL1TestResultsWithoutValgrind.json
  ./rdkL1TestResultsWithValgrind.json (if valgrind run)
  ./coverage/ (if coverage enabled)
  ./valgrind_log (if valgrind run)

Examples:
  ./run_l1_tests.sh
  ENABLE_SETUP_FILES=1 ENABLE_VALGRIND=1 ./run_l1_tests.sh
  ./run_l1_tests.sh --no-coverage
  THUNDERTOOLS_INSTALL_MODE=shared ./run_l1_tests.sh
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
ensure_python_jsonref() {
  # Ensure Python package 'jsonref' is available for JsonGenerator (non-interactive).
  #
  # Thunder/ThunderTools JsonGenerator depends on the Python module `jsonref`.
  # Some environments (local runners/CI images) do not have it preinstalled, which causes
  # CMake configure to fail in FindJsonGenerator.cmake with:
  #   "Install jsonref first" / "JsonGenerator generator failed."
  #
  # Strategy (non-interactive, no entservices-testframework dependency):
  #   1) Verify importability via: python3 -c "import jsonref"
  #   2) Only if missing: ensure pip exists (python3 -m pip, bootstrap via ensurepip best-effort)
  #   3) Install via: python3 -m pip install --user jsonref
  #
  # Env controls:
  #   ENSURE_JSONREF=1 (default) to enable this step; set to 0 to skip.
  if [[ "${ENSURE_JSONREF:-1}" != "1" ]]; then
    log "Skipping jsonref ensure step (ENSURE_JSONREF=0)."
    return 0
  fi

  if ! command -v python3 >/dev/null 2>&1; then
    err "python3 not found; cannot ensure 'jsonref' for JsonGenerator. Install python3 or set ENSURE_JSONREF=0 to skip."
    return 1
  fi

  # Only install when actually missing.
  if python3 -c "import jsonref" >/dev/null 2>&1; then
    log "Python dependency satisfied: jsonref is already importable."
    return 0
  fi

  log "Python dependency missing: jsonref. Attempting non-interactive install (user-site)."

  # Ensure pip exists (try ensurepip first, then proceed). Keep non-interactive.
  if ! python3 -m pip --version >/dev/null 2>&1; then
    warn "pip not available for python3; attempting bootstrap: python3 -m ensurepip --upgrade"
    python3 -m ensurepip --upgrade >/dev/null 2>&1 || true
  fi

  if ! python3 -m pip --version >/dev/null 2>&1; then
    err "python3 pip is not available and could not be bootstrapped. Please install python3-pip (or equivalent) or set ENSURE_JSONREF=0 to skip."
    return 1
  fi

  # Install to the current user's site-packages (no sudo). Non-interactive.
  python3 -m pip install --user --no-input --disable-pip-version-check -q jsonref

  # Re-check import (fail fast if still missing).
  if ! python3 -c "import jsonref" >/dev/null 2>&1; then
    err "Failed to make 'jsonref' importable after pip install. Check pip/user-site permissions and PYTHONPATH."
    return 1
  fi

  log "Installed/ensured Python dependency: jsonref."
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
  local cmake_module_path="${4:?cmake_module_path required}"
  shift 4
  local extra_args=("$@")

  cmake -G "${CMAKE_GENERATOR:-Ninja}" \
    -S "$src_dir" \
    -B "$build_dir" \
    -DCMAKE_INSTALL_PREFIX="$install_prefix" \
    -DCMAKE_MODULE_PATH="$cmake_module_path" \
    -DGENERIC_CMAKE_MODULE_PATH="$cmake_module_path" \
    "${extra_args[@]}"

  cmake --build "$build_dir" -j"$(nproc)"
  cmake --install "$build_dir"
}

# PUBLIC_INTERFACE
safe_stage_thunder_install_artifacts() {
  # Stage a minimal, permission-safe "install" for Thunder (WPEFramework) without invoking
  # `cmake --install`, which can fail in restricted/overlay filesystems with errors like:
  #   file INSTALL cannot set permissions on ".../lib/cmake/WPEFramework/common"
  #
  # We copy only the typical artifacts required by downstream CMake config-mode and builds:
  #   - include/
  #   - lib/ (including wpeframework/* and proxystubs)
  #   - lib/cmake/ (WPEFrameworkConfig.cmake, etc.)
  #
  # This avoids any chmod/chown operations performed by CMake's install scripts.
  #
  # Args:
  #   $1: thunder_build_dir
  #   $2: thunder_install_prefix (destination)
  local thunder_build_dir="${1:?thunder_build_dir required}"
  local thunder_install_prefix="${2:?thunder_install_prefix required}"

  log "Thunder install: using permission-safe staged copy (skipping cmake --install)"
  log "  from build dir: $thunder_build_dir"
  log "  to prefix:      $thunder_install_prefix"

  mkdir -p "$thunder_install_prefix"

  # Use rsync if available (best for copying trees), otherwise fall back to cp -a.
  #
  # NOTE: bash does NOT allow `local fn() {}` nested function definitions.
  # The prior code used `local copy_tree() { ... }`, which triggers:
  #   syntax error near unexpected token `('
  #
  # We implement the helper as a small subshell script and invoke it with args.
  local copy_tree_sh
  copy_tree_sh="$(cat <<'COPY_TREE_SH'
src="$1"
dst="$2"

if [[ ! -d "$src" ]]; then
  exit 0
fi

mkdir -p "$dst"
if command -v rsync >/dev/null 2>&1; then
  rsync -a --delete "$src/" "$dst/"
else
  rm -rf "$dst"/*
  cp -a "$src/." "$dst/"
fi
COPY_TREE_SH
)"

  # Preferred source: the install tree inside the build directory (common with CMake).
  local staged_root="$thunder_build_dir/_install"
  local staged_usr="$staged_root"

  # Some projects stage under <build>/_install or <build>/install; try both.
  if [[ ! -d "$staged_usr" ]]; then
    staged_root="$thunder_build_dir/install"
    staged_usr="$staged_root"
  fi

  # If no staged install tree exists, fall back to copying from known output locations.
  if [[ -d "$staged_usr" ]]; then
    bash -c "$copy_tree_sh" -- "$staged_usr/include" "$thunder_install_prefix/include"
    bash -c "$copy_tree_sh" -- "$staged_usr/lib" "$thunder_install_prefix/lib"
    bash -c "$copy_tree_sh" -- "$staged_usr/etc" "$thunder_install_prefix/etc"
    return 0
  fi

  # Fallback heuristic: copy from common build output directories.
  warn "Thunder build did not produce a staged install tree; using heuristic copy of build outputs."

  # Headers: often not generated, but if there are any exported headers under Source/, copy none here.
  # Downstream builds typically rely on installed headers; if missing, they likely already exist from
  # a prior successful install. We still try common locations below.
  if [[ -d "$thunder_build_dir/include" ]]; then
    bash -c "$copy_tree_sh" -- "$thunder_build_dir/include" "$thunder_install_prefix/include"
  fi

  # Libraries: copy from build tree if present.
  mkdir -p "$thunder_install_prefix/lib"
  find "$thunder_build_dir" -maxdepth 4 -type f \( -name "libWPEFramework*.so*" -o -name "libWPEFramework*.a" \) -exec cp -a {} "$thunder_install_prefix/lib/" \; 2>/dev/null || true

  # CMake package config: common install location in build tree might be present already
  # (but in our failure case, install prefix partially exists). If present, keep it.
  if [[ -d "$thunder_install_prefix/lib/cmake/WPEFramework" ]]; then
    log "Thunder cmake package dir already present: $thunder_install_prefix/lib/cmake/WPEFramework"
  else
    warn "Thunder cmake package dir not found under prefix; downstream config-mode may fail if WPEFrameworkConfig.cmake is missing."
  fi
}

###############################################################################
# Patch helpers (non-interactive, git-format aware)
###############################################################################

# PUBLIC_INTERFACE
is_git_format_patch() {
  """Return 0 if the patch appears to be a git-format patch (has diff --git and/or commit headers)."""
  local patch_file="${1:?patch_file required}"
  # "diff --git" is the strongest signal; "commit " header appears in patches exported from git show.
  if grep -qE '^(diff --git |commit [0-9a-f]{7,40}$)' "$patch_file" 2>/dev/null; then
    return 0
  fi
  return 1
}

# PUBLIC_INTERFACE
apply_patch_non_interactive() {
  # Apply a patch file to a git repo directory in a non-interactive way.
  #
  # Behavior:
  #   1) If patch is git-format (diff --git / commit headers): use `git apply` (with --3way).
  #      - Skip cleanly if already applied (or reverse-applied).
  #   2) Otherwise: use `patch` but auto-detect working strip level (-pN) via --dry-run.
  #      - Apply with --batch/--forward to avoid prompts; treat "already applied" as success.
  #
  # Args:
  #   $1: repo_dir (git working tree)
  #   $2: patch_file (path to patch)
  local repo_dir="${1:?repo_dir required}"
  local patch_file="${2:?patch_file required}"

  if [[ ! -d "$repo_dir/.git" ]]; then
    warn "Not a git repo: $repo_dir (skipping patch $patch_file)"
    return 0
  fi
  if [[ ! -f "$patch_file" ]]; then
    warn "Patch file missing: $patch_file (skipping)"
    return 0
  fi

  pushd "$repo_dir" >/dev/null

  # Git-format patches: prefer git apply to avoid strip-level prompts.
  if is_git_format_patch "$patch_file"; then
    # First check: does it apply cleanly?
    if git apply --check "$patch_file" >/dev/null 2>&1; then
      log "Applying (git apply) $(basename "$patch_file") in $repo_dir"
      # --3way helps when context differs slightly; still non-interactive.
      if ! git apply --3way "$patch_file"; then
        warn "git apply failed for $patch_file; continuing."
      fi
      popd >/dev/null
      return 0
    fi

    # Second check: maybe already applied? (reverse would apply cleanly)
    if git apply --reverse --check "$patch_file" >/dev/null 2>&1; then
      log "Patch already applied; skipping: $(basename "$patch_file")"
      popd >/dev/null
      return 0
    fi

    # If neither forward nor reverse check works, do best-effort 3way apply.
    warn "Patch does not apply cleanly (and not detected as already-applied). Best-effort git apply --3way: $(basename "$patch_file")"
    if ! git apply --3way "$patch_file"; then
      warn "Best-effort git apply still failed; continuing."
    fi
    popd >/dev/null
    return 0
  fi

  # Non-git patches: use `patch` with auto -pN detection.
  local p_level=""
  local p
  for p in 0 1 2 3 4 5 6; do
    # --batch avoids prompts; -t treats reversed/already applied as success in dry-run probing.
    if patch --dry-run --batch -t -p"$p" <"$patch_file" >/dev/null 2>&1; then
      p_level="$p"
      break
    fi
  done

  if [[ -z "$p_level" ]]; then
    warn "Could not find a working patch strip level (-pN) for $patch_file in $repo_dir; skipping."
    popd >/dev/null
    return 0
  fi

  log "Applying (patch) $(basename "$patch_file") with -p${p_level} in $repo_dir"
  # --forward: if already applied/reversed, skip without prompting.
  # --batch: never prompt.
  if ! patch --batch --forward -p"$p_level" <"$patch_file"; then
    warn "patch tool failed for $patch_file; continuing."
  fi

  popd >/dev/null
}

###############################################################################
# ThunderTools / Thunder install-prefix selection (permission-safe defaults)
###############################################################################

# PUBLIC_INTERFACE
compute_thundertools_prefixes() {
  # Decide where to install ThunderTools and which module path to use.
  #
  # This avoids a known failure during `cmake --install`:
  #   file INSTALL cannot set permissions on .../usr/sbin/ProxyStubGenerator
  #
  # Outputs (echo as "key=value" lines so caller can eval them safely):
  #   THUNDERTOOLS_INSTALL_PREFIX=...
  #   THUNDERTOOLS_MODULE_PATH=...
  local workspace="${1:?workspace required}"

  local mode="${THUNDERTOOLS_INSTALL_MODE:-user}"
  local tt_install_prefix
  local tt_module_path

  if [[ "$mode" == "shared" ]]; then
    tt_install_prefix="$workspace/install/usr"
    tt_module_path="$tt_install_prefix/../tools/cmake"
  else
    # Default: isolate ThunderTools into a user-writable prefix.
    # This prevents chmod/chown issues from affecting the rest of the build.
    tt_install_prefix="$workspace/install_thundertools/usr"
    tt_module_path="$tt_install_prefix/../tools/cmake"
  fi

  echo "THUNDERTOOLS_INSTALL_PREFIX=$tt_install_prefix"
  echo "THUNDERTOOLS_MODULE_PATH=$tt_module_path"
}

# PUBLIC_INTERFACE
compute_thunder_prefixes() {
  # Decide where to install Thunder (WPEFramework) so local runs don't fail due to
  # chmod/chown limitations of the filesystem (common in sandbox/overlay setups).
  #
  # The failure we want to avoid is typically:
  #   file INSTALL cannot set permissions on .../install/usr/lib/cmake/WPEFramework/common
  #
  # Outputs (echo as "key=value" lines so caller can eval them safely):
  #   THUNDER_INSTALL_PREFIX=...
  #   THUNDER_CMAKE_PREFIX_PATH=...   (should be exported as CMAKE_PREFIX_PATH)
  #   THUNDER_WPEFRAMEWORK_DIR=...    (directory containing WPEFrameworkConfig.cmake)
  local workspace="${1:?workspace required}"

  local mode="${THUNDER_INSTALL_MODE:-user}"
  local thunder_install_prefix

  if [[ "$mode" == "shared" ]]; then
    thunder_install_prefix="$workspace/install/usr"
  else
    # Default: isolate Thunder into a user-writable prefix.
    thunder_install_prefix="$workspace/install_thunder/usr"
  fi

  echo "THUNDER_INSTALL_PREFIX=$thunder_install_prefix"
  echo "THUNDER_CMAKE_PREFIX_PATH=$thunder_install_prefix"
  echo "THUNDER_WPEFRAMEWORK_DIR=$thunder_install_prefix/lib/cmake/WPEFramework"
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
# NEW: Repair/detect invalid "empty dirs" when fetch is disabled
###############################################################################

# PUBLIC_INTERFACE
ensure_git_repo_or_die() {
  # Ensure a directory is a valid git repo; if it's not, attempt to repair it.
  #
  # Repair strategy:
  #   - If ENABLE_FETCH_DEPS=1: delete and re-clone.
  #   - If ENABLE_FETCH_DEPS=0: fail with a clear error (because we cannot fetch),
  #     rather than proceeding to cmake errors like "missing CMakeLists.txt".
  local workspace="${1:?workspace required}"
  local name="${2:?name required}"          # e.g. Thunder
  local repo_dir="${3:?repo_dir required}"  # full path
  local remote_url="${4:?remote_url required}"
  local ref="${5:?ref required}"

  if [[ -d "$repo_dir" && -d "$repo_dir/.git" ]]; then
    return 0
  fi

  # Common failure mode from the log context: directory exists but is NOT a git repo (often empty).
  if [[ -d "$repo_dir" && ! -d "$repo_dir/.git" ]]; then
    warn "$name exists but is not a git repo: $repo_dir"
  fi
  if [[ ! -d "$repo_dir" ]]; then
    warn "$name repo directory missing: $repo_dir"
  fi

  if [[ "${ENABLE_FETCH_DEPS:-0}" == "1" ]]; then
    warn "Attempting to repair $name by re-cloning (ENABLE_FETCH_DEPS=1)."
    ensure_repo_cloned "$repo_dir" "$remote_url" "$ref"
    return 0
  fi

  err "Cannot proceed: $name is not a valid git clone at $repo_dir and ENABLE_FETCH_DEPS=0."
  err "Set ENABLE_FETCH_DEPS=1 (or pass --full-deps) to allow re-clone/repair."
  return 1
}

###############################################################################
# NEW: Thunder source dir detection (Thunder root may not contain CMakeLists.txt)
###############################################################################

# PUBLIC_INTERFACE
detect_thunder_cmake_source_dir() {
  # Determine the correct Thunder CMake source directory (the one containing CMakeLists.txt).
  #
  # Observed failure (authoritative log context):
  #   CMake Error: The source directory ".../Thunder" does not appear to contain CMakeLists.txt.
  #
  # Thunder often builds from Thunder/Source.
  #
  # Prints the detected path to stdout.
  local workspace="${1:?workspace required}"
  local repo_root="$workspace/Thunder"

  local candidates=(
    "$repo_root"
    "$repo_root/Source"
    "$repo_root/source"
    "$repo_root/WPEFramework"
  )

  local c
  for c in "${candidates[@]}"; do
    if [[ -f "$c/CMakeLists.txt" ]]; then
      echo "$c"
      return 0
    fi
  done

  # Fallback: find first CMakeLists.txt under Thunder (bounded depth).
  # We keep this simple and robust across versions.
  local found
  found="$(find "$repo_root" -maxdepth 3 -name CMakeLists.txt -print -quit 2>/dev/null || true)"
  if [[ -n "$found" ]]; then
    echo "$(dirname "$found")"
    return 0
  fi

  return 1
}

###############################################################################
# Patch steps (mirror .github/workflows/L1-tests.yml)
###############################################################################

# PUBLIC_INTERFACE
apply_patches_thundertools() {
  # Apply ThunderTools patch non-interactively:
  # - If git-format patch: use git apply (with --3way), skip if already applied.
  # - Else: auto-detect patch -pN.
  local workspace="${1:?workspace required}"

  local repo_dir="$workspace/ThunderTools"
  local patch_file="$workspace/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch"

  if [[ ! -d "$repo_dir" ]]; then
    warn "ThunderTools missing; skipping ThunderTools patch step."
    return 0
  fi
  if [[ ! -f "$patch_file" ]]; then
    warn "ThunderTools patch file missing ($patch_file); skipping ThunderTools patch step."
    return 0
  fi

  log "Step: Apply patches ThunderTools (match L1-tests.yml; non-interactive)"
  apply_patch_non_interactive "$repo_dir" "$patch_file"
}

# PUBLIC_INTERFACE
apply_patches_thunder() {
  # Apply Thunder patches, non-interactively, in a git-format aware manner.
  local workspace="${1:?workspace required}"

  local repo_dir="$workspace/Thunder"
  local patches_dir="$workspace/entservices-testframework/patches"

  if [[ ! -d "$repo_dir" || ! -d "$workspace/entservices-testframework" ]]; then
    warn "Thunder or entservices-testframework missing; skipping Thunder patch step."
    return 0
  fi

  log "Step: Apply patches Thunder (match L1-tests.yml; non-interactive)"

  # Keep the patch list as in CI.
  apply_patch_non_interactive "$repo_dir" "$patches_dir/Use_Legact_Alt_Based_On_ThunderTools_R4.4.3.patch"
  apply_patch_non_interactive "$repo_dir" "$patches_dir/error_code_R4_4.patch"
  apply_patch_non_interactive "$repo_dir" "$patches_dir/1004-Add-support-for-project-dir.patch"
  apply_patch_non_interactive "$repo_dir" "$patches_dir/RDKEMW-733-Add-ENTOS-IDS.patch"
  apply_patch_non_interactive "$repo_dir" "$patches_dir/Jsonrpc_dynamic_error_handling.patch"
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
  # Configure, build and install Thunder in a dedicated step.
  #
  # Fixes two local failure modes:
  #   1) Thunder dir exists but isn't a real git repo (often empty) -> handled earlier.
  #   2) Thunder repo root may not contain CMakeLists.txt -> auto-detect a correct subdir (e.g. Thunder/Source).
  local workspace="${1:?workspace required}"
  local build_type="${BUILD_TYPE:-Debug}"
  local toolchain="${TOOLCHAIN_FILE:-}"

  detect_cmake_generator
  require_cmd cmake

  # ThunderTools prefix/module-path (needed to run ProxyStubGenerator/JsonGenerator during Thunder build).
  local thundertools_install_prefix=""
  local thundertools_module_path=""
  while IFS='=' read -r k v; do
    case "$k" in
      THUNDERTOOLS_INSTALL_PREFIX) thundertools_install_prefix="$v" ;;
      THUNDERTOOLS_MODULE_PATH) thundertools_module_path="$v" ;;
    esac
  done < <(compute_thundertools_prefixes "$workspace")

  # Thunder (WPEFramework) install prefix (permission-safe default).
  local thunder_install_prefix=""
  local thunder_cmake_prefix_path=""
  local thunder_wpeframework_dir=""
  while IFS='=' read -r k v; do
    case "$k" in
      THUNDER_INSTALL_PREFIX) thunder_install_prefix="$v" ;;
      THUNDER_CMAKE_PREFIX_PATH) thunder_cmake_prefix_path="$v" ;;
      THUNDER_WPEFRAMEWORK_DIR) thunder_wpeframework_dir="$v" ;;
    esac
  done < <(compute_thunder_prefixes "$workspace")

  mkdir -p "$thunder_install_prefix"

  # Export so subsequent configure steps (and also this Thunder configure) can find WPEFramework via config mode.
  export CMAKE_PREFIX_PATH="${thunder_cmake_prefix_path}${CMAKE_PREFIX_PATH:+:$CMAKE_PREFIX_PATH}"
  export WPEFramework_DIR="$thunder_wpeframework_dir"

  local thunder_src_dir
  if ! thunder_src_dir="$(detect_thunder_cmake_source_dir "$workspace")"; then
    err "Could not locate Thunder CMake source directory (no CMakeLists.txt found under $workspace/Thunder)."
    err "If Thunder is not cloned correctly, set ENABLE_FETCH_DEPS=1 (or pass --full-deps) to re-clone."
    return 1
  fi

  local thunder_build_dir="$workspace/build/Thunder"
  log "Thunder source dir (CMakeLists.txt): $thunder_src_dir"
  log "Thunder build directory: $thunder_build_dir"
  log "Thunder install mode: ${THUNDER_INSTALL_MODE:-user}"
  log "Thunder install prefix: $thunder_install_prefix"
  log "Exported CMAKE_PREFIX_PATH: $CMAKE_PREFIX_PATH"
  log "Exported WPEFramework_DIR: $WPEFramework_DIR"
  log "ThunderTools CMake module path (for generators): $thundertools_module_path"

  cmake -G "${CMAKE_GENERATOR:-Ninja}" \
    -S "$thunder_src_dir" \
    -B "$thunder_build_dir" \
    -DCMAKE_INSTALL_PREFIX="$thunder_install_prefix" \
    -DCMAKE_MODULE_PATH="$thundertools_module_path" \
    -DGENERIC_CMAKE_MODULE_PATH="$thundertools_module_path" \
    -DMESSAGING=ON \
    -DBUILD_TYPE="$build_type" \
    -DBINDING=127.0.0.1 \
    -DPORT=55555 \
    -DEXCEPTIONS_ENABLE=ON \
    ${toolchain:+-DCMAKE_TOOLCHAIN_FILE="$toolchain"}

  cmake --build "$thunder_build_dir" -j"$(nproc)"

  # IMPORTANT:
  # Avoid `cmake --install` for Thunder because it can fail in restricted environments
  # (overlay/sandbox filesystems) with "file INSTALL cannot set permissions".
  #
  # Instead, do a permission-safe staged copy of only the required artifacts.
  safe_stage_thunder_install_artifacts "$thunder_build_dir" "$thunder_install_prefix"
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

  # CI installs everything into ./install/usr. Locally, we keep "product" artifacts there,
  # but Thunder itself is installed into a user-writable prefix by default to avoid chmod failures.
  local install_prefix="$workspace/install/usr"
  mkdir -p "$install_prefix"

  # Choose ThunderTools install prefix in a permission-safe way.
  local thundertools_install_prefix=""
  local thundertools_module_path=""
  while IFS='=' read -r k v; do
    case "$k" in
      THUNDERTOOLS_INSTALL_PREFIX) thundertools_install_prefix="$v" ;;
      THUNDERTOOLS_MODULE_PATH) thundertools_module_path="$v" ;;
    esac
  done < <(compute_thundertools_prefixes "$workspace")

  # Choose Thunder install prefix in a permission-safe way.
  local thunder_install_prefix=""
  local thunder_cmake_prefix_path=""
  local thunder_wpeframework_dir=""
  while IFS='=' read -r k v; do
    case "$k" in
      THUNDER_INSTALL_PREFIX) thunder_install_prefix="$v" ;;
      THUNDER_CMAKE_PREFIX_PATH) thunder_cmake_prefix_path="$v" ;;
      THUNDER_WPEFRAMEWORK_DIR) thunder_wpeframework_dir="$v" ;;
    esac
  done < <(compute_thunder_prefixes "$workspace")

  mkdir -p "$thundertools_install_prefix" "$thundertools_module_path" "$thunder_install_prefix"

  # Export so *all* subsequent CMake config steps locate Thunder via config mode.
  export CMAKE_PREFIX_PATH="${thunder_cmake_prefix_path}${CMAKE_PREFIX_PATH:+:$CMAKE_PREFIX_PATH}"
  export WPEFramework_DIR="$thunder_wpeframework_dir"

  log "Build type: $build_type"
  if [[ -n "$toolchain" ]]; then
    log "Toolchain file: $toolchain"
  fi
  log "ThunderTools install mode: ${THUNDERTOOLS_INSTALL_MODE:-user}"
  log "ThunderTools install prefix: $thundertools_install_prefix"
  log "ThunderTools CMake module path: $thundertools_module_path"
  log "Thunder install mode: ${THUNDER_INSTALL_MODE:-user}"
  log "Thunder install prefix: $thunder_install_prefix"
  log "Exported CMAKE_PREFIX_PATH: $CMAKE_PREFIX_PATH"
  log "Exported WPEFramework_DIR: $WPEFramework_DIR"

  # ThunderTools
  log "Step: Build ThunderTools"
  cmake_configure_build_install \
    "$workspace/ThunderTools" \
    "$workspace/build/ThunderTools" \
    "$thundertools_install_prefix" \
    "$thundertools_module_path" \
    -DEXCEPTIONS_ENABLE=ON

  # For the rest of the build, point CMake to ThunderTools' Find*.cmake modules and tools
  # from the user-writable prefix.
  local cmake_module_path_for_rest="$thundertools_module_path"

  # Thunder (install into user-writable prefix by default)
  local thunder_src_dir
  if ! thunder_src_dir="$(detect_thunder_cmake_source_dir "$workspace")"; then
    err "Could not locate Thunder CMake source directory (no CMakeLists.txt found under $workspace/Thunder)."
    return 1
  fi

  log "Step: Build Thunder"
  # Do NOT call cmake --install for Thunder here (see build_thunder()) as it can fail due to
  # chmod/chown permission restrictions in some CI/overlay filesystems.
  cmake -G "${CMAKE_GENERATOR:-Ninja}" \
    -S "$thunder_src_dir" \
    -B "$workspace/build/Thunder" \
    -DCMAKE_INSTALL_PREFIX="$thunder_install_prefix" \
    -DCMAKE_MODULE_PATH="$cmake_module_path_for_rest" \
    -DGENERIC_CMAKE_MODULE_PATH="$cmake_module_path_for_rest" \
    -DMESSAGING=ON \
    -DBUILD_TYPE="$build_type" \
    -DBINDING=127.0.0.1 \
    -DPORT=55555 \
    -DEXCEPTIONS_ENABLE=ON
  cmake --build "$workspace/build/Thunder" -j"$(nproc)"
  safe_stage_thunder_install_artifacts "$workspace/build/Thunder" "$thunder_install_prefix"

  # entservices-apis
  log "Step: Build entservices-apis"

  local thunder_install_prefix_local=""
  local thunder_wpeframework_dir_local=""
  while IFS='=' read -r k v; do
    case "$k" in
      THUNDER_INSTALL_PREFIX) thunder_install_prefix_local="$v" ;;
      THUNDER_WPEFRAMEWORK_DIR) thunder_wpeframework_dir_local="$v" ;;
    esac
  done < <(compute_thunder_prefixes "$workspace")

  export CMAKE_PREFIX_PATH="${thunder_install_prefix_local}${CMAKE_PREFIX_PATH:+:$CMAKE_PREFIX_PATH}"
  export WPEFramework_DIR="$thunder_wpeframework_dir_local"

  local thunder_include_root="$thunder_install_prefix_local/include"
  local thunder_wpeframework_include="$thunder_include_root/WPEFramework"

  local install_include_root="$install_prefix/include"
  local install_wpeframework_include="$install_include_root/WPEFramework"

  rm -rf "$workspace/build/entservices-apis"

  cmake_configure_build_install \
    "$workspace/entservices-apis" \
    "$workspace/build/entservices-apis" \
    "$install_prefix" \
    "$cmake_module_path_for_rest" \
    -DEXCEPTIONS_ENABLE=ON \
    -DWPEFramework_DIR="$thunder_wpeframework_dir_local" \
    -DCMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH" \
    -DCMAKE_CXX_FLAGS="-I$thunder_wpeframework_include -I$install_wpeframework_include" \
    -DCMAKE_C_FLAGS="-I$thunder_wpeframework_include -I$install_wpeframework_include"

  # googletest (build only)
  log "Step: Build googletest"
  cmake -G "${CMAKE_GENERATOR:-Ninja}" \
    -S "$workspace/googletest" \
    -B "$workspace/build/googletest" \
    -DCMAKE_INSTALL_PREFIX="$install_prefix" \
    -DCMAKE_MODULE_PATH="$cmake_module_path_for_rest" \
    -DGENERIC_CMAKE_MODULE_PATH="$cmake_module_path_for_rest" \
    -DBUILD_TYPE="$build_type" \
    -DBUILD_GMOCK=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON
  cmake --build "$workspace/build/googletest" -j"$(nproc)"

  # headers (only if testframework present)
  if [[ -d "$workspace/entservices-testframework/Tests" ]]; then
    generate_external_headers "$workspace"
  else
    warn "entservices-testframework not present; skipping external header generation."
  fi

  # Common flags (mirror CI)
  local thunder_install_prefix_for_builds=""
  while IFS='=' read -r k v; do
    case "$k" in
      THUNDER_INSTALL_PREFIX) thunder_install_prefix_for_builds="$v" ;;
    esac
  done < <(compute_thunder_prefixes "$workspace")

  local thunder_include_root_for_builds="$thunder_install_prefix_for_builds/include"
  local thunder_wpeframework_include_for_builds="$thunder_include_root_for_builds/WPEFramework"

  local common_include_dirs=(
    "$workspace/entservices-testframework/Tests/headers"
    "$workspace/entservices-testframework/Tests"
    "$workspace/entservices-appgateway/helpers"
    "$workspace/Thunder/Source"
    "$workspace/Thunder/Source/core"
    "$workspace/install/usr/include"
    "$workspace/install/usr/include/WPEFramework"
    "$thunder_include_root_for_builds"
    "$thunder_wpeframework_include_for_builds"
  )

  local common_includes_flags=""
  for d in "${common_include_dirs[@]}"; do
    common_includes_flags+=" -I $d"
  done

  local common_include_dirs_cmake
  common_include_dirs_cmake="$(IFS=';'; echo "${common_include_dirs[*]}")"

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

  # mocks (optional)
  if [[ "${ENABLE_BUILD_MOCKS:-0}" == "1" ]]; then
    log "Step: Build mocks (ENABLE_BUILD_MOCKS=1)"

    local enable_protobuf_mocks="ON"
    if ! command -v protoc >/dev/null 2>&1; then
      warn "protoc not found; disabling Protobuf-dependent mocks for this run."
      enable_protobuf_mocks="OFF"
    fi
    if ! command -v grpc_cpp_plugin >/dev/null 2>&1; then
      warn "grpc_cpp_plugin not found; disabling Protobuf-dependent mocks for this run."
      enable_protobuf_mocks="OFF"
    fi

    set +e
    cmake -S "$workspace/entservices-testframework/Tests/mocks" \
      -B "$workspace/build/mocks" \
      -DBUILD_SHARED_LIBS=ON \
      -DRDK_SERVICES_L1_TEST=ON \
      -DUSE_THUNDER_R4=ON \
      -DENABLE_PROTOBUF_MOCKS="$enable_protobuf_mocks" \
      ${toolchain:+-DCMAKE_TOOLCHAIN_FILE="$toolchain"} \
      -DCMAKE_INSTALL_PREFIX="$install_prefix" \
      -DCMAKE_MODULE_PATH="$cmake_module_path_for_rest" \
      -DCMAKE_BUILD_TYPE="$build_type" \
      -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES="$common_include_dirs_cmake" \
      -DCMAKE_INCLUDE_PATH="$common_include_dirs_cmake" \
      -DCMAKE_CXX_FLAGS="${common_defines[*]} ${common_includes_flags} -include $workspace/entservices-testframework/Tests/mocks/pkg.h ${coverage_flags[*]} -Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format= -Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,-wrap,v_secure_system -Wl,-wrap,v_secure_popen -Wl,-wrap,v_secure_pclose -Wl,-wrap,unlink -Wl,-wrap,v_secure_system -Wl,-wrap,v_secure_pclose -Wl,-wrap,pclose -Wl,-wrap,setmntent -Wl,-wrap,getmntent"
    local mocks_cfg_rc=$?

    local mocks_build_rc=0
    local mocks_install_rc=0
    if [[ $mocks_cfg_rc -eq 0 ]]; then
      cmake --build "$workspace/build/mocks" -j"$(nproc)"
      mocks_build_rc=$?
      if [[ $mocks_build_rc -eq 0 ]]; then
        cmake --install "$workspace/build/mocks"
        mocks_install_rc=$?
      fi
    fi
    set -e

    if [[ $mocks_cfg_rc -ne 0 || $mocks_build_rc -ne 0 || $mocks_install_rc -ne 0 ]]; then
      warn "Mocks step did not complete successfully (cfg=$mocks_cfg_rc build=$mocks_build_rc install=$mocks_install_rc). Continuing with AppGateway/L1 build+tests."
    fi
  else
    log "Skipping mocks build (ENABLE_BUILD_MOCKS=0)."
  fi

  # AppGateway (repo root)
  log "Step: Build AppGateway (repo root)"
  local appgateway_src_dir="$workspace"
  local appgateway_build_dir="$workspace/build/entservices-appgateway"

  local appgateway_install_stamp="$appgateway_build_dir/CMakeFiles/install.stamp"
  local appgateway_configured=0
  if [[ -f "$appgateway_build_dir/CMakeCache.txt" ]]; then
    appgateway_configured=1
  fi

  if [[ "$appgateway_configured" -ne 1 ]]; then
    local tf_pkg_header="$workspace/entservices-testframework/Tests/mocks/pkg.h"
    local tf_secure_header="$workspace/entservices-testframework/Tests/mocks/secure_wrappermock.h"
    local tf_forced_includes=""
    if [[ -f "$tf_pkg_header" ]]; then
      tf_forced_includes+=" -include $tf_pkg_header"
    fi
    if [[ -f "$tf_secure_header" ]]; then
      tf_forced_includes+=" -include $tf_secure_header"
    fi
    if [[ -z "$tf_forced_includes" ]]; then
      log "No entservices-testframework mock headers found; building AppGateway without forced mock includes."
    fi

    cmake -G "$generator" \
      -S "$appgateway_src_dir" \
      -B "$appgateway_build_dir" \
      -DCMAKE_INSTALL_PREFIX="$install_prefix" \
      -DCMAKE_MODULE_PATH="$cmake_module_path_for_rest" \
      -DCMAKE_BUILD_TYPE="$build_type" \
      -DRDK_SERVICES_L1_TEST=ON \
      -DUSE_THUNDER_R4=ON \
      -DHIDE_NON_EXTERNAL_SYMBOLS=OFF \
      -DENABLE_UNIT_TESTS=ON \
      ${toolchain:+-DCMAKE_TOOLCHAIN_FILE="$toolchain"} \
      -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES="$common_include_dirs_cmake" \
      -DCMAKE_INCLUDE_PATH="$common_include_dirs_cmake" \
      -DCMAKE_CXX_FLAGS="${common_defines[*]} ${common_includes_flags}${tf_forced_includes} ${coverage_flags[*]} -Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format= -Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,-wrap,v_secure_system -Wl,-wrap,v_secure_popen -Wl,-wrap,v_secure_pclose -Wl,-wrap,unlink"
  else
    log "AppGateway already configured (found $appgateway_build_dir/CMakeCache.txt); skipping reconfigure."
  fi

  cmake --build "$appgateway_build_dir" -j"$(nproc)"

  if [[ ! -f "$appgateway_install_stamp" ]]; then
    cmake --install "$appgateway_build_dir"
  else
    log "AppGateway already installed once (found install stamp); skipping reinstall."
  fi

  # entservices-testframework (optional)
  if [[ "${ENABLE_BUILD_TESTFRAMEWORK:-0}" == "1" ]]; then
    log "Step: Build entservices-testframework (ENABLE_BUILD_TESTFRAMEWORK=1)"
    cmake -G "$generator" \
      -S "$workspace/entservices-testframework" \
      -B "$workspace/build/entservices-testframework" \
      -DCMAKE_INSTALL_PREFIX="$install_prefix" \
      -DCMAKE_MODULE_PATH="$cmake_module_path_for_rest" \
      -DCMAKE_BUILD_TYPE="$build_type" \
      -DRDK_SERVICES_L1_TEST=ON \
      -DUSE_THUNDER_R4=ON \
      -DHIDE_NON_EXTERNAL_SYMBOLS=OFF \
      -DENABLE_UNIT_TESTS=ON \
      ${toolchain:+-DCMAKE_TOOLCHAIN_FILE="$toolchain"} \
      -DCMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES="$common_include_dirs_cmake" \
      -DCMAKE_INCLUDE_PATH="$common_include_dirs_cmake" \
      -DCMAKE_CXX_FLAGS="${common_defines[*]} ${common_includes_flags} -I ./usr/include/libdrm -include $workspace/entservices-testframework/Tests/mocks/pkg.h ${coverage_flags[*]} -Wall -Wno-unused-result -Wno-deprecated-declarations -Wno-error=format= -Wl,-wrap,system -Wl,-wrap,popen -Wl,-wrap,syslog -Wl,--no-as-needed"
    cmake --build "$workspace/build/entservices-testframework" -j"$(nproc)"
    cmake --install "$workspace/build/entservices-testframework"
  else
    log "Skipping entservices-testframework build/install (ENABLE_BUILD_TESTFRAMEWORK=0)."
  fi
}

# PUBLIC_INTERFACE
run_tests() {
  # Run RdkServicesL1Test similarly to CI (optionally with valgrind).
  local workspace="${1:?workspace required}"
  local install_usr="$workspace/install/usr"

  # Thunder install prefix (may be separate from install/usr)
  local thunder_install_prefix=""
  while IFS='=' read -r k v; do
    case "$k" in
      THUNDER_INSTALL_PREFIX) thunder_install_prefix="$v" ;;
    esac
  done < <(compute_thunder_prefixes "$workspace")
  local thunder_usr="$thunder_install_prefix"

  if [[ ! -x "$install_usr/bin/RdkServicesL1Test" && ! -x "$install_usr/bin/RdkServicesL1Testd" ]]; then
    warn "RdkServicesL1Test binary not found in $install_usr/bin (will still attempt to run via PATH)."
  fi

  log "Step: Run unit tests without valgrind"

  if command -v RdkServicesL1Test >/dev/null 2>&1; then
    (
      export PATH="$install_usr/bin:${PATH}"
      export LD_LIBRARY_PATH="$install_usr/lib:$install_usr/lib/wpeframework/plugins:$thunder_usr/lib:$thunder_usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"
      export GTEST_OUTPUT="json:$(pwd)/rdkL1TestResults.json"
      RdkServicesL1Test
    )
    cp -f "$(pwd)/rdkL1TestResults.json" "$workspace/rdkL1TestResultsWithoutValgrind.json"
    rm -f "$(pwd)/rdkL1TestResults.json"
  else
    warn "RdkServicesL1Test not found on PATH; falling back to ctest on build tree."
    (
      export LD_LIBRARY_PATH="$install_usr/lib:$install_usr/lib/wpeframework/plugins:$thunder_usr/lib:$thunder_usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"
      ctest --test-dir "$workspace/build/entservices-appgateway" --output-on-failure
    )
  fi

  if [[ "${ENABLE_VALGRIND:-0}" == "1" ]]; then
    require_cmd valgrind
    log "Step: Run unit tests with valgrind"
    (
      export PATH="$install_usr/bin:${PATH}"
      export LD_LIBRARY_PATH="$install_usr/lib:$install_usr/lib/wpeframework/plugins:$thunder_usr/lib:$thunder_usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"
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

  local lcovrc="$workspace/Tests/L1Tests/.lcovrc_l1"
  local lcovrc_tf="$workspace/entservices-testframework/Tests/L1Tests/.lcovrc_l1"
  if [[ -f "$lcovrc" ]]; then
    log "Using repo lcovrc: $lcovrc"
    cp "$lcovrc" "$HOME/.lcovrc"
  elif [[ -f "$lcovrc_tf" ]]; then
    log "Using lcovrc from testframework: $lcovrc_tf"
    cp "$lcovrc_tf" "$HOME/.lcovrc"
  else
    warn "No lcovrc found (checked: $lcovrc, $lcovrc_tf); continuing without it"
  fi

  log "Step: Generate coverage (lcov + genhtml)"
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

  export ENABLE_PACKAGE_INSTALL="${ENABLE_PACKAGE_INSTALL:-0}"
  export ENABLE_SETUP_FILES="${ENABLE_SETUP_FILES:-0}"
  export ENABLE_VALGRIND="${ENABLE_VALGRIND:-0}"
  export ENABLE_COVERAGE="${ENABLE_COVERAGE:-1}"
  export BUILD_TYPE="${BUILD_TYPE:-Debug}"

  export MINIMAL_L1="${MINIMAL_L1:-1}"
  export ENABLE_FETCH_DEPS="${ENABLE_FETCH_DEPS:-0}"
  export ENABLE_BUILD_MOCKS="${ENABLE_BUILD_MOCKS:-0}"
  export ENABLE_BUILD_TESTFRAMEWORK="${ENABLE_BUILD_TESTFRAMEWORK:-0}"

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
      --full-deps)
        export MINIMAL_L1=0
        export ENABLE_BUILD_MOCKS=1
        export ENABLE_BUILD_TESTFRAMEWORK=1
        export ENABLE_FETCH_DEPS=1
        shift
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

  require_cmd git
  require_cmd patch
  require_cmd cmake

  detect_cmake_generator

  install_packages_if_enabled

  # Thunder's CMake configure may invoke JsonGenerator which requires the Python module `jsonref`.
  # Ensure it is present *before* any Thunder/ThunderTools configure steps run.
  ensure_python_jsonref

  if [[ "${ENABLE_FETCH_DEPS:-0}" == "1" ]]; then
    ensure_l1_workflow_repos_present "$GITHUB_WORKSPACE"
  else
    log "Skipping dependency fetch/update (ENABLE_FETCH_DEPS=0). Using repos already present in workspace."
    for d in Thunder ThunderTools googletest trower-base64 entservices-apis; do
      if [[ ! -d "$GITHUB_WORKSPACE/$d" ]]; then
        warn "Missing workspace dependency directory: $GITHUB_WORKSPACE/$d (set ENABLE_FETCH_DEPS=1 or pass --full-deps to fetch)"
      fi
    done
  fi

  # Critical: Thunder/ThunderTools must be real git clones (log context shows they were empty/non-git).
  ensure_git_repo_or_die "$GITHUB_WORKSPACE" "ThunderTools" "$GITHUB_WORKSPACE/ThunderTools" "https://github.com/rdkcentral/ThunderTools.git" "R4.4.3"
  ensure_git_repo_or_die "$GITHUB_WORKSPACE" "Thunder" "$GITHUB_WORKSPACE/Thunder" "https://github.com/rdkcentral/Thunder.git" "${THUNDER_REF:-R4.4.1}"

  if command -v meson >/dev/null 2>&1 && command -v ninja >/dev/null 2>&1; then
    if sudo -n true >/dev/null 2>&1; then
      build_and_install_trower_base64 "$GITHUB_WORKSPACE"
    else
      warn "Skipping trower-base64 install (sudo not available without password). Run with sudo privileges if needed."
    fi
  else
    warn "meson/ninja not found; skipping trower-base64 build/install."
  fi

  # Patch steps must never block the rest of the run (and must never prompt).
  apply_patches_thundertools "$GITHUB_WORKSPACE"
  apply_patches_thunder "$GITHUB_WORKSPACE"

  setup_files_if_enabled

  if [[ "$do_build" == "1" ]]; then
    log "Step: Configure/build Thunder (dedicated step)"
    build_thunder "$GITHUB_WORKSPACE"

    if [[ "${MINIMAL_L1:-1}" == "1" ]]; then
      log "Minimal L1 mode enabled (MINIMAL_L1=1): skipping mocks + entservices-testframework build/install unless explicitly enabled."
      export ENABLE_BUILD_MOCKS="${ENABLE_BUILD_MOCKS:-0}"
      export ENABLE_BUILD_TESTFRAMEWORK="${ENABLE_BUILD_TESTFRAMEWORK:-0}"
    fi

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
