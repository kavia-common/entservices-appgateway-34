// C++ classes for SharedStorageInspector API JSON-RPC API.
// Generated automatically from 'ISharedStorage.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ISharedStorage.h>

namespace WPEFramework {

namespace JsonData {

    namespace SharedStorageInspector {

        // Common classes
        //

        class GetNamespacesParamsInfo : public Core::JSON::Container {
        public:
            GetNamespacesParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetNamespacesParamsInfo(const GetNamespacesParamsInfo&) = delete;
            GetNamespacesParamsInfo& operator=(const GetNamespacesParamsInfo&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISharedStorageInspector::ScopeType> Scope; // must be device or account
        }; // class GetNamespacesParamsInfo

        // Method params/result classes
        //

        class GetKeysParamsData : public Core::JSON::Container {
        public:
            GetKeysParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("namespace"), &Ns);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetKeysParamsData(const GetKeysParamsData&) = delete;
            GetKeysParamsData& operator=(const GetKeysParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISharedStorageInspector::ScopeType> Scope; // must be device or account
            Core::JSON::String Ns; // name space
        }; // class GetKeysParamsData

        class GetKeysResultData : public Core::JSON::Container {
        public:
            GetKeysResultData()
                : Core::JSON::Container()
            {
                Add(_T("keys"), &Keys);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetKeysResultData(const GetKeysResultData&) = delete;
            GetKeysResultData& operator=(const GetKeysResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> Keys; // keys list
            Core::JSON::Boolean Success; // success
        }; // class GetKeysResultData

        class GetNamespacesResultData : public Core::JSON::Container {
        public:
            GetNamespacesResultData()
                : Core::JSON::Container()
            {
                Add(_T("namespaces"), &Namespaces);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetNamespacesResultData(const GetNamespacesResultData&) = delete;
            GetNamespacesResultData& operator=(const GetNamespacesResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> Namespaces; // namespaces list
            Core::JSON::Boolean Success; // success
        }; // class GetNamespacesResultData

        class GetStorageSizesResultData : public Core::JSON::Container {
        public:
            class NamespaceSizeData : public Core::JSON::Container {
            public:
                NamespaceSizeData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                NamespaceSizeData(const NamespaceSizeData& _other)
                    : Core::JSON::Container()
                    , Ns(_other.Ns)
                    , Size(_other.Size)
                {
                    _Init();
                }

                NamespaceSizeData& operator=(const NamespaceSizeData& _rhs)
                {
                    Ns = _rhs.Ns;
                    Size = _rhs.Size;
                    return (*this);
                }

                NamespaceSizeData(const Exchange::ISharedStorageInspector::NamespaceSize& _other)
                    : Core::JSON::Container()
                {
                    Ns = _other.ns;
                    Size = _other.size;
                    _Init();
                }

                NamespaceSizeData& operator=(const Exchange::ISharedStorageInspector::NamespaceSize& _rhs)
                {
                    Ns = _rhs.ns;
                    Size = _rhs.size;
                    return (*this);
                }

                operator Exchange::ISharedStorageInspector::NamespaceSize() const
                {
                    Exchange::ISharedStorageInspector::NamespaceSize _value{};
                    _value.ns = Ns;
                    _value.size = Size;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("namespace"), &Ns);
                    Add(_T("size"), &Size);
                }

            public:
                Core::JSON::String Ns;
                Core::JSON::DecUInt32 Size;
            }; // class NamespaceSizeData

            GetStorageSizesResultData()
                : Core::JSON::Container()
            {
                Add(_T("storageList"), &StorageList);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetStorageSizesResultData(const GetStorageSizesResultData&) = delete;
            GetStorageSizesResultData& operator=(const GetStorageSizesResultData&) = delete;

        public:
            Core::JSON::ArrayType<GetStorageSizesResultData::NamespaceSizeData> StorageList; // list of namespaces and their sizes
            Core::JSON::Boolean Success; // success
        }; // class GetStorageSizesResultData

    } // namespace SharedStorageInspector

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ISharedStorage::ScopeType)

}

