// Generated automatically from 'IUSBMassStorage.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_USBMassStorage.h"
#include <interfaces/IUSBMassStorage.h>

namespace WPEFramework {

namespace Exchange {

    namespace JUSBMassStorage {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IUSBMassStorage* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JUSBMassStorage"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getDeviceList' - Get list of devices that are currently mounted in the system
            _module_.Register<void, Core::JSON::ArrayType<JsonData::USBMassStorage::USBStorageDeviceInfoData>>(_T("getDeviceList"), 
                [_impl_](Core::JSON::ArrayType<JsonData::USBMassStorage::USBStorageDeviceInfoData>& deviceInfo) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<IUSBMassStorage::USBStorageDeviceInfo, ID_USB_MASS_STORAGE_DEVICE_INFO_ITERATOR>* _deviceInfo{};

                    _errorCode = _impl_->GetDeviceList(_deviceInfo);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_deviceInfo != nullptr) {
                            Exchange::IUSBMassStorage::USBStorageDeviceInfo _resultItem_{};
                            while (_deviceInfo->Next(_resultItem_) == true) { deviceInfo.Add() = _resultItem_; }
                            _deviceInfo->Release();
                        }
                    }

                    return (_errorCode);
                });

            // Method: 'getMountPoints' - Get mount points information for a specified device
            _module_.Register<JsonData::USBMassStorage::GetMountPointsParamsData,
                     Core::JSON::ArrayType<JsonData::USBMassStorage::USBStorageMountInfoData>>(_T("getMountPoints"), 
                [_impl_](const JsonData::USBMassStorage::GetMountPointsParamsData& params,
                         Core::JSON::ArrayType<JsonData::USBMassStorage::USBStorageMountInfoData>& mountPoints) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _deviceName{params.DeviceName};
                    ::WPEFramework::RPC::IIteratorType<IUSBMassStorage::USBStorageMountInfo, ID_USB_MASS_STORAGE_MOUNT_INFO_ITERATOR>* _mountPoints{};

                    _errorCode = _impl_->GetMountPoints(_deviceName, _mountPoints);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_mountPoints != nullptr) {
                            Exchange::IUSBMassStorage::USBStorageMountInfo _resultItem_{};
                            while (_mountPoints->Next(_resultItem_) == true) { mountPoints.Add() = _resultItem_; }
                            _mountPoints->Release();
                        }
                    }

                    return (_errorCode);
                });

            // Method: 'getPartitionInfo' - Get partition information for a given partition
            _module_.Register<JsonData::USBMassStorage::GetPartitionInfoParamsData,
                     JsonData::USBMassStorage::USBStoragePartitionInfoData>(_T("getPartitionInfo"), 
                [_impl_](const JsonData::USBMassStorage::GetPartitionInfoParamsData& params,
                         JsonData::USBMassStorage::USBStoragePartitionInfoData& partitionInfo) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _mountPath{params.MountPath};
                    Exchange::IUSBMassStorage::USBStoragePartitionInfo _partitionInfo{};

                    _errorCode = _impl_->GetPartitionInfo(_mountPath, _partitionInfo);

                    if (_errorCode == Core::ERROR_NONE) {
                        partitionInfo = _partitionInfo;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getDeviceList"));
            _module_.Unregister(_T("getMountPoints"));
            _module_.Unregister(_T("getPartitionInfo"));
        }

        POP_WARNING()

    } // namespace JUSBMassStorage

} // namespace Exchange

} // namespace WPEFramework

