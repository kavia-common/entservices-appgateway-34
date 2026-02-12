#!/usr/bin/env bash
# L1 test runner script (host-shell)
#
# This script intentionally mirrors the CI workflow for the parts that must be
# identical between local runs and GitHub Actions:
#   - Repo checkouts (Thunder/ThunderTools/entservices-apis/googletest/trower-base64)
#   - Patch application (ThunderTools + Thunder) exactly as .github/workflows/L1-tests.yml
#
# CI reference: .github/workflows/L1-tests.yml
#
# NOTE:
#  - This script is intended to be EXECUTED, not sourced.
#  - Some steps require sudo (package installs, /dev nodes, etc.) depending on your env.

set -euo pipefail

###############################################################################
# Repo cloning helpers (mirror .github/workflows/L1-tests.yml)
###############################################################################

# PUBLIC_INTERFACE
ensure_repo_cloned() {
  # Ensure a git repo exists at a given directory, checked out at a specific ref.
  #
  # If the directory doesn't exist, it will be cloned.
  # If it exists and is a git repo, it will fetch (best-effort) and checkout the ref.
  #
  # Args:
  #   $1: target_dir (absolute path)
  #   $2: remote_url (e.g., https://github.com/rdkcentral/Thunder.git)
  #   $3: ref        (tag/branch/commit)
  local target_dir="${1:?target_dir required}"
  local remote_url="${2:?remote_url required}"
  local ref="${3:?ref required}"

  # CI/workspaces can leave behind a directory named like the repo but without git metadata.
  # For parity with the workflow we remove and re-clone in that case.
  if [[ -d "$target_dir" && ! -d "$target_dir/.git" ]]; then
    echo "INFO: Path exists but is not a git repo; removing so it can be re-cloned: $target_dir" >&2
    rm -rf "$target_dir"
  fi

  if [[ ! -d "$target_dir" ]]; then
    echo "Cloning: $remote_url -> $target_dir (ref=$ref)"
    git clone --no-tags --depth 1 --branch "$ref" "$remote_url" "$target_dir" >/dev/null 2>&1 || {
      # Fallback: if shallow/tag checkout fails, do a full clone.
      echo "INFO: Shallow clone failed; retrying with full clone for $remote_url" >&2
      git clone "$remote_url" "$target_dir"
      pushd "$target_dir" >/dev/null
      git checkout -f "$ref"
      popd >/dev/null
    }
    return 0
  fi

  echo "Repo exists: $target_dir (ensuring ref=$ref)"
  pushd "$target_dir" >/dev/null
  git remote set-url origin "$remote_url" >/dev/null 2>&1 || true
  git fetch --tags --force >/dev/null 2>&1 || true
  git fetch --all --prune >/dev/null 2>&1 || true
  git checkout -f "$ref" >/dev/null 2>&1 || {
    echo "ERROR: Failed to checkout ref '$ref' in $target_dir" >&2
    popd >/dev/null
    return 1
  }
  popd >/dev/null
}

# PUBLIC_INTERFACE
ensure_l1_workflow_repos_present() {
  # Clone repos required by the L1-tests workflow (excluding entservices-testframework).
  #
  # Mirrors .github/workflows/L1-tests.yml:
  #   - Thunder                 rdkcentral/Thunder              ref: env.THUNDER_REF (default R4.4.1)
  #   - ThunderTools            rdkcentral/ThunderTools         ref: R4.4.3 (hard-coded in workflow)
  #   - entservices-apis        rdkcentral/entservices-apis     ref: env.INTERFACES_REF (default develop)
  #   - googletest              google/googletest              ref: v1.15.0
  #   - trower-base64           xmidt-org/trower-base64         (no ref pinned in workflow; default branch)
  #
  # NOTE: entservices-testframework is intentionally NOT cloned here.
  local workspace="${1:?workspace required}"

  local thunder_ref="${THUNDER_REF:-R4.4.1}"
  local interfaces_ref="${INTERFACES_REF:-develop}"
  local googletest_ref="${GOOGLETEST_REF:-v1.15.0}"

  echo "Step: Ensure required repos are present (mirror L1-tests.yml)"
  ensure_repo_cloned "$workspace/Thunder" "https://github.com/rdkcentral/Thunder.git" "$thunder_ref"
  ensure_repo_cloned "$workspace/ThunderTools" "https://github.com/rdkcentral/ThunderTools.git" "R4.4.3"
  ensure_repo_cloned "$workspace/entservices-apis" "https://github.com/rdkcentral/entservices-apis.git" "$interfaces_ref"
  ensure_repo_cloned "$workspace/googletest" "https://github.com/google/googletest.git" "$googletest_ref"

  if [[ ! -d "$workspace/trower-base64" ]]; then
    echo "Cloning: https://github.com/xmidt-org/trower-base64.git -> $workspace/trower-base64"
    git clone https://github.com/xmidt-org/trower-base64.git "$workspace/trower-base64"
  else
    echo "Repo exists: $workspace/trower-base64"
  fi
}

###############################################################################
# Patch steps (mirror .github/workflows/L1-tests.yml)
###############################################################################

# PUBLIC_INTERFACE
apply_patches_thundertools() {
  # Apply ThunderTools patch exactly as CI does.
  local workspace="${1:?workspace required}"

  # CI:
  #   cd $GITHUB_WORKSPACE/ThunderTools
  #   patch -p1 < $GITHUB_WORKSPACE/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch
  if [[ -d "$workspace/ThunderTools" && -d "$workspace/entservices-testframework" ]]; then
    echo "Step: Apply patches ThunderTools (match L1-tests.yml)"
    pushd "$workspace/ThunderTools" >/dev/null
    patch -p1 <"$workspace/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch"
    popd >/dev/null
  else
    echo "INFO: ThunderTools or entservices-testframework missing; skipping ThunderTools patch step."
  fi
}

# PUBLIC_INTERFACE
apply_patches_thunder() {
  # Apply Thunder patches exactly as CI does (same order, same patch files).
  local workspace="${1:?workspace required}"

  # CI:
  #   cd $GITHUB_WORKSPACE/Thunder
  #   patch -p1 < .../Use_Legact_Alt_Based_On_ThunderTools_R4.4.3.patch
  #   patch -p1 < .../error_code_R4_4.patch
  #   patch -p1 < .../1004-Add-support-for-project-dir.patch
  #   patch -p1 < .../RDKEMW-733-Add-ENTOS-IDS.patch
  #   patch -p1 < .../Jsonrpc_dynamic_error_handling.patch
  #   cd -
  if [[ -d "$workspace/Thunder" && -d "$workspace/entservices-testframework" ]]; then
    echo "Step: Apply patches Thunder (match L1-tests.yml)"
    pushd "$workspace/Thunder" >/dev/null
    patch -p1 <"$workspace/entservices-testframework/patches/Use_Legact_Alt_Based_On_ThunderTools_R4.4.3.patch"
    patch -p1 <"$workspace/entservices-testframework/patches/error_code_R4_4.patch"
    patch -p1 <"$workspace/entservices-testframework/patches/1004-Add-support-for-project-dir.patch"
    patch -p1 <"$workspace/entservices-testframework/patches/RDKEMW-733-Add-ENTOS-IDS.patch"
    patch -p1 <"$workspace/entservices-testframework/patches/Jsonrpc_dynamic_error_handling.patch"
    popd >/dev/null
  else
    echo "INFO: Thunder or entservices-testframework missing; skipping Thunder patch step."
  fi
}

###############################################################################
# Main
###############################################################################

# PUBLIC_INTERFACE
main() {
  # Entry point for the host-shell L1 test workflow.
  #
  # This script now:
  #   1) Ensures required repos are present
  #   2) Applies ThunderTools patches (as CI)
  #   3) Applies Thunder patches (as CI)
  #   4) Continues to the remaining build/test steps (existing flow)
  local workspace
  workspace="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  local GITHUB_WORKSPACE="${GITHUB_WORKSPACE:-$workspace}"

  echo "Workspace: $GITHUB_WORKSPACE"

  ensure_l1_workflow_repos_present "$GITHUB_WORKSPACE"

  apply_patches_thundertools "$GITHUB_WORKSPACE"
  apply_patches_thunder "$GITHUB_WORKSPACE"

  # Continue with the rest of the existing script/flow (build/test steps).
  # If you have additional build/test logic below in your local variant, keep it here.
  echo "Continuing to remaining build/test steps..."
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  main "$@"
fi
