// Generated automatically from 'IMiracastService.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_MiracastService.h"
#include <interfaces/IMiracastService.h>

namespace WPEFramework {

namespace Exchange {

    namespace JMiracastService {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IMiracastService* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JMiracastService"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setEnable' - To enable or disable the Miracast feature
            _module_.Register<JsonData::MiracastService::SetEnabledParamsInfo, JsonData::MiracastService::ResultInfo>(_T("setEnable"), 
                [_impl_](const JsonData::MiracastService::SetEnabledParamsInfo& params, JsonData::MiracastService::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};
                    Exchange::IMiracastService::Result _result{};

                    _errorCode = _impl_->SetEnabled(_enabled, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'getEnable' - To get the enable status of the Miracast feature
            _module_.Register<void, JsonData::MiracastService::GetEnabledResultData>(_T("getEnable"), 
                [_impl_](JsonData::MiracastService::GetEnabledResultData& result) -> uint32_t {
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

            // Method: 'acceptClientConnection' - To accept or reject new client connection requests for the Miracast feature
            _module_.Register<JsonData::MiracastService::AcceptClientConnectionParamsData, JsonData::MiracastService::ResultInfo>(_T("acceptClientConnection"), 
                [_impl_](const JsonData::MiracastService::AcceptClientConnectionParamsData& params, JsonData::MiracastService::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _requestStatus{params.RequestStatus};
                    Exchange::IMiracastService::Result _result{};

                    _errorCode = _impl_->AcceptClientConnection(_requestStatus, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'stopClientConnection' - To abort the ongoing connection after accepted connection request
            _module_.Register<JsonData::MiracastService::StopClientConnectionParamsInfo, JsonData::MiracastService::ResultInfo>(_T("stopClientConnection"), 
                [_impl_](const JsonData::MiracastService::StopClientConnectionParamsInfo& params, JsonData::MiracastService::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _clientMac{params.ClientMac};
                    const string _clientName{params.ClientName};
                    Exchange::IMiracastService::Result _result{};

                    _errorCode = _impl_->StopClientConnection(_clientMac, _clientName, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'updatePlayerState' - Update the Miracast Player State to the Miracast Service Plugin
            _module_.Register<JsonData::MiracastService::UpdatePlayerStateParamsData, JsonData::MiracastService::ResultInfo>(_T("updatePlayerState"), 
                [_impl_](const JsonData::MiracastService::UpdatePlayerStateParamsData& params, JsonData::MiracastService::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _clientMac{params.ClientMac};
                    const Exchange::IMiracastService::PlayerState _playerState{params.PlayerState};
                    const int32_t _reasonCode{params.ReasonCode};
                    Exchange::IMiracastService::Result _result{};

                    _errorCode = _impl_->UpdatePlayerState(_clientMac, _playerState, _reasonCode, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'setP2PBackendDiscovery' - Sets the status of the MiracastService backend discovery
            _module_.Register<JsonData::MiracastService::SetEnabledParamsInfo, JsonData::MiracastService::ResultInfo>(_T("setP2PBackendDiscovery"), 
                [_impl_](const JsonData::MiracastService::SetEnabledParamsInfo& params, JsonData::MiracastService::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};
                    Exchange::IMiracastService::Result _result{};

                    _errorCode = _impl_->SetP2PBackendDiscovery(_enabled, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setEnable"));
            _module_.Unregister(_T("getEnable"));
            _module_.Unregister(_T("acceptClientConnection"));
            _module_.Unregister(_T("stopClientConnection"));
            _module_.Unregister(_T("updatePlayerState"));
            _module_.Unregister(_T("setP2PBackendDiscovery"));
        }

        namespace Event {

            // Event: 'onClientConnectionRequest' - Triggered when the Miracast Service plugin receives a new connection request from a client
            static void OnClientConnectionRequest(const JSONRPC& _module_, const JsonData::MiracastService::StopClientConnectionParamsInfo& params)
            {
                _module_.Notify(_T("onClientConnectionRequest"), params);
            }

            // Event: 'onClientConnectionRequest' - Triggered when the Miracast Service plugin receives a new connection request from a client
            static void OnClientConnectionRequest(const JSONRPC& _module_, const Core::JSON::String& clientMac, const Core::JSON::String& clientName)
            {
                JsonData::MiracastService::StopClientConnectionParamsInfo _params_;
                _params_.ClientMac = clientMac;
                _params_.ClientName = clientName;

                OnClientConnectionRequest(_module_, _params_);
            }

            // Event: 'onClientConnectionRequest' - Triggered when the Miracast Service plugin receives a new connection request from a client
            static void OnClientConnectionRequest(const JSONRPC& _module_, const string& clientMac, const string& clientName)
            {
                JsonData::MiracastService::StopClientConnectionParamsInfo _params_;
                _params_.ClientMac = clientMac;
                _params_.ClientName = clientName;

                OnClientConnectionRequest(_module_, _params_);
            }

            // Event: 'onClientConnectionError' - It is triggered when the Miracast Service plugin failed to connect with the source streaming device due to some error, like P2P related errors during activation or while streaming
            static void OnClientConnectionError(const JSONRPC& _module_, const JsonData::MiracastService::OnClientConnectionErrorParamsData& params)
            {
                _module_.Notify(_T("onClientConnectionError"), params);
            }

            // Event: 'onClientConnectionError' - It is triggered when the Miracast Service plugin failed to connect with the source streaming device due to some error, like P2P related errors during activation or while streaming
            static void OnClientConnectionError(const JSONRPC& _module_, const Core::JSON::String& clientMac, const Core::JSON::String& clientName,
                     const Core::JSON::String& reasonCode, const Core::JSON::EnumType<Exchange::IMiracastService::ReasonCode>& reasonDescription)
            {
                JsonData::MiracastService::OnClientConnectionErrorParamsData _params_;
                _params_.ClientMac = clientMac;
                _params_.ClientName = clientName;
                _params_.ReasonCode = reasonCode;
                _params_.ReasonDescription = reasonDescription;

                OnClientConnectionError(_module_, _params_);
            }

            // Event: 'onClientConnectionError' - It is triggered when the Miracast Service plugin failed to connect with the source streaming device due to some error, like P2P related errors during activation or while streaming
            static void OnClientConnectionError(const JSONRPC& _module_, const string& clientMac, const string& clientName, const string& reasonCode,
                     const Exchange::IMiracastService::ReasonCode& reasonDescription)
            {
                JsonData::MiracastService::OnClientConnectionErrorParamsData _params_;
                _params_.ClientMac = clientMac;
                _params_.ClientName = clientName;
                _params_.ReasonCode = reasonCode;
                _params_.ReasonDescription = reasonDescription;

                OnClientConnectionError(_module_, _params_);
            }

            // Event: 'onLaunchRequest' - Miracast Service Plugin raises this Event to request RA or MiracastWidget to launch the Miracast Player
            static void OnLaunchRequest(const JSONRPC& _module_, const JsonData::MiracastService::OnLaunchRequestParamsData& params)
            {
                _module_.Notify(_T("onLaunchRequest"), params);
            }

            // Event: 'onLaunchRequest' - Miracast Service Plugin raises this Event to request RA or MiracastWidget to launch the Miracast Player
            static void OnLaunchRequest(const JSONRPC& _module_, const Exchange::IMiracastService::DeviceParameters& deviceParameters)
            {
                JsonData::MiracastService::OnLaunchRequestParamsData _params_;
                _params_.DeviceParameters = deviceParameters;

                OnLaunchRequest(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JMiracastService

} // namespace Exchange

} // namespace WPEFramework

