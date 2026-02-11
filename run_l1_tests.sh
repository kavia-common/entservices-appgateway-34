#!/usr/bin/env bash
# L1 test runner script (host-shell)
#
# Goals:
#  - Ensure ThunderTools is at the expected *clean* revision before applying
#    entservices-testframework patches (prevents patch mismatch / reverse-detect prompts).
#  - Apply patches idempotently and non-interactively (no "Assume -R?" prompts).

set -euo pipefail

###############################################################################
# Patch helper
###############################################################################

# PUBLIC_INTERFACE
apply_patch_idempotent() {
  # Apply a unified diff patch idempotently and non-interactively.
  #
  # Behavior:
  # - If the patch would apply cleanly: apply it.
  # - If the patch is already applied (i.e., reverse dry-run would apply): skip cleanly.
  # - Otherwise: fail with a helpful message (do not force; avoid .rej files).
  #
  # Args:
  #   $1: target_dir   (directory to run patch from)
  #   $2: strip_level  (e.g., 1 for -p1)
  #   $3: patch_file   (path to patch file)
  local target_dir="${1:?target_dir required}"
  local strip_level="${2:?strip_level required}"
  local patch_file="${3:?patch_file required}"

  # Reject unexpected extra args to avoid accidental shifting mistakes.
  if [[ $# -ne 3 ]]; then
    echo "ERROR: apply_patch_idempotent expects exactly 3 args, got $#." >&2
    echo "  Usage: apply_patch_idempotent <target_dir> <strip_level> <patch_file>" >&2
    return 2
  fi

  if [[ ! -d "$target_dir" ]]; then
    echo "ERROR: target directory not found: $target_dir" >&2
    return 2
  fi
  if [[ ! -f "$patch_file" ]]; then
    echo "ERROR: patch file not found: $patch_file" >&2
    return 2
  fi
  if [[ ! "$strip_level" =~ ^[0-9]+$ ]]; then
    echo "ERROR: strip_level must be a non-negative integer (e.g., 0, 1, 2). Got: $strip_level" >&2
    return 2
  fi

  # Non-interactive & .rej-safe approach:
  # 1) Forward dry-run: if it applies cleanly, then apply for real.
  # 2) Reverse dry-run: if that applies cleanly, the patch is already applied -> skip.
  # 3) Otherwise: fail (do NOT use --force; it may create .rej files).
  #
  # Flags:
  # --batch      : never prompt (prevents "Assume -R?" / "Apply anyway?")
  # --silent     : reduce noise
  # --dry-run    : detection without touching files
  # --binary     : avoid CRLF normalization prompts/noise ("Stripping trailing CRs...")
  # --forward    : when applying, do not apply reversed patches
  # -N           : when applying, ignore already-applied hunks (keeps it idempotent)
  pushd "$target_dir" >/dev/null

  if patch "-p${strip_level}" --dry-run --silent --batch --binary --forward <"$patch_file" >/dev/null 2>&1; then
    echo "Applying patch: $patch_file (in $target_dir)"
    patch "-p${strip_level}" --silent --batch --binary --forward -N <"$patch_file" >/dev/null
    popd >/dev/null
    return 0
  fi

  # If reverse dry-run succeeds, the forward patch has already been applied. Skip without touching files.
  if patch "-p${strip_level}" -R --dry-run --silent --batch --binary <"$patch_file" >/dev/null 2>&1; then
    echo "Skipping patch (already applied): $patch_file (in $target_dir)"
    popd >/dev/null
    return 0
  fi

  echo "ERROR: Patch does not apply cleanly and is not already applied: $patch_file" >&2
  echo "  target_dir=$target_dir strip_level=$strip_level" >&2
  echo "  NOTE: This script refuses to force-apply patches to avoid generating .rej files." >&2
  popd >/dev/null
  return 1
}

###############################################################################
# ThunderTools revision pinning (required for entservices-testframework patches)
###############################################################################

# PUBLIC_INTERFACE
ensure_thundertools_expected_revision() {
  # Reset ThunderTools to the expected tag/commit before applying patches.
  #
  # The entservices-testframework patchset (notably 00010-R4.4-Add-support-for-project-dir.patch)
  # is authored against a specific ThunderTools baseline. If ThunderTools has local
  # modifications or is at a different revision, patch(1) may detect "reversed" hunks
  # and (in interactive mode) would prompt; here we avoid prompts and avoid mismatches
  # by checking out the expected revision.
  #
  # Behavior:
  #   - If ThunderTools is not a git repo: fail.
  #   - Fetch tags (best-effort).
  #   - checkout + hard reset to expected revision.
  #   - clean untracked files to ensure a pristine tree.
  #
  # Environment:
  #   - THUNDERTOOLS_EXPECTED_REF (optional): git ref (tag/commit). Defaults to "R4.4.3".
  local workspace="${1:?workspace required}"
  local tt_dir="$workspace/ThunderTools"
  local expected_ref="${THUNDERTOOLS_EXPECTED_REF:-R4.4.3}"

  if [[ ! -d "$tt_dir" ]]; then
    echo "ERROR: ThunderTools directory not found at: $tt_dir" >&2
    return 2
  fi
  if [[ ! -d "$tt_dir/.git" ]]; then
    echo "ERROR: ThunderTools is not a git repository: $tt_dir" >&2
    return 2
  fi

  echo "Step: Reset ThunderTools to expected revision: ${expected_ref}"
  pushd "$tt_dir" >/dev/null

  # Best-effort to ensure tags/refs are available locally.
  # (If fetch fails due to offline environment, checkout may still work if ref exists locally.)
  git fetch --tags --force >/dev/null 2>&1 || true
  git fetch --all --prune >/dev/null 2>&1 || true

  # Ensure a clean baseline matching the patch author's expectation.
  git checkout -f "${expected_ref}" >/dev/null 2>&1 || {
    echo "ERROR: Failed to checkout ThunderTools ref '${expected_ref}'." >&2
    echo "  Available tags (sample):" >&2
    git tag -l | tail -n 20 >&2 || true
    popd >/dev/null
    return 1
  }
  git reset --hard "${expected_ref}" >/dev/null
  git clean -ffd >/dev/null

  echo "ThunderTools now at: $(git describe --tags --always --dirty)"
  popd >/dev/null
}

###############################################################################
# Main
###############################################################################

# NOTE: This script is a host-shell translation of the L1 workflow.
# Update the paths below if your workspace layout differs.
GITHUB_WORKSPACE="${GITHUB_WORKSPACE:-$(pwd)}"

# Ensure ThunderTools is at the right baseline before patching it.
if [[ -d "$GITHUB_WORKSPACE/ThunderTools" ]]; then
  ensure_thundertools_expected_revision "$GITHUB_WORKSPACE"
fi

# Apply entservices-testframework patches idempotently.
if [[ -d "$GITHUB_WORKSPACE/ThunderTools" && -d "$GITHUB_WORKSPACE/entservices-testframework" ]]; then
  echo "Step: Apply patches to ThunderTools"
  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/ThunderTools" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch"
fi

if [[ -d "$GITHUB_WORKSPACE/Thunder" && -d "$GITHUB_WORKSPACE/entservices-testframework" ]]; then
  echo "Step: Apply patches to Thunder"
  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/Thunder" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/Use_Legact_Alt_Based_On_ThunderTools_R4.4.3.patch"

  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/Thunder" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/error_code_R4_4.patch"

  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/Thunder" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/1004-Add-support-for-project-dir.patch"

  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/Thunder" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/RDKEMW-733-Add-ENTOS-IDS.patch"

  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/Thunder" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/Jsonrpc_dynamic_error_handling.patch"
fi

if [[ -d "$GITHUB_WORKSPACE/entservices-apis" && -d "$GITHUB_WORKSPACE/entservices-testframework" ]]; then
  echo "Step: Apply patches to entservices-apis"
  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/entservices-apis" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/RDKEMW-1007.patch"
fi

# The remainder of the original run_l1_tests.sh (build/test steps) should follow here.
echo "Patch application stage completed (idempotent)."
