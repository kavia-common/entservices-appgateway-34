// Generated automatically from 'ILEDControl.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_LEDControl.h"
#include <interfaces/ILEDControl.h>

namespace WPEFramework {

namespace Exchange {

    namespace JLEDControl {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ILEDControl* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JLEDControl"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getSupportedLEDStates'
            _module_.Register<void, JsonData::LEDControl::GetSupportedLEDStatesResultData>(_T("getSupportedLEDStates"), 
                [_impl_](JsonData::LEDControl::GetSupportedLEDStatesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _supportedLEDStates{};
                    bool _success{};

                    _errorCode = _impl_->GetSupportedLEDStates(_supportedLEDStates, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_supportedLEDStates != nullptr) {
                            string _supportedLEDStatesItem_{};
                            while (_supportedLEDStates->Next(_supportedLEDStatesItem_) == true) { result.SupportedLEDStates.Add() = _supportedLEDStatesItem_; }
                            _supportedLEDStates->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getLEDState' - Retrieves current state of the LED
            _module_.Register<void, JsonData::LEDControl::LEDStateInfo>(_T("getLEDState"), 
                [_impl_](JsonData::LEDControl::LEDStateInfo& ledState) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::ILEDControl::LEDState _ledState{};

                    _errorCode = _impl_->GetLEDState(_ledState);

                    if (_errorCode == Core::ERROR_NONE) {
                        ledState = _ledState;
                    }

                    return (_errorCode);
                });

            // Method: 'setLEDState' - Sets the device LED to a requested state from those available in `GetSupportedLEDStates`
            _module_.Register<JsonData::LEDControl::LEDStateInfo, Core::JSON::Boolean>(_T("setLEDState"), 
                [_impl_](const JsonData::LEDControl::LEDStateInfo& params, Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ILEDControl::LEDControlState _state{params.State};
                    bool _success{};

                    _errorCode = _impl_->SetLEDState(_state, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getSupportedLEDStates"));
            _module_.Unregister(_T("getLEDState"));
            _module_.Unregister(_T("setLEDState"));
        }

        POP_WARNING()

    } // namespace JLEDControl

} // namespace Exchange

} // namespace WPEFramework

