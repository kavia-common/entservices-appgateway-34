// C++ classes for AppManager API JSON-RPC API.
// Generated automatically from 'IAppManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAppManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace AppManager {

        // Common classes
        //

        class IsInstalledParamsInfo : public Core::JSON::Container {
        public:
            IsInstalledParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
            }

            bool IsValid() const
            {
                return (true);
            }

            IsInstalledParamsInfo(const IsInstalledParamsInfo&) = delete;
            IsInstalledParamsInfo& operator=(const IsInstalledParamsInfo&) = delete;

        public:
            Core::JSON::String AppId; // check whether the Application is installed or not
        }; // class IsInstalledParamsInfo

        // Method params/result classes
        //

        class GetAppMetadataParamsData : public Core::JSON::Container {
        public:
            GetAppMetadataParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("metaData"), &MetaData);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetAppMetadataParamsData(const GetAppMetadataParamsData&) = delete;
            GetAppMetadataParamsData& operator=(const GetAppMetadataParamsData&) = delete;

        public:
            Core::JSON::String AppId; // App identifier for the application.
            Core::JSON::String MetaData; // the name of the meta-data
        }; // class GetAppMetadataParamsData

        class GetAppPropertyParamsData : public Core::JSON::Container {
        public:
            GetAppPropertyParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("key"), &Key);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetAppPropertyParamsData(const GetAppPropertyParamsData&) = delete;
            GetAppPropertyParamsData& operator=(const GetAppPropertyParamsData&) = delete;

        public:
            Core::JSON::String AppId; // App identifier for the application.
            Core::JSON::String Key; // the name of the property to get
        }; // class GetAppPropertyParamsData

        class LoadedAppInfoData : public Core::JSON::Container {
        public:
            LoadedAppInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            LoadedAppInfoData(const LoadedAppInfoData& _other)
                : Core::JSON::Container()
                , AppId(_other.AppId)
                , AppInstanceId(_other.AppInstanceId)
                , ActiveSessionId(_other.ActiveSessionId)
                , Type(_other.Type)
                , TargetLifecycleState(_other.TargetLifecycleState)
                , LifecycleState(_other.LifecycleState)
            {
                _Init();
            }

            LoadedAppInfoData& operator=(const LoadedAppInfoData& _rhs)
            {
                AppId = _rhs.AppId;
                AppInstanceId = _rhs.AppInstanceId;
                ActiveSessionId = _rhs.ActiveSessionId;
                Type = _rhs.Type;
                TargetLifecycleState = _rhs.TargetLifecycleState;
                LifecycleState = _rhs.LifecycleState;
                return (*this);
            }

            LoadedAppInfoData(const Exchange::IAppManager::LoadedAppInfo& _other)
                : Core::JSON::Container()
            {
                AppId = _other.appId;
                AppInstanceId = _other.appInstanceId;
                ActiveSessionId = _other.activeSessionId;
                Type = _other.type;
                TargetLifecycleState = _other.targetLifecycleState;
                LifecycleState = _other.lifecycleState;
                _Init();
            }

            LoadedAppInfoData& operator=(const Exchange::IAppManager::LoadedAppInfo& _rhs)
            {
                AppId = _rhs.appId;
                AppInstanceId = _rhs.appInstanceId;
                ActiveSessionId = _rhs.activeSessionId;
                Type = _rhs.type;
                TargetLifecycleState = _rhs.targetLifecycleState;
                LifecycleState = _rhs.lifecycleState;
                return (*this);
            }

            operator Exchange::IAppManager::LoadedAppInfo() const
            {
                Exchange::IAppManager::LoadedAppInfo _value{};
                _value.appId = AppId;
                _value.appInstanceId = AppInstanceId;
                _value.activeSessionId = ActiveSessionId;
                _value.type = Type;
                _value.targetLifecycleState = TargetLifecycleState;
                _value.lifecycleState = LifecycleState;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("appId"), &AppId);
                Add(_T("appInstanceId"), &AppInstanceId);
                Add(_T("activeSessionId"), &ActiveSessionId);
                Add(_T("type"), &Type);
                Add(_T("targetLifecycleState"), &TargetLifecycleState);
                Add(_T("lifecycleState"), &LifecycleState);
            }

        public:
            Core::JSON::String AppId; // App identifier for the application
            Core::JSON::String AppInstanceId; // A numerical identifier for a specific instance of the application
            Core::JSON::String ActiveSessionId; // Identifier for the active session associated with the application instance
            Core::JSON::String Type; // The type or category of the application
            Core::JSON::EnumType<Exchange::IAppManager::AppLifecycleState> TargetLifecycleState; // The desired lifecycle state that the application is transitioning to
            Core::JSON::EnumType<Exchange::IAppManager::AppLifecycleState> LifecycleState; // The current lifecycle state of the application instance
        }; // class LoadedAppInfoData

        class LaunchAppParamsData : public Core::JSON::Container {
        public:
            LaunchAppParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("intent"), &Intent);
                Add(_T("launchArgs"), &LaunchArgs);
            }

            bool IsValid() const
            {
                return (true);
            }

            LaunchAppParamsData(const LaunchAppParamsData&) = delete;
            LaunchAppParamsData& operator=(const LaunchAppParamsData&) = delete;

        public:
            Core::JSON::String AppId; // App identifier for the application.
            Core::JSON::String Intent; // Launch an Application and app will be in ACTIVE state.
            Core::JSON::String LaunchArgs; // Launch an Application and app will be in ACTIVE state.
        }; // class LaunchAppParamsData

        class OnAppInstalledParamsData : public Core::JSON::Container {
        public:
            OnAppInstalledParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("version"), &Version);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppInstalledParamsData(const OnAppInstalledParamsData&) = delete;
            OnAppInstalledParamsData& operator=(const OnAppInstalledParamsData&) = delete;

        public:
            Core::JSON::String AppId; // Triggered whenever the App is installed.
            Core::JSON::String Version; // The version number of the application in string format
        }; // class OnAppInstalledParamsData

        class OnAppLaunchRequestParamsData : public Core::JSON::Container {
        public:
            OnAppLaunchRequestParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("intent"), &Intent);
                Add(_T("source"), &Source);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppLaunchRequestParamsData(const OnAppLaunchRequestParamsData&) = delete;
            OnAppLaunchRequestParamsData& operator=(const OnAppLaunchRequestParamsData&) = delete;

        public:
            Core::JSON::String AppId; // Triggered whenever there is a request for App Launch.
            Core::JSON::String Intent; // Triggered whenever there is a request for App Launch.
            Core::JSON::String Source; // Triggered whenever there is a request for App Launch.
        }; // class OnAppLaunchRequestParamsData

        class OnAppLifecycleStateChangedParamsData : public Core::JSON::Container {
        public:
            OnAppLifecycleStateChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("appInstanceId"), &AppInstanceId);
                Add(_T("newState"), &NewState);
                Add(_T("oldState"), &OldState);
                Add(_T("errorReason"), &ErrorReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppLifecycleStateChangedParamsData(const OnAppLifecycleStateChangedParamsData&) = delete;
            OnAppLifecycleStateChangedParamsData& operator=(const OnAppLifecycleStateChangedParamsData&) = delete;

        public:
            Core::JSON::String AppId; // Triggered whenever there is a change in the lifecycle state of a running app.
            Core::JSON::String AppInstanceId; // Triggered whenever there is a change in the lifecycle state of a running app.
            Core::JSON::EnumType<Exchange::IAppManager::AppLifecycleState> NewState; // Triggered whenever there is a change in the lifecycle state of a running app.
            Core::JSON::EnumType<Exchange::IAppManager::AppLifecycleState> OldState; // Triggered whenever there is a change in the lifecycle state of a running app.
            Core::JSON::EnumType<Exchange::IAppManager::AppErrorReason> ErrorReason; // Triggered whenever there is a change in the lifecycle state of a running app.
        }; // class OnAppLifecycleStateChangedParamsData

        class OnAppUnloadedParamsData : public Core::JSON::Container {
        public:
            OnAppUnloadedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("appInstanceId"), &AppInstanceId);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppUnloadedParamsData(const OnAppUnloadedParamsData&) = delete;
            OnAppUnloadedParamsData& operator=(const OnAppUnloadedParamsData&) = delete;

        public:
            Core::JSON::String AppId; // Triggered whenever the App is unloaded(terminated).
            Core::JSON::String AppInstanceId; // Triggered whenever the App is unloaded(terminated).
        }; // class OnAppUnloadedParamsData

        class PreloadAppParamsData : public Core::JSON::Container {
        public:
            PreloadAppParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("launchArgs"), &LaunchArgs);
            }

            bool IsValid() const
            {
                return (true);
            }

            PreloadAppParamsData(const PreloadAppParamsData&) = delete;
            PreloadAppParamsData& operator=(const PreloadAppParamsData&) = delete;

        public:
            Core::JSON::String AppId; // App identifier for the application.
            Core::JSON::String LaunchArgs; // Preloads an Application and app will be in the RUNNING state (hidden).
        }; // class PreloadAppParamsData

        class SendIntentParamsData : public Core::JSON::Container {
        public:
            SendIntentParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("intent"), &Intent);
            }

            bool IsValid() const
            {
                return (true);
            }

            SendIntentParamsData(const SendIntentParamsData&) = delete;
            SendIntentParamsData& operator=(const SendIntentParamsData&) = delete;

        public:
            Core::JSON::String AppId; // App identifier for the application.
            Core::JSON::String Intent; // Specifies the intent or message to be executed.
        }; // class SendIntentParamsData

        class SetAppPropertyParamsData : public Core::JSON::Container {
        public:
            SetAppPropertyParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("key"), &Key);
                Add(_T("value"), &Value);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetAppPropertyParamsData(const SetAppPropertyParamsData&) = delete;
            SetAppPropertyParamsData& operator=(const SetAppPropertyParamsData&) = delete;

        public:
            Core::JSON::String AppId; // App identifier for the application.
            Core::JSON::String Key; // the name of the property to get
            Core::JSON::String Value; // the property value to set, this can be a boolean,number, string or object type
        }; // class SetAppPropertyParamsData

    } // namespace AppManager

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IAppManager::AppLifecycleState)
ENUM_CONVERSION_HANDLER(Exchange::IAppManager::AppErrorReason)

}

