// C++ classes for FirmwareUpdate API JSON-RPC API.
// Generated automatically from 'IFirmwareUpdate.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IFirmwareUpdate.h>

namespace WPEFramework {

namespace JsonData {

    namespace FirmwareUpdate {

        // Common classes
        //

        class GetUpdateStateResultInfo : public Core::JSON::Container {
        public:
            GetUpdateStateResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetUpdateStateResultInfo(const Exchange::IFirmwareUpdate::GetUpdateStateResult& _other)
                : Core::JSON::Container()
            {
                State = _other.state;
                Substate = _other.substate;
                _Init();
            }

            GetUpdateStateResultInfo& operator=(const Exchange::IFirmwareUpdate::GetUpdateStateResult& _rhs)
            {
                State = _rhs.state;
                Substate = _rhs.substate;
                return (*this);
            }

            operator Exchange::IFirmwareUpdate::GetUpdateStateResult() const
            {
                Exchange::IFirmwareUpdate::GetUpdateStateResult _value{};
                _value.state = State;
                _value.substate = Substate;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("state"), &State);
                Add(_T("substate"), &Substate);
            }

        public:
            Core::JSON::EnumType<Exchange::IFirmwareUpdate::State> State; // Firmware update consists of 2 major steps: 1. Firmware Validation,
                    //  and 2. Firmware Flashing. This method returns the "status" of these steps in the firmware update process that was triggered by updateFirmware method.
            Core::JSON::EnumType<Exchange::IFirmwareUpdate::SubState> Substate; // Firmware update consists of 2 major steps: 1. Firmware Validation,
                    // 
                    //  and 2. Firmware Flashing. This method returns the "status" of these steps in the firmware update process that was triggered by updateFirmware method.
        }; // class GetUpdateStateResultInfo

        class ResultInfo : public Core::JSON::Container {
        public:
            ResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            ResultInfo(const Exchange::IFirmwareUpdate::Result& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            ResultInfo& operator=(const Exchange::IFirmwareUpdate::Result& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IFirmwareUpdate::Result() const
            {
                Exchange::IFirmwareUpdate::Result _value{};
                _value.success = Success;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::Boolean Success; // Initiates a firmware update.
        }; // class ResultInfo

        // Method params/result classes
        //

        class OnFlashingStateChangeParamsData : public Core::JSON::Container {
        public:
            OnFlashingStateChangeParamsData()
                : Core::JSON::Container()
            {
                Add(_T("percentageComplete"), &PercentageComplete);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnFlashingStateChangeParamsData(const OnFlashingStateChangeParamsData&) = delete;
            OnFlashingStateChangeParamsData& operator=(const OnFlashingStateChangeParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 PercentageComplete; // : Number between 0 and 100 indicating the "percentage complete" of the flashing process.
        }; // class OnFlashingStateChangeParamsData

        class SetAutoRebootParamsData : public Core::JSON::Container {
        public:
            SetAutoRebootParamsData()
                : Core::JSON::Container()
            {
                Add(_T("enable"), &Enable);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetAutoRebootParamsData(const SetAutoRebootParamsData&) = delete;
            SetAutoRebootParamsData& operator=(const SetAutoRebootParamsData&) = delete;

        public:
            Core::JSON::Boolean Enable; // Enable or disable the AutoReboot feature.
        }; // class SetAutoRebootParamsData

        class UpdateFirmwareParamsData : public Core::JSON::Container {
        public:
            UpdateFirmwareParamsData()
                : Core::JSON::Container()
            {
                Add(_T("firmwareFilepath"), &FirmwareFilepath);
                Add(_T("firmwareType"), &FirmwareType);
            }

            bool IsValid() const
            {
                return (true);
            }

            UpdateFirmwareParamsData(const UpdateFirmwareParamsData&) = delete;
            UpdateFirmwareParamsData& operator=(const UpdateFirmwareParamsData&) = delete;

        public:
            Core::JSON::String FirmwareFilepath; // Initiates a firmware update.
            Core::JSON::String FirmwareType; // Initiates a firmware update.
        }; // class UpdateFirmwareParamsData

    } // namespace FirmwareUpdate

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IFirmwareUpdate::State)
ENUM_CONVERSION_HANDLER(Exchange::IFirmwareUpdate::SubState)

}

