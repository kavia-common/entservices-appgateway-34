// C++ classes for USBMassStorage API JSON-RPC API.
// Generated automatically from 'IUSBMassStorage.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IUSBMassStorage.h>

namespace WPEFramework {

namespace JsonData {

    namespace USBMassStorage {

        // Method params/result classes
        //

        class USBStorageDeviceInfoData : public Core::JSON::Container {
        public:
            USBStorageDeviceInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            USBStorageDeviceInfoData(const USBStorageDeviceInfoData& _other)
                : Core::JSON::Container()
                , DevicePath(_other.DevicePath)
                , DeviceName(_other.DeviceName)
            {
                _Init();
            }

            USBStorageDeviceInfoData& operator=(const USBStorageDeviceInfoData& _rhs)
            {
                DevicePath = _rhs.DevicePath;
                DeviceName = _rhs.DeviceName;
                return (*this);
            }

            USBStorageDeviceInfoData(const Exchange::IUSBMassStorage::USBStorageDeviceInfo& _other)
                : Core::JSON::Container()
            {
                DevicePath = _other.devicePath;
                DeviceName = _other.deviceName;
                _Init();
            }

            USBStorageDeviceInfoData& operator=(const Exchange::IUSBMassStorage::USBStorageDeviceInfo& _rhs)
            {
                DevicePath = _rhs.devicePath;
                DeviceName = _rhs.deviceName;
                return (*this);
            }

            operator Exchange::IUSBMassStorage::USBStorageDeviceInfo() const
            {
                Exchange::IUSBMassStorage::USBStorageDeviceInfo _value{};
                _value.devicePath = DevicePath;
                _value.deviceName = DeviceName;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("devicePath"), &DevicePath);
                Add(_T("deviceName"), &DeviceName);
            }

        public:
            Core::JSON::String DevicePath; // Device path in the file system (sysfs)
            Core::JSON::String DeviceName; // Device name identifying the device
        }; // class USBStorageDeviceInfoData

        class GetMountPointsParamsData : public Core::JSON::Container {
        public:
            GetMountPointsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("deviceName"), &DeviceName);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetMountPointsParamsData(const GetMountPointsParamsData&) = delete;
            GetMountPointsParamsData& operator=(const GetMountPointsParamsData&) = delete;

        public:
            Core::JSON::String DeviceName; // name of the device for which mount points are to be retrieved
        }; // class GetMountPointsParamsData

        class USBStorageMountInfoData : public Core::JSON::Container {
        public:
            USBStorageMountInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            USBStorageMountInfoData(const USBStorageMountInfoData& _other)
                : Core::JSON::Container()
                , PartitionName(_other.PartitionName)
                , MountFlags(_other.MountFlags)
                , MountPath(_other.MountPath)
                , FileSystem(_other.FileSystem)
            {
                _Init();
            }

            USBStorageMountInfoData& operator=(const USBStorageMountInfoData& _rhs)
            {
                PartitionName = _rhs.PartitionName;
                MountFlags = _rhs.MountFlags;
                MountPath = _rhs.MountPath;
                FileSystem = _rhs.FileSystem;
                return (*this);
            }

            USBStorageMountInfoData(const Exchange::IUSBMassStorage::USBStorageMountInfo& _other)
                : Core::JSON::Container()
            {
                PartitionName = _other.partitionName;
                MountFlags = _other.mountFlags;
                MountPath = _other.mountPath;
                FileSystem = _other.fileSystem;
                _Init();
            }

            USBStorageMountInfoData& operator=(const Exchange::IUSBMassStorage::USBStorageMountInfo& _rhs)
            {
                PartitionName = _rhs.partitionName;
                MountFlags = _rhs.mountFlags;
                MountPath = _rhs.mountPath;
                FileSystem = _rhs.fileSystem;
                return (*this);
            }

            operator Exchange::IUSBMassStorage::USBStorageMountInfo() const
            {
                Exchange::IUSBMassStorage::USBStorageMountInfo _value{};
                _value.partitionName = PartitionName;
                _value.mountFlags = MountFlags;
                _value.mountPath = MountPath;
                _value.fileSystem = FileSystem;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("partitionName"), &PartitionName);
                Add(_T("mountFlags"), &MountFlags);
                Add(_T("mountPath"), &MountPath);
                Add(_T("fileSystem"), &FileSystem);
            }

        public:
            Core::JSON::String PartitionName; // name of the partition
            Core::JSON::EnumType<Exchange::IUSBMassStorage::USBStorageMountFlags> MountFlags; // Mount flags used for mounting the device / partition
            Core::JSON::String MountPath; // path at which the partition is mounted on
            Core::JSON::EnumType<Exchange::IUSBMassStorage::USBStorageFileSystem> FileSystem; // file system of the partition
        }; // class USBStorageMountInfoData

        class GetPartitionInfoParamsData : public Core::JSON::Container {
        public:
            GetPartitionInfoParamsData()
                : Core::JSON::Container()
            {
                Add(_T("mountPath"), &MountPath);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetPartitionInfoParamsData(const GetPartitionInfoParamsData&) = delete;
            GetPartitionInfoParamsData& operator=(const GetPartitionInfoParamsData&) = delete;

        public:
            Core::JSON::String MountPath; // : mount path of the partition for which more info is required
        }; // class GetPartitionInfoParamsData

        class USBStoragePartitionInfoData : public Core::JSON::Container {
        public:
            USBStoragePartitionInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            USBStoragePartitionInfoData(const Exchange::IUSBMassStorage::USBStoragePartitionInfo& _other)
                : Core::JSON::Container()
            {
                FileSystem = _other.fileSystem;
                Size = _other.size;
                StartSector = _other.startSector;
                NumSectors = _other.numSectors;
                SectorSize = _other.sectorSize;
                TotalSpace = _other.totalSpace;
                UsedSpace = _other.usedSpace;
                AvailableSpace = _other.availableSpace;
                _Init();
            }

            USBStoragePartitionInfoData& operator=(const Exchange::IUSBMassStorage::USBStoragePartitionInfo& _rhs)
            {
                FileSystem = _rhs.fileSystem;
                Size = _rhs.size;
                StartSector = _rhs.startSector;
                NumSectors = _rhs.numSectors;
                SectorSize = _rhs.sectorSize;
                TotalSpace = _rhs.totalSpace;
                UsedSpace = _rhs.usedSpace;
                AvailableSpace = _rhs.availableSpace;
                return (*this);
            }

            operator Exchange::IUSBMassStorage::USBStoragePartitionInfo() const
            {
                Exchange::IUSBMassStorage::USBStoragePartitionInfo _value{};
                _value.fileSystem = FileSystem;
                _value.size = Size;
                _value.startSector = StartSector;
                _value.numSectors = NumSectors;
                _value.sectorSize = SectorSize;
                _value.totalSpace = TotalSpace;
                _value.usedSpace = UsedSpace;
                _value.availableSpace = AvailableSpace;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("fileSystem"), &FileSystem);
                Add(_T("size"), &Size);
                Add(_T("startSector"), &StartSector);
                Add(_T("numSectors"), &NumSectors);
                Add(_T("sectorSize"), &SectorSize);
                Add(_T("totalSpace"), &TotalSpace);
                Add(_T("usedSpace"), &UsedSpace);
                Add(_T("availableSpace"), &AvailableSpace);
            }

        public:
            Core::JSON::EnumType<Exchange::IUSBMassStorage::USBStorageFileSystem> FileSystem; // Get partition information for a given partition
            Core::JSON::DecUInt32 Size; // Get partition information for a given partition
            Core::JSON::DecUInt64 StartSector; // Get partition information for a given partition
            Core::JSON::DecUInt64 NumSectors; // Get partition information for a given partition
            Core::JSON::DecUInt32 SectorSize; // Get partition information for a given partition
            Core::JSON::DecUInt32 TotalSpace; // Get partition information for a given partition
            Core::JSON::DecUInt32 UsedSpace; // Get partition information for a given partition
            Core::JSON::DecUInt32 AvailableSpace; // Get partition information for a given partition
        }; // class USBStoragePartitionInfoData

    } // namespace USBMassStorage

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IUSBMassStorage::USBStorageMountFlags)
ENUM_CONVERSION_HANDLER(Exchange::IUSBMassStorage::USBStorageFileSystem)

}

