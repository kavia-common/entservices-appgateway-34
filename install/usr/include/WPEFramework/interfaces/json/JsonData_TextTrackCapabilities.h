// C++ classes for TextTrackCapabilities API JSON-RPC API.
// Generated automatically from 'ITextTrack.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ITextTrack.h>

namespace WPEFramework {

namespace JsonData {

    namespace TextTrackCapabilities {

        // Method params/result classes
        //

        class GetCapabilityParamsData : public Core::JSON::Container {
        public:
            GetCapabilityParamsData()
                : Core::JSON::Container()
            {
                Add(_T("capability"), &Capability);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetCapabilityParamsData(const GetCapabilityParamsData&) = delete;
            GetCapabilityParamsData& operator=(const GetCapabilityParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ITextTrackCapabilities::Capability> Capability; // The capability to query ex: FIREBOLT_MIGRATION
        }; // class GetCapabilityParamsData

    } // namespace TextTrackCapabilities

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontFamily)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontSize)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontEdge)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackCapabilities::Capability)

}

