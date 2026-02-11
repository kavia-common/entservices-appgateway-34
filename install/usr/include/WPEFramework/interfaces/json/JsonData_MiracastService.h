// C++ classes for MiracastService API JSON-RPC API.
// Generated automatically from 'IMiracastService.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IMiracastService.h>

namespace WPEFramework {

namespace JsonData {

    namespace MiracastService {

        // Common classes
        //

        class ResultInfo : public Core::JSON::Container {
        public:
            ResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            ResultInfo(const Exchange::IMiracastService::Result& _other)
                : Core::JSON::Container()
            {
                Message = _other.message;
                Success = _other.success;
                _Init();
            }

            ResultInfo& operator=(const Exchange::IMiracastService::Result& _rhs)
            {
                Message = _rhs.message;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IMiracastService::Result() const
            {
                Exchange::IMiracastService::Result _value{};
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
            Core::JSON::Boolean Success; // To enable or disable the Miracast feature
        }; // class ResultInfo

        class SetEnabledParamsInfo : public Core::JSON::Container {
        public:
            SetEnabledParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetEnabledParamsInfo(const SetEnabledParamsInfo&) = delete;
            SetEnabledParamsInfo& operator=(const SetEnabledParamsInfo&) = delete;

        public:
            Core::JSON::Boolean Enabled; // Is the MiracastService discovery enabled or not
        }; // class SetEnabledParamsInfo

        class StopClientConnectionParamsInfo : public Core::JSON::Container {
        public:
            StopClientConnectionParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("mac"), &ClientMac);
                Add(_T("name"), &ClientName);
            }

            bool IsValid() const
            {
                return (true);
            }

            StopClientConnectionParamsInfo(const StopClientConnectionParamsInfo&) = delete;
            StopClientConnectionParamsInfo& operator=(const StopClientConnectionParamsInfo&) = delete;

        public:
            Core::JSON::String ClientMac; // MacAddress of the client device
            Core::JSON::String ClientName; // Name of the client device
        }; // class StopClientConnectionParamsInfo

        // Method params/result classes
        //

        class AcceptClientConnectionParamsData : public Core::JSON::Container {
        public:
            AcceptClientConnectionParamsData()
                : Core::JSON::Container()
            {
                Add(_T("requestStatus"), &RequestStatus);
            }

            bool IsValid() const
            {
                return (true);
            }

            AcceptClientConnectionParamsData(const AcceptClientConnectionParamsData&) = delete;
            AcceptClientConnectionParamsData& operator=(const AcceptClientConnectionParamsData&) = delete;

        public:
            Core::JSON::String RequestStatus; // It should be "Accept" or "Reject"
        }; // class AcceptClientConnectionParamsData

        class GetEnabledResultData : public Core::JSON::Container {
        public:
            GetEnabledResultData()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetEnabledResultData(const GetEnabledResultData&) = delete;
            GetEnabledResultData& operator=(const GetEnabledResultData&) = delete;

        public:
            Core::JSON::Boolean Enabled; // Is the MiracastService discovery enabled or not
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetEnabledResultData

        class OnClientConnectionErrorParamsData : public Core::JSON::Container {
        public:
            OnClientConnectionErrorParamsData()
                : Core::JSON::Container()
            {
                Add(_T("mac"), &ClientMac);
                Add(_T("name"), &ClientName);
                Add(_T("error_code"), &ReasonCode);
                Add(_T("reason"), &ReasonDescription);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnClientConnectionErrorParamsData(const OnClientConnectionErrorParamsData&) = delete;
            OnClientConnectionErrorParamsData& operator=(const OnClientConnectionErrorParamsData&) = delete;

        public:
            Core::JSON::String ClientMac; // MacAddress of the client device
            Core::JSON::String ClientName; // Name of the client device
            Core::JSON::String ReasonCode; // It is triggered when the Miracast Service plugin failed to connect with the source streaming device due to some error, like P2P related errors during activation or while streaming
            Core::JSON::EnumType<Exchange::IMiracastService::ReasonCode> ReasonDescription; // It is triggered when the Miracast Service plugin failed to connect with the source streaming device due to some error, like P2P related errors during activation or while streaming
        }; // class OnClientConnectionErrorParamsData

        class OnLaunchRequestParamsData : public Core::JSON::Container {
        public:
            class DeviceParametersData : public Core::JSON::Container {
            public:
                DeviceParametersData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                DeviceParametersData(const Exchange::IMiracastService::DeviceParameters& _other)
                    : Core::JSON::Container()
                {
                    SourceDeviceIP = _other.sourceDeviceIP;
                    SourceDeviceMac = _other.sourceDeviceMac;
                    SourceDeviceName = _other.sourceDeviceName;
                    SinkDeviceIP = _other.sinkDeviceIP;
                    _Init();
                }

                DeviceParametersData& operator=(const Exchange::IMiracastService::DeviceParameters& _rhs)
                {
                    SourceDeviceIP = _rhs.sourceDeviceIP;
                    SourceDeviceMac = _rhs.sourceDeviceMac;
                    SourceDeviceName = _rhs.sourceDeviceName;
                    SinkDeviceIP = _rhs.sinkDeviceIP;
                    return (*this);
                }

                operator Exchange::IMiracastService::DeviceParameters() const
                {
                    Exchange::IMiracastService::DeviceParameters _value{};
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

            OnLaunchRequestParamsData()
                : Core::JSON::Container()
            {
                Add(_T("device_parameters"), &DeviceParameters);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnLaunchRequestParamsData(const OnLaunchRequestParamsData&) = delete;
            OnLaunchRequestParamsData& operator=(const OnLaunchRequestParamsData&) = delete;

        public:
            OnLaunchRequestParamsData::DeviceParametersData DeviceParameters; // Miracast Service Plugin raises this Event to request RA or MiracastWidget to launch the Miracast Player
        }; // class OnLaunchRequestParamsData

        class UpdatePlayerStateParamsData : public Core::JSON::Container {
        public:
            UpdatePlayerStateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("mac"), &ClientMac);
                Add(_T("state"), &PlayerState);
                Add(_T("reason_code"), &ReasonCode);
            }

            bool IsValid() const
            {
                return (true);
            }

            UpdatePlayerStateParamsData(const UpdatePlayerStateParamsData&) = delete;
            UpdatePlayerStateParamsData& operator=(const UpdatePlayerStateParamsData&) = delete;

        public:
            Core::JSON::String ClientMac; // MacAddress of the client device
            Core::JSON::EnumType<Exchange::IMiracastService::PlayerState> PlayerState; // Player state to be updated
            Core::JSON::DecSInt32 ReasonCode; // Reason code for the player state update
        }; // class UpdatePlayerStateParamsData

    } // namespace MiracastService

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IMiracastService::PlayerState)
ENUM_CONVERSION_HANDLER(Exchange::IMiracastService::ReasonCode)

}

