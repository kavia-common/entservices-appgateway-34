// C++ classes for TextTrackClosedCaptionsStyle API JSON-RPC API.
// Generated automatically from 'ITextTrack.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ITextTrack.h>

namespace WPEFramework {

namespace JsonData {

    namespace TextTrackClosedCaptionsStyle {

        // Common classes
        //

        class ClosedCaptionsStyleInfo : public Core::JSON::Container {
        public:
            ClosedCaptionsStyleInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            ClosedCaptionsStyleInfo(const Exchange::ITextTrackClosedCaptionsStyle::ClosedCaptionsStyle& _other)
                : Core::JSON::Container()
            {
                FontFamily = _other.fontFamily;
                FontSize = _other.fontSize;
                FontColor = _other.fontColor;
                FontOpacity = _other.fontOpacity;
                FontEdge = _other.fontEdge;
                FontEdgeColor = _other.fontEdgeColor;
                BackgroundColor = _other.backgroundColor;
                BackgroundOpacity = _other.backgroundOpacity;
                WindowColor = _other.windowColor;
                WindowOpacity = _other.windowOpacity;
                _Init();
            }

            ClosedCaptionsStyleInfo& operator=(const Exchange::ITextTrackClosedCaptionsStyle::ClosedCaptionsStyle& _rhs)
            {
                FontFamily = _rhs.fontFamily;
                FontSize = _rhs.fontSize;
                FontColor = _rhs.fontColor;
                FontOpacity = _rhs.fontOpacity;
                FontEdge = _rhs.fontEdge;
                FontEdgeColor = _rhs.fontEdgeColor;
                BackgroundColor = _rhs.backgroundColor;
                BackgroundOpacity = _rhs.backgroundOpacity;
                WindowColor = _rhs.windowColor;
                WindowOpacity = _rhs.windowOpacity;
                return (*this);
            }

            operator Exchange::ITextTrackClosedCaptionsStyle::ClosedCaptionsStyle() const
            {
                Exchange::ITextTrackClosedCaptionsStyle::ClosedCaptionsStyle _value{};
                _value.fontFamily = FontFamily;
                _value.fontSize = FontSize;
                _value.fontColor = FontColor;
                _value.fontOpacity = FontOpacity;
                _value.fontEdge = FontEdge;
                _value.fontEdgeColor = FontEdgeColor;
                _value.backgroundColor = BackgroundColor;
                _value.backgroundOpacity = BackgroundOpacity;
                _value.windowColor = WindowColor;
                _value.windowOpacity = WindowOpacity;
                return (_value);
            }

            bool IsValid() const
            {
                return (((FontColor.Value().size() <= 7)) && ((FontOpacity >= -1) && (FontOpacity <= 100)) && ((FontEdgeColor.Value().size() <= 7)) && ((BackgroundColor.Value().size() <= 7)) && ((BackgroundOpacity >= -1) && (BackgroundOpacity <= 100)) && ((WindowColor.Value().size() <= 7)) && ((WindowOpacity >= -1) && (WindowOpacity <= 100)));
            }

        private:
            void _Init()
            {
                Add(_T("fontFamily"), &FontFamily);
                Add(_T("fontSize"), &FontSize);
                Add(_T("fontColor"), &FontColor);
                Add(_T("fontOpacity"), &FontOpacity);
                Add(_T("fontEdge"), &FontEdge);
                Add(_T("fontEdgeColor"), &FontEdgeColor);
                Add(_T("backgroundColor"), &BackgroundColor);
                Add(_T("backgroundOpacity"), &BackgroundOpacity);
                Add(_T("windowColor"), &WindowColor);
                Add(_T("windowOpacity"), &WindowOpacity);
            }

        public:
            Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontFamily> FontFamily; // Selected fontFamily
            Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontSize> FontSize; // Selected fontSize
            Core::JSON::String FontColor; // #rrggbb Empty string implies - use stream default
            Core::JSON::DecSInt8 FontOpacity; // 0-100% where 100% is solid and 0% is transparent. -1 implies - use stream default
            Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontEdge> FontEdge; // Selected fontEdge
            Core::JSON::String FontEdgeColor; // #rrggbb Empty string implies - use stream default
            Core::JSON::String BackgroundColor; // #rrggbb Empty string implies - use stream default
            Core::JSON::DecSInt8 BackgroundOpacity; // 0-100% where 100% is solid and 0% is transparent. -1 implies - use stream default
            Core::JSON::String WindowColor; // #rrggbb Empty string implies - use stream default
            Core::JSON::DecSInt8 WindowOpacity; // 0-100% where 100% is solid and 0% is transparent. -1 implies - use stream default
        }; // class ClosedCaptionsStyleInfo

        class SetClosedCaptionsStyleParamsInfo : public Core::JSON::Container {
        public:
            SetClosedCaptionsStyleParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("style"), &Style);
            }

            bool IsValid() const
            {
                return ((Style.IsValid()));
            }

            SetClosedCaptionsStyleParamsInfo(const SetClosedCaptionsStyleParamsInfo&) = delete;
            SetClosedCaptionsStyleParamsInfo& operator=(const SetClosedCaptionsStyleParamsInfo&) = delete;

        public:
            ClosedCaptionsStyleInfo Style; // Contains the chosen styles
        }; // class SetClosedCaptionsStyleParamsInfo

        class SetFontColorParamsInfo : public Core::JSON::Container {
        public:
            SetFontColorParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("color"), &Color);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetFontColorParamsInfo(const SetFontColorParamsInfo&) = delete;
            SetFontColorParamsInfo& operator=(const SetFontColorParamsInfo&) = delete;

        public:
            Core::JSON::String Color; // Setter for FontColor
        }; // class SetFontColorParamsInfo

        class SetFontEdgeParamsInfo : public Core::JSON::Container {
        public:
            SetFontEdgeParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("edge"), &Edge);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetFontEdgeParamsInfo(const SetFontEdgeParamsInfo&) = delete;
            SetFontEdgeParamsInfo& operator=(const SetFontEdgeParamsInfo&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontEdge> Edge; // Setter for FontEdge
        }; // class SetFontEdgeParamsInfo

        class SetFontFamilyParamsInfo : public Core::JSON::Container {
        public:
            SetFontFamilyParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("font"), &Font);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetFontFamilyParamsInfo(const SetFontFamilyParamsInfo&) = delete;
            SetFontFamilyParamsInfo& operator=(const SetFontFamilyParamsInfo&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontFamily> Font; // Setter for FontFamily
        }; // class SetFontFamilyParamsInfo

        class SetFontOpacityParamsInfo : public Core::JSON::Container {
        public:
            SetFontOpacityParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("opacity"), &Opacity);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetFontOpacityParamsInfo(const SetFontOpacityParamsInfo&) = delete;
            SetFontOpacityParamsInfo& operator=(const SetFontOpacityParamsInfo&) = delete;

        public:
            Core::JSON::DecSInt8 Opacity; // Setter for FontOpacity
        }; // class SetFontOpacityParamsInfo

        class SetFontSizeParamsInfo : public Core::JSON::Container {
        public:
            SetFontSizeParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("size"), &Size);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetFontSizeParamsInfo(const SetFontSizeParamsInfo&) = delete;
            SetFontSizeParamsInfo& operator=(const SetFontSizeParamsInfo&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ITextTrackClosedCaptionsStyle::FontSize> Size; // Setter for FontSize
        }; // class SetFontSizeParamsInfo

        // Method params/result classes
        //

    } // namespace TextTrackClosedCaptionsStyle

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontFamily)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontSize)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontEdge)

}

