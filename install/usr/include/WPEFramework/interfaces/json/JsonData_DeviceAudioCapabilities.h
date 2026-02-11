// C++ classes for DeviceAudioCapabilities API JSON-RPC API.
// Generated automatically from 'IDeviceInfo.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IDeviceInfo.h>

namespace WPEFramework {

namespace JsonData {

    namespace DeviceAudioCapabilities {

        // Common classes
        //

        class AudioCapabilitiesParamsInfo : public Core::JSON::Container {
        public:
            AudioCapabilitiesParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("audioPort"), &AudioPort);
            }

            bool IsValid() const
            {
                return (true);
            }

            AudioCapabilitiesParamsInfo(const AudioCapabilitiesParamsInfo&) = delete;
            AudioCapabilitiesParamsInfo& operator=(const AudioCapabilitiesParamsInfo&) = delete;

        public:
            Core::JSON::String AudioPort; // Audio port name
        }; // class AudioCapabilitiesParamsInfo

        // Method params/result classes
        //

        class AudioCapabilitiesResultData : public Core::JSON::Container {
        public:
            AudioCapabilitiesResultData()
                : Core::JSON::Container()
            {
                Add(_T("AudioCapabilities"), &AudioCapabilities);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            AudioCapabilitiesResultData(const AudioCapabilitiesResultData&) = delete;
            AudioCapabilitiesResultData& operator=(const AudioCapabilitiesResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::EnumType<Exchange::IDeviceAudioCapabilities::AudioCapability>> AudioCapabilities; // Audio capability
            Core::JSON::Boolean Success; // Audio capabilities for the specified audio port.
        }; // class AudioCapabilitiesResultData

        class MS12CapabilitiesResultData : public Core::JSON::Container {
        public:
            MS12CapabilitiesResultData()
                : Core::JSON::Container()
            {
                Add(_T("MS12Capabilities"), &MS12Capabilities);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            MS12CapabilitiesResultData(const MS12CapabilitiesResultData&) = delete;
            MS12CapabilitiesResultData& operator=(const MS12CapabilitiesResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::EnumType<Exchange::IDeviceAudioCapabilities::MS12Capability>> MS12Capabilities; // MS12 audio capability
            Core::JSON::Boolean Success; // MS12 audio capabilities for the specified audio port.
        }; // class MS12CapabilitiesResultData

        class SupportedMS12AudioProfilesResultData : public Core::JSON::Container {
        public:
            SupportedMS12AudioProfilesResultData()
                : Core::JSON::Container()
            {
                Add(_T("supportedMS12AudioProfiles"), &SupportedMS12AudioProfiles);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            SupportedMS12AudioProfilesResultData(const SupportedMS12AudioProfilesResultData&) = delete;
            SupportedMS12AudioProfilesResultData& operator=(const SupportedMS12AudioProfilesResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> SupportedMS12AudioProfiles; // MS12 audio profiles
            Core::JSON::Boolean Success; // Supported MS12 audio profiles for the specified audio port.
        }; // class SupportedMS12AudioProfilesResultData

    } // namespace DeviceAudioCapabilities

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IDeviceInfo::DeviceTypeInfo)
ENUM_CONVERSION_HANDLER(Exchange::IDeviceAudioCapabilities::AudioCapability)
ENUM_CONVERSION_HANDLER(Exchange::IDeviceAudioCapabilities::MS12Capability)

}

