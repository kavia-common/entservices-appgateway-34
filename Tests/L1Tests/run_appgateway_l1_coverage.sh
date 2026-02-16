#!/usr/bin/env bash
set -euo pipefail

###############################################################################
# AppGateway L1 test + coverage runner
#
# Purpose:
#   Runs the L1 test runner binary (RdkServicesL1Test) and generates lcov + HTML
#   coverage report for the code exercised by this repo's L1 tests.
#
# Conventions:
#   This script intentionally follows the workspace layout and paths used in:
#     kavia-docs/run_l1_tests.sh.md
#
# Key CI-equivalent paths (default expectations):
#   - Install prefix:   $WS/install/usr
#   - Build dir:        $WS/build/entservices-appgateway
#   - Test runner:      $WS/install/usr/bin/RdkServicesL1Test
#   - lcovrc:           $WS/entservices-testframework/Tests/L1Tests/.lcovrc_l1
#                       (fallback: $WS/Tests/L1Tests/.lcovrc_l1 if present)
#
# Output:
#   - $OUT_DIR/filtered_coverage.info
#   - $OUT_DIR/html/index.html
#
# Usage:
#   bash Tests/L1Tests/run_appgateway_l1_coverage.sh
#
# Environment overrides:
#   WS                 Workspace root (auto-detected if unset)
#   INSTALL_PREFIX      Install prefix (auto-detected; default: $WS/install/usr)
#   BUILD_DIR           Build dir containing .gcda/.gcno (auto-detected)
#   OUT_DIR             Coverage output dir (default: $WS/coverage/appgateway_l1)
#   TEST_FILTER         Optional gtest filter (default: *AppGateway*)
#   KEEP_RAW_INFO       If "1", keep unfiltered coverage.info (default: 0)
###############################################################################

log() { printf "\n[%s] %s\n" "$(date +'%Y-%m-%dT%H:%M:%S%z')" "$*"; }

require_cmd() {
  local cmd="$1"
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "ERROR: Missing required command: $cmd"
    echo "Install it (typically): sudo apt install -y lcov"
    exit 1
  fi
}

# PUBLIC_INTERFACE
infer_ws() {
  """Infer workspace root (WS) following run_l1_tests.sh.md conventions.

  The L1 docs assume a workspace containing sibling dirs such as:
    Thunder/, ThunderTools/, entservices-testframework/, build/, install/
  This function walks upwards from this script location trying to find a
  directory that looks like that workspace.
  """
  local start_dir="$1"
  local d="$start_dir"
  while true; do
    if [[ -d "$d/build" && -d "$d/install" ]]; then
      # Strong signal of workspace root.
      echo "$d"
      return 0
    fi
    # If we see entservices-testframework at this level, it's also a strong signal
    # (even if build/install not created yet).
    if [[ -d "$d/entservices-testframework" ]]; then
      echo "$d"
      return 0
    fi

    local parent
    parent="$(cd "$d/.." && pwd)"
    if [[ "$parent" == "$d" ]]; then
      # Reached filesystem root.
      echo ""
      return 1
    fi
    d="$parent"
  done
}

# PUBLIC_INTERFACE
pick_first_existing_dir() {
  """Print the first directory from arguments that exists, else empty string."""
  for candidate in "$@"; do
    if [[ -n "$candidate" && -d "$candidate" ]]; then
      echo "$candidate"
      return 0
    fi
  done
  echo ""
  return 1
}

# Prefer explicit WS; otherwise infer from this script location.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [[ -z "${WS:-}" ]]; then
  # Start searching from repo root (…/entservices-appgateway-34)
  # Script is at: <repo>/Tests/L1Tests, so repo root is two levels up.
  REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"
  if WS_GUESS="$(infer_ws "$REPO_ROOT")"; then
    WS="$WS_GUESS"
  else
    # Fallback to repo root (still usable for repo-local builds)
    WS="$REPO_ROOT"
  fi
fi

# Auto-detect install prefix.
if [[ -z "${INSTALL_PREFIX:-}" ]]; then
  # Primary convention from run_l1_tests.sh.md
  if [[ -d "$WS/install/usr" ]]; then
    INSTALL_PREFIX="$WS/install/usr"
  elif [[ -d "$WS/install" ]]; then
    INSTALL_PREFIX="$WS/install"
  else
    # Fall back to local install under repo (if user used a different layout)
    INSTALL_PREFIX="$WS/install/usr"
  fi
fi

# Auto-detect build dir containing appgateway coverage counters.
if [[ -z "${BUILD_DIR:-}" ]]; then
  BUILD_DIR="$(pick_first_existing_dir \
    "$WS/build/entservices-appgateway" \
    "$WS/build" \
    "$WS/cmake-build-debug" \
    "$WS/cmake-build-release" \
  )"
  if [[ -z "$BUILD_DIR" ]]; then
    # Keep the canonical default even if it doesn't exist yet.
    BUILD_DIR="$WS/build/entservices-appgateway"
  fi
fi

: "${OUT_DIR:=$WS/coverage/appgateway_l1}"
: "${TEST_FILTER:=*AppGateway*}"
: "${KEEP_RAW_INFO:=0}"

L1_BIN="$INSTALL_PREFIX/bin/RdkServicesL1Test"

# lcovrc location per run_l1_tests.sh.md (testframework is canonical).
LCOVRC=""
if [[ -f "$WS/entservices-testframework/Tests/L1Tests/.lcovrc_l1" ]]; then
  LCOVRC="$WS/entservices-testframework/Tests/L1Tests/.lcovrc_l1"
elif [[ -f "$WS/Tests/L1Tests/.lcovrc_l1" ]]; then
  # Fallback for repo-local usage if present.
  LCOVRC="$WS/Tests/L1Tests/.lcovrc_l1"
fi

log "Workspace (WS): $WS"
log "Build dir:       $BUILD_DIR"
log "Install prefix:  $INSTALL_PREFIX"
log "Output dir:      $OUT_DIR"

require_cmd lcov
require_cmd genhtml

if [[ ! -x "$L1_BIN" ]]; then
  echo "ERROR: L1 test runner not found/executable at: $L1_BIN"
  echo "Expected by run_l1_tests.sh.md after installing entservices-testframework."
  echo ""
  echo "Hints:"
  echo "  - Ensure you ran: cmake --install \"$WS/build/entservices-testframework\""
  echo "  - Ensure INSTALL_PREFIX is correct (currently: $INSTALL_PREFIX)"
  exit 1
fi

if [[ -z "$LCOVRC" ]]; then
  echo "ERROR: lcov config (.lcovrc_l1) not found."
  echo "Expected (preferred): $WS/entservices-testframework/Tests/L1Tests/.lcovrc_l1"
  echo "Fallback (optional):  $WS/Tests/L1Tests/.lcovrc_l1"
  exit 1
fi

mkdir -p "$OUT_DIR"

###############################################################################
# Runtime env (match doc)
###############################################################################
export PATH="$INSTALL_PREFIX/bin:$PATH"
export LD_LIBRARY_PATH="$INSTALL_PREFIX/lib:$INSTALL_PREFIX/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"

# Keep test outputs alongside coverage artifacts
export GTEST_OUTPUT="json:$OUT_DIR/rdkL1TestResults.json"

###############################################################################
# Clean previous coverage counters (important for accurate report)
###############################################################################
if [[ -d "$BUILD_DIR" ]]; then
  log "Zeroing counters in build directory (lcov -z)"
  # Note: -z only affects existing counters; it does not delete files.
  lcov -z -d "$BUILD_DIR" >/dev/null
else
  log "WARNING: BUILD_DIR does not exist yet: $BUILD_DIR"
  log "         Coverage capture will likely fail unless you built with coverage flags."
fi

###############################################################################
# Run L1 tests (AppGateway focused)
###############################################################################
log "Running L1 tests: $L1_BIN"
log "Using gtest filter: $TEST_FILTER"
"$L1_BIN" --gtest_filter="$TEST_FILTER"

###############################################################################
# Capture and filter coverage
###############################################################################
log "Capturing coverage from: $BUILD_DIR"

# Use repo/testframework-provided lcovrc to keep consistent settings.
cp "$LCOVRC" "$OUT_DIR/.lcovrc"
export LCOVRC="$OUT_DIR/.lcovrc"

RAW_INFO="$OUT_DIR/coverage.info"
FILTERED_INFO="$OUT_DIR/filtered_coverage.info"
HTML_DIR="$OUT_DIR/html"

lcov -c -o "$RAW_INFO" -d "$BUILD_DIR"

# Filter out non-product code and test sources (including test sources themselves).
log "Filtering coverage info"
lcov -r "$RAW_INFO" \
  '/usr/include/*' \
  '*/build/entservices-appgateway/_deps/*' \
  '*/install/usr/include/*' \
  '*/Tests/headers/*' \
  '*/Tests/mocks/*' \
  '*/Tests/L1Tests/tests/*' \
  '*/Thunder/*' \
  -o "$FILTERED_INFO"

log "Generating HTML report"
rm -rf "$HTML_DIR"
genhtml -o "$HTML_DIR" -t "entservices-appgateway L1 coverage" "$FILTERED_INFO" >/dev/null

if [[ "$KEEP_RAW_INFO" != "1" ]]; then
  rm -f "$RAW_INFO"
fi

log "Coverage report generated:"
log "  lcov: $FILTERED_INFO"
log "  html: $HTML_DIR/index.html"
log "Done."
