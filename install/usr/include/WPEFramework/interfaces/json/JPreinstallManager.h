// Generated automatically from 'IPreinstallManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_PreinstallManager.h"
#include <interfaces/IPreinstallManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JPreinstallManager {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IPreinstallManager* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JPreinstallManager"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'startPreinstall' - Checks the preinstall directory for packages to be preinstalled and installs them as needed
            _module_.Register<JsonData::PreinstallManager::StartPreinstallParamsData, void>(_T("startPreinstall"), 
                [_impl_](const JsonData::PreinstallManager::StartPreinstallParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _forceInstall{params.ForceInstall};

                    _errorCode = _impl_->StartPreinstall(_forceInstall);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("startPreinstall"));
        }

        namespace Event {

            // Event: 'onAppInstallationStatus' - Emitted when the installation of a preinstalled app succeeds or fails
            static void OnAppInstallationStatus(const JSONRPC& _module_, const JsonData::PreinstallManager::OnAppInstallationStatusParamsData& params)
            {
                _module_.Notify(_T("onAppInstallationStatus"), params);
            }

            // Event: 'onAppInstallationStatus' - Emitted when the installation of a preinstalled app succeeds or fails
            static void OnAppInstallationStatus(const JSONRPC& _module_, const Core::JSON::String& jsonresponse)
            {
                JsonData::PreinstallManager::OnAppInstallationStatusParamsData _params_;
                _params_.Jsonresponse = jsonresponse;
                _params_.Jsonresponse.SetQuoted(false);

                OnAppInstallationStatus(_module_, _params_);
            }

            // Event: 'onAppInstallationStatus' - Emitted when the installation of a preinstalled app succeeds or fails
            static void OnAppInstallationStatus(const JSONRPC& _module_, const string& jsonresponse)
            {
                JsonData::PreinstallManager::OnAppInstallationStatusParamsData _params_;
                _params_.Jsonresponse = jsonresponse;
                _params_.Jsonresponse.SetQuoted(false);

                OnAppInstallationStatus(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JPreinstallManager

} // namespace Exchange

} // namespace WPEFramework

