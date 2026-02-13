# AppGateway L1Tests Mapping (from reference `code_ref/Tests/L1Tests/tests`)

## Purpose and scope

This document maps the reference L1 test style found in `code_ref/Tests/L1Tests/tests` to concrete, coverage-oriented L1 test cases for the AppGateway plugin in this repository (`entservices-appgateway-34`). The goal is to maximize AppGateway coverage by enumerating the specific branches and behaviors present in the current AppGateway implementation and by describing what a test must set up, call, and assert.

This mapping is intentionally code-driven. Every recommended test case is derived from what the current AppGateway implementation actually does. The mapping is also pattern-driven: it adapts the established conventions in the reference L1 suite (interface setup via callsign lookup, JSON-RPC registration checks via `handler.Exists`, end-to-end JSON-RPC calls via `handler.Invoke`, and event verification via `EVENT_SUBSCRIBE` and `service->Submit` interception).

## Current L1 test cases in this repository (and coverage)

The `Tests/L1Tests` target in this repository currently builds a single test file, `Tests/L1Tests/tests/test_UtilsFile.cpp`, into the `L1TestsIN` shared library (see `Tests/L1Tests/CMakeLists.txt`). The table below lists the concrete test cases that exist today, and what they cover.

| Test suite / case | Location | Type | Primary code under test | Coverage details (what it actually exercises) | Notes / gaps |
|---|---|---|---|---|---|
| `UtilsFileTest.createFolder_createFile_moveFile_verifyFile` | `Tests/L1Tests/tests/test_UtilsFile.cpp` | Unit-style (filesystem) | `helpers/UtilsFile.h` (and `WPEFramework::Core::Directory`, `WPEFramework::Core::File`) | Creates and destroys `/tmp/UtilsFileTest`, creates a file, writes bytes, uses `Utils::MoveFile(...)` to move into a nested destination path, and verifies file existence and contents after move. | This test improves coverage for helper filesystem utilities but does not directly cover AppGateway, Resolver, notifications, or WebSocket behavior. |

## Reference L1Tests suite patterns (what the reference teaches)

The reference suite under `code_ref/Tests/L1Tests/tests` contains multiple plugin tests (for example `test_AppManager.cpp`, `test_UserSettings.cpp`, `test_LifecycleManager.cpp`, `test_MessageControl.cpp`, `test_RDKShell.cpp`, and `test_UtilsFile.cpp`). These files demonstrate repeatable patterns that are directly applicable to AppGateway.

### Pattern 1: “Registered methods” checks (JSON-RPC surface verification)

Several reference tests start by asserting that a plugin exposes all expected JSON-RPC methods through `Core::JSONRPC::Handler::Exists`, for example:

In `test_AppManager.cpp`, `RegisteredMethodsUsingJsonRpcSuccess` checks methods like `getInstalledApps`, `launchApp`, `preloadApp`, `closeApp`, and others.

In `test_UserSettings.cpp`, `RegisteredMethods` checks a long list of `set*` and `get*` methods.

In `test_RDKShell.cpp`, `RegisteredMethods` enumerates many JSON-RPC methods.

This pattern is valuable because it gives broad, low-effort coverage of the JSON-RPC registration layer and will quickly reveal missing or renamed methods.

### Pattern 2: JSON-RPC Invoke with explicit request/response assertions

The reference suite frequently uses `handler.Invoke(connection, "method", requestJson, response)` and asserts:

That the return code matches expectations (`Core::ERROR_NONE`, `Core::ERROR_GENERAL`, `Core::ERROR_INVALID_PARAMETER`, and so on).

That the response JSON string matches exactly, or contains specific substrings.

For example, `test_AppManager.cpp` asserts exact JSON event payloads that are emitted via `service->Submit`.

### Pattern 3: COM-RPC and callsign-based dependency injection

The reference tests often simulate the Thunder runtime dependency graph by providing a `ServiceMock` and configuring `QueryInterfaceByCallsign` to return specific interface mocks based on callsign and requested interface ID.

For example, `test_AppManager.cpp` uses `QueryInterfaceByCallsign` to return mocks for:

- `org.rdk.LifecycleManager` (ILifecycleManager / ILifecycleManagerState)
- `org.rdk.PersistentStore` (IStore2)
- `org.rdk.StorageManager`
- `org.rdk.PackageManagerRDKEMS` (IPackageHandler / IPackageInstaller)

The AppGateway plugin uses the same style of callsign lookup for AppNotifications, request handlers, and authenticators. Tests should mimic this reference approach.

### Pattern 4: Event subscription and event payload verification

The reference `test_AppManager.cpp` uses the macros `EVENT_SUBSCRIBE` / `EVENT_UNSUBSCRIBE` and intercepts event payloads via `EXPECT_CALL(*mServiceMock, Submit(...))` to verify that emitted JSON matches an expected string, such as:

- `org.rdk.AppManager.onAppLaunchRequest`
- `org.rdk.AppManager.onAppLifecycleStateChanged`

For AppGateway, this pattern is directly relevant for two areas:

Event-style “listen” subscriptions (AppGatewayImplementation routes “event” methods to AppNotifications subscription).

WebSocket responder connection status notifications (AppGatewayResponderImplementation submits notifications via jobs).

### Pattern 5: Self-contained file-based testing for config parsing and filesystem utilities

`test_UtilsFile.cpp` illustrates a “real filesystem” approach using `/tmp` and verifying observable outcomes (file exists, bytes match). This is an excellent match for AppGateway’s resolver/config behavior because the resolver loads JSON configs from paths, and L1 tests can write temporary config JSON under `/tmp` to trigger branches deterministically.

## AppGateway code under test (what we are mapping to)

This mapping targets the following AppGateway implementation files:

Plugin wrapper behavior in `AppGateway/AppGateway.cpp` and `AppGateway/AppGateway.h`.

Request routing and configuration in `AppGateway/AppGatewayImplementation.cpp`.

Resolution parsing and Thunder invocation in `AppGateway/Resolver.cpp`.

WebSocket/authentication/dispatch logic in `AppGateway/AppGatewayResponderImplementation.cpp`.

Method classification inputs in `AppGateway/resolutions/resolution.base.json`.

## Proposed AppGateway-focused L1 tests (coverage-oriented mapping)

These are the L1 test cases that should be added to expand AppGateway coverage. They are written to align with the reference suite patterns, and each one points to specific branches/behaviors in the current implementation.

### Proposed test case table

| S.No | Proposed test case | Component(s) | Code paths / branches targeted | Setup pattern (based on reference) | Key assertions / observable outcomes |
|---:|---|---|---|---|---|
| 1 | `Resolver_LoadConfig_MissingFile_ReturnsFalse` | `Resolver` | `Resolver::LoadConfig`: file open failure (`!file.is_open()`) | No mocks required; call `LoadConfig("/tmp/does-not-exist.json")` | Returns `false`. `IsConfigured()` remains `false`. |
| 2 | `Resolver_LoadConfig_InvalidJson_ReturnsFalse` | `Resolver` | `Resolver::LoadConfig`: parse failure (`!FromString(...)`) | Write invalid JSON to `/tmp/resolution.invalid.json` | Returns `false`. Does not add resolutions. |
| 3 | `Resolver_LoadConfig_MissingResolutionsObject_ReturnsFalse` | `Resolver` | `Resolver::LoadConfig`: `!config.Resolutions.IsSet()` branch | Write `{ "notResolutions": {} }` to `/tmp` | Returns `false`. |
| 4 | `Resolver_LoadConfig_LowercasesKeysAndOverrides` | `Resolver` | Key normalization (`StringUtils::toLower(it.Label())`), override behavior (`mResolutions[key] = ...`) | Write config with mixed-case key; optionally load two configs with same key to exercise override counter path | `ResolveAlias("MiXeDCaSe")` returns expected alias. Later-loaded config wins. |
| 5 | `Resolver_LoadConfig_EventAndComRpcFlags` | `Resolver` | `HasEvent(...)` uses `!event.empty()`. `HasComRpcRequestSupport(...)` uses `useComRpc` | Write config containing one entry with `event` set and another with `useComRpc: true` | `HasEvent(method)` true for event entry. `HasComRpcRequestSupport(method)` true for COM-RPC entry. |
| 6 | `AppGateway_Resolve_ResolverNotInitialized` | `AppGatewayImplementation` | `FetchResolvedData`: `mResolverPtr == nullptr` -> `CustomInitialize("Resolver not initialized")` | Create `AppGatewayImplementation` and call `Resolve(...)` before `Configure(IShell*)` or force resolver null | Returns `Core::ERROR_GENERAL`. `resolution` contains initialization error JSON. |
| 7 | `AppGateway_Resolve_ResolverNotConfigured` | `AppGatewayImplementation` | `FetchResolvedData`: `!mResolverPtr->IsConfigured()` -> `CustomInitialize("Resolver not configured")` | Configure plugin but ensure `LoadConfig` never succeeds (e.g., use minimal shell + default paths absent in test env), or explicitly clear resolutions if a hook becomes available | Returns `Core::ERROR_GENERAL`. `resolution` contains “Resolver not configured”. |
| 8 | `AppGateway_Resolve_MethodNotSupported_NoAlias` | `AppGatewayImplementation` | `ResolveAlias(method)` empty -> `ErrorUtils::NotSupported` | Use a resolver config that omits the tested method | Returns `Core::ERROR_GENERAL`. `resolution` contains NotSupported error JSON (validate by substring). |
| 9 | `AppGateway_Event_PreProcessEvent_MissingParams_BadRequest` | `AppGatewayImplementation` | `PreProcessEvent`: params JSON parse fails -> `CustomBadRequest("Event methods require parameters")` | Configure resolver so `HasEvent(method)` is true; call `Resolve(..., params="")` or invalid JSON | Returns `Core::ERROR_BAD_REQUEST`. `resolution` contains the “Event methods require parameters” message. |
| 10 | `AppGateway_Event_PreProcessEvent_MissingListen_BadRequest` | `AppGatewayImplementation` | `PreProcessEvent`: missing boolean `listen` -> `CustomBadRequest("Missing required boolean 'listen' parameter")` | Provide event method resolution; call with `{}` or `{ "listen": "true" }` | Returns `Core::ERROR_BAD_REQUEST`. Resolution contains message. |
| 11 | `AppGateway_Event_SubscribeListenTrue_ReturnsListeningResponse` | `AppGatewayImplementation` + `IAppNotifications` | `HandleEvent` calls `mAppNotifications->Subscribe(...)` and `PreProcessEvent` returns `{ "listening": true, "event": method }` | Reference Pattern 3: `ServiceMock` + `QueryInterfaceByCallsign<Exchange::IAppNotifications>(APP_NOTIFICATIONS_CALLSIGN)` returns mock; method configured as event | Asserts `Subscribe` called with `listen=true`, `alias`, and `event` equal to the method key passed into `Resolve`. Asserts resolution JSON includes `"listening":true` and `"event":"<method>"`. |
| 12 | `AppGateway_ComRpc_RequestHandlerMissing_NotAvailable` | `AppGatewayImplementation` + `IAppGatewayRequestHandler` | `ProcessComRpcRequest`: `QueryInterfaceByCallsign<...>(alias)` returns null -> `ErrorUtils::NotAvailable` | Configure resolver with `useComRpc: true` and an alias callsign; do not provide handler mock | Returns `Core::ERROR_GENERAL`. `resolution` contains NotAvailable error JSON. |
| 13 | `AppGateway_ComRpc_AdditionalContext_WrapsParamsWith_additionalContext` | `AppGatewayImplementation` + `IAppGatewayRequestHandler` | `UpdateContext(... onlyAdditionalContext=true)` path: wraps `{ "params": <orig>, "_additionalContext": <additionalContext + origin> }` | Provide resolver entry where `additionalContext` is an object and (by default) `useComRpc` becomes true; mock a request handler and inspect the `finalParams` string passed to `HandleAppGatewayRequest` | Asserts `finalParams` JSON contains `params` and `_additionalContext.origin == origin`, plus the configured additionalContext fields. |
| 14 | `AppGateway_PermissionGroup_Denied_NotPermitted` | `AppGatewayImplementation` + `IAppGatewayAuthenticator` | `HasPermissionGroup` branch; `SetupAppGatewayAuthenticator` + `CheckPermissionGroup(...)` yields `allowed=false` or error | Configure resolver with `permissionGroup`; return authenticator mock; test both error return and `allowed=false` | Returns `Core::ERROR_GENERAL`. `resolution` contains NotPermitted. |
| 15 | `AppGateway_PermissionGroup_AuthenticatorMissing_AllowsToProceed` | `AppGatewayImplementation` | Behavior when authenticator interface is unavailable: `SetupAppGatewayAuthenticator()` returns false and code does not fail closed | Configure resolver with `permissionGroup` but ensure `QueryInterfaceByCallsign<IAppGatewayAuthenticator>` returns null; ensure downstream path is reachable (e.g., COM-RPC handler mock exists) | Verifies the current behavior that missing authenticator does not deny access, and downstream handler is invoked. This is security-sensitive and should be locked down by test so changes are deliberate. |

## Implementation details that tests must reflect

### 1. Resolution keys are always lowercased in `Resolver`

Because `LoadConfig` lowercases keys, tests must query using normalized keys and should include a case-insensitivity test.

### 2. Event method naming as implemented

Even if the config stores an `event` field, the implementation uses the method key when returning `event` in responses and when passing `event` to the notification subscription.

### 3. COM-RPC alias shape

In COM-RPC routing, the alias used for callsign lookup is a callsign (for example `org.rdk.AppGatewayCommon`), not a `callsign.method` string. This differs from the Thunder JSON-RPC invocation path in `CallThunderPlugin`, which expects `callsign.method`.

### 4. `_additionalContext` wrapping structure

When additional context is enabled for COM-RPC routing, the final params string becomes an object containing `params` and `_additionalContext`. Tests should assert this exact shape.

## Coverage gaps and risks (derived from reference suite and AppGateway’s architecture)

The reference suite demonstrates both JSON-RPC and COM-RPC style testing, but AppGateway combines multiple subsystems (resolver, permission checks, notification subscription, and WebSocket dispatch). Achieving high coverage will require reusable mocks similar to the reference’s `ServiceMock`-based callsign injection and the associated `QueryInterfaceByCallsign`-driven callsign routing, because many AppGateway branches only become reachable when the test injects the correct interface mock for a specific callsign.

Some tests will also need a flexible assertion strategy for error and resolution payloads. Depending on how the error formatting helpers serialize JSON, the precise ordering/formatting of fields can vary, so it can be more robust to validate behavior using substring-based checks on the `resolution` JSON (for example asserting that the payload contains an expected error code/message fragment) rather than requiring exact full-string comparisons.

## Sources

This mapping is derived from:

- Current repository L1 test build and tests:
  - `Tests/L1Tests/CMakeLists.txt`
  - `Tests/L1Tests/tests/test_UtilsFile.cpp`
- Reference L1 tests:
  - `code_ref/Tests/L1Tests/tests/test_AppManager.cpp`
  - `code_ref/Tests/L1Tests/tests/test_UserSettings.cpp`
  - `code_ref/Tests/L1Tests/tests/test_LifecycleManager.cpp`
  - `code_ref/Tests/L1Tests/tests/test_MessageControl.cpp`
  - `code_ref/Tests/L1Tests/tests/test_RDKShell.cpp`
  - `code_ref/Tests/L1Tests/tests/test_UtilsFile.cpp`
  - `code_ref/Tests/L1Tests/CMakeLists.txt`
- AppGateway implementation:
  - `AppGateway/AppGateway.cpp`
  - `AppGateway/AppGateway.h`
  - `AppGateway/AppGatewayImplementation.cpp`
  - `AppGateway/Resolver.cpp`
  - `AppGateway/AppGatewayResponderImplementation.cpp`
  - `AppGateway/resolutions/resolution.base.json`
- Supporting repo docs:
  - `Tests/README.md`
  - `docs/l1-workflow-vs-runner.md`
