# L1 GitHub Workflow vs `run_l1_tests.sh` (Coverage and Missing Steps)

## Purpose

This repository has two distinct ways to run L1 tests:

The first way is the GitHub Actions workflow at `.github/workflows/L1-tests.yml`, which performs a full, self-contained CI-style build that pulls in external dependencies and generates artifacts such as valgrind logs and LCOV HTML coverage.

The second way is the host-shell script `run_l1_tests.sh`, which is designed for running in constrained host/container environments without relying on `act` or Docker, and it primarily focuses on applying patches idempotently and then running a CMake + CTest based test pass.

This document summarizes what the workflow does that the script does not, with special attention to coverage generation.

## High-level summary of differences

The GitHub Actions workflow is a full environment provisioning and multi-repo build pipeline. It installs OS packages, clones dependencies, builds Thunder/ThunderTools/googletest, builds mocks, builds `entservices-appgateway`, builds `entservices-testframework`, runs `RdkServicesL1Test` twice (with and without valgrind), generates coverage using `lcov`/`genhtml`, and uploads artifacts.

By contrast, `run_l1_tests.sh` assumes most of the environment is already present. It optionally runs `build_dependencies.sh` (but skips it by default), applies some patches (when the target repos exist in the workspace), and then configures/builds/tests the current repository using `cmake` and `ctest`. It does not build the external dependency stack, does not run `RdkServicesL1Test`, and does not generate LCOV coverage.

## What `.github/workflows/L1-tests.yml` does

### Tooling and dependencies

The workflow installs a long list of system packages, notably including `valgrind`, `lcov`, `clang`, `meson`, `protobuf-compiler-grpc`, `libgrpc-dev`, and others. It also installs a Python dependency (`jsonref`) using `pip`.

It then builds and installs `trower-base64` using Meson + Ninja.

### External repo checkouts and caching

The workflow checks out (and caches the build outputs/install tree for) several repositories:

It checks out `Thunder` at `R4.4.1` and `ThunderTools` at `R4.4.3`, checks out `googletest` at `v1.15.0`, checks out `entservices-apis` and applies patches, checks out `entservices-testframework`, and checks out `entservices-appgateway` either locally or from GitHub depending on `inputs.caller_source`.

### Patch application

The workflow applies patch sets to ThunderTools and Thunder, and applies `RDKEMW-1007.patch` to `entservices-apis`.

### Builds (multiple build roots)

The workflow builds and installs, in order:

It builds ThunderTools into `build/ThunderTools` and installs into `$GITHUB_WORKSPACE/install/usr`.

It builds Thunder into `build/Thunder` and installs into the same prefix.

It builds `entservices-apis` into `build/entservices-apis` and installs it.

It builds `googletest` into `build/googletest` and installs it.

It builds testframework mocks into `build/mocks` and installs them.

It builds `entservices-appgateway` into `build/entservices-appgateway` and installs it.

It builds `entservices-testframework` into `build/entservices-testframework` and installs it.

Several of these build steps inject coverage flags directly via `-DCMAKE_CXX_FLAGS=" ... --coverage ..."` and include `-fprofile-arcs` and `-ftest-coverage`.

### Test execution and artifacts

The workflow runs `RdkServicesL1Test` directly (not via `ctest`) and captures GTest JSON output twice:

It runs once without valgrind and copies the JSON report to `rdkL1TestResultsWithoutValgrind.json`.

It runs once with valgrind (in non-`ACT` contexts) and copies the JSON report to `rdkL1TestResultsWithValgrind.json`, plus saves `valgrind_log`.

### Coverage generation (LCOV + HTML)

The workflow generates coverage only when the matrix indicates `with-coverage` and when not running under `ACT`.

The coverage step does the following:

It copies `entservices-testframework/Tests/L1Tests/.lcovrc_l1` to `~/.lcovrc`.

It runs `lcov -c -o coverage.info -d build/entservices-appgateway`.

It filters out third party and irrelevant paths using `lcov -r ... -o filtered_coverage.info`.

It runs `genhtml -o coverage -t "entservices-appgateway coverage" filtered_coverage.info`.

Finally, it uploads `coverage/` as an artifact.

## What `run_l1_tests.sh` does today

### Patch behavior

The script provides an idempotent, non-interactive patch application helper that avoids the interactive `patch` prompts (including "Assume -R?") and avoids forcing patches that would generate `.rej` files.

It can pin ThunderTools to an expected revision (`R4.4.3`) before patching, but it only does so if a `ThunderTools/` directory exists in the workspace.

It conditionally applies:

It applies `00010-R4.4-Add-support-for-project-dir.patch` to ThunderTools if both `ThunderTools/` and `entservices-testframework/` exist.

It applies five Thunder patches if both `Thunder/` and `entservices-testframework/` exist.

It applies `RDKEMW-1007.patch` to `entservices-apis` if both `entservices-apis/` and `entservices-testframework/` exist.

### Build and test execution model

The script then runs:

`cmake -S <repo-root> -B <build_dir> -DCMAKE_BUILD_TYPE=Debug -DRDK_SERVICES_L1_TEST=ON`

`cmake --build <build_dir>`

`ctest --test-dir <build_dir> --output-on-failure`

This is a standard CMake + CTest invocation for this repo only. It does not build the multi-repo dependency stack, does not install to `$GITHUB_WORKSPACE/install/usr`, and does not run `RdkServicesL1Test` directly.

### Dependency installation behavior

Although the repo contains `build_dependencies.sh` (which is effectively a CI bootstrap script that does `apt install`, clones repos, and builds them), `run_l1_tests.sh` intentionally skips it by default (`INSTALL_DEPS=auto`) to avoid failures in constrained environments where `apt` cannot run.

This means a typical `./run_l1_tests.sh` run is not equivalent to the GitHub Actions workflow unless the workspace is already prepared.

## Missing steps/options in `run_l1_tests.sh` compared to the workflow

### Coverage generation is not implemented in the script

The workflow explicitly enables coverage compilation flags for multiple targets and generates LCOV HTML output using:

It uses `--coverage`, `-fprofile-arcs`, and `-ftest-coverage`.

It runs `lcov` and `genhtml` and creates a `coverage/` directory output.

`run_l1_tests.sh` does none of these things. It also does not ensure that `lcov` is installed.

If you need local coverage output comparable to CI, you must either:

Run `build_dependencies.sh` in a suitable privileged environment and then manually run the LCOV commands, or

Extend the local workflow to configure the build with coverage flags and then run `lcov`/`genhtml` (see the local reproduction section below).

### Valgrind runs and GTest JSON reports are not produced

The workflow runs `RdkServicesL1Test` and saves:

`rdkL1TestResultsWithoutValgrind.json`

`rdkL1TestResultsWithValgrind.json`

and `valgrind_log`.

`run_l1_tests.sh` runs `ctest` and does not produce these files. It also does not set `GTEST_OUTPUT` or run valgrind.

### Multi-repo dependency stack is not provisioned

The workflow checks out and builds all of the following into a local install prefix:

Thunder, ThunderTools, googletest, entservices-apis, entservices-testframework mocks, entservices-testframework runner.

`run_l1_tests.sh` only builds this repository (and only applies patches to external repos if they already exist locally). It does not clone or build any external repositories.

### Toolchain selection matrix and `ACT` conditionals do not exist

The workflow has a matrix over:

compiler: `gcc` and `clang` (although the current matrix excludes all clang entries)

coverage: `with-coverage` and `without-coverage` (but only gcc+with-coverage is enabled via exclusions)

It also conditionally disables some steps when `env.ACT` is set.

`run_l1_tests.sh` does not have a notion of a compiler matrix or a coverage mode switch.

### Environment setup and fake filesystem scaffolding are missing

The workflow creates a large number of directories and files under `/tmp`, `/opt`, `/run`, `/dev`, and `/etc` to satisfy expectations in tests.

`run_l1_tests.sh` does not attempt to create these. If your tests or the test runner require them, local runs may behave differently.

## Local reproduction: coverage generation (workflow-equivalent commands)

The GitHub Actions workflow’s coverage generation step assumes that:

Your build directory for the appgateway build is `build/entservices-appgateway`.

The build was compiled with GCC coverage instrumentation (`--coverage`, `-fprofile-arcs`, `-ftest-coverage`).

The test execution has already happened (so `.gcda` files exist).

To reproduce the workflow coverage step locally, run from the same workspace root layout used by the workflow:

```bash
cp entservices-testframework/Tests/L1Tests/.lcovrc_l1 ~/.lcovrc

lcov -c -o coverage.info -d build/entservices-appgateway

lcov -r coverage.info \
  '/usr/include/*' \
  '*/build/entservices-appgateway/_deps/*' \
  '*/install/usr/include/*' \
  '*/Tests/headers/*' \
  '*/Tests/mocks/*' \
  '*/Tests/L1Tests/tests/*' \
  '*/Thunder/*' \
  -o filtered_coverage.info

genhtml -o coverage -t "entservices-appgateway coverage" filtered_coverage.info
```

If you are using `run_l1_tests.sh` as-is, the script’s default build directory is `build_l1` and it does not enable coverage flags. In that case, the `lcov` command above will not produce meaningful output.

## Notes from recent local runs

The attached run log indicates failures during CMake configuration in constrained environments, including:

A permission error in CMake’s CTest module writing configuration.

A `config_generator` failure with an unrecognized parameter.

These are environment- and toolchain-dependent issues and are not directly addressed by `run_l1_tests.sh` because the GitHub Actions workflow builds and installs a very specific dependency stack and configuration generator tooling into `$GITHUB_WORKSPACE/install/usr` and sets include paths and compilation flags extensively.
