// C++ classes for PowerManager API JSON-RPC API.
// Generated automatically from 'IPowerManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IPowerManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace PowerManager {

        // Common classes
        //

        class RebootParamsInfo : public Core::JSON::Container {
        public:
            RebootParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("rebootRequestor"), &RebootRequestor);
                Add(_T("rebootReasonCustom"), &RebootReasonCustom);
                Add(_T("rebootReasonOther"), &RebootReasonOther);
            }

            bool IsValid() const
            {
                return (true);
            }

            RebootParamsInfo(const RebootParamsInfo&) = delete;
            RebootParamsInfo& operator=(const RebootParamsInfo&) = delete;

        public:
            Core::JSON::String RebootRequestor; // Reboot device
            Core::JSON::String RebootReasonCustom; // Reboot device
            Core::JSON::String RebootReasonOther; // Reboot device
        }; // class RebootParamsInfo

        class SetTemperatureThresholdsParamsInfo : public Core::JSON::Container {
        public:
            SetTemperatureThresholdsParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("high"), &High);
                Add(_T("critical"), &Critical);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetTemperatureThresholdsParamsInfo(const SetTemperatureThresholdsParamsInfo&) = delete;
            SetTemperatureThresholdsParamsInfo& operator=(const SetTemperatureThresholdsParamsInfo&) = delete;

        public:
            Core::JSON::Float High; // high threshold
            Core::JSON::Float Critical; // : critical threshold
        }; // class SetTemperatureThresholdsParamsInfo

        class WakeupSourceConfigInfo : public Core::JSON::Container {
        public:
            WakeupSourceConfigInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            WakeupSourceConfigInfo(const WakeupSourceConfigInfo& _other)
                : Core::JSON::Container()
                , WakeupSource(_other.WakeupSource)
                , Enabled(_other.Enabled)
            {
                _Init();
            }

            WakeupSourceConfigInfo& operator=(const WakeupSourceConfigInfo& _rhs)
            {
                WakeupSource = _rhs.WakeupSource;
                Enabled = _rhs.Enabled;
                return (*this);
            }

            WakeupSourceConfigInfo(const Exchange::IPowerManager::WakeupSourceConfig& _other)
                : Core::JSON::Container()
            {
                WakeupSource = _other.wakeupSource;
                Enabled = _other.enabled;
                _Init();
            }

            WakeupSourceConfigInfo& operator=(const Exchange::IPowerManager::WakeupSourceConfig& _rhs)
            {
                WakeupSource = _rhs.wakeupSource;
                Enabled = _rhs.enabled;
                return (*this);
            }

            operator Exchange::IPowerManager::WakeupSourceConfig() const
            {
                Exchange::IPowerManager::WakeupSourceConfig _value{};
                _value.wakeupSource = WakeupSource;
                _value.enabled = Enabled;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("wakeupSource"), &WakeupSource);
                Add(_T("enabled"), &Enabled);
            }

        public:
            Core::JSON::EnumType<Exchange::IPowerManager::WakeupSrcType> WakeupSource;
            Core::JSON::Boolean Enabled;
        }; // class WakeupSourceConfigInfo

        // Method params/result classes
        //

        class AddPowerModePreChangeClientParamsData : public Core::JSON::Container {
        public:
            AddPowerModePreChangeClientParamsData()
                : Core::JSON::Container()
            {
                Add(_T("clientName"), &ClientName);
            }

            bool IsValid() const
            {
                return (true);
            }

            AddPowerModePreChangeClientParamsData(const AddPowerModePreChangeClientParamsData&) = delete;
            AddPowerModePreChangeClientParamsData& operator=(const AddPowerModePreChangeClientParamsData&) = delete;

        public:
            Core::JSON::String ClientName; // Name of the client
        }; // class AddPowerModePreChangeClientParamsData

        class DelayPowerModeChangeByParamsData : public Core::JSON::Container {
        public:
            DelayPowerModeChangeByParamsData()
                : Core::JSON::Container()
            {
                Add(_T("clientId"), &ClientId);
                Add(_T("transactionId"), &TransactionId);
                Add(_T("delayPeriod"), &DelayPeriod);
            }

            bool IsValid() const
            {
                return (true);
            }

            DelayPowerModeChangeByParamsData(const DelayPowerModeChangeByParamsData&) = delete;
            DelayPowerModeChangeByParamsData& operator=(const DelayPowerModeChangeByParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 ClientId; // Unique identifier for the client, as received in AddPowerModePreChangeClient
            Core::JSON::DecSInt32 TransactionId; // transaction id as received in OnPowerModePreChange
            Core::JSON::DecSInt32 DelayPeriod; // delay in seconds
        }; // class DelayPowerModeChangeByParamsData

        class GetPowerStateResultData : public Core::JSON::Container {
        public:
            GetPowerStateResultData()
                : Core::JSON::Container()
            {
                Add(_T("currentState"), &CurrentState);
                Add(_T("previousState"), &PreviousState);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetPowerStateResultData(const GetPowerStateResultData&) = delete;
            GetPowerStateResultData& operator=(const GetPowerStateResultData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IPowerManager::PowerState> CurrentState; // Get Power State
            Core::JSON::EnumType<Exchange::IPowerManager::PowerState> PreviousState; // Get Power State
        }; // class GetPowerStateResultData

        class OnDeepSleepTimeoutParamsData : public Core::JSON::Container {
        public:
            OnDeepSleepTimeoutParamsData()
                : Core::JSON::Container()
            {
                Add(_T("wakeupTimeout"), &WakeupTimeout);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnDeepSleepTimeoutParamsData(const OnDeepSleepTimeoutParamsData&) = delete;
            OnDeepSleepTimeoutParamsData& operator=(const OnDeepSleepTimeoutParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 WakeupTimeout; // Deep sleep wakeup timeout in seconds
        }; // class OnDeepSleepTimeoutParamsData

        class OnNetworkStandbyModeChangedParamsData : public Core::JSON::Container {
        public:
            OnNetworkStandbyModeChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnNetworkStandbyModeChangedParamsData(const OnNetworkStandbyModeChangedParamsData&) = delete;
            OnNetworkStandbyModeChangedParamsData& operator=(const OnNetworkStandbyModeChangedParamsData&) = delete;

        public:
            Core::JSON::Boolean Enabled; // network standby enabled or disabled
        }; // class OnNetworkStandbyModeChangedParamsData

        class OnPowerModeChangedParamsData : public Core::JSON::Container {
        public:
            OnPowerModeChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("currentState"), &CurrentState);
                Add(_T("newState"), &NewState);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnPowerModeChangedParamsData(const OnPowerModeChangedParamsData&) = delete;
            OnPowerModeChangedParamsData& operator=(const OnPowerModeChangedParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IPowerManager::PowerState> CurrentState; // Current Power State
            Core::JSON::EnumType<Exchange::IPowerManager::PowerState> NewState; // New Power State
        }; // class OnPowerModeChangedParamsData

        class OnPowerModePreChangeParamsData : public Core::JSON::Container {
        public:
            OnPowerModePreChangeParamsData()
                : Core::JSON::Container()
            {
                Add(_T("currentState"), &CurrentState);
                Add(_T("newState"), &NewState);
                Add(_T("transactionId"), &TransactionId);
                Add(_T("stateChangeAfter"), &StateChangeAfter);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnPowerModePreChangeParamsData(const OnPowerModePreChangeParamsData&) = delete;
            OnPowerModePreChangeParamsData& operator=(const OnPowerModePreChangeParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IPowerManager::PowerState> CurrentState; // Current Power State
            Core::JSON::EnumType<Exchange::IPowerManager::PowerState> NewState; // Changing power state to this New Power State
            Core::JSON::DecSInt32 TransactionId; // transactionId to be used when invoking prePowerChangeComplete() / delayPowerModeChangeBy API
            Core::JSON::DecSInt32 StateChangeAfter; // seconds after which the actual power mode will be applied.
        }; // class OnPowerModePreChangeParamsData

        class OnThermalModeChangedParamsData : public Core::JSON::Container {
        public:
            OnThermalModeChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("currentThermalLevel"), &CurrentThermalLevel);
                Add(_T("newThermalLevel"), &NewThermalLevel);
                Add(_T("currentTemperature"), &CurrentTemperature);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnThermalModeChangedParamsData(const OnThermalModeChangedParamsData&) = delete;
            OnThermalModeChangedParamsData& operator=(const OnThermalModeChangedParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IPowerManager::ThermalTemperature> CurrentThermalLevel; // current thermal level
            Core::JSON::EnumType<Exchange::IPowerManager::ThermalTemperature> NewThermalLevel; // new thermal level
            Core::JSON::Float CurrentTemperature; // current temperature
        }; // class OnThermalModeChangedParamsData

        class PowerModePreChangeCompleteParamsData : public Core::JSON::Container {
        public:
            PowerModePreChangeCompleteParamsData()
                : Core::JSON::Container()
            {
                Add(_T("clientId"), &ClientId);
                Add(_T("transactionId"), &TransactionId);
            }

            bool IsValid() const
            {
                return (true);
            }

            PowerModePreChangeCompleteParamsData(const PowerModePreChangeCompleteParamsData&) = delete;
            PowerModePreChangeCompleteParamsData& operator=(const PowerModePreChangeCompleteParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 ClientId; // Unique identifier for the client, as received in AddPowerModePreChangeClient
            Core::JSON::DecSInt32 TransactionId; // transaction id as received in OnPowerModePreChange
        }; // class PowerModePreChangeCompleteParamsData

        class RemovePowerModePreChangeClientParamsData : public Core::JSON::Container {
        public:
            RemovePowerModePreChangeClientParamsData()
                : Core::JSON::Container()
            {
                Add(_T("clientId"), &ClientId);
            }

            bool IsValid() const
            {
                return (true);
            }

            RemovePowerModePreChangeClientParamsData(const RemovePowerModePreChangeClientParamsData&) = delete;
            RemovePowerModePreChangeClientParamsData& operator=(const RemovePowerModePreChangeClientParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 ClientId; // Unique identifier for the client. See `AddPowerModePreChangeClient`
        }; // class RemovePowerModePreChangeClientParamsData

        class SetDeepSleepTimerData : public Core::JSON::Container {
        public:
            SetDeepSleepTimerData()
                : Core::JSON::Container()
            {
                Add(_T("timeOut"), &TimeOut);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetDeepSleepTimerData(const SetDeepSleepTimerData&) = delete;
            SetDeepSleepTimerData& operator=(const SetDeepSleepTimerData&) = delete;

        public:
            Core::JSON::DecSInt32 TimeOut; // deep sleep timeout
        }; // class SetDeepSleepTimerData

        class SetNetworkStandbyModeData : public Core::JSON::Container {
        public:
            SetNetworkStandbyModeData()
                : Core::JSON::Container()
            {
                Add(_T("standbyMode"), &StandbyMode);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetNetworkStandbyModeData(const SetNetworkStandbyModeData&) = delete;
            SetNetworkStandbyModeData& operator=(const SetNetworkStandbyModeData&) = delete;

        public:
            Core::JSON::Boolean StandbyMode; // Network standby mode
        }; // class SetNetworkStandbyModeData

        class SetOvertempGraceIntervalData : public Core::JSON::Container {
        public:
            SetOvertempGraceIntervalData()
                : Core::JSON::Container()
            {
                Add(_T("graceInterval"), &GraceInterval);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetOvertempGraceIntervalData(const SetOvertempGraceIntervalData&) = delete;
            SetOvertempGraceIntervalData& operator=(const SetOvertempGraceIntervalData&) = delete;

        public:
            Core::JSON::DecSInt32 GraceInterval; // interval in secs?
        }; // class SetOvertempGraceIntervalData

        class SetPowerStateParamsData : public Core::JSON::Container {
        public:
            SetPowerStateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("keyCode"), &KeyCode);
                Add(_T("powerState"), &PowerState);
                Add(_T("reason"), &Reason);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPowerStateParamsData(const SetPowerStateParamsData&) = delete;
            SetPowerStateParamsData& operator=(const SetPowerStateParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 KeyCode; // Set Power State
            Core::JSON::EnumType<Exchange::IPowerManager::PowerState> PowerState; // Set power to this state
            Core::JSON::String Reason; // Reason for moving to the power state
        }; // class SetPowerStateParamsData

        class SetWakeupSourceConfigParamsData : public Core::JSON::Container {
        public:
            SetWakeupSourceConfigParamsData()
                : Core::JSON::Container()
            {
                Add(_T("wakeupSources"), &WakeupSources);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetWakeupSourceConfigParamsData(const SetWakeupSourceConfigParamsData&) = delete;
            SetWakeupSourceConfigParamsData& operator=(const SetWakeupSourceConfigParamsData&) = delete;

        public:
            Core::JSON::ArrayType<WakeupSourceConfigInfo> WakeupSources; // Wake up sources array
        }; // class SetWakeupSourceConfigParamsData

    } // namespace PowerManager

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IPowerManager::PowerState)
ENUM_CONVERSION_HANDLER(Exchange::IPowerManager::WakeupSrcType)
ENUM_CONVERSION_HANDLER(Exchange::IPowerManager::WakeupReason)
ENUM_CONVERSION_HANDLER(Exchange::IPowerManager::ThermalTemperature)

}

