// Generated automatically from 'IUSBDevice.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_USBDevice.h"
#include <interfaces/IUSBDevice.h>

namespace WPEFramework {

namespace Exchange {

    namespace JUSBDevice {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IUSBDevice* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JUSBDevice"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getDeviceList' - Get the basic information about list of devices connected with the system
            _module_.Register<void, Core::JSON::ArrayType<JsonData::USBDevice::USBDeviceInfo>>(_T("getDeviceList"), 
                [_impl_](Core::JSON::ArrayType<JsonData::USBDevice::USBDeviceInfo>& devices) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<IUSBDevice::USBDevice, ID_USB_DEVICE_ITERATOR>* _devices{};

                    _errorCode = _impl_->GetDeviceList(_devices);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_devices != nullptr) {
                            Exchange::IUSBDevice::USBDevice _resultItem_{};
                            while (_devices->Next(_resultItem_) == true) { devices.Add() = _resultItem_; }
                            _devices->Release();
                        }
                    }

                    return (_errorCode);
                });

            // Method: 'getDeviceInfo' - Get the extended USB device information for the provided device name
            _module_.Register<JsonData::USBDevice::GetDeviceInfoParamsInfo, JsonData::USBDevice::USBDeviceInfoData>(_T("getDeviceInfo"), 
                [_impl_](const JsonData::USBDevice::GetDeviceInfoParamsInfo& params, JsonData::USBDevice::USBDeviceInfoData& deviceInfo) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _deviceName{params.DeviceName};
                    Exchange::IUSBDevice::USBDeviceInfo _deviceInfo{};

                    _errorCode = _impl_->GetDeviceInfo(_deviceName, _deviceInfo);

                    if (_errorCode == Core::ERROR_NONE) {
                        deviceInfo = _deviceInfo;
                    }

                    return (_errorCode);
                });

            // Method: 'bindDriver' - Bind the respective driver for the device
            _module_.Register<JsonData::USBDevice::GetDeviceInfoParamsInfo, void>(_T("bindDriver"), 
                [_impl_](const JsonData::USBDevice::GetDeviceInfoParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _deviceName{params.DeviceName};

                    _errorCode = _impl_->BindDriver(_deviceName);

                    return (_errorCode);
                });

            // Method: 'unbindDriver' - Unbind the respective driver for the device
            _module_.Register<JsonData::USBDevice::GetDeviceInfoParamsInfo, void>(_T("unbindDriver"), 
                [_impl_](const JsonData::USBDevice::GetDeviceInfoParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _deviceName{params.DeviceName};

                    _errorCode = _impl_->UnbindDriver(_deviceName);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getDeviceList"));
            _module_.Unregister(_T("getDeviceInfo"));
            _module_.Unregister(_T("bindDriver"));
            _module_.Unregister(_T("unbindDriver"));
        }

        namespace Event {

            // Event: 'onDevicePluggedIn' - Device Plugged in notification
            static void OnDevicePluggedIn(const JSONRPC& _module_, const JsonData::USBDevice::OnDevicePluggedInParamsInfo& params)
            {
                _module_.Notify(_T("onDevicePluggedIn"), params);
            }

            // Event: 'onDevicePluggedIn' - Device Plugged in notification
            static void OnDevicePluggedIn(const JSONRPC& _module_, const Exchange::IUSBDevice::USBDevice& device)
            {
                JsonData::USBDevice::OnDevicePluggedInParamsInfo _params_;
                _params_.Device = device;

                OnDevicePluggedIn(_module_, _params_);
            }

            // Event: 'onDevicePluggedOut' - Device Plugged out notification
            static void OnDevicePluggedOut(const JSONRPC& _module_, const JsonData::USBDevice::OnDevicePluggedInParamsInfo& params)
            {
                _module_.Notify(_T("onDevicePluggedOut"), params);
            }

            // Event: 'onDevicePluggedOut' - Device Plugged out notification
            static void OnDevicePluggedOut(const JSONRPC& _module_, const Exchange::IUSBDevice::USBDevice& device)
            {
                JsonData::USBDevice::OnDevicePluggedInParamsInfo _params_;
                _params_.Device = device;

                OnDevicePluggedOut(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JUSBDevice

} // namespace Exchange

} // namespace WPEFramework

