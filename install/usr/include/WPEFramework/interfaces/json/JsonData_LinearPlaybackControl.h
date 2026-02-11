// C++ classes for Linear Playback Control API JSON-RPC API.
// Generated automatically from 'LinearPlaybackControl.json'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>

namespace WPEFramework {

namespace JsonData {

    namespace LinearPlaybackControl {

        // Method params/result classes
        //

        class ChannelData : public Core::JSON::Container {
        public:
            ChannelData()
                : Core::JSON::Container()
            {
                Add(_T("channel"), &Channel);
            }

            bool IsValid() const
            {
                return (true);
            }

            ChannelData(const ChannelData&) = delete;
            ChannelData& operator=(const ChannelData&) = delete;

        public:
            Core::JSON::String Channel; // Channel address.
        }; // class ChannelData

        class SeekData : public Core::JSON::Container {
        public:
            SeekData()
                : Core::JSON::Container()
            {
                Add(_T("seekPosInSeconds"), &SeekPosInSeconds);
            }

            bool IsValid() const
            {
                return (true);
            }

            SeekData(const SeekData&) = delete;
            SeekData& operator=(const SeekData&) = delete;

        public:
            Core::JSON::DecUInt64 SeekPosInSeconds; // TSB seek position offset from live in seconds. The value must be an unsigned integer. If the value exceeds the current TSB size, the seek position will be reduced accordingly.
        }; // class SeekData

        class SpeedchangedParamsData : public Core::JSON::Container {
        public:
            SpeedchangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("speed"), &Speed);
                Add(_T("muxId"), &MuxId);
            }

            bool IsValid() const
            {
                return (true);
            }

            SpeedchangedParamsData(const SpeedchangedParamsData&) = delete;
            SpeedchangedParamsData& operator=(const SpeedchangedParamsData&) = delete;

        public:
            Core::JSON::DecSInt16 Speed; // New trick play speed. The direction is defined by the sign of speed,
                    //  where a negative value means rewind and positive value means fast forward.
            Core::JSON::DecUInt8 MuxId; // Stream muxId
        }; // class SpeedchangedParamsData

        class StatusData : public Core::JSON::Container {
        public:
            StatusData()
                : Core::JSON::Container()
            {
                Add(_T("maxSizeInBytes"), &MaxSizeInBytes);
                Add(_T("currentSizeInBytes"), &CurrentSizeInBytes);
                Add(_T("currentSizeInSeconds"), &CurrentSizeInSeconds);
                Add(_T("seekPosInBytes"), &SeekPosInBytes);
                Add(_T("seekPosInSeconds"), &SeekPosInSeconds);
                Add(_T("trickPlaySpeed"), &TrickPlaySpeed);
                Add(_T("streamSourceLost"), &StreamSourceLost);
                Add(_T("streamSourceLossCount"), &StreamSourceLossCount);
            }

            bool IsValid() const
            {
                return (true);
            }

            StatusData(const StatusData&) = delete;
            StatusData& operator=(const StatusData&) = delete;

        public:
            Core::JSON::DecUInt64 MaxSizeInBytes; // Maximum TSB size in bytes.
            Core::JSON::DecUInt64 CurrentSizeInBytes; // Current TSB size in bytes.
            Core::JSON::DecUInt64 CurrentSizeInSeconds; // Current TSB size in seconds.
            Core::JSON::DecUInt64 SeekPosInBytes; // Current TSB seek position offset from live in bytes. The value is an unsigned integer and cannot exceed the current TSB size in bytes.
            Core::JSON::DecUInt64 SeekPosInSeconds; // Current TSB seek position offset from live in seconds. The value is an unsigned integer and cannot exceed the current TSB size in seconds.
            Core::JSON::DecSInt16 TrickPlaySpeed; // Current trick play speed and direction. The direction is defined by the sign of speed,
                    //  where a negative value means rewind and positive value means fast forward.
            Core::JSON::Boolean StreamSourceLost; // Boolean indicating if the buffer source is lost (true) as a result of e.g. network connectivity issues or not (false).
            Core::JSON::DecUInt64 StreamSourceLossCount; // Number of times the streaming is lost and the TSB stopped receiving data from the stream source,
                    //  during a valid channel selected.
        }; // class StatusData

        class TracingData : public Core::JSON::Container {
        public:
            TracingData()
                : Core::JSON::Container()
            {
                Add(_T("tracing"), &Tracing);
            }

            bool IsValid() const
            {
                return (true);
            }

            TracingData(const TracingData&) = delete;
            TracingData& operator=(const TracingData&) = delete;

        public:
            Core::JSON::Boolean Tracing; // Tracing enable (true) / disable (false).
        }; // class TracingData

        class TrickplayData : public Core::JSON::Container {
        public:
            TrickplayData()
                : Core::JSON::Container()
            {
                Add(_T("speed"), &Speed);
            }

            bool IsValid() const
            {
                return (true);
            }

            TrickplayData(const TrickplayData&) = delete;
            TrickplayData& operator=(const TrickplayData&) = delete;

        public:
            Core::JSON::DecSInt16 Speed; // Trick play speed. The direction is defined by the sign of speed,
                    //  where a negative value means rewind and positive value means fast forward.
        }; // class TrickplayData

    } // namespace LinearPlaybackControl

} // namespace JsonData

}

