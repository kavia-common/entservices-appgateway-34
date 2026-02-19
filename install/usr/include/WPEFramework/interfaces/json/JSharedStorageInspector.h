// Generated automatically from 'ISharedStorage.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_SharedStorageInspector.h"
#include <interfaces/ISharedStorage.h>

namespace WPEFramework {

namespace Exchange {

    namespace JSharedStorageInspector {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ISharedStorageInspector* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JSharedStorageInspector"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getKeys' - Returns the keys that are stored in the specified namespace
            _module_.Register<JsonData::SharedStorageInspector::GetKeysParamsData, JsonData::SharedStorageInspector::GetKeysResultData>(_T("getKeys"), 
                [_impl_](const JsonData::SharedStorageInspector::GetKeysParamsData& params,
                         JsonData::SharedStorageInspector::GetKeysResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorageInspector::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _keys{};
                    bool _success{};

                    _errorCode = _impl_->GetKeys(_scope, _ns, _keys, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_keys != nullptr) {
                            string _keysItem_{};
                            while (_keys->Next(_keysItem_) == true) { result.Keys.Add() = _keysItem_; }
                            _keys->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getNamespaces' - Returns the namespaces
            _module_.Register<JsonData::SharedStorageInspector::GetNamespacesParamsInfo,
                     JsonData::SharedStorageInspector::GetNamespacesResultData>(_T("getNamespaces"), 
                [_impl_](const JsonData::SharedStorageInspector::GetNamespacesParamsInfo& params,
                         JsonData::SharedStorageInspector::GetNamespacesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorageInspector::ScopeType _scope{params.Scope};
                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _namespaces{};
                    bool _success{};

                    _errorCode = _impl_->GetNamespaces(_scope, _namespaces, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_namespaces != nullptr) {
                            string _namespacesItem_{};
                            while (_namespaces->Next(_namespacesItem_) == true) { result.Namespaces.Add() = _namespacesItem_; }
                            _namespaces->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getStorageSizes' - Returns the size occupied by each namespace
            _module_.Register<JsonData::SharedStorageInspector::GetNamespacesParamsInfo,
                     JsonData::SharedStorageInspector::GetStorageSizesResultData>(_T("getStorageSizes"), 
                [_impl_](const JsonData::SharedStorageInspector::GetNamespacesParamsInfo& params,
                         JsonData::SharedStorageInspector::GetStorageSizesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorageInspector::ScopeType _scope{params.Scope};
                    ::WPEFramework::RPC::IIteratorType<ISharedStorageInspector::NamespaceSize,
                             ID_SHARED_STORAGE_INSPECTOR_NAMESPACE_SIZE_ITERATOR>* _storageList{};
                    bool _success{};

                    _errorCode = _impl_->GetStorageSizes(_scope, _storageList, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_storageList != nullptr) {
                            Exchange::ISharedStorageInspector::NamespaceSize _storageListItem_{};
                            while (_storageList->Next(_storageListItem_) == true) { result.StorageList.Add() = _storageListItem_; }
                            _storageList->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getKeys"));
            _module_.Unregister(_T("getNamespaces"));
            _module_.Unregister(_T("getStorageSizes"));
        }

        POP_WARNING()

    } // namespace JSharedStorageInspector

} // namespace Exchange

} // namespace WPEFramework

