// C++ classes for StorageManager API JSON-RPC API.
// Generated automatically from 'IStorageManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IStorageManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace StorageManager {

        // Method params/result classes
        //

        class ClearAllParamsData : public Core::JSON::Container {
        public:
            ClearAllParamsData()
                : Core::JSON::Container()
            {
                Add(_T("exemptionAppIds"), &ExemptionAppIds);
            }

            bool IsValid() const
            {
                return (true);
            }

            ClearAllParamsData(const ClearAllParamsData&) = delete;
            ClearAllParamsData& operator=(const ClearAllParamsData&) = delete;

        public:
            Core::JSON::String ExemptionAppIds; // - in - string Clears all app data except for the exempt app ids as a json format
        }; // class ClearAllParamsData

        class ClearParamsData : public Core::JSON::Container {
        public:
            ClearParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
            }

            bool IsValid() const
            {
                return (true);
            }

            ClearParamsData(const ClearParamsData&) = delete;
            ClearParamsData& operator=(const ClearParamsData&) = delete;

        public:
            Core::JSON::String AppId; // - in - string App identifier for the application.
        }; // class ClearParamsData

    } // namespace StorageManager

} // namespace JsonData

}

