# AppGateway L1Tests Mapping (from reference `code_ref/Tests/L1Tests/tests`)

## Purpose and scope

This document maps the reference L1 test style found in `code_ref/Tests/L1Tests/tests` to concrete, coverage-oriented L1 test cases for the AppGateway plugin in this repository (`entservices-appgateway-34`). The goal is to maximize AppGateway coverage by enumerating the specific branches and behaviors present in the current AppGateway implementation and by describing what a test must set up, call, and assert.

This mapping is intentionally code-driven. Every recommended test case is derived from what the current AppGateway implementation actually does. The mapping is also pattern-driven: it adapts the established conventions in the reference L1 suite (interface setup via callsign lookup, JSON-RPC registration checks via `handler.Exists`, end-to-end JSON-RPC calls via `handler.Invoke`, and event verification via `EVENT_SUBSCRIBE` and `service->Submit` interception).

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

- Event-style “listen” subscriptions (AppGatewayImplementation routes “event” methods to AppNotifications subscription).
- WebSocket responder connection status notifications (AppGatewayResponderImplementation submits notifications via jobs).

### Pattern 5: Self-contained file-based testing for config parsing and filesystem utilities

`test_UtilsFile.cpp` illustrates a “real filesystem” approach using `/tmp` and verifying observable outcomes (file exists, bytes match). This is an excellent match for AppGateway’s resolver/config behavior because the resolver loads JSON configs from paths, and L1 tests can write temporary config JSON under `/tmp` to trigger branches deterministically.

## AppGateway code under test (what we are mapping to)

This mapping covers:

- Plugin wrapper behavior in `AppGateway/AppGateway.cpp` and `AppGateway/AppGateway.h`.
- Request routing and configuration in `AppGateway/AppGatewayImplementation.cpp`.
- Resolution parsing and Thunder invocation in `AppGateway/Resolver.cpp`.
- WebSocket/authentication/dispatch logic in `AppGateway/AppGatewayResponderImplementation.cpp`.
- Method classification inputs in `AppGateway/resolutions/resolution.base.json`.

## Concrete mapping: recommended AppGateway L1 tests (aligned to reference patterns)

The test cases below are organized by AppGateway component and are phrased as: what to test, what reference pattern it mirrors, where it lands in code, and what to assert.

### A. JSON-RPC surface tests (reference “RegisteredMethods” pattern)

#### A1. AppGateway exposes resolver methods via JSON-RPC registration

This mirrors `test_AppManager.cpp` / `test_UserSettings.cpp` “RegisteredMethods” checks.

The test should initialize the AppGateway plugin and assert that the `Core::JSONRPC::Handler` reports expected resolver methods exist. The exact method names to check must match the symbols registered by `Exchange::JAppGatewayResolver::Register(*this, ...)` in the AppGateway wrapper.

The assertions should be:

It asserts that `handler.Exists("...")` returns `Core::ERROR_NONE` for each required method.

It asserts that `handler.Exists("aDefinitelyMissingMethod")` returns a non-zero error to prove the test is meaningful.

Note: this document does not hardcode the exact JSON-RPC method strings because the AppGateway JSON-RPC facade is generated and can vary by interface version. The test should use the same names that are used by clients in the repository (or derive them from the generated `JAppGatewayResolver` headers).

### B. Resolver config parsing tests (`Resolver::LoadConfig`) (reference “/tmp filesystem” pattern)

These tests follow the `test_UtilsFile.cpp` pattern: create temp files under `/tmp`, call methods, and assert results.

#### B1. LoadConfig fails when file is missing

It targets `Resolver::LoadConfig` early failure when `std::ifstream(path)` is not open.

It asserts that `LoadConfig("/tmp/does-not-exist.json")` returns `false` and that `IsConfigured()` remains `false`.

#### B2. LoadConfig fails on invalid JSON

It targets the JSON parse failure branch (`IElement::FromString`).

It writes invalid JSON to `/tmp` and asserts `LoadConfig(path)` returns `false`.

#### B3. LoadConfig fails when `resolutions` is missing

It writes a valid JSON file without a `resolutions` object and asserts `LoadConfig` returns `false`.

#### B4. LoadConfig loads an entry and lowercases the resolution key

It targets the lowercasing behavior (`StringUtils::toLower(it.Label())`).

It writes a config with a mixed-case key and asserts `ResolveAlias(lowercaseKey)` returns the expected alias.

#### B5. LoadConfig marks event methods and COM-RPC methods correctly

It writes a config entry with an `event` field and asserts `HasEvent(methodKey)` is true.

It writes a config entry with `useComRpc: true` and asserts `HasComRpcRequestSupport(methodKey)` is true.

#### B6. Default boolean behavior when `additionalContext` is an object

It writes `additionalContext` as an object without explicitly setting `includeContext` and `useComRpc`, then asserts the defaults reflect `hasAdditionalContext`.

This is important because AppGateway uses context injection and additional context in multiple branches.

#### B7. Multiple config loads override earlier entries

It loads config A then config B for the same key and asserts that the later alias is returned.

This matches how the implementation overwrites `mResolutions[key]`.

### C. AppGatewayImplementation resolution routing tests (event vs COM-RPC vs Thunder)

These tests should follow the reference’s callsign-based injection style (as in `test_AppManager.cpp`) by using a `ServiceMock` whose `QueryInterfaceByCallsign` returns the necessary dependency mocks.

#### C1. Resolve fails when resolver is not initialized

It targets `AppGatewayImplementation::Resolve` before the resolver is set up.

It asserts return `Core::ERROR_GENERAL` and that the `resolution` output string includes the phrase “Resolver not initialized”.

#### C2. Resolve fails when resolver is not configured

It targets the `!IsConfigured()` branch.

It asserts return `Core::ERROR_GENERAL` and that `resolution` indicates “Resolver not configured”.

#### C3. Resolve fails when method has no alias (NotSupported)

It loads a config that does not contain the requested method and asserts:

It returns `Core::ERROR_GENERAL`.

The `resolution` is an error JSON consistent with the NotSupported helper (non-empty, and stable enough to validate via substring checks).

#### C4. Event routing: missing params / missing `listen` (BadRequest)

This maps to AppGateway’s `PreProcessEvent` checks:

If params are not valid JSON, it returns a bad request error indicating event methods require parameters.

If params JSON does not include a boolean `listen`, it returns a bad request error indicating missing required boolean `listen`.

These tests should assert both the error code (`Core::ERROR_BAD_REQUEST`) and that `resolution` includes the corresponding message.

#### C5. Event routing: subscribe and response shape (reference “event payload verification” idea)

This maps to the reference suite’s emphasis on observable outcomes, like verifying `service->Submit` payloads in `test_AppManager.cpp`. For AppGateway, the key observable is that the gateway calls into AppNotifications with the correct parameters and returns the correct JSON response.

The test should:

Provide a fake or mock `Exchange::IAppNotifications` via callsign lookup.

Call `Resolve` for an event method with `{"listen": true}` and assert:

The subscription method is called with the expected alias and event identifiers.

`Resolve` returns `Core::ERROR_NONE`.

`resolution` contains JSON that includes `listening` and `event`.

Important implementation detail: AppGateway’s event branch uses the *method key* as the event identifier when building the result and when calling into AppNotifications. Tests should assert the behavior as implemented, not as might be expected from the `Resolution.event` field.

#### C6. COM-RPC routing: request handler missing (NotAvailable)

It targets the branch where `QueryInterfaceByCallsign<Exchange::IAppGatewayRequestHandler>(alias)` returns null.

It asserts return `Core::ERROR_GENERAL` and `resolution` indicates NotAvailable.

#### C7. COM-RPC routing: additional context wrapping (`_additionalContext`)

It targets `UpdateContext(... onlyAdditionalContext=true)` behavior.

The test should:

Create a resolution entry with `additionalContext` as a JSON object.

Call `Resolve` with a JSON params object.

Assert that the request handler receives a JSON string shaped as:

- A top-level object containing `params` (the original params object)
- And `_additionalContext` containing the configured additional context fields plus an injected `origin`

This is a high-value structural assertion because it covers a core “gateway enrichment” behavior.

### D. Permission group enforcement tests

This area has the same style of dependency injection used throughout the reference suite: call `QueryInterfaceByCallsign` to get the authenticator.

#### D1. Permission denied when authenticator returns error

It forces `CheckPermissionGroup` to return an error and asserts NotPermitted.

#### D2. Permission denied when allowed is false

It forces `allowed=false` with a success return code and asserts NotPermitted.

#### D3. Permission allowed continues to downstream route

It forces `allowed=true` and asserts the downstream route is taken and succeeds (for example, COM-RPC handler is called).

Important: in the current implementation, permission enforcement only runs if `SetupAppGatewayAuthenticator()` succeeds. If the authenticator interface cannot be queried, the request does not fail closed. Tests should explicitly capture this current behavior so security-sensitive changes are intentional.

### E. WebSocket responder tests (`AppGatewayResponderImplementation`) (reference “self-contained shell” pattern)

`test_MessageControl.cpp` includes a minimal `TestShell` implementation of `PluginHost::IShell` used for plugin initialization. For AppGateway’s responder, a similar minimal shell can be used where needed.

High-value responder tests include:

It denies authentication when the `session` query is missing from the token.

It denies authentication when the authenticator interface is unavailable.

It closes the connection when a message is received for a connectionId with no registered appId.

It calls resolver `Resolve` with a context that includes `requestId`, `connectionId`, and `appId` when the appId mapping exists.

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

The reference suite demonstrates both JSON-RPC and COM-RPC style testing, but AppGateway combines multiple subsystems (resolver, permission checks, notification subscription, and WebSocket dispatch). Achieving high coverage will require reusable mocks similar to the reference’s `ServiceMock`-based callsign injection, and some tests may need to validate behavior using substring checks on resolution JSON rather than exact full-string comparisons, depending on error formatting helpers.

## Sources

This mapping is derived from:

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
