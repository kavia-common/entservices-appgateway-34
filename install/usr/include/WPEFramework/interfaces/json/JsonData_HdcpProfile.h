// C++ classes for HdcpProfile API JSON-RPC API.
// Generated automatically from 'IHdcpProfile.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IHdcpProfile.h>

namespace WPEFramework {

namespace JsonData {

    namespace HdcpProfile {

        // Common classes
        //

        class HDCPStatusInfo : public Core::JSON::Container {
        public:
            HDCPStatusInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            HDCPStatusInfo(const Exchange::IHdcpProfile::HDCPStatus& _other)
                : Core::JSON::Container()
            {
                IsConnected = _other.isConnected;
                IsHDCPCompliant = _other.isHDCPCompliant;
                IsHDCPEnabled = _other.isHDCPEnabled;
                HdcpReason = _other.hdcpReason;
                SupportedHDCPVersion = _other.supportedHDCPVersion;
                ReceiverHDCPVersion = _other.receiverHDCPVersion;
                CurrentHDCPVersion = _other.currentHDCPVersion;
                _Init();
            }

            HDCPStatusInfo& operator=(const Exchange::IHdcpProfile::HDCPStatus& _rhs)
            {
                IsConnected = _rhs.isConnected;
                IsHDCPCompliant = _rhs.isHDCPCompliant;
                IsHDCPEnabled = _rhs.isHDCPEnabled;
                HdcpReason = _rhs.hdcpReason;
                SupportedHDCPVersion = _rhs.supportedHDCPVersion;
                ReceiverHDCPVersion = _rhs.receiverHDCPVersion;
                CurrentHDCPVersion = _rhs.currentHDCPVersion;
                return (*this);
            }

            operator Exchange::IHdcpProfile::HDCPStatus() const
            {
                Exchange::IHdcpProfile::HDCPStatus _value{};
                _value.isConnected = IsConnected;
                _value.isHDCPCompliant = IsHDCPCompliant;
                _value.isHDCPEnabled = IsHDCPEnabled;
                _value.hdcpReason = HdcpReason;
                _value.supportedHDCPVersion = SupportedHDCPVersion;
                _value.receiverHDCPVersion = ReceiverHDCPVersion;
                _value.currentHDCPVersion = CurrentHDCPVersion;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("isConnected"), &IsConnected);
                Add(_T("isHDCPCompliant"), &IsHDCPCompliant);
                Add(_T("isHDCPEnabled"), &IsHDCPEnabled);
                Add(_T("hdcpReason"), &HdcpReason);
                Add(_T("supportedHDCPVersion"), &SupportedHDCPVersion);
                Add(_T("receiverHDCPVersion"), &ReceiverHDCPVersion);
                Add(_T("currentHDCPVersion"), &CurrentHDCPVersion);
            }

        public:
            Core::JSON::Boolean IsConnected; // Indicates whether a display is connected
            Core::JSON::Boolean IsHDCPCompliant; // Indicates whether the display is HDCP compliant
            Core::JSON::Boolean IsHDCPEnabled; // Indicates whether content is protected
            Core::JSON::DecUInt32 HdcpReason; // The HDCP status reason
            Core::JSON::String SupportedHDCPVersion; // Supported HDCP protocol version by the host device
            Core::JSON::String ReceiverHDCPVersion; // Supported HDCP protocol version by the receiver device (display)
            Core::JSON::String CurrentHDCPVersion; // Currently used HDCP protocol version
        }; // class HDCPStatusInfo

        // Method params/result classes
        //

        class GetHDCPStatusResultData : public Core::JSON::Container {
        public:
            GetHDCPStatusResultData()
                : Core::JSON::Container()
            {
                Add(_T("HDCPStatus"), &HdcpStatus);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetHDCPStatusResultData(const GetHDCPStatusResultData&) = delete;
            GetHDCPStatusResultData& operator=(const GetHDCPStatusResultData&) = delete;

        public:
            HDCPStatusInfo HdcpStatus; // Returns HDCP-related data.
            Core::JSON::Boolean Success; // Indicates whether the operation was successful
        }; // class GetHDCPStatusResultData

        class GetSettopHDCPSupportResultData : public Core::JSON::Container {
        public:
            GetSettopHDCPSupportResultData()
                : Core::JSON::Container()
            {
                Add(_T("supportedHDCPVersion"), &SupportedHDCPVersion);
                Add(_T("isHDCPSupported"), &IsHDCPSupported);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetSettopHDCPSupportResultData(const GetSettopHDCPSupportResultData&) = delete;
            GetSettopHDCPSupportResultData& operator=(const GetSettopHDCPSupportResultData&) = delete;

        public:
            Core::JSON::String SupportedHDCPVersion; // Supported HDCP protocol version by the host device
            Core::JSON::Boolean IsHDCPSupported; // Indicates whether HDCP is supported by the STB
            Core::JSON::Boolean Success; // Indicates whether the operation was successful
        }; // class GetSettopHDCPSupportResultData

        class OnDisplayConnectionChangedParamsData : public Core::JSON::Container {
        public:
            OnDisplayConnectionChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("HDCPStatus"), &HdcpStatus);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnDisplayConnectionChangedParamsData(const OnDisplayConnectionChangedParamsData&) = delete;
            OnDisplayConnectionChangedParamsData& operator=(const OnDisplayConnectionChangedParamsData&) = delete;

        public:
            HDCPStatusInfo HdcpStatus; // Triggered if HDMI was connected or disconnected upon receiving onHdmiOutputHotPlug
        }; // class OnDisplayConnectionChangedParamsData

    } // namespace HdcpProfile

} // namespace JsonData

}

