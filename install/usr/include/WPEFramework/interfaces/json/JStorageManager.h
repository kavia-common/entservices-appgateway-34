// Generated automatically from 'IStorageManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_StorageManager.h"
#include <interfaces/IStorageManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JStorageManager {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IStorageManager* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JStorageManager"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'clear' - Called by IUI
            _module_.Register<JsonData::StorageManager::ClearParamsData, Core::JSON::String>(_T("clear"), 
                [_impl_](const JsonData::StorageManager::ClearParamsData& params, Core::JSON::String& errorReason) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    string _errorReason{};

                    _errorCode = _impl_->Clear(_appId, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        errorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'clearAll' - Called by IUI
            _module_.Register<JsonData::StorageManager::ClearAllParamsData, Core::JSON::String>(_T("clearAll"), 
                [_impl_](const JsonData::StorageManager::ClearAllParamsData& params, Core::JSON::String& errorReason) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _exemptionAppIds{params.ExemptionAppIds};
                    string _errorReason{};

                    _errorCode = _impl_->ClearAll(_exemptionAppIds, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        errorReason = _errorReason;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("clear"));
            _module_.Unregister(_T("clearAll"));
        }

        POP_WARNING()

    } // namespace JStorageManager

} // namespace Exchange

} // namespace WPEFramework

