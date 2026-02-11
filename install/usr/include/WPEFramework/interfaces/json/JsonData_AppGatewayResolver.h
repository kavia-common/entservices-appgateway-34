// C++ classes for AppGatewayResolver API JSON-RPC API.
// Generated automatically from 'IAppGateway.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAppGateway.h>

namespace WPEFramework {

namespace JsonData {

    namespace AppGatewayResolver {

        // Method params/result classes
        //

        class ConfigureParamsData : public Core::JSON::Container {
        public:
            ConfigureParamsData()
                : Core::JSON::Container()
            {
                Add(_T("paths"), &Paths);
            }

            bool IsValid() const
            {
                return (true);
            }

            ConfigureParamsData(const ConfigureParamsData&) = delete;
            ConfigureParamsData& operator=(const ConfigureParamsData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> Paths; // Adds set of paths in the order of override to be used by gateway to update the resolutions
        }; // class ConfigureParamsData

    } // namespace AppGatewayResolver

} // namespace JsonData

}

