// Generated automatically from 'ITextTrack.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_TextTrackClosedCaptionsStyle.h"
#include <interfaces/ITextTrack.h>

namespace WPEFramework {

namespace Exchange {

    namespace JTextTrackClosedCaptionsStyle {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ITextTrackClosedCaptionsStyle* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JTextTrackClosedCaptionsStyle"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setClosedCaptionsStyle' - Sets the ClosedCaptionsStyle
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetClosedCaptionsStyleParamsInfo, void>(_T("setClosedCaptionsStyle"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetClosedCaptionsStyleParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    if ((params.IsValid() == false)) {
                        _errorCode = Core::ERROR_INVALID_RANGE;
                    }

                    if (_errorCode == Core::ERROR_NONE) {
                        const Exchange::ITextTrackClosedCaptionsStyle::ClosedCaptionsStyle _style(params.Style);

                        _errorCode = _impl_->SetClosedCaptionsStyle(_style);

                    }
                    return (_errorCode);
                });

            // Method: 'getClosedCaptionsStyle' - Gets the current ClosedCaptionsStyle settings
            _module_.Register<void, JsonData::TextTrackClosedCaptionsStyle::ClosedCaptionsStyleInfo>(_T("getClosedCaptionsStyle"), 
                [_impl_](JsonData::TextTrackClosedCaptionsStyle::ClosedCaptionsStyleInfo& style) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::ITextTrackClosedCaptionsStyle::ClosedCaptionsStyle _style{};

                    _errorCode = _impl_->GetClosedCaptionsStyle(_style);

                    if (_errorCode == Core::ERROR_NONE) {
                        style = _style;
                    }

                    return (_errorCode);
                });

            // Method: 'setFontFamily' - Setter for FontFamily
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontFamilyParamsInfo, void>(_T("setFontFamily"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontFamilyParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ITextTrackClosedCaptionsStyle::FontFamily _font{params.Font};

                    _errorCode = _impl_->SetFontFamily(_font);

                    return (_errorCode);
                });

            // Method: 'getFontFamily' - Getter for FontFamily
            _module_.Register<void, Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontFamily>>(_T("getFontFamily"), 
                [_impl_](Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontFamily>& font) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::ITextTrackClosedCaptionsStyle::FontFamily _font{};

                    _errorCode = _impl_->GetFontFamily(_font);

                    if (_errorCode == Core::ERROR_NONE) {
                        font = _font;
                    }

                    return (_errorCode);
                });

            // Method: 'setFontSize' - Setter for FontSize
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontSizeParamsInfo, void>(_T("setFontSize"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontSizeParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ITextTrackClosedCaptionsStyle::FontSize _size{params.Size};

                    _errorCode = _impl_->SetFontSize(_size);

                    return (_errorCode);
                });

            // Method: 'getFontSize' - Getter for FontSize
            _module_.Register<void, Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontSize>>(_T("getFontSize"), 
                [_impl_](Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontSize>& size) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::ITextTrackClosedCaptionsStyle::FontSize _size{};

                    _errorCode = _impl_->GetFontSize(_size);

                    if (_errorCode == Core::ERROR_NONE) {
                        size = _size;
                    }

                    return (_errorCode);
                });

            // Method: 'setFontColor' - Setter for FontColor
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo, void>(_T("setFontColor"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _color{params.Color};

                    _errorCode = _impl_->SetFontColor(_color);

                    return (_errorCode);
                });

            // Method: 'getFontColor' - Getter for FontColor
            _module_.Register<void, Core::JSON::String>(_T("getFontColor"), 
                [_impl_](Core::JSON::String& color) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _color{};

                    _errorCode = _impl_->GetFontColor(_color);

                    if (_errorCode == Core::ERROR_NONE) {
                        color = _color;
                    }

                    return (_errorCode);
                });

            // Method: 'setFontOpacity' - Setter for FontOpacity
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo, void>(_T("setFontOpacity"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int8_t _opacity{params.Opacity};

                    _errorCode = _impl_->SetFontOpacity(_opacity);

                    return (_errorCode);
                });

            // Method: 'getFontOpacity' - Getter for FontOpacity
            _module_.Register<void, Core::JSON::DecSInt8>(_T("getFontOpacity"), 
                [_impl_](Core::JSON::DecSInt8& opacity) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    int8_t _opacity{};

                    _errorCode = _impl_->GetFontOpacity(_opacity);

                    if (_errorCode == Core::ERROR_NONE) {
                        opacity = _opacity;
                    }

                    return (_errorCode);
                });

            // Method: 'setFontEdge' - Setter for FontEdge
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontEdgeParamsInfo, void>(_T("setFontEdge"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontEdgeParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ITextTrackClosedCaptionsStyle::FontEdge _edge{params.Edge};

                    _errorCode = _impl_->SetFontEdge(_edge);

                    return (_errorCode);
                });

            // Method: 'getFontEdge' - Getter for FontEdge
            _module_.Register<void, Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontEdge>>(_T("getFontEdge"), 
                [_impl_](Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontEdge>& edge) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::ITextTrackClosedCaptionsStyle::FontEdge _edge{};

                    _errorCode = _impl_->GetFontEdge(_edge);

                    if (_errorCode == Core::ERROR_NONE) {
                        edge = _edge;
                    }

                    return (_errorCode);
                });

            // Method: 'setFontEdgeColor' - Setter for FontEdgeColor
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo, void>(_T("setFontEdgeColor"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _color{params.Color};

                    _errorCode = _impl_->SetFontEdgeColor(_color);

                    return (_errorCode);
                });

            // Method: 'getFontEdgeColor' - Getter for FontEdgeColor
            _module_.Register<void, Core::JSON::String>(_T("getFontEdgeColor"), 
                [_impl_](Core::JSON::String& color) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _color{};

                    _errorCode = _impl_->GetFontEdgeColor(_color);

                    if (_errorCode == Core::ERROR_NONE) {
                        color = _color;
                    }

                    return (_errorCode);
                });

            // Method: 'setBackgroundColor' - Setter for BackgroundColor
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo, void>(_T("setBackgroundColor"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _color{params.Color};

                    _errorCode = _impl_->SetBackgroundColor(_color);

                    return (_errorCode);
                });

            // Method: 'getBackgroundColor' - Getter for BackgroundColor
            _module_.Register<void, Core::JSON::String>(_T("getBackgroundColor"), 
                [_impl_](Core::JSON::String& color) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _color{};

                    _errorCode = _impl_->GetBackgroundColor(_color);

                    if (_errorCode == Core::ERROR_NONE) {
                        color = _color;
                    }

                    return (_errorCode);
                });

            // Method: 'setBackgroundOpacity' - Setter for BackgroundOpacity
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo, void>(_T("setBackgroundOpacity"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int8_t _opacity{params.Opacity};

                    _errorCode = _impl_->SetBackgroundOpacity(_opacity);

                    return (_errorCode);
                });

            // Method: 'getBackgroundOpacity' - Getter for BackgroundOpacity
            _module_.Register<void, Core::JSON::DecSInt8>(_T("getBackgroundOpacity"), 
                [_impl_](Core::JSON::DecSInt8& opacity) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    int8_t _opacity{};

                    _errorCode = _impl_->GetBackgroundOpacity(_opacity);

                    if (_errorCode == Core::ERROR_NONE) {
                        opacity = _opacity;
                    }

                    return (_errorCode);
                });

            // Method: 'setWindowColor' - Setter for WindowColor
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo, void>(_T("setWindowColor"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _color{params.Color};

                    _errorCode = _impl_->SetWindowColor(_color);

                    return (_errorCode);
                });

            // Method: 'getWindowColor' - Getter for WindowColor
            _module_.Register<void, Core::JSON::String>(_T("getWindowColor"), 
                [_impl_](Core::JSON::String& color) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _color{};

                    _errorCode = _impl_->GetWindowColor(_color);

                    if (_errorCode == Core::ERROR_NONE) {
                        color = _color;
                    }

                    return (_errorCode);
                });

            // Method: 'setWindowOpacity' - Setter for WindowOpacity
            _module_.Register<JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo, void>(_T("setWindowOpacity"), 
                [_impl_](const JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int8_t _opacity{params.Opacity};

                    _errorCode = _impl_->SetWindowOpacity(_opacity);

                    return (_errorCode);
                });

            // Method: 'getWindowOpacity' - Getter for WindowOpacity
            _module_.Register<void, Core::JSON::DecSInt8>(_T("getWindowOpacity"), 
                [_impl_](Core::JSON::DecSInt8& opacity) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    int8_t _opacity{};

                    _errorCode = _impl_->GetWindowOpacity(_opacity);

                    if (_errorCode == Core::ERROR_NONE) {
                        opacity = _opacity;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setClosedCaptionsStyle"));
            _module_.Unregister(_T("getClosedCaptionsStyle"));
            _module_.Unregister(_T("setFontFamily"));
            _module_.Unregister(_T("getFontFamily"));
            _module_.Unregister(_T("setFontSize"));
            _module_.Unregister(_T("getFontSize"));
            _module_.Unregister(_T("setFontColor"));
            _module_.Unregister(_T("getFontColor"));
            _module_.Unregister(_T("setFontOpacity"));
            _module_.Unregister(_T("getFontOpacity"));
            _module_.Unregister(_T("setFontEdge"));
            _module_.Unregister(_T("getFontEdge"));
            _module_.Unregister(_T("setFontEdgeColor"));
            _module_.Unregister(_T("getFontEdgeColor"));
            _module_.Unregister(_T("setBackgroundColor"));
            _module_.Unregister(_T("getBackgroundColor"));
            _module_.Unregister(_T("setBackgroundOpacity"));
            _module_.Unregister(_T("getBackgroundOpacity"));
            _module_.Unregister(_T("setWindowColor"));
            _module_.Unregister(_T("getWindowColor"));
            _module_.Unregister(_T("setWindowOpacity"));
            _module_.Unregister(_T("getWindowOpacity"));
        }

        namespace Event {

            // Event: 'onClosedCaptionsStyleChanged' - The ClosedCaptionsStyle settings has changed
            static void OnClosedCaptionsStyleChanged(const JSONRPC& _module_,
                     const JsonData::TextTrackClosedCaptionsStyle::SetClosedCaptionsStyleParamsInfo& params)
            {
                _module_.Notify(_T("onClosedCaptionsStyleChanged"), params);
            }

            // Event: 'onClosedCaptionsStyleChanged' - The ClosedCaptionsStyle settings has changed
            static void OnClosedCaptionsStyleChanged(const JSONRPC& _module_, const Exchange::ITextTrackClosedCaptionsStyle::ClosedCaptionsStyle& style)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetClosedCaptionsStyleParamsInfo _params_;
                _params_.Style = style;

                OnClosedCaptionsStyleChanged(_module_, _params_);
            }

            // Event: 'onFontFamilyChanged' - Notify fontFamily Changed
            static void OnFontFamilyChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontFamilyParamsInfo& params)
            {
                _module_.Notify(_T("onFontFamilyChanged"), params);
            }

            // Event: 'onFontFamilyChanged' - Notify fontFamily Changed
            static void OnFontFamilyChanged(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontFamily>& font)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontFamilyParamsInfo _params_;
                _params_.Font = font;

                OnFontFamilyChanged(_module_, _params_);
            }

            // Event: 'onFontFamilyChanged' - Notify fontFamily Changed
            static void OnFontFamilyChanged(const JSONRPC& _module_, const Exchange::ITextTrackClosedCaptionsStyle::FontFamily& font)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontFamilyParamsInfo _params_;
                _params_.Font = font;

                OnFontFamilyChanged(_module_, _params_);
            }

            // Event: 'onFontSizeChanged' - Notify fontSize Changed
            static void OnFontSizeChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontSizeParamsInfo& params)
            {
                _module_.Notify(_T("onFontSizeChanged"), params);
            }

            // Event: 'onFontSizeChanged' - Notify fontSize Changed
            static void OnFontSizeChanged(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontSize>& size)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontSizeParamsInfo _params_;
                _params_.Size = size;

                OnFontSizeChanged(_module_, _params_);
            }

            // Event: 'onFontSizeChanged' - Notify fontSize Changed
            static void OnFontSizeChanged(const JSONRPC& _module_, const Exchange::ITextTrackClosedCaptionsStyle::FontSize& size)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontSizeParamsInfo _params_;
                _params_.Size = size;

                OnFontSizeChanged(_module_, _params_);
            }

            // Event: 'onFontColorChanged' - Notify fontColor Changed
            static void OnFontColorChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo& params)
            {
                _module_.Notify(_T("onFontColorChanged"), params);
            }

            // Event: 'onFontColorChanged' - Notify fontColor Changed
            static void OnFontColorChanged(const JSONRPC& _module_, const Core::JSON::String& color)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo _params_;
                _params_.Color = color;

                OnFontColorChanged(_module_, _params_);
            }

            // Event: 'onFontColorChanged' - Notify fontColor Changed
            static void OnFontColorChanged(const JSONRPC& _module_, const string& color)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo _params_;
                _params_.Color = color;

                OnFontColorChanged(_module_, _params_);
            }

            // Event: 'onFontOpacityChanged' - Notify fontOpacity Changed
            static void OnFontOpacityChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo& params)
            {
                _module_.Notify(_T("onFontOpacityChanged"), params);
            }

            // Event: 'onFontOpacityChanged' - Notify fontOpacity Changed
            static void OnFontOpacityChanged(const JSONRPC& _module_, const Core::JSON::DecSInt8& opacity)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo _params_;
                _params_.Opacity = opacity;

                OnFontOpacityChanged(_module_, _params_);
            }

            // Event: 'onFontOpacityChanged' - Notify fontOpacity Changed
            static void OnFontOpacityChanged(const JSONRPC& _module_, const int8_t& opacity)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo _params_;
                _params_.Opacity = opacity;

                OnFontOpacityChanged(_module_, _params_);
            }

            // Event: 'onFontEdgeChanged' - Notify fontEdge Changed
            static void OnFontEdgeChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontEdgeParamsInfo& params)
            {
                _module_.Notify(_T("onFontEdgeChanged"), params);
            }

            // Event: 'onFontEdgeChanged' - Notify fontEdge Changed
            static void OnFontEdgeChanged(const JSONRPC& _module_, const Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontEdge>& edge)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontEdgeParamsInfo _params_;
                _params_.Edge = edge;

                OnFontEdgeChanged(_module_, _params_);
            }

            // Event: 'onFontEdgeChanged' - Notify fontEdge Changed
            static void OnFontEdgeChanged(const JSONRPC& _module_, const Exchange::ITextTrackClosedCaptionsStyle::FontEdge& edge)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontEdgeParamsInfo _params_;
                _params_.Edge = edge;

                OnFontEdgeChanged(_module_, _params_);
            }

            // Event: 'onFontEdgeColorChanged' - Notify fontEdgeColor Changed
            static void OnFontEdgeColorChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo& params)
            {
                _module_.Notify(_T("onFontEdgeColorChanged"), params);
            }

            // Event: 'onFontEdgeColorChanged' - Notify fontEdgeColor Changed
            static void OnFontEdgeColorChanged(const JSONRPC& _module_, const Core::JSON::String& color)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo _params_;
                _params_.Color = color;

                OnFontEdgeColorChanged(_module_, _params_);
            }

            // Event: 'onFontEdgeColorChanged' - Notify fontEdgeColor Changed
            static void OnFontEdgeColorChanged(const JSONRPC& _module_, const string& color)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo _params_;
                _params_.Color = color;

                OnFontEdgeColorChanged(_module_, _params_);
            }

            // Event: 'onBackgroundColorChanged' - Notify backgroundColor Changed
            static void OnBackgroundColorChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo& params)
            {
                _module_.Notify(_T("onBackgroundColorChanged"), params);
            }

            // Event: 'onBackgroundColorChanged' - Notify backgroundColor Changed
            static void OnBackgroundColorChanged(const JSONRPC& _module_, const Core::JSON::String& color)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo _params_;
                _params_.Color = color;

                OnBackgroundColorChanged(_module_, _params_);
            }

            // Event: 'onBackgroundColorChanged' - Notify backgroundColor Changed
            static void OnBackgroundColorChanged(const JSONRPC& _module_, const string& color)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo _params_;
                _params_.Color = color;

                OnBackgroundColorChanged(_module_, _params_);
            }

            // Event: 'onBackgroundOpacityChanged' - Notify backgroundOpacity Changed
            static void OnBackgroundOpacityChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo& params)
            {
                _module_.Notify(_T("onBackgroundOpacityChanged"), params);
            }

            // Event: 'onBackgroundOpacityChanged' - Notify backgroundOpacity Changed
            static void OnBackgroundOpacityChanged(const JSONRPC& _module_, const Core::JSON::DecSInt8& opacity)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo _params_;
                _params_.Opacity = opacity;

                OnBackgroundOpacityChanged(_module_, _params_);
            }

            // Event: 'onBackgroundOpacityChanged' - Notify backgroundOpacity Changed
            static void OnBackgroundOpacityChanged(const JSONRPC& _module_, const int8_t& opacity)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo _params_;
                _params_.Opacity = opacity;

                OnBackgroundOpacityChanged(_module_, _params_);
            }

            // Event: 'onWindowColorChanged' - Notify windowColor Changed
            static void OnWindowColorChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo& params)
            {
                _module_.Notify(_T("onWindowColorChanged"), params);
            }

            // Event: 'onWindowColorChanged' - Notify windowColor Changed
            static void OnWindowColorChanged(const JSONRPC& _module_, const Core::JSON::String& color)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo _params_;
                _params_.Color = color;

                OnWindowColorChanged(_module_, _params_);
            }

            // Event: 'onWindowColorChanged' - Notify windowColor Changed
            static void OnWindowColorChanged(const JSONRPC& _module_, const string& color)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontColorParamsInfo _params_;
                _params_.Color = color;

                OnWindowColorChanged(_module_, _params_);
            }

            // Event: 'onWindowOpacityChanged' - Notify windowOpacity Changed
            static void OnWindowOpacityChanged(const JSONRPC& _module_, const JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo& params)
            {
                _module_.Notify(_T("onWindowOpacityChanged"), params);
            }

            // Event: 'onWindowOpacityChanged' - Notify windowOpacity Changed
            static void OnWindowOpacityChanged(const JSONRPC& _module_, const Core::JSON::DecSInt8& opacity)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo _params_;
                _params_.Opacity = opacity;

                OnWindowOpacityChanged(_module_, _params_);
            }

            // Event: 'onWindowOpacityChanged' - Notify windowOpacity Changed
            static void OnWindowOpacityChanged(const JSONRPC& _module_, const int8_t& opacity)
            {
                JsonData::TextTrackClosedCaptionsStyle::SetFontOpacityParamsInfo _params_;
                _params_.Opacity = opacity;

                OnWindowOpacityChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JTextTrackClosedCaptionsStyle

} // namespace Exchange

} // namespace WPEFramework

