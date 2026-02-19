// Generated automatically from 'IMigration.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_Migration.h"
#include <interfaces/IMigration.h>

namespace WPEFramework {

namespace Exchange {

    namespace JMigration {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IMigration* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JMigration"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getBootTypeInfo' - query the BootType details
            _module_.Register<void, JsonData::Migration::BootTypeInfoData>(_T("getBootTypeInfo"), 
                [_impl_](JsonData::Migration::BootTypeInfoData& bootTypeInfo) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IMigration::BootTypeInfo _bootTypeInfo{};

                    _errorCode = _impl_->GetBootTypeInfo(_bootTypeInfo);

                    if (_errorCode == Core::ERROR_NONE) {
                        bootTypeInfo = _bootTypeInfo;
                    }

                    return (_errorCode);
                });

            // Method: 'setMigrationStatus' - sets the tr181 MigrationStatus parameter
            _module_.Register<JsonData::Migration::SetMigrationStatusParamsData, JsonData::Migration::MigrationResultData>(_T("setMigrationStatus"), 
                [_impl_](const JsonData::Migration::SetMigrationStatusParamsData& params,
                         JsonData::Migration::MigrationResultData& migrationResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IMigration::MigrationStatus _status{params.Status};
                    Exchange::IMigration::MigrationResult _migrationResult{};

                    _errorCode = _impl_->SetMigrationStatus(_status, _migrationResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        migrationResult = _migrationResult;
                    }

                    return (_errorCode);
                });

            // Method: 'getMigrationStatus' - get the MigrationStatus details
            _module_.Register<void, JsonData::Migration::MigrationStatusInfoData>(_T("getMigrationStatus"), 
                [_impl_](JsonData::Migration::MigrationStatusInfoData& migrationStatusInfo) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IMigration::MigrationStatusInfo _migrationStatusInfo{};

                    _errorCode = _impl_->GetMigrationStatus(_migrationStatusInfo);

                    if (_errorCode == Core::ERROR_NONE) {
                        migrationStatusInfo = _migrationStatusInfo;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getBootTypeInfo"));
            _module_.Unregister(_T("setMigrationStatus"));
            _module_.Unregister(_T("getMigrationStatus"));
        }

        POP_WARNING()

    } // namespace JMigration

} // namespace Exchange

} // namespace WPEFramework

