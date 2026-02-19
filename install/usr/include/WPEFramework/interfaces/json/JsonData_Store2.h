// C++ classes for Store2 API JSON-RPC API.
// Generated automatically from 'IStore2.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IStore2.h>

namespace WPEFramework {

namespace JsonData {

    namespace Store2 {

        // Common classes
        //

        class DeleteNamespaceParamsInfo : public Core::JSON::Container {
        public:
            DeleteNamespaceParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("scope"), &Scope);
                Add(_T("namespace"), &Ns);
            }

            bool IsValid() const
            {
                return (true);
            }

            DeleteNamespaceParamsInfo(const DeleteNamespaceParamsInfo&) = delete;
            DeleteNamespaceParamsInfo& operator=(const DeleteNamespaceParamsInfo&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IStore2::ScopeType> Scope;
            Core::JSON::String Ns;
        }; // class DeleteNamespaceParamsInfo

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
            Core::JSON::EnumType<Exchange::IStore2::ScopeType> Scope;
            Core::JSON::String Ns;
            Core::JSON::String Key;
        }; // class GetValueParamsInfo

        class GetValueResultInfo : public Core::JSON::Container {
        public:
            GetValueResultInfo()
                : Core::JSON::Container()
            {
                Add(_T("value"), &Value);
                Add(_T("ttl"), &Ttl);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetValueResultInfo(const GetValueResultInfo&) = delete;
            GetValueResultInfo& operator=(const GetValueResultInfo&) = delete;

        public:
            Core::JSON::String Value;
            Core::JSON::DecUInt32 Ttl;
        }; // class GetValueResultInfo

        class SetValueParamsInfo : public Core::JSON::Container {
        public:
            SetValueParamsInfo()
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

            SetValueParamsInfo(const SetValueParamsInfo&) = delete;
            SetValueParamsInfo& operator=(const SetValueParamsInfo&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IStore2::ScopeType> Scope;
            Core::JSON::String Ns;
            Core::JSON::String Key;
            Core::JSON::String Value;
            Core::JSON::DecUInt32 Ttl;
        }; // class SetValueParamsInfo

        // Method params/result classes
        //

        class ValueChangedParamsData : public Core::JSON::Container {
        public:
            ValueChangedParamsData()
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

            ValueChangedParamsData(const ValueChangedParamsData&) = delete;
            ValueChangedParamsData& operator=(const ValueChangedParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IStore2::ScopeType> Scope;
            Core::JSON::String Ns;
            Core::JSON::String Key;
            Core::JSON::String Value;
        }; // class ValueChangedParamsData

    } // namespace Store2

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IStore2::ScopeType)

}

