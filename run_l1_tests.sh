#!/usr/bin/env bash
# L1 test runner script (host-shell)
#
# This script intentionally mirrors the CI workflow for the specific parts that
# have been flaky locally:
#   - ThunderTools checkout/ref
#   - ThunderTools patch application
#
# CI reference: .github/workflows/L1-tests.yml
#
# NOTE:
#  - This script is intended to be EXECUTED, not sourced.

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

  # Some CI/workspaces can leave behind a directory named like the repo but without git metadata
  # (e.g., extracted tarball, empty dir, partial checkout). For parity with the workflow we
  # remove and re-clone in that case.
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
  # Clone any repos required by the L1-tests workflow (excluding entservices-testframework).
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
# Main
###############################################################################

# PUBLIC_INTERFACE
main() {
  # Entry point for the host-shell L1 test workflow.
  #
  # For this task we only guarantee parity with CI for:
  #   - ThunderTools checkout/ref
  #   - ThunderTools patch application
  local workspace
  workspace="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
  local GITHUB_WORKSPACE="${GITHUB_WORKSPACE:-$workspace}"

  echo "Workspace: $GITHUB_WORKSPACE"

  ensure_l1_workflow_repos_present "$GITHUB_WORKSPACE"

  # CI: "Apply patches ThunderTools"
  #   cd $GITHUB_WORKSPACE/ThunderTools
  #   patch -p1 < $GITHUB_WORKSPACE/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch
  if [[ -d "$GITHUB_WORKSPACE/ThunderTools" && -d "$GITHUB_WORKSPACE/entservices-testframework" ]]; then
    echo "Step: Apply patches ThunderTools (match L1-tests.yml)"
    pushd "$GITHUB_WORKSPACE/ThunderTools" >/dev/null
    patch -p1 <"$GITHUB_WORKSPACE/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch"
    popd >/dev/null
  else
    echo "INFO: ThunderTools or entservices-testframework missing; skipping ThunderTools patch step."
  fi

  echo "NOTE: Remaining build/test steps are not modified by this change."
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  main "$@"
fi
