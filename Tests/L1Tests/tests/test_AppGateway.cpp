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

#include "Module.h"

// NOTE:
// This file intentionally focuses on "L1 scaffolding" and resolver-driven branches that
// do not require the full Thunder ServiceMock stack. The mapping document recommends
// many AppGatewayImplementation tests that require QueryInterfaceByCallsign-based mocks;
// those can be added once entservices-testframework is available in the workspace.
//
// These tests still align with the L1 style:
// - Use /tmp for config files, deterministic inputs.
// - Validate return values and observable behavior.

#include "Resolver.h"
#include <fstream>

using namespace WPEFramework;

namespace {
static const char* kTmpValidConfigPath = "/tmp/appgateway_resolver_l1_valid.json";
static const char* kTmpInvalidJsonPath = "/tmp/appgateway_resolver_l1_invalid.json";
static const char* kTmpNoResolutionsPath = "/tmp/appgateway_resolver_l1_no_resolutions.json";
static const char* kTmpOverrideConfigPath1 = "/tmp/appgateway_resolver_l1_override1.json";
static const char* kTmpOverrideConfigPath2 = "/tmp/appgateway_resolver_l1_override2.json";

static void WriteTextFile(const std::string& path, const std::string& content)
{
    std::ofstream out(path, std::ios::out | std::ios::trunc);
    ASSERT_TRUE(out.is_open());
    out << content;
    out.close();
}
} // namespace

TEST(AppGatewayResolverTest, LoadConfig_MissingFile_ReturnsFalseAndNotConfigured)
{
    Plugin::Resolver resolver(nullptr);

    EXPECT_FALSE(resolver.IsConfigured());
    EXPECT_FALSE(resolver.LoadConfig("/tmp/this_file_should_not_exist_appgateway_l1.json"));
    EXPECT_FALSE(resolver.IsConfigured());
}

TEST(AppGatewayResolverTest, LoadConfig_InvalidJson_ReturnsFalse)
{
    Plugin::Resolver resolver(nullptr);

    WriteTextFile(kTmpInvalidJsonPath, "{not-valid-json");

    EXPECT_FALSE(resolver.LoadConfig(kTmpInvalidJsonPath));
    EXPECT_FALSE(resolver.IsConfigured());
}

TEST(AppGatewayResolverTest, LoadConfig_MissingResolutionsObject_ReturnsFalse)
{
    Plugin::Resolver resolver(nullptr);

    WriteTextFile(kTmpNoResolutionsPath, R"json(
        { "notResolutions": { "some.key": { "alias": "org.rdk.Dummy.method" } } }
    )json");

    EXPECT_FALSE(resolver.LoadConfig(kTmpNoResolutionsPath));
    EXPECT_FALSE(resolver.IsConfigured());
}

TEST(AppGatewayResolverTest, LoadConfig_LowercasesKeys_AndResolveAliasIsCaseInsensitive)
{
    Plugin::Resolver resolver(nullptr);

    WriteTextFile(kTmpValidConfigPath, R"json(
        {
          "resolutions": {
            "MiXeD.CaSe.Method": { "alias": "org.rdk.SomePlugin.someMethod" }
          }
        }
    )json");

    EXPECT_TRUE(resolver.LoadConfig(kTmpValidConfigPath));
    EXPECT_TRUE(resolver.IsConfigured());

    // ResolveAlias lowercases the input key before lookup, so any casing should work.
    EXPECT_EQ(std::string("org.rdk.SomePlugin.someMethod"), resolver.ResolveAlias("mixed.case.method"));
    EXPECT_EQ(std::string("org.rdk.SomePlugin.someMethod"), resolver.ResolveAlias("MiXeD.CaSe.MeThOd"));
}

TEST(AppGatewayResolverTest, LoadConfig_OverridesExistingEntries_LastWins)
{
    Plugin::Resolver resolver(nullptr);

    WriteTextFile(kTmpOverrideConfigPath1, R"json(
        {
          "resolutions": {
            "test.method": { "alias": "org.rdk.First.first" }
          }
        }
    )json");

    WriteTextFile(kTmpOverrideConfigPath2, R"json(
        {
          "resolutions": {
            "test.method": { "alias": "org.rdk.Second.second" }
          }
        }
    )json");

    EXPECT_TRUE(resolver.LoadConfig(kTmpOverrideConfigPath1));
    EXPECT_EQ(std::string("org.rdk.First.first"), resolver.ResolveAlias("test.method"));

    // Loading a second config containing the same key should override.
    EXPECT_TRUE(resolver.LoadConfig(kTmpOverrideConfigPath2));
    EXPECT_EQ(std::string("org.rdk.Second.second"), resolver.ResolveAlias("test.method"));
}

TEST(AppGatewayResolverTest, HasEvent_ReturnsTrueOnlyWhenEventFieldNonEmpty)
{
    Plugin::Resolver resolver(nullptr);

    WriteTextFile(kTmpValidConfigPath, R"json(
        {
          "resolutions": {
            "event.method": { "alias": "org.rdk.Dummy.method", "event": "someEventName" },
            "noevent.method": { "alias": "org.rdk.Dummy.method2" }
          }
        }
    )json");

    EXPECT_TRUE(resolver.LoadConfig(kTmpValidConfigPath));

    EXPECT_TRUE(resolver.HasEvent("event.method"));
    EXPECT_FALSE(resolver.HasEvent("noevent.method"));
    EXPECT_FALSE(resolver.HasEvent("unknown.method"));
}

TEST(AppGatewayResolverTest, HasComRpcRequestSupport_DefaultsToTrueWhenAdditionalContextPresent)
{
    Plugin::Resolver resolver(nullptr);

    // In Resolver::LoadConfig:
    // - additionalContext is extracted via ExtractAdditionalContext (Variant).
    // - if additionalContext is OBJECT, hasAdditionalContext==true.
    // - includeContext defaults to hasAdditionalContext unless overridden.
    // - useComRpc defaults to hasAdditionalContext unless overridden.
    //
    // So: additionalContext object without explicit useComRpc should yield HasComRpcRequestSupport == true.
    WriteTextFile(kTmpValidConfigPath, R"json(
        {
          "resolutions": {
            "comrpc.method": {
              "alias": "org.rdk.SomeHandler",
              "additionalContext": { "foo": "bar" }
            },
            "explicitfalse.method": {
              "alias": "org.rdk.SomeHandler2",
              "additionalContext": { "x": 1 },
              "useComRpc": false
            }
          }
        }
    )json");

    EXPECT_TRUE(resolver.LoadConfig(kTmpValidConfigPath));

    EXPECT_TRUE(resolver.HasComRpcRequestSupport("comrpc.method"));
    EXPECT_FALSE(resolver.HasComRpcRequestSupport("explicitfalse.method"));
    EXPECT_FALSE(resolver.HasComRpcRequestSupport("unknown.method"));
}

TEST(AppGatewayResolverTest, HasIncludeContext_DefaultsToTrueWhenAdditionalContextPresent_AndReturnsAdditionalContext)
{
    Plugin::Resolver resolver(nullptr);

    WriteTextFile(kTmpValidConfigPath, R"json(
        {
          "resolutions": {
            "ctx.method": {
              "alias": "org.rdk.SomeHandler",
              "additionalContext": { "alpha": "beta", "num": 3 }
            },
            "ctx.disabled": {
              "alias": "org.rdk.SomeHandler",
              "additionalContext": { "a": 1 },
              "includeContext": false
            }
          }
        }
    )json");

    EXPECT_TRUE(resolver.LoadConfig(kTmpValidConfigPath));

    JsonValue additionalContext;
    EXPECT_TRUE(resolver.HasIncludeContext("ctx.method", additionalContext));
    EXPECT_TRUE(additionalContext.IsSet());

    // The underlying JSON value type should be OBJECT in this case.
    EXPECT_EQ(WPEFramework::Core::JSON::Variant::type::OBJECT, additionalContext.Content());

    JsonValue disabledContext;
    EXPECT_FALSE(resolver.HasIncludeContext("ctx.disabled", disabledContext));
    EXPECT_TRUE(disabledContext.IsSet()); // still set (resolver copies if present), but includeContext disabled.
    EXPECT_EQ(WPEFramework::Core::JSON::Variant::type::OBJECT, disabledContext.Content());

    JsonValue unknownContext;
    EXPECT_FALSE(resolver.HasIncludeContext("unknown.method", unknownContext));
}

TEST(AppGatewayResolverTest, HasPermissionGroup_ReturnsTrueAndOutputsGroup)
{
    Plugin::Resolver resolver(nullptr);

    WriteTextFile(kTmpValidConfigPath, R"json(
        {
          "resolutions": {
            "perm.method": {
              "alias": "org.rdk.SomeHandler",
              "permissionGroup": "some.permission.group"
            },
            "noperm.method": {
              "alias": "org.rdk.SomeHandler2"
            }
          }
        }
    )json");

    EXPECT_TRUE(resolver.LoadConfig(kTmpValidConfigPath));

    std::string permissionGroup;
    EXPECT_TRUE(resolver.HasPermissionGroup("perm.method", permissionGroup));
    EXPECT_EQ(std::string("some.permission.group"), permissionGroup);

    std::string permissionGroup2;
    EXPECT_FALSE(resolver.HasPermissionGroup("noperm.method", permissionGroup2));
    EXPECT_TRUE(permissionGroup2.empty());
}
