// Generated automatically from 'ILifecycleManagerState.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_LifecycleManagerState.h"
#include <interfaces/ILifecycleManagerState.h>

namespace WPEFramework {

namespace Exchange {

    namespace JLifecycleManagerState {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ILifecycleManagerState* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JLifecycleManagerState"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'appReady' - Response api call to appInitializing API
            _module_.Register<JsonData::LifecycleManagerState::AppReadyParamsData, void>(_T("appReady"), 
                [_impl_](const JsonData::LifecycleManagerState::AppReadyParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};

                    _errorCode = _impl_->AppReady(_appId);

                    return (_errorCode);
                });

            // Method: 'stateChangeComplete' - Response api call to appLifecycleStateChanged API
            _module_.Register<JsonData::LifecycleManagerState::StateChangeCompleteParamsData, void>(_T("stateChangeComplete"), 
                [_impl_](const JsonData::LifecycleManagerState::StateChangeCompleteParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const uint32_t _stateChangedId{params.StateChangedId};
                    const bool _success{params.Success};

                    _errorCode = _impl_->StateChangeComplete(_appId, _stateChangedId, _success);

                    return (_errorCode);
                });

            // Method: 'closeApp' - close the app
            _module_.Register<JsonData::LifecycleManagerState::CloseAppParamsData, void>(_T("closeApp"), 
                [_impl_](const JsonData::LifecycleManagerState::CloseAppParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const Exchange::ILifecycleManagerState::AppCloseReason _closeReason{params.CloseReason};

                    _errorCode = _impl_->CloseApp(_appId, _closeReason);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("appReady"));
            _module_.Unregister(_T("stateChangeComplete"));
            _module_.Unregister(_T("closeApp"));
        }

        namespace Event {

            // Event: 'onAppLifecycleStateChanged' - Notifies the new state
            static void OnAppLifecycleStateChanged(const JSONRPC& _module_, const JsonData::LifecycleManagerState::OnAppLifecycleStateChangedParamsData& params)
            {
                _module_.Notify(_T("onAppLifecycleStateChanged"), params);
            }

            // Event: 'onAppLifecycleStateChanged' - Notifies the new state
            static void OnAppLifecycleStateChanged(const JSONRPC& _module_, const Core::JSON::String& appId, const Core::JSON::String& appInstanceId,
                     const Core::JSON::EnumType<Exchange::ILifecycleManager::LifecycleState>& oldLifecycleState,
                     const Core::JSON::EnumType<Exchange::ILifecycleManager::LifecycleState>& newLifecycleState, const Core::JSON::String& navigationIntent)
            {
                JsonData::LifecycleManagerState::OnAppLifecycleStateChangedParamsData _params_;
                _params_.AppId = appId;
                _params_.AppInstanceId = appInstanceId;
                _params_.OldLifecycleState = oldLifecycleState;
                _params_.NewLifecycleState = newLifecycleState;
                _params_.NavigationIntent = navigationIntent;

                OnAppLifecycleStateChanged(_module_, _params_);
            }

            // Event: 'onAppLifecycleStateChanged' - Notifies the new state
            static void OnAppLifecycleStateChanged(const JSONRPC& _module_, const string& appId, const string& appInstanceId,
                     const Exchange::ILifecycleManager::LifecycleState& oldLifecycleState, const Exchange::ILifecycleManager::LifecycleState& newLifecycleState, const string& navigationIntent)
            {
                JsonData::LifecycleManagerState::OnAppLifecycleStateChangedParamsData _params_;
                _params_.AppId = appId;
                _params_.AppInstanceId = appInstanceId;
                _params_.OldLifecycleState = oldLifecycleState;
                _params_.NewLifecycleState = newLifecycleState;
                _params_.NavigationIntent = navigationIntent;

                OnAppLifecycleStateChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JLifecycleManagerState

} // namespace Exchange

} // namespace WPEFramework

