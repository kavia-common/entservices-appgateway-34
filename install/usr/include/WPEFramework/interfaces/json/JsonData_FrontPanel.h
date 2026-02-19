// C++ classes for FrontPanel API JSON-RPC API.
// Generated automatically from 'IFrontPanel.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IFrontPanel.h>

namespace WPEFramework {

namespace JsonData {

    namespace FrontPanel {

        // Common classes
        //

        class FrontPanelSuccessInfo : public Core::JSON::Container {
        public:
            FrontPanelSuccessInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            FrontPanelSuccessInfo(const Exchange::IFrontPanel::FrontPanelSuccess& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            FrontPanelSuccessInfo& operator=(const Exchange::IFrontPanel::FrontPanelSuccess& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IFrontPanel::FrontPanelSuccess() const
            {
                Exchange::IFrontPanel::FrontPanelSuccess _value{};
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
            Core::JSON::Boolean Success; // Switches the specified LED off
        }; // class FrontPanelSuccessInfo

        class GetBrightnessParamsInfo : public Core::JSON::Container {
        public:
            GetBrightnessParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("index"), &Index);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetBrightnessParamsInfo(const GetBrightnessParamsInfo&) = delete;
            GetBrightnessParamsInfo& operator=(const GetBrightnessParamsInfo&) = delete;

        public:
            Core::JSON::String Index; // Index of the brightness level
        }; // class GetBrightnessParamsInfo

        // Method params/result classes
        //

        class GetBrightnessResultData : public Core::JSON::Container {
        public:
            GetBrightnessResultData()
                : Core::JSON::Container()
            {
                Add(_T("brightness"), &Brightness);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetBrightnessResultData(const GetBrightnessResultData&) = delete;
            GetBrightnessResultData& operator=(const GetBrightnessResultData&) = delete;

        public:
            Core::JSON::DecUInt32 Brightness; // Brightness level
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetBrightnessResultData

        class GetFrontPanelLightsResultData : public Core::JSON::Container {
        public:
            GetFrontPanelLightsResultData()
                : Core::JSON::Container()
            {
                Add(_T("supportedLights"), &SupportedLights);
                Add(_T("supportedLightsInfo"), &SupportedLightsInfo);
                SupportedLightsInfo.SetQuoted(false);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetFrontPanelLightsResultData(const GetFrontPanelLightsResultData&) = delete;
            GetFrontPanelLightsResultData& operator=(const GetFrontPanelLightsResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> SupportedLights; // List of supported front panel lights
            Core::JSON::String SupportedLightsInfo; // Information about the supported front panel lights
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetFrontPanelLightsResultData

        class SetBlinkParamsData : public Core::JSON::Container {
        public:
            SetBlinkParamsData()
                : Core::JSON::Container()
            {
                Add(_T("blinkInfo"), &BlinkInfo);
                BlinkInfo.SetQuoted(false);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetBlinkParamsData(const SetBlinkParamsData&) = delete;
            SetBlinkParamsData& operator=(const SetBlinkParamsData&) = delete;

        public:
            Core::JSON::String BlinkInfo; // JSON string with blink pattern information containing ledIndicator, iterations, and pattern array with brightness,
                    //  duration(milliseconds), and optional color and red/green/blue values.
        }; // class SetBlinkParamsData

        class SetBrightnessParamsData : public Core::JSON::Container {
        public:
            SetBrightnessParamsData()
                : Core::JSON::Container()
            {
                Add(_T("index"), &Index);
                Add(_T("brightness"), &Brightness);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetBrightnessParamsData(const SetBrightnessParamsData&) = delete;
            SetBrightnessParamsData& operator=(const SetBrightnessParamsData&) = delete;

        public:
            Core::JSON::String Index; // Index of the brightness level
            Core::JSON::DecUInt32 Brightness; // Brightness level to set
        }; // class SetBrightnessParamsData

        class SetLEDParamsData : public Core::JSON::Container {
        public:
            SetLEDParamsData()
                : Core::JSON::Container()
            {
                Add(_T("ledIndicator"), &LedIndicator);
                Add(_T("brightness"), &Brightness);
                Add(_T("color"), &Color);
                Add(_T("red"), &Red);
                Add(_T("green"), &Green);
                Add(_T("blue"), &Blue);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetLEDParamsData(const SetLEDParamsData&) = delete;
            SetLEDParamsData& operator=(const SetLEDParamsData&) = delete;

        public:
            Core::JSON::String LedIndicator; // LED indicator to set
            Core::JSON::DecUInt32 Brightness; // Brightness level of the LED
            Core::JSON::String Color; // Color of the LED
            Core::JSON::DecUInt32 Red; // Red component of the LED color
            Core::JSON::DecUInt32 Green; // Green component of the LED color
            Core::JSON::DecUInt32 Blue; // Blue component of the LED color
        }; // class SetLEDParamsData

    } // namespace FrontPanel

} // namespace JsonData

}

