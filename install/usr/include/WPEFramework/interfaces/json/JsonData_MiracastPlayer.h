// C++ classes for MiracastPlayer API JSON-RPC API.
// Generated automatically from 'IMiracastPlayer.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IMiracastPlayer.h>

namespace WPEFramework {

namespace JsonData {

    namespace MiracastPlayer {

        // Common classes
        //

        class EnvArgumentsInfo : public Core::JSON::Container {
        public:
            EnvArgumentsInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            EnvArgumentsInfo(const EnvArgumentsInfo& _other)
                : Core::JSON::Container()
                , ArgName(_other.ArgName)
                , ArgValue(_other.ArgValue)
            {
                _Init();
            }

            EnvArgumentsInfo& operator=(const EnvArgumentsInfo& _rhs)
            {
                ArgName = _rhs.ArgName;
                ArgValue = _rhs.ArgValue;
                return (*this);
            }

            EnvArgumentsInfo(const Exchange::IMiracastPlayer::EnvArguments& _other)
                : Core::JSON::Container()
            {
                ArgName = _other.argName;
                ArgValue = _other.argValue;
                _Init();
            }

            EnvArgumentsInfo& operator=(const Exchange::IMiracastPlayer::EnvArguments& _rhs)
            {
                ArgName = _rhs.argName;
                ArgValue = _rhs.argValue;
                return (*this);
            }

            operator Exchange::IMiracastPlayer::EnvArguments() const
            {
                Exchange::IMiracastPlayer::EnvArguments _value{};
                _value.argName = ArgName;
                _value.argValue = ArgValue;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("argName"), &ArgName);
                Add(_T("argValue"), &ArgValue);
            }

        public:
            Core::JSON::String ArgName; // environment argument name
            Core::JSON::String ArgValue; // environment argument value
        }; // class EnvArgumentsInfo

        class ResultInfo : public Core::JSON::Container {
        public:
            ResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            ResultInfo(const Exchange::IMiracastPlayer::Result& _other)
                : Core::JSON::Container()
            {
                Message = _other.message;
                Success = _other.success;
                _Init();
            }

            ResultInfo& operator=(const Exchange::IMiracastPlayer::Result& _rhs)
            {
                Message = _rhs.message;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IMiracastPlayer::Result() const
            {
                Exchange::IMiracastPlayer::Result _value{};
                _value.message = Message;
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
                Add(_T("message"), &Message);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String Message; // reason for success or failure
            Core::JSON::Boolean Success; // To set the Miracast Player State to Play after the Miracast session like RTSP communication and GStreamer Playback
        }; // class ResultInfo

        class VideoRectangleInfo : public Core::JSON::Container {
        public:
            VideoRectangleInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            VideoRectangleInfo(const Exchange::IMiracastPlayer::VideoRectangle& _other)
                : Core::JSON::Container()
            {
                StartX = _other.startX;
                StartY = _other.startY;
                Width = _other.width;
                Height = _other.height;
                _Init();
            }

            VideoRectangleInfo& operator=(const Exchange::IMiracastPlayer::VideoRectangle& _rhs)
            {
                StartX = _rhs.startX;
                StartY = _rhs.startY;
                Width = _rhs.width;
                Height = _rhs.height;
                return (*this);
            }

            operator Exchange::IMiracastPlayer::VideoRectangle() const
            {
                Exchange::IMiracastPlayer::VideoRectangle _value{};
                _value.startX = StartX;
                _value.startY = StartY;
                _value.width = Width;
                _value.height = Height;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("X"), &StartX);
                Add(_T("Y"), &StartY);
                Add(_T("W"), &Width);
                Add(_T("H"), &Height);
            }

        public:
            Core::JSON::DecSInt32 StartX; // X coordinate of the rectangle
            Core::JSON::DecSInt32 StartY; // Y coordinate of the rectangle
            Core::JSON::DecSInt32 Width; // Width of the rectangle
            Core::JSON::DecSInt32 Height; // Height of the rectangle
        }; // class VideoRectangleInfo

        // Method params/result classes
        //

        class OnStateChangeParamsData : public Core::JSON::Container {
        public:
            OnStateChangeParamsData()
                : Core::JSON::Container()
            {
                Add(_T("name"), &ClientName);
                Add(_T("mac"), &ClientMac);
                Add(_T("state"), &PlayerState);
                Add(_T("reason_code"), &ReasonCode);
                Add(_T("reason"), &ReasonDescription);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnStateChangeParamsData(const OnStateChangeParamsData&) = delete;
            OnStateChangeParamsData& operator=(const OnStateChangeParamsData&) = delete;

        public:
            Core::JSON::String ClientName; // Name of the client device
            Core::JSON::String ClientMac; // MacAddress of the client device
            Core::JSON::EnumType<Exchange::IMiracastPlayer::State> PlayerState; // Current state of the player
            Core::JSON::String ReasonCode; // Reason code for the player state update
            Core::JSON::EnumType<Exchange::IMiracastPlayer::ReasonCode> ReasonDescription; // Notifies when a Miracast source device wants to connect
        }; // class OnStateChangeParamsData

        class PlayRequestParamsData : public Core::JSON::Container {
        public:
            class DeviceParametersData : public Core::JSON::Container {
            public:
                DeviceParametersData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                DeviceParametersData(const Exchange::IMiracastPlayer::DeviceParameters& _other)
                    : Core::JSON::Container()
                {
                    SourceDeviceIP = _other.sourceDeviceIP;
                    SourceDeviceMac = _other.sourceDeviceMac;
                    SourceDeviceName = _other.sourceDeviceName;
                    SinkDeviceIP = _other.sinkDeviceIP;
                    _Init();
                }

                DeviceParametersData& operator=(const Exchange::IMiracastPlayer::DeviceParameters& _rhs)
                {
                    SourceDeviceIP = _rhs.sourceDeviceIP;
                    SourceDeviceMac = _rhs.sourceDeviceMac;
                    SourceDeviceName = _rhs.sourceDeviceName;
                    SinkDeviceIP = _rhs.sinkDeviceIP;
                    return (*this);
                }

                operator Exchange::IMiracastPlayer::DeviceParameters() const
                {
                    Exchange::IMiracastPlayer::DeviceParameters _value{};
                    _value.sourceDeviceIP = SourceDeviceIP;
                    _value.sourceDeviceMac = SourceDeviceMac;
                    _value.sourceDeviceName = SourceDeviceName;
                    _value.sinkDeviceIP = SinkDeviceIP;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("source_dev_ip"), &SourceDeviceIP);
                    Add(_T("source_dev_mac"), &SourceDeviceMac);
                    Add(_T("source_dev_name"), &SourceDeviceName);
                    Add(_T("sink_dev_ip"), &SinkDeviceIP);
                }

            public:
                Core::JSON::String SourceDeviceIP; // IP Address of Source Device
                Core::JSON::String SourceDeviceMac; // MAC Address of Source Device
                Core::JSON::String SourceDeviceName; // Name of Source Device
                Core::JSON::String SinkDeviceIP; // IP Address of Sink Device
            }; // class DeviceParametersData

            PlayRequestParamsData()
                : Core::JSON::Container()
            {
                Add(_T("device_parameters"), &DeviceParam);
                Add(_T("video_rectangle"), &VideoRect);
            }

            bool IsValid() const
            {
                return (true);
            }

            PlayRequestParamsData(const PlayRequestParamsData&) = delete;
            PlayRequestParamsData& operator=(const PlayRequestParamsData&) = delete;

        public:
            PlayRequestParamsData::DeviceParametersData DeviceParam; // Contains Source and Sink Device related properties
            VideoRectangleInfo VideoRect; // Video rectangle to be used for Miracast playback (x, y, width, height)
        }; // class PlayRequestParamsData

        class SetEnvArgumentsParamsData : public Core::JSON::Container {
        public:
            SetEnvArgumentsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("envArgs"), &EnvArgs);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetEnvArgumentsParamsData(const SetEnvArgumentsParamsData&) = delete;
            SetEnvArgumentsParamsData& operator=(const SetEnvArgumentsParamsData&) = delete;

        public:
            Core::JSON::ArrayType<EnvArgumentsInfo> EnvArgs; // environment arguments to be set
        }; // class SetEnvArgumentsParamsData

        class SetWesterosEnvironmentParamsData : public Core::JSON::Container {
        public:
            SetWesterosEnvironmentParamsData()
                : Core::JSON::Container()
            {
                Add(_T("westerosArgs"), &WesterosArgs);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetWesterosEnvironmentParamsData(const SetWesterosEnvironmentParamsData&) = delete;
            SetWesterosEnvironmentParamsData& operator=(const SetWesterosEnvironmentParamsData&) = delete;

        public:
            Core::JSON::ArrayType<EnvArgumentsInfo> WesterosArgs; // Westeros environment arguments to be set
        }; // class SetWesterosEnvironmentParamsData

        class StopRequestParamsData : public Core::JSON::Container {
        public:
            StopRequestParamsData()
                : Core::JSON::Container()
            {
                Add(_T("mac"), &ClientMac);
                Add(_T("name"), &ClientName);
                Add(_T("reason_code"), &ReasonCode);
            }

            bool IsValid() const
            {
                return (true);
            }

            StopRequestParamsData(const StopRequestParamsData&) = delete;
            StopRequestParamsData& operator=(const StopRequestParamsData&) = delete;

        public:
            Core::JSON::String ClientMac; // MacAddress of the client device
            Core::JSON::String ClientName; // Name of the client device
            Core::JSON::DecSInt32 ReasonCode; // Reason code for the player stop request
        }; // class StopRequestParamsData

    } // namespace MiracastPlayer

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IMiracastPlayer::State)
ENUM_CONVERSION_HANDLER(Exchange::IMiracastPlayer::ReasonCode)

}

