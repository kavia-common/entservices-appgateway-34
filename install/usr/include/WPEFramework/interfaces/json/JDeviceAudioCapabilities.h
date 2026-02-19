// Generated automatically from 'IDeviceInfo.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_DeviceAudioCapabilities.h"
#include <interfaces/IDeviceInfo.h>

namespace WPEFramework {

namespace Exchange {

    namespace JDeviceAudioCapabilities {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IDeviceAudioCapabilities* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JDeviceAudioCapabilities"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'audiocapabilities' - Audio capabilities for the specified audio port (DEPRECATED)
            _module_.Register<JsonData::DeviceAudioCapabilities::AudioCapabilitiesParamsInfo,
                     JsonData::DeviceAudioCapabilities::AudioCapabilitiesResultData>(_T("audiocapabilities"), 
                [_impl_](const JsonData::DeviceAudioCapabilities::AudioCapabilitiesParamsInfo& params,
                         JsonData::DeviceAudioCapabilities::AudioCapabilitiesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _audioPort{params.AudioPort};
                    ::WPEFramework::RPC::IIteratorType<IDeviceAudioCapabilities::AudioCapability,
                             ID_DEVICE_CAPABILITIES_AUDIO_CAPABILITY>* _audioCapabilities{};
                    bool _success{};

                    _errorCode = _impl_->AudioCapabilities(_audioPort, _audioCapabilities, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_audioCapabilities != nullptr) {
                            Exchange::IDeviceAudioCapabilities::AudioCapability _audioCapabilitiesItem_{};
                            while (_audioCapabilities->Next(_audioCapabilitiesItem_) == true) { result.AudioCapabilities.Add() = _audioCapabilitiesItem_; }
                            _audioCapabilities->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'ms12capabilities' - MS12 audio capabilities for the specified audio port (DEPRECATED)
            _module_.Register<JsonData::DeviceAudioCapabilities::AudioCapabilitiesParamsInfo,
                     JsonData::DeviceAudioCapabilities::MS12CapabilitiesResultData>(_T("ms12capabilities"), 
                [_impl_](const JsonData::DeviceAudioCapabilities::AudioCapabilitiesParamsInfo& params,
                         JsonData::DeviceAudioCapabilities::MS12CapabilitiesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _audioPort{params.AudioPort};
                    ::WPEFramework::RPC::IIteratorType<IDeviceAudioCapabilities::MS12Capability,
                             ID_DEVICE_CAPABILITIES_AUDIO_MS12_CAPABILITY>* _mS12Capabilities{};
                    bool _success{};

                    _errorCode = _impl_->MS12Capabilities(_audioPort, _mS12Capabilities, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_mS12Capabilities != nullptr) {
                            Exchange::IDeviceAudioCapabilities::MS12Capability _mS12CapabilitiesItem_{};
                            while (_mS12Capabilities->Next(_mS12CapabilitiesItem_) == true) { result.MS12Capabilities.Add() = _mS12CapabilitiesItem_; }
                            _mS12Capabilities->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'supportedms12audioprofiles' - Supported MS12 audio profiles for the specified audio port (DEPRECATED)
            _module_.Register<JsonData::DeviceAudioCapabilities::AudioCapabilitiesParamsInfo,
                     JsonData::DeviceAudioCapabilities::SupportedMS12AudioProfilesResultData>(_T("supportedms12audioprofiles"), 
                [_impl_](const JsonData::DeviceAudioCapabilities::AudioCapabilitiesParamsInfo& params,
                         JsonData::DeviceAudioCapabilities::SupportedMS12AudioProfilesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _audioPort{params.AudioPort};
                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _supportedMS12AudioProfiles{};
                    bool _success{};

                    _errorCode = _impl_->SupportedMS12AudioProfiles(_audioPort, _supportedMS12AudioProfiles, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_supportedMS12AudioProfiles != nullptr) {
                            string _supportedMS12AudioProfilesItem_{};
                            while (_supportedMS12AudioProfiles->Next(_supportedMS12AudioProfilesItem_) == true) { result.SupportedMS12AudioProfiles.Add() = _supportedMS12AudioProfilesItem_; }
                            _supportedMS12AudioProfiles->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("audiocapabilities"));
            _module_.Unregister(_T("ms12capabilities"));
            _module_.Unregister(_T("supportedms12audioprofiles"));
        }

        POP_WARNING()

    } // namespace JDeviceAudioCapabilities

} // namespace Exchange

} // namespace WPEFramework

