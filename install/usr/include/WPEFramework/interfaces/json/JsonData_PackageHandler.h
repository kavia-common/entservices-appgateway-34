// C++ classes for PackageHandler API JSON-RPC API.
// Generated automatically from 'IAppPackageManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAppPackageManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace PackageHandler {

        // Common classes
        //

        class AdditionalLockInfo : public Core::JSON::Container {
        public:
            AdditionalLockInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            AdditionalLockInfo(const AdditionalLockInfo& _other)
                : Core::JSON::Container()
                , PackageId(_other.PackageId)
                , Version(_other.Version)
            {
                _Init();
            }

            AdditionalLockInfo& operator=(const AdditionalLockInfo& _rhs)
            {
                PackageId = _rhs.PackageId;
                Version = _rhs.Version;
                return (*this);
            }

            AdditionalLockInfo(const Exchange::IPackageHandler::AdditionalLock& _other)
                : Core::JSON::Container()
            {
                PackageId = _other.packageId;
                Version = _other.version;
                _Init();
            }

            AdditionalLockInfo& operator=(const Exchange::IPackageHandler::AdditionalLock& _rhs)
            {
                PackageId = _rhs.packageId;
                Version = _rhs.version;
                return (*this);
            }

            operator Exchange::IPackageHandler::AdditionalLock() const
            {
                Exchange::IPackageHandler::AdditionalLock _value{};
                _value.packageId = PackageId;
                _value.version = Version;
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
            }

        public:
            Core::JSON::String PackageId; // PackageId
            Core::JSON::String Version; // Version
        }; // class AdditionalLockInfo

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
            Core::JSON::Boolean Dial;
            Core::JSON::Boolean WanLanAccess;
            Core::JSON::Boolean Thunder;
            Core::JSON::DecSInt32 SystemMemoryLimit;
            Core::JSON::DecSInt32 GpuMemoryLimit;
            Core::JSON::String EnvVariables;
            Core::JSON::DecUInt32 UserId;
            Core::JSON::DecUInt32 GroupId;
            Core::JSON::DecUInt32 DataImageSize;
            Core::JSON::Boolean ResourceManagerClientEnabled;
            Core::JSON::String DialId;
            Core::JSON::String Command;
            Core::JSON::String AppType;
            Core::JSON::String AppPath;
            Core::JSON::String RuntimePath;
            Core::JSON::String LogFilePath;
            Core::JSON::DecUInt32 LogFileMaxSize;
            Core::JSON::String LogLevels;
            Core::JSON::Boolean Mapi;
            Core::JSON::String FkpsFiles;
            Core::JSON::String FireboltVersion;
            Core::JSON::Boolean EnableDebugger;
        }; // class RuntimeConfigInfo

        // Method params/result classes
        //

        class GetLockedInfoResultData : public Core::JSON::Container {
        public:
            GetLockedInfoResultData()
                : Core::JSON::Container()
            {
                Add(_T("unpackedPath"), &UnpackedPath);
                Add(_T("configMetadata"), &ConfigMetadata);
                Add(_T("gatewayMetadataPath"), &GatewayMetadataPath);
                Add(_T("locked"), &Locked);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetLockedInfoResultData(const GetLockedInfoResultData&) = delete;
            GetLockedInfoResultData& operator=(const GetLockedInfoResultData&) = delete;

        public:
            Core::JSON::String UnpackedPath; // GetLockedInfo
            RuntimeConfigInfo ConfigMetadata; // GetLockedInfo
            Core::JSON::String GatewayMetadataPath; // GetLockedInfo
            Core::JSON::Boolean Locked; // GetLockedInfo
        }; // class GetLockedInfoResultData

        class LockParamsData : public Core::JSON::Container {
        public:
            LockParamsData()
                : Core::JSON::Container()
            {
                Add(_T("packageId"), &PackageId);
                Add(_T("version"), &Version);
                Add(_T("lockReason"), &LockReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            LockParamsData(const LockParamsData&) = delete;
            LockParamsData& operator=(const LockParamsData&) = delete;

        public:
            Core::JSON::String PackageId; // Package Id
            Core::JSON::String Version; // Version
            Core::JSON::EnumType<Exchange::IPackageHandler::LockReason> LockReason; // LockReason
        }; // class LockParamsData

        class LockResultData : public Core::JSON::Container {
        public:
            LockResultData()
                : Core::JSON::Container()
            {
                Add(_T("lockId"), &LockId);
                Add(_T("unpackedPath"), &UnpackedPath);
                Add(_T("configMetadata"), &ConfigMetadata);
                Add(_T("appMetadata"), &AppMetadata);
            }

            bool IsValid() const
            {
                return (true);
            }

            LockResultData(const LockResultData&) = delete;
            LockResultData& operator=(const LockResultData&) = delete;

        public:
            Core::JSON::DecUInt32 LockId; // Lock Id
            Core::JSON::String UnpackedPath; // Unpacked Path
            RuntimeConfigInfo ConfigMetadata; // Config Metadata
            Core::JSON::ArrayType<AdditionalLockInfo> AppMetadata; // App Metadata
        }; // class LockResultData

    } // namespace PackageHandler

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IPackageInstaller::FailReason)
ENUM_CONVERSION_HANDLER(Exchange::IPackageInstaller::InstallState)
ENUM_CONVERSION_HANDLER(Exchange::IPackageHandler::LockReason)

}

