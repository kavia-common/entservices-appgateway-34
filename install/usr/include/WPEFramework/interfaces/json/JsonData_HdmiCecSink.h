// C++ classes for HdmiCecSink API JSON-RPC API.
// Generated automatically from 'IHdmiCecSink.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IHdmiCecSink.h>

namespace WPEFramework {

namespace JsonData {

    namespace HdmiCecSink {

        // Common classes
        //

        class ArcInitiationEventParamsInfo : public Core::JSON::Container {
        public:
            ArcInitiationEventParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
            }

            bool IsValid() const
            {
                return (true);
            }

            ArcInitiationEventParamsInfo(const ArcInitiationEventParamsInfo&) = delete;
            ArcInitiationEventParamsInfo& operator=(const ArcInitiationEventParamsInfo&) = delete;

        public:
            Core::JSON::String Status; // Is the operation successful or not
        }; // class ArcInitiationEventParamsInfo

        class HdmiCecSinkSuccessInfo : public Core::JSON::Container {
        public:
            HdmiCecSinkSuccessInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            HdmiCecSinkSuccessInfo(const Exchange::IHdmiCecSink::HdmiCecSinkSuccess& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            HdmiCecSinkSuccessInfo& operator=(const Exchange::IHdmiCecSink::HdmiCecSinkSuccess& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IHdmiCecSink::HdmiCecSinkSuccess() const
            {
                Exchange::IHdmiCecSink::HdmiCecSinkSuccess _value{};
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
            Core::JSON::Boolean Success; // Request the active source in the network
        }; // class HdmiCecSinkSuccessInfo

        class OnActiveSourceChangeParamsInfo : public Core::JSON::Container {
        public:
            OnActiveSourceChangeParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("logicalAddress"), &LogicalAddress);
                Add(_T("physicalAddress"), &PhysicalAddress);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnActiveSourceChangeParamsInfo(const OnActiveSourceChangeParamsInfo&) = delete;
            OnActiveSourceChangeParamsInfo& operator=(const OnActiveSourceChangeParamsInfo&) = delete;

        public:
            Core::JSON::DecSInt32 LogicalAddress; // Logical address of the active source
            Core::JSON::String PhysicalAddress; // Physical address of the active source
        }; // class OnActiveSourceChangeParamsInfo

        class OnDeviceAddedParamsInfo : public Core::JSON::Container {
        public:
            OnDeviceAddedParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("logicalAddress"), &LogicalAddress);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnDeviceAddedParamsInfo(const OnDeviceAddedParamsInfo&) = delete;
            OnDeviceAddedParamsInfo& operator=(const OnDeviceAddedParamsInfo&) = delete;

        public:
            Core::JSON::DecSInt32 LogicalAddress; // Logical address of the added device
        }; // class OnDeviceAddedParamsInfo

        class SendKeyPressEventParamsInfo : public Core::JSON::Container {
        public:
            SendKeyPressEventParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("logicalAddress"), &LogicalAddress);
                Add(_T("keyCode"), &KeyCode);
            }

            bool IsValid() const
            {
                return (true);
            }

            SendKeyPressEventParamsInfo(const SendKeyPressEventParamsInfo&) = delete;
            SendKeyPressEventParamsInfo& operator=(const SendKeyPressEventParamsInfo&) = delete;

        public:
            Core::JSON::DecUInt32 LogicalAddress; // Logical address of the device
            Core::JSON::DecUInt32 KeyCode; // Key code of the key press event
        }; // class SendKeyPressEventParamsInfo

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
            Core::JSON::Boolean Enabled; // Is the HDMI CEC Sink enabled or not
        }; // class SetEnabledParamsInfo

        // Method params/result classes
        //

        class GetActiveRouteResultData : public Core::JSON::Container {
        public:
            class HdmiCecSinkActivePathData : public Core::JSON::Container {
            public:
                HdmiCecSinkActivePathData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                HdmiCecSinkActivePathData(const HdmiCecSinkActivePathData& _other)
                    : Core::JSON::Container()
                    , LogicalAddress(_other.LogicalAddress)
                    , PhysicalAddress(_other.PhysicalAddress)
                    , DeviceType(_other.DeviceType)
                    , VendorID(_other.VendorID)
                    , OsdName(_other.OsdName)
                {
                    _Init();
                }

                HdmiCecSinkActivePathData& operator=(const HdmiCecSinkActivePathData& _rhs)
                {
                    LogicalAddress = _rhs.LogicalAddress;
                    PhysicalAddress = _rhs.PhysicalAddress;
                    DeviceType = _rhs.DeviceType;
                    VendorID = _rhs.VendorID;
                    OsdName = _rhs.OsdName;
                    return (*this);
                }

                HdmiCecSinkActivePathData(const Exchange::IHdmiCecSink::HdmiCecSinkActivePath& _other)
                    : Core::JSON::Container()
                {
                    LogicalAddress = _other.logicalAddress;
                    PhysicalAddress = _other.physicalAddress;
                    DeviceType = _other.deviceType;
                    VendorID = _other.vendorID;
                    OsdName = _other.osdName;
                    _Init();
                }

                HdmiCecSinkActivePathData& operator=(const Exchange::IHdmiCecSink::HdmiCecSinkActivePath& _rhs)
                {
                    LogicalAddress = _rhs.logicalAddress;
                    PhysicalAddress = _rhs.physicalAddress;
                    DeviceType = _rhs.deviceType;
                    VendorID = _rhs.vendorID;
                    OsdName = _rhs.osdName;
                    return (*this);
                }

                operator Exchange::IHdmiCecSink::HdmiCecSinkActivePath() const
                {
                    Exchange::IHdmiCecSink::HdmiCecSinkActivePath _value{};
                    _value.logicalAddress = LogicalAddress;
                    _value.physicalAddress = PhysicalAddress;
                    _value.deviceType = DeviceType;
                    _value.vendorID = VendorID;
                    _value.osdName = OsdName;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("logicalAddress"), &LogicalAddress);
                    Add(_T("physicalAddress"), &PhysicalAddress);
                    Add(_T("deviceType"), &DeviceType);
                    Add(_T("vendorID"), &VendorID);
                    Add(_T("osdName"), &OsdName);
                }

            public:
                Core::JSON::DecUInt8 LogicalAddress;
                Core::JSON::String PhysicalAddress;
                Core::JSON::String DeviceType;
                Core::JSON::String VendorID;
                Core::JSON::String OsdName;
            }; // class HdmiCecSinkActivePathData

            GetActiveRouteResultData()
                : Core::JSON::Container()
            {
                Add(_T("available"), &Available);
                Add(_T("length"), &Length);
                Add(_T("pathList"), &PathList);
                Add(_T("ActiveRoute"), &ActiveRoute);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetActiveRouteResultData(const GetActiveRouteResultData&) = delete;
            GetActiveRouteResultData& operator=(const GetActiveRouteResultData&) = delete;

        public:
            Core::JSON::Boolean Available; // Is the active route available or not
            Core::JSON::DecUInt8 Length; // Length of the active route
            Core::JSON::ArrayType<GetActiveRouteResultData::HdmiCecSinkActivePathData> PathList; // List of active path
            Core::JSON::String ActiveRoute; // Active route of the device
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetActiveRouteResultData

        class GetActiveSourceResultData : public Core::JSON::Container {
        public:
            GetActiveSourceResultData()
                : Core::JSON::Container()
            {
                Add(_T("available"), &Available);
                Add(_T("logicalAddress"), &LogicalAddress);
                Add(_T("physicalAddress"), &PhysicalAddress);
                Add(_T("deviceType"), &DeviceType);
                Add(_T("cecVersion"), &CecVersion);
                Add(_T("osdName"), &OsdName);
                Add(_T("vendorID"), &VendorID);
                Add(_T("powerStatus"), &PowerStatus);
                Add(_T("port"), &Port);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetActiveSourceResultData(const GetActiveSourceResultData&) = delete;
            GetActiveSourceResultData& operator=(const GetActiveSourceResultData&) = delete;

        public:
            Core::JSON::Boolean Available; // Is the active source available or not
            Core::JSON::DecUInt8 LogicalAddress; // Logical address of the active source
            Core::JSON::String PhysicalAddress; // Physical address of the active source
            Core::JSON::String DeviceType; // Device type of the active source
            Core::JSON::String CecVersion; // CEC version of the active source
            Core::JSON::String OsdName; // OSD name of the active source
            Core::JSON::String VendorID; // Vendor ID of the active source
            Core::JSON::String PowerStatus; // Power status of the active source
            Core::JSON::String Port; // Gets the status of the current active source
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetActiveSourceResultData

        class GetAudioDeviceConnectedStatusResultData : public Core::JSON::Container {
        public:
            GetAudioDeviceConnectedStatusResultData()
                : Core::JSON::Container()
            {
                Add(_T("connected"), &Connected);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetAudioDeviceConnectedStatusResultData(const GetAudioDeviceConnectedStatusResultData&) = delete;
            GetAudioDeviceConnectedStatusResultData& operator=(const GetAudioDeviceConnectedStatusResultData&) = delete;

        public:
            Core::JSON::Boolean Connected; // Is the audio device connected or not
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetAudioDeviceConnectedStatusResultData

        class GetDeviceListResultData : public Core::JSON::Container {
        public:
            class HdmiCecSinkDevicesData : public Core::JSON::Container {
            public:
                HdmiCecSinkDevicesData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                HdmiCecSinkDevicesData(const HdmiCecSinkDevicesData& _other)
                    : Core::JSON::Container()
                    , LogicalAddress(_other.LogicalAddress)
                    , PhysicalAddress(_other.PhysicalAddress)
                    , DeviceType(_other.DeviceType)
                    , CecVersion(_other.CecVersion)
                    , OsdName(_other.OsdName)
                    , VendorID(_other.VendorID)
                    , PowerStatus(_other.PowerStatus)
                    , PortNumber(_other.PortNumber)
                {
                    _Init();
                }

                HdmiCecSinkDevicesData& operator=(const HdmiCecSinkDevicesData& _rhs)
                {
                    LogicalAddress = _rhs.LogicalAddress;
                    PhysicalAddress = _rhs.PhysicalAddress;
                    DeviceType = _rhs.DeviceType;
                    CecVersion = _rhs.CecVersion;
                    OsdName = _rhs.OsdName;
                    VendorID = _rhs.VendorID;
                    PowerStatus = _rhs.PowerStatus;
                    PortNumber = _rhs.PortNumber;
                    return (*this);
                }

                HdmiCecSinkDevicesData(const Exchange::IHdmiCecSink::HdmiCecSinkDevices& _other)
                    : Core::JSON::Container()
                {
                    LogicalAddress = _other.logicalAddress;
                    PhysicalAddress = _other.physicalAddress;
                    DeviceType = _other.deviceType;
                    CecVersion = _other.cecVersion;
                    OsdName = _other.osdName;
                    VendorID = _other.vendorID;
                    PowerStatus = _other.powerStatus;
                    PortNumber = _other.portNumber;
                    _Init();
                }

                HdmiCecSinkDevicesData& operator=(const Exchange::IHdmiCecSink::HdmiCecSinkDevices& _rhs)
                {
                    LogicalAddress = _rhs.logicalAddress;
                    PhysicalAddress = _rhs.physicalAddress;
                    DeviceType = _rhs.deviceType;
                    CecVersion = _rhs.cecVersion;
                    OsdName = _rhs.osdName;
                    VendorID = _rhs.vendorID;
                    PowerStatus = _rhs.powerStatus;
                    PortNumber = _rhs.portNumber;
                    return (*this);
                }

                operator Exchange::IHdmiCecSink::HdmiCecSinkDevices() const
                {
                    Exchange::IHdmiCecSink::HdmiCecSinkDevices _value{};
                    _value.logicalAddress = LogicalAddress;
                    _value.physicalAddress = PhysicalAddress;
                    _value.deviceType = DeviceType;
                    _value.cecVersion = CecVersion;
                    _value.osdName = OsdName;
                    _value.vendorID = VendorID;
                    _value.powerStatus = PowerStatus;
                    _value.portNumber = PortNumber;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("logicalAddress"), &LogicalAddress);
                    Add(_T("physicalAddress"), &PhysicalAddress);
                    Add(_T("deviceType"), &DeviceType);
                    Add(_T("cecVersion"), &CecVersion);
                    Add(_T("osdName"), &OsdName);
                    Add(_T("vendorID"), &VendorID);
                    Add(_T("powerStatus"), &PowerStatus);
                    Add(_T("portNumber"), &PortNumber);
                }

            public:
                Core::JSON::DecUInt8 LogicalAddress;
                Core::JSON::String PhysicalAddress;
                Core::JSON::String DeviceType;
                Core::JSON::String CecVersion;
                Core::JSON::String OsdName;
                Core::JSON::String VendorID;
                Core::JSON::String PowerStatus;
                Core::JSON::String PortNumber;
            }; // class HdmiCecSinkDevicesData

            GetDeviceListResultData()
                : Core::JSON::Container()
            {
                Add(_T("numberofdevices"), &Numberofdevices);
                Add(_T("deviceList"), &DeviceList);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetDeviceListResultData(const GetDeviceListResultData&) = delete;
            GetDeviceListResultData& operator=(const GetDeviceListResultData&) = delete;

        public:
            Core::JSON::DecUInt32 Numberofdevices; // Number of devices connected to the HDMI CEC sink
            Core::JSON::ArrayType<GetDeviceListResultData::HdmiCecSinkDevicesData> DeviceList; // List of devices connected to the HDMI CEC sink
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetDeviceListResultData

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
            Core::JSON::Boolean Enabled; // Is the HDMI CEC Sink enabled or not
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetEnabledResultData

        class GetOSDNameResultData : public Core::JSON::Container {
        public:
            GetOSDNameResultData()
                : Core::JSON::Container()
            {
                Add(_T("name"), &Name);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetOSDNameResultData(const GetOSDNameResultData&) = delete;
            GetOSDNameResultData& operator=(const GetOSDNameResultData&) = delete;

        public:
            Core::JSON::String Name; // OSD name of the HDMI CEC Sink
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetOSDNameResultData

        class GetVendorIdResultData : public Core::JSON::Container {
        public:
            GetVendorIdResultData()
                : Core::JSON::Container()
            {
                Add(_T("vendorid"), &Vendorid);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetVendorIdResultData(const GetVendorIdResultData&) = delete;
            GetVendorIdResultData& operator=(const GetVendorIdResultData&) = delete;

        public:
            Core::JSON::String Vendorid; // Vendor ID of the HDMI CEC Sink
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetVendorIdResultData

        class PrintDeviceListResultData : public Core::JSON::Container {
        public:
            PrintDeviceListResultData()
                : Core::JSON::Container()
            {
                Add(_T("printed"), &Printed);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            PrintDeviceListResultData(const PrintDeviceListResultData&) = delete;
            PrintDeviceListResultData& operator=(const PrintDeviceListResultData&) = delete;

        public:
            Core::JSON::Boolean Printed; // Is the device list printed or not
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class PrintDeviceListResultData

        class ReportAudioDeviceConnectedStatusParamsData : public Core::JSON::Container {
        public:
            ReportAudioDeviceConnectedStatusParamsData()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
                Add(_T("audioDeviceConnected"), &AudioDeviceConnected);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReportAudioDeviceConnectedStatusParamsData(const ReportAudioDeviceConnectedStatusParamsData&) = delete;
            ReportAudioDeviceConnectedStatusParamsData& operator=(const ReportAudioDeviceConnectedStatusParamsData&) = delete;

        public:
            Core::JSON::String Status; // Status of the audio device
            Core::JSON::String AudioDeviceConnected; // Audio device connected or not
        }; // class ReportAudioDeviceConnectedStatusParamsData

        class ReportAudioDevicePowerStatusParamsData : public Core::JSON::Container {
        public:
            ReportAudioDevicePowerStatusParamsData()
                : Core::JSON::Container()
            {
                Add(_T("powerStatus"), &PowerStatus);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReportAudioDevicePowerStatusParamsData(const ReportAudioDevicePowerStatusParamsData&) = delete;
            ReportAudioDevicePowerStatusParamsData& operator=(const ReportAudioDevicePowerStatusParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 PowerStatus; // Power status of the device
        }; // class ReportAudioDevicePowerStatusParamsData

        class ReportAudioStatusEventParamsData : public Core::JSON::Container {
        public:
            ReportAudioStatusEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("muteStatus"), &MuteStatus);
                Add(_T("volumeLevel"), &VolumeLevel);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReportAudioStatusEventParamsData(const ReportAudioStatusEventParamsData&) = delete;
            ReportAudioStatusEventParamsData& operator=(const ReportAudioStatusEventParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 MuteStatus; // Mute status of the device
            Core::JSON::DecSInt32 VolumeLevel; // Volume level of the device
        }; // class ReportAudioStatusEventParamsData

        class ReportCecEnabledEventParamsData : public Core::JSON::Container {
        public:
            ReportCecEnabledEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("cecEnable"), &CecEnable);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReportCecEnabledEventParamsData(const ReportCecEnabledEventParamsData&) = delete;
            ReportCecEnabledEventParamsData& operator=(const ReportCecEnabledEventParamsData&) = delete;

        public:
            Core::JSON::String CecEnable; // HDMI-CEC enabled or not
        }; // class ReportCecEnabledEventParamsData

        class ReportFeatureAbortEventParamsData : public Core::JSON::Container {
        public:
            ReportFeatureAbortEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("logicalAddress"), &LogicalAddress);
                Add(_T("opcode"), &Opcode);
                Add(_T("FeatureAbortReason"), &FeatureAbortReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReportFeatureAbortEventParamsData(const ReportFeatureAbortEventParamsData&) = delete;
            ReportFeatureAbortEventParamsData& operator=(const ReportFeatureAbortEventParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 LogicalAddress; // Logical address of the device
            Core::JSON::DecSInt32 Opcode; // Opcode of the message
            Core::JSON::DecSInt32 FeatureAbortReason; // Reason for the feature abort
        }; // class ReportFeatureAbortEventParamsData

        class SendUserControlReleasedParamsData : public Core::JSON::Container {
        public:
            SendUserControlReleasedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("logicalAddress"), &LogicalAddress);
            }

            bool IsValid() const
            {
                return (true);
            }

            SendUserControlReleasedParamsData(const SendUserControlReleasedParamsData&) = delete;
            SendUserControlReleasedParamsData& operator=(const SendUserControlReleasedParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 LogicalAddress; // Logical address of the device
        }; // class SendUserControlReleasedParamsData

        class SetActivePathParamsData : public Core::JSON::Container {
        public:
            SetActivePathParamsData()
                : Core::JSON::Container()
            {
                Add(_T("activePath"), &ActivePath);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetActivePathParamsData(const SetActivePathParamsData&) = delete;
            SetActivePathParamsData& operator=(const SetActivePathParamsData&) = delete;

        public:
            Core::JSON::String ActivePath; // Active path of the device
        }; // class SetActivePathParamsData

        class SetLatencyInfoParamsData : public Core::JSON::Container {
        public:
            SetLatencyInfoParamsData()
                : Core::JSON::Container()
            {
                Add(_T("videoLatency"), &VideoLatency);
                Add(_T("lowLatencyMode"), &LowLatencyMode);
                Add(_T("audioOutputCompensated"), &AudioOutputCompensated);
                Add(_T("audioOutputDelay"), &AudioOutputDelay);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetLatencyInfoParamsData(const SetLatencyInfoParamsData&) = delete;
            SetLatencyInfoParamsData& operator=(const SetLatencyInfoParamsData&) = delete;

        public:
            Core::JSON::String VideoLatency; // Video Latency value
            Core::JSON::String LowLatencyMode; // Low Latency Mode value
            Core::JSON::String AudioOutputCompensated; // Audio Output Compensated value
            Core::JSON::String AudioOutputDelay; // Audio Output Delay value
        }; // class SetLatencyInfoParamsData

        class SetMenuLanguageParamsData : public Core::JSON::Container {
        public:
            SetMenuLanguageParamsData()
                : Core::JSON::Container()
            {
                Add(_T("language"), &Language);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetMenuLanguageParamsData(const SetMenuLanguageParamsData&) = delete;
            SetMenuLanguageParamsData& operator=(const SetMenuLanguageParamsData&) = delete;

        public:
            Core::JSON::String Language; // Menu language to be set
        }; // class SetMenuLanguageParamsData

        class SetOSDNameParamsData : public Core::JSON::Container {
        public:
            SetOSDNameParamsData()
                : Core::JSON::Container()
            {
                Add(_T("name"), &Name);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetOSDNameParamsData(const SetOSDNameParamsData&) = delete;
            SetOSDNameParamsData& operator=(const SetOSDNameParamsData&) = delete;

        public:
            Core::JSON::String Name; // Sets the OSD name of the HDMI CEC Sink
        }; // class SetOSDNameParamsData

        class SetRoutingChangeParamsData : public Core::JSON::Container {
        public:
            SetRoutingChangeParamsData()
                : Core::JSON::Container()
            {
                Add(_T("oldPort"), &OldPort);
                Add(_T("newPort"), &NewPort);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetRoutingChangeParamsData(const SetRoutingChangeParamsData&) = delete;
            SetRoutingChangeParamsData& operator=(const SetRoutingChangeParamsData&) = delete;

        public:
            Core::JSON::String OldPort; // Old port number
            Core::JSON::String NewPort; // New port number
        }; // class SetRoutingChangeParamsData

        class SetSystemAudioModeEventParamsData : public Core::JSON::Container {
        public:
            SetSystemAudioModeEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("audioMode"), &AudioMode);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetSystemAudioModeEventParamsData(const SetSystemAudioModeEventParamsData&) = delete;
            SetSystemAudioModeEventParamsData& operator=(const SetSystemAudioModeEventParamsData&) = delete;

        public:
            Core::JSON::String AudioMode; // Audio mode of the device
        }; // class SetSystemAudioModeEventParamsData

        class SetVendorIdParamsData : public Core::JSON::Container {
        public:
            SetVendorIdParamsData()
                : Core::JSON::Container()
            {
                Add(_T("vendorid"), &Vendorid);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetVendorIdParamsData(const SetVendorIdParamsData&) = delete;
            SetVendorIdParamsData& operator=(const SetVendorIdParamsData&) = delete;

        public:
            Core::JSON::String Vendorid; // Sets the vendor ID of the HDMI CEC Sink
        }; // class SetVendorIdParamsData

        class ShortAudiodescriptorEventParamsData : public Core::JSON::Container {
        public:
            ShortAudiodescriptorEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("shortAudioDescriptor"), &ShortAudioDescriptor);
            }

            bool IsValid() const
            {
                return (true);
            }

            ShortAudiodescriptorEventParamsData(const ShortAudiodescriptorEventParamsData&) = delete;
            ShortAudiodescriptorEventParamsData& operator=(const ShortAudiodescriptorEventParamsData&) = delete;

        public:
            Core::JSON::String ShortAudioDescriptor; // JSON response containing the Short Audio Descriptor (SAD) information
        }; // class ShortAudiodescriptorEventParamsData

    } // namespace HdmiCecSink

} // namespace JsonData

}

