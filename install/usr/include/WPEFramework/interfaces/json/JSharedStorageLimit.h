// Generated automatically from 'ISharedStorage.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_SharedStorageLimit.h"
#include <interfaces/ISharedStorage.h>

namespace WPEFramework {

namespace Exchange {

    namespace JSharedStorageLimit {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ISharedStorageLimit* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JSharedStorageLimit"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setNamespaceStorageLimit' - Sets the storage limit for a given namespace
            _module_.Register<JsonData::SharedStorageLimit::SetNamespaceStorageLimitParamsData, Core::JSON::Boolean>(_T("setNamespaceStorageLimit"), 
                [_impl_](const JsonData::SharedStorageLimit::SetNamespaceStorageLimitParamsData& params, Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorageLimit::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const uint32_t _storageLimit{params.StorageLimit};
                    bool _success{};

                    _errorCode = _impl_->SetNamespaceStorageLimit(_scope, _ns, _storageLimit, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getNamespaceStorageLimit' - Returns the storage limit for a given namespace
            _module_.Register<JsonData::SharedStorageLimit::GetNamespaceStorageLimitParamsData,
                     JsonData::SharedStorageLimit::StorageLimitData>(_T("getNamespaceStorageLimit"), 
                [_impl_](const JsonData::SharedStorageLimit::GetNamespaceStorageLimitParamsData& params,
                         JsonData::SharedStorageLimit::StorageLimitData& storageLimit) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorageLimit::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    Exchange::ISharedStorageLimit::StorageLimit _storageLimit{};

                    _errorCode = _impl_->GetNamespaceStorageLimit(_scope, _ns, _storageLimit);

                    if (_errorCode == Core::ERROR_NONE) {
                        storageLimit = _storageLimit;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setNamespaceStorageLimit"));
            _module_.Unregister(_T("getNamespaceStorageLimit"));
        }

        POP_WARNING()

    } // namespace JSharedStorageLimit

} // namespace Exchange

} // namespace WPEFramework

