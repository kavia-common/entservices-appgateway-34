// C++ classes for HdmiCecSource API JSON-RPC API.
// Generated automatically from 'IHdmiCecSource.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IHdmiCecSource.h>

namespace WPEFramework {

namespace JsonData {

    namespace HdmiCecSource {

        // Common classes
        //

        class GetEnabledResultInfo : public Core::JSON::Container {
        public:
            GetEnabledResultInfo()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetEnabledResultInfo(const GetEnabledResultInfo&) = delete;
            GetEnabledResultInfo& operator=(const GetEnabledResultInfo&) = delete;

        public:
            Core::JSON::Boolean Enabled; // Is the HDMI CEC source enabled or not
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetEnabledResultInfo

        class HdmiCecSourceSuccessInfo : public Core::JSON::Container {
        public:
            HdmiCecSourceSuccessInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            HdmiCecSourceSuccessInfo(const Exchange::IHdmiCecSource::HdmiCecSourceSuccess& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            HdmiCecSourceSuccessInfo& operator=(const Exchange::IHdmiCecSource::HdmiCecSourceSuccess& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IHdmiCecSource::HdmiCecSourceSuccess() const
            {
                Exchange::IHdmiCecSource::HdmiCecSourceSuccess _value{};
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
            Core::JSON::Boolean Success; // Performs the OTP action
        }; // class HdmiCecSourceSuccessInfo

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
            Core::JSON::Boolean Enabled; // Is the HDMI CEC source enabled or not
        }; // class SetEnabledParamsInfo

        // Method params/result classes
        //

        class GetActiveSourceStatusResultData : public Core::JSON::Container {
        public:
            GetActiveSourceStatusResultData()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetActiveSourceStatusResultData(const GetActiveSourceStatusResultData&) = delete;
            GetActiveSourceStatusResultData& operator=(const GetActiveSourceStatusResultData&) = delete;

        public:
            Core::JSON::Boolean Status; // Is the active source active or not
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetActiveSourceStatusResultData

        class GetDeviceListResultData : public Core::JSON::Container {
        public:
            class HdmiCecSourceDevicesData : public Core::JSON::Container {
            public:
                HdmiCecSourceDevicesData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                HdmiCecSourceDevicesData(const HdmiCecSourceDevicesData& _other)
                    : Core::JSON::Container()
                    , LogicalAddress(_other.LogicalAddress)
                    , VendorID(_other.VendorID)
                    , OsdName(_other.OsdName)
                {
                    _Init();
                }

                HdmiCecSourceDevicesData& operator=(const HdmiCecSourceDevicesData& _rhs)
                {
                    LogicalAddress = _rhs.LogicalAddress;
                    VendorID = _rhs.VendorID;
                    OsdName = _rhs.OsdName;
                    return (*this);
                }

                HdmiCecSourceDevicesData(const Exchange::IHdmiCecSource::HdmiCecSourceDevices& _other)
                    : Core::JSON::Container()
                {
                    LogicalAddress = _other.logicalAddress;
                    VendorID = _other.vendorID;
                    OsdName = _other.osdName;
                    _Init();
                }

                HdmiCecSourceDevicesData& operator=(const Exchange::IHdmiCecSource::HdmiCecSourceDevices& _rhs)
                {
                    LogicalAddress = _rhs.logicalAddress;
                    VendorID = _rhs.vendorID;
                    OsdName = _rhs.osdName;
                    return (*this);
                }

                operator Exchange::IHdmiCecSource::HdmiCecSourceDevices() const
                {
                    Exchange::IHdmiCecSource::HdmiCecSourceDevices _value{};
                    _value.logicalAddress = LogicalAddress;
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
                    Add(_T("vendorID"), &VendorID);
                    Add(_T("osdName"), &OsdName);
                }

            public:
                Core::JSON::DecUInt8 LogicalAddress;
                Core::JSON::String VendorID;
                Core::JSON::String OsdName;
            }; // class HdmiCecSourceDevicesData

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
            Core::JSON::DecUInt32 Numberofdevices; // Number of devices connected to the HDMI CEC source
            Core::JSON::ArrayType<GetDeviceListResultData::HdmiCecSourceDevicesData> DeviceList; // List of devices connected to the HDMI CEC source
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetDeviceListResultData

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
            Core::JSON::String Name; // OSD name of the HDMI CEC source
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
            Core::JSON::String Vendorid; // Gets the vendor ID of the HDMI CEC source
            Core::JSON::Boolean Success; // Is the operation successful or not
        }; // class GetVendorIdResultData

        class OnActiveSourceStatusUpdatedParamsData : public Core::JSON::Container {
        public:
            OnActiveSourceStatusUpdatedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnActiveSourceStatusUpdatedParamsData(const OnActiveSourceStatusUpdatedParamsData&) = delete;
            OnActiveSourceStatusUpdatedParamsData& operator=(const OnActiveSourceStatusUpdatedParamsData&) = delete;

        public:
            Core::JSON::Boolean Status; // Notifies when the active source status is updated
        }; // class OnActiveSourceStatusUpdatedParamsData

        class OnKeyPressEventParamsData : public Core::JSON::Container {
        public:
            OnKeyPressEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("logicalAddress"), &LogicalAddress);
                Add(_T("keyCode"), &KeyCode);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnKeyPressEventParamsData(const OnKeyPressEventParamsData&) = delete;
            OnKeyPressEventParamsData& operator=(const OnKeyPressEventParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 LogicalAddress; // Logical address of the device
            Core::JSON::DecSInt32 KeyCode; // Key code of the key press event
        }; // class OnKeyPressEventParamsData

        class SendKeyPressEventParamsData : public Core::JSON::Container {
        public:
            SendKeyPressEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("logicalAddress"), &LogicalAddress);
                Add(_T("keyCode"), &KeyCode);
            }

            bool IsValid() const
            {
                return (true);
            }

            SendKeyPressEventParamsData(const SendKeyPressEventParamsData&) = delete;
            SendKeyPressEventParamsData& operator=(const SendKeyPressEventParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 LogicalAddress; // Logical address of the device
            Core::JSON::DecUInt32 KeyCode; // Key code of the key press event
        }; // class SendKeyPressEventParamsData

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
            Core::JSON::String Name; // Sets the OSD name of the HDMI CEC source
        }; // class SetOSDNameParamsData

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
            Core::JSON::String Vendorid; // Sets the vendor ID of the HDMI CEC source
        }; // class SetVendorIdParamsData

    } // namespace HdmiCecSource

} // namespace JsonData

}

