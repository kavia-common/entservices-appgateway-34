// C++ classes for USBDevice API JSON-RPC API.
// Generated automatically from 'IUSBDevice.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IUSBDevice.h>

namespace WPEFramework {

namespace JsonData {

    namespace USBDevice {

        // Common classes
        //

        class GetDeviceInfoParamsInfo : public Core::JSON::Container {
        public:
            GetDeviceInfoParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("deviceName"), &DeviceName);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetDeviceInfoParamsInfo(const GetDeviceInfoParamsInfo&) = delete;
            GetDeviceInfoParamsInfo& operator=(const GetDeviceInfoParamsInfo&) = delete;

        public:
            Core::JSON::String DeviceName; // device name
        }; // class GetDeviceInfoParamsInfo

        class USBDeviceInfo : public Core::JSON::Container {
        public:
            USBDeviceInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            USBDeviceInfo(const USBDeviceInfo& _other)
                : Core::JSON::Container()
                , DeviceClass(_other.DeviceClass)
                , DeviceSubclass(_other.DeviceSubclass)
                , DeviceName(_other.DeviceName)
                , DevicePath(_other.DevicePath)
            {
                _Init();
            }

            USBDeviceInfo& operator=(const USBDeviceInfo& _rhs)
            {
                DeviceClass = _rhs.DeviceClass;
                DeviceSubclass = _rhs.DeviceSubclass;
                DeviceName = _rhs.DeviceName;
                DevicePath = _rhs.DevicePath;
                return (*this);
            }

            USBDeviceInfo(const Exchange::IUSBDevice::USBDevice& _other)
                : Core::JSON::Container()
            {
                DeviceClass = _other.deviceClass;
                DeviceSubclass = _other.deviceSubclass;
                DeviceName = _other.deviceName;
                DevicePath = _other.devicePath;
                _Init();
            }

            USBDeviceInfo& operator=(const Exchange::IUSBDevice::USBDevice& _rhs)
            {
                DeviceClass = _rhs.deviceClass;
                DeviceSubclass = _rhs.deviceSubclass;
                DeviceName = _rhs.deviceName;
                DevicePath = _rhs.devicePath;
                return (*this);
            }

            operator Exchange::IUSBDevice::USBDevice() const
            {
                Exchange::IUSBDevice::USBDevice _value{};
                _value.deviceClass = DeviceClass;
                _value.deviceSubclass = DeviceSubclass;
                _value.deviceName = DeviceName;
                _value.devicePath = DevicePath;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("deviceClass"), &DeviceClass);
                Add(_T("deviceSubclass"), &DeviceSubclass);
                Add(_T("deviceName"), &DeviceName);
                Add(_T("devicePath"), &DevicePath);
            }

        public:
            Core::JSON::DecUInt8 DeviceClass; // USB class of the device as per USB specificiation
            Core::JSON::DecUInt8 DeviceSubclass; // USB sub class of the device as per USB specificiation
            Core::JSON::String DeviceName; // Name of the USB device
            Core::JSON::String DevicePath; // the path to be used for the USB device ex: /dev/sdX
        }; // class USBDeviceInfo

        class OnDevicePluggedInParamsInfo : public Core::JSON::Container {
        public:
            OnDevicePluggedInParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("device"), &Device);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnDevicePluggedInParamsInfo(const OnDevicePluggedInParamsInfo&) = delete;
            OnDevicePluggedInParamsInfo& operator=(const OnDevicePluggedInParamsInfo&) = delete;

        public:
            USBDeviceInfo Device; // Device Plugged in notification
        }; // class OnDevicePluggedInParamsInfo

        // Method params/result classes
        //

        class USBDeviceInfoData : public Core::JSON::Container {
        public:
            class USBProductInfoData : public Core::JSON::Container {
            public:
                USBProductInfoData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                USBProductInfoData(const Exchange::IUSBDevice::USBProductInfo& _other)
                    : Core::JSON::Container()
                {
                    LanguageId = _other.languageId;
                    SerialNumber = _other.serialNumber;
                    Manufacturer = _other.manufacturer;
                    Product = _other.product;
                    _Init();
                }

                USBProductInfoData& operator=(const Exchange::IUSBDevice::USBProductInfo& _rhs)
                {
                    LanguageId = _rhs.languageId;
                    SerialNumber = _rhs.serialNumber;
                    Manufacturer = _rhs.manufacturer;
                    Product = _rhs.product;
                    return (*this);
                }

                operator Exchange::IUSBDevice::USBProductInfo() const
                {
                    Exchange::IUSBDevice::USBProductInfo _value{};
                    _value.languageId = LanguageId;
                    _value.serialNumber = SerialNumber;
                    _value.manufacturer = Manufacturer;
                    _value.product = Product;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("languageId"), &LanguageId);
                    Add(_T("serialNumber"), &SerialNumber);
                    Add(_T("manufacturer"), &Manufacturer);
                    Add(_T("product"), &Product);
                }

            public:
                Core::JSON::DecUInt16 LanguageId; // language id present on the device
                Core::JSON::String SerialNumber; // unicode string representing the serial number of the device
                Core::JSON::String Manufacturer; // unicode string representing the manufacturer of the device
                Core::JSON::String Product; // unicode string representing the product
            }; // class USBProductInfoData

            USBDeviceInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            USBDeviceInfoData(const Exchange::IUSBDevice::USBDeviceInfo& _other)
                : Core::JSON::Container()
            {
                ParentId = _other.parentId;
                DeviceStatus = _other.deviceStatus;
                DeviceLevel = _other.deviceLevel;
                PortNumber = _other.portNumber;
                VendorId = _other.vendorId;
                ProductId = _other.productId;
                Protocol = _other.protocol;
                SerialNumber = _other.serialNumber;
                Device = _other.device;
                Flags = _other.flags;
                Features = _other.features;
                BusSpeed = _other.busSpeed;
                NumLanguageIds = _other.numLanguageIds;
                ProductInfo1 = _other.productInfo1;
                ProductInfo2 = _other.productInfo2;
                ProductInfo3 = _other.productInfo3;
                ProductInfo4 = _other.productInfo4;
                _Init();
            }

            USBDeviceInfoData& operator=(const Exchange::IUSBDevice::USBDeviceInfo& _rhs)
            {
                ParentId = _rhs.parentId;
                DeviceStatus = _rhs.deviceStatus;
                DeviceLevel = _rhs.deviceLevel;
                PortNumber = _rhs.portNumber;
                VendorId = _rhs.vendorId;
                ProductId = _rhs.productId;
                Protocol = _rhs.protocol;
                SerialNumber = _rhs.serialNumber;
                Device = _rhs.device;
                Flags = _rhs.flags;
                Features = _rhs.features;
                BusSpeed = _rhs.busSpeed;
                NumLanguageIds = _rhs.numLanguageIds;
                ProductInfo1 = _rhs.productInfo1;
                ProductInfo2 = _rhs.productInfo2;
                ProductInfo3 = _rhs.productInfo3;
                ProductInfo4 = _rhs.productInfo4;
                return (*this);
            }

            operator Exchange::IUSBDevice::USBDeviceInfo() const
            {
                Exchange::IUSBDevice::USBDeviceInfo _value{};
                _value.parentId = ParentId;
                _value.deviceStatus = DeviceStatus;
                _value.deviceLevel = DeviceLevel;
                _value.portNumber = PortNumber;
                _value.vendorId = VendorId;
                _value.productId = ProductId;
                _value.protocol = Protocol;
                _value.serialNumber = SerialNumber;
                _value.device = Device;
                _value.flags = Flags;
                _value.features = Features;
                _value.busSpeed = BusSpeed;
                _value.numLanguageIds = NumLanguageIds;
                _value.productInfo1 = ProductInfo1;
                _value.productInfo2 = ProductInfo2;
                _value.productInfo3 = ProductInfo3;
                _value.productInfo4 = ProductInfo4;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("parentId"), &ParentId);
                Add(_T("deviceStatus"), &DeviceStatus);
                Add(_T("deviceLevel"), &DeviceLevel);
                Add(_T("portNumber"), &PortNumber);
                Add(_T("vendorId"), &VendorId);
                Add(_T("productId"), &ProductId);
                Add(_T("protocol"), &Protocol);
                Add(_T("serialNumber"), &SerialNumber);
                Add(_T("device"), &Device);
                Add(_T("flags"), &Flags);
                Add(_T("features"), &Features);
                Add(_T("busSpeed"), &BusSpeed);
                Add(_T("numLanguageIds"), &NumLanguageIds);
                Add(_T("productInfo1"), &ProductInfo1);
                Add(_T("productInfo2"), &ProductInfo2);
                Add(_T("productInfo3"), &ProductInfo3);
                Add(_T("productInfo4"), &ProductInfo4);
            }

        public:
            Core::JSON::DecUInt32 ParentId; // Parent Node ID of the device
            Core::JSON::DecUInt8 DeviceStatus; // Get the extended USB device information for the provided device name
            Core::JSON::DecUInt8 DeviceLevel; // device level
            Core::JSON::DecUInt8 PortNumber; // port number of USB on which the device is attached
            Core::JSON::DecUInt16 VendorId; // Vendor ID of the device
            Core::JSON::DecUInt16 ProductId; // Product ID of the device
            Core::JSON::DecUInt8 Protocol; // Protocol supported by the device
            Core::JSON::String SerialNumber; // Serial number of the device
            USBDeviceInfo Device; // Basic device information included
            Core::JSON::EnumType<Exchange::IUSBDevice::USBDeviceFlags> Flags; // Flags of the device
            Core::JSON::DecUInt32 Features; // Features supported by the device - reserved
            Core::JSON::EnumType<Exchange::IUSBDevice::USBDeviceSpeed> BusSpeed; // Speed of the device
            Core::JSON::DecUInt8 NumLanguageIds; // number of language ids present on the device
            USBDeviceInfoData::USBProductInfoData ProductInfo1; // Get the extended USB device information for the provided device name
            USBProductInfoData ProductInfo2; // Get the extended USB device information for the provided device name
            USBProductInfoData ProductInfo3; // Get the extended USB device information for the provided device name
            USBProductInfoData ProductInfo4; // Get the extended USB device information for the provided device name
        }; // class USBDeviceInfoData

    } // namespace USBDevice

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IUSBDevice::USBDeviceFlags)
ENUM_CONVERSION_HANDLER(Exchange::IUSBDevice::USBDeviceSpeed)

}

