// C++ classes for PackageInstaller API JSON-RPC API.
// Generated automatically from 'IAppPackageManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAppPackageManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace PackageInstaller {

        // Common classes
        //

        class ConfigParamsInfo : public Core::JSON::Container {
        public:
            ConfigParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("packageId"), &PackageId);
                Add(_T("version"), &Version);
            }

            bool IsValid() const
            {
                return (true);
            }

            ConfigParamsInfo(const ConfigParamsInfo&) = delete;
            ConfigParamsInfo& operator=(const ConfigParamsInfo&) = delete;

        public:
            Core::JSON::String PackageId; // Package Id
            Core::JSON::String Version; // Version
        }; // class ConfigParamsInfo

        class RuntimeConfigInfo : public Core::JSON::Container {
        public:
            RuntimeConfigInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            RuntimeConfigInfo(const Exchange::RuntimeConfig& _other)
                : Core::JSON::Container()
            {
                Dial = _other.dial;
                WanLanAccess = _other.wanLanAccess;
                Thunder = _other.thunder;
                SystemMemoryLimit = _other.systemMemoryLimit;
                GpuMemoryLimit = _other.gpuMemoryLimit;
                EnvVariables = _other.envVariables;
                UserId = _other.userId;
                GroupId = _other.groupId;
                DataImageSize = _other.dataImageSize;
                ResourceManagerClientEnabled = _other.resourceManagerClientEnabled;
                DialId = _other.dialId;
                Command = _other.command;
                AppType = _other.appType;
                AppPath = _other.appPath;
                RuntimePath = _other.runtimePath;
                LogFilePath = _other.logFilePath;
                LogFileMaxSize = _other.logFileMaxSize;
                LogLevels = _other.logLevels;
                Mapi = _other.mapi;
                FkpsFiles = _other.fkpsFiles;
                FireboltVersion = _other.fireboltVersion;
                EnableDebugger = _other.enableDebugger;
                _Init();
            }

            RuntimeConfigInfo& operator=(const Exchange::RuntimeConfig& _rhs)
            {
                Dial = _rhs.dial;
                WanLanAccess = _rhs.wanLanAccess;
                Thunder = _rhs.thunder;
                SystemMemoryLimit = _rhs.systemMemoryLimit;
                GpuMemoryLimit = _rhs.gpuMemoryLimit;
                EnvVariables = _rhs.envVariables;
                UserId = _rhs.userId;
                GroupId = _rhs.groupId;
                DataImageSize = _rhs.dataImageSize;
                ResourceManagerClientEnabled = _rhs.resourceManagerClientEnabled;
                DialId = _rhs.dialId;
                Command = _rhs.command;
                AppType = _rhs.appType;
                AppPath = _rhs.appPath;
                RuntimePath = _rhs.runtimePath;
                LogFilePath = _rhs.logFilePath;
                LogFileMaxSize = _rhs.logFileMaxSize;
                LogLevels = _rhs.logLevels;
                Mapi = _rhs.mapi;
                FkpsFiles = _rhs.fkpsFiles;
                FireboltVersion = _rhs.fireboltVersion;
                EnableDebugger = _rhs.enableDebugger;
                return (*this);
            }

            operator Exchange::RuntimeConfig() const
            {
                Exchange::RuntimeConfig _value{};
                _value.dial = Dial;
                _value.wanLanAccess = WanLanAccess;
                _value.thunder = Thunder;
                _value.systemMemoryLimit = SystemMemoryLimit;
                _value.gpuMemoryLimit = GpuMemoryLimit;
                _value.envVariables = EnvVariables;
                _value.userId = UserId;
                _value.groupId = GroupId;
                _value.dataImageSize = DataImageSize;
                _value.resourceManagerClientEnabled = ResourceManagerClientEnabled;
                _value.dialId = DialId;
                _value.command = Command;
                _value.appType = AppType;
                _value.appPath = AppPath;
                _value.runtimePath = RuntimePath;
                _value.logFilePath = LogFilePath;
                _value.logFileMaxSize = LogFileMaxSize;
                _value.logLevels = LogLevels;
                _value.mapi = Mapi;
                _value.fkpsFiles = FkpsFiles;
                _value.fireboltVersion = FireboltVersion;
                _value.enableDebugger = EnableDebugger;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("dial"), &Dial);
                Add(_T("wanLanAccess"), &WanLanAccess);
                Add(_T("thunder"), &Thunder);
                Add(_T("systemMemoryLimit"), &SystemMemoryLimit);
                Add(_T("gpuMemoryLimit"), &GpuMemoryLimit);
                Add(_T("envVariables"), &EnvVariables);
                Add(_T("userId"), &UserId);
                Add(_T("groupId"), &GroupId);
                Add(_T("dataImageSize"), &DataImageSize);
                Add(_T("resourceManagerClientEnabled"), &ResourceManagerClientEnabled);
                Add(_T("dialId"), &DialId);
                Add(_T("command"), &Command);
                Add(_T("appType"), &AppType);
                Add(_T("appPath"), &AppPath);
                Add(_T("runtimePath"), &RuntimePath);
                Add(_T("logFilePath"), &LogFilePath);
                Add(_T("logFileMaxSize"), &LogFileMaxSize);
                Add(_T("logLevels"), &LogLevels);
                Add(_T("mapi"), &Mapi);
                Add(_T("fkpsFiles"), &FkpsFiles);
                Add(_T("fireboltVersion"), &FireboltVersion);
                Add(_T("enableDebugger"), &EnableDebugger);
            }

        public:
            Core::JSON::Boolean Dial; // Config
            Core::JSON::Boolean WanLanAccess; // Config
            Core::JSON::Boolean Thunder; // Config
            Core::JSON::DecSInt32 SystemMemoryLimit; // Config
            Core::JSON::DecSInt32 GpuMemoryLimit; // Config
            Core::JSON::String EnvVariables; // Config
            Core::JSON::DecUInt32 UserId; // Config
            Core::JSON::DecUInt32 GroupId; // Config
            Core::JSON::DecUInt32 DataImageSize; // Config
            Core::JSON::Boolean ResourceManagerClientEnabled; // Config
            Core::JSON::String DialId; // Config
            Core::JSON::String Command; // Config
            Core::JSON::String AppType; // Config
            Core::JSON::String AppPath; // Config
            Core::JSON::String RuntimePath; // Config
            Core::JSON::String LogFilePath; // Config
            Core::JSON::DecUInt32 LogFileMaxSize; // Config
            Core::JSON::String LogLevels; // Config
            Core::JSON::Boolean Mapi; // Config
            Core::JSON::String FkpsFiles; // Config
            Core::JSON::String FireboltVersion; // Config
            Core::JSON::Boolean EnableDebugger; // Config
        }; // class RuntimeConfigInfo

        // Method params/result classes
        //

        class GetConfigForPackageParamsData : public Core::JSON::Container {
        public:
            GetConfigForPackageParamsData()
                : Core::JSON::Container()
            {
                Add(_T("fileLocator"), &FileLocator);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetConfigForPackageParamsData(const GetConfigForPackageParamsData&) = delete;
            GetConfigForPackageParamsData& operator=(const GetConfigForPackageParamsData&) = delete;

        public:
            Core::JSON::String FileLocator; // locator of package
        }; // class GetConfigForPackageParamsData

        class GetConfigForPackageResultData : public Core::JSON::Container {
        public:
            GetConfigForPackageResultData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
                Add(_T("version"), &Version);
                Add(_T("config"), &Config);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetConfigForPackageResultData(const GetConfigForPackageResultData&) = delete;
            GetConfigForPackageResultData& operator=(const GetConfigForPackageResultData&) = delete;

        public:
            Core::JSON::String Id; // package id
            Core::JSON::String Version; // version of package
            RuntimeConfigInfo Config; // metadata of package
        }; // class GetConfigForPackageResultData

        class InstallParamsData : public Core::JSON::Container {
        public:
            class KeyValueData : public Core::JSON::Container {
            public:
                KeyValueData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                KeyValueData(const KeyValueData& _other)
                    : Core::JSON::Container()
                    , Name(_other.Name)
                    , Value(_other.Value)
                {
                    _Init();
                }

                KeyValueData& operator=(const KeyValueData& _rhs)
                {
                    Name = _rhs.Name;
                    Value = _rhs.Value;
                    return (*this);
                }

                KeyValueData(const Exchange::IPackageInstaller::KeyValue& _other)
                    : Core::JSON::Container()
                {
                    Name = _other.name;
                    Value = _other.value;
                    _Init();
                }

                KeyValueData& operator=(const Exchange::IPackageInstaller::KeyValue& _rhs)
                {
                    Name = _rhs.name;
                    Value = _rhs.value;
                    return (*this);
                }

                operator Exchange::IPackageInstaller::KeyValue() const
                {
                    Exchange::IPackageInstaller::KeyValue _value{};
                    _value.name = Name;
                    _value.value = Value;
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
                    Add(_T("value"), &Value);
                }

            public:
                Core::JSON::String Name; // Name
                Core::JSON::String Value; // Value
            }; // class KeyValueData

            InstallParamsData()
                : Core::JSON::Container()
            {
                Add(_T("packageId"), &PackageId);
                Add(_T("version"), &Version);
                Add(_T("additionalMetadata"), &AdditionalMetadata);
                Add(_T("fileLocator"), &FileLocator);
            }

            bool IsValid() const
            {
                return (true);
            }

            InstallParamsData(const InstallParamsData&) = delete;
            InstallParamsData& operator=(const InstallParamsData&) = delete;

        public:
            Core::JSON::String PackageId; // Package Id
            Core::JSON::String Version; // Version
            Core::JSON::ArrayType<InstallParamsData::KeyValueData> AdditionalMetadata; // Additional Metadata
            Core::JSON::String FileLocator; // File Locator
        }; // class InstallParamsData

        class PackageData : public Core::JSON::Container {
        public:
            PackageData()
                : Core::JSON::Container()
            {
                _Init();
            }

            PackageData(const PackageData& _other)
                : Core::JSON::Container()
                , PackageId(_other.PackageId)
                , Version(_other.Version)
                , State(_other.State)
                , Digest(_other.Digest)
                , SizeKb(_other.SizeKb)
            {
                _Init();
            }

            PackageData& operator=(const PackageData& _rhs)
            {
                PackageId = _rhs.PackageId;
                Version = _rhs.Version;
                State = _rhs.State;
                Digest = _rhs.Digest;
                SizeKb = _rhs.SizeKb;
                return (*this);
            }

            PackageData(const Exchange::IPackageInstaller::Package& _other)
                : Core::JSON::Container()
            {
                PackageId = _other.packageId;
                Version = _other.version;
                State = _other.state;
                Digest = _other.digest;
                SizeKb = _other.sizeKb;
                _Init();
            }

            PackageData& operator=(const Exchange::IPackageInstaller::Package& _rhs)
            {
                PackageId = _rhs.packageId;
                Version = _rhs.version;
                State = _rhs.state;
                Digest = _rhs.digest;
                SizeKb = _rhs.sizeKb;
                return (*this);
            }

            operator Exchange::IPackageInstaller::Package() const
            {
                Exchange::IPackageInstaller::Package _value{};
                _value.packageId = PackageId;
                _value.version = Version;
                _value.state = State;
                _value.digest = Digest;
                _value.sizeKb = SizeKb;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("packageId"), &PackageId);
                Add(_T("version"), &Version);
                Add(_T("state"), &State);
                Add(_T("digest"), &Digest);
                Add(_T("sizeKb"), &SizeKb);
            }

        public:
            Core::JSON::String PackageId; // PackageId
            Core::JSON::String Version; // Version
            Core::JSON::EnumType<Exchange::IPackageInstaller::InstallState> State; // state
            Core::JSON::String Digest; // Digest
            Core::JSON::DecUInt64 SizeKb; // SizeKb
        }; // class PackageData

        class OnAppInstallationStatusParamsData : public Core::JSON::Container {
        public:
            OnAppInstallationStatusParamsData()
                : Core::JSON::Container()
            {
                Add(_T("jsonresponse"), &Jsonresponse);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppInstallationStatusParamsData(const OnAppInstallationStatusParamsData&) = delete;
            OnAppInstallationStatusParamsData& operator=(const OnAppInstallationStatusParamsData&) = delete;

        public:
            Core::JSON::String Jsonresponse; // Signal changes on the status
        }; // class OnAppInstallationStatusParamsData

        class UninstallParamsData : public Core::JSON::Container {
        public:
            UninstallParamsData()
                : Core::JSON::Container()
            {
                Add(_T("packageId"), &PackageId);
            }

            bool IsValid() const
            {
                return (true);
            }

            UninstallParamsData(const UninstallParamsData&) = delete;
            UninstallParamsData& operator=(const UninstallParamsData&) = delete;

        public:
            Core::JSON::String PackageId; // Package Id
        }; // class UninstallParamsData

    } // namespace PackageInstaller

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IPackageInstaller::FailReason)
ENUM_CONVERSION_HANDLER(Exchange::IPackageInstaller::InstallState)

}

