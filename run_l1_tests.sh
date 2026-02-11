#!/usr/bin/env bash
# L1 test runner script (host-shell) - idempotent patch application
#
# This script is intended to be re-runnable: patch steps will not prompt
# interactively and will cleanly skip patches that are already applied
# or already reversed.
set -euo pipefail

###############################################################################
# Patch helper
###############################################################################

# PUBLIC_INTERFACE
apply_patch_idempotent() {
  """
  Apply a unified diff patch idempotently and non-interactively.

  Behavior:
  - If the patch is already applied: skip cleanly.
  - If the patch would apply cleanly: apply it.
  - If the patch is already reversed (i.e., -R would apply): skip cleanly.
  - Otherwise: fail with a helpful message.

  Args:
    $1: target_dir (directory to run patch from)
    $2: strip_level (e.g., 1 for -p1)
    $3: patch_file (path to patch file)
  """
  local target_dir="${1:?target_dir required}"
  local strip_level="${2:?strip_level required}"
  local patch_file="${3:?patch_file required}"

  if [[ ! -d "$target_dir" ]]; then
    echo "ERROR: target directory not found: $target_dir" >&2
    return 2
  fi
  if [[ ! -f "$patch_file" ]]; then
    echo "ERROR: patch file not found: $patch_file" >&2
    return 2
  fi

  # Non-interactive & .rej-safe approach:
  # 1) Forward dry-run: if it applies cleanly, then apply for real.
  # 2) Reverse dry-run: if that applies cleanly, patch is already applied (or tree is in reversed state) -> skip.
  # 3) Otherwise: fail (do NOT use --force; it may create .rej files).
  #
  # Flags:
  # --batch      : never prompt (prevents "Assume -R?" / "Apply anyway?")
  # --silent     : reduce noise
  # --dry-run    : detection without touching files
  # --binary     : avoid CRLF "Stripping trailing CRs..." normalization behavior/messages
  # --forward    : in apply step, don't apply reversed patches
  # -N           : ignore already-applied hunks when applying forward (still non-interactive)
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
# Main (minimal skeleton; integrate into existing workflow-generated script)
###############################################################################

# NOTE: This script is a host-shell translation of the L1 workflow.
# Update the paths below if your workspace layout differs.
GITHUB_WORKSPACE="${GITHUB_WORKSPACE:-$(pwd)}"

# Example idempotent patch applications matching the workflow steps.
# These paths mirror the workflow structure:
#   ThunderTools: entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch
#   Thunder:      multiple patches
#   entservices-apis: RDKEMW-1007.patch
#
# If your script already performs these steps, keep the rest of the script intact
# and replace only the raw `patch -p1 < ...` lines with `apply_patch_idempotent ...`.

if [[ -d "$GITHUB_WORKSPACE/ThunderTools" && -d "$GITHUB_WORKSPACE/entservices-testframework" ]]; then
  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/ThunderTools" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/00010-R4.4-Add-support-for-project-dir.patch"
fi

if [[ -d "$GITHUB_WORKSPACE/Thunder" && -d "$GITHUB_WORKSPACE/entservices-testframework" ]]; then
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
  apply_patch_idempotent \
    "$GITHUB_WORKSPACE/entservices-apis" \
    1 \
    "$GITHUB_WORKSPACE/entservices-testframework/patches/RDKEMW-1007.patch"
fi

# The remainder of the original run_l1_tests.sh should follow here (build steps, etc.).
# This file is intentionally focused on the patch-idempotency fix requested.
echo "Patch application stage completed (idempotent)."
