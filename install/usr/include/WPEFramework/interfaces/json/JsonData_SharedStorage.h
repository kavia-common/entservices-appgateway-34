// C++ classes for SharedStorage API JSON-RPC API.
// Generated automatically from 'ISharedStorage.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ISharedStorage.h>

namespace WPEFramework {

namespace JsonData {

    namespace SharedStorage {

        // Common classes
        //

        class GetValueParamsInfo : public Core::JSON::Container {
        public:
            GetValueParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("namespace"), &Ns);
                Add(_T("key"), &Key);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetValueParamsInfo(const GetValueParamsInfo&) = delete;
            GetValueParamsInfo& operator=(const GetValueParamsInfo&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISharedStorage::ScopeType> Scope; // must be device or account
            Core::JSON::String Ns; // name space
            Core::JSON::String Key; // key
        }; // class GetValueParamsInfo

        class SuccessInfo : public Core::JSON::Container {
        public:
            SuccessInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            SuccessInfo(const Exchange::ISharedStorage::Success& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            SuccessInfo& operator=(const Exchange::ISharedStorage::Success& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::ISharedStorage::Success() const
            {
                Exchange::ISharedStorage::Success _value{};
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
            Core::JSON::Boolean Success; // Sets the value of a key in the the specified namespace
        }; // class SuccessInfo

        // Method params/result classes
        //

        class DeleteNamespaceParamsData : public Core::JSON::Container {
        public:
            DeleteNamespaceParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("namespace"), &Ns);
            }

            bool IsValid() const
            {
                return (true);
            }

            DeleteNamespaceParamsData(const DeleteNamespaceParamsData&) = delete;
            DeleteNamespaceParamsData& operator=(const DeleteNamespaceParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISharedStorage::ScopeType> Scope; // must be device or account
            Core::JSON::String Ns; // name space
        }; // class DeleteNamespaceParamsData

        class GetValueResultData : public Core::JSON::Container {
        public:
            GetValueResultData()
                : Core::JSON::Container()
            {
                Add(_T("value"), &Value);
                Add(_T("ttl"), &Ttl);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetValueResultData(const GetValueResultData&) = delete;
            GetValueResultData& operator=(const GetValueResultData&) = delete;

        public:
            Core::JSON::String Value; // value out
            Core::JSON::DecUInt32 Ttl; // time to live (optional)
            Core::JSON::Boolean Success; // success
        }; // class GetValueResultData

        class OnValueChangedParamsData : public Core::JSON::Container {
        public:
            OnValueChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("namespace"), &Ns);
                Add(_T("key"), &Key);
                Add(_T("value"), &Value);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnValueChangedParamsData(const OnValueChangedParamsData&) = delete;
            OnValueChangedParamsData& operator=(const OnValueChangedParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISharedStorage::ScopeType> Scope; // must be device or account
            Core::JSON::String Ns; // Values stored are changed using setValue
            Core::JSON::String Key; // key
            Core::JSON::String Value; // value
        }; // class OnValueChangedParamsData

        class SetValueParamsData : public Core::JSON::Container {
        public:
            SetValueParamsData()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("namespace"), &Ns);
                Add(_T("key"), &Key);
                Add(_T("value"), &Value);
                Add(_T("ttl"), &Ttl);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetValueParamsData(const SetValueParamsData&) = delete;
            SetValueParamsData& operator=(const SetValueParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISharedStorage::ScopeType> Scope; // must be device or account
            Core::JSON::String Ns; // name space
            Core::JSON::String Key; // key
            Core::JSON::String Value; // value
            Core::JSON::DecUInt32 Ttl; // time to live (optional)
        }; // class SetValueParamsData

    } // namespace SharedStorage

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ISharedStorage::ScopeType)

}

