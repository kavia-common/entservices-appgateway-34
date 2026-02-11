// C++ classes for LEDControl API JSON-RPC API.
// Generated automatically from 'ILEDControl.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ILEDControl.h>

namespace WPEFramework {

namespace JsonData {

    namespace LEDControl {

        // Common classes
        //

        class LEDStateInfo : public Core::JSON::Container {
        public:
            LEDStateInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            LEDStateInfo(const Exchange::ILEDControl::LEDState& _other)
                : Core::JSON::Container()
            {
                State = _other.state;
                _Init();
            }

            LEDStateInfo& operator=(const Exchange::ILEDControl::LEDState& _rhs)
            {
                State = _rhs.state;
                return (*this);
            }

            operator Exchange::ILEDControl::LEDState() const
            {
                Exchange::ILEDControl::LEDState _value{};
                _value.state = State;
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
            }

        public:
            Core::JSON::EnumType<Exchange::ILEDControl::LEDControlState> State; // Retrieves current state of the LED. e.g. {"state":"WPS_CONNECTING"}
        }; // class LEDStateInfo

        // Method params/result classes
        //

        class GetSupportedLEDStatesResultData : public Core::JSON::Container {
        public:
            GetSupportedLEDStatesResultData()
                : Core::JSON::Container()
            {
                Add(_T("supportedLEDStates"), &SupportedLEDStates);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetSupportedLEDStatesResultData(const GetSupportedLEDStatesResultData&) = delete;
            GetSupportedLEDStatesResultData& operator=(const GetSupportedLEDStatesResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> SupportedLEDStates; // string [] of supported LED states. e.g. "['ACTIVE', 'STANDBY', 'WPS_CONNECTING',
                    //  'WPS_CONNECTED', 'WPS_ERROR', 'FACTORY_RESET', 'USB_UPGRADE', 'DOWNLOAD_ERROR']"
            Core::JSON::Boolean Success; // boolean
        }; // class GetSupportedLEDStatesResultData

    } // namespace LEDControl

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ILEDControl::LEDControlState)

}

