// C++ classes for DeviceVideoCapabilities API JSON-RPC API.
// Generated automatically from 'IDeviceInfo.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IDeviceInfo.h>

namespace WPEFramework {

namespace JsonData {

    namespace DeviceVideoCapabilities {

        // Common classes
        //

        class DefaultResolutionParamsInfo : public Core::JSON::Container {
        public:
            DefaultResolutionParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("videoDisplay"), &VideoDisplay);
            }

            bool IsValid() const
            {
                return (true);
            }

            DefaultResolutionParamsInfo(const DefaultResolutionParamsInfo&) = delete;
            DefaultResolutionParamsInfo& operator=(const DefaultResolutionParamsInfo&) = delete;

        public:
            Core::JSON::String VideoDisplay; // Video display port name
        }; // class DefaultResolutionParamsInfo

        // Method params/result classes
        //

        class DefaultReslnData : public Core::JSON::Container {
        public:
            DefaultReslnData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DefaultReslnData(const Exchange::IDeviceVideoCapabilities::DefaultResln& _other)
                : Core::JSON::Container()
            {
                DefaultResolution = _other.defaultResolution;
                _Init();
            }

            DefaultReslnData& operator=(const Exchange::IDeviceVideoCapabilities::DefaultResln& _rhs)
            {
                DefaultResolution = _rhs.defaultResolution;
                return (*this);
            }

            operator Exchange::IDeviceVideoCapabilities::DefaultResln() const
            {
                Exchange::IDeviceVideoCapabilities::DefaultResln _value{};
                _value.defaultResolution = DefaultResolution;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("defaultResolution"), &DefaultResolution);
            }

        public:
            Core::JSON::String DefaultResolution; // Resolution supported by the device
        }; // class DefaultReslnData

        class HostEdidData : public Core::JSON::Container {
        public:
            HostEdidData()
                : Core::JSON::Container()
            {
                _Init();
            }

            HostEdidData(const Exchange::IDeviceVideoCapabilities::HostEdid& _other)
                : Core::JSON::Container()
            {
                EDID = _other.EDID;
                _Init();
            }

            HostEdidData& operator=(const Exchange::IDeviceVideoCapabilities::HostEdid& _rhs)
            {
                EDID = _rhs.EDID;
                return (*this);
            }

            operator Exchange::IDeviceVideoCapabilities::HostEdid() const
            {
                Exchange::IDeviceVideoCapabilities::HostEdid _value{};
                _value.EDID = EDID;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("EDID"), &EDID);
            }

        public:
            Core::JSON::String EDID; // A base64 encoded byte array string representing the EDID
        }; // class HostEdidData

        class SupportedHDCPVerData : public Core::JSON::Container {
        public:
            SupportedHDCPVerData()
                : Core::JSON::Container()
            {
                _Init();
            }

            SupportedHDCPVerData(const Exchange::IDeviceVideoCapabilities::SupportedHDCPVer& _other)
                : Core::JSON::Container()
            {
                SupportedHDCPVersion = _other.supportedHDCPVersion;
                _Init();
            }

            SupportedHDCPVerData& operator=(const Exchange::IDeviceVideoCapabilities::SupportedHDCPVer& _rhs)
            {
                SupportedHDCPVersion = _rhs.supportedHDCPVersion;
                return (*this);
            }

            operator Exchange::IDeviceVideoCapabilities::SupportedHDCPVer() const
            {
                Exchange::IDeviceVideoCapabilities::SupportedHDCPVer _value{};
                _value.supportedHDCPVersion = SupportedHDCPVersion;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("supportedHDCPVersion"), &SupportedHDCPVersion);
            }

        public:
            Core::JSON::EnumType<Exchange::IDeviceVideoCapabilities::CopyProtection> SupportedHDCPVersion; // HDCP support (must be one of the following: unavailable, 1.4, 2.0, 2.1, 2.2)
        }; // class SupportedHDCPVerData

        class SupportedResolutionsResultData : public Core::JSON::Container {
        public:
            SupportedResolutionsResultData()
                : Core::JSON::Container()
            {
                Add(_T("supportedResolutions"), &SupportedResolutions);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            SupportedResolutionsResultData(const SupportedResolutionsResultData&) = delete;
            SupportedResolutionsResultData& operator=(const SupportedResolutionsResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> SupportedResolutions; // Supported Resolutions
            Core::JSON::Boolean Success; // Supported resolutions on the selected video display port.
        }; // class SupportedResolutionsResultData

        class SupportedVideoDisplaysResultData : public Core::JSON::Container {
        public:
            SupportedVideoDisplaysResultData()
                : Core::JSON::Container()
            {
                Add(_T("supportedVideoDisplays"), &SupportedVideoDisplays);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            SupportedVideoDisplaysResultData(const SupportedVideoDisplaysResultData&) = delete;
            SupportedVideoDisplaysResultData& operator=(const SupportedVideoDisplaysResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> SupportedVideoDisplays; // Video ports supported on the device
            Core::JSON::Boolean Success; // Provides access to the video ports supported on the device.
        }; // class SupportedVideoDisplaysResultData

    } // namespace DeviceVideoCapabilities

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IDeviceInfo::DeviceTypeInfo)
ENUM_CONVERSION_HANDLER(Exchange::IDeviceAudioCapabilities::AudioCapability)
ENUM_CONVERSION_HANDLER(Exchange::IDeviceAudioCapabilities::MS12Capability)
ENUM_CONVERSION_HANDLER(Exchange::IDeviceVideoCapabilities::CopyProtection)

}

