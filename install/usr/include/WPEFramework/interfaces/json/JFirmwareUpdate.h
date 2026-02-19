// Generated automatically from 'IFirmwareUpdate.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_FirmwareUpdate.h"
#include <interfaces/IFirmwareUpdate.h>

namespace WPEFramework {

namespace Exchange {

    namespace JFirmwareUpdate {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IFirmwareUpdate* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JFirmwareUpdate"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'updateFirmware' - Initiates a firmware update
            _module_.Register<JsonData::FirmwareUpdate::UpdateFirmwareParamsData, JsonData::FirmwareUpdate::ResultInfo>(_T("updateFirmware"), 
                [_impl_](const JsonData::FirmwareUpdate::UpdateFirmwareParamsData& params, JsonData::FirmwareUpdate::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _firmwareFilepath{params.FirmwareFilepath};
                    const string _firmwareType{params.FirmwareType};
                    Exchange::IFirmwareUpdate::Result _result{};

                    _errorCode = _impl_->UpdateFirmware(_firmwareFilepath, _firmwareType, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'getUpdateState' - Firmware update consists of 2 major steps: 1
            _module_.Register<void, JsonData::FirmwareUpdate::GetUpdateStateResultInfo>(_T("getUpdateState"), 
                [_impl_](JsonData::FirmwareUpdate::GetUpdateStateResultInfo& getUpdateStateResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IFirmwareUpdate::GetUpdateStateResult _getUpdateStateResult{};

                    _errorCode = _impl_->GetUpdateState(_getUpdateStateResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        getUpdateStateResult = _getUpdateStateResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setAutoReboot' - Enable or disable the AutoReboot feature
            _module_.Register<JsonData::FirmwareUpdate::SetAutoRebootParamsData, JsonData::FirmwareUpdate::ResultInfo>(_T("setAutoReboot"), 
                [_impl_](const JsonData::FirmwareUpdate::SetAutoRebootParamsData& params, JsonData::FirmwareUpdate::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enable{params.Enable};
                    Exchange::IFirmwareUpdate::Result _result{};

                    _errorCode = _impl_->SetAutoReboot(_enable, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("updateFirmware"));
            _module_.Unregister(_T("getUpdateState"));
            _module_.Unregister(_T("setAutoReboot"));
        }

        namespace Event {

            // Event: 'onUpdateStateChange' - notify Firmware update state change
            static void OnUpdateStateChange(const JSONRPC& _module_, const JsonData::FirmwareUpdate::GetUpdateStateResultInfo& params)
            {
                _module_.Notify(_T("onUpdateStateChange"), params);
            }

            // Event: 'onUpdateStateChange' - notify Firmware update state change
            static void OnUpdateStateChange(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::IFirmwareUpdate::State>& state,
                     const Core::JSON::EnumType<Exchange::IFirmwareUpdate::SubState>& substate)
            {
                JsonData::FirmwareUpdate::GetUpdateStateResultInfo _params_;
                _params_.State = state;
                _params_.Substate = substate;

                OnUpdateStateChange(_module_, _params_);
            }

            // Event: 'onUpdateStateChange' - notify Firmware update state change
            static void OnUpdateStateChange(const JSONRPC& _module_, const Exchange::IFirmwareUpdate::State& state,
                     const Exchange::IFirmwareUpdate::SubState& substate)
            {
                JsonData::FirmwareUpdate::GetUpdateStateResultInfo _params_;
                _params_.State = state;
                _params_.Substate = substate;

                OnUpdateStateChange(_module_, _params_);
            }

            // Event: 'onFlashingStateChange' - This notification is raised between flashing started state and flashing succeeded/failed
            static void OnFlashingStateChange(const JSONRPC& _module_, const JsonData::FirmwareUpdate::OnFlashingStateChangeParamsData& params)
            {
                _module_.Notify(_T("onFlashingStateChange"), params);
            }

            // Event: 'onFlashingStateChange' - This notification is raised between flashing started state and flashing succeeded/failed
            static void OnFlashingStateChange(const JSONRPC& _module_, const Core::JSON::DecUInt32& percentageComplete)
            {
                JsonData::FirmwareUpdate::OnFlashingStateChangeParamsData _params_;
                _params_.PercentageComplete = percentageComplete;

                OnFlashingStateChange(_module_, _params_);
            }

            // Event: 'onFlashingStateChange' - This notification is raised between flashing started state and flashing succeeded/failed
            static void OnFlashingStateChange(const JSONRPC& _module_, const uint32_t& percentageComplete)
            {
                JsonData::FirmwareUpdate::OnFlashingStateChangeParamsData _params_;
                _params_.PercentageComplete = percentageComplete;

                OnFlashingStateChange(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JFirmwareUpdate

} // namespace Exchange

} // namespace WPEFramework

