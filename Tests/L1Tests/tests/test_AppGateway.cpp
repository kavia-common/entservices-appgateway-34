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

#include <cstdio>
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
static constexpr const char* kTmpFlags = "/tmp/appgw_resolver_flags.json";
static constexpr const char* kTmpExtra = "/tmp/appgw_resolver_extra.json";

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
 * repository and still yields meaningful coverage for resolver/config logic.
 */

TEST(AppGatewayResolverTest, Resolver_LoadConfig_MissingFile_ReturnsFalse)
{
    // Ensure the file does not exist.
    std::remove(kTmpMissing);

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
    WriteTextFile(kTmpFlags, R"json(
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

    ASSERT_TRUE(resolver.LoadConfig(kTmpFlags));
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

TEST(AppGatewayResolverTest, Resolver_HasIncludeContext_PopulatesAdditionalContext)
{
    Resolver resolver(nullptr);

    // Covers:
    // - ExtractAdditionalContext + hasAdditionalContext detection
    // - includeContext defaulting to true when additionalContext is OBJECT
    // - HasIncludeContext returning includeContext and copying additionalContext back to caller
    WriteTextFile(kTmpExtra, R"json(
        {
          "resolutions": {
            "ctx.defaulttrue": {
              "alias": "org.rdk.SomeComRpcHandler",
              "additionalContext": { "k": "v" }
            },
            "ctx.explicitfalse": {
              "alias": "org.rdk.SomeComRpcHandler",
              "includeContext": false,
              "additionalContext": { "k": "v2" }
            }
          }
        }
    )json");

    ASSERT_TRUE(resolver.LoadConfig(kTmpExtra));
    EXPECT_TRUE(resolver.IsConfigured());

    {
        JsonValue additional;
        EXPECT_TRUE(resolver.HasIncludeContext("ctx.defaulttrue", additional));
        EXPECT_TRUE(additional.IsSet());
        EXPECT_EQ(additional.Content(), Core::JSON::Variant::type::OBJECT);
    }

    {
        JsonValue additional;
        EXPECT_FALSE(resolver.HasIncludeContext("ctx.explicitfalse", additional));
        EXPECT_TRUE(additional.IsSet());
        EXPECT_EQ(additional.Content(), Core::JSON::Variant::type::OBJECT);
    }

    {
        JsonValue additional;
        EXPECT_FALSE(resolver.HasIncludeContext("no.such.key", additional));
        EXPECT_FALSE(additional.IsSet());
    }
}

TEST(AppGatewayResolverTest, Resolver_HasPermissionGroup_ReturnsGroup)
{
    Resolver resolver(nullptr);

    WriteTextFile(kTmpExtra, R"json(
        {
          "resolutions": {
            "perm.method": {
              "alias": "org.rdk.SomePlugin.someMethod",
              "permissionGroup": "pg.test"
            },
            "perm.empty": {
              "alias": "org.rdk.SomePlugin.someMethod",
              "permissionGroup": ""
            }
          }
        }
    )json");

    ASSERT_TRUE(resolver.LoadConfig(kTmpExtra));
    EXPECT_TRUE(resolver.IsConfigured());

    std::string group;
    EXPECT_TRUE(resolver.HasPermissionGroup("perm.method", group));
    EXPECT_EQ(group, "pg.test");

    group.clear();
    EXPECT_FALSE(resolver.HasPermissionGroup("perm.empty", group));

    group.clear();
    EXPECT_FALSE(resolver.HasPermissionGroup("perm.missing", group));
}

TEST(AppGatewayResolverTest, Resolver_ClearResolutions_ClearsConfiguredState)
{
    Resolver resolver(nullptr);

    WriteTextFile(kTmpCfg1, R"json(
        {
          "resolutions": {
            "a": { "alias": "org.rdk.One.method" }
          }
        }
    )json");
    ASSERT_TRUE(resolver.LoadConfig(kTmpCfg1));
    EXPECT_TRUE(resolver.IsConfigured());

    resolver.ClearResolutions();
    EXPECT_FALSE(resolver.IsConfigured());
    EXPECT_EQ(resolver.ResolveAlias("a"), "");
    EXPECT_FALSE(resolver.HasEvent("a"));
}

TEST(AppGatewayResolverTest, Resolver_CallThunderPlugin_NullShell_ReturnsError)
{
    Resolver resolver(nullptr);

    std::string response;
    EXPECT_EQ(resolver.CallThunderPlugin("org.rdk.SomePlugin.someMethod", "{}", response), Core::ERROR_GENERAL);
}
