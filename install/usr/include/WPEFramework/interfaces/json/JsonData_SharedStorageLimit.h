// C++ classes for SharedStorageLimit API JSON-RPC API.
// Generated automatically from 'ISharedStorage.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ISharedStorage.h>

namespace WPEFramework {

namespace JsonData {

    namespace SharedStorageLimit {

        // Method params/result classes
        //

        class GetNamespaceStorageLimitParamsData : public Core::JSON::Container {
        public:
            GetNamespaceStorageLimitParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("namespace"), &Ns);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetNamespaceStorageLimitParamsData(const GetNamespaceStorageLimitParamsData&) = delete;
            GetNamespaceStorageLimitParamsData& operator=(const GetNamespaceStorageLimitParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISharedStorageLimit::ScopeType> Scope; // must be device or account
            Core::JSON::String Ns; // name space
        }; // class GetNamespaceStorageLimitParamsData

        class StorageLimitData : public Core::JSON::Container {
        public:
            StorageLimitData()
                : Core::JSON::Container()
            {
                _Init();
            }

            StorageLimitData(const Exchange::ISharedStorageLimit::StorageLimit& _other)
                : Core::JSON::Container()
            {
                StorageLimit = _other.storageLimit;
                _Init();
            }

            StorageLimitData& operator=(const Exchange::ISharedStorageLimit::StorageLimit& _rhs)
            {
                StorageLimit = _rhs.storageLimit;
                return (*this);
            }

            operator Exchange::ISharedStorageLimit::StorageLimit() const
            {
                Exchange::ISharedStorageLimit::StorageLimit _value{};
                _value.storageLimit = StorageLimit;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("storageLimit"), &StorageLimit);
            }

        public:
            Core::JSON::DecUInt32 StorageLimit; // Returns the storage limit for a given namespace
        }; // class StorageLimitData

        class SetNamespaceStorageLimitParamsData : public Core::JSON::Container {
        public:
            SetNamespaceStorageLimitParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("namespace"), &Ns);
                Add(_T("storageLimit"), &StorageLimit);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetNamespaceStorageLimitParamsData(const SetNamespaceStorageLimitParamsData&) = delete;
            SetNamespaceStorageLimitParamsData& operator=(const SetNamespaceStorageLimitParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISharedStorageLimit::ScopeType> Scope; // must be device or account
            Core::JSON::String Ns; // name space
            Core::JSON::DecUInt32 StorageLimit; // size
        }; // class SetNamespaceStorageLimitParamsData

    } // namespace SharedStorageLimit

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ISharedStorage::ScopeType)

}

