// C++ classes for UserSettingsInspector API JSON-RPC API.
// Generated automatically from 'IUserSettings.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IUserSettings.h>

namespace WPEFramework {

namespace JsonData {

    namespace UserSettingsInspector {

        // Method params/result classes
        //

        class GetMigrationStateParamsData : public Core::JSON::Container {
        public:
            GetMigrationStateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("key"), &Key);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetMigrationStateParamsData(const GetMigrationStateParamsData&) = delete;
            GetMigrationStateParamsData& operator=(const GetMigrationStateParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IUserSettingsInspector::SettingsKey> Key; // one of UserSettingsKey
        }; // class GetMigrationStateParamsData

        class SettingsMigrationStateData : public Core::JSON::Container {
        public:
            SettingsMigrationStateData()
                : Core::JSON::Container()
            {
                _Init();
            }

            SettingsMigrationStateData(const SettingsMigrationStateData& _other)
                : Core::JSON::Container()
                , Key(_other.Key)
                , RequiresMigration(_other.RequiresMigration)
            {
                _Init();
            }

            SettingsMigrationStateData& operator=(const SettingsMigrationStateData& _rhs)
            {
                Key = _rhs.Key;
                RequiresMigration = _rhs.RequiresMigration;
                return (*this);
            }

            SettingsMigrationStateData(const Exchange::IUserSettingsInspector::SettingsMigrationState& _other)
                : Core::JSON::Container()
            {
                Key = _other.key;
                RequiresMigration = _other.requiresMigration;
                _Init();
            }

            SettingsMigrationStateData& operator=(const Exchange::IUserSettingsInspector::SettingsMigrationState& _rhs)
            {
                Key = _rhs.key;
                RequiresMigration = _rhs.requiresMigration;
                return (*this);
            }

            operator Exchange::IUserSettingsInspector::SettingsMigrationState() const
            {
                Exchange::IUserSettingsInspector::SettingsMigrationState _value{};
                _value.key = Key;
                _value.requiresMigration = RequiresMigration;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("key"), &Key);
                Add(_T("requiresMigration"), &RequiresMigration);
            }

        public:
            Core::JSON::EnumType<Exchange::IUserSettingsInspector::SettingsKey> Key;
            Core::JSON::Boolean RequiresMigration;
        }; // class SettingsMigrationStateData

    } // namespace UserSettingsInspector

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IUserSettingsInspector::SettingsKey)

}

