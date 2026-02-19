// Generated automatically from 'ISharedStorage.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_SharedStorage.h"
#include <interfaces/ISharedStorage.h>

namespace WPEFramework {

namespace Exchange {

    namespace JSharedStorage {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ISharedStorage* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JSharedStorage"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setValue' - Sets the value of a key in the the specified namespace
            _module_.Register<JsonData::SharedStorage::SetValueParamsData, JsonData::SharedStorage::SuccessInfo>(_T("setValue"), 
                [_impl_](const JsonData::SharedStorage::SetValueParamsData& params, JsonData::SharedStorage::SuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorage::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};
                    const string _value{params.Value};
                    const uint32_t _ttl{params.Ttl};
                    Exchange::ISharedStorage::Success _success{};

                    _errorCode = _impl_->SetValue(_scope, _ns, _key, _value, _ttl, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getValue' - Returns the value of a key from the specified namespace
            _module_.Register<JsonData::SharedStorage::GetValueParamsInfo, JsonData::SharedStorage::GetValueResultData>(_T("getValue"), 
                [_impl_](const JsonData::SharedStorage::GetValueParamsInfo& params, JsonData::SharedStorage::GetValueResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorage::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};
                    string _value{};
                    uint32_t _ttl{};
                    bool _success{};

                    _errorCode = _impl_->GetValue(_scope, _ns, _key, _value, _ttl, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Value = _value;
                        result.Ttl = _ttl;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'deleteKey' - Deletes a key from the specified namespace
            _module_.Register<JsonData::SharedStorage::GetValueParamsInfo, JsonData::SharedStorage::SuccessInfo>(_T("deleteKey"), 
                [_impl_](const JsonData::SharedStorage::GetValueParamsInfo& params, JsonData::SharedStorage::SuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorage::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    const string _key{params.Key};
                    Exchange::ISharedStorage::Success _success{};

                    _errorCode = _impl_->DeleteKey(_scope, _ns, _key, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'deleteNamespace' - Deletes the specified namespace
            _module_.Register<JsonData::SharedStorage::DeleteNamespaceParamsData, JsonData::SharedStorage::SuccessInfo>(_T("deleteNamespace"), 
                [_impl_](const JsonData::SharedStorage::DeleteNamespaceParamsData& params, JsonData::SharedStorage::SuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ISharedStorage::ScopeType _scope{params.Scope};
                    const string _ns{params.Ns};
                    Exchange::ISharedStorage::Success _success{};

                    _errorCode = _impl_->DeleteNamespace(_scope, _ns, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setValue"));
            _module_.Unregister(_T("getValue"));
            _module_.Unregister(_T("deleteKey"));
            _module_.Unregister(_T("deleteNamespace"));
        }

        namespace Event {

            // Event: 'onValueChanged' - Values stored are changed using setValue
            static void OnValueChanged(const JSONRPC& _module_, const JsonData::SharedStorage::OnValueChangedParamsData& params)
            {
                _module_.Notify(_T("onValueChanged"), params);
            }

            // Event: 'onValueChanged' - Values stored are changed using setValue
            static void OnValueChanged(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::ISharedStorage::ScopeType>& scope,
                     const Core::JSON::String& ns, const Core::JSON::String& key, const Core::JSON::String& value)
            {
                JsonData::SharedStorage::OnValueChangedParamsData _params_;
                _params_.Scope = scope;
                _params_.Ns = ns;
                _params_.Key = key;
                _params_.Value = value;

                OnValueChanged(_module_, _params_);
            }

            // Event: 'onValueChanged' - Values stored are changed using setValue
            static void OnValueChanged(const JSONRPC& _module_, const Exchange::ISharedStorage::ScopeType& scope, const string& ns, const string& key,
                     const string& value)
            {
                JsonData::SharedStorage::OnValueChangedParamsData _params_;
                _params_.Scope = scope;
                _params_.Ns = ns;
                _params_.Key = key;
                _params_.Value = value;

                OnValueChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JSharedStorage

} // namespace Exchange

} // namespace WPEFramework

