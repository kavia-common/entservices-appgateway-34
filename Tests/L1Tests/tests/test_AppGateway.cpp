/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Module.h"

#include <interfaces/IAppGateway.h>
#include <plugins/IShell.h>

#include "AppGateway.h"

// Reuse the common Thunder IShell mock from entservices-testframework.
#include "ServiceMock.h"

using namespace WPEFramework;

using ::testing::_;
using ::testing::AllOf;
using ::testing::DoAll;
using ::testing::Field;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::SetArgReferee;
using ::testing::StrictMock;

namespace {

// Simple IUnknown-ish base for Exchange interfaces.
// In many Thunder repos, mocks do not strictly model AddRef/Release semantics
// unless the SUT explicitly relies on them. AppGateway::Deinitialize asserts
// the Release result equals Core::ERROR_DESTRUCTION_SUCCEEDED, so we implement
// Release to return that for deterministic tests.
class RefCounted {
public:
    RefCounted() = default;
    virtual ~RefCounted() = default;

    uint32_t AddRef() const
    {
        return Core::ERROR_NONE;
    }
    uint32_t Release() const
    {
        // AppGateway::Deinitialize asserts this exact value.
        return Core::ERROR_DESTRUCTION_SUCCEEDED;
    }
};

// Resolver mock: only the Resolve method is required for these L1 tests.
class AppGatewayResolverMock : public Exchange::IAppGatewayResolver, public RefCounted {
public:
    // Exchange::IAppGatewayResolver
    MOCK_METHOD(uint32_t,
        Resolve,
        (const Exchange::GatewayContext& context,
            const string& origin,
            const string& method,
            const string& params,
            string& result),
        (override));

    // Core::IUnknown
    uint32_t AddRef() const override { return RefCounted::AddRef(); }
    uint32_t Release() const override { return RefCounted::Release(); }

    void* QueryInterface(const uint32_t interfaceId) override
    {
        // We only need to satisfy QueryInterface for IAppGatewayResolver itself.
        if (interfaceId == Exchange::IAppGatewayResolver::ID) {
            return static_cast<Exchange::IAppGatewayResolver*>(this);
        }
        // AppGateway::Initialize optionally queries IConfiguration. Return nullptr
        // so tests don't need to model configuration behavior.
        return nullptr;
    }
};

// Responder mock: only needed for Initialize() to succeed.
// No responder methods are expected to be called by current resolve path.
class AppGatewayResponderMock : public Exchange::IAppGatewayResponder, public RefCounted {
public:
    // Core::IUnknown
    uint32_t AddRef() const override { return RefCounted::AddRef(); }
    uint32_t Release() const override { return RefCounted::Release(); }

    void* QueryInterface(const uint32_t interfaceId) override
    {
        if (interfaceId == Exchange::IAppGatewayResponder::ID) {
            return static_cast<Exchange::IAppGatewayResponder*>(this);
        }
        return nullptr;
    }

    // Exchange::IAppGatewayResponder (minimal set; keep as stubs)
    // Note: exact interface methods can differ across Thunder versions; to avoid
    // hard build breaks, we only implement QueryInterface/AddRef/Release and
    // rely on the fact that AppGateway::Initialize does not call other methods.
};

class AppGatewayL1Test : public ::testing::Test {
public:
    void SetUp() override
    {
        // Ensure deterministic QueryInterface behavior per test plan.
        setenv("APPGATEWAY_L0_DISABLE_COMRPC", "1", 1);

        // Default service expectations.
        // AppGateway::Initialize calls AddRef/Release; keep them permissive.
        ON_CALL(service, AddRef()).WillByDefault(Return());
        ON_CALL(service, Release()).WillByDefault(Return(Core::ERROR_DESTRUCTION_SUCCEEDED));
    }

    void TearDown() override
    {
        // best-effort cleanup if a test failed early after initialization
        if (plugin != nullptr && initialized) {
            plugin->Deinitialize(&service);
        }
        if (dispatcher != nullptr) {
            dispatcher->Release();
            dispatcher = nullptr;
        }
        if (plugin != nullptr) {
            plugin->Release();
            plugin = nullptr;
        }
    }

    void CreatePluginAndDispatcher()
    {
        plugin = Core::Service<Plugin::AppGateway>::Create<PluginHost::IPlugin>();
        ASSERT_NE(plugin, nullptr);

        dispatcher = plugin->QueryInterface<PluginHost::IDispatcher>();
        ASSERT_NE(dispatcher, nullptr);
    }

    std::string ValidRequestJson(const std::string& origin = "org.rdk.AppGateway",
        const std::string& method = "dummy.method",
        const std::string& paramsFragment = "{}",
        bool includeParams = true) const
    {
        // Build JSON deterministically. Note: key presence check in current code
        // requires "requestId", "connectionId", and "appId" appear in the JSON text.
        std::string json = "{";
        json += "\"context\":{\"requestId\":1001,\"connectionId\":10,\"appId\":\"com.example.test\"}";
        if (!origin.empty()) {
            json += ",\"origin\":\"" + origin + "\"";
        }
        if (!method.empty()) {
            json += ",\"method\":\"" + method + "\"";
        }
        if (includeParams) {
            json += ",\"params\":" + paramsFragment;
        }
        json += "}";
        return json;
    }

    void ExpectServiceRoots()
    {
        // AppGateway::Initialize uses service->Root<T>(...) for resolver/responder.
        // Root<T>() internally uses COMLink/QueryInterface patterns; in unit tests
        // we can't intercept template Root<>() directly. Therefore we instead
        // supply the aggregated interfaces through QueryInterfaceByCallsign/QueryInterface
        // in a way compatible with Root() in the Thunder test environment.
        //
        // In practice, existing entservices L1 tests commonly mock QueryInterface
        // and rely on Root's implementation using QueryInterfaceByCallsign or
        // QueryInterface. We add expectations for both to increase compatibility.
        ON_CALL(service, QueryInterface(_)).WillByDefault([this](const uint32_t id) -> void* {
            if (id == Exchange::IAppGatewayResolver::ID) {
                return static_cast<Exchange::IAppGatewayResolver*>(&resolver);
            }
            if (id == Exchange::IAppGatewayResponder::ID) {
                return static_cast<Exchange::IAppGatewayResponder*>(&responder);
            }
            return nullptr;
        });
        ON_CALL(service, QueryInterfaceByCallsign(_, _)).WillByDefault([this](const uint32_t id, const string&) -> void* {
            if (id == Exchange::IAppGatewayResolver::ID) {
                return static_cast<Exchange::IAppGatewayResolver*>(&resolver);
            }
            if (id == Exchange::IAppGatewayResponder::ID) {
                return static_cast<Exchange::IAppGatewayResponder*>(&responder);
            }
            return nullptr;
        });

        // RemoteConnection is used during Deinitialize if an out-of-process connection exists.
        // We can return nullptr (treated as in-process) for L1.
        ON_CALL(service, RemoteConnection(_)).WillByDefault(Return(nullptr));
    }

    void InitializePlugin()
    {
        CreatePluginAndDispatcher();
        ExpectServiceRoots();

        const string init = plugin->Initialize(&service);
        EXPECT_EQ(init, EMPTY_STRING);
        initialized = true;
    }

protected:
    NiceMock<ServiceMock> service;
    StrictMock<AppGatewayResolverMock> resolver;
    NiceMock<AppGatewayResponderMock> responder;

    PluginHost::IPlugin* plugin { nullptr };
    PluginHost::IDispatcher* dispatcher { nullptr };
    bool initialized { false };
};

TEST_F(AppGatewayL1Test, TC_L1_01_InitializeAndResolve_Success)
{
    InitializePlugin();

    const auto ctxMatcher = AllOf(
        Field(&Exchange::GatewayContext::requestId, 1001u),
        Field(&Exchange::GatewayContext::connectionId, 10u),
        Field(&Exchange::GatewayContext::appId, string("com.example.test")));

    EXPECT_CALL(resolver,
        Resolve(ctxMatcher, "org.rdk.AppGateway", "dummy.method", "{}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("null")), Return(Core::ERROR_NONE)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", ValidRequestJson(), response);

    EXPECT_EQ(rc, Core::ERROR_NONE);
    EXPECT_EQ(response, "null");
}

TEST_F(AppGatewayL1Test, TC_L1_02_InitializeIdempotency_DoubleInitialize)
{
    CreatePluginAndDispatcher();
    ExpectServiceRoots();

    EXPECT_EQ(plugin->Initialize(&service), EMPTY_STRING);
    initialized = true;
    EXPECT_EQ(plugin->Initialize(&service), EMPTY_STRING);

    EXPECT_CALL(resolver, Resolve(_, _, _, _, _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("null")), Return(Core::ERROR_NONE)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", ValidRequestJson(), response);
    EXPECT_EQ(rc, Core::ERROR_NONE);
    EXPECT_EQ(response, "null");
}

TEST_F(AppGatewayL1Test, TC_L1_03_DeinitializeUnregistersResolve_UnknownMethod)
{
    InitializePlugin();

    plugin->Deinitialize(&service);
    initialized = false;

    EXPECT_CALL(resolver, Resolve(_, _, _, _, _)).Times(0);

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", ValidRequestJson(), response);

    // In most Thunder builds this is ERROR_UNKNOWN_METHOD after unregister.
    EXPECT_EQ(rc, Core::ERROR_UNKNOWN_METHOD);
}

TEST_F(AppGatewayL1Test, TC_L1_04_DeinitializeIdempotency_DoubleDeinit_NoCrash)
{
    InitializePlugin();

    plugin->Deinitialize(&service);
    initialized = false;

    EXPECT_CALL(resolver, Resolve(_, _, _, _, _)).Times(0);

    // Second deinit should not crash.
    plugin->Deinitialize(&service);

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", ValidRequestJson(), response);
    EXPECT_EQ(rc, Core::ERROR_UNKNOWN_METHOD);
}

TEST_F(AppGatewayL1Test, TC_L1_07_MissingOrigin_BadRequest)
{
    InitializePlugin();

    EXPECT_CALL(resolver, Resolve(_, _, _, _, _)).Times(0);

    string response;
    // omit "origin" by passing empty origin (we will not include it)
    const std::string json = "{\"context\":{\"requestId\":1001,\"connectionId\":10,\"appId\":\"com.example.test\"},\"method\":\"dummy.method\",\"params\":{}}";
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_BAD_REQUEST);
    EXPECT_TRUE(response.empty());
}

TEST_F(AppGatewayL1Test, TC_L1_08_MissingMethod_BadRequest)
{
    InitializePlugin();

    EXPECT_CALL(resolver, Resolve(_, _, _, _, _)).Times(0);

    string response;
    const std::string json = "{\"context\":{\"requestId\":1001,\"connectionId\":10,\"appId\":\"com.example.test\"},\"origin\":\"org.rdk.AppGateway\",\"params\":{}}";
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_BAD_REQUEST);
    EXPECT_TRUE(response.empty());
}

TEST_F(AppGatewayL1Test, TC_L1_09_MissingContextAndRequiredKeys_BadRequest)
{
    InitializePlugin();

    EXPECT_CALL(resolver, Resolve(_, _, _, _, _)).Times(0);

    string response;
    const std::string json = "{\"origin\":\"org.rdk.AppGateway\",\"method\":\"dummy.method\",\"params\":{}}";
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_BAD_REQUEST);
    EXPECT_TRUE(response.empty());
}

TEST_F(AppGatewayL1Test, TC_L1_11_MalformedJson_BadRequest)
{
    InitializePlugin();

    EXPECT_CALL(resolver, Resolve(_, _, _, _, _)).Times(0);

    string response;
    const std::string json =
        "{\"context\":{\"requestId\":1001,\"connectionId\":10,\"appId\":\"com.example.test\"},"
        "\"origin\":\"org.rdk.AppGateway\",\"method\":\"dummy.method\",\"params\":{}";
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_BAD_REQUEST);
    EXPECT_TRUE(response.empty());
}

TEST_F(AppGatewayL1Test, TC_L1_12_EmptyAppId_BadRequest)
{
    InitializePlugin();

    EXPECT_CALL(resolver, Resolve(_, _, _, _, _)).Times(0);

    string response;
    const std::string json =
        "{\"context\":{\"requestId\":1001,\"connectionId\":10,\"appId\":\"\"},"
        "\"origin\":\"org.rdk.AppGateway\",\"method\":\"dummy.method\",\"params\":{}}";
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_BAD_REQUEST);
    EXPECT_TRUE(response.empty());
}

TEST_F(AppGatewayL1Test, TC_L1_13_ParamsOmitted_NormalizesToEmptyObject)
{
    InitializePlugin();

    const auto ctxMatcher = AllOf(
        Field(&Exchange::GatewayContext::requestId, 1001u),
        Field(&Exchange::GatewayContext::connectionId, 10u),
        Field(&Exchange::GatewayContext::appId, string("com.example.test")));

    EXPECT_CALL(resolver,
        Resolve(ctxMatcher, "org.rdk.AppGateway", "dummy.method", "{}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("null")), Return(Core::ERROR_NONE)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve",
        ValidRequestJson("org.rdk.AppGateway", "dummy.method", "{}", false /* includeParams */),
        response);

    EXPECT_EQ(rc, Core::ERROR_NONE);
    EXPECT_EQ(response, "null");
}

TEST_F(AppGatewayL1Test, TC_L1_14_ParamsNull_NormalizesToEmptyObject)
{
    InitializePlugin();

    EXPECT_CALL(resolver, Resolve(_, _, _, "{}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("null")), Return(Core::ERROR_NONE)));

    string response;
    const std::string json =
        "{\"context\":{\"requestId\":1001,\"connectionId\":10,\"appId\":\"com.example.test\"},"
        "\"origin\":\"org.rdk.AppGateway\",\"method\":\"dummy.method\",\"params\":null}";
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_NONE);
    EXPECT_EQ(response, "null");
}

TEST_F(AppGatewayL1Test, TC_L1_16_ParamsEmptyObject_NormalizesToEmptyObject)
{
    InitializePlugin();

    EXPECT_CALL(resolver, Resolve(_, _, _, "{}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("null")), Return(Core::ERROR_NONE)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", ValidRequestJson(), response);

    EXPECT_EQ(rc, Core::ERROR_NONE);
    EXPECT_EQ(response, "null");
}

TEST_F(AppGatewayL1Test, TC_L1_17_ParamsObject_PassesFragment)
{
    InitializePlugin();

    const auto ctxMatcher = AllOf(
        Field(&Exchange::GatewayContext::requestId, 1001u),
        Field(&Exchange::GatewayContext::connectionId, 10u),
        Field(&Exchange::GatewayContext::appId, string("com.example.test")));

    // Use deterministic compact JSON in request.
    const std::string json =
        "{\"context\":{\"requestId\":1001,\"connectionId\":10,\"appId\":\"com.example.test\"},"
        "\"origin\":\"org.rdk.AppGateway\",\"method\":\"dummy.method\",\"params\":{\"a\":1}}";

    EXPECT_CALL(resolver,
        Resolve(ctxMatcher, "org.rdk.AppGateway", "dummy.method", "{\\\"a\\\":1}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("null")), Return(Core::ERROR_NONE)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_NONE);
    EXPECT_EQ(response, "null");
}

TEST_F(AppGatewayL1Test, TC_L1_20_SuccessPayload_ResponseMatches)
{
    InitializePlugin();

    EXPECT_CALL(resolver, Resolve(_, "org.rdk.AppGateway", "dummy.method", "{}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("{\\\"ok\\\":true}")), Return(Core::ERROR_NONE)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", ValidRequestJson(), response);

    EXPECT_EQ(rc, Core::ERROR_NONE);
    EXPECT_EQ(response, "{\\\"ok\\\":true}");
}

TEST_F(AppGatewayL1Test, TC_L1_21_ErrorPropagation_NotSupported)
{
    InitializePlugin();

    const std::string json = ValidRequestJson("org.rdk.AppGateway", "l1.notSupported", "{}", true);

    EXPECT_CALL(resolver, Resolve(_, "org.rdk.AppGateway", "l1.notSupported", "{}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("{\\\"error\\\":\\\"NotSupported\\\"}")),
            Return(Core::ERROR_NOT_SUPPORTED)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_NOT_SUPPORTED);
    EXPECT_EQ(response, "{\\\"error\\\":\\\"NotSupported\\\"}");
}

TEST_F(AppGatewayL1Test, TC_L1_22_ErrorPropagation_Unavailable)
{
    InitializePlugin();

    const std::string json = ValidRequestJson("org.rdk.AppGateway", "l1.notAvailable", "{}", true);

    EXPECT_CALL(resolver, Resolve(_, "org.rdk.AppGateway", "l1.notAvailable", "{}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("{\\\"error\\\":\\\"NotAvailable\\\"}")),
            Return(Core::ERROR_UNAVAILABLE)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_UNAVAILABLE);
    EXPECT_EQ(response, "{\\\"error\\\":\\\"NotAvailable\\\"}");
}

TEST_F(AppGatewayL1Test, TC_L1_23_ErrorPropagation_General)
{
    InitializePlugin();

    const std::string json = ValidRequestJson("org.rdk.AppGateway", "l1.internal", "{}", true);

    EXPECT_CALL(resolver, Resolve(_, "org.rdk.AppGateway", "l1.internal", "{}", _))
        .Times(1)
        .WillOnce(DoAll(SetArgReferee<4>(std::string("{\\\"error\\\":\\\"Internal\\\"}")),
            Return(Core::ERROR_GENERAL)));

    string response;
    const Core::hresult rc = dispatcher->Invoke(nullptr, 0, 0, "", "resolve", json, response);

    EXPECT_EQ(rc, Core::ERROR_GENERAL);
    EXPECT_EQ(response, "{\\\"error\\\":\\\"Internal\\\"}");
}

} // namespace
