// C++ classes for TextTrack API JSON-RPC API.
// Generated automatically from 'ITextTrack.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ITextTrack.h>

namespace WPEFramework {

namespace JsonData {

    namespace TextTrack {

        // Common classes
        //

        class CloseSessionParamsInfo : public Core::JSON::Container {
        public:
            CloseSessionParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
            }

            bool IsValid() const
            {
                return (true);
            }

            CloseSessionParamsInfo(const CloseSessionParamsInfo&) = delete;
            CloseSessionParamsInfo& operator=(const CloseSessionParamsInfo&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // Is the session to close
        }; // class CloseSessionParamsInfo

        // Method params/result classes
        //

        class ApplyCustomTtmlStyleOverridesToSessionParamsData : public Core::JSON::Container {
        public:
            ApplyCustomTtmlStyleOverridesToSessionParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
                Add(_T("style"), &Style);
            }

            bool IsValid() const
            {
                return (true);
            }

            ApplyCustomTtmlStyleOverridesToSessionParamsData(const ApplyCustomTtmlStyleOverridesToSessionParamsData&) = delete;
            ApplyCustomTtmlStyleOverridesToSessionParamsData& operator=(const ApplyCustomTtmlStyleOverridesToSessionParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // Is the session as returned in the ITextTrack interface.
            Core::JSON::String Style; // Contains the list of styles to be overridden
        }; // class ApplyCustomTtmlStyleOverridesToSessionParamsData

        class AssociateVideoDecoderParamsData : public Core::JSON::Container {
        public:
            AssociateVideoDecoderParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
                Add(_T("handle"), &Handle);
            }

            bool IsValid() const
            {
                return (true);
            }

            AssociateVideoDecoderParamsData(const AssociateVideoDecoderParamsData&) = delete;
            AssociateVideoDecoderParamsData& operator=(const AssociateVideoDecoderParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // is the session
            Core::JSON::String Handle; // is a textual representation of the video decoder h
        }; // class AssociateVideoDecoderParamsData

        class OpenSessionParamsData : public Core::JSON::Container {
        public:
            OpenSessionParamsData()
                : Core::JSON::Container()
            {
                Add(_T("displayHandle"), &DisplayHandle);
            }

            bool IsValid() const
            {
                return (true);
            }

            OpenSessionParamsData(const OpenSessionParamsData&) = delete;
            OpenSessionParamsData& operator=(const OpenSessionParamsData&) = delete;

        public:
            Core::JSON::String DisplayHandle; // is an encoding of the wayland display name
        }; // class OpenSessionParamsData

        class SendSessionDataParamsData : public Core::JSON::Container {
        public:
            SendSessionDataParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
                Add(_T("type"), &Type);
                Add(_T("displayOffsetMs"), &DisplayOffsetMs);
                Add(_T("data"), &Data);
            }

            bool IsValid() const
            {
                return (true);
            }

            SendSessionDataParamsData(const SendSessionDataParamsData&) = delete;
            SendSessionDataParamsData& operator=(const SendSessionDataParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // Is the session
            Core::JSON::EnumType<Exchange::ITextTrack::DataType> Type; // Is the type of data
            Core::JSON::DecSInt64 DisplayOffsetMs; // Sends data of Closed Captions, Captions or Timed Text data to a render session.
            Core::JSON::String Data; // Sends data of Closed Captions, Captions or Timed Text data to a render session.
        }; // class SendSessionDataParamsData

        class SendSessionTimestampParamsData : public Core::JSON::Container {
        public:
            SendSessionTimestampParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
                Add(_T("mediaTimestampMs"), &MediaTimestampMs);
            }

            bool IsValid() const
            {
                return (true);
            }

            SendSessionTimestampParamsData(const SendSessionTimestampParamsData&) = delete;
            SendSessionTimestampParamsData& operator=(const SendSessionTimestampParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // Is the session
            Core::JSON::DecUInt64 MediaTimestampMs; // Is a timestamp
        }; // class SendSessionTimestampParamsData

        class SetPreviewTextParamsData : public Core::JSON::Container {
        public:
            SetPreviewTextParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
                Add(_T("text"), &Text);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPreviewTextParamsData(const SetPreviewTextParamsData&) = delete;
            SetPreviewTextParamsData& operator=(const SetPreviewTextParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // Sets a static text in the display for preview purposes.
            Core::JSON::String Text; // Is the text to display
        }; // class SetPreviewTextParamsData

        class SetSessionClosedCaptionsServiceParamsData : public Core::JSON::Container {
        public:
            SetSessionClosedCaptionsServiceParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
                Add(_T("service"), &Service);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetSessionClosedCaptionsServiceParamsData(const SetSessionClosedCaptionsServiceParamsData&) = delete;
            SetSessionClosedCaptionsServiceParamsData& operator=(const SetSessionClosedCaptionsServiceParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // Is the session
            Core::JSON::String Service; // Identifies the service to display e.g.
        }; // class SetSessionClosedCaptionsServiceParamsData

        class SetSessionDvbSubtitleSelectionParamsData : public Core::JSON::Container {
        public:
            SetSessionDvbSubtitleSelectionParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
                Add(_T("compositionPageId"), &CompositionPageId);
                Add(_T("ancillaryPageId"), &AncillaryPageId);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetSessionDvbSubtitleSelectionParamsData(const SetSessionDvbSubtitleSelectionParamsData&) = delete;
            SetSessionDvbSubtitleSelectionParamsData& operator=(const SetSessionDvbSubtitleSelectionParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // Is the session
            Core::JSON::DecUInt16 CompositionPageId; // Is the one Id
            Core::JSON::DecUInt16 AncillaryPageId; // Set the render session into Dvb Subtitle mode,
                    //  specifying the the page for presentation. (See ETSI EN 300 743)
        }; // class SetSessionDvbSubtitleSelectionParamsData

        class SetSessionTeletextSelectionParamsData : public Core::JSON::Container {
        public:
            SetSessionTeletextSelectionParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sessionId"), &SessionId);
                Add(_T("page"), &Page);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetSessionTeletextSelectionParamsData(const SetSessionTeletextSelectionParamsData&) = delete;
            SetSessionTeletextSelectionParamsData& operator=(const SetSessionTeletextSelectionParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 SessionId; // Is the session
            Core::JSON::DecUInt16 Page; // The user selected teletext caption page 100-899
        }; // class SetSessionTeletextSelectionParamsData

    } // namespace TextTrack

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontFamily)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontSize)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackClosedCaptionsStyle::FontEdge)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrackCapabilities::Capability)
ENUM_CONVERSION_HANDLER(Exchange::ITextTrack::DataType)

}

