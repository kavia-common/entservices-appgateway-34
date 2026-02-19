// Generated automatically from 'IFrontPanel.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_FrontPanel.h"
#include <interfaces/IFrontPanel.h>

namespace WPEFramework {

namespace Exchange {

    namespace JFrontPanel {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IFrontPanel* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JFrontPanel"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getBrightness' - Gets the status of the Front Panel
            _module_.Register<JsonData::FrontPanel::GetBrightnessParamsInfo, JsonData::FrontPanel::GetBrightnessResultData>(_T("getBrightness"), 
                [_impl_](const JsonData::FrontPanel::GetBrightnessParamsInfo& params, JsonData::FrontPanel::GetBrightnessResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _index{params.Index};
                    uint32_t _brightness{};
                    bool _success{};

                    _errorCode = _impl_->GetBrightness(_index, _brightness, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Brightness = _brightness;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getFrontPanelLights' - Gets the front panel lights
            _module_.Register<void, JsonData::FrontPanel::GetFrontPanelLightsResultData>(_T("getFrontPanelLights"), 
                [_impl_](JsonData::FrontPanel::GetFrontPanelLightsResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<string, ID_FRONT_PANEL_LIGHTS_LIST_ITERATOR>* _supportedLights{};
                    string _supportedLightsInfo{};
                    bool _success{};

                    _errorCode = _impl_->GetFrontPanelLights(_supportedLights, _supportedLightsInfo, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_supportedLights != nullptr) {
                            string _supportedLightsItem_{};
                            while (_supportedLights->Next(_supportedLightsItem_) == true) { result.SupportedLights.Add() = _supportedLightsItem_; }
                            _supportedLights->Release();
                        }
                        result.SupportedLightsInfo = _supportedLightsInfo;
                        result.SupportedLightsInfo.SetQuoted(false);
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'powerLedOff' - Switches the specified LED off
            _module_.Register<JsonData::FrontPanel::GetBrightnessParamsInfo, JsonData::FrontPanel::FrontPanelSuccessInfo>(_T("powerLedOff"), 
                [_impl_](const JsonData::FrontPanel::GetBrightnessParamsInfo& params, JsonData::FrontPanel::FrontPanelSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _index{params.Index};
                    Exchange::IFrontPanel::FrontPanelSuccess _success{};

                    _errorCode = _impl_->PowerLedOff(_index, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'powerLedOn' - Switches the specified LED on
            _module_.Register<JsonData::FrontPanel::GetBrightnessParamsInfo, JsonData::FrontPanel::FrontPanelSuccessInfo>(_T("powerLedOn"), 
                [_impl_](const JsonData::FrontPanel::GetBrightnessParamsInfo& params, JsonData::FrontPanel::FrontPanelSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _index{params.Index};
                    Exchange::IFrontPanel::FrontPanelSuccess _success{};

                    _errorCode = _impl_->PowerLedOn(_index, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setBlink' - Sets a blink pattern for the specified LED
            _module_.Register<JsonData::FrontPanel::SetBlinkParamsData, JsonData::FrontPanel::FrontPanelSuccessInfo>(_T("setBlink"), 
                [_impl_](const JsonData::FrontPanel::SetBlinkParamsData& params, JsonData::FrontPanel::FrontPanelSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _blinkInfo{params.BlinkInfo};
                    Exchange::IFrontPanel::FrontPanelSuccess _success{};

                    _errorCode = _impl_->SetBlink(_blinkInfo, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setBrightness' - Sets the brightness of the specified LED
            _module_.Register<JsonData::FrontPanel::SetBrightnessParamsData, JsonData::FrontPanel::FrontPanelSuccessInfo>(_T("setBrightness"), 
                [_impl_](const JsonData::FrontPanel::SetBrightnessParamsData& params, JsonData::FrontPanel::FrontPanelSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _index{params.Index};
                    const uint32_t _brightness{params.Brightness};
                    Exchange::IFrontPanel::FrontPanelSuccess _success{};

                    _errorCode = _impl_->SetBrightness(_index, _brightness, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setLED' - Sets the LED with the specified color and brightness
            _module_.Register<JsonData::FrontPanel::SetLEDParamsData, JsonData::FrontPanel::FrontPanelSuccessInfo>(_T("setLED"), 
                [_impl_](const JsonData::FrontPanel::SetLEDParamsData& params, JsonData::FrontPanel::FrontPanelSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _ledIndicator{params.LedIndicator};
                    const uint32_t _brightness{params.Brightness};
                    const string _color{params.Color};
                    const uint32_t _red{params.Red};
                    const uint32_t _green{params.Green};
                    const uint32_t _blue{params.Blue};
                    Exchange::IFrontPanel::FrontPanelSuccess _success{};

                    _errorCode = _impl_->SetLED(_ledIndicator, _brightness, _color, _red, _green, _blue, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getBrightness"));
            _module_.Unregister(_T("getFrontPanelLights"));
            _module_.Unregister(_T("powerLedOff"));
            _module_.Unregister(_T("powerLedOn"));
            _module_.Unregister(_T("setBlink"));
            _module_.Unregister(_T("setBrightness"));
            _module_.Unregister(_T("setLED"));
        }

        POP_WARNING()

    } // namespace JFrontPanel

} // namespace Exchange

} // namespace WPEFramework

