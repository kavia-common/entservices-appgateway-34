// Generated automatically from 'IPowerManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_PowerManager.h"
#include <interfaces/IPowerManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JPowerManager {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IPowerManager* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JPowerManager"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'addPowerModePreChangeClient' - Register a client to engage in power mode state changes
            _module_.Register<JsonData::PowerManager::AddPowerModePreChangeClientParamsData, Core::JSON::DecUInt32>(_T("addPowerModePreChangeClient"), 
                [_impl_](const JsonData::PowerManager::AddPowerModePreChangeClientParamsData& params, Core::JSON::DecUInt32& clientId) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _clientName{params.ClientName};
                    uint32_t _clientId{};

                    _errorCode = _impl_->AddPowerModePreChangeClient(_clientName, _clientId);

                    if (_errorCode == Core::ERROR_NONE) {
                        clientId = _clientId;
                    }

                    return (_errorCode);
                });

            // Method: 'removePowerModePreChangeClient' - Removes a registered client from participating in power mode pre-change operations
            _module_.Register<JsonData::PowerManager::RemovePowerModePreChangeClientParamsData, void>(_T("removePowerModePreChangeClient"), 
                [_impl_](const JsonData::PowerManager::RemovePowerModePreChangeClientParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _clientId{params.ClientId};

                    _errorCode = _impl_->RemovePowerModePreChangeClient(_clientId);

                    return (_errorCode);
                });

            // Method: 'setPowerState' - Set Power State
            _module_.Register<JsonData::PowerManager::SetPowerStateParamsData, void>(_T("setPowerState"), 
                [_impl_](const JsonData::PowerManager::SetPowerStateParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _keyCode{params.KeyCode};
                    const Exchange::IPowerManager::PowerState _powerState{params.PowerState};
                    const string _reason{params.Reason};

                    _errorCode = _impl_->SetPowerState(_keyCode, _powerState, _reason);

                    return (_errorCode);
                });

            // Method: 'getPowerState' - Get Power State
            _module_.Register<void, JsonData::PowerManager::GetPowerStateResultData>(_T("getPowerState"), 
                [_impl_](JsonData::PowerManager::GetPowerStateResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IPowerManager::PowerState _currentState{};
                    Exchange::IPowerManager::PowerState _previousState{};

                    _errorCode = _impl_->GetPowerState(_currentState, _previousState);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.CurrentState = _currentState;
                        result.PreviousState = _previousState;
                    }

                    return (_errorCode);
                });

            // Method: 'getThermalState' - Get Current Thermal State (temperature)
            _module_.Register<void, Core::JSON::Float>(_T("getThermalState"), 
                [_impl_](Core::JSON::Float& currentTemperature) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    float _currentTemperature{};

                    _errorCode = _impl_->GetThermalState(_currentTemperature);

                    if (_errorCode == Core::ERROR_NONE) {
                        currentTemperature = _currentTemperature;
                    }

                    return (_errorCode);
                });

            // Method: 'setTemperatureThresholds' - Set Temperature Thresholds
            _module_.Register<JsonData::PowerManager::SetTemperatureThresholdsParamsInfo, void>(_T("setTemperatureThresholds"), 
                [_impl_](const JsonData::PowerManager::SetTemperatureThresholdsParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const float _high{params.High};
                    const float _critical{params.Critical};

                    _errorCode = _impl_->SetTemperatureThresholds(_high, _critical);

                    return (_errorCode);
                });

            // Method: 'getTemperatureThresholds' - Get Temperature Thresholds
            _module_.Register<void, JsonData::PowerManager::SetTemperatureThresholdsParamsInfo>(_T("getTemperatureThresholds"), 
                [_impl_](JsonData::PowerManager::SetTemperatureThresholdsParamsInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    float _high{};
                    float _critical{};

                    _errorCode = _impl_->GetTemperatureThresholds(_high, _critical);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.High = _high;
                        result.Critical = _critical;
                    }

                    return (_errorCode);
                });

            // Method: 'reboot' - Reboot device
            _module_.Register<JsonData::PowerManager::RebootParamsInfo, void>(_T("reboot"), 
                [_impl_](const JsonData::PowerManager::RebootParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _rebootRequestor{params.RebootRequestor};
                    const string _rebootReasonCustom{params.RebootReasonCustom};
                    const string _rebootReasonOther{params.RebootReasonOther};

                    _errorCode = _impl_->Reboot(_rebootRequestor, _rebootReasonCustom, _rebootReasonOther);

                    return (_errorCode);
                });

            // Method: 'getNetworkStandbyMode' - Get the standby mode for Network
            _module_.Register<void, Core::JSON::Boolean>(_T("getNetworkStandbyMode"), 
                [_impl_](Core::JSON::Boolean& standbyMode) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _standbyMode{};

                    _errorCode = _impl_->GetNetworkStandbyMode(_standbyMode);

                    if (_errorCode == Core::ERROR_NONE) {
                        standbyMode = _standbyMode;
                    }

                    return (_errorCode);
                });

            // Method: 'setWakeupSourceConfig' - Set the source configuration for device wakeup
            _module_.Register<JsonData::PowerManager::SetWakeupSourceConfigParamsData, void>(_T("setWakeupSourceConfig"), 
                [_impl_](const JsonData::PowerManager::SetWakeupSourceConfigParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    std::list<Exchange::IPowerManager::WakeupSourceConfig> _elements;
                    auto _Iterator = params.WakeupSources.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<IPowerManager::WakeupSourceConfig,
                             ID_POWER_MANAGER_WAKEUP_SRC_ITERATOR>* const _wakeupSources{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<IPowerManager::WakeupSourceConfig,
                             ID_POWER_MANAGER_WAKEUP_SRC_ITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<IPowerManager::WakeupSourceConfig,
                             ID_POWER_MANAGER_WAKEUP_SRC_ITERATOR>>(_elements)};

                    ASSERT(_wakeupSources != nullptr); 

                    if ((_wakeupSources != nullptr)) {
                        _errorCode = _impl_->SetWakeupSourceConfig(_wakeupSources);
                        _wakeupSources->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    return (_errorCode);
                });

            // Method: 'getWakeupSourceConfig' - Get the source configuration for device wakeup
            _module_.Register<void, Core::JSON::ArrayType<JsonData::PowerManager::WakeupSourceConfigInfo>>(_T("getWakeupSourceConfig"), 
                [_impl_](Core::JSON::ArrayType<JsonData::PowerManager::WakeupSourceConfigInfo>& wakeupSources) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<IPowerManager::WakeupSourceConfig, ID_POWER_MANAGER_WAKEUP_SRC_ITERATOR>* _wakeupSources{};

                    _errorCode = _impl_->GetWakeupSourceConfig(_wakeupSources);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_wakeupSources != nullptr) {
                            Exchange::IPowerManager::WakeupSourceConfig _resultItem_{};
                            while (_wakeupSources->Next(_resultItem_) == true) { wakeupSources.Add() = _resultItem_; }
                            _wakeupSources->Release();
                        }
                    }

                    return (_errorCode);
                });

            // Method: 'getPowerStateBeforeReboot' - Get Power state before reboot
            _module_.Register<void, Core::JSON::EnumType<Exchange::IPowerManager::PowerState>>(_T("getPowerStateBeforeReboot"), 
                [_impl_](Core::JSON::EnumType<Exchange::IPowerManager::PowerState>& powerStateBeforeReboot) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IPowerManager::PowerState _powerStateBeforeReboot{};

                    _errorCode = _impl_->GetPowerStateBeforeReboot(_powerStateBeforeReboot);

                    if (_errorCode == Core::ERROR_NONE) {
                        powerStateBeforeReboot = _powerStateBeforeReboot;
                    }

                    return (_errorCode);
                });

            // Method: 'powerModePreChangeComplete' - Pre power mode handling complete for given client and transation id
            _module_.Register<JsonData::PowerManager::PowerModePreChangeCompleteParamsData, void>(_T("powerModePreChangeComplete"), 
                [_impl_](const JsonData::PowerManager::PowerModePreChangeCompleteParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _clientId{params.ClientId};
                    const int32_t _transactionId{params.TransactionId};

                    _errorCode = _impl_->PowerModePreChangeComplete(_clientId, _transactionId);

                    return (_errorCode);
                });

            // Method: 'delayPowerModeChangeBy' - Delay Powermode change by given time
            _module_.Register<JsonData::PowerManager::DelayPowerModeChangeByParamsData, void>(_T("delayPowerModeChangeBy"), 
                [_impl_](const JsonData::PowerManager::DelayPowerModeChangeByParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _clientId{params.ClientId};
                    const int32_t _transactionId{params.TransactionId};
                    const int32_t _delayPeriod{params.DelayPeriod};

                    _errorCode = _impl_->DelayPowerModeChangeBy(_clientId, _transactionId, _delayPeriod);

                    return (_errorCode);
                });

            // Property: 'setOvertempGraceInterval' - Set Temperature Thresholds (w/o)
            _module_.Register<JsonData::PowerManager::SetOvertempGraceIntervalData, void>(_T("setOvertempGraceInterval"), 
                [_impl_](const JsonData::PowerManager::SetOvertempGraceIntervalData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // write-only property set
                    const int32_t _graceInterval{params.GraceInterval};

                    _errorCode = _impl_->SetOvertempGraceInterval(_graceInterval);

                    return (_errorCode);
                });

            // Property: 'getOvertempGraceInterval' - Get Temperature Grace interval (r/o)
            _module_.Register<void, Core::JSON::DecSInt32>(_T("getOvertempGraceInterval"), 
                [_impl_](Core::JSON::DecSInt32& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    int32_t _result{};

                    _errorCode = _impl_->GetOvertempGraceInterval(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'setDeepSleepTimer' - Set Deep sleep timer for timeOut period (w/o)
            _module_.Register<JsonData::PowerManager::SetDeepSleepTimerData, void>(_T("setDeepSleepTimer"), 
                [_impl_](const JsonData::PowerManager::SetDeepSleepTimerData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // write-only property set
                    const int32_t _timeOut{params.TimeOut};

                    _errorCode = _impl_->SetDeepSleepTimer(_timeOut);

                    return (_errorCode);
                });

            // Property: 'getLastWakeupReason' - Get Last Wake up reason (r/o)
            _module_.Register<void, Core::JSON::EnumType<Exchange::IPowerManager::WakeupReason>>(_T("getLastWakeupReason"), 
                [_impl_](Core::JSON::EnumType<Exchange::IPowerManager::WakeupReason>& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IPowerManager::WakeupReason _result{};

                    _errorCode = _impl_->GetLastWakeupReason(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'getLastWakeupKeyCode' - Get the key code that can be used for wakeup (r/o)
            _module_.Register<void, Core::JSON::DecSInt32>(_T("getLastWakeupKeyCode"), 
                [_impl_](Core::JSON::DecSInt32& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    int32_t _result{};

                    _errorCode = _impl_->GetLastWakeupKeyCode(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'setNetworkStandbyMode' - Set the standby mode for Network (w/o)
            _module_.Register<JsonData::PowerManager::SetNetworkStandbyModeData, void>(_T("setNetworkStandbyMode"), 
                [_impl_](const JsonData::PowerManager::SetNetworkStandbyModeData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // write-only property set
                    const bool _standbyMode{params.StandbyMode};

                    _errorCode = _impl_->SetNetworkStandbyMode(_standbyMode);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("addPowerModePreChangeClient"));
            _module_.Unregister(_T("removePowerModePreChangeClient"));
            _module_.Unregister(_T("setPowerState"));
            _module_.Unregister(_T("getPowerState"));
            _module_.Unregister(_T("getThermalState"));
            _module_.Unregister(_T("setTemperatureThresholds"));
            _module_.Unregister(_T("getTemperatureThresholds"));
            _module_.Unregister(_T("reboot"));
            _module_.Unregister(_T("getNetworkStandbyMode"));
            _module_.Unregister(_T("setWakeupSourceConfig"));
            _module_.Unregister(_T("getWakeupSourceConfig"));
            _module_.Unregister(_T("getPowerStateBeforeReboot"));
            _module_.Unregister(_T("powerModePreChangeComplete"));
            _module_.Unregister(_T("delayPowerModeChangeBy"));
            _module_.Unregister(_T("setOvertempGraceInterval"));
            _module_.Unregister(_T("getOvertempGraceInterval"));
            _module_.Unregister(_T("setDeepSleepTimer"));
            _module_.Unregister(_T("getLastWakeupReason"));
            _module_.Unregister(_T("getLastWakeupKeyCode"));
            _module_.Unregister(_T("setNetworkStandbyMode"));
        }

        namespace Event {

            // Event: 'onDeepSleepTimeout' - Deep sleep timeout event
            static void OnDeepSleepTimeout(const JSONRPC& _module_, const JsonData::PowerManager::OnDeepSleepTimeoutParamsData& params)
            {
                _module_.Notify(_T("onDeepSleepTimeout"), params);
            }

            // Event: 'onDeepSleepTimeout' - Deep sleep timeout event
            static void OnDeepSleepTimeout(const JSONRPC& _module_, const Core::JSON::DecSInt32& wakeupTimeout)
            {
                JsonData::PowerManager::OnDeepSleepTimeoutParamsData _params_;
                _params_.WakeupTimeout = wakeupTimeout;

                OnDeepSleepTimeout(_module_, _params_);
            }

            // Event: 'onDeepSleepTimeout' - Deep sleep timeout event
            static void OnDeepSleepTimeout(const JSONRPC& _module_, const int32_t& wakeupTimeout)
            {
                JsonData::PowerManager::OnDeepSleepTimeoutParamsData _params_;
                _params_.WakeupTimeout = wakeupTimeout;

                OnDeepSleepTimeout(_module_, _params_);
            }

            // Event: 'onNetworkStandbyModeChanged' - Network Standby Mode changed event - only on XIone
            static void OnNetworkStandbyModeChanged(const JSONRPC& _module_, const JsonData::PowerManager::OnNetworkStandbyModeChangedParamsData& params)
            {
                _module_.Notify(_T("onNetworkStandbyModeChanged"), params);
            }

            // Event: 'onNetworkStandbyModeChanged' - Network Standby Mode changed event - only on XIone
            static void OnNetworkStandbyModeChanged(const JSONRPC& _module_, const Core::JSON::Boolean& enabled)
            {
                JsonData::PowerManager::OnNetworkStandbyModeChangedParamsData _params_;
                _params_.Enabled = enabled;

                OnNetworkStandbyModeChanged(_module_, _params_);
            }

            // Event: 'onNetworkStandbyModeChanged' - Network Standby Mode changed event - only on XIone
            static void OnNetworkStandbyModeChanged(const JSONRPC& _module_, const bool& enabled)
            {
                JsonData::PowerManager::OnNetworkStandbyModeChangedParamsData _params_;
                _params_.Enabled = enabled;

                OnNetworkStandbyModeChanged(_module_, _params_);
            }

            // Event: 'onRebootBegin' - Reboot begin event
            static void OnRebootBegin(const JSONRPC& _module_, const JsonData::PowerManager::RebootParamsInfo& params)
            {
                _module_.Notify(_T("onRebootBegin"), params);
            }

            // Event: 'onRebootBegin' - Reboot begin event
            static void OnRebootBegin(const JSONRPC& _module_, const Core::JSON::String& rebootReasonCustom, const Core::JSON::String& rebootReasonOther,
                     const Core::JSON::String& rebootRequestor)
            {
                JsonData::PowerManager::RebootParamsInfo _params_;
                _params_.RebootReasonCustom = rebootReasonCustom;
                _params_.RebootReasonOther = rebootReasonOther;
                _params_.RebootRequestor = rebootRequestor;

                OnRebootBegin(_module_, _params_);
            }

            // Event: 'onRebootBegin' - Reboot begin event
            static void OnRebootBegin(const JSONRPC& _module_, const string& rebootReasonCustom, const string& rebootReasonOther, const string& rebootRequestor)
            {
                JsonData::PowerManager::RebootParamsInfo _params_;
                _params_.RebootReasonCustom = rebootReasonCustom;
                _params_.RebootReasonOther = rebootReasonOther;
                _params_.RebootRequestor = rebootRequestor;

                OnRebootBegin(_module_, _params_);
            }

            // Event: 'onPowerModePreChange' - Power mode Pre-change event
            static void OnPowerModePreChange(const JSONRPC& _module_, const JsonData::PowerManager::OnPowerModePreChangeParamsData& params)
            {
                _module_.Notify(_T("onPowerModePreChange"), params);
            }

            // Event: 'onPowerModePreChange' - Power mode Pre-change event
            static void OnPowerModePreChange(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::IPowerManager::PowerState>& currentState,
                     const Core::JSON::EnumType<Exchange::IPowerManager::PowerState>& newState, const Core::JSON::DecSInt32& transactionId,
                     const Core::JSON::DecSInt32& stateChangeAfter)
            {
                JsonData::PowerManager::OnPowerModePreChangeParamsData _params_;
                _params_.CurrentState = currentState;
                _params_.NewState = newState;
                _params_.TransactionId = transactionId;
                _params_.StateChangeAfter = stateChangeAfter;

                OnPowerModePreChange(_module_, _params_);
            }

            // Event: 'onPowerModePreChange' - Power mode Pre-change event
            static void OnPowerModePreChange(const JSONRPC& _module_, const Exchange::IPowerManager::PowerState& currentState,
                     const Exchange::IPowerManager::PowerState& newState, const int32_t& transactionId, const int32_t& stateChangeAfter)
            {
                JsonData::PowerManager::OnPowerModePreChangeParamsData _params_;
                _params_.CurrentState = currentState;
                _params_.NewState = newState;
                _params_.TransactionId = transactionId;
                _params_.StateChangeAfter = stateChangeAfter;

                OnPowerModePreChange(_module_, _params_);
            }

            // Event: 'onThermalModeChanged' - Thermal Mode changed event
            static void OnThermalModeChanged(const JSONRPC& _module_, const JsonData::PowerManager::OnThermalModeChangedParamsData& params)
            {
                _module_.Notify(_T("onThermalModeChanged"), params);
            }

            // Event: 'onThermalModeChanged' - Thermal Mode changed event
            static void OnThermalModeChanged(const JSONRPC& _module_,
                     const Core::JSON::EnumType<Exchange::IPowerManager::ThermalTemperature>& currentThermalLevel, const Core::JSON::EnumType<Exchange::IPowerManager::ThermalTemperature>& newThermalLevel, const Core::JSON::Float& currentTemperature)
            {
                JsonData::PowerManager::OnThermalModeChangedParamsData _params_;
                _params_.CurrentThermalLevel = currentThermalLevel;
                _params_.NewThermalLevel = newThermalLevel;
                _params_.CurrentTemperature = currentTemperature;

                OnThermalModeChanged(_module_, _params_);
            }

            // Event: 'onThermalModeChanged' - Thermal Mode changed event
            static void OnThermalModeChanged(const JSONRPC& _module_, const Exchange::IPowerManager::ThermalTemperature& currentThermalLevel,
                     const Exchange::IPowerManager::ThermalTemperature& newThermalLevel, const float& currentTemperature)
            {
                JsonData::PowerManager::OnThermalModeChangedParamsData _params_;
                _params_.CurrentThermalLevel = currentThermalLevel;
                _params_.NewThermalLevel = newThermalLevel;
                _params_.CurrentTemperature = currentTemperature;

                OnThermalModeChanged(_module_, _params_);
            }

            // Event: 'onPowerModeChanged' - Power mode changed
            static void OnPowerModeChanged(const JSONRPC& _module_, const JsonData::PowerManager::OnPowerModeChangedParamsData& params)
            {
                _module_.Notify(_T("onPowerModeChanged"), params);
            }

            // Event: 'onPowerModeChanged' - Power mode changed
            static void OnPowerModeChanged(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::IPowerManager::PowerState>& currentState,
                     const Core::JSON::EnumType<Exchange::IPowerManager::PowerState>& newState)
            {
                JsonData::PowerManager::OnPowerModeChangedParamsData _params_;
                _params_.CurrentState = currentState;
                _params_.NewState = newState;

                OnPowerModeChanged(_module_, _params_);
            }

            // Event: 'onPowerModeChanged' - Power mode changed
            static void OnPowerModeChanged(const JSONRPC& _module_, const Exchange::IPowerManager::PowerState& currentState,
                     const Exchange::IPowerManager::PowerState& newState)
            {
                JsonData::PowerManager::OnPowerModeChangedParamsData _params_;
                _params_.CurrentState = currentState;
                _params_.NewState = newState;

                OnPowerModeChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JPowerManager

} // namespace Exchange

} // namespace WPEFramework

