// Generated automatically from 'IStore2.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_Store2.h"
#include <interfaces/IStore2.h>

namespace WPEFramework {

namespace Exchange {

    namespace JStore2 {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IStore2* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JStore2"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setvalue'
            _module_.Register<JsonData::Store2::SetValueParamsInfo, void>(_T("setvalue"), 
                [_impl_](const JsonData::Store2::SetValueParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IStore2::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};
                    const string _value{params.Value};
                    const uint32_t _ttl{params.Ttl};

                    _errorCode = _impl_->SetValue(_scope, _ns, _key, _value, _ttl);

                    return (_errorCode);
                });

            // Method: 'setValue'
            _module_.Register<JsonData::Store2::SetValueParamsInfo, void>(_T("setValue"), 
                [_impl_](const JsonData::Store2::SetValueParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IStore2::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};
                    const string _value{params.Value};
                    const uint32_t _ttl{params.Ttl};

                    _errorCode = _impl_->SetValue(_scope, _ns, _key, _value, _ttl);

                    return (_errorCode);
                });

            // Method: 'getvalue'
            _module_.Register<JsonData::Store2::GetValueParamsInfo, JsonData::Store2::GetValueResultInfo>(_T("getvalue"), 
                [_impl_](const JsonData::Store2::GetValueParamsInfo& params, JsonData::Store2::GetValueResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IStore2::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};
                    string _value{};
                    uint32_t _ttl{};

                    _errorCode = _impl_->GetValue(_scope, _ns, _key, _value, _ttl);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Value = _value;
                        result.Ttl = _ttl;
                    }

                    return (_errorCode);
                });

            // Method: 'getValue'
            _module_.Register<JsonData::Store2::GetValueParamsInfo, JsonData::Store2::GetValueResultInfo>(_T("getValue"), 
                [_impl_](const JsonData::Store2::GetValueParamsInfo& params, JsonData::Store2::GetValueResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IStore2::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};
                    string _value{};
                    uint32_t _ttl{};

                    _errorCode = _impl_->GetValue(_scope, _ns, _key, _value, _ttl);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Value = _value;
                        result.Ttl = _ttl;
                    }

                    return (_errorCode);
                });

            // Method: 'deletekey'
            _module_.Register<JsonData::Store2::GetValueParamsInfo, void>(_T("deletekey"), 
                [_impl_](const JsonData::Store2::GetValueParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IStore2::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};

                    _errorCode = _impl_->DeleteKey(_scope, _ns, _key);

                    return (_errorCode);
                });

            // Method: 'deleteKey'
            _module_.Register<JsonData::Store2::GetValueParamsInfo, void>(_T("deleteKey"), 
                [_impl_](const JsonData::Store2::GetValueParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IStore2::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};

                    _errorCode = _impl_->DeleteKey(_scope, _ns, _key);

                    return (_errorCode);
                });

            // Method: 'deletenamespace'
            _module_.Register<JsonData::Store2::DeleteNamespaceParamsInfo, void>(_T("deletenamespace"), 
                [_impl_](const JsonData::Store2::DeleteNamespaceParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IStore2::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};

                    _errorCode = _impl_->DeleteNamespace(_scope, _ns);

                    return (_errorCode);
                });

            // Method: 'deleteNamespace'
            _module_.Register<JsonData::Store2::DeleteNamespaceParamsInfo, void>(_T("deleteNamespace"), 
                [_impl_](const JsonData::Store2::DeleteNamespaceParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IStore2::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};

                    _errorCode = _impl_->DeleteNamespace(_scope, _ns);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setvalue"));
            _module_.Unregister(_T("setValue"));
            _module_.Unregister(_T("getvalue"));
            _module_.Unregister(_T("getValue"));
            _module_.Unregister(_T("deletekey"));
            _module_.Unregister(_T("deleteKey"));
            _module_.Unregister(_T("deletenamespace"));
            _module_.Unregister(_T("deleteNamespace"));
        }

        namespace Event {

            // Event: 'valuechanged'
            static void ValueChanged(const JSONRPC& _module_, const JsonData::Store2::ValueChangedParamsData& params)
            {
                _module_.Notify(_T("valuechanged"), params);
                _module_.Notify(_T("onValueChanged"), params);
            }

            // Event: 'valuechanged'
            static void ValueChanged(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::IStore2::ScopeType>& scope, const Core::JSON::String& ns,
                     const Core::JSON::String& key, const Core::JSON::String& value)
            {
                JsonData::Store2::ValueChangedParamsData _params_;
                _params_.Scope = scope;
                _params_.Ns = ns;
                _params_.Key = key;
                _params_.Value = value;

                ValueChanged(_module_, _params_);
            }

            // Event: 'valuechanged'
            static void ValueChanged(const JSONRPC& _module_, const Exchange::IStore2::ScopeType& scope, const string& ns, const string& key,
                     const string& value)
            {
                JsonData::Store2::ValueChangedParamsData _params_;
                _params_.Scope = scope;
                _params_.Ns = ns;
                _params_.Key = key;
                _params_.Value = value;

                ValueChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JStore2

} // namespace Exchange

} // namespace WPEFramework

