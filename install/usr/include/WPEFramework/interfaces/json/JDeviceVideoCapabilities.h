// Generated automatically from 'IDeviceInfo.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_DeviceVideoCapabilities.h"
#include <interfaces/IDeviceInfo.h>

namespace WPEFramework {

namespace Exchange {

    namespace JDeviceVideoCapabilities {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IDeviceVideoCapabilities* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JDeviceVideoCapabilities"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'supportedvideodisplays' - Provides access to the video ports supported on the device (DEPRECATED)
            _module_.Register<void, JsonData::DeviceVideoCapabilities::SupportedVideoDisplaysResultData>(_T("supportedvideodisplays"), 
                [_impl_](JsonData::DeviceVideoCapabilities::SupportedVideoDisplaysResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _supportedVideoDisplays{};
                    bool _success{};

                    _errorCode = _impl_->SupportedVideoDisplays(_supportedVideoDisplays, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_supportedVideoDisplays != nullptr) {
                            string _supportedVideoDisplaysItem_{};
                            while (_supportedVideoDisplays->Next(_supportedVideoDisplaysItem_) == true) { result.SupportedVideoDisplays.Add() = _supportedVideoDisplaysItem_; }
                            _supportedVideoDisplays->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'defaultresolution' - Default resolution on the selected video display port (DEPRECATED)
            _module_.Register<JsonData::DeviceVideoCapabilities::DefaultResolutionParamsInfo,
                     JsonData::DeviceVideoCapabilities::DefaultReslnData>(_T("defaultresolution"), 
                [_impl_](const JsonData::DeviceVideoCapabilities::DefaultResolutionParamsInfo& params,
                         JsonData::DeviceVideoCapabilities::DefaultReslnData& defaultResln) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _videoDisplay{params.VideoDisplay};
                    Exchange::IDeviceVideoCapabilities::DefaultResln _defaultResln{};

                    _errorCode = _impl_->DefaultResolution(_videoDisplay, _defaultResln);

                    if (_errorCode == Core::ERROR_NONE) {
                        defaultResln = _defaultResln;
                    }

                    return (_errorCode);
                });

            // Method: 'supportedresolutions' - Supported resolutions on the selected video display port (DEPRECATED)
            _module_.Register<JsonData::DeviceVideoCapabilities::DefaultResolutionParamsInfo,
                     JsonData::DeviceVideoCapabilities::SupportedResolutionsResultData>(_T("supportedresolutions"), 
                [_impl_](const JsonData::DeviceVideoCapabilities::DefaultResolutionParamsInfo& params,
                         JsonData::DeviceVideoCapabilities::SupportedResolutionsResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _videoDisplay{params.VideoDisplay};
                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _supportedResolutions{};
                    bool _success{};

                    _errorCode = _impl_->SupportedResolutions(_videoDisplay, _supportedResolutions, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_supportedResolutions != nullptr) {
                            string _supportedResolutionsItem_{};
                            while (_supportedResolutions->Next(_supportedResolutionsItem_) == true) { result.SupportedResolutions.Add() = _supportedResolutionsItem_; }
                            _supportedResolutions->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'supportedhdcp' - Supported hdcp version on the selected video display port (DEPRECATED)
            _module_.Register<JsonData::DeviceVideoCapabilities::DefaultResolutionParamsInfo,
                     JsonData::DeviceVideoCapabilities::SupportedHDCPVerData>(_T("supportedhdcp"), 
                [_impl_](const JsonData::DeviceVideoCapabilities::DefaultResolutionParamsInfo& params,
                         JsonData::DeviceVideoCapabilities::SupportedHDCPVerData& supportedHDCPVer) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _videoDisplay{params.VideoDisplay};
                    Exchange::IDeviceVideoCapabilities::SupportedHDCPVer _supportedHDCPVer{};

                    _errorCode = _impl_->SupportedHdcp(_videoDisplay, _supportedHDCPVer);

                    if (_errorCode == Core::ERROR_NONE) {
                        supportedHDCPVer = _supportedHDCPVer;
                    }

                    return (_errorCode);
                });

            // Property: 'hostedid' - Provides access to the EDID of the host (DEPRECATED) (r/o)
            _module_.Register<void, JsonData::DeviceVideoCapabilities::HostEdidData>(_T("hostedid"), 
                [_impl_](JsonData::DeviceVideoCapabilities::HostEdidData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceVideoCapabilities::HostEdid _result{};

                    _errorCode = _impl_->HostEDID(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("supportedvideodisplays"));
            _module_.Unregister(_T("defaultresolution"));
            _module_.Unregister(_T("supportedresolutions"));
            _module_.Unregister(_T("supportedhdcp"));
            _module_.Unregister(_T("hostedid"));
        }

        POP_WARNING()

    } // namespace JDeviceVideoCapabilities

} // namespace Exchange

} // namespace WPEFramework

