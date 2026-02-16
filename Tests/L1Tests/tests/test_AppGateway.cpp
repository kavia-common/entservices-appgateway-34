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

#include <gtest/gtest.h>

#include <fstream>
#include <string>

#include "Module.h"

#include "Resolver.h"

using namespace WPEFramework;
using namespace WPEFramework::Plugin;

namespace {

static constexpr const char* kTmpMissing = "/tmp/appgw_resolver_missing.json";
static constexpr const char* kTmpInvalid = "/tmp/appgw_resolver_invalid.json";
static constexpr const char* kTmpNoResolutions = "/tmp/appgw_resolver_no_resolutions.json";
static constexpr const char* kTmpCfg1 = "/tmp/appgw_resolver_cfg1.json";
static constexpr const char* kTmpCfg2 = "/tmp/appgw_resolver_cfg2.json";

static void WriteTextFile(const std::string& path, const std::string& contents)
{
    std::ofstream out(path, std::ios::out | std::ios::trunc);
    ASSERT_TRUE(out.is_open()) << "Failed to open " << path << " for writing";
    out << contents;
    out.close();
}

} // namespace

/**
 * Resolver-focused tests.
 *
 * These tests are intentionally independent of Thunder PluginHost runtime and
 * external mock headers (ServiceMock, etc.). This makes them robust for this
 * repo snapshot and still yields meaningful coverage for resolver/config logic.
 */

TEST(AppGatewayResolverTest, Resolver_LoadConfig_MissingFile_ReturnsFalse)
{
    // Note: Passing nullptr shell is safe for LoadConfig/ResolveAlias/etc. as long as we
    // don't call CallThunderPlugin which requires a shell.
    Resolver resolver(nullptr);

    EXPECT_FALSE(resolver.LoadConfig(kTmpMissing));
    EXPECT_FALSE(resolver.IsConfigured());
}

TEST(AppGatewayResolverTest, Resolver_LoadConfig_InvalidJson_ReturnsFalse)
{
    Resolver resolver(nullptr);

    WriteTextFile(kTmpInvalid, "{ invalid json :::");
    EXPECT_FALSE(resolver.LoadConfig(kTmpInvalid));
    EXPECT_FALSE(resolver.IsConfigured());
}

TEST(AppGatewayResolverTest, Resolver_LoadConfig_MissingResolutionsObject_ReturnsFalse)
{
    Resolver resolver(nullptr);

    WriteTextFile(kTmpNoResolutions, R"json(
        { "notResolutions": { "a": { "alias": "x" } } }
    )json");
    EXPECT_FALSE(resolver.LoadConfig(kTmpNoResolutions));
    EXPECT_FALSE(resolver.IsConfigured());
}

TEST(AppGatewayResolverTest, Resolver_LoadConfig_LowercasesKeysAndOverrides)
{
    Resolver resolver(nullptr);

    // First config sets MixedKey -> alias1
    WriteTextFile(kTmpCfg1, R"json(
        {
          "resolutions": {
            "MiXeDKey": {
              "alias": "org.rdk.First.method"
            }
          }
        }
    )json");
    ASSERT_TRUE(resolver.LoadConfig(kTmpCfg1));
    EXPECT_TRUE(resolver.IsConfigured());

    // Resolver lowercases lookup key
    EXPECT_EQ(resolver.ResolveAlias("mixedkey"), "org.rdk.First.method");
    EXPECT_EQ(resolver.ResolveAlias("MiXeDKey"), "org.rdk.First.method");

    // Second config overrides same key (case-insensitive) -> alias2
    WriteTextFile(kTmpCfg2, R"json(
        {
          "resolutions": {
            "mixedKEY": {
              "alias": "org.rdk.Second.method"
            }
          }
        }
    )json");
    ASSERT_TRUE(resolver.LoadConfig(kTmpCfg2));
    EXPECT_TRUE(resolver.IsConfigured());

    EXPECT_EQ(resolver.ResolveAlias("mixedkey"), "org.rdk.Second.method");
}

TEST(AppGatewayResolverTest, Resolver_LoadConfig_EventAndComRpcFlags_AndIncludeContextDefaults)
{
    Resolver resolver(nullptr);

    // This config hits:
    // - HasEvent: event string non-empty
    // - HasComRpcRequestSupport explicit true
    // - additionalContext object -> default includeContext/useComRpc should become true
    const char* cfg = "/tmp/appgw_resolver_flags.json";
    WriteTextFile(cfg, R"json(
        {
          "resolutions": {
            "event.method": {
              "alias": "org.rdk.SomePlugin.someMethod",
              "event": "non-empty"
            },
            "comrpc.explicit": {
              "alias": "org.rdk.SomeComRpcHandler",
              "useComRpc": true
            },
            "comrpc.derived": {
              "alias": "org.rdk.SomeComRpcHandler",
              "additionalContext": { "foo": "bar" }
            }
          }
        }
    )json");

    ASSERT_TRUE(resolver.LoadConfig(cfg));
    EXPECT_TRUE(resolver.IsConfigured());

    EXPECT_TRUE(resolver.HasEvent("event.method"));
    EXPECT_FALSE(resolver.HasEvent("comrpc.explicit"));

    EXPECT_TRUE(resolver.HasComRpcRequestSupport("comrpc.explicit"));

    // For the additionalContext object case:
    // Resolver::LoadConfig sets:
    //   bool hasAdditionalContext = additionalContext is OBJECT;
    //   includeContext = ExtractBooleanField(..., default=hasAdditionalContext)
    //   useComRpc      = ExtractBooleanField(..., default=hasAdditionalContext)
    EXPECT_TRUE(resolver.HasComRpcRequestSupport("comrpc.derived"));

    // Also sanity: resolving by different case
    EXPECT_TRUE(resolver.HasComRpcRequestSupport("COMRPC.DERIVED"));
}
