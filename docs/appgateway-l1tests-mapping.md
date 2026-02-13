# AppGateway L1Tests Coverage Mapping (from Code_Ref)

## Purpose and scope

This document maps the kinds of L1Tests found in `Code_Ref/Tests/L1Tests/tests` to the AppGateway plugin implementation in `entservices-appgateway-34/AppGateway`. The goal is to maximize coverage by enumerating concrete test cases that exercise the primary success and failure paths in the AppGateway plugin, its Resolver, and its WebSocket responder.

The Code_Ref suite (as provided) illustrates a lightweight, GoogleTest-based approach that directly tests functional outcomes and error paths (for example, verifying filesystem operations and results). The AppGateway plugin needs similar L1 coverage, but because it is a WPEFramework/Thunder plugin, many scenarios require mocks/fakes for `PluginHost::IShell` and interfaces queried by callsign.

## Reference L1Tests pattern (Code_Ref)

The reference L1 test file `Code_Ref/Tests/L1Tests/tests/test_UtilsFile.cpp` demonstrates these L1 characteristics:

The test is small, self-contained, and asserts functional outcomes rather than internal implementation details. It uses minimal setup and verifies end-to-end behavior of the utility under test (create directory, create/write file, move file, verify content). It also contains conditional logic for compatibility (`USE_THUNDER_R4`).

This suggests AppGateway L1 tests should favor functional outcomes such as return codes, returned JSON payloads, and side effects like subscription calls, rather than strict internal state introspection.

## AppGateway components under test

### AppGateway (plugin wrapper)
`AppGateway/AppGateway.cpp` and `AppGateway/AppGateway.h` implement the WPEFramework plugin wrapper that:

It stores `mService`, aggregates `Exchange::IAppGatewayResolver` and `Exchange::IAppGatewayResponder` from out-of-process roots, optionally configures them via `Exchange::IConfiguration`, registers JSON-RPC bindings via `Exchange::JAppGatewayResolver::Register`, and tears everything down in `Deinitialize()`. It also handles remote deactivation via `Deactivated()`.

### AppGatewayImplementation (resolver implementation + request routing)
`AppGateway/AppGatewayImplementation.cpp` implements `AppGatewayImplementation` which:

It initializes a `Resolver` instance, loads resolution configuration based on `RESOLUTIONS_PATH_CFG` and a device country (read from build/vendor JSON), supports `Configure(pathsIterator)` overrides, resolves incoming methods to alias/event/COM-RPC/Thunder-RPC calls, conditionally injects context or additional context, performs permission checks via an authenticator, and delegates event subscription to `IAppNotifications`.

### Resolver (configuration parsing + thunder invocation)
`AppGateway/Resolver.cpp` implements `Resolver` which:

It loads and merges resolution entries from JSON files, stores them keyed by lowercased method, answers queries (`ResolveAlias`, `HasEvent`, `HasIncludeContext`, `HasComRpcRequestSupport`, `HasPermissionGroup`), and invokes a Thunder plugin method by parsing `alias` into `callsign.method` and invoking via a `JSONRPCDirectLink` (via `Utils::GetThunderControllerClient`).

### AppGatewayResponderImplementation (WebSocket server / authentication / dispatch)
`AppGateway/AppGatewayResponderImplementation.cpp` implements the WebSocket-facing responder which:

It configures and starts a WebSocket server, authenticates connection tokens into appIds using an authenticator, tracks connectionId -> appId, dispatches websocket JSON-RPC messages to `IAppGatewayResolver::Resolve`, emits/responds jobs depending on JSON-RPC compliance, performs AppNotifications cleanup on disconnect, and notifies registered connection-status observers.

## Test case mapping (what to test to maximize coverage)

The table below lists recommended L1 test cases, grouped by component. Each entry includes a target code path, key assertions, and known dependencies to mock or fake.

### 1) Plugin wrapper: `Plugin::AppGateway` (Initialize/Deinitialize)

| Test case | Target code path | Setup / mocks needed | Key assertions |
|---|---|---|---|
| Initialize returns error when resolver root cannot be obtained | `AppGateway::Initialize` after `service->Root<Exchange::IAppGatewayResolver>` returns `nullptr` | Fake `IShell` whose `Root<IAppGatewayResolver>` returns null; optionally allow responder root to succeed or fail | Returned string equals `"Could not retrieve the AppGateway interface."`; error log is expected; should still attempt responder root |
| Initialize returns error when responder root cannot be obtained | `AppGateway::Initialize` after resolver ok but responder root null | Fake resolver root non-null; responder root null | Returned string equals `"Could not retrieve the AppGateway interface."` |
| Initialize calls Configure on both roots if they implement `IConfiguration` | `QueryInterface<Exchange::IConfiguration>()` blocks for both resolver and responder | Fake resolver/responder that returns a fake `IConfiguration` | Verify `Configure(service)` called on each; verify `Release()` called |
| Initialize registers JSONRPC binding when resolver exists | `Exchange::JAppGatewayResolver::Register(*this, mAppGateway)` | Resolver root non-null | Verify register is invoked (this typically requires linking/observing registration or using a wrapper seam in test framework) |
| Deinitialize unregisters JSONRPC and releases interfaces | `AppGateway::Deinitialize` | Initialize first with fakes; provide fake remote connection via `service->RemoteConnection(mConnectionId)` | Verify `JAppGatewayResolver::Unregister` invoked; verify `Release()` on responder/resolver; assert destruction succeeded behavior if test framework supports it |
| Deinitialize terminates remote connection when roots existed | `connection->Terminate()` path | Provide fake `RPC::IRemoteConnection` for `RemoteConnection` | Verify `Terminate()` and `Release()` called |
| Deactivated submits DEACTIVATED job when IDs match | `AppGateway::Deactivated` | Fake connection returning same id; provide fake `Core::IWorkerPool` if possible or validate no crash | Verify job submission attempted (may require test harness seam) |

Coverage note: these tests primarily cover `AppGateway.cpp` branches and lifetime management, which otherwise tends to be untested.

### 2) Resolver configuration: `Resolver::LoadConfig` and accessors

These tests are high-value because they do not require a full Thunder runtime. They can be file-based like the Code_Ref `UtilsFile` test, using temporary JSON files.

| Test case | Target code path | Setup | Key assertions |
|---|---|---|---|
| LoadConfig fails on missing file | `Resolver::LoadConfig` `!file.is_open()` | Provide path to non-existent file | Returns `false` |
| LoadConfig fails on invalid JSON | `FromString` failure | Write temp file with invalid JSON | Returns `false` |
| LoadConfig fails when `resolutions` missing | `!config.Resolutions.IsSet()` | Write JSON with `{}` or other top-level keys | Returns `false` |
| LoadConfig loads simple alias-only resolution | variant iteration and `ExtractStringField` | JSON includes one resolution with `alias` and no other fields | Returns `true`; `IsConfigured()` true; `ResolveAlias(method)` returns alias |
| Keys are case-insensitive (lowercased) | `StringUtils::toLower` on label and lookup | Put `"Device.Name"` in JSON; query with `"device.name"` | `ResolveAlias` returns alias |
| `HasEvent` true when event is set | `Resolver::HasEvent` | JSON includes `"event": "X"` | `HasEvent(key)` is true |
| `HasIncludeContext` default is true when `additionalContext` is an object | `hasAdditionalContext` influences default boolean | JSON includes `"additionalContext": {"foo": "bar"}` and no `includeContext` | `HasIncludeContext` returns true and `additionalContext` returned is object |
| `includeContext` explicit false overrides additionalContext default | `ExtractBooleanField` | JSON includes `"additionalContext": {...}, "includeContext": false` | `HasIncludeContext` returns false |
| `useComRpc` default is true when `additionalContext` is an object (current behavior) | `ExtractBooleanField(..., hasAdditionalContext)` | JSON includes `"additionalContext": {...}` and no `useComRpc` | `HasComRpcRequestSupport` returns true |
| LoadConfig overriding behavior | `mResolutions[key]` overwrite | Load file A defining key K alias A; load file B defining key K alias B | `ResolveAlias(K)` returns B after second load |
| ParseAlias splits callsign and method by last dot | `Resolver::ParseAlias` | Call with `"org.rdk.AppGatewayCommon.method"` | Callsign equals `"org.rdk.AppGatewayCommon"` and method equals `"method"` |
| CallThunderPlugin validates alias format | `CallThunderPlugin` alias parsing and empty checks | Call with empty alias; alias without dot; alias with trailing dot | Returns error codes and does not crash |

Coverage note: `CallThunderPlugin` success-path invocation requires mocking `Utils::GetThunderControllerClient(...)` or running against a real Thunder instance. For L1 unit-style coverage, focus on validation failures and optionally introduce a link seam in test framework to inject a fake controller client.

### 3) AppGatewayImplementation: configuration loading and fallback behavior

These tests cover `InitializeResolver()` which decides what config paths to load.

Because `InitializeResolver()` reads fixed paths like `/etc/app-gateway/resolutions.json`, full coverage in L1 tests usually requires one of the following:

Tests run in an environment that can write to `/etc/app-gateway/` (often not acceptable), or the code is compiled with test hooks, or the harness provides a staging filesystem root.

Given we are only mapping tests here, the recommended cases are:

| Test case | Target code path | Setup / mocks | Key assertions |
|---|---|---|---|
| Configure(shell) returns error if Resolver allocation fails | `catch(std::bad_alloc)` | Hard to force naturally; requires allocation fault injection | Returns `Core::ERROR_GENERAL` |
| InitializeResolver falls back when resolutions config missing | `!resolutionConfigFile.is_open()` branch | Ensure `/etc/app-gateway/resolutions.json` not present in test env; provide default base config file or mock `Resolver::LoadConfig` | Calls `InternalResolutionConfigure` with `{DEFAULT_CONFIG_PATH}` and returns success if load succeeded |
| InitializeResolver falls back when resolutions config parse fails | `regionalConfig.FromString(...) == false` branch | Provide invalid JSON at RESOLUTIONS_PATH_CFG (via test filesystem staging) | Loads fallback `{DEFAULT_CONFIG_PATH}` |
| If country empty, uses defaultCountryCode from config | `if (country.empty() && defaultCountryCode.IsSet())` | Provide resolutions.json with `defaultCountryCode`; vendor/build country absent | Verify chosen paths correspond to default country |
| If country unknown, uses last resort fallback | `GetPathsForCountry` returns empty -> set to DEFAULT_CONFIG_PATH | Provide config with regions that do not match country and no default | Load `{DEFAULT_CONFIG_PATH}` |

Gaps/risks: without a filesystem staging strategy, the above tests can be flaky. A coverage-friendly approach is to add test-only override of config path constants, but that requires code changes (not part of this documentation task). In the absence of code changes, tests should focus on the public `Configure(pathsIterator)` method.

### 4) AppGatewayImplementation: `Configure(pathsIterator)` and `InternalResolutionConfigure`

| Test case | Target code path | Setup | Key assertions |
|---|---|---|---|
| Configure(paths) returns BAD_REQUEST on null iterator | `if (paths == nullptr)` | Call with null | Returns `Core::ERROR_BAD_REQUEST` |
| Configure(paths) returns GENERAL when resolver not initialized | `if (mResolverPtr == nullptr)` | Instantiate implementation but do not call `Configure(shell)`; call `Configure(pathsIterator)` | Returns `Core::ERROR_GENERAL` |
| Configure(paths) returns BAD_REQUEST on empty iterator | `if (configPaths.empty())` | Provide iterator whose `Next()` returns false immediately | Returns `Core::ERROR_BAD_REQUEST` |
| InternalResolutionConfigure returns GENERAL if all LoadConfig fail | `!anyConfigLoaded` | Provide iterator with paths that do not exist | Returns `Core::ERROR_GENERAL` |
| InternalResolutionConfigure succeeds if at least one LoadConfig succeeds | mixed path list | Provide two paths, first missing, second valid JSON | Returns `Core::ERROR_NONE` and Resolver configured |
| Override order: later configs take precedence | loop order and Resolver merge | Use two config files defining same method key with different alias | After configure, `Resolve` should use alias from later file |

### 5) AppGatewayImplementation: resolve flow (`Resolve` / `FetchResolvedData`)

These are the most important functional L1 tests for the gateway behavior.

#### 5.1 Preconditions and resolution lookup

| Test case | Target code path | Setup / mocks | Key assertions |
|---|---|---|---|
| Resolve fails when resolver not initialized | `if (mResolverPtr == nullptr)` | Do not call `Configure(shell)` and call `Resolve()` | Returns `Core::ERROR_GENERAL`; resolution contains custom error initialized `"Resolver not initialized"` |
| Resolve fails when resolver not configured | `if (!mResolverPtr->IsConfigured())` | Create resolver but do not load configs | Returns `Core::ERROR_GENERAL`; resolution contains `"Resolver not configured"` |
| Resolve returns NotSupported when no alias found | `alias.empty()` branch | Configured resolver but no mapping for method | Returns `Core::ERROR_GENERAL`; resolution matches NotSupported error format |

#### 5.2 Permission group enforcement

Based on `resolution.base.json`, several methods include `permissionGroup`.

| Test case | Target code path | Setup / mocks | Key assertions |
|---|---|---|---|
| Permission check denies when authenticator not available | `SetupAppGatewayAuthenticator()` returns false | Map a method with permissionGroup; fake `IShell->QueryInterfaceByCallsign` returns null for authenticator | Current code logs but does not explicitly fail just because Setup returns false; test should verify actual observed behavior (likely it proceeds without check). This is a potential security gap (see gaps section). |
| Permission check returns NotPermitted when CheckPermissionGroup fails | `CheckPermissionGroup != ERROR_NONE` | Fake authenticator returning error | Returns `Core::ERROR_GENERAL`, resolution NotPermitted |
| Permission check returns NotPermitted when allowed is false | `if (!allowed)` | Fake authenticator returns allowed=false | Returns `Core::ERROR_GENERAL`, resolution NotPermitted |
| Permission check allows request when allowed is true | allowed=true | Fake authenticator returns allowed=true and downstream handler succeeds | Returns `Core::ERROR_NONE` |

#### 5.3 Event subscription (`HasEvent` and `PreProcessEvent`)

| Test case | Target code path | Setup / mocks | Key assertions |
|---|---|---|---|
| Event call requires params JSON | `params_obj.FromString(params)` false | Call with empty string or invalid JSON | Returns `Core::ERROR_BAD_REQUEST`; resolution contains bad request message |
| Event call requires boolean listen | `HasBooleanEntry(..., "listen", resultValue)` false | Params JSON without listen | Returns `Core::ERROR_BAD_REQUEST`; resolution contains bad request |
| Event listen true calls Subscribe(listen=true) | `HandleEvent` | Fake `IAppNotifications` returned by callsign, record calls | Returns `Core::ERROR_NONE`; resolution JSON includes `"listening": true` and `"event": <method>` |
| Event listen false calls Subscribe(listen=false) | same | same | Similar assertions with listening false |
| HandleEvent fails when IAppNotifications unavailable | `mAppNotifications == nullptr` and query returns null | Fake shell returns null for AppNotifications | Returns `Core::ERROR_GENERAL` |

#### 5.4 COM-RPC request path (`useComRpc`)

Many entries in `resolution.base.json` include `"useComRpc": true`. This triggers `ProcessComRpcRequest`.

| Test case | Target code path | Setup / mocks | Key assertions |
|---|---|---|---|
| COM-RPC handler missing returns NotAvailable | `requestHandler == nullptr` | Fake shell returns null for callsign alias | Returns `Core::ERROR_GENERAL`; resolution NotAvailable |
| COM-RPC handler returns error -> internal error if resolution empty | `HandleAppGatewayRequest != ERROR_NONE` with empty resolution | Fake handler returns error and leaves resolution empty | Returns `Core::ERROR_GENERAL`; resolution has `"HandleAppGatewayRequest failed"` internal error |
| COM-RPC handler success returns OK and uses UpdateContext onlyAdditionalContext=true | success path | Fake handler validates received `finalParams` structure and returns success | Returns `Core::ERROR_NONE`; confirms that `finalParams` contains `_additionalContext` with origin (when configured) |

#### 5.5 Thunder JSON-RPC invocation path (`CallThunderPlugin`)

This covers the non-event and non-COM-RPC path. Full success-path coverage requires a Thunder controller link mock. Still, several L1 tests can cover parameter shaping and error handling around failure.

| Test case | Target code path | Setup / mocks | Key assertions |
|---|---|---|---|
| includeContext=true injects context object | `UpdateContext(... onlyAdditionalContext=false)` | Use resolution entry with includeContext true and no COM-RPC | Confirm outgoing params passed to `CallThunderPlugin` includes `context` object with appId/connectionId/requestId |
| includeContext parse-failure logs but continues | `paramsObj.FromString(params)` false | Provide non-JSON params; includeContext enabled | Ensure it still produces a JSON payload containing context, and does not crash |
| Thunder call failure yields internal error | `CallThunderPlugin result != ERROR_NONE` branch | Fake resolver link or force failure | Returns error and sets resolution to CustomInternal `"Failed with internal error"` |
| Thunder call success but empty response maps to `"null"` | `if (resolution.empty()) resolution = "null";` | Fake CallThunderPlugin to return OK with empty response | resolution equals `"null"` |

### 6) AppGatewayResponderImplementation: WebSocket auth, dispatch, and disconnect

These tests depend on `WebSocketConnectionManager` behavior and job scheduling. For L1, focus on directly testing the lambda handlers and the dispatch method `DispatchWsMsg()` (it is a member function and can be invoked directly if accessible in test compilation unit, or by making a friend in test build). This section maps required cases even if harness work is needed.

| Test case | Target code path | Setup / mocks | Key assertions |
|---|---|---|---|
| Auth fails when session query missing | `ResolveQuery(token,"session")` empty | Invoke auth handler with token not containing session | Returns false; authenticator not queried |
| Auth fails when authenticator interface not available | query callsign returns null | Fake shell QueryInterfaceByCallsign returns null | Returns false |
| Auth succeeds registers appId and compliant JSON-RPC state | `Authenticate` OK | Fake authenticator returns appId; token includes session | Returns true; registry contains (connectionId->appId) and compliance updated |
| DispatchWsMsg closes connection when appId missing | `!mAppIdRegistry.Get` branch | No appId for connection | Verify `mWsManager.Close(connectionId)` called |
| DispatchWsMsg resolves when appId present | `mResolver->Resolve(...)` | Populate registry with appId; fake `mResolver` interface | Verify `Resolve` invoked with origin `APP_GATEWAY_CALLSIGN` and passed method/params |
| Disconnect triggers AppNotifications Cleanup | disconnect handler | Fake AppNotifications `Cleanup` expected call | Verify cleanup called with connectionId and `APP_GATEWAY_CALLSIGN` |
| Register prevents duplicate callbacks | `Register` checks for duplicates | Register same notification twice | Callback list size remains 1 and AddRef called once |
| Unregister fails when notification not found | `notification not found` | Call Unregister without prior Register | Returns `Core::ERROR_GENERAL` |
| OnConnectionStatusChanged calls all callbacks | iterates and calls `OnAppConnectionChanged` | Register multiple fakes | Verify each called with correct args |

## Coverage gaps and risks identified

### Gap 1: Code_Ref L1Tests suite is minimal in provided reference
Only `test_UtilsFile.cpp` is present in the reference path provided. This means there is no direct reference coverage for plugin-level mocking patterns (IShell fakes, interface-by-callsign fakes, workerpool/job assertions). The AppGateway L1 tests will likely need additional testframework utilities beyond what Code_Ref demonstrates.

### Gap 2: Permission enforcement behavior if authenticator missing
In `FetchResolvedData`, permission checking is guarded by `if (SetupAppGatewayAuthenticator()) { ... }`. If the authenticator cannot be obtained, the request proceeds without permission enforcement. This is likely a security gap. At minimum, L1 tests should document and lock down the expected behavior (deny-by-default is typically preferred).

### Gap 3: Hard-coded filesystem paths reduce testability
`InitializeResolver()` reads fixed file paths (`/etc/app-gateway/resolutions.json`, `/etc/app-gateway/resolution.base.json`). Without filesystem staging or build-time overrides, L1 tests cannot reliably exercise all config branches. Tests should instead prioritize `Configure(pathsIterator)` and `Resolver::LoadConfig` which can use temp files.

### Gap 4: Worker pool/job execution is difficult to assert in unit-style tests
Several paths submit jobs (`RespondJob`, `WsMsgJob`, `EmitJob`, connection status notifications). For L1, aim to cover branches and ensure no crashes. Deeper validation of job execution may require integration tests or a controllable worker pool in the test framework.

## Recommended minimal “high coverage” test set

If time is limited, the following subset will yield the most coverage quickly:

1. `Resolver::LoadConfig` success and failure variants (missing file, bad JSON, missing resolutions, override merge).
2. `AppGatewayImplementation::Configure(pathsIterator)` validation cases (null iterator, empty iterator, at-least-one-valid-path).
3. `FetchResolvedData` primary error paths (resolver null, not configured, alias missing).
4. Event flow with listen true/false and missing listen parameter (ensures `PreProcessEvent` and `HandleEvent` coverage).
5. COM-RPC handler missing vs success (covers `ProcessComRpcRequest` branches).
6. Plugin wrapper `AppGateway::Initialize` failure cases (resolver root null, responder root null).

## Sources

The mapping above is derived from these repository sources:

It uses the Code_Ref L1Tests example file and the current AppGateway plugin implementation files, plus the shipped base resolution configuration JSON which dictates important routing behaviors (event vs COM-RPC vs permission group).
