// Generated automatically from 'IUserSettings.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_UserSettingsInspector.h"
#include <interfaces/IUserSettings.h>

namespace WPEFramework {

namespace Exchange {

    namespace JUserSettingsInspector {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IUserSettingsInspector* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JUserSettingsInspector"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getMigrationState' - Get the migration state of the respective key
            _module_.Register<JsonData::UserSettingsInspector::GetMigrationStateParamsData, Core::JSON::Boolean>(_T("getMigrationState"), 
                [_impl_](const JsonData::UserSettingsInspector::GetMigrationStateParamsData& params, Core::JSON::Boolean& requiresMigration) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IUserSettingsInspector::SettingsKey _key{params.Key};
                    bool _requiresMigration{};

                    _errorCode = _impl_->GetMigrationState(_key, _requiresMigration);

                    if (_errorCode == Core::ERROR_NONE) {
                        requiresMigration = _requiresMigration;
                    }

                    return (_errorCode);
                });

            // Method: 'getMigrationStates' - Get the migration state of all the defined keys
            _module_.Register<void, Core::JSON::ArrayType<JsonData::UserSettingsInspector::SettingsMigrationStateData>>(_T("getMigrationStates"), 
                [_impl_](Core::JSON::ArrayType<JsonData::UserSettingsInspector::SettingsMigrationStateData>& states) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<IUserSettingsInspector::SettingsMigrationState, ID_USER_SETTINGS_MIGRATION_STATE_ITERATOR>* _states{};

                    _errorCode = _impl_->GetMigrationStates(_states);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_states != nullptr) {
                            Exchange::IUserSettingsInspector::SettingsMigrationState _resultItem_{};
                            while (_states->Next(_resultItem_) == true) { states.Add() = _resultItem_; }
                            _states->Release();
                        }
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getMigrationState"));
            _module_.Unregister(_T("getMigrationStates"));
        }

        POP_WARNING()

    } // namespace JUserSettingsInspector

} // namespace Exchange

} // namespace WPEFramework

