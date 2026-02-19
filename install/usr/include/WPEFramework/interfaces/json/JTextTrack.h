// Generated automatically from 'ITextTrack.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_TextTrack.h"
#include <interfaces/ITextTrack.h>

namespace WPEFramework {

namespace Exchange {

    namespace JTextTrack {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 4;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ITextTrack* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JTextTrack"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'openSession' - Opens a new renderSession
            _module_.Register<JsonData::TextTrack::OpenSessionParamsData, Core::JSON::DecUInt32>(_T("openSession"), 
                [_impl_](const JsonData::TextTrack::OpenSessionParamsData& params, Core::JSON::DecUInt32& sessionId) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _displayHandle{params.DisplayHandle};
                    uint32_t _sessionId{};

                    _errorCode = _impl_->OpenSession(_displayHandle, _sessionId);

                    if (_errorCode == Core::ERROR_NONE) {
                        sessionId = _sessionId;
                    }

                    return (_errorCode);
                });

            // Method: 'closeSession' - Closes a previously opened render session
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("closeSession"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->CloseSession(_sessionId);

                    return (_errorCode);
                });

            // Method: 'resetSession' - Resets a previously opened render session back to its opened state
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("resetSession"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->ResetSession(_sessionId);

                    return (_errorCode);
                });

            // Method: 'pauseSession' - Pauses a render session
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("pauseSession"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->PauseSession(_sessionId);

                    return (_errorCode);
                });

            // Method: 'resumeSession' - Resumed a paused session
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("resumeSession"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->ResumeSession(_sessionId);

                    return (_errorCode);
                });

            // Method: 'muteSession' - Mute will hide rendering of Captions
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("muteSession"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->MuteSession(_sessionId);

                    return (_errorCode);
                });

            // Method: 'unMuteSession' - UnMute will unhide the rendering of Captions
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("unMuteSession"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->UnMuteSession(_sessionId);

                    return (_errorCode);
                });

            // Method: 'sendSessionData' - Sends data of Closed Captions, Captions or Timed Text data to a render session
            _module_.Register<JsonData::TextTrack::SendSessionDataParamsData, void>(_T("sendSessionData"), 
                [_impl_](const JsonData::TextTrack::SendSessionDataParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};
                    const Exchange::ITextTrack::DataType _type{params.Type};
                    const int64_t _displayOffsetMs{params.DisplayOffsetMs};
                    const string _data{params.Data};

                    _errorCode = _impl_->SendSessionData(_sessionId, _type, _displayOffsetMs, _data);

                    return (_errorCode);
                });

            // Method: 'sendSessionTimestamp' - Sends the current timestamp from a media player to a render session
            _module_.Register<JsonData::TextTrack::SendSessionTimestampParamsData, void>(_T("sendSessionTimestamp"), 
                [_impl_](const JsonData::TextTrack::SendSessionTimestampParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};
                    const uint64_t _mediaTimestampMs{params.MediaTimestampMs};

                    _errorCode = _impl_->SendSessionTimestamp(_sessionId, _mediaTimestampMs);

                    return (_errorCode);
                });

            // Method: 'setPreviewText' - Sets a static text in the display for preview purposes
            _module_.Register<JsonData::TextTrack::SetPreviewTextParamsData, void>(_T("setPreviewText"), 
                [_impl_](const JsonData::TextTrack::SetPreviewTextParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};
                    const string _text{params.Text};

                    _errorCode = _impl_->SetPreviewText(_sessionId, _text);

                    return (_errorCode);
                });

            // Method: 'setSessionClosedCaptionsService' - Sets the render session into CC mode
            _module_.Register<JsonData::TextTrack::SetSessionClosedCaptionsServiceParamsData, void>(_T("setSessionClosedCaptionsService"), 
                [_impl_](const JsonData::TextTrack::SetSessionClosedCaptionsServiceParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};
                    const string _service{params.Service};

                    _errorCode = _impl_->SetSessionClosedCaptionsService(_sessionId, _service);

                    return (_errorCode);
                });

            // Method: 'setSessionTeletextSelection' - Set the render session into Teletext mode, providing the teletext caption page for presentation
            _module_.Register<JsonData::TextTrack::SetSessionTeletextSelectionParamsData, void>(_T("setSessionTeletextSelection"), 
                [_impl_](const JsonData::TextTrack::SetSessionTeletextSelectionParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};
                    const uint16_t _page{params.Page};

                    _errorCode = _impl_->SetSessionTeletextSelection(_sessionId, _page);

                    return (_errorCode);
                });

            // Method: 'setSessionDvbSubtitleSelection' - Set the render session into Dvb Subtitle mode, specifying the the page for presentation
            _module_.Register<JsonData::TextTrack::SetSessionDvbSubtitleSelectionParamsData, void>(_T("setSessionDvbSubtitleSelection"), 
                [_impl_](const JsonData::TextTrack::SetSessionDvbSubtitleSelectionParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};
                    const uint16_t _compositionPageId{params.CompositionPageId};
                    const uint16_t _ancillaryPageId{params.AncillaryPageId};

                    _errorCode = _impl_->SetSessionDvbSubtitleSelection(_sessionId, _compositionPageId, _ancillaryPageId);

                    return (_errorCode);
                });

            // Method: 'setSessionWebVTTSelection' - Set the render session into WebVTT mode
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("setSessionWebVTTSelection"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->SetSessionWebVTTSelection(_sessionId);

                    return (_errorCode);
                });

            // Method: 'setSessionTTMLSelection' - Set the render session into TTML mode
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("setSessionTTMLSelection"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->SetSessionTTMLSelection(_sessionId);

                    return (_errorCode);
                });

            // Method: 'setSessionSCTESelection' - Set the render session into SCTE mode
            _module_.Register<JsonData::TextTrack::CloseSessionParamsInfo, void>(_T("setSessionSCTESelection"), 
                [_impl_](const JsonData::TextTrack::CloseSessionParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};

                    _errorCode = _impl_->SetSessionSCTESelection(_sessionId);

                    return (_errorCode);
                });

            // Method: 'applyCustomTtmlStyleOverridesToSession' - Applies a custom TTML styling with overrides that is applied on all elements
            _module_.Register<JsonData::TextTrack::ApplyCustomTtmlStyleOverridesToSessionParamsData, void>(_T("applyCustomTtmlStyleOverridesToSession"), 
                [_impl_](const JsonData::TextTrack::ApplyCustomTtmlStyleOverridesToSessionParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};
                    const string _style{params.Style};

                    _errorCode = _impl_->ApplyCustomTtmlStyleOverridesToSession(_sessionId, _style);

                    return (_errorCode);
                });

            // Method: 'associateVideoDecoder' - Associate a video decoder with the given session
            _module_.Register<JsonData::TextTrack::AssociateVideoDecoderParamsData, void>(_T("associateVideoDecoder"), 
                [_impl_](const JsonData::TextTrack::AssociateVideoDecoderParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _sessionId{params.SessionId};
                    const string _handle{params.Handle};

                    _errorCode = _impl_->AssociateVideoDecoder(_sessionId, _handle);

                    return (_errorCode);
                });

            // Method: 'getInterfaceVersion' - Return the interface version implemented
            _module_.Register<void, Core::JSON::DecUInt32>(_T("getInterfaceVersion"), 
                [_impl_](Core::JSON::DecUInt32& version) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    uint32_t _version{};

                    _errorCode = _impl_->GetInterfaceVersion(_version);

                    if (_errorCode == Core::ERROR_NONE) {
                        version = _version;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("openSession"));
            _module_.Unregister(_T("closeSession"));
            _module_.Unregister(_T("resetSession"));
            _module_.Unregister(_T("pauseSession"));
            _module_.Unregister(_T("resumeSession"));
            _module_.Unregister(_T("muteSession"));
            _module_.Unregister(_T("unMuteSession"));
            _module_.Unregister(_T("sendSessionData"));
            _module_.Unregister(_T("sendSessionTimestamp"));
            _module_.Unregister(_T("setPreviewText"));
            _module_.Unregister(_T("setSessionClosedCaptionsService"));
            _module_.Unregister(_T("setSessionTeletextSelection"));
            _module_.Unregister(_T("setSessionDvbSubtitleSelection"));
            _module_.Unregister(_T("setSessionWebVTTSelection"));
            _module_.Unregister(_T("setSessionTTMLSelection"));
            _module_.Unregister(_T("setSessionSCTESelection"));
            _module_.Unregister(_T("applyCustomTtmlStyleOverridesToSession"));
            _module_.Unregister(_T("associateVideoDecoder"));
            _module_.Unregister(_T("getInterfaceVersion"));
        }

        POP_WARNING()

    } // namespace JTextTrack

} // namespace Exchange

} // namespace WPEFramework

