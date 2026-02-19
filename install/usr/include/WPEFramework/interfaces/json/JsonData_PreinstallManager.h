// C++ classes for PreinstallManager API JSON-RPC API.
// Generated automatically from 'IPreinstallManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IPreinstallManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace PreinstallManager {

        // Method params/result classes
        //

        class OnAppInstallationStatusParamsData : public Core::JSON::Container {
        public:
            OnAppInstallationStatusParamsData()
                : Core::JSON::Container()
            {
                Add(_T("jsonresponse"), &Jsonresponse);
                Jsonresponse.SetQuoted(false);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppInstallationStatusParamsData(const OnAppInstallationStatusParamsData&) = delete;
            OnAppInstallationStatusParamsData& operator=(const OnAppInstallationStatusParamsData&) = delete;

        public:
            Core::JSON::String Jsonresponse; // Output installation status details as string object
        }; // class OnAppInstallationStatusParamsData

        class StartPreinstallParamsData : public Core::JSON::Container {
        public:
            StartPreinstallParamsData()
                : Core::JSON::Container()
            {
                Add(_T("forceInstall"), &ForceInstall);
            }

            bool IsValid() const
            {
                return (true);
            }

            StartPreinstallParamsData(const StartPreinstallParamsData&) = delete;
            StartPreinstallParamsData& operator=(const StartPreinstallParamsData&) = delete;

        public:
            Core::JSON::Boolean ForceInstall; // Checks the preinstall directory for packages to be preinstalled and installs them as needed.
        }; // class StartPreinstallParamsData

    } // namespace PreinstallManager

} // namespace JsonData

}

