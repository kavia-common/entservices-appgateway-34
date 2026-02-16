# Vendored test mocks (repo-local)

This directory contains a minimal set of mock/portability headers vendored from `entservices-testframework` so this repository’s tests can be built and run **without** a compile-time dependency on that external repository.

Layout is segregated by functionality:

- `thunder/`: Thunder/WPEFramework portability macros and common Thunder-style mock helpers (e.g., `ServiceMock.h`, `ThunderPortability.h`).

Notes:
- These headers are intentionally kept small and are only meant to unblock L1 compilation/execution for this repository.
- If additional mocks are needed for deeper coverage, add them under a dedicated subfolder to keep responsibilities separated.
