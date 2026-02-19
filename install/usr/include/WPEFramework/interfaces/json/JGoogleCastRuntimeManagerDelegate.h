// Generated automatically from 'IGoogleCast.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_GoogleCastRuntimeManagerDelegate.h"
#include <interfaces/IGoogleCast.h>

namespace WPEFramework {

namespace Exchange {

    namespace GoogleCast {

        namespace JRuntimeManagerDelegate {

            namespace Version {

                constexpr uint8_t Major = 1;
                constexpr uint8_t Minor = 0;
                constexpr uint8_t Patch = 0;

            } // namespace Version

            using JSONRPC = PluginHost::JSONRPC;

            PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

            static void Register(JSONRPC& _module_, IGoogleCast::IRuntimeManagerDelegate* _impl_)
            {
                ASSERT(_impl_ != nullptr);

                _module_.RegisterVersion(_T("JRuntimeManagerDelegate"), Version::Major, Version::Minor, Version::Patch);

                // Register methods and properties...

                (void) _impl_;
            }

            static void Unregister(JSONRPC& _module_)
            {
                (void) _module_;
            }

            namespace Event {

                // Event: 'onIntentChanged' - Notifies about GoogleCast intent to launch/close/destroy cast application runtime
                static void OnIntentChanged(const JSONRPC& _module_, const JsonData::GoogleCast::RuntimeManagerDelegate::OnIntentChangedParamsData& params)
                {
                    _module_.Notify(_T("onIntentChanged"), params);
                }

                // Event: 'onIntentChanged' - Notifies about GoogleCast intent to launch/close/destroy cast application runtime
                static void OnIntentChanged(const JSONRPC& _module_, const string& appId, const bool& inactive,
                         const Exchange::IGoogleCast::IRuntimeManagerDelegate::Intent& intent)
                {
                    JsonData::GoogleCast::RuntimeManagerDelegate::OnIntentChangedParamsData _params_;
                    _params_.AppId = appId;
                    _params_.Inactive = inactive;
                    _params_.Intent = intent;

                    OnIntentChanged(_module_, _params_);
                }

            } // namespace Event

            POP_WARNING()

        } // namespace JRuntimeManagerDelegate

    } // namespace GoogleCast

} // namespace Exchange

} // namespace WPEFramework

