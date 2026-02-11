// C++ classes for Migration API JSON-RPC API.
// Generated automatically from 'IMigration.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IMigration.h>

namespace WPEFramework {

namespace JsonData {

    namespace Migration {

        // Method params/result classes
        //

        class BootTypeInfoData : public Core::JSON::Container {
        public:
            BootTypeInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            BootTypeInfoData(const Exchange::IMigration::BootTypeInfo& _other)
                : Core::JSON::Container()
            {
                BootType = _other.bootType;
                _Init();
            }

            BootTypeInfoData& operator=(const Exchange::IMigration::BootTypeInfo& _rhs)
            {
                BootType = _rhs.bootType;
                return (*this);
            }

            operator Exchange::IMigration::BootTypeInfo() const
            {
                Exchange::IMigration::BootTypeInfo _value{};
                _value.bootType = BootType;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("bootType"), &BootType);
            }

        public:
            Core::JSON::EnumType<Exchange::IMigration::BootType> BootType; // query the BootType details
        }; // class BootTypeInfoData

        class MigrationStatusInfoData : public Core::JSON::Container {
        public:
            MigrationStatusInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            MigrationStatusInfoData(const Exchange::IMigration::MigrationStatusInfo& _other)
                : Core::JSON::Container()
            {
                MigrationStatus = _other.migrationStatus;
                _Init();
            }

            MigrationStatusInfoData& operator=(const Exchange::IMigration::MigrationStatusInfo& _rhs)
            {
                MigrationStatus = _rhs.migrationStatus;
                return (*this);
            }

            operator Exchange::IMigration::MigrationStatusInfo() const
            {
                Exchange::IMigration::MigrationStatusInfo _value{};
                _value.migrationStatus = MigrationStatus;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("migrationStatus"), &MigrationStatus);
            }

        public:
            Core::JSON::EnumType<Exchange::IMigration::MigrationStatus> MigrationStatus; // get the MigrationStatus details
        }; // class MigrationStatusInfoData

        class MigrationResultData : public Core::JSON::Container {
        public:
            MigrationResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            MigrationResultData(const Exchange::IMigration::MigrationResult& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            MigrationResultData& operator=(const Exchange::IMigration::MigrationResult& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IMigration::MigrationResult() const
            {
                Exchange::IMigration::MigrationResult _value{};
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
            Core::JSON::Boolean Success; // sets the tr181 MigrationStatus parameter
        }; // class MigrationResultData

        class SetMigrationStatusParamsData : public Core::JSON::Container {
        public:
            SetMigrationStatusParamsData()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetMigrationStatusParamsData(const SetMigrationStatusParamsData&) = delete;
            SetMigrationStatusParamsData& operator=(const SetMigrationStatusParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IMigration::MigrationStatus> Status; // - in - enum
        }; // class SetMigrationStatusParamsData

    } // namespace Migration

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IMigration::BootType)
ENUM_CONVERSION_HANDLER(Exchange::IMigration::MigrationStatus)

}

