// Generated automatically from 'IDeviceInfo.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_DeviceInfo.h"
#include <interfaces/IDeviceInfo.h>

namespace WPEFramework {

namespace Exchange {

    namespace JDeviceInfo {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IDeviceInfo* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JDeviceInfo"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'supportedaudioports' - Provides access to the audio ports supported on the device
            _module_.Register<void, JsonData::DeviceInfo::SupportedAudioPortsResultData>(_T("supportedaudioports"), 
                [_impl_](JsonData::DeviceInfo::SupportedAudioPortsResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _supportedAudioPorts{};
                    bool _success{};

                    _errorCode = _impl_->SupportedAudioPorts(_supportedAudioPorts, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_supportedAudioPorts != nullptr) {
                            string _supportedAudioPortsItem_{};
                            while (_supportedAudioPorts->Next(_supportedAudioPortsItem_) == true) { result.SupportedAudioPorts.Add() = _supportedAudioPortsItem_; }
                            _supportedAudioPorts->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Property: 'serialnumber' - Provides access to the serial number set by manufacture (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceSerialNoData>(_T("serialnumber"), 
                [_impl_](JsonData::DeviceInfo::DeviceSerialNoData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceSerialNo _result{};

                    _errorCode = _impl_->SerialNumber(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'modelid' - Provides access to the device model number (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceModelNoData>(_T("modelid"), 
                [_impl_](JsonData::DeviceInfo::DeviceModelNoData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceModelNo _result{};

                    _errorCode = _impl_->Sku(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'make' - Provides access to the device manufacturer (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceMakeData>(_T("make"), 
                [_impl_](JsonData::DeviceInfo::DeviceMakeData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceMake _result{};

                    _errorCode = _impl_->Make(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'modelname' - Provides access to the friendly device model name (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceModelData>(_T("modelname"), 
                [_impl_](JsonData::DeviceInfo::DeviceModelData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceModel _result{};

                    _errorCode = _impl_->Model(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'devicetype' - Provides access to the device type (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceTypeInfosData>(_T("devicetype"), 
                [_impl_](JsonData::DeviceInfo::DeviceTypeInfosData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceTypeInfos _result{};

                    _errorCode = _impl_->DeviceType(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'socname' - Provides access to the SOC Name (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceSocData>(_T("socname"), 
                [_impl_](JsonData::DeviceInfo::DeviceSocData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceSoc _result{};

                    _errorCode = _impl_->SocName(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'distributorid' - Provides access to the partner ID or distributor ID for device (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceDistIdData>(_T("distributorid"), 
                [_impl_](JsonData::DeviceInfo::DeviceDistIdData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceDistId _result{};

                    _errorCode = _impl_->DistributorId(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'brandname' - Provides access to device brand name (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceBrandData>(_T("brandname"), 
                [_impl_](JsonData::DeviceInfo::DeviceBrandData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceBrand _result{};

                    _errorCode = _impl_->Brand(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'releaseversion' - Provides access to the ReleaseVersion of the Image (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceReleaseVerData>(_T("releaseversion"), 
                [_impl_](JsonData::DeviceInfo::DeviceReleaseVerData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceReleaseVer _result{};

                    _errorCode = _impl_->ReleaseVersion(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'chipset' - Provides access to the chipset of the device (r/o)
            _module_.Register<void, JsonData::DeviceInfo::DeviceChipData>(_T("chipset"), 
                [_impl_](JsonData::DeviceInfo::DeviceChipData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::DeviceChip _result{};

                    _errorCode = _impl_->ChipSet(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'firmwareversion' - Provides access to the versions maintained in version (r/o)
            _module_.Register<void, JsonData::DeviceInfo::FirmwareversionInfoData>(_T("firmwareversion"), 
                [_impl_](JsonData::DeviceInfo::FirmwareversionInfoData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::FirmwareversionInfo _result{};

                    _errorCode = _impl_->FirmwareVersion(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'systeminfo' - Provides access to the system general information (r/o)
            _module_.Register<void, JsonData::DeviceInfo::SystemInfosData>(_T("systeminfo"), 
                [_impl_](JsonData::DeviceInfo::SystemInfosData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::SystemInfos _result{};

                    _errorCode = _impl_->SystemInfo(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'addresses' - Provides access to the network interface addresses (r/o)
            _module_.Register<void, Core::JSON::ArrayType<JsonData::DeviceInfo::AddressesInfoData>>(_T("addresses"), 
                [_impl_](Core::JSON::ArrayType<JsonData::DeviceInfo::AddressesInfoData>& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    ::WPEFramework::RPC::IIteratorType<IDeviceInfo::AddressesInfo, ID_DEVICE_INFO_ADDRESSES_ITERATOR>* _result{};

                    _errorCode = _impl_->Addresses(_result);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_result != nullptr) {
                            Exchange::IDeviceInfo::AddressesInfo _resultItem_{};
                            while (_result->Next(_resultItem_) == true) { result.Add() = _resultItem_; }
                            _result->Release();
                        }
                    }

                    return (_errorCode);
                });

            // Property: 'ethmac' - Provides access to the Ethernet MAC addresses (r/o)
            _module_.Register<void, JsonData::DeviceInfo::EthernetMacData>(_T("ethmac"), 
                [_impl_](JsonData::DeviceInfo::EthernetMacData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::EthernetMac _result{};

                    _errorCode = _impl_->EthMac(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'estbmac' - Provides access to the STB MAC addresses (r/o)
            _module_.Register<void, JsonData::DeviceInfo::StbMacData>(_T("estbmac"), 
                [_impl_](JsonData::DeviceInfo::StbMacData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::StbMac _result{};

                    _errorCode = _impl_->EstbMac(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'wifimac' - Provides access to the WIFI MAC addresses (r/o)
            _module_.Register<void, JsonData::DeviceInfo::WiFiMacData>(_T("wifimac"), 
                [_impl_](JsonData::DeviceInfo::WiFiMacData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::WiFiMac _result{};

                    _errorCode = _impl_->WifiMac(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'estbip' - Provides access to the STB IP addresses (r/o)
            _module_.Register<void, JsonData::DeviceInfo::StbIpData>(_T("estbip"), 
                [_impl_](JsonData::DeviceInfo::StbIpData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IDeviceInfo::StbIp _result{};

                    _errorCode = _impl_->EstbIp(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("supportedaudioports"));
            _module_.Unregister(_T("serialnumber"));
            _module_.Unregister(_T("modelid"));
            _module_.Unregister(_T("make"));
            _module_.Unregister(_T("modelname"));
            _module_.Unregister(_T("devicetype"));
            _module_.Unregister(_T("socname"));
            _module_.Unregister(_T("distributorid"));
            _module_.Unregister(_T("brandname"));
            _module_.Unregister(_T("releaseversion"));
            _module_.Unregister(_T("chipset"));
            _module_.Unregister(_T("firmwareversion"));
            _module_.Unregister(_T("systeminfo"));
            _module_.Unregister(_T("addresses"));
            _module_.Unregister(_T("ethmac"));
            _module_.Unregister(_T("estbmac"));
            _module_.Unregister(_T("wifimac"));
            _module_.Unregister(_T("estbip"));
        }

        POP_WARNING()

    } // namespace JDeviceInfo

} // namespace Exchange

} // namespace WPEFramework

