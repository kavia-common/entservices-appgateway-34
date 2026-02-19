// Generated automatically from 'IMiracastPlayer.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_MiracastPlayer.h"
#include <interfaces/IMiracastPlayer.h>

namespace WPEFramework {

namespace Exchange {

    namespace JMiracastPlayer {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IMiracastPlayer* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JMiracastPlayer"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'playRequest' - To set the Miracast Player State to Play after the Miracast session like RTSP communication and GStreamer Playback
            _module_.Register<JsonData::MiracastPlayer::PlayRequestParamsData, JsonData::MiracastPlayer::ResultInfo>(_T("playRequest"), 
                [_impl_](const JsonData::MiracastPlayer::PlayRequestParamsData& params, JsonData::MiracastPlayer::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::IMiracastPlayer::DeviceParameters _deviceParam(params.DeviceParam);
                    const Exchange::IMiracastPlayer::VideoRectangle _videoRect(params.VideoRect);
                    Exchange::IMiracastPlayer::Result _result{};

                    _errorCode = _impl_->PlayRequest(_deviceParam, _videoRect, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'stopRequest' - To stop the Miracast Player to tear down the RTSP communication, stop/close the GStreamer pipeline, clean up,
                    //  and reset the player state
            _module_.Register<JsonData::MiracastPlayer::StopRequestParamsData, JsonData::MiracastPlayer::ResultInfo>(_T("stopRequest"), 
                [_impl_](const JsonData::MiracastPlayer::StopRequestParamsData& params, JsonData::MiracastPlayer::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _clientMac{params.ClientMac};
                    const string _clientName{params.ClientName};
                    const int32_t _reasonCode{params.ReasonCode};
                    Exchange::IMiracastPlayer::Result _result{};

                    _errorCode = _impl_->StopRequest(_clientMac, _clientName, _reasonCode, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'setVideoRectangle' - Set the Video Rectangle
            _module_.Register<JsonData::MiracastPlayer::VideoRectangleInfo, JsonData::MiracastPlayer::ResultInfo>(_T("setVideoRectangle"), 
                [_impl_](const JsonData::MiracastPlayer::VideoRectangleInfo& params, JsonData::MiracastPlayer::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _startX{params.StartX};
                    const int32_t _startY{params.StartY};
                    const int32_t _width{params.Width};
                    const int32_t _height{params.Height};
                    Exchange::IMiracastPlayer::Result _result{};

                    _errorCode = _impl_->SetVideoRectangle(_startX, _startY, _width, _height, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'setWesterosEnvironment' - To configure the westeros environment arguments for the Miracast Player
            _module_.Register<JsonData::MiracastPlayer::SetWesterosEnvironmentParamsData, JsonData::MiracastPlayer::ResultInfo>(_T("setWesterosEnvironment"), 
                [_impl_](const JsonData::MiracastPlayer::SetWesterosEnvironmentParamsData& params, JsonData::MiracastPlayer::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    std::list<Exchange::IMiracastPlayer::EnvArguments> _elements;
                    auto _Iterator = params.WesterosArgs.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<IMiracastPlayer::EnvArguments,
                             ID_MIRACAST_PLAYER_ENV_ARGUMENTS_ITERATOR>* const _westerosArgs{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<IMiracastPlayer::EnvArguments,
                             ID_MIRACAST_PLAYER_ENV_ARGUMENTS_ITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<IMiracastPlayer::EnvArguments,
                             ID_MIRACAST_PLAYER_ENV_ARGUMENTS_ITERATOR>>(_elements)};
                    Exchange::IMiracastPlayer::Result _result{};

                    ASSERT(_westerosArgs != nullptr); 

                    if ((_westerosArgs != nullptr)) {
                        _errorCode = _impl_->SetWesterosEnvironment(_westerosArgs, _result);
                        _westerosArgs->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'unsetWesterosEnvironment' - To reset the westeros environment arguments for the Miracast Player
            _module_.Register<void, JsonData::MiracastPlayer::ResultInfo>(_T("unsetWesterosEnvironment"), 
                [_impl_](JsonData::MiracastPlayer::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IMiracastPlayer::Result _result{};

                    _errorCode = _impl_->UnsetWesterosEnvironment(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'setEnvArguments' - To configure the environment arguments for the Miracast Player
            _module_.Register<JsonData::MiracastPlayer::SetEnvArgumentsParamsData, JsonData::MiracastPlayer::ResultInfo>(_T("setEnvArguments"), 
                [_impl_](const JsonData::MiracastPlayer::SetEnvArgumentsParamsData& params, JsonData::MiracastPlayer::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    std::list<Exchange::IMiracastPlayer::EnvArguments> _elements;
                    auto _Iterator = params.EnvArgs.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<IMiracastPlayer::EnvArguments,
                             ID_MIRACAST_PLAYER_ENV_ARGUMENTS_ITERATOR>* const _envArgs{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<IMiracastPlayer::EnvArguments,
                             ID_MIRACAST_PLAYER_ENV_ARGUMENTS_ITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<IMiracastPlayer::EnvArguments,
                             ID_MIRACAST_PLAYER_ENV_ARGUMENTS_ITERATOR>>(_elements)};
                    Exchange::IMiracastPlayer::Result _result{};

                    ASSERT(_envArgs != nullptr); 

                    if ((_envArgs != nullptr)) {
                        _errorCode = _impl_->SetEnvArguments(_envArgs, _result);
                        _envArgs->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'unsetEnvArguments' - To reset the environment arguments for the Miracast Player
            _module_.Register<void, JsonData::MiracastPlayer::ResultInfo>(_T("unsetEnvArguments"), 
                [_impl_](JsonData::MiracastPlayer::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IMiracastPlayer::Result _result{};

                    _errorCode = _impl_->UnsetEnvArguments(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("playRequest"));
            _module_.Unregister(_T("stopRequest"));
            _module_.Unregister(_T("setVideoRectangle"));
            _module_.Unregister(_T("setWesterosEnvironment"));
            _module_.Unregister(_T("unsetWesterosEnvironment"));
            _module_.Unregister(_T("setEnvArguments"));
            _module_.Unregister(_T("unsetEnvArguments"));
        }

        namespace Event {

            // Event: 'onStateChange' - Notifies when a Miracast source device wants to connect
            static void OnStateChange(const JSONRPC& _module_, const JsonData::MiracastPlayer::OnStateChangeParamsData& params)
            {
                _module_.Notify(_T("onStateChange"), params);
            }

            // Event: 'onStateChange' - Notifies when a Miracast source device wants to connect
            static void OnStateChange(const JSONRPC& _module_, const Core::JSON::String& clientName, const Core::JSON::String& clientMac,
                     const Core::JSON::EnumType<Exchange::IMiracastPlayer::State>& playerState, const Core::JSON::String& reasonCode,
                     const Core::JSON::EnumType<Exchange::IMiracastPlayer::ReasonCode>& reasonDescription)
            {
                JsonData::MiracastPlayer::OnStateChangeParamsData _params_;
                _params_.ClientName = clientName;
                _params_.ClientMac = clientMac;
                _params_.PlayerState = playerState;
                _params_.ReasonCode = reasonCode;
                _params_.ReasonDescription = reasonDescription;

                OnStateChange(_module_, _params_);
            }

            // Event: 'onStateChange' - Notifies when a Miracast source device wants to connect
            static void OnStateChange(const JSONRPC& _module_, const string& clientName, const string& clientMac,
                     const Exchange::IMiracastPlayer::State& playerState, const string& reasonCode, const Exchange::IMiracastPlayer::ReasonCode& reasonDescription)
            {
                JsonData::MiracastPlayer::OnStateChangeParamsData _params_;
                _params_.ClientName = clientName;
                _params_.ClientMac = clientMac;
                _params_.PlayerState = playerState;
                _params_.ReasonCode = reasonCode;
                _params_.ReasonDescription = reasonDescription;

                OnStateChange(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JMiracastPlayer

} // namespace Exchange

} // namespace WPEFramework

