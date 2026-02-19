// C++ classes for TextTrackTtmlStyle API JSON-RPC API.
// Generated automatically from 'ITextTrack.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ITextTrack.h>

namespace WPEFramework {

namespace JsonData {

    namespace TextTrackTtmlStyle {

        // Common classes
        //

        class SetTtmlStyleOverridesParamsInfo : public Core::JSON::Container {
        public:
            SetTtmlStyleOverridesParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("style"), &Style);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetTtmlStyleOverridesParamsInfo(const SetTtmlStyleOverridesParamsInfo&) = delete;
            SetTtmlStyleOverridesParamsInfo& operator=(const SetTtmlStyleOverridesParamsInfo&) = delete;

        public:
            Core::JSON::String Style; // Contains the chosen override for styles
        }; // class SetTtmlStyleOverridesParamsInfo

        // Method params/result classes
        //

    } // namespace TextTrackTtmlStyle

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontFamily)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontSize)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontEdge)

}

