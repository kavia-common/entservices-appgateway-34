// C++ classes for DeviceInfo API JSON-RPC API.
// Generated automatically from 'IDeviceInfo.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IDeviceInfo.h>

namespace WPEFramework {

namespace JsonData {

    namespace DeviceInfo {

        // Method params/result classes
        //

        class AddressesInfoData : public Core::JSON::Container {
        public:
            AddressesInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            AddressesInfoData(const AddressesInfoData& _other)
                : Core::JSON::Container()
                , Name(_other.Name)
                , Mac(_other.Mac)
                , Ip(_other.Ip)
            {
                _Init();
            }

            AddressesInfoData& operator=(const AddressesInfoData& _rhs)
            {
                Name = _rhs.Name;
                Mac = _rhs.Mac;
                Ip = _rhs.Ip;
                return (*this);
            }

            AddressesInfoData(const Exchange::IDeviceInfo::AddressesInfo& _other)
                : Core::JSON::Container()
            {
                Name = _other.name;
                Mac = _other.mac;
                Ip = _other.ip;
                _Init();
            }

            AddressesInfoData& operator=(const Exchange::IDeviceInfo::AddressesInfo& _rhs)
            {
                Name = _rhs.name;
                Mac = _rhs.mac;
                Ip = _rhs.ip;
                return (*this);
            }

            operator Exchange::IDeviceInfo::AddressesInfo() const
            {
                Exchange::IDeviceInfo::AddressesInfo _value{};
                _value.name = Name;
                _value.mac = Mac;
                _value.ip = Ip;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("name"), &Name);
                Add(_T("mac"), &Mac);
                Add(_T("ip"), &Ip);
            }

        public:
            Core::JSON::String Name; // Interface name
            Core::JSON::String Mac; // Interface MAC address
            Core::JSON::String Ip; // Interface IP address
        }; // class AddressesInfoData

        class DeviceBrandData : public Core::JSON::Container {
        public:
            DeviceBrandData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceBrandData(const Exchange::IDeviceInfo::DeviceBrand& _other)
                : Core::JSON::Container()
            {
                Brand = _other.brand;
                _Init();
            }

            DeviceBrandData& operator=(const Exchange::IDeviceInfo::DeviceBrand& _rhs)
            {
                Brand = _rhs.brand;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceBrand() const
            {
                Exchange::IDeviceInfo::DeviceBrand _value{};
                _value.brand = Brand;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("brand"), &Brand);
            }

        public:
            Core::JSON::String Brand; // Brand Name
        }; // class DeviceBrandData

        class DeviceChipData : public Core::JSON::Container {
        public:
            DeviceChipData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceChipData(const Exchange::IDeviceInfo::DeviceChip& _other)
                : Core::JSON::Container()
            {
                Chipset = _other.chipset;
                _Init();
            }

            DeviceChipData& operator=(const Exchange::IDeviceInfo::DeviceChip& _rhs)
            {
                Chipset = _rhs.chipset;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceChip() const
            {
                Exchange::IDeviceInfo::DeviceChip _value{};
                _value.chipset = Chipset;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("chipset"), &Chipset);
            }

        public:
            Core::JSON::String Chipset; // Device chip set Name
        }; // class DeviceChipData

        class DeviceTypeInfosData : public Core::JSON::Container {
        public:
            DeviceTypeInfosData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceTypeInfosData(const Exchange::IDeviceInfo::DeviceTypeInfos& _other)
                : Core::JSON::Container()
            {
                Devicetype = _other.devicetype;
                _Init();
            }

            DeviceTypeInfosData& operator=(const Exchange::IDeviceInfo::DeviceTypeInfos& _rhs)
            {
                Devicetype = _rhs.devicetype;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceTypeInfos() const
            {
                Exchange::IDeviceInfo::DeviceTypeInfos _value{};
                _value.devicetype = Devicetype;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("devicetype"), &Devicetype);
            }

        public:
            Core::JSON::EnumType<Exchange::IDeviceInfo::DeviceTypeInfo> Devicetype; // Device type (must be one of the following: tv, IpStb, QamIpStb)
        }; // class DeviceTypeInfosData

        class DeviceDistIdData : public Core::JSON::Container {
        public:
            DeviceDistIdData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceDistIdData(const Exchange::IDeviceInfo::DeviceDistId& _other)
                : Core::JSON::Container()
            {
                Distributorid = _other.distributorid;
                _Init();
            }

            DeviceDistIdData& operator=(const Exchange::IDeviceInfo::DeviceDistId& _rhs)
            {
                Distributorid = _rhs.distributorid;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceDistId() const
            {
                Exchange::IDeviceInfo::DeviceDistId _value{};
                _value.distributorid = Distributorid;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("distributorid"), &Distributorid);
            }

        public:
            Core::JSON::String Distributorid; // Partner ID or distributor ID for device
        }; // class DeviceDistIdData

        class StbIpData : public Core::JSON::Container {
        public:
            StbIpData()
                : Core::JSON::Container()
            {
                _Init();
            }

            StbIpData(const Exchange::IDeviceInfo::StbIp& _other)
                : Core::JSON::Container()
            {
                EstbIp = _other.estbIp;
                _Init();
            }

            StbIpData& operator=(const Exchange::IDeviceInfo::StbIp& _rhs)
            {
                EstbIp = _rhs.estbIp;
                return (*this);
            }

            operator Exchange::IDeviceInfo::StbIp() const
            {
                Exchange::IDeviceInfo::StbIp _value{};
                _value.estbIp = EstbIp;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("estb_ip"), &EstbIp);
            }

        public:
            Core::JSON::String EstbIp; // STB IP Address
        }; // class StbIpData

        class StbMacData : public Core::JSON::Container {
        public:
            StbMacData()
                : Core::JSON::Container()
            {
                _Init();
            }

            StbMacData(const Exchange::IDeviceInfo::StbMac& _other)
                : Core::JSON::Container()
            {
                EstbMac = _other.estbMac;
                _Init();
            }

            StbMacData& operator=(const Exchange::IDeviceInfo::StbMac& _rhs)
            {
                EstbMac = _rhs.estbMac;
                return (*this);
            }

            operator Exchange::IDeviceInfo::StbMac() const
            {
                Exchange::IDeviceInfo::StbMac _value{};
                _value.estbMac = EstbMac;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("estb_mac"), &EstbMac);
            }

        public:
            Core::JSON::String EstbMac; // STB Mac Address
        }; // class StbMacData

        class EthernetMacData : public Core::JSON::Container {
        public:
            EthernetMacData()
                : Core::JSON::Container()
            {
                _Init();
            }

            EthernetMacData(const Exchange::IDeviceInfo::EthernetMac& _other)
                : Core::JSON::Container()
            {
                EthMac = _other.ethMac;
                _Init();
            }

            EthernetMacData& operator=(const Exchange::IDeviceInfo::EthernetMac& _rhs)
            {
                EthMac = _rhs.ethMac;
                return (*this);
            }

            operator Exchange::IDeviceInfo::EthernetMac() const
            {
                Exchange::IDeviceInfo::EthernetMac _value{};
                _value.ethMac = EthMac;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("eth_mac"), &EthMac);
            }

        public:
            Core::JSON::String EthMac; // Ethernet Mac Address
        }; // class EthernetMacData

        class FirmwareversionInfoData : public Core::JSON::Container {
        public:
            FirmwareversionInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            FirmwareversionInfoData(const Exchange::IDeviceInfo::FirmwareversionInfo& _other)
                : Core::JSON::Container()
            {
                Imagename = _other.imagename;
                Sdk = _other.sdk;
                Mediarite = _other.mediarite;
                Yocto = _other.yocto;
                Pdri = _other.pdri;
                _Init();
            }

            FirmwareversionInfoData& operator=(const Exchange::IDeviceInfo::FirmwareversionInfo& _rhs)
            {
                Imagename = _rhs.imagename;
                Sdk = _rhs.sdk;
                Mediarite = _rhs.mediarite;
                Yocto = _rhs.yocto;
                Pdri = _rhs.pdri;
                return (*this);
            }

            operator Exchange::IDeviceInfo::FirmwareversionInfo() const
            {
                Exchange::IDeviceInfo::FirmwareversionInfo _value{};
                _value.imagename = Imagename;
                _value.sdk = Sdk;
                _value.mediarite = Mediarite;
                _value.yocto = Yocto;
                _value.pdri = Pdri;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("imagename"), &Imagename);
                Add(_T("sdk"), &Sdk);
                Add(_T("mediarite"), &Mediarite);
                Add(_T("yocto"), &Yocto);
                Add(_T("pdri"), &Pdri);
            }

        public:
            Core::JSON::String Imagename; // Image name
            Core::JSON::String Sdk; // sdk version
            Core::JSON::String Mediarite; // mediarite
            Core::JSON::String Yocto; // yocto version
            Core::JSON::String Pdri; // pdri version
        }; // class FirmwareversionInfoData

        class DeviceMakeData : public Core::JSON::Container {
        public:
            DeviceMakeData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceMakeData(const Exchange::IDeviceInfo::DeviceMake& _other)
                : Core::JSON::Container()
            {
                Make = _other.make;
                _Init();
            }

            DeviceMakeData& operator=(const Exchange::IDeviceInfo::DeviceMake& _rhs)
            {
                Make = _rhs.make;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceMake() const
            {
                Exchange::IDeviceInfo::DeviceMake _value{};
                _value.make = Make;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("make"), &Make);
            }

        public:
            Core::JSON::String Make; // Device manufacturer
        }; // class DeviceMakeData

        class DeviceModelData : public Core::JSON::Container {
        public:
            DeviceModelData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceModelData(const Exchange::IDeviceInfo::DeviceModel& _other)
                : Core::JSON::Container()
            {
                Model = _other.model;
                _Init();
            }

            DeviceModelData& operator=(const Exchange::IDeviceInfo::DeviceModel& _rhs)
            {
                Model = _rhs.model;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceModel() const
            {
                Exchange::IDeviceInfo::DeviceModel _value{};
                _value.model = Model;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("model"), &Model);
            }

        public:
            Core::JSON::String Model; // Friendly device model name
        }; // class DeviceModelData

        class DeviceReleaseVerData : public Core::JSON::Container {
        public:
            DeviceReleaseVerData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceReleaseVerData(const Exchange::IDeviceInfo::DeviceReleaseVer& _other)
                : Core::JSON::Container()
            {
                Releaseversion = _other.releaseversion;
                _Init();
            }

            DeviceReleaseVerData& operator=(const Exchange::IDeviceInfo::DeviceReleaseVer& _rhs)
            {
                Releaseversion = _rhs.releaseversion;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceReleaseVer() const
            {
                Exchange::IDeviceInfo::DeviceReleaseVer _value{};
                _value.releaseversion = Releaseversion;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("releaseversion"), &Releaseversion);
            }

        public:
            Core::JSON::String Releaseversion; // Release version
        }; // class DeviceReleaseVerData

        class DeviceSerialNoData : public Core::JSON::Container {
        public:
            DeviceSerialNoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceSerialNoData(const Exchange::IDeviceInfo::DeviceSerialNo& _other)
                : Core::JSON::Container()
            {
                Serialnumber = _other.serialnumber;
                _Init();
            }

            DeviceSerialNoData& operator=(const Exchange::IDeviceInfo::DeviceSerialNo& _rhs)
            {
                Serialnumber = _rhs.serialnumber;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceSerialNo() const
            {
                Exchange::IDeviceInfo::DeviceSerialNo _value{};
                _value.serialnumber = Serialnumber;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("serialnumber"), &Serialnumber);
            }

        public:
            Core::JSON::String Serialnumber; // Serial number set by manufacturer
        }; // class DeviceSerialNoData

        class DeviceModelNoData : public Core::JSON::Container {
        public:
            DeviceModelNoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceModelNoData(const Exchange::IDeviceInfo::DeviceModelNo& _other)
                : Core::JSON::Container()
            {
                Sku = _other.sku;
                _Init();
            }

            DeviceModelNoData& operator=(const Exchange::IDeviceInfo::DeviceModelNo& _rhs)
            {
                Sku = _rhs.sku;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceModelNo() const
            {
                Exchange::IDeviceInfo::DeviceModelNo _value{};
                _value.sku = Sku;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("sku"), &Sku);
            }

        public:
            Core::JSON::String Sku; // Device model number or SKU
        }; // class DeviceModelNoData

        class DeviceSocData : public Core::JSON::Container {
        public:
            DeviceSocData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DeviceSocData(const Exchange::IDeviceInfo::DeviceSoc& _other)
                : Core::JSON::Container()
            {
                Socname = _other.socname;
                _Init();
            }

            DeviceSocData& operator=(const Exchange::IDeviceInfo::DeviceSoc& _rhs)
            {
                Socname = _rhs.socname;
                return (*this);
            }

            operator Exchange::IDeviceInfo::DeviceSoc() const
            {
                Exchange::IDeviceInfo::DeviceSoc _value{};
                _value.socname = Socname;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("socname"), &Socname);
            }

        public:
            Core::JSON::String Socname; // SOC Name
        }; // class DeviceSocData

        class SupportedAudioPortsResultData : public Core::JSON::Container {
        public:
            SupportedAudioPortsResultData()
                : Core::JSON::Container()
            {
                Add(_T("supportedAudioPorts"), &SupportedAudioPorts);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            SupportedAudioPortsResultData(const SupportedAudioPortsResultData&) = delete;
            SupportedAudioPortsResultData& operator=(const SupportedAudioPortsResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> SupportedAudioPorts; // Audio ports supported on the device.
            Core::JSON::Boolean Success; // Provides access to the audio ports supported on the device.
        }; // class SupportedAudioPortsResultData

        class SystemInfosData : public Core::JSON::Container {
        public:
            class CpuLoadAvgData : public Core::JSON::Container {
            public:
                CpuLoadAvgData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                CpuLoadAvgData(const Exchange::IDeviceInfo::CpuLoadAvg& _other)
                    : Core::JSON::Container()
                {
                    Avg1min = _other.avg1min;
                    Avg5min = _other.avg5min;
                    Avg15min = _other.avg15min;
                    _Init();
                }

                CpuLoadAvgData& operator=(const Exchange::IDeviceInfo::CpuLoadAvg& _rhs)
                {
                    Avg1min = _rhs.avg1min;
                    Avg5min = _rhs.avg5min;
                    Avg15min = _rhs.avg15min;
                    return (*this);
                }

                operator Exchange::IDeviceInfo::CpuLoadAvg() const
                {
                    Exchange::IDeviceInfo::CpuLoadAvg _value{};
                    _value.avg1min = Avg1min;
                    _value.avg5min = Avg5min;
                    _value.avg15min = Avg15min;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("avg1min"), &Avg1min);
                    Add(_T("avg5min"), &Avg5min);
                    Add(_T("avg15min"), &Avg15min);
                }

            public:
                Core::JSON::DecUInt32 Avg1min; // 1min cpuload average
                Core::JSON::DecUInt32 Avg5min; // 5min cpuload average
                Core::JSON::DecUInt32 Avg15min; // 15min cpuload average
            }; // class CpuLoadAvgData

            SystemInfosData()
                : Core::JSON::Container()
            {
                _Init();
            }

            SystemInfosData(const Exchange::IDeviceInfo::SystemInfos& _other)
                : Core::JSON::Container()
            {
                Version = _other.version;
                Uptime = _other.uptime;
                Totalram = _other.totalram;
                Freeram = _other.freeram;
                Totalswap = _other.totalswap;
                Freeswap = _other.freeswap;
                Devicename = _other.devicename;
                Cpuload = _other.cpuload;
                Cpuloadavg = _other.cpuloadavg;
                Serialnumber = _other.serialnumber;
                Time = _other.time;
                _Init();
            }

            SystemInfosData& operator=(const Exchange::IDeviceInfo::SystemInfos& _rhs)
            {
                Version = _rhs.version;
                Uptime = _rhs.uptime;
                Totalram = _rhs.totalram;
                Freeram = _rhs.freeram;
                Totalswap = _rhs.totalswap;
                Freeswap = _rhs.freeswap;
                Devicename = _rhs.devicename;
                Cpuload = _rhs.cpuload;
                Cpuloadavg = _rhs.cpuloadavg;
                Serialnumber = _rhs.serialnumber;
                Time = _rhs.time;
                return (*this);
            }

            operator Exchange::IDeviceInfo::SystemInfos() const
            {
                Exchange::IDeviceInfo::SystemInfos _value{};
                _value.version = Version;
                _value.uptime = Uptime;
                _value.totalram = Totalram;
                _value.freeram = Freeram;
                _value.totalswap = Totalswap;
                _value.freeswap = Freeswap;
                _value.devicename = Devicename;
                _value.cpuload = Cpuload;
                _value.cpuloadavg = Cpuloadavg;
                _value.serialnumber = Serialnumber;
                _value.time = Time;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("version"), &Version);
                Add(_T("uptime"), &Uptime);
                Add(_T("totalram"), &Totalram);
                Add(_T("freeram"), &Freeram);
                Add(_T("totalswap"), &Totalswap);
                Add(_T("freeswap"), &Freeswap);
                Add(_T("devicename"), &Devicename);
                Add(_T("cpuload"), &Cpuload);
                Add(_T("cpuloadavg"), &Cpuloadavg);
                Add(_T("serialnumber"), &Serialnumber);
                Add(_T("time"), &Time);
            }

        public:
            Core::JSON::String Version; // Software version (in form version#hashtag)
            Core::JSON::DecUInt32 Uptime; // System uptime (in seconds)
            Core::JSON::DecUInt32 Totalram; // Total installed system RAM memory (in bytes)
            Core::JSON::DecUInt32 Freeram; // Free system RAM memory (in bytes)
            Core::JSON::DecUInt32 Totalswap; // Total swap space (in bytes)
            Core::JSON::DecUInt32 Freeswap; // Swap space still available (in bytes)
            Core::JSON::String Devicename; // Host name
            Core::JSON::String Cpuload; // Current CPU load (percentage)
            SystemInfosData::CpuLoadAvgData Cpuloadavg; // CPU load average
            Core::JSON::String Serialnumber; // Device serial number
            Core::JSON::String Time; // Current system date and time
        }; // class SystemInfosData

        class WiFiMacData : public Core::JSON::Container {
        public:
            WiFiMacData()
                : Core::JSON::Container()
            {
                _Init();
            }

            WiFiMacData(const Exchange::IDeviceInfo::WiFiMac& _other)
                : Core::JSON::Container()
            {
                WifiMac = _other.wifiMac;
                _Init();
            }

            WiFiMacData& operator=(const Exchange::IDeviceInfo::WiFiMac& _rhs)
            {
                WifiMac = _rhs.wifiMac;
                return (*this);
            }

            operator Exchange::IDeviceInfo::WiFiMac() const
            {
                Exchange::IDeviceInfo::WiFiMac _value{};
                _value.wifiMac = WifiMac;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("wifi_mac"), &WifiMac);
            }

        public:
            Core::JSON::String WifiMac; // Wifi Mac Address
        }; // class WiFiMacData

    } // namespace DeviceInfo

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IDeviceInfo::DeviceTypeInfo)

}

