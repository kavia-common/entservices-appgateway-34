// Generated automatically from 'IFrameRate.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_FrameRate.h"
#include <interfaces/IFrameRate.h>

namespace WPEFramework {

namespace Exchange {

    namespace JFrameRate {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IFrameRate* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JFrameRate"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getDisplayFrameRate' - Gets the current display frame rate values
            _module_.Register<void, JsonData::FrameRate::GetDisplayFrameRateResultData>(_T("getDisplayFrameRate"), 
                [_impl_](JsonData::FrameRate::GetDisplayFrameRateResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _framerate{};
                    bool _success{};

                    _errorCode = _impl_->GetDisplayFrameRate(_framerate, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Framerate = _framerate;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getFrmMode' - Gets the current auto framerate mode
            _module_.Register<void, JsonData::FrameRate::GetFrmModeResultData>(_T("getFrmMode"), 
                [_impl_](JsonData::FrameRate::GetFrmModeResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    int32_t _framerateMode{};
                    bool _success{};

                    _errorCode = _impl_->GetFrmMode(_framerateMode, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.FramerateMode = _framerateMode;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setCollectionFrequency' - Sets the FPS data collection interval
            _module_.Register<JsonData::FrameRate::SetCollectionFrequencyParamsData, Core::JSON::Boolean>(_T("setCollectionFrequency"), 
                [_impl_](const JsonData::FrameRate::SetCollectionFrequencyParamsData& params, Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _frequency{params.Frequency};
                    bool _success{};

                    _errorCode = _impl_->SetCollectionFrequency(_frequency, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setDisplayFrameRate' - Sets the display framerate values
            _module_.Register<JsonData::FrameRate::SetDisplayFrameRateParamsData, Core::JSON::Boolean>(_T("setDisplayFrameRate"), 
                [_impl_](const JsonData::FrameRate::SetDisplayFrameRateParamsData& params, Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _framerate{params.Framerate};
                    bool _success{};

                    _errorCode = _impl_->SetDisplayFrameRate(_framerate, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setFrmMode' - Set the Frm mode
            _module_.Register<JsonData::FrameRate::SetFrmModeParamsData, Core::JSON::Boolean>(_T("setFrmMode"), 
                [_impl_](const JsonData::FrameRate::SetFrmModeParamsData& params, Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _frmmode{params.Frmmode};
                    bool _success{};

                    _errorCode = _impl_->SetFrmMode(_frmmode, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'startFpsCollection' - Starts the FPS data collection
            _module_.Register<void, Core::JSON::Boolean>(_T("startFpsCollection"), 
                [_impl_](Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _success{};

                    _errorCode = _impl_->StartFpsCollection(_success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'stopFpsCollection' - Stops the FPS data collection
            _module_.Register<void, Core::JSON::Boolean>(_T("stopFpsCollection"), 
                [_impl_](Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _success{};

                    _errorCode = _impl_->StopFpsCollection(_success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'updateFps' - Update the FPS value
            _module_.Register<JsonData::FrameRate::UpdateFpsParamsData, Core::JSON::Boolean>(_T("updateFps"), 
                [_impl_](const JsonData::FrameRate::UpdateFpsParamsData& params, Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _newFpsValue{params.NewFpsValue};
                    bool _success{};

                    _errorCode = _impl_->UpdateFps(_newFpsValue, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getDisplayFrameRate"));
            _module_.Unregister(_T("getFrmMode"));
            _module_.Unregister(_T("setCollectionFrequency"));
            _module_.Unregister(_T("setDisplayFrameRate"));
            _module_.Unregister(_T("setFrmMode"));
            _module_.Unregister(_T("startFpsCollection"));
            _module_.Unregister(_T("stopFpsCollection"));
            _module_.Unregister(_T("updateFps"));
        }

        namespace Event {

            // Event: 'onFpsEvent' - Triggered by callback from FrameRate after onFpsEvent
            static void OnFpsEvent(const JSONRPC& _module_, const JsonData::FrameRate::OnFpsEventParamsData& params)
            {
                _module_.Notify(_T("onFpsEvent"), params);
            }

            // Event: 'onFpsEvent' - Triggered by callback from FrameRate after onFpsEvent
            static void OnFpsEvent(const JSONRPC& _module_, const Core::JSON::DecSInt32& average, const Core::JSON::DecSInt32& min,
                     const Core::JSON::DecSInt32& max)
            {
                JsonData::FrameRate::OnFpsEventParamsData _params_;
                _params_.Average = average;
                _params_.Min = min;
                _params_.Max = max;

                OnFpsEvent(_module_, _params_);
            }

            // Event: 'onFpsEvent' - Triggered by callback from FrameRate after onFpsEvent
            static void OnFpsEvent(const JSONRPC& _module_, const int32_t& average, const int32_t& min, const int32_t& max)
            {
                JsonData::FrameRate::OnFpsEventParamsData _params_;
                _params_.Average = average;
                _params_.Min = min;
                _params_.Max = max;

                OnFpsEvent(_module_, _params_);
            }

            // Event: 'onDisplayFrameRateChanging' - Triggered when the framerate changes started
            static void OnDisplayFrameRateChanging(const JSONRPC& _module_, const JsonData::FrameRate::OnDisplayFrameRateChangingParamsInfo& params)
            {
                _module_.Notify(_T("onDisplayFrameRateChanging"), params);
            }

            // Event: 'onDisplayFrameRateChanging' - Triggered when the framerate changes started
            static void OnDisplayFrameRateChanging(const JSONRPC& _module_, const Core::JSON::String& displayFrameRate)
            {
                JsonData::FrameRate::OnDisplayFrameRateChangingParamsInfo _params_;
                _params_.DisplayFrameRate = displayFrameRate;

                OnDisplayFrameRateChanging(_module_, _params_);
            }

            // Event: 'onDisplayFrameRateChanging' - Triggered when the framerate changes started
            static void OnDisplayFrameRateChanging(const JSONRPC& _module_, const string& displayFrameRate)
            {
                JsonData::FrameRate::OnDisplayFrameRateChangingParamsInfo _params_;
                _params_.DisplayFrameRate = displayFrameRate;

                OnDisplayFrameRateChanging(_module_, _params_);
            }

            // Event: 'onDisplayFrameRateChanged' - Triggered when the framerate changed
            static void OnDisplayFrameRateChanged(const JSONRPC& _module_, const JsonData::FrameRate::OnDisplayFrameRateChangingParamsInfo& params)
            {
                _module_.Notify(_T("onDisplayFrameRateChanged"), params);
            }

            // Event: 'onDisplayFrameRateChanged' - Triggered when the framerate changed
            static void OnDisplayFrameRateChanged(const JSONRPC& _module_, const Core::JSON::String& displayFrameRate)
            {
                JsonData::FrameRate::OnDisplayFrameRateChangingParamsInfo _params_;
                _params_.DisplayFrameRate = displayFrameRate;

                OnDisplayFrameRateChanged(_module_, _params_);
            }

            // Event: 'onDisplayFrameRateChanged' - Triggered when the framerate changed
            static void OnDisplayFrameRateChanged(const JSONRPC& _module_, const string& displayFrameRate)
            {
                JsonData::FrameRate::OnDisplayFrameRateChangingParamsInfo _params_;
                _params_.DisplayFrameRate = displayFrameRate;

                OnDisplayFrameRateChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JFrameRate

} // namespace Exchange

} // namespace WPEFramework

