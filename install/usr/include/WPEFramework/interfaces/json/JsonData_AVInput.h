// C++ classes for AVInput API JSON-RPC API.
// Generated automatically from 'IAVInput.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAVInput.h>

namespace WPEFramework {

namespace JsonData {

    namespace AVInput {

        // Common classes
        //

        class GetRawSPDResultInfo : public Core::JSON::Container {
        public:
            GetRawSPDResultInfo()
                : Core::JSON::Container()
            {
                Add(_T("HDMISPD"), &HDMISPD);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetRawSPDResultInfo(const GetRawSPDResultInfo&) = delete;
            GetRawSPDResultInfo& operator=(const GetRawSPDResultInfo&) = delete;

        public:
            Core::JSON::String HDMISPD; // - out - The SPD information as raw bits
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class GetRawSPDResultInfo

        class ReadEDIDParamsInfo : public Core::JSON::Container {
        public:
            ReadEDIDParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("portId"), &PortId);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReadEDIDParamsInfo(const ReadEDIDParamsInfo&) = delete;
            ReadEDIDParamsInfo& operator=(const ReadEDIDParamsInfo&) = delete;

        public:
            Core::JSON::String PortId; // - in - An ID of an HDMI/Composite Input port as returned by the getInputDevices method
        }; // class ReadEDIDParamsInfo

        class SuccessResultInfo : public Core::JSON::Container {
        public:
            SuccessResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            SuccessResultInfo(const Exchange::IAVInput::SuccessResult& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            SuccessResultInfo& operator=(const Exchange::IAVInput::SuccessResult& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAVInput::SuccessResult() const
            {
                Exchange::IAVInput::SuccessResult _value{};
                _value.success = Success;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::Boolean Success; // success
        }; // class SuccessResultInfo

        // Method params/result classes
        //

        class AviContentTypeUpdateParamsData : public Core::JSON::Container {
        public:
            AviContentTypeUpdateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
                Add(_T("aviContentType"), &AviContentType);
            }

            bool IsValid() const
            {
                return (true);
            }

            AviContentTypeUpdateParamsData(const AviContentTypeUpdateParamsData&) = delete;
            AviContentTypeUpdateParamsData& operator=(const AviContentTypeUpdateParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Id; // - in - Hdmi Input port ID for which content type change event received and possible values are port id 0,
                    //  1 and 2 for three Hdmi Input ports
            Core::JSON::DecSInt32 AviContentType; // - in - new Content type received for the active hdmi input port and the possible integer values indicates following accordingly 0 - Graphics, 1 - Photo, 2 - Cinema, 3 - Game, 4 - Invalid data
        }; // class AviContentTypeUpdateParamsData

        class ContentProtectedResultData : public Core::JSON::Container {
        public:
            ContentProtectedResultData()
                : Core::JSON::Container()
            {
                Add(_T("isContentProtected"), &IsContentProtected);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            ContentProtectedResultData(const ContentProtectedResultData&) = delete;
            ContentProtectedResultData& operator=(const ContentProtectedResultData&) = delete;

        public:
            Core::JSON::Boolean IsContentProtected; // - out - Whether the HDMI input is protected
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class ContentProtectedResultData

        class CurrentVideoModeResultData : public Core::JSON::Container {
        public:
            CurrentVideoModeResultData()
                : Core::JSON::Container()
            {
                Add(_T("currentVideoMode"), &CurrentVideoMode);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            CurrentVideoModeResultData(const CurrentVideoModeResultData&) = delete;
            CurrentVideoModeResultData& operator=(const CurrentVideoModeResultData&) = delete;

        public:
            Core::JSON::String CurrentVideoMode; // - out - The current video mode
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class CurrentVideoModeResultData

        class GameFeatureStatusUpdateParamsData : public Core::JSON::Container {
        public:
            GameFeatureStatusUpdateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
                Add(_T("gameFeature"), &GameFeature);
                Add(_T("mode"), &Mode);
            }

            bool IsValid() const
            {
                return (true);
            }

            GameFeatureStatusUpdateParamsData(const GameFeatureStatusUpdateParamsData&) = delete;
            GameFeatureStatusUpdateParamsData& operator=(const GameFeatureStatusUpdateParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Id; // - in - The port identifier for the HDMI Input
            Core::JSON::String GameFeature; // - in - Game Feature to which current status requested
            Core::JSON::Boolean Mode; // - in - The current game feature status. Mode is required only for ALLM. Need to add support for future game features
        }; // class GameFeatureStatusUpdateParamsData

        class GetEdid2AllmSupportResultData : public Core::JSON::Container {
        public:
            GetEdid2AllmSupportResultData()
                : Core::JSON::Container()
            {
                Add(_T("allmSupport"), &AllmSupport);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetEdid2AllmSupportResultData(const GetEdid2AllmSupportResultData&) = delete;
            GetEdid2AllmSupportResultData& operator=(const GetEdid2AllmSupportResultData&) = delete;

        public:
            Core::JSON::Boolean AllmSupport; // - out - The ALLM bit value in edid
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class GetEdid2AllmSupportResultData

        class GetEdidVersionResultData : public Core::JSON::Container {
        public:
            GetEdidVersionResultData()
                : Core::JSON::Container()
            {
                Add(_T("edidVersion"), &EdidVersion);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetEdidVersionResultData(const GetEdidVersionResultData&) = delete;
            GetEdidVersionResultData& operator=(const GetEdidVersionResultData&) = delete;

        public:
            Core::JSON::String EdidVersion; // - out - The EDID version
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class GetEdidVersionResultData

        class GetGameFeatureStatusParamsData : public Core::JSON::Container {
        public:
            GetGameFeatureStatusParamsData()
                : Core::JSON::Container()
            {
                Add(_T("portId"), &PortId);
                Add(_T("gameFeature"), &GameFeature);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetGameFeatureStatusParamsData(const GetGameFeatureStatusParamsData&) = delete;
            GetGameFeatureStatusParamsData& operator=(const GetGameFeatureStatusParamsData&) = delete;

        public:
            Core::JSON::String PortId; // - in - An ID of an HDMI Input port as returned by the getInputDevices method
            Core::JSON::String GameFeature; // - in - Game Feature to which current status requested
        }; // class GetGameFeatureStatusParamsData

        class GetGameFeatureStatusResultData : public Core::JSON::Container {
        public:
            GetGameFeatureStatusResultData()
                : Core::JSON::Container()
            {
                Add(_T("mode"), &Mode);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetGameFeatureStatusResultData(const GetGameFeatureStatusResultData&) = delete;
            GetGameFeatureStatusResultData& operator=(const GetGameFeatureStatusResultData&) = delete;

        public:
            Core::JSON::Boolean Mode; // - out - The current game feature status. Mode is required only for ALLM. Need to add support for future game features
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class GetGameFeatureStatusResultData

        class GetHdmiVersionResultData : public Core::JSON::Container {
        public:
            GetHdmiVersionResultData()
                : Core::JSON::Container()
            {
                Add(_T("HdmiCapabilityVersion"), &HdmiCapabilityVersion);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetHdmiVersionResultData(const GetHdmiVersionResultData&) = delete;
            GetHdmiVersionResultData& operator=(const GetHdmiVersionResultData&) = delete;

        public:
            Core::JSON::String HdmiCapabilityVersion; // - out - The Maximum Hdmi compatibility version supported by the given port
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class GetHdmiVersionResultData

        class GetSupportedGameFeaturesResultData : public Core::JSON::Container {
        public:
            GetSupportedGameFeaturesResultData()
                : Core::JSON::Container()
            {
                Add(_T("supportedGameFeatures"), &SupportedGameFeatures);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetSupportedGameFeaturesResultData(const GetSupportedGameFeaturesResultData&) = delete;
            GetSupportedGameFeaturesResultData& operator=(const GetSupportedGameFeaturesResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> SupportedGameFeatures; // - out - The supported game Features
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class GetSupportedGameFeaturesResultData

        class GetVRRFrameRateResultData : public Core::JSON::Container {
        public:
            GetVRRFrameRateResultData()
                : Core::JSON::Container()
            {
                Add(_T("currentVRRVideoFrameRate"), &CurrentVRRVideoFrameRate);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetVRRFrameRateResultData(const GetVRRFrameRateResultData&) = delete;
            GetVRRFrameRateResultData& operator=(const GetVRRFrameRateResultData&) = delete;

        public:
            Core::JSON::Double CurrentVRRVideoFrameRate; // - out - The current VRR frame rate
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class GetVRRFrameRateResultData

        class GetVRRSupportResultData : public Core::JSON::Container {
        public:
            GetVRRSupportResultData()
                : Core::JSON::Container()
            {
                Add(_T("vrrSupport"), &VrrSupport);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetVRRSupportResultData(const GetVRRSupportResultData&) = delete;
            GetVRRSupportResultData& operator=(const GetVRRSupportResultData&) = delete;

        public:
            Core::JSON::Boolean VrrSupport; // - out - The VRR support bit value
            Core::JSON::Boolean Success; // Returns the VRR support bit in EDID
        }; // class GetVRRSupportResultData

        class NumberOfInputsResultData : public Core::JSON::Container {
        public:
            NumberOfInputsResultData()
                : Core::JSON::Container()
            {
                Add(_T("numberOfInputs"), &NumberOfInputs);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            NumberOfInputsResultData(const NumberOfInputsResultData&) = delete;
            NumberOfInputsResultData& operator=(const NumberOfInputsResultData&) = delete;

        public:
            Core::JSON::DecUInt32 NumberOfInputs; // - out - The number of inputs that are available for selection
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class NumberOfInputsResultData

        class OnInputStatusChangedParamsData : public Core::JSON::Container {
        public:
            OnInputStatusChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
                Add(_T("locator"), &Locator);
                Add(_T("status"), &Status);
                Add(_T("plane"), &Plane);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnInputStatusChangedParamsData(const OnInputStatusChangedParamsData&) = delete;
            OnInputStatusChangedParamsData& operator=(const OnInputStatusChangedParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Id; // - in - The port identifier for the HDMI/Composite Input
            Core::JSON::String Locator; // - in - A URL corresponding to the HDMI/Composite Input port
            Core::JSON::String Status; // - in - Status of the HDMI/Composite Input. Valid values are started or stopped
            Core::JSON::DecSInt32 Plane; // - in - Defines whether the video plane type, 0 - Primary video plane, 1 - Secondary Video Plane,
                    //  Other values - Invalid
        }; // class OnInputStatusChangedParamsData

        class OnSignalChangedParamsData : public Core::JSON::Container {
        public:
            OnSignalChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
                Add(_T("locator"), &Locator);
                Add(_T("signalStatus"), &SignalStatus);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnSignalChangedParamsData(const OnSignalChangedParamsData&) = delete;
            OnSignalChangedParamsData& operator=(const OnSignalChangedParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Id; // - in - The port identifier for the HDMI/Composite Input
            Core::JSON::String Locator; // - in - A URL corresponding to the HDMI/Composite Input port
            Core::JSON::String SignalStatus; // - in - Signal Status of the HDMI/Composite Input. Valid values are noSignal, unstableSignal, notSupportedSignal,
                    //  stableSignal
        }; // class OnSignalChangedParamsData

        class ReadEDIDResultData : public Core::JSON::Container {
        public:
            ReadEDIDResultData()
                : Core::JSON::Container()
            {
                Add(_T("EDID"), &EDID);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReadEDIDResultData(const ReadEDIDResultData&) = delete;
            ReadEDIDResultData& operator=(const ReadEDIDResultData&) = delete;

        public:
            Core::JSON::String EDID; // - out - The EDID Value
            Core::JSON::Boolean Success; // - out - Whether the request succeeded
        }; // class ReadEDIDResultData

        class SetEdid2AllmSupportParamsData : public Core::JSON::Container {
        public:
            SetEdid2AllmSupportParamsData()
                : Core::JSON::Container()
            {
                Add(_T("portId"), &PortId);
                Add(_T("allmSupport"), &AllmSupport);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetEdid2AllmSupportParamsData(const SetEdid2AllmSupportParamsData&) = delete;
            SetEdid2AllmSupportParamsData& operator=(const SetEdid2AllmSupportParamsData&) = delete;

        public:
            Core::JSON::String PortId; // - in - An ID of an HDMI/Composite Input port as returned by the getInputDevices method
            Core::JSON::Boolean AllmSupport; // - in - The ALLM support in EDID
        }; // class SetEdid2AllmSupportParamsData

        class SetEdidVersionParamsData : public Core::JSON::Container {
        public:
            SetEdidVersionParamsData()
                : Core::JSON::Container()
            {
                Add(_T("portId"), &PortId);
                Add(_T("edidVersion"), &EdidVersion);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetEdidVersionParamsData(const SetEdidVersionParamsData&) = delete;
            SetEdidVersionParamsData& operator=(const SetEdidVersionParamsData&) = delete;

        public:
            Core::JSON::String PortId; // - in - An ID of an HDMI/Composite Input port as returned by the getInputDevices method
            Core::JSON::String EdidVersion; // - in - The EDID version
        }; // class SetEdidVersionParamsData

        class SetMixerLevelsParamsData : public Core::JSON::Container {
        public:
            SetMixerLevelsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("primaryVolume"), &PrimaryVolume);
                Add(_T("inputVolume"), &InputVolume);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetMixerLevelsParamsData(const SetMixerLevelsParamsData&) = delete;
            SetMixerLevelsParamsData& operator=(const SetMixerLevelsParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 PrimaryVolume; // - in - Primary audio input volume
            Core::JSON::DecSInt32 InputVolume; // - in - System audio input volume
        }; // class SetMixerLevelsParamsData

        class SetVRRSupportParamsData : public Core::JSON::Container {
        public:
            SetVRRSupportParamsData()
                : Core::JSON::Container()
            {
                Add(_T("portId"), &PortId);
                Add(_T("vrrSupport"), &VrrSupport);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetVRRSupportParamsData(const SetVRRSupportParamsData&) = delete;
            SetVRRSupportParamsData& operator=(const SetVRRSupportParamsData&) = delete;

        public:
            Core::JSON::String PortId; // Sets an HDMI VRR support bit in EDID
            Core::JSON::Boolean VrrSupport; // - in - The VRR support bit value to set
        }; // class SetVRRSupportParamsData

        class SetVideoRectangleParamsData : public Core::JSON::Container {
        public:
            SetVideoRectangleParamsData()
                : Core::JSON::Container()
            {
                Add(_T("x"), &X);
                Add(_T("y"), &Y);
                Add(_T("w"), &W);
                Add(_T("h"), &H);
                Add(_T("typeOfInput"), &TypeOfInput);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetVideoRectangleParamsData(const SetVideoRectangleParamsData&) = delete;
            SetVideoRectangleParamsData& operator=(const SetVideoRectangleParamsData&) = delete;

        public:
            Core::JSON::DecUInt16 X; // - in - The x-coordinate of the video rectangle
            Core::JSON::DecUInt16 Y; // - in - The y-coordinate of the video rectangle
            Core::JSON::DecUInt16 W; // - in - The width of the video rectangle
            Core::JSON::DecUInt16 H; // - in - The height of the video rectangle
            Core::JSON::String TypeOfInput; // - in - The type of Input - HDMI/COMPOSITE
        }; // class SetVideoRectangleParamsData

        class StartInputParamsData : public Core::JSON::Container {
        public:
            StartInputParamsData()
                : Core::JSON::Container()
            {
                Add(_T("portId"), &PortId);
                Add(_T("typeOfInput"), &TypeOfInput);
                Add(_T("requestAudioMix"), &RequestAudioMix);
                Add(_T("plane"), &Plane);
                Add(_T("topMost"), &TopMost);
            }

            bool IsValid() const
            {
                return (true);
            }

            StartInputParamsData(const StartInputParamsData&) = delete;
            StartInputParamsData& operator=(const StartInputParamsData&) = delete;

        public:
            Core::JSON::String PortId; // - in - An ID of an HDMI/Composite Input port as returned by the getInputDevices method
            Core::JSON::String TypeOfInput; // - in - The type of Input - HDMI/COMPOSITE
            Core::JSON::Boolean RequestAudioMix; // - in - Defines whether the Audio mixing is true or false, This is an optional argument
            Core::JSON::DecSInt32 Plane; // - in - Defines whether the video plane type, 0 - Primary video plane, 1 - Secondary Video Plane,
                    //  Other values - Invalid - This is an optional argument
            Core::JSON::Boolean TopMost; // - in - Defines whether the Hdmi Input should be over or under the other video plane
        }; // class StartInputParamsData

        class StopInputParamsData : public Core::JSON::Container {
        public:
            StopInputParamsData()
                : Core::JSON::Container()
            {
                Add(_T("typeOfInput"), &TypeOfInput);
            }

            bool IsValid() const
            {
                return (true);
            }

            StopInputParamsData(const StopInputParamsData&) = delete;
            StopInputParamsData& operator=(const StopInputParamsData&) = delete;

        public:
            Core::JSON::String TypeOfInput; // - in - The type of Input - HDMI/COMPOSITE
        }; // class StopInputParamsData

        class VideoStreamInfoUpdateParamsData : public Core::JSON::Container {
        public:
            VideoStreamInfoUpdateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
                Add(_T("locator"), &Locator);
                Add(_T("width"), &Width);
                Add(_T("height"), &Height);
                Add(_T("progressive"), &Progressive);
                Add(_T("frameRateN"), &FrameRateN);
                Add(_T("frameRateD"), &FrameRateD);
            }

            bool IsValid() const
            {
                return (true);
            }

            VideoStreamInfoUpdateParamsData(const VideoStreamInfoUpdateParamsData&) = delete;
            VideoStreamInfoUpdateParamsData& operator=(const VideoStreamInfoUpdateParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Id; // - in - The port identifier for the HDMI/Composite Input
            Core::JSON::String Locator; // - in - A URL corresponding to the HDMI/Composite Input port
            Core::JSON::DecSInt32 Width; // - in - Width of the Video Stream
            Core::JSON::DecSInt32 Height; // - in - Height of the Video Stream
            Core::JSON::Boolean Progressive; // - in - Whether the Video Stream is progressive or not
            Core::JSON::DecSInt32 FrameRateN; // - in - FrameRate Numerator
            Core::JSON::DecSInt32 FrameRateD; // - in - FrameRate Denominator
        }; // class VideoStreamInfoUpdateParamsData

        class WriteEDIDParamsData : public Core::JSON::Container {
        public:
            WriteEDIDParamsData()
                : Core::JSON::Container()
            {
                Add(_T("portId"), &PortId);
                Add(_T("message"), &Message);
            }

            bool IsValid() const
            {
                return (true);
            }

            WriteEDIDParamsData(const WriteEDIDParamsData&) = delete;
            WriteEDIDParamsData& operator=(const WriteEDIDParamsData&) = delete;

        public:
            Core::JSON::String PortId; // - in - An ID of an HDMI/Composite Input port as returned by the getInputDevices method
            Core::JSON::String Message; // - in - A new EDID value
        }; // class WriteEDIDParamsData

    } // namespace AVInput

} // namespace JsonData

}

