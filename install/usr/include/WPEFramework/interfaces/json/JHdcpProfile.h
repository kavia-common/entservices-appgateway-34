// Generated automatically from 'IHdcpProfile.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_HdcpProfile.h"
#include <interfaces/IHdcpProfile.h>

namespace WPEFramework {

namespace Exchange {

    namespace JHdcpProfile {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IHdcpProfile* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JHdcpProfile"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getHDCPStatus' - Returns HDCP-related data
            _module_.Register<void, JsonData::HdcpProfile::GetHDCPStatusResultData>(_T("getHDCPStatus"), 
                [_impl_](JsonData::HdcpProfile::GetHDCPStatusResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdcpProfile::HDCPStatus _hdcpStatus{};
                    bool _success{};

                    _errorCode = _impl_->GetHDCPStatus(_hdcpStatus, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.HdcpStatus = _hdcpStatus;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getSettopHDCPSupport' - Returns which version of HDCP is supported by the STB
            _module_.Register<void, JsonData::HdcpProfile::GetSettopHDCPSupportResultData>(_T("getSettopHDCPSupport"), 
                [_impl_](JsonData::HdcpProfile::GetSettopHDCPSupportResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _supportedHDCPVersion{};
                    bool _isHDCPSupported{};
                    bool _success{};

                    _errorCode = _impl_->GetSettopHDCPSupport(_supportedHDCPVersion, _isHDCPSupported, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.SupportedHDCPVersion = _supportedHDCPVersion;
                        result.IsHDCPSupported = _isHDCPSupported;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getHDCPStatus"));
            _module_.Unregister(_T("getSettopHDCPSupport"));
        }

        namespace Event {

            // Event: 'onDisplayConnectionChanged' - Triggered if HDMI was connected or disconnected upon receiving onHdmiOutputHotPlug
            static void OnDisplayConnectionChanged(const JSONRPC& _module_, const JsonData::HdcpProfile::OnDisplayConnectionChangedParamsData& params)
            {
                _module_.Notify(_T("onDisplayConnectionChanged"), params);
            }

            // Event: 'onDisplayConnectionChanged' - Triggered if HDMI was connected or disconnected upon receiving onHdmiOutputHotPlug
            static void OnDisplayConnectionChanged(const JSONRPC& _module_, const Exchange::IHdcpProfile::HDCPStatus& hdcpStatus)
            {
                JsonData::HdcpProfile::OnDisplayConnectionChangedParamsData _params_;
                _params_.HdcpStatus = hdcpStatus;

                OnDisplayConnectionChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JHdcpProfile

} // namespace Exchange

} // namespace WPEFramework

