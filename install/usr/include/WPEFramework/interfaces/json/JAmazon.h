// Generated automatically from 'IAmazonPrime.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_Amazon.h"
#include <interfaces/IAmazonPrime.h>

namespace WPEFramework {

namespace Exchange {

    namespace JAmazon {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IAmazon* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JAmazon"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setDeepLink' - Set the deeplink command for amazon prime
            _module_.Register<JsonData::Amazon::SetDeepLinkParamsInfo, void>(_T("setDeepLink"), 
                [_impl_](const JsonData::Amazon::SetDeepLinkParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _command{params.Command};

                    _errorCode = _impl_->SetDeepLink(_command);

                    return (_errorCode);
                });

            // Method: 'personalInfoRequest' - Request for personal access token to amazon prime app
            _module_.Register<void, void>(_T("personalInfoRequest"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->PersonalInfoRequest();

                    return (_errorCode);
                });

            // Method: 'factoryResetRequest' - Factory reset amazon prime app data
            _module_.Register<void, void>(_T("factoryResetRequest"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->FactoryResetRequest();

                    return (_errorCode);
                });

            // Method: 'SetLaunchReason' - Set launch reason for amazon prime app
            _module_.Register<JsonData::Amazon::SetDeepLinkParamsInfo, void>(_T("SetLaunchReason"), 
                [_impl_](const JsonData::Amazon::SetDeepLinkParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _command{params.Command};

                    _errorCode = _impl_->SetLaunchReason(_command);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setDeepLink"));
            _module_.Unregister(_T("personalInfoRequest"));
            _module_.Unregister(_T("factoryResetRequest"));
            _module_.Unregister(_T("SetLaunchReason"));
        }

        namespace Event {

            // Event: 'StateChange' - Triggered whenever the App state changes
            static void StateChange(const JSONRPC& _module_, const JsonData::Amazon::StateChangeParamsData& params)
            {
                _module_.Notify(_T("StateChange"), params);
            }

            // Event: 'StateChange' - Triggered whenever the App state changes
            static void StateChange(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::IAmazon::State>& state)
            {
                JsonData::Amazon::StateChangeParamsData _params_;
                _params_.State = state;

                StateChange(_module_, _params_);
            }

            // Event: 'StateChange' - Triggered whenever the App state changes
            static void StateChange(const JSONRPC& _module_, const Exchange::IAmazon::State& state)
            {
                JsonData::Amazon::StateChangeParamsData _params_;
                _params_.State = state;

                StateChange(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JAmazon

} // namespace Exchange

} // namespace WPEFramework

