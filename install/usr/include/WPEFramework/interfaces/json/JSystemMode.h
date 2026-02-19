// Generated automatically from 'ISystemMode.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_SystemMode.h"
#include <interfaces/ISystemMode.h>

namespace WPEFramework {

namespace Exchange {

    namespace JSystemMode {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ISystemMode* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JSystemMode"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'requestState' - Requests a new system mode state in the device
            _module_.Register<JsonData::SystemMode::RequestStateParamsData, void>(_T("requestState"), 
                [_impl_](const JsonData::SystemMode::RequestStateParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISystemMode::SystemMode _systemMode{params.SystemMode};
                    const Exchange::ISystemMode::State _state{params.State};

                    _errorCode = _impl_->RequestState(_systemMode, _state);

                    return (_errorCode);
                });

            // Method: 'getState' - Gets the current state for a given system property
            _module_.Register<JsonData::SystemMode::GetStateParamsData, JsonData::SystemMode::GetStateResultData>(_T("getState"), 
                [_impl_](const JsonData::SystemMode::GetStateParamsData& params, JsonData::SystemMode::GetStateResultData& getStateResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISystemMode::SystemMode _systemMode{params.SystemMode};
                    Exchange::ISystemMode::GetStateResult _getStateResult{};

                    _errorCode = _impl_->GetState(_systemMode, _getStateResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        getStateResult = _getStateResult;
                    }

                    return (_errorCode);
                });

            // Method: 'clientActivated' - To put client plugin entry in map
            _module_.Register<JsonData::SystemMode::ClientActivatedParamsInfo, void>(_T("clientActivated"), 
                [_impl_](const JsonData::SystemMode::ClientActivatedParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _callsign{params.Callsign};
                    const string _systemMode{params.SystemMode};

                    _errorCode = _impl_->ClientActivated(_callsign, _systemMode);

                    return (_errorCode);
                });

            // Method: 'clientDeactivated' - To put client plugin entry in map
            _module_.Register<JsonData::SystemMode::ClientActivatedParamsInfo, void>(_T("clientDeactivated"), 
                [_impl_](const JsonData::SystemMode::ClientActivatedParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _callsign{params.Callsign};
                    const string _systemMode{params.SystemMode};

                    _errorCode = _impl_->ClientDeactivated(_callsign, _systemMode);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("requestState"));
            _module_.Unregister(_T("getState"));
            _module_.Unregister(_T("clientActivated"));
            _module_.Unregister(_T("clientDeactivated"));
        }

        POP_WARNING()

    } // namespace JSystemMode

} // namespace Exchange

} // namespace WPEFramework

