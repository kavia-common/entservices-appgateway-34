# AppGateway L1Tests Mapping (coverage-oriented)

## Purpose and scope

This document maps L1 test patterns (as seen in `code_ref/Tests/L1Tests/tests`) to concrete, coverage-oriented L1 test cases for the AppGateway plugin in this repository (`entservices-appgateway-34`).

Primary goals:

- Increase **AppGateway/Resolver** coverage with tests that are deterministic and runnable in constrained environments.
- Keep L1 tests runnable **without a compile-time dependency on `entservices-testframework`** by vendoring the minimal required mock/dependency headers under:
  - `Tests/L1Tests/mocks/**` (segregated by functionality).

## Current L1 test files in this repository

These are compiled under `Tests/L1Tests/tests`:

- `test_UtilsFile.cpp` – filesystem helper coverage (`helpers/UtilsFile.h`)
- `test_AppGateway.cpp` – Resolver/config coverage (`AppGateway/Resolver.*`)

## Reference L1 patterns (from `code_ref/Tests/L1Tests/tests`)

The reference suite demonstrates patterns that can be applied to AppGateway:

1. **Registered methods checks** via `Core::JSONRPC::Handler::Exists`
2. **JSON-RPC Invoke assertions** via `handler.Invoke(...)`
3. **Callsign-based dependency injection** via `ServiceMock::QueryInterfaceByCallsign(...)`
4. **Event subscription/payload verification** via `EVENT_SUBSCRIBE` and `service->Submit(...)`
5. **File-driven tests** for deterministic config parsing behavior

For AppGateway, the highest value “easy coverage” is in **Resolver** and **config-driven branching**. Deeper coverage of `AppGatewayImplementation` requires a Thunder-style `IShell` mock and additional interface mocks (AppNotifications, Authenticator, RequestHandler), which are not always available in minimal environments.

## Important note: no entservices-testframework compile-time dependency

Historically, L1 test builds used include paths pointing at:

- `../entservices-testframework/Tests/mocks/**`

This repository now vendors the minimal required headers into:

- `Tests/L1Tests/mocks/thunder/**` (e.g., `ThunderPortability.h`)

This allows `Tests/L1Tests/CMakeLists.txt` to remove include-path references to `entservices-testframework` while still compiling tests like `test_UtilsFile.cpp` that include `ThunderPortability.h`.

## Running the tests locally

### Via the repo runner (`run_l1_tests.sh`)

`run_l1_tests.sh` builds the repo with `-DRDK_SERVICES_L1_TEST=ON` and will run tests:

- Prefer `RdkServicesL1Test` (CI parity) if present
- Otherwise fallback to `ctest`

To ensure the fallback path actually executes tests without `RdkServicesL1Test`, this repo now also builds a standalone gtest binary:

- `AppGatewayL1Tests` (registered with `add_test(...)`)

So `ctest` runs real tests and coverage `.gcda` files are produced.

## AppGateway code under test (current focus)

- Resolver/config parsing and lookup:
  - `AppGateway/Resolver.cpp`
  - `AppGateway/Resolver.h`

Secondary (future expansion, requires additional mocks):

- `AppGateway/AppGatewayImplementation.cpp` (event handling, COM-RPC routing, permission checks)
- `AppGateway/AppGatewayResponderImplementation.cpp` (WebSocket auth/dispatch/cleanup)

## Tier A: Implemented now (no Thunder runtime required)

These tests live in `Tests/L1Tests/tests/test_AppGateway.cpp` and focus on `Resolver` behavior:

| S.No | Test case | Code paths / branches targeted | Key assertions |
|---:|---|---|---|
| 1 | `Resolver_LoadConfig_MissingFile_ReturnsFalse` | `LoadConfig`: file open failure | returns `false`, `IsConfigured()==false` |
| 2 | `Resolver_LoadConfig_InvalidJson_ReturnsFalse` | `LoadConfig`: JSON parse failure | returns `false`, `IsConfigured()==false` |
| 3 | `Resolver_LoadConfig_MissingResolutionsObject_ReturnsFalse` | `LoadConfig`: missing `"resolutions"` branch | returns `false` |
| 4 | `Resolver_LoadConfig_LowercasesKeysAndOverrides` | key normalization + override semantics | resolves lowercased key, later config overrides |
| 5 | `Resolver_LoadConfig_EventAndComRpcFlags_AndIncludeContextDefaults` | `HasEvent`, `HasComRpcRequestSupport`, defaulting based on `additionalContext` object | event true/false as expected; COM-RPC support derived |
| 6 | `Resolver_HasIncludeContext_PopulatesAdditionalContext` | `includeContext` defaulting + `HasIncludeContext` copying additionalContext | includeContext bool matches expected; returned additionalContext is set and object |
| 7 | `Resolver_HasPermissionGroup_ReturnsGroup` | `permissionGroup` parsing + `HasPermissionGroup` | permissionGroup returned; empty/missing returns false |
| 8 | `Resolver_ClearResolutions_ClearsConfiguredState` | `ClearResolutions` and post-clear behavior | `IsConfigured()==false`, lookup returns empty |
| 9 | `Resolver_CallThunderPlugin_NullShell_ReturnsError` | `CallThunderPlugin`: null-shell error path | returns `Core::ERROR_GENERAL` |

## Tier B: Deferred (requires more mocks / runtime simulation)

These cover `AppGatewayImplementation` branches but typically require:

- `ServiceMock` with `QueryInterfaceByCallsign` routing
- `Exchange::IAppNotifications` mock for subscribe/cleanup
- `Exchange::IAppGatewayAuthenticator` mock for permission group checks
- `Exchange::IAppGatewayRequestHandler` mock for COM-RPC routing

Examples of deferred tests:

- Resolver not initialized / not configured errors surfaced via `FetchResolvedData`
- Event param validation (`listen` missing / wrong type)
- Subscribe/unsubscribe behavior via AppNotifications
- Permission group allow/deny behavior
- COM-RPC request handler not available vs success path

## Sources

- Current repo tests:
  - `Tests/L1Tests/tests/test_AppGateway.cpp`
  - `Tests/L1Tests/tests/test_UtilsFile.cpp`
  - `Tests/L1Tests/CMakeLists.txt`
- Reference patterns:
  - `code_ref/Tests/L1Tests/tests/*`
- AppGateway implementation:
  - `AppGateway/Resolver.*`
  - `AppGateway/AppGatewayImplementation.*`
  - `AppGateway/AppGatewayResponderImplementation.*`
