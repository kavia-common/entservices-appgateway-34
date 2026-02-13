# AppGateway L1Tests Mapping (from Code_Ref L1Tests)

## Purpose and scope

This document maps the reference L1 test style found in `Code_Ref/Tests/L1Tests/tests` to concrete, coverage-oriented L1 test cases for the AppGateway plugin in this repository (`entservices-appgateway-34`). The goal is to maximize AppGateway coverage by enumerating the specific branches and behaviors present in the current AppGateway implementation and by describing what a test must set up, call, and assert.

This document is intentionally code-driven. Every recommended test case is derived from what the current implementation actually does in:

It covers plugin wrapper behavior in `AppGateway/AppGateway.cpp`, request routing and configuration in `AppGateway/AppGatewayImplementation.cpp`, config parsing and Thunder invocation in `AppGateway/Resolver.cpp`, and WebSocket/authentication/dispatch logic in `AppGateway/AppGatewayResponderImplementation.cpp`. It also uses `AppGateway/resolutions/resolution.base.json` to identify which request classes (event vs COM-RPC vs Thunder JSON-RPC) need direct test coverage.

## Reference Code_Ref L1Tests pattern (what it teaches)

The only provided reference test file is:

`Code_Ref/Tests/L1Tests/tests/test_UtilsFile.cpp`

It is identical in structure to this repository’s `Tests/L1Tests/tests/test_UtilsFile.cpp`. The reference illustrates the key L1 characteristics used in this ecosystem:

The test is self-contained and asserts observable outcomes rather than internal state. It uses real filesystem operations in `/tmp`, creates and moves real files, and verifies the final content bytes. It also includes a small portability conditional (`USE_THUNDER_R4`) to match differing Thunder versions.

The implication for AppGateway is that high-value L1 tests should aim for functional results (return codes, JSON payload strings, and side effects such as “Subscribe was called with these parameters”), while using lightweight fakes/mocks only where the code requires a Thunder shell or interfaces queried by callsign.

## AppGateway code under test (what we are mapping to)

### Plugin wrapper: `WPEFramework::Plugin::AppGateway`

`AppGateway/AppGateway.cpp` and `AppGateway/AppGateway.h` implement the Thunder plugin wrapper that:

It stores `mService`, roots the out-of-process resolver and responder implementations (`Root<Exchange::IAppGatewayResolver>` and `Root<Exchange::IAppGatewayResponder>`), optionally calls `IConfiguration::Configure(service)` on each, registers/unregisters the JSON-RPC interface via `Exchange::JAppGatewayResolver::{Register,Unregister}`, and terminates remote connections in `Deinitialize()`.

This wrapper has critical error branches that are easy to miss if tests only cover the inner implementations.

### Resolver implementation and routing: `WPEFramework::Plugin::AppGatewayImplementation`

`AppGateway/AppGatewayImplementation.cpp` implements:

It creates a `Resolver` and loads config via `InitializeResolver()` (regional config in `/etc/app-gateway/resolutions.json` with fallback to `/etc/app-gateway/resolution.base.json`). It also provides an override configuration entry point `Configure(IStringIterator* paths)` for testability. It routes each `Resolve()` to one of three paths based on the loaded resolution entry:

It treats a method as an event when `Resolver::HasEvent(method)` is true, then it requires JSON params containing boolean `listen` and subscribes via `IAppNotifications::Subscribe(...)`.

It routes to COM-RPC when `Resolver::HasComRpcRequestSupport(method)` is true, using `QueryInterfaceByCallsign<Exchange::IAppGatewayRequestHandler>(alias)` and calling `HandleAppGatewayRequest(...)`. In this branch, `UpdateContext(..., onlyAdditionalContext=true)` wraps parameters in a `{"params": <original>, "_additionalContext": {...}}` object if an additional context object is present.

It routes to Thunder JSON-RPC when neither event nor COM-RPC, and it may inject a `context` object into the params object when `includeContext` is enabled for the method. It then calls `Resolver::CallThunderPlugin(alias, finalParams, resolution)`.

It also enforces permission groups (when configured in the resolution entry) by acquiring an authenticator (`QueryInterfaceByCallsign<Exchange::IAppGatewayAuthenticator>(GATEWAY_AUTHENTICATOR_CALLSIGN)`) and calling `CheckPermissionGroup(appId, permissionGroup, allowed)`.

### Configuration parsing and Thunder invocation: `WPEFramework::Plugin::Resolver`

`AppGateway/Resolver.cpp` implements:

It loads resolution entries from JSON using `LoadConfig(path)`, storing them in an internal map keyed by the lowercased method string. It extracts fields `alias`, `event`, `permissionGroup`, `additionalContext`, `includeContext`, and `useComRpc`. It defaults `includeContext` and `useComRpc` to `true` when `additionalContext` is a JSON object and the booleans are not explicitly present. It also parses `alias` by splitting on the last dot to determine `callsign` and `pluginMethod` for Thunder invocation.

`CallThunderPlugin` obtains a Thunder controller client via `Utils::GetThunderControllerClient(mService, callsign)` and then performs `Invoke<std::string, std::string>(pluginMethod, params, response)`.

### WebSocket side: `WPEFramework::Plugin::AppGatewayResponderImplementation`

`AppGateway/AppGatewayResponderImplementation.cpp` implements:

It starts a WebSocket server using `WebSocketConnectionManager`, sets a message handler that schedules `WsMsgJob`, sets an auth handler that extracts a `session` query parameter from a token, authenticates it to an `appId`, and registers `connectionId -> appId` internally. On disconnect it cleans up, emits connection status notifications, and calls `IAppNotifications::Cleanup(connectionId, APP_GATEWAY_CALLSIGN)` if available.

It dispatches WebSocket messages in `DispatchWsMsg(...)` by constructing a `Context { requestId, connectionId, appId }`, querying the resolver interface (`mService->QueryInterface<Exchange::IAppGatewayResolver>()`), and calling `Resolve(context, APP_GATEWAY_CALLSIGN, method, params, resolution)`. If there is no appId for the connection, it closes the connection via `mWsManager.Close(connectionId)`.

## Concrete mapping: recommended AppGateway L1 tests (code-accurate)

The following test cases are expressed as “what to test”, “where in code it lands”, and “what to assert”. They are intended to be implemented in the L1 tests suite (under this repo’s `Tests/L1Tests/tests/`) and linked into the L1 runner (via the external testframework repo), consistent with `Tests/README.md`.

### A. Code_Ref-aligned “file-based config” tests for `Resolver::LoadConfig`

These tests are the closest match to the Code_Ref `UtilsFile` pattern because they can create temp files and assert observable outcomes without requiring a live Thunder runtime.

#### A1. LoadConfig fails when file is missing

It targets `Resolver::LoadConfig` early failure when `std::ifstream(path)` is not open.

It sets up a `Resolver` instance and calls `LoadConfig("/tmp/does-not-exist.json")`.

It asserts that the return value is `false`, and that `IsConfigured()` remains `false`.

#### A2. LoadConfig fails on invalid JSON

It targets `IElement::FromString(jsonContent, error)` failure branch.

It writes an invalid JSON file under `/tmp` and calls `LoadConfig(path)`.

It asserts `false` and `IsConfigured()` remains `false`.

#### A3. LoadConfig fails when `resolutions` is missing

It targets the explicit check:

`if (!config.Resolutions.IsSet()) { ... return false; }`

It writes a valid JSON file with a top-level object that does not include `"resolutions"`.

It asserts `false`.

#### A4. LoadConfig loads an alias-only resolution and lowercases keys

It targets resolution insertion and case-insensitive lookup behavior:

`const std::string& key = StringUtils::toLower(it.Label());`

It writes:

```json
{
  "resolutions": {
    "Device.Name": { "alias": "org.rdk.AppGatewayCommon", "useComRpc": true }
  }
}
```

It asserts:

It returns `true`.

It makes `IsConfigured()` true.

It returns `org.rdk.AppGatewayCommon` from `ResolveAlias("device.name")`.

#### A5. LoadConfig marks event presence when `event` string is set

It targets `HasEvent` and the `event` string extraction.

It writes a resolution entry including `"event": "Device.onDeviceNameChanged"`.

It asserts `HasEvent("device.onnamechanged")` is true (matching the key used in the JSON file you wrote).

#### A6. Default boolean behavior when `additionalContext` is an object

This targets the defaulting logic:

`bool hasAdditionalContext = r.additionalContext.Content() == OBJECT;`
`includeContext = ExtractBooleanField(..., default=hasAdditionalContext)`
`useComRpc = ExtractBooleanField(..., default=hasAdditionalContext)`

It writes a resolution entry with:

`"additionalContext": {"foo":"bar"}` and omits `includeContext` and `useComRpc`.

It asserts:

`HasIncludeContext(key, additionalContext)` returns `true` and `additionalContext` is set to an object.

`HasComRpcRequestSupport(key)` returns `true`.

It also should include a companion test where `includeContext` is explicitly `false` even when `additionalContext` is an object, and assert that `HasIncludeContext` is `false`.

#### A7. Overriding behavior when loading multiple configs

It targets the override behavior:

`mResolutions[key] = std::move(r);` and the “overriddenCount” path.

It loads config A defining the same method key with alias A, then config B defining the same key with alias B.

It asserts `ResolveAlias(key)` returns alias B after the second load, confirming later loads override earlier entries (which matches how `InternalResolutionConfigure` is documented and implemented).

#### A8. ParseAlias uses the last dot

It targets `Resolver::ParseAlias` using `rfind('.')`.

It calls `ParseAlias("org.rdk.AppGatewayCommon.method", callsign, method)`.

It asserts callsign is `org.rdk.AppGatewayCommon` and method is `method`.

This is important because it is how `CallThunderPlugin` decides `callsign` vs `pluginMethod`.

### B. `AppGatewayImplementation::Configure(pathsIterator)` tests (pure validation + successful config load)

These tests avoid hard-coded `/etc/app-gateway` dependencies by using the override `Configure(IStringIterator*)` and temporary config files created under `/tmp`.

#### B1. Configure(paths) returns BAD_REQUEST on null iterator

It targets:

`if (paths == nullptr) return Core::ERROR_BAD_REQUEST;`

It asserts the return value equals `Core::ERROR_BAD_REQUEST`.

#### B2. Configure(paths) returns GENERAL when resolver is not initialized

It targets:

`if (mResolverPtr == nullptr) return Core::ERROR_GENERAL;`

It constructs `AppGatewayImplementation` and calls `Configure(pathsIterator)` without first calling `Configure(PluginHost::IShell*)` (which calls `InitializeResolver`).

It asserts `Core::ERROR_GENERAL`.

#### B3. Configure(paths) returns BAD_REQUEST when iterator yields no paths

It targets `if (configPaths.empty()) return Core::ERROR_BAD_REQUEST;`

It provides an iterator whose `Next(currentPath)` returns false immediately.

It asserts `Core::ERROR_BAD_REQUEST`.

#### B4. InternalResolutionConfigure returns GENERAL if no provided config loads

It targets `if (!anyConfigLoaded) return Core::ERROR_GENERAL;`

It provides a paths iterator returning only nonexistent file paths.

It asserts `Core::ERROR_GENERAL`.

#### B5. InternalResolutionConfigure succeeds when at least one config loads

It provides two paths, one missing, one valid config JSON.

It asserts `Core::ERROR_NONE` and that the resolver can now resolve methods from the loaded config.

#### B6. Override order matches implementation (“later paths take precedence”)

It loads two configs with the same resolution key, and asserts that the alias corresponds to the later file.

This directly covers the intended behavior described by log messages and implemented in `InternalResolutionConfigure`.

### C. `AppGatewayImplementation::FetchResolvedData` routing tests (event vs COM-RPC vs Thunder)

These tests provide the highest functional coverage of the gateway’s behavior. They require a fake `PluginHost::IShell` that can satisfy `QueryInterfaceByCallsign<...>(alias)` and/or `QueryInterfaceByCallsign<...>(APP_NOTIFICATIONS_CALLSIGN)` calls.

#### C1. Resolve returns “Resolver not initialized”

It targets:

`if (mResolverPtr == nullptr) { ErrorUtils::CustomInitialize("Resolver not initialized", resolution); return Core::ERROR_GENERAL; }`

It calls `Resolve(...)` before `Configure(shell)`.

It asserts it returns `Core::ERROR_GENERAL` and that the returned `resolution` contains the error message string (at minimum the phrase “Resolver not initialized”).

#### C2. Resolve returns “Resolver not configured”

It targets:

`if (!mResolverPtr->IsConfigured()) { ErrorUtils::CustomInitialize("Resolver not configured", ...); return ERROR_GENERAL; }`

It sets up `mResolverPtr` (by calling `Configure(shell)` in an environment where `InitializeResolver()` creates the Resolver but does not load any config), or it constructs a test seam where the resolver map is empty.

It asserts `Core::ERROR_GENERAL` and that `resolution` contains “Resolver not configured”.

#### C3. Resolve returns NotSupported when alias is missing

It targets:

`std::string alias = mResolverPtr->ResolveAlias(method); if (alias.empty()) { ErrorUtils::NotSupported(resolution); return ERROR_GENERAL; }`

It loads a config that does not include the method.

It asserts the error code and that the resolution is the NotSupported error JSON string (or at least that it is non-empty and corresponds to NotSupported).

#### C4. Event pre-processing: params must be JSON

It targets:

`if (!params_obj.FromString(params)) { CustomBadRequest("Event methods require parameters", ...); return BAD_REQUEST; }`

It chooses an event method from `AppGateway/resolutions/resolution.base.json`, for example:

`"device.onnamechanged"` with `"event": "Device.onDeviceNameChanged"`

It calls `Resolve(...)` with a non-JSON params string.

It asserts `Core::ERROR_BAD_REQUEST` and that the resolution contains the “Event methods require parameters” message.

#### C5. Event pre-processing: params must include boolean `listen`

It targets:

`if (!ObjectUtils::HasBooleanEntry(params_obj, "listen", resultValue)) { CustomBadRequest("Missing required boolean 'listen' parameter", ...); return BAD_REQUEST; }`

It calls an event method with params `{}`.

It asserts `Core::ERROR_BAD_REQUEST` and that the resolution contains the missing `listen` message.

#### C6. Event subscribe success: listen true/false

It targets `HandleEvent` and subscription via:

`mAppNotifications->Subscribe(ContextUtils::ConvertAppGatewayToNotificationContext(...), listen, alias, event);`

It uses a fake `IAppNotifications` returned by `QueryInterfaceByCallsign(APP_NOTIFICATIONS_CALLSIGN)` and captures the call.

It asserts:

`Resolve(...)` returns `Core::ERROR_NONE` when the fake `Subscribe` returns `Core::ERROR_NONE`.

The `resolution` string is JSON that includes `"listening": true/false` and `"event": <method>` (note: the implementation uses the *method*, not the underlying alias event string).

The `Subscribe` call uses `alias` equal to `"org.rdk.AppGatewayCommon"` and `event` equal to the method key being resolved.

#### C7. Event subscribe fails when AppNotifications is not available

It targets:

If `mService->QueryInterfaceByCallsign<IAppNotifications>` returns null, `HandleEvent` returns `Core::ERROR_GENERAL`.

It asserts that `Resolve(...)` returns `Core::ERROR_GENERAL`.

#### C8. COM-RPC request handler missing returns NotAvailable

This targets:

`requestHandler = QueryInterfaceByCallsign<IAppGatewayRequestHandler>(alias); if (requestHandler == nullptr) { NotAvailable(resolution); }`

It chooses a non-event method that has `"useComRpc": true` in `resolution.base.json`, for example:

`device.name` with alias `org.rdk.AppGatewayCommon`

It sets up the fake shell so that `QueryInterfaceByCallsign<IAppGatewayRequestHandler>("org.rdk.AppGatewayCommon")` returns null.

It asserts `Core::ERROR_GENERAL` and that resolution is NotAvailable.

#### C9. COM-RPC request handler failure sets internal error if resolution is empty

It targets:

If `HandleAppGatewayRequest` returns not OK and `resolution` is empty, it sets:

`ErrorUtils::CustomInternal("HandleAppGatewayRequest failed", resolution);`

It sets up a fake handler that returns an error and does not set `resolution`.

It asserts:

Return is `Core::ERROR_GENERAL`.

Resolution is non-empty and includes “HandleAppGatewayRequest failed”.

#### C10. COM-RPC request handler success and parameter shaping for `_additionalContext`

This targets `UpdateContext(... onlyAdditionalContext=true)` and the final call:

`requestHandler->HandleAppGatewayRequest(context, method, finalParams, resolution)`

To make this test meaningful you should load a resolution entry that includes `"additionalContext"` as an object and (implicitly or explicitly) enables includeContext.

It asserts the fake handler receives a JSON string shaped as:

`{"params": <original params object>, "_additionalContext": {"origin": <origin>, ...}}`

It also asserts that the `origin` passed into `Resolve` is present in `_additionalContext.origin`.

### D. Permission group tests (`permissionGroup` in resolution entries)

`resolution.base.json` includes permission groups for methods such as `device.setName`, `localization.setLocale`, and others.

#### D1. Permission denied when CheckPermissionGroup returns error

It targets:

`if (ERROR_NONE != CheckPermissionGroup(...)) { NotPermitted(resolution); return ERROR_GENERAL; }`

It supplies a fake authenticator that returns a non-zero error.

It asserts `Core::ERROR_GENERAL` and that resolution is NotPermitted.

#### D2. Permission denied when allowed is false

It targets the explicit `if (!allowed) { NotPermitted(...) }` branch.

It supplies a fake authenticator that returns `ERROR_NONE` and sets `allowed=false`.

It asserts `NotPermitted`.

#### D3. Permission allowed when allowed is true

It supplies a fake authenticator returning `allowed=true` and ensures the downstream route succeeds (COM-RPC or event). It asserts `Core::ERROR_NONE`.

Important implementation detail: permission checks are only performed if `SetupAppGatewayAuthenticator()` returns true. If the authenticator cannot be queried, the current code does not fail the request by default. Tests should explicitly document the observed behavior so it does not silently change.

### E. Thunder JSON-RPC invocation tests (`Resolver::CallThunderPlugin`) focusing on validation branches

Full success-path coverage of `CallThunderPlugin` requires controlling `Utils::GetThunderControllerClient(...)`, which is usually done through a link seam or by running in an environment with a real Thunder controller client. L1 unit-style tests can still cover important validation paths.

#### E1. CallThunderPlugin returns GENERAL on empty alias

It targets `if (alias.empty()) return ERROR_GENERAL;`.

It asserts `Core::ERROR_GENERAL`.

#### E2. CallThunderPlugin returns GENERAL when alias contains no dot

It targets `ParseAlias(alias, callsign, pluginMethod)` and then:

`if (pluginMethod.empty()) return ERROR_GENERAL;`

It calls with alias `"org.rdk.AppGatewayCommon"`.

It asserts `Core::ERROR_GENERAL`.

#### E3. CallThunderPlugin returns GENERAL when thunderLink cannot be created

It targets:

`auto thunderLink = Utils::GetThunderControllerClient(...); if (!thunderLink) return ERROR_GENERAL;`

This branch is reachable when the environment cannot create a controller client.

It asserts `Core::ERROR_GENERAL`.

### F. WebSocket responder tests (`AppGatewayResponderImplementation`)

These tests are higher-effort because much behavior is behind lambdas given to the WebSocket manager and behind worker pool jobs. However, the code contains direct logic that can be covered, and the mapping below specifies what should be exercised for coverage.

#### F1. Auth handler denies tokens missing `session=...`

It targets:

`sessionId = Utils::ResolveQuery(token, "session"); if (sessionId.empty()) return false;`

It asserts the auth handler returns false.

#### F2. Auth handler denies when authenticator interface is unavailable

It targets the branch where:

`mService->QueryInterfaceByCallsign<IAppGatewayAuthenticator>(...)` returns null.

It asserts false.

#### F3. Auth handler success stores appId and emits connected notification job

It targets:

On success `Authenticate(sessionId, appId)` returns `ERROR_NONE`, then it adds to `mAppIdRegistry` and submits `ConnectionStatusNotificationJob`.

It asserts the registry contains the connection mapping (this may require a test seam if the registry is private; alternatively assert behavior via subsequent dispatch).

#### F4. DispatchWsMsg closes connection if appId is missing

It targets:

`if (!mAppIdRegistry.Get(connectionId, appId)) { mWsManager.Close(connectionId); }`

It asserts `Close(connectionId)` is called.

#### F5. DispatchWsMsg calls resolver Resolve when appId exists

It targets:

`mResolver->Resolve(context, APP_GATEWAY_CALLSIGN, method, params, resolution)`

It sets up a fake resolver interface returned by `mService->QueryInterface<Exchange::IAppGatewayResolver>()`.

It asserts `Resolve` is called with:

`origin` equal to `APP_GATEWAY_CALLSIGN`

`context.connectionId` and `context.requestId` matching the dispatch inputs

`context.appId` matching the registry mapping.

#### F6. Disconnect handler calls AppNotifications Cleanup if available

It targets:

`QueryInterfaceByCallsign<IAppNotifications>(APP_NOTIFICATIONS_CALLSIGN)` and then `Cleanup(connectionId, APP_GATEWAY_CALLSIGN)`.

It asserts `Cleanup` is called.

#### F7. Register prevents duplicate notifications

It targets:

`std::find(...) == end` check in `Register`.

It asserts registering the same notification twice results in only one stored instance (and therefore only one `AddRef`).

#### F8. Unregister returns GENERAL when notification not found

It targets:

The `else { LOGERR("notification not found"); }` path and returns `Core::ERROR_GENERAL`.

It asserts error code.

#### F9. OnConnectionStatusChanged calls all callbacks

It targets the iteration in `OnConnectionStatusChanged`.

It registers two notification fakes and asserts both are invoked with expected arguments.

## Implementation details that tests must reflect (important for correctness)

### 1. Resolution keys are always lowercased in `Resolver`

Because `LoadConfig` lowercases `it.Label()`, tests must ensure:

They query using any case but expect normalized behavior.

They do not assume case-sensitive method keys.

### 2. Event “method” vs “event” naming

For event entries, `resolution.base.json` stores:

Key like `device.onnamechanged` with `"event": "Device.onDeviceNameChanged"`

However, `PreProcessEvent` uses `returnResult["event"] = method` and `HandleEvent(..., alias, method, ...)` passes `event` equal to the method string, not the `Resolution.event` string.

Tests should assert the behavior as implemented (and not as one might expect logically).

### 3. COM-RPC alias is a callsign, not a callsign.method

For COM-RPC, the base config uses:

`"alias": "org.rdk.AppGatewayCommon"`

`ProcessComRpcRequest` uses `QueryInterfaceByCallsign<IAppGatewayRequestHandler>(alias)` where `alias` must be a callsign string.

For Thunder JSON-RPC invocation, `CallThunderPlugin` expects alias strings that include a method suffix (`callsign.method`). If in the future there are entries that are non-COM-RPC and use Thunder invocation, those entries must use the dotted alias format, or they will fail the `pluginMethod.empty()` validation branch.

### 4. `_additionalContext` wrapping structure

When `UpdateContext(... onlyAdditionalContext=true)` is in effect and additional context is a JSON object, the final params string becomes a JSON object with:

`params`: the parsed original params object (or empty object if parse failed)

`_additionalContext`: the configured additional context object plus an injected `origin` field.

Tests should assert this exact structure because it is a key part of the COM-RPC branch behavior.

## Coverage gaps and risks (derived from current implementation)

### Gap 1: The provided Code_Ref L1Tests suite is minimal

Only the UtilsFile example is present in the reference folder. It does not demonstrate how to fake a Thunder `IShell`, how to implement “callsign interface registry” fakes, or how to validate workerpool job outcomes. AppGateway L1 tests will need helper fakes beyond what Code_Ref shows, even if the overall “functional outcome first” style is preserved.

### Gap 2: Permission enforcement when authenticator is missing is not fail-closed

Permission checks are only executed if `SetupAppGatewayAuthenticator()` succeeds. If the authenticator is unavailable, the current code proceeds without returning NotPermitted. This behavior should be explicitly captured in tests so it does not change unintentionally (and should be reviewed from a security standpoint).

### Gap 3: Hard-coded `/etc/app-gateway` paths make `InitializeResolver()` branch coverage environment-dependent

`InitializeResolver()` reads:

`/etc/app-gateway/resolutions.json` and falls back to `/etc/app-gateway/resolution.base.json`

Unless the L1 environment stages those paths, tests should prefer the override configuration API (`Configure(IStringIterator*)`) and direct `Resolver::LoadConfig` tests using `/tmp` files.

## Sources

This mapping is derived from the following sources:

It uses the reference Code_Ref L1 test `Code_Ref/Tests/L1Tests/tests/test_UtilsFile.cpp` and its identical counterpart in this repository (`Tests/L1Tests/tests/test_UtilsFile.cpp`). The AppGateway behaviors are mapped directly from `AppGateway/AppGateway.cpp`, `AppGateway/AppGatewayImplementation.cpp`, `AppGateway/Resolver.cpp`, and `AppGateway/AppGatewayResponderImplementation.cpp`, and the method classification (event vs COM-RPC vs permission group) is derived from `AppGateway/resolutions/resolution.base.json`.
