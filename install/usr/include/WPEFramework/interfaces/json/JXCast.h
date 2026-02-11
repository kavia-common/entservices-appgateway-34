// Generated automatically from 'IXCast.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_XCast.h"
#include <interfaces/IXCast.h>

namespace WPEFramework {

namespace Exchange {

    namespace JXCast {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IXCast* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JXCast"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setApplicationState' - Triggered when the cast service receives an application state change notification from a client
            _module_.Register<JsonData::XCast::SetApplicationStateParamsData, JsonData::XCast::XCastSuccessInfo>(_T("setApplicationState"), 
                [_impl_](const JsonData::XCast::SetApplicationStateParamsData& params, JsonData::XCast::XCastSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _applicationName{params.ApplicationName};
                    const Exchange::IXCast::State _state{params.State};
                    const string _applicationId{params.ApplicationId};
                    const Exchange::IXCast::ErrorCode _error{params.Error};
                    Exchange::IXCast::XCastSuccess _success{};

                    _errorCode = _impl_->SetApplicationState(_applicationName, _state, _applicationId, _error, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getProtocolVersion' - Returns the DIAL protocol version supported by the server
            _module_.Register<void, JsonData::XCast::GetProtocolVersionResultData>(_T("getProtocolVersion"), 
                [_impl_](JsonData::XCast::GetProtocolVersionResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _protocolVersion{};
                    bool _success{};

                    _errorCode = _impl_->GetProtocolVersion(_protocolVersion, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.ProtocolVersion = _protocolVersion;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setManufacturerName' - Sets the manufacturer name of the device
            _module_.Register<JsonData::XCast::SetManufacturerNameParamsData, JsonData::XCast::XCastSuccessInfo>(_T("setManufacturerName"), 
                [_impl_](const JsonData::XCast::SetManufacturerNameParamsData& params, JsonData::XCast::XCastSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _manufacturername{params.Manufacturername};
                    Exchange::IXCast::XCastSuccess _success{};

                    _errorCode = _impl_->SetManufacturerName(_manufacturername, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getManufacturerName' - Returns the manufacturer name set by setManufacturerName API
            _module_.Register<void, JsonData::XCast::GetManufacturerNameResultData>(_T("getManufacturerName"), 
                [_impl_](JsonData::XCast::GetManufacturerNameResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _manufacturername{};
                    bool _success{};

                    _errorCode = _impl_->GetManufacturerName(_manufacturername, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Manufacturername = _manufacturername;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setModelName' - Sets the model name of the device
            _module_.Register<JsonData::XCast::SetModelNameParamsData, JsonData::XCast::XCastSuccessInfo>(_T("setModelName"), 
                [_impl_](const JsonData::XCast::SetModelNameParamsData& params, JsonData::XCast::XCastSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _modelname{params.Modelname};
                    Exchange::IXCast::XCastSuccess _success{};

                    _errorCode = _impl_->SetModelName(_modelname, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getModelName' - Returns the model name set by setModelName API
            _module_.Register<void, JsonData::XCast::GetModelNameResultData>(_T("getModelName"), 
                [_impl_](JsonData::XCast::GetModelNameResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _modelname{};
                    bool _success{};

                    _errorCode = _impl_->GetModelName(_modelname, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Modelname = _modelname;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setEnabled' - Enable or disable XCAST service
            _module_.Register<JsonData::XCast::SetEnabledParamsData, JsonData::XCast::XCastSuccessInfo>(_T("setEnabled"), 
                [_impl_](const JsonData::XCast::SetEnabledParamsData& params, JsonData::XCast::XCastSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};
                    Exchange::IXCast::XCastSuccess _success{};

                    _errorCode = _impl_->SetEnabled(_enabled, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getEnabled' - Reports whether xcast plugin is enabled or disabled
            _module_.Register<void, JsonData::XCast::GetEnabledResultData>(_T("getEnabled"), 
                [_impl_](JsonData::XCast::GetEnabledResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _enabled{};
                    bool _success{};

                    _errorCode = _impl_->GetEnabled(_enabled, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Enabled = _enabled;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setStandbyBehavior' - Sets the expected xcast behavior in standby mode
            _module_.Register<JsonData::XCast::SetStandbyBehaviorParamsData, JsonData::XCast::XCastSuccessInfo>(_T("setStandbyBehavior"), 
                [_impl_](const JsonData::XCast::SetStandbyBehaviorParamsData& params, JsonData::XCast::XCastSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IXCast::StandbyBehavior _standbybehavior{params.Standbybehavior};
                    Exchange::IXCast::XCastSuccess _success{};

                    _errorCode = _impl_->SetStandbyBehavior(_standbybehavior, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getStandbyBehavior' - Return current standby behavior option string set uisng setStandbyBehavior or default value
            _module_.Register<void, JsonData::XCast::GetStandbyBehaviorResultData>(_T("getStandbyBehavior"), 
                [_impl_](JsonData::XCast::GetStandbyBehaviorResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IXCast::StandbyBehavior _standbybehavior{};
                    bool _success{};

                    _errorCode = _impl_->GetStandbyBehavior(_standbybehavior, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Standbybehavior = _standbybehavior;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setFriendlyName' - Sets the friendly name of the device
            _module_.Register<JsonData::XCast::SetFriendlyNameParamsData, JsonData::XCast::XCastSuccessInfo>(_T("setFriendlyName"), 
                [_impl_](const JsonData::XCast::SetFriendlyNameParamsData& params, JsonData::XCast::XCastSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _friendlyname{params.Friendlyname};
                    Exchange::IXCast::XCastSuccess _success{};

                    _errorCode = _impl_->SetFriendlyName(_friendlyname, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getFriendlyName' - Returns the friendly name set by setFriendlyName API
            _module_.Register<void, JsonData::XCast::GetFriendlyNameResultData>(_T("getFriendlyName"), 
                [_impl_](JsonData::XCast::GetFriendlyNameResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _friendlyname{};
                    bool _success{};

                    _errorCode = _impl_->GetFriendlyName(_friendlyname, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Friendlyname = _friendlyname;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'registerApplications' - Registers an application
            _module_.Register<JsonData::XCast::RegisterApplicationsParamsData, JsonData::XCast::XCastSuccessInfo>(_T("registerApplications"), 
                [_impl_](const JsonData::XCast::RegisterApplicationsParamsData& params, JsonData::XCast::XCastSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    std::list<Exchange::IXCast::ApplicationInfo> _elements;
                    auto _Iterator = params.AppInfoList.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<IXCast::ApplicationInfo,
                             ID_XCAST_APPLICATION_INFO_ITERATOR>* const _appInfoList{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<IXCast::ApplicationInfo,
                             ID_XCAST_APPLICATION_INFO_ITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<IXCast::ApplicationInfo, ID_XCAST_APPLICATION_INFO_ITERATOR>>(_elements)};
                    Exchange::IXCast::XCastSuccess _success{};

                    ASSERT(_appInfoList != nullptr); 

                    if ((_appInfoList != nullptr)) {
                        _errorCode = _impl_->RegisterApplications(_appInfoList, _success);
                        _appInfoList->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'unregisterApplications' - Unregisters an application
            _module_.Register<JsonData::XCast::UnregisterApplicationsParamsData, JsonData::XCast::XCastSuccessInfo>(_T("unregisterApplications"), 
                [_impl_](const JsonData::XCast::UnregisterApplicationsParamsData& params, JsonData::XCast::XCastSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    std::list<string> _elements;
                    auto _Iterator = params.Applications.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>* const _applications{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>>(_elements)};
                    Exchange::IXCast::XCastSuccess _success{};

                    ASSERT(_applications != nullptr); 

                    if ((_applications != nullptr)) {
                        _errorCode = _impl_->UnregisterApplications(_applications, _success);
                        _applications->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setApplicationState"));
            _module_.Unregister(_T("getProtocolVersion"));
            _module_.Unregister(_T("setManufacturerName"));
            _module_.Unregister(_T("getManufacturerName"));
            _module_.Unregister(_T("setModelName"));
            _module_.Unregister(_T("getModelName"));
            _module_.Unregister(_T("setEnabled"));
            _module_.Unregister(_T("getEnabled"));
            _module_.Unregister(_T("setStandbyBehavior"));
            _module_.Unregister(_T("getStandbyBehavior"));
            _module_.Unregister(_T("setFriendlyName"));
            _module_.Unregister(_T("getFriendlyName"));
            _module_.Unregister(_T("registerApplications"));
            _module_.Unregister(_T("unregisterApplications"));
        }

        namespace Event {

            // Event: 'onApplicationLaunchRequest' - Triggered when the cast service receives a launch request from a client with launch params
            static void OnApplicationLaunchRequestWithParam(const JSONRPC& _module_,
                     const JsonData::XCast::OnApplicationLaunchRequestWithParamParamsData& params)
            {
                _module_.Notify(_T("onApplicationLaunchRequest"), params);
            }

            // Event: 'onApplicationLaunchRequest' - Triggered when the cast service receives a launch request from a client with launch params
            static void OnApplicationLaunchRequestWithParam(const JSONRPC& _module_, const Core::JSON::String& appName, const Core::JSON::String& strPayLoad,
                     const Core::JSON::String& strQuery, const Core::JSON::String& strAddDataUrl)
            {
                JsonData::XCast::OnApplicationLaunchRequestWithParamParamsData _params_;
                _params_.AppName = appName;
                _params_.StrPayLoad = strPayLoad;
                _params_.StrQuery = strQuery;
                _params_.StrAddDataUrl = strAddDataUrl;

                OnApplicationLaunchRequestWithParam(_module_, _params_);
            }

            // Event: 'onApplicationLaunchRequest' - Triggered when the cast service receives a launch request from a client with launch params
            static void OnApplicationLaunchRequestWithParam(const JSONRPC& _module_, const string& appName, const string& strPayLoad, const string& strQuery,
                     const string& strAddDataUrl)
            {
                JsonData::XCast::OnApplicationLaunchRequestWithParamParamsData _params_;
                _params_.AppName = appName;
                _params_.StrPayLoad = strPayLoad;
                _params_.StrQuery = strQuery;
                _params_.StrAddDataUrl = strAddDataUrl;

                OnApplicationLaunchRequestWithParam(_module_, _params_);
            }

            // Event: 'onApplicationLaunchRequest' - Triggered when the cast service receives a launch request from a client with launch params
            static void OnApplicationLaunchRequest(const JSONRPC& _module_, const JsonData::XCast::OnApplicationLaunchRequestParamsData& params)
            {
                _module_.Notify(_T("onApplicationLaunchRequest"), params);
            }

            // Event: 'onApplicationLaunchRequest' - Triggered when the cast service receives a launch request from a client with launch params
            static void OnApplicationLaunchRequest(const JSONRPC& _module_, const Core::JSON::String& appName, const Core::JSON::String& parameter)
            {
                JsonData::XCast::OnApplicationLaunchRequestParamsData _params_;
                _params_.AppName = appName;
                _params_.Parameter = parameter;

                OnApplicationLaunchRequest(_module_, _params_);
            }

            // Event: 'onApplicationLaunchRequest' - Triggered when the cast service receives a launch request from a client with launch params
            static void OnApplicationLaunchRequest(const JSONRPC& _module_, const string& appName, const string& parameter)
            {
                JsonData::XCast::OnApplicationLaunchRequestParamsData _params_;
                _params_.AppName = appName;
                _params_.Parameter = parameter;

                OnApplicationLaunchRequest(_module_, _params_);
            }

            // Event: 'onApplicationStopRequest' - Triggered when the cast service receives a stop request from a client
            static void OnApplicationStopRequest(const JSONRPC& _module_, const JsonData::XCast::OnApplicationStopRequestParamsInfo& params)
            {
                _module_.Notify(_T("onApplicationStopRequest"), params);
            }

            // Event: 'onApplicationStopRequest' - Triggered when the cast service receives a stop request from a client
            static void OnApplicationStopRequest(const JSONRPC& _module_, const Core::JSON::String& appName, const Core::JSON::String& appID)
            {
                JsonData::XCast::OnApplicationStopRequestParamsInfo _params_;
                _params_.AppName = appName;
                _params_.AppID = appID;

                OnApplicationStopRequest(_module_, _params_);
            }

            // Event: 'onApplicationStopRequest' - Triggered when the cast service receives a stop request from a client
            static void OnApplicationStopRequest(const JSONRPC& _module_, const string& appName, const string& appID)
            {
                JsonData::XCast::OnApplicationStopRequestParamsInfo _params_;
                _params_.AppName = appName;
                _params_.AppID = appID;

                OnApplicationStopRequest(_module_, _params_);
            }

            // Event: 'onApplicationHideRequest' - Triggered when the cast service receives a hide request from a client
            static void OnApplicationHideRequest(const JSONRPC& _module_, const JsonData::XCast::OnApplicationStopRequestParamsInfo& params)
            {
                _module_.Notify(_T("onApplicationHideRequest"), params);
            }

            // Event: 'onApplicationHideRequest' - Triggered when the cast service receives a hide request from a client
            static void OnApplicationHideRequest(const JSONRPC& _module_, const Core::JSON::String& appName, const Core::JSON::String& appID)
            {
                JsonData::XCast::OnApplicationStopRequestParamsInfo _params_;
                _params_.AppName = appName;
                _params_.AppID = appID;

                OnApplicationHideRequest(_module_, _params_);
            }

            // Event: 'onApplicationHideRequest' - Triggered when the cast service receives a hide request from a client
            static void OnApplicationHideRequest(const JSONRPC& _module_, const string& appName, const string& appID)
            {
                JsonData::XCast::OnApplicationStopRequestParamsInfo _params_;
                _params_.AppName = appName;
                _params_.AppID = appID;

                OnApplicationHideRequest(_module_, _params_);
            }

            // Event: 'onApplicationStateRequest' - Triggered when the cast service needs an update of the application state
            static void OnApplicationStateRequest(const JSONRPC& _module_, const JsonData::XCast::OnApplicationStopRequestParamsInfo& params)
            {
                _module_.Notify(_T("onApplicationStateRequest"), params);
            }

            // Event: 'onApplicationStateRequest' - Triggered when the cast service needs an update of the application state
            static void OnApplicationStateRequest(const JSONRPC& _module_, const Core::JSON::String& appName, const Core::JSON::String& appID)
            {
                JsonData::XCast::OnApplicationStopRequestParamsInfo _params_;
                _params_.AppName = appName;
                _params_.AppID = appID;

                OnApplicationStateRequest(_module_, _params_);
            }

            // Event: 'onApplicationStateRequest' - Triggered when the cast service needs an update of the application state
            static void OnApplicationStateRequest(const JSONRPC& _module_, const string& appName, const string& appID)
            {
                JsonData::XCast::OnApplicationStopRequestParamsInfo _params_;
                _params_.AppName = appName;
                _params_.AppID = appID;

                OnApplicationStateRequest(_module_, _params_);
            }

            // Event: 'onApplicationResumeRequest' - Triggered when the cast service receives a resume request from a client
            static void OnApplicationResumeRequest(const JSONRPC& _module_, const JsonData::XCast::OnApplicationStopRequestParamsInfo& params)
            {
                _module_.Notify(_T("onApplicationResumeRequest"), params);
            }

            // Event: 'onApplicationResumeRequest' - Triggered when the cast service receives a resume request from a client
            static void OnApplicationResumeRequest(const JSONRPC& _module_, const Core::JSON::String& appName, const Core::JSON::String& appID)
            {
                JsonData::XCast::OnApplicationStopRequestParamsInfo _params_;
                _params_.AppName = appName;
                _params_.AppID = appID;

                OnApplicationResumeRequest(_module_, _params_);
            }

            // Event: 'onApplicationResumeRequest' - Triggered when the cast service receives a resume request from a client
            static void OnApplicationResumeRequest(const JSONRPC& _module_, const string& appName, const string& appID)
            {
                JsonData::XCast::OnApplicationStopRequestParamsInfo _params_;
                _params_.AppName = appName;
                _params_.AppID = appID;

                OnApplicationResumeRequest(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JXCast

} // namespace Exchange

} // namespace WPEFramework

