#!/usr/bin/env bash
set -euo pipefail

###############################################################################
# AppGateway L1 test + coverage runner
#
# Purpose:
#   Runs the L1 test binary (RdkServicesL1Test) for entservices-appgateway and
#   generates an lcov + HTML coverage report for the code exercised by
#   Tests/L1Tests/tests/test_AppGateway.cpp.
#
# Assumptions:
#   - The workspace has already been built with coverage flags as documented in:
#       kavia-docs/run_l1_tests.sh.md
#     (i.e., compilation with --coverage / -fprofile-arcs -ftest-coverage)
#   - The L1 runner executable is available at:
#       $WS/install/usr/bin/RdkServicesL1Test
#
# Output:
#   - $WS/coverage/appgateway_l1/filtered_coverage.info
#   - $WS/coverage/appgateway_l1/html/index.html
#
# Usage:
#   bash Tests/L1Tests/run_appgateway_l1_coverage.sh
#
# Environment overrides:
#   WS                 Workspace root (defaults to this repo root)
#   BUILD_DIR          CMake build dir to scan for gcda/gcno (default: $WS/build/entservices-appgateway)
#   INSTALL_PREFIX     Install prefix (default: $WS/install/usr)
#   OUT_DIR            Coverage output dir (default: $WS/coverage/appgateway_l1)
#   TEST_FILTER        Optional gtest filter (default: *AppGateway*)
#   KEEP_RAW_INFO      If "1", keep unfiltered coverage.info (default: 0)
###############################################################################

# Prefer explicit WS; otherwise infer from this script location.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
: "${WS:=$(cd "$SCRIPT_DIR/../.." && pwd)}"

: "${INSTALL_PREFIX:=$WS/install/usr}"
: "${BUILD_DIR:=$WS/build/entservices-appgateway}"
: "${OUT_DIR:=$WS/coverage/appgateway_l1}"
: "${TEST_FILTER:=*AppGateway*}"
: "${KEEP_RAW_INFO:=0}"

L1_BIN="$INSTALL_PREFIX/bin/RdkServicesL1Test"
LCOVRC="$WS/Tests/L1Tests/.lcovrc_l1"

log() { printf "\n[%s] %s\n" "$(date +'%Y-%m-%dT%H:%M:%S%z')" "$*"; }

require_cmd() {
  local cmd="$1"
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "ERROR: Missing required command: $cmd"
    echo "Install it (typically): sudo apt install -y lcov"
    exit 1
  fi
}

log "Workspace: $WS"
log "Build dir: $BUILD_DIR"
log "Install prefix: $INSTALL_PREFIX"
log "Output dir: $OUT_DIR"

require_cmd lcov
require_cmd genhtml

if [ ! -x "$L1_BIN" ]; then
  echo "ERROR: L1 test binary not found/executable at: $L1_BIN"
  echo "Build/install it first following kavia-docs/run_l1_tests.sh.md (Steps 10-11, then install)."
  exit 1
fi

if [ ! -f "$LCOVRC" ]; then
  echo "ERROR: lcov config not found at: $LCOVRC"
  echo "Expected to exist in this repo under Tests/L1Tests/.lcovrc_l1"
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
log "Zeroing counters in build directory (lcov -z)"
# Note: -z only affects existing counters; it does not delete files.
lcov -z -d "$BUILD_DIR" >/dev/null

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
# Use repo-provided lcovrc to keep consistent branch/line settings and filters.
cp "$LCOVRC" "$OUT_DIR/.lcovrc"
export LCOVRC="$OUT_DIR/.lcovrc"

RAW_INFO="$OUT_DIR/coverage.info"
FILTERED_INFO="$OUT_DIR/filtered_coverage.info"
HTML_DIR="$OUT_DIR/html"

lcov -c -o "$RAW_INFO" -d "$BUILD_DIR"

# Filter out non-product code and test sources (including test_AppGateway.cpp itself).
# This keeps the report focused on appgateway/appgatewaycommon code being exercised.
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
genhtml -o "$HTML_DIR" -t "entservices-appgateway L1 coverage (test_AppGateway.cpp)" "$FILTERED_INFO" >/dev/null

if [ "$KEEP_RAW_INFO" != "1" ]; then
  rm -f "$RAW_INFO"
fi

log "Coverage report generated:"
log "  lcov: $FILTERED_INFO"
log "  html: $HTML_DIR/index.html"
log "Done."
