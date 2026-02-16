#!/usr/bin/env bash
set -euo pipefail

###############################################################################
# Run AppGateway L1 tests and generate coverage report focused on:
#   Tests/L1Tests/tests/test_AppGateway.cpp
#
# This script is derived from the procedure documented in:
#   /home/kavia/workspace/code-generation/kavia-docs/run_l1_tests.sh.md
#
# Assumptions:
# - The full L1 build (with coverage flags) has already been performed at least
#   once following the documented procedure, producing:
#     $WS/install/usr/bin/RdkServicesL1Test
#     $WS/build/entservices-appgateway/**.gcno
# - The runtime fixtures creation step (sudo mkdir/mknod/touch/chmod) has been
#   completed as required by the L1 tests (see doc).
#
# Output:
# - coverage_appgateway_l1/         (HTML report)
# - coverage_appgateway_l1.info     (filtered lcov info)
# - coverage_appgateway_l1_raw.info (raw lcov capture)
###############################################################################

# Configuration (override via env vars)
: "${WS:=/home/kavia/workspace/code-generation/entservices-appgateway-34}"
: "${BUILD_DIR:=$WS/build/entservices-appgateway}"

# Where to place output artifacts
: "${OUT_DIR:=$WS/coverage_appgateway_l1}"
: "${RAW_INFO:=$WS/coverage_appgateway_l1_raw.info}"
: "${FILTERED_INFO:=$WS/coverage_appgateway_l1.info}"

# Optional: restrict test execution to only tests that mention "AppGateway" in the
# test name (GoogleTest filter). Leave empty to run full suite.
: "${GTEST_FILTER:=*AppGateway*}"

# If you want to also preserve gtest JSON output (useful in CI logs)
: "${GTEST_JSON:=$WS/rdkL1TestResults_appgateway.json}"

# For reproducibility in CI, allow disabling the L1 run and just generate coverage
# from existing gcda files (e.g., if tests were run elsewhere).
: "${SKIP_TEST_RUN:=0}"

log() { printf "\n[%s] %s\n" "$(date +'%Y-%m-%dT%H:%M:%S%z')" "$*"; }

require_cmd() {
  command -v "$1" >/dev/null 2>&1 || {
    echo "ERROR: required command not found: $1" >&2
    exit 1
  }
}

log "Validating prerequisites"
require_cmd lcov
require_cmd genhtml

if [ ! -d "$WS" ]; then
  echo "ERROR: WS does not exist: $WS" >&2
  exit 1
fi

if [ ! -d "$BUILD_DIR" ]; then
  echo "ERROR: Build dir not found: $BUILD_DIR" >&2
  echo "Expected you to have run the documented L1 build with coverage enabled." >&2
  exit 1
fi

if [ ! -x "$WS/install/usr/bin/RdkServicesL1Test" ]; then
  echo "ERROR: L1 test runner not found/executable: $WS/install/usr/bin/RdkServicesL1Test" >&2
  echo "Build entservices-testframework per the doc to produce RdkServicesL1Test." >&2
  exit 1
fi

# Coverage focus file (used for filtering)
FOCUS_FILE_REL="Tests/L1Tests/tests/test_AppGateway.cpp"
FOCUS_FILE_ABS="$WS/$FOCUS_FILE_REL"
if [ ! -f "$FOCUS_FILE_ABS" ]; then
  echo "ERROR: Focus file not found: $FOCUS_FILE_ABS" >&2
  exit 1
fi

log "Cleaning previous output"
rm -rf "$OUT_DIR" "$RAW_INFO" "$FILTERED_INFO"
mkdir -p "$OUT_DIR"

# Best-effort: start from a clean coverage baseline (removes old counters)
# If your environment uses multiple build dirs or you want to keep counters, set:
#   SKIP_CLEAN_COUNTERS=1
: "${SKIP_CLEAN_COUNTERS:=0}"
if [ "$SKIP_CLEAN_COUNTERS" = "0" ]; then
  log "Zeroing coverage counters in build dir: $BUILD_DIR"
  # lcov --zerocounters can fail if no counters exist yet; treat that as non-fatal.
  lcov --quiet --directory "$BUILD_DIR" --zerocounters || true
fi

if [ "$SKIP_TEST_RUN" = "0" ]; then
  log "Running AppGateway L1 tests via RdkServicesL1Test"
  export PATH="$WS/install/usr/bin:$PATH"
  export LD_LIBRARY_PATH="$WS/install/usr/lib:$WS/install/usr/lib/wpeframework/plugins:${LD_LIBRARY_PATH:-}"

  # Emit gtest JSON for easy debugging
  export GTEST_OUTPUT="json:$GTEST_JSON"

  if [ -n "$GTEST_FILTER" ]; then
    "$WS/install/usr/bin/RdkServicesL1Test" "--gtest_filter=$GTEST_FILTER"
  else
    "$WS/install/usr/bin/RdkServicesL1Test"
  fi
else
  log "SKIP_TEST_RUN=1: skipping test execution; using existing .gcda files"
fi

log "Capturing raw lcov coverage from: $BUILD_DIR"
lcov -c -o "$RAW_INFO" -d "$BUILD_DIR"

log "Filtering coverage to focus on: $FOCUS_FILE_REL"
# Keep only entries that match the focus file. This yields a report that is
# specifically about the test translation unit requested.
lcov -e "$RAW_INFO" "*/$FOCUS_FILE_REL" -o "$FILTERED_INFO"

log "Generating HTML report at: $OUT_DIR"
genhtml -o "$OUT_DIR" -t "AppGateway L1 coverage - test_AppGateway.cpp" "$FILTERED_INFO"

log "Done."
log "Report index: $OUT_DIR/index.html"
log "Filtered info: $FILTERED_INFO"
log "Raw info:      $RAW_INFO"
