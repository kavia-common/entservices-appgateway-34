// Generated automatically from 'ITextTrack.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_TextTrackTtmlStyle.h"
#include <interfaces/ITextTrack.h>

namespace WPEFramework {

namespace Exchange {

    namespace JTextTrackTtmlStyle {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ITextTrackTtmlStyle* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JTextTrackTtmlStyle"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setTtmlStyleOverrides' - Sets global TTML override style
            _module_.Register<JsonData::TextTrackTtmlStyle::SetTtmlStyleOverridesParamsInfo, void>(_T("setTtmlStyleOverrides"), 
                [_impl_](const JsonData::TextTrackTtmlStyle::SetTtmlStyleOverridesParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _style{params.Style};

                    _errorCode = _impl_->SetTtmlStyleOverrides(_style);

                    return (_errorCode);
                });

            // Method: 'getTtmlStyleOverrides' - Gets the global TTML style overrides
            _module_.Register<void, Core::JSON::String>(_T("getTtmlStyleOverrides"), 
                [_impl_](Core::JSON::String& style) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _style{};

                    _errorCode = _impl_->GetTtmlStyleOverrides(_style);

                    if (_errorCode == Core::ERROR_NONE) {
                        style = _style;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setTtmlStyleOverrides"));
            _module_.Unregister(_T("getTtmlStyleOverrides"));
        }

        namespace Event {

            // Event: 'onTtmlStyleOverridesChanged' - The TTML Style override settings has changed
            static void OnTtmlStyleOverridesChanged(const JSONRPC& _module_, const JsonData::TextTrackTtmlStyle::SetTtmlStyleOverridesParamsInfo& params)
            {
                _module_.Notify(_T("onTtmlStyleOverridesChanged"), params);
            }

            // Event: 'onTtmlStyleOverridesChanged' - The TTML Style override settings has changed
            static void OnTtmlStyleOverridesChanged(const JSONRPC& _module_, const Core::JSON::String& style)
            {
                JsonData::TextTrackTtmlStyle::SetTtmlStyleOverridesParamsInfo _params_;
                _params_.Style = style;

                OnTtmlStyleOverridesChanged(_module_, _params_);
            }

            // Event: 'onTtmlStyleOverridesChanged' - The TTML Style override settings has changed
            static void OnTtmlStyleOverridesChanged(const JSONRPC& _module_, const string& style)
            {
                JsonData::TextTrackTtmlStyle::SetTtmlStyleOverridesParamsInfo _params_;
                _params_.Style = style;

                OnTtmlStyleOverridesChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JTextTrackTtmlStyle

} // namespace Exchange

} // namespace WPEFramework

