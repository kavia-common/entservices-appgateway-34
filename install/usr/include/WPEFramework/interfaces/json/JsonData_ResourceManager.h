// C++ classes for ResourceManager API JSON-RPC API.
// Generated automatically from 'IResourceManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IResourceManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace ResourceManager {

        // Common classes
        //

        class SetAVBlockedResultInfo : public Core::JSON::Container {
        public:
            SetAVBlockedResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            SetAVBlockedResultInfo(const Exchange::IResourceManager::SetAVBlockedResult& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            SetAVBlockedResultInfo& operator=(const Exchange::IResourceManager::SetAVBlockedResult& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IResourceManager::SetAVBlockedResult() const
            {
                Exchange::IResourceManager::SetAVBlockedResult _value{};
                _value.success = Success;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::Boolean Success; // Sets AV blocking status for an application
        }; // class SetAVBlockedResultInfo

        // Method params/result classes
        //

        class GetBlockedAVApplicationsResultData : public Core::JSON::Container {
        public:
            GetBlockedAVApplicationsResultData()
                : Core::JSON::Container()
            {
                Add(_T("clients"), &Clients);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetBlockedAVApplicationsResultData(const GetBlockedAVApplicationsResultData&) = delete;
            GetBlockedAVApplicationsResultData& operator=(const GetBlockedAVApplicationsResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> Clients; // list of blocked applications
            Core::JSON::Boolean Success; // success status
        }; // class GetBlockedAVApplicationsResultData

        class ReserveTTSResourceParamsData : public Core::JSON::Container {
        public:
            ReserveTTSResourceParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReserveTTSResourceParamsData(const ReserveTTSResourceParamsData&) = delete;
            ReserveTTSResourceParamsData& operator=(const ReserveTTSResourceParamsData&) = delete;

        public:
            Core::JSON::String AppId; // - in - string
        }; // class ReserveTTSResourceParamsData

        class ReserveTTSResourceForAppsParamsData : public Core::JSON::Container {
        public:
            ReserveTTSResourceForAppsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appids"), &Appids);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReserveTTSResourceForAppsParamsData(const ReserveTTSResourceForAppsParamsData&) = delete;
            ReserveTTSResourceForAppsParamsData& operator=(const ReserveTTSResourceForAppsParamsData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> Appids; // list of application IDs
        }; // class ReserveTTSResourceForAppsParamsData

        class SetAVBlockedParamsData : public Core::JSON::Container {
        public:
            SetAVBlockedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("blocked"), &Blocked);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetAVBlockedParamsData(const SetAVBlockedParamsData&) = delete;
            SetAVBlockedParamsData& operator=(const SetAVBlockedParamsData&) = delete;

        public:
            Core::JSON::String AppId; // - in - string
            Core::JSON::Boolean Blocked; // - in - bool
        }; // class SetAVBlockedParamsData

    } // namespace ResourceManager

} // namespace JsonData

}

