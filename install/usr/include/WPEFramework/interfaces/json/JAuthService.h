// Generated automatically from 'IAuthService.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_AuthService.h"
#include <interfaces/IAuthService.h>

namespace WPEFramework {

namespace Exchange {

    namespace JAuthService {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IAuthService* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JAuthService"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'Configure'
            _module_.Register<void, void>(_T("Configure"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->Configure();

                    return (_errorCode);
                });

            // Method: 'getInfo' - Returns the STB Auth Service info
            _module_.Register<void, JsonData::AuthService::GetInfoResultData>(_T("getInfo"), 
                [_impl_](JsonData::AuthService::GetInfoResultData& info) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetInfoResult _info{};

                    _errorCode = _impl_->GetInfo(_info);

                    if (_errorCode == Core::ERROR_NONE) {
                        info = _info;
                    }

                    return (_errorCode);
                });

            // Method: 'getDeviceInfo' - Returns device info - Deprecated
            _module_.Register<void, JsonData::AuthService::GetDeviceInfoResultData>(_T("getDeviceInfo"), 
                [_impl_](JsonData::AuthService::GetDeviceInfoResultData& info) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetDeviceInfoResult _info{};

                    _errorCode = _impl_->GetDeviceInfo(_info);

                    if (_errorCode == Core::ERROR_NONE) {
                        info = _info;
                    }

                    return (_errorCode);
                });

            // Method: 'getDeviceId' - Returns the device (receiver) id
            _module_.Register<void, JsonData::AuthService::GetDeviceIdResultData>(_T("getDeviceId"), 
                [_impl_](JsonData::AuthService::GetDeviceIdResultData& idInfo) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetDeviceIdResult _idInfo{};

                    _errorCode = _impl_->GetDeviceId(_idInfo);

                    if (_errorCode == Core::ERROR_NONE) {
                        idInfo = _idInfo;
                    }

                    return (_errorCode);
                });

            // Method: 'setDeviceId' - Sets device id
            _module_.Register<JsonData::AuthService::SetDeviceIdParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setDeviceId"), 
                [_impl_](const JsonData::AuthService::SetDeviceIdParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& idStatus) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _deviceId{params.DeviceId};
                    Exchange::IAuthService::SuccessMsgResult _idStatus{};

                    _errorCode = _impl_->SetDeviceId(_deviceId, _idStatus);

                    if (_errorCode == Core::ERROR_NONE) {
                        idStatus = _idStatus;
                    }

                    return (_errorCode);
                });

            // Method: 'setPartnerId' - Sets partner id
            _module_.Register<JsonData::AuthService::SetPartnerIdParamsData, JsonData::AuthService::SetPartnerIdResultData>(_T("setPartnerId"), 
                [_impl_](const JsonData::AuthService::SetPartnerIdParamsData& params, JsonData::AuthService::SetPartnerIdResultData& idStatus) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _partnerId{params.PartnerId};
                    Exchange::IAuthService::SetPartnerIdResult _idStatus{};

                    _errorCode = _impl_->SetPartnerId(_partnerId, _idStatus);

                    if (_errorCode == Core::ERROR_NONE) {
                        idStatus = _idStatus;
                    }

                    return (_errorCode);
                });

            // Method: 'getAuthToken' - Returns the authorization token
            _module_.Register<JsonData::AuthService::GetAuthTokenParamsData, JsonData::AuthService::GetAuthTokenResultData>(_T("getAuthToken"), 
                [_impl_](const JsonData::AuthService::GetAuthTokenParamsData& params, JsonData::AuthService::GetAuthTokenResultData& getResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _forceNew{params.ForceNew};
                    const bool _recoverRenewal{params.RecoverRenewal};
                    Exchange::IAuthService::GetAuthTokenResult _getResult{};

                    _errorCode = _impl_->GetAuthToken(_forceNew, _recoverRenewal, _getResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        getResult = _getResult;
                    }

                    return (_errorCode);
                });

            // Method: 'getSessionToken' - Returns the session token
            _module_.Register<void, JsonData::AuthService::GetSessionTokenResultData>(_T("getSessionToken"), 
                [_impl_](JsonData::AuthService::GetSessionTokenResultData& getResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetSessionTokenResult _getResult{};

                    _errorCode = _impl_->GetSessionToken(_getResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        getResult = _getResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setSessionToken' - Sets the session token
            _module_.Register<JsonData::AuthService::SetSessionTokenParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setSessionToken"), 
                [_impl_](const JsonData::AuthService::SetSessionTokenParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _status{params.Status};
                    const string _token{params.Token};
                    const uint32_t _expires{params.Expires};
                    const string _clientId{params.ClientId};
                    const string _messageId{params.MessageId};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetSessionToken(_status, _token, _expires, _clientId, _messageId, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'getServiceAccessToken' - Returns the service access token
            _module_.Register<void, JsonData::AuthService::GetServiceAccessTokenResultData>(_T("getServiceAccessToken"), 
                [_impl_](JsonData::AuthService::GetServiceAccessTokenResultData& getResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetServiceAccessTokenResult _getResult{};

                    _errorCode = _impl_->GetServiceAccessToken(_getResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        getResult = _getResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setServiceAccessToken' - Sets the service access token
            _module_.Register<JsonData::AuthService::SetServiceAccessTokenParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setServiceAccessToken"), 
                [_impl_](const JsonData::AuthService::SetServiceAccessTokenParamsData& params,
                         JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _status{params.Status};
                    const string _token{params.Token};
                    const uint32_t _expires{params.Expires};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetServiceAccessToken(_status, _token, _expires, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'setContentAccessToken' - Stores the content access token in the secured persistent location
            _module_.Register<JsonData::AuthService::SetContentAccessTokenParamsInfo, Core::JSON::Boolean>(_T("setContentAccessToken"), 
                [_impl_](const JsonData::AuthService::SetContentAccessTokenParamsInfo& params, Core::JSON::Boolean& status) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _token{params.Token};
                    const uint32_t _expires{params.Expires};
                    bool _status{};

                    _errorCode = _impl_->SetContentAccessToken(_token, _expires, _status);

                    if (_errorCode == Core::ERROR_NONE) {
                        status = _status;
                    }

                    return (_errorCode);
                });

            // Method: 'getContentAccessToken' - Retrieves the content access token from the secured persistent location
            _module_.Register<void, JsonData::AuthService::SetContentAccessTokenParamsInfo>(_T("getContentAccessToken"), 
                [_impl_](JsonData::AuthService::SetContentAccessTokenParamsInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _token{};
                    uint32_t _expires{};

                    _errorCode = _impl_->GetContentAccessToken(_token, _expires);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Token = _token;
                        result.Expires = _expires;
                    }

                    return (_errorCode);
                });

            // Method: 'getServiceAccountId' - Returns the service account ID
            _module_.Register<void, JsonData::AuthService::GetServiceAccountIdResultData>(_T("getServiceAccountId"), 
                [_impl_](JsonData::AuthService::GetServiceAccountIdResultData& getResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetServiceAccountIdResult _getResult{};

                    _errorCode = _impl_->GetServiceAccountId(_getResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        getResult = _getResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setServiceAccountId' - Sets the service account ID
            _module_.Register<JsonData::AuthService::SetServiceAccountIdParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setServiceAccountId"), 
                [_impl_](const JsonData::AuthService::SetServiceAccountIdParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _serviceAccountId{params.ServiceAccountId};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetServiceAccountId(_serviceAccountId, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'setAuthIdToken' - Sets the authorization ID token
            _module_.Register<JsonData::AuthService::SetAuthIdTokenParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setAuthIdToken"), 
                [_impl_](const JsonData::AuthService::SetAuthIdTokenParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _authIdToken{params.AuthIdToken};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetAuthIdToken(_authIdToken, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'ready' - Lets the Auth Service know that the device's provisioned keys, certificates, and binaries are present on the device
            _module_.Register<JsonData::AuthService::ReadyParamsInfo, JsonData::AuthService::SuccessMsgResultInfo>(_T("ready"), 
                [_impl_](const JsonData::AuthService::ReadyParamsInfo& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _status{params.Status};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->Ready(_status, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'getBootstrapProperty' - Returns the bootstrap property associated with the current partnerId
            _module_.Register<JsonData::AuthService::GetBootstrapPropertyParamsData,
                     JsonData::AuthService::GetBootstrapPropResultData>(_T("getBootstrapProperty"), 
                [_impl_](const JsonData::AuthService::GetBootstrapPropertyParamsData& params,
                         JsonData::AuthService::GetBootstrapPropResultData& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _bootstrapProperty{params.BootstrapProperty};
                    Exchange::IAuthService::GetBootstrapPropResult _setStat{};

                    _errorCode = _impl_->GetBootstrapProperty(_bootstrapProperty, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'activationStarted' - Lets the Auth Service know that the device's activation is started
            _module_.Register<void, JsonData::AuthService::SuccessResultInfo>(_T("activationStarted"), 
                [_impl_](JsonData::AuthService::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::SuccessResult _successResult{};

                    _errorCode = _impl_->ActivationStarted(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'activationComplete' - Lets the Auth Service know that the device's activation is completed
            _module_.Register<void, JsonData::AuthService::SuccessResultInfo>(_T("activationComplete"), 
                [_impl_](JsonData::AuthService::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::SuccessResult _successResult{};

                    _errorCode = _impl_->ActivationComplete(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'getLostAndFoundAccessToken' - Returns the stored Lost and Found access token (LFAT) if one is available
            _module_.Register<void, JsonData::AuthService::GetLostAndFoundAccessTokenResultData>(_T("getLostAndFoundAccessToken"), 
                [_impl_](JsonData::AuthService::GetLostAndFoundAccessTokenResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _lostAndFoundAccessToken{};
                    string _message{};
                    bool _success{};

                    _errorCode = _impl_->GetLostAndFoundAccessToken(_lostAndFoundAccessToken, _message, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.LostAndFoundAccessToken = _lostAndFoundAccessToken;
                        result.LostAndFoundAccessToken.SetQuoted(false);
                        result.Message = _message;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setLostAndFoundAccessToken' - Sets the Lost and Found access token
            _module_.Register<JsonData::AuthService::SetLostAndFoundAccessTokenParamsData,
                     JsonData::AuthService::SuccessMsgResultInfo>(_T("setLostAndFoundAccessToken"), 
                [_impl_](const JsonData::AuthService::SetLostAndFoundAccessTokenParamsData& params,
                         JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _lostAndFoundAccessToken{params.LostAndFoundAccessToken};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetLostAndFoundAccessToken(_lostAndFoundAccessToken, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'getXDeviceId' - Returns the xDevice ID
            _module_.Register<void, JsonData::AuthService::GetXDeviceIdResultData>(_T("getXDeviceId"), 
                [_impl_](JsonData::AuthService::GetXDeviceIdResultData& xdResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetXDeviceIdResult _xdResult{};

                    _errorCode = _impl_->GetXDeviceId(_xdResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        xdResult = _xdResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setXDeviceId' - Sets the xDevice ID
            _module_.Register<JsonData::AuthService::SetXDeviceIdParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setXDeviceId"), 
                [_impl_](const JsonData::AuthService::SetXDeviceIdParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _xDeviceId{params.XDeviceId};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetXDeviceId(_xDeviceId, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'getExperience' - Returns the experience
            _module_.Register<void, JsonData::AuthService::GetExpResultData>(_T("getExperience"), 
                [_impl_](JsonData::AuthService::GetExpResultData& expdResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetExpResult _expdResult{};

                    _errorCode = _impl_->GetExperience(_expdResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        expdResult = _expdResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setExperience' - Sets the experience
            _module_.Register<JsonData::AuthService::SetExperienceParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setExperience"), 
                [_impl_](const JsonData::AuthService::SetExperienceParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _experience{params.Experience};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetExperience(_experience, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'getXifaId' - Returns xifaId
            _module_.Register<void, JsonData::AuthService::GetxifaIdResultData>(_T("getXifaId"), 
                [_impl_](JsonData::AuthService::GetxifaIdResultData& xifaIdResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::GetxifaIdResult _xifaIdResult{};

                    _errorCode = _impl_->GetXifaId(_xifaIdResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        xifaIdResult = _xifaIdResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setXifaId' - Sets xifaId
            _module_.Register<JsonData::AuthService::SetXifaIdParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setXifaId"), 
                [_impl_](const JsonData::AuthService::SetXifaIdParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _xifaId{params.XifaId};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetXifaId(_xifaId, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'getAdvtOptOut' - Returns advtOptOut
            _module_.Register<void, JsonData::AuthService::AdvtOptOutResultData>(_T("getAdvtOptOut"), 
                [_impl_](JsonData::AuthService::AdvtOptOutResultData& advtOptOutResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::AdvtOptOutResult _advtOptOutResult{};

                    _errorCode = _impl_->GetAdvtOptOut(_advtOptOutResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        advtOptOutResult = _advtOptOutResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setAdvtOptOut' - Sets advtOptOut
            _module_.Register<JsonData::AuthService::SetAdvtOptOutParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setAdvtOptOut"), 
                [_impl_](const JsonData::AuthService::SetAdvtOptOutParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _advtOptOut{params.AdvtOptOut};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetAdvtOptOut(_advtOptOut, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'getActivationStatus' - Returns the activation status
            _module_.Register<void, JsonData::AuthService::ActivationStatusResultData>(_T("getActivationStatus"), 
                [_impl_](JsonData::AuthService::ActivationStatusResultData& statusResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::ActivationStatusResult _statusResult{};

                    _errorCode = _impl_->GetActivationStatus(_statusResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        statusResult = _statusResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setActivationStatus'
            _module_.Register<JsonData::AuthService::ReadyParamsInfo, JsonData::AuthService::SuccessMsgResultInfo>(_T("setActivationStatus"), 
                [_impl_](const JsonData::AuthService::ReadyParamsInfo& params, JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _status{params.Status};
                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->SetActivationStatus(_status, _setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'clearAuthToken' - Clears the authorization token
            _module_.Register<void, JsonData::AuthService::SuccessMsgResultInfo>(_T("clearAuthToken"), 
                [_impl_](JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->ClearAuthToken(_setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'clearSessionToken' - Clears the session token
            _module_.Register<void, JsonData::AuthService::SuccessMsgResultInfo>(_T("clearSessionToken"), 
                [_impl_](JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->ClearSessionToken(_setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'clearServiceAccessToken' - Clears the service access token
            _module_.Register<void, JsonData::AuthService::SuccessMsgResultInfo>(_T("clearServiceAccessToken"), 
                [_impl_](JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->ClearServiceAccessToken(_setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'clearLostAndFoundAccessToken' - Clears the Lost and Found access token
            _module_.Register<void, JsonData::AuthService::SuccessMsgResultInfo>(_T("clearLostAndFoundAccessToken"), 
                [_impl_](JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->ClearLostAndFoundAccessToken(_setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'clearServiceAccountId' - Clears the service account ID
            _module_.Register<void, JsonData::AuthService::SuccessMsgResultInfo>(_T("clearServiceAccountId"), 
                [_impl_](JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->ClearServiceAccountId(_setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'clearCustomProperties' - Clears the custom properties
            _module_.Register<void, JsonData::AuthService::SuccessMsgResultInfo>(_T("clearCustomProperties"), 
                [_impl_](JsonData::AuthService::SuccessMsgResultInfo& setStat) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IAuthService::SuccessMsgResult _setStat{};

                    _errorCode = _impl_->ClearCustomProperties(_setStat);

                    if (_errorCode == Core::ERROR_NONE) {
                        setStat = _setStat;
                    }

                    return (_errorCode);
                });

            // Method: 'getCustomProperties' - Returns the custom properties
            _module_.Register<void, JsonData::AuthService::GetCustomPropertiesResultData>(_T("getCustomProperties"), 
                [_impl_](JsonData::AuthService::GetCustomPropertiesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _customProperties{};
                    bool _success{};

                    _errorCode = _impl_->GetCustomProperties(_customProperties, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.CustomProperties = _customProperties;
                        result.CustomProperties.SetQuoted(false);
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setCustomProperties' - Sets the custom properties
            _module_.Register<JsonData::AuthService::SetCustomPropertiesParamsData, Core::JSON::Boolean>(_T("setCustomProperties"), 
                [_impl_](const JsonData::AuthService::SetCustomPropertiesParamsData& params, Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _customProperties{params.CustomProperties};
                    bool _success{};

                    _errorCode = _impl_->SetCustomProperties(_customProperties, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getAlternateIds' - Returns alternate IDs as key/value pairs
            _module_.Register<void, JsonData::AuthService::GetAlternateIdsResultData>(_T("getAlternateIds"), 
                [_impl_](JsonData::AuthService::GetAlternateIdsResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _alternateIds{};
                    string _message{};
                    bool _success{};

                    _errorCode = _impl_->GetAlternateIds(_alternateIds, _message, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.AlternateIds = _alternateIds;
                        result.AlternateIds.SetQuoted(false);
                        result.Message = _message;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setAlternateIds' - Sets alternate IDs as key/value pairs
            _module_.Register<JsonData::AuthService::SetAlternateIdsParamsData, JsonData::AuthService::SuccessMsgResultInfo>(_T("setAlternateIds"), 
                [_impl_](const JsonData::AuthService::SetAlternateIdsParamsData& params, JsonData::AuthService::SuccessMsgResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _alternateIds{params.AlternateIds};
                    string _message{};
                    bool _success{};

                    _errorCode = _impl_->SetAlternateIds(_alternateIds, _message, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Message = _message;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getTransitionData' - Returns the transition data
            _module_.Register<void, JsonData::AuthService::GetTransitionDataResultData>(_T("getTransitionData"), 
                [_impl_](JsonData::AuthService::GetTransitionDataResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _transitionData{};
                    string _message{};
                    bool _success{};

                    _errorCode = _impl_->GetTransitionData(_transitionData, _message, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.TransitionData = _transitionData;
                        result.TransitionData.SetQuoted(false);
                        result.Message = _message;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("Configure"));
            _module_.Unregister(_T("getInfo"));
            _module_.Unregister(_T("getDeviceInfo"));
            _module_.Unregister(_T("getDeviceId"));
            _module_.Unregister(_T("setDeviceId"));
            _module_.Unregister(_T("setPartnerId"));
            _module_.Unregister(_T("getAuthToken"));
            _module_.Unregister(_T("getSessionToken"));
            _module_.Unregister(_T("setSessionToken"));
            _module_.Unregister(_T("getServiceAccessToken"));
            _module_.Unregister(_T("setServiceAccessToken"));
            _module_.Unregister(_T("setContentAccessToken"));
            _module_.Unregister(_T("getContentAccessToken"));
            _module_.Unregister(_T("getServiceAccountId"));
            _module_.Unregister(_T("setServiceAccountId"));
            _module_.Unregister(_T("setAuthIdToken"));
            _module_.Unregister(_T("ready"));
            _module_.Unregister(_T("getBootstrapProperty"));
            _module_.Unregister(_T("activationStarted"));
            _module_.Unregister(_T("activationComplete"));
            _module_.Unregister(_T("getLostAndFoundAccessToken"));
            _module_.Unregister(_T("setLostAndFoundAccessToken"));
            _module_.Unregister(_T("getXDeviceId"));
            _module_.Unregister(_T("setXDeviceId"));
            _module_.Unregister(_T("getExperience"));
            _module_.Unregister(_T("setExperience"));
            _module_.Unregister(_T("getXifaId"));
            _module_.Unregister(_T("setXifaId"));
            _module_.Unregister(_T("getAdvtOptOut"));
            _module_.Unregister(_T("setAdvtOptOut"));
            _module_.Unregister(_T("getActivationStatus"));
            _module_.Unregister(_T("setActivationStatus"));
            _module_.Unregister(_T("clearAuthToken"));
            _module_.Unregister(_T("clearSessionToken"));
            _module_.Unregister(_T("clearServiceAccessToken"));
            _module_.Unregister(_T("clearLostAndFoundAccessToken"));
            _module_.Unregister(_T("clearServiceAccountId"));
            _module_.Unregister(_T("clearCustomProperties"));
            _module_.Unregister(_T("getCustomProperties"));
            _module_.Unregister(_T("setCustomProperties"));
            _module_.Unregister(_T("getAlternateIds"));
            _module_.Unregister(_T("setAlternateIds"));
            _module_.Unregister(_T("getTransitionData"));
        }

        namespace Event {

            // Event: 'onActivationStatusChanged' - The Activation status changed has changed
            static void OnActivationStatusChanged(const JSONRPC& _module_, const JsonData::AuthService::OnActivationStatusChangedParamsData& params)
            {
                _module_.Notify(_T("onActivationStatusChanged"), params);
            }

            // Event: 'onActivationStatusChanged' - The Activation status changed has changed
            static void OnActivationStatusChanged(const JSONRPC& _module_, const Core::JSON::String& oldActivationStatus,
                     const Core::JSON::String& newActivationStatus)
            {
                JsonData::AuthService::OnActivationStatusChangedParamsData _params_;
                _params_.OldActivationStatus = oldActivationStatus;
                _params_.NewActivationStatus = newActivationStatus;

                OnActivationStatusChanged(_module_, _params_);
            }

            // Event: 'onActivationStatusChanged' - The Activation status changed has changed
            static void OnActivationStatusChanged(const JSONRPC& _module_, const string& oldActivationStatus, const string& newActivationStatus)
            {
                JsonData::AuthService::OnActivationStatusChangedParamsData _params_;
                _params_.OldActivationStatus = oldActivationStatus;
                _params_.NewActivationStatus = newActivationStatus;

                OnActivationStatusChanged(_module_, _params_);
            }

            // Event: 'onServiceAccountIdChanged' - The Service account Id has changed
            static void OnServiceAccountIdChanged(const JSONRPC& _module_, const JsonData::AuthService::OnServiceAccountIdChangedParamsData& params)
            {
                _module_.Notify(_T("onServiceAccountIdChanged"), params);
            }

            // Event: 'onServiceAccountIdChanged' - The Service account Id has changed
            static void OnServiceAccountIdChanged(const JSONRPC& _module_, const Core::JSON::String& oldServiceAccountId,
                     const Core::JSON::String& newServiceAccountId)
            {
                JsonData::AuthService::OnServiceAccountIdChangedParamsData _params_;
                _params_.OldServiceAccountId = oldServiceAccountId;
                _params_.NewServiceAccountId = newServiceAccountId;

                OnServiceAccountIdChanged(_module_, _params_);
            }

            // Event: 'onServiceAccountIdChanged' - The Service account Id has changed
            static void OnServiceAccountIdChanged(const JSONRPC& _module_, const string& oldServiceAccountId, const string& newServiceAccountId)
            {
                JsonData::AuthService::OnServiceAccountIdChangedParamsData _params_;
                _params_.OldServiceAccountId = oldServiceAccountId;
                _params_.NewServiceAccountId = newServiceAccountId;

                OnServiceAccountIdChanged(_module_, _params_);
            }

            // Event: 'authTokenChanged' - The Auth token has changed
            static void AuthTokenChanged(const JSONRPC& _module_)
            {
                _module_.Notify(_T("authTokenChanged"));
            }

            // Event: 'sessionTokenChanged' - The session token has changed
            static void SessionTokenChanged(const JSONRPC& _module_)
            {
                _module_.Notify(_T("sessionTokenChanged"));
            }

            // Event: 'serviceAccessTokenChanged' - The service access token has changed
            static void ServiceAccessTokenChanged(const JSONRPC& _module_)
            {
                _module_.Notify(_T("serviceAccessTokenChanged"));
            }

            // Event: 'onPartnerIdChanged' - The Partner ID has changed
            static void OnPartnerIdChanged(const JSONRPC& _module_, const JsonData::AuthService::OnPartnerIdChangedParamsData& params)
            {
                _module_.Notify(_T("onPartnerIdChanged"), params);
            }

            // Event: 'onPartnerIdChanged' - The Partner ID has changed
            static void OnPartnerIdChanged(const JSONRPC& _module_, const Core::JSON::String& oldPartnerId, const Core::JSON::String& newPartnerId)
            {
                JsonData::AuthService::OnPartnerIdChangedParamsData _params_;
                _params_.OldPartnerId = oldPartnerId;
                _params_.NewPartnerId = newPartnerId;

                OnPartnerIdChanged(_module_, _params_);
            }

            // Event: 'onPartnerIdChanged' - The Partner ID has changed
            static void OnPartnerIdChanged(const JSONRPC& _module_, const string& oldPartnerId, const string& newPartnerId)
            {
                JsonData::AuthService::OnPartnerIdChangedParamsData _params_;
                _params_.OldPartnerId = oldPartnerId;
                _params_.NewPartnerId = newPartnerId;

                OnPartnerIdChanged(_module_, _params_);
            }

            // Event: 'onContentAccessTokenChanged' - Indication for the clients that the Content Access Token is now changed so retrieve the token freshly
            static void OnContentAccessTokenChanged(const JSONRPC& _module_)
            {
                _module_.Notify(_T("onContentAccessTokenChanged"));
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JAuthService

} // namespace Exchange

} // namespace WPEFramework

