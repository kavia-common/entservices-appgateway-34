// Generated automatically from 'IAppManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_AppManager.h"
#include <interfaces/IAppManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JAppManager {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IAppManager* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JAppManager"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getInstalledApps' - Function fetches the details of all applications currently installed
            _module_.Register<void, Core::JSON::String>(_T("getInstalledApps"), 
                [_impl_](Core::JSON::String& apps) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _apps{};

                    _errorCode = _impl_->GetInstalledApps(_apps);

                    if (_errorCode == Core::ERROR_NONE) {
                        apps = _apps;
                        apps.SetQuoted(false);
                    }

                    return (_errorCode);
                });

            // Method: 'isInstalled' - check whether the Application is installed or not
            _module_.Register<JsonData::AppManager::IsInstalledParamsInfo, Core::JSON::Boolean>(_T("isInstalled"), 
                [_impl_](const JsonData::AppManager::IsInstalledParamsInfo& params, Core::JSON::Boolean& installed) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    bool _installed{};

                    _errorCode = _impl_->IsInstalled(_appId, _installed);

                    if (_errorCode == Core::ERROR_NONE) {
                        installed = _installed;
                    }

                    return (_errorCode);
                });

            // Method: 'getLoadedApps' - Retrieves a list of applications currently loaded on the system
            _module_.Register<void, Core::JSON::ArrayType<JsonData::AppManager::LoadedAppInfoData>>(_T("getLoadedApps"), 
                [_impl_](Core::JSON::ArrayType<JsonData::AppManager::LoadedAppInfoData>& apps) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<IAppManager::LoadedAppInfo, ID_LOADED_APP_INFO_ITERATOR>* _apps{};

                    _errorCode = _impl_->GetLoadedApps(_apps);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_apps != nullptr) {
                            Exchange::IAppManager::LoadedAppInfo _resultItem_{};
                            while (_apps->Next(_resultItem_) == true) { apps.Add() = _resultItem_; }
                            _apps->Release();
                        }
                    }

                    return (_errorCode);
                });

            // Method: 'launchApp' - Launch an Application and app will be in ACTIVE state
            _module_.Register<JsonData::AppManager::LaunchAppParamsData, void>(_T("launchApp"), 
                [_impl_](const JsonData::AppManager::LaunchAppParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const string _intent{params.Intent};
                    const string _launchArgs{params.LaunchArgs};

                    _errorCode = _impl_->LaunchApp(_appId, _intent, _launchArgs);

                    return (_errorCode);
                });

            // Method: 'preloadApp' - Preloads an Application and app will be in the RUNNING state (hidden)
            _module_.Register<JsonData::AppManager::PreloadAppParamsData, Core::JSON::String>(_T("preloadApp"), 
                [_impl_](const JsonData::AppManager::PreloadAppParamsData& params, Core::JSON::String& error) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const string _launchArgs{params.LaunchArgs};
                    string _error{};

                    _errorCode = _impl_->PreloadApp(_appId, _launchArgs, _error);

                    if (_errorCode == Core::ERROR_NONE) {
                        error = _error;
                    }

                    return (_errorCode);
                });

            // Method: 'closeApp' - closeApp moves the state from Active to Running state
            _module_.Register<JsonData::AppManager::IsInstalledParamsInfo, void>(_T("closeApp"), 
                [_impl_](const JsonData::AppManager::IsInstalledParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};

                    _errorCode = _impl_->CloseApp(_appId);

                    return (_errorCode);
                });

            // Method: 'terminateApp' - TerminateApp will terminate gracefully
            _module_.Register<JsonData::AppManager::IsInstalledParamsInfo, void>(_T("terminateApp"), 
                [_impl_](const JsonData::AppManager::IsInstalledParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};

                    _errorCode = _impl_->TerminateApp(_appId);

                    return (_errorCode);
                });

            // Method: 'startSystemApp' - Start the System Application
            _module_.Register<JsonData::AppManager::IsInstalledParamsInfo, void>(_T("startSystemApp"), 
                [_impl_](const JsonData::AppManager::IsInstalledParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};

                    _errorCode = _impl_->StartSystemApp(_appId);

                    return (_errorCode);
                });

            // Method: 'stopSystemApp' - Stop the System Application
            _module_.Register<JsonData::AppManager::IsInstalledParamsInfo, void>(_T("stopSystemApp"), 
                [_impl_](const JsonData::AppManager::IsInstalledParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};

                    _errorCode = _impl_->StopSystemApp(_appId);

                    return (_errorCode);
                });

            // Method: 'killApp' - killApp will terminate forcefully
            _module_.Register<JsonData::AppManager::IsInstalledParamsInfo, void>(_T("killApp"), 
                [_impl_](const JsonData::AppManager::IsInstalledParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};

                    _errorCode = _impl_->KillApp(_appId);

                    return (_errorCode);
                });

            // Method: 'sendIntent' - Sends an intent to a loaded app
            _module_.Register<JsonData::AppManager::SendIntentParamsData, void>(_T("sendIntent"), 
                [_impl_](const JsonData::AppManager::SendIntentParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const string _intent{params.Intent};

                    _errorCode = _impl_->SendIntent(_appId, _intent);

                    return (_errorCode);
                });

            // Method: 'clearAppData' - Clears all persistent data for a given appId
            _module_.Register<JsonData::AppManager::IsInstalledParamsInfo, void>(_T("clearAppData"), 
                [_impl_](const JsonData::AppManager::IsInstalledParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};

                    _errorCode = _impl_->ClearAppData(_appId);

                    return (_errorCode);
                });

            // Method: 'clearAllAppData' - Clears all persistent data for all apps
            _module_.Register<void, void>(_T("clearAllAppData"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->ClearAllAppData();

                    return (_errorCode);
                });

            // Method: 'getAppMetadata' - Retrieves meta data about an installed app
            _module_.Register<JsonData::AppManager::GetAppMetadataParamsData, Core::JSON::String>(_T("getAppMetadata"), 
                [_impl_](const JsonData::AppManager::GetAppMetadataParamsData& params, Core::JSON::String& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const string _metaData{params.MetaData};
                    string _result{};

                    _errorCode = _impl_->GetAppMetadata(_appId, _metaData, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'getAppProperty' - Gets a property for a given app
            _module_.Register<JsonData::AppManager::GetAppPropertyParamsData, Core::JSON::String>(_T("getAppProperty"), 
                [_impl_](const JsonData::AppManager::GetAppPropertyParamsData& params, Core::JSON::String& value) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const string _key{params.Key};
                    string _value{};

                    _errorCode = _impl_->GetAppProperty(_appId, _key, _value);

                    if (_errorCode == Core::ERROR_NONE) {
                        value = _value;
                    }

                    return (_errorCode);
                });

            // Method: 'setAppProperty' - Sets a property for a given app
            _module_.Register<JsonData::AppManager::SetAppPropertyParamsData, void>(_T("setAppProperty"), 
                [_impl_](const JsonData::AppManager::SetAppPropertyParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const string _key{params.Key};
                    const string _value{params.Value};

                    _errorCode = _impl_->SetAppProperty(_appId, _key, _value);

                    return (_errorCode);
                });

            // Property: 'getMaxRunningApps' - Gets the maximum number of apps to maintain in the running or suspended state (r/o)
            _module_.Register<void, Core::JSON::DecSInt32>(_T("getMaxRunningApps"), 
                [_impl_](Core::JSON::DecSInt32& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    int32_t _result{};

                    _errorCode = _impl_->GetMaxRunningApps(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'getMaxHibernatedApps' - Get the maximum number of apps to maintain in the hibernated state (r/o)
            _module_.Register<void, Core::JSON::DecSInt32>(_T("getMaxHibernatedApps"), 
                [_impl_](Core::JSON::DecSInt32& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    int32_t _result{};

                    _errorCode = _impl_->GetMaxHibernatedApps(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'getMaxHibernatedFlashUsage' - Gets the max size of flash to use for hibernated apps (in mebibytes) (r/o)
            _module_.Register<void, Core::JSON::DecSInt32>(_T("getMaxHibernatedFlashUsage"), 
                [_impl_](Core::JSON::DecSInt32& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    int32_t _result{};

                    _errorCode = _impl_->GetMaxHibernatedFlashUsage(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'getMaxInactiveRamUsage' - Gets the max amount of ram available for inactive apps (in mebibytes) (r/o)
            _module_.Register<void, Core::JSON::DecSInt32>(_T("getMaxInactiveRamUsage"), 
                [_impl_](Core::JSON::DecSInt32& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    int32_t _result{};

                    _errorCode = _impl_->GetMaxInactiveRamUsage(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getInstalledApps"));
            _module_.Unregister(_T("isInstalled"));
            _module_.Unregister(_T("getLoadedApps"));
            _module_.Unregister(_T("launchApp"));
            _module_.Unregister(_T("preloadApp"));
            _module_.Unregister(_T("closeApp"));
            _module_.Unregister(_T("terminateApp"));
            _module_.Unregister(_T("startSystemApp"));
            _module_.Unregister(_T("stopSystemApp"));
            _module_.Unregister(_T("killApp"));
            _module_.Unregister(_T("sendIntent"));
            _module_.Unregister(_T("clearAppData"));
            _module_.Unregister(_T("clearAllAppData"));
            _module_.Unregister(_T("getAppMetadata"));
            _module_.Unregister(_T("getAppProperty"));
            _module_.Unregister(_T("setAppProperty"));
            _module_.Unregister(_T("getMaxRunningApps"));
            _module_.Unregister(_T("getMaxHibernatedApps"));
            _module_.Unregister(_T("getMaxHibernatedFlashUsage"));
            _module_.Unregister(_T("getMaxInactiveRamUsage"));
        }

        namespace Event {

            // Event: 'onAppInstalled' - Triggered whenever the App is installed
            static void OnAppInstalled(const JSONRPC& _module_, const JsonData::AppManager::OnAppInstalledParamsData& params)
            {
                _module_.Notify(_T("onAppInstalled"), params);
            }

            // Event: 'onAppInstalled' - Triggered whenever the App is installed
            static void OnAppInstalled(const JSONRPC& _module_, const Core::JSON::String& appId, const Core::JSON::String& version)
            {
                JsonData::AppManager::OnAppInstalledParamsData _params_;
                _params_.AppId = appId;
                _params_.Version = version;

                OnAppInstalled(_module_, _params_);
            }

            // Event: 'onAppInstalled' - Triggered whenever the App is installed
            static void OnAppInstalled(const JSONRPC& _module_, const string& appId, const string& version)
            {
                JsonData::AppManager::OnAppInstalledParamsData _params_;
                _params_.AppId = appId;
                _params_.Version = version;

                OnAppInstalled(_module_, _params_);
            }

            // Event: 'onAppUninstalled' - Triggered whenever the App is uninstalled
            static void OnAppUninstalled(const JSONRPC& _module_, const JsonData::AppManager::IsInstalledParamsInfo& params)
            {
                _module_.Notify(_T("onAppUninstalled"), params);
            }

            // Event: 'onAppUninstalled' - Triggered whenever the App is uninstalled
            static void OnAppUninstalled(const JSONRPC& _module_, const Core::JSON::String& appId)
            {
                JsonData::AppManager::IsInstalledParamsInfo _params_;
                _params_.AppId = appId;

                OnAppUninstalled(_module_, _params_);
            }

            // Event: 'onAppUninstalled' - Triggered whenever the App is uninstalled
            static void OnAppUninstalled(const JSONRPC& _module_, const string& appId)
            {
                JsonData::AppManager::IsInstalledParamsInfo _params_;
                _params_.AppId = appId;

                OnAppUninstalled(_module_, _params_);
            }

            // Event: 'onAppLifecycleStateChanged' - Triggered whenever there is a change in the lifecycle state of a running app
            static void OnAppLifecycleStateChanged(const JSONRPC& _module_, const JsonData::AppManager::OnAppLifecycleStateChangedParamsData& params)
            {
                _module_.Notify(_T("onAppLifecycleStateChanged"), params);
            }

            // Event: 'onAppLifecycleStateChanged' - Triggered whenever there is a change in the lifecycle state of a running app
            static void OnAppLifecycleStateChanged(const JSONRPC& _module_, const Core::JSON::String& appId, const Core::JSON::String& appInstanceId,
                     const Core::JSON::EnumType<Exchange::IAppManager::AppLifecycleState>& newState,
                     const Core::JSON::EnumType<Exchange::IAppManager::AppLifecycleState>& oldState, const Core::JSON::EnumType<Exchange::IAppManager::AppErrorReason>& errorReason)
            {
                JsonData::AppManager::OnAppLifecycleStateChangedParamsData _params_;
                _params_.AppId = appId;
                _params_.AppInstanceId = appInstanceId;
                _params_.NewState = newState;
                _params_.OldState = oldState;
                _params_.ErrorReason = errorReason;

                OnAppLifecycleStateChanged(_module_, _params_);
            }

            // Event: 'onAppLifecycleStateChanged' - Triggered whenever there is a change in the lifecycle state of a running app
            static void OnAppLifecycleStateChanged(const JSONRPC& _module_, const string& appId, const string& appInstanceId,
                     const Exchange::IAppManager::AppLifecycleState& newState, const Exchange::IAppManager::AppLifecycleState& oldState, const Exchange::IAppManager::AppErrorReason& errorReason)
            {
                JsonData::AppManager::OnAppLifecycleStateChangedParamsData _params_;
                _params_.AppId = appId;
                _params_.AppInstanceId = appInstanceId;
                _params_.NewState = newState;
                _params_.OldState = oldState;
                _params_.ErrorReason = errorReason;

                OnAppLifecycleStateChanged(_module_, _params_);
            }

            // Event: 'onAppLaunchRequest' - Triggered whenever there is a request for App Launch
            static void OnAppLaunchRequest(const JSONRPC& _module_, const JsonData::AppManager::OnAppLaunchRequestParamsData& params)
            {
                _module_.Notify(_T("onAppLaunchRequest"), params);
            }

            // Event: 'onAppLaunchRequest' - Triggered whenever there is a request for App Launch
            static void OnAppLaunchRequest(const JSONRPC& _module_, const Core::JSON::String& appId, const Core::JSON::String& intent,
                     const Core::JSON::String& source)
            {
                JsonData::AppManager::OnAppLaunchRequestParamsData _params_;
                _params_.AppId = appId;
                _params_.Intent = intent;
                _params_.Source = source;

                OnAppLaunchRequest(_module_, _params_);
            }

            // Event: 'onAppLaunchRequest' - Triggered whenever there is a request for App Launch
            static void OnAppLaunchRequest(const JSONRPC& _module_, const string& appId, const string& intent, const string& source)
            {
                JsonData::AppManager::OnAppLaunchRequestParamsData _params_;
                _params_.AppId = appId;
                _params_.Intent = intent;
                _params_.Source = source;

                OnAppLaunchRequest(_module_, _params_);
            }

            // Event: 'onAppUnloaded' - Triggered whenever the App is unloaded(terminated)
            static void OnAppUnloaded(const JSONRPC& _module_, const JsonData::AppManager::OnAppUnloadedParamsData& params)
            {
                _module_.Notify(_T("onAppUnloaded"), params);
            }

            // Event: 'onAppUnloaded' - Triggered whenever the App is unloaded(terminated)
            static void OnAppUnloaded(const JSONRPC& _module_, const Core::JSON::String& appId, const Core::JSON::String& appInstanceId)
            {
                JsonData::AppManager::OnAppUnloadedParamsData _params_;
                _params_.AppId = appId;
                _params_.AppInstanceId = appInstanceId;

                OnAppUnloaded(_module_, _params_);
            }

            // Event: 'onAppUnloaded' - Triggered whenever the App is unloaded(terminated)
            static void OnAppUnloaded(const JSONRPC& _module_, const string& appId, const string& appInstanceId)
            {
                JsonData::AppManager::OnAppUnloadedParamsData _params_;
                _params_.AppId = appId;
                _params_.AppInstanceId = appInstanceId;

                OnAppUnloaded(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JAppManager

} // namespace Exchange

} // namespace WPEFramework

