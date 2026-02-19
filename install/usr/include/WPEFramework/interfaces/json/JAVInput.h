// Generated automatically from 'IAVInput.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_AVInput.h"
#include <interfaces/IAVInput.h>

namespace WPEFramework {

namespace Exchange {

    namespace JAVInput {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IAVInput* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JAVInput"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'numberOfInputs' - Returns an integer that specifies the number of available inputs
            _module_.Register<void, JsonData::AVInput::NumberOfInputsResultData>(_T("numberOfInputs"), 
                [_impl_](JsonData::AVInput::NumberOfInputsResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    uint32_t _numberOfInputs{};
                    bool _success{};

                    _errorCode = _impl_->NumberOfInputs(_numberOfInputs, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.NumberOfInputs = _numberOfInputs;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'writeEDID' - Changes a current EDID value
            _module_.Register<JsonData::AVInput::WriteEDIDParamsData, JsonData::AVInput::SuccessResultInfo>(_T("writeEDID"), 
                [_impl_](const JsonData::AVInput::WriteEDIDParamsData& params, JsonData::AVInput::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    const string _message{params.Message};
                    Exchange::IAVInput::SuccessResult _successResult{};

                    _errorCode = _impl_->WriteEDID(_portId, _message, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'readEDID' - Returns the current EDID value
            _module_.Register<JsonData::AVInput::ReadEDIDParamsInfo, JsonData::AVInput::ReadEDIDResultData>(_T("readEDID"), 
                [_impl_](const JsonData::AVInput::ReadEDIDParamsInfo& params, JsonData::AVInput::ReadEDIDResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    string _eDID{};
                    bool _success{};

                    _errorCode = _impl_->ReadEDID(_portId, _eDID, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.EDID = _eDID;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getRawSPD' - Returns the Source Data Product Descriptor (SPD) infoFrame packet information for the specified HDMI Input device as raw bits
            _module_.Register<JsonData::AVInput::ReadEDIDParamsInfo, JsonData::AVInput::GetRawSPDResultInfo>(_T("getRawSPD"), 
                [_impl_](const JsonData::AVInput::ReadEDIDParamsInfo& params, JsonData::AVInput::GetRawSPDResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    string _hDMISPD{};
                    bool _success{};

                    _errorCode = _impl_->GetRawSPD(_portId, _hDMISPD, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.HDMISPD = _hDMISPD;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getSPD' - Returns the Source Data Product Descriptor (SPD) infoFrame packet information for the specified HDMI Input device
            _module_.Register<JsonData::AVInput::ReadEDIDParamsInfo, JsonData::AVInput::GetRawSPDResultInfo>(_T("getSPD"), 
                [_impl_](const JsonData::AVInput::ReadEDIDParamsInfo& params, JsonData::AVInput::GetRawSPDResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    string _hDMISPD{};
                    bool _success{};

                    _errorCode = _impl_->GetSPD(_portId, _hDMISPD, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.HDMISPD = _hDMISPD;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setEdidVersion' - Sets an HDMI EDID version
            _module_.Register<JsonData::AVInput::SetEdidVersionParamsData, JsonData::AVInput::SuccessResultInfo>(_T("setEdidVersion"), 
                [_impl_](const JsonData::AVInput::SetEdidVersionParamsData& params, JsonData::AVInput::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    const string _edidVersion{params.EdidVersion};
                    Exchange::IAVInput::SuccessResult _successResult{};

                    _errorCode = _impl_->SetEdidVersion(_portId, _edidVersion, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'getEdidVersion' - Returns the EDID version
            _module_.Register<JsonData::AVInput::ReadEDIDParamsInfo, JsonData::AVInput::GetEdidVersionResultData>(_T("getEdidVersion"), 
                [_impl_](const JsonData::AVInput::ReadEDIDParamsInfo& params, JsonData::AVInput::GetEdidVersionResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    string _edidVersion{};
                    bool _success{};

                    _errorCode = _impl_->GetEdidVersion(_portId, _edidVersion, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.EdidVersion = _edidVersion;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setEdid2AllmSupport' - Sets an HDMI ALLM bit in EDID
            _module_.Register<JsonData::AVInput::SetEdid2AllmSupportParamsData, JsonData::AVInput::SuccessResultInfo>(_T("setEdid2AllmSupport"), 
                [_impl_](const JsonData::AVInput::SetEdid2AllmSupportParamsData& params, JsonData::AVInput::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    const bool _allmSupport{params.AllmSupport};
                    Exchange::IAVInput::SuccessResult _successResult{};

                    _errorCode = _impl_->SetEdid2AllmSupport(_portId, _allmSupport, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'getEdid2AllmSupport' - Returns the ALLM bit in EDID
            _module_.Register<JsonData::AVInput::ReadEDIDParamsInfo, JsonData::AVInput::GetEdid2AllmSupportResultData>(_T("getEdid2AllmSupport"), 
                [_impl_](const JsonData::AVInput::ReadEDIDParamsInfo& params, JsonData::AVInput::GetEdid2AllmSupportResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    bool _allmSupport{};
                    bool _success{};

                    _errorCode = _impl_->GetEdid2AllmSupport(_portId, _allmSupport, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.AllmSupport = _allmSupport;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setVRRSupport' - Sets an HDMI VRR support bit in EDID
            _module_.Register<JsonData::AVInput::SetVRRSupportParamsData, JsonData::AVInput::SuccessResultInfo>(_T("setVRRSupport"), 
                [_impl_](const JsonData::AVInput::SetVRRSupportParamsData& params, JsonData::AVInput::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    const bool _vrrSupport{params.VrrSupport};
                    Exchange::IAVInput::SuccessResult _successResult{};

                    _errorCode = _impl_->SetVRRSupport(_portId, _vrrSupport, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'getVRRSupport' - Returns the VRR support bit in EDID
            _module_.Register<JsonData::AVInput::ReadEDIDParamsInfo, JsonData::AVInput::GetVRRSupportResultData>(_T("getVRRSupport"), 
                [_impl_](const JsonData::AVInput::ReadEDIDParamsInfo& params, JsonData::AVInput::GetVRRSupportResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    bool _vrrSupport{};
                    bool _success{};

                    _errorCode = _impl_->GetVRRSupport(_portId, _vrrSupport, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.VrrSupport = _vrrSupport;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getHdmiVersion' - Gets the maximum hdmi compatibility version supported for the given port
            _module_.Register<JsonData::AVInput::ReadEDIDParamsInfo, JsonData::AVInput::GetHdmiVersionResultData>(_T("getHdmiVersion"), 
                [_impl_](const JsonData::AVInput::ReadEDIDParamsInfo& params, JsonData::AVInput::GetHdmiVersionResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    string _hdmiCapabilityVersion{};
                    bool _success{};

                    _errorCode = _impl_->GetHdmiVersion(_portId, _hdmiCapabilityVersion, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.HdmiCapabilityVersion = _hdmiCapabilityVersion;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setMixerLevels' - Sets the audio mixer level for given audio input
            _module_.Register<JsonData::AVInput::SetMixerLevelsParamsData, JsonData::AVInput::SuccessResultInfo>(_T("setMixerLevels"), 
                [_impl_](const JsonData::AVInput::SetMixerLevelsParamsData& params, JsonData::AVInput::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _primaryVolume{params.PrimaryVolume};
                    const int32_t _inputVolume{params.InputVolume};
                    Exchange::IAVInput::SuccessResult _successResult{};

                    _errorCode = _impl_->SetMixerLevels(_primaryVolume, _inputVolume, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'startInput' - Activates the specified HDMI/Composite Input port as the primary video source
            _module_.Register<JsonData::AVInput::StartInputParamsData, JsonData::AVInput::SuccessResultInfo>(_T("startInput"), 
                [_impl_](const JsonData::AVInput::StartInputParamsData& params, JsonData::AVInput::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    const string _typeOfInput{params.TypeOfInput};
                    const bool _requestAudioMix{params.RequestAudioMix};
                    const int32_t _plane{params.Plane};
                    const bool _topMost{params.TopMost};
                    Exchange::IAVInput::SuccessResult _successResult{};

                    _errorCode = _impl_->StartInput(_portId, _typeOfInput, _requestAudioMix, _plane, _topMost, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'stopInput' - Deactivates the HDMI/Composite Input port currently selected as the primary video source
            _module_.Register<JsonData::AVInput::StopInputParamsData, JsonData::AVInput::SuccessResultInfo>(_T("stopInput"), 
                [_impl_](const JsonData::AVInput::StopInputParamsData& params, JsonData::AVInput::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _typeOfInput{params.TypeOfInput};
                    Exchange::IAVInput::SuccessResult _successResult{};

                    _errorCode = _impl_->StopInput(_typeOfInput, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setVideoRectangle' - Sets an HDMI/Composite Input video window
            _module_.Register<JsonData::AVInput::SetVideoRectangleParamsData, JsonData::AVInput::SuccessResultInfo>(_T("setVideoRectangle"), 
                [_impl_](const JsonData::AVInput::SetVideoRectangleParamsData& params, JsonData::AVInput::SuccessResultInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint16_t _x{params.X};
                    const uint16_t _y{params.Y};
                    const uint16_t _w{params.W};
                    const uint16_t _h{params.H};
                    const string _typeOfInput{params.TypeOfInput};
                    Exchange::IAVInput::SuccessResult _successResult{};

                    _errorCode = _impl_->SetVideoRectangle(_x, _y, _w, _h, _typeOfInput, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'currentVideoMode' - Returns the current video mode for the specified input device
            _module_.Register<void, JsonData::AVInput::CurrentVideoModeResultData>(_T("currentVideoMode"), 
                [_impl_](JsonData::AVInput::CurrentVideoModeResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _currentVideoMode{};
                    bool _success{};

                    _errorCode = _impl_->CurrentVideoMode(_currentVideoMode, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.CurrentVideoMode = _currentVideoMode;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'contentProtected' - Returns whether the content is protected for the specified input device
            _module_.Register<void, JsonData::AVInput::ContentProtectedResultData>(_T("contentProtected"), 
                [_impl_](JsonData::AVInput::ContentProtectedResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _isContentProtected{};
                    bool _success{};

                    _errorCode = _impl_->ContentProtected(_isContentProtected, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.IsContentProtected = _isContentProtected;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getSupportedGameFeatures' - Returns the list of supported game features
            _module_.Register<void, JsonData::AVInput::GetSupportedGameFeaturesResultData>(_T("getSupportedGameFeatures"), 
                [_impl_](JsonData::AVInput::GetSupportedGameFeaturesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _supportedGameFeatures{};
                    bool _success{};

                    _errorCode = _impl_->GetSupportedGameFeatures(_supportedGameFeatures, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_supportedGameFeatures != nullptr) {
                            string _supportedGameFeaturesItem_{};
                            while (_supportedGameFeatures->Next(_supportedGameFeaturesItem_) == true) { result.SupportedGameFeatures.Add() = _supportedGameFeaturesItem_; }
                            _supportedGameFeatures->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getGameFeatureStatus' - Returns the Game Feature Status
            _module_.Register<JsonData::AVInput::GetGameFeatureStatusParamsData, JsonData::AVInput::GetGameFeatureStatusResultData>(_T("getGameFeatureStatus"), 
                [_impl_](const JsonData::AVInput::GetGameFeatureStatusParamsData& params,
                         JsonData::AVInput::GetGameFeatureStatusResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    const string _gameFeature{params.GameFeature};
                    bool _mode{};
                    bool _success{};

                    _errorCode = _impl_->GetGameFeatureStatus(_portId, _gameFeature, _mode, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Mode = _mode;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getVRRFrameRate' - Returns the current VRR frame rate for the specified input device
            _module_.Register<JsonData::AVInput::ReadEDIDParamsInfo, JsonData::AVInput::GetVRRFrameRateResultData>(_T("getVRRFrameRate"), 
                [_impl_](const JsonData::AVInput::ReadEDIDParamsInfo& params, JsonData::AVInput::GetVRRFrameRateResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _portId{params.PortId};
                    double _currentVRRVideoFrameRate{};
                    bool _success{};

                    _errorCode = _impl_->GetVRRFrameRate(_portId, _currentVRRVideoFrameRate, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.CurrentVRRVideoFrameRate = _currentVRRVideoFrameRate;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("numberOfInputs"));
            _module_.Unregister(_T("writeEDID"));
            _module_.Unregister(_T("readEDID"));
            _module_.Unregister(_T("getRawSPD"));
            _module_.Unregister(_T("getSPD"));
            _module_.Unregister(_T("setEdidVersion"));
            _module_.Unregister(_T("getEdidVersion"));
            _module_.Unregister(_T("setEdid2AllmSupport"));
            _module_.Unregister(_T("getEdid2AllmSupport"));
            _module_.Unregister(_T("setVRRSupport"));
            _module_.Unregister(_T("getVRRSupport"));
            _module_.Unregister(_T("getHdmiVersion"));
            _module_.Unregister(_T("setMixerLevels"));
            _module_.Unregister(_T("startInput"));
            _module_.Unregister(_T("stopInput"));
            _module_.Unregister(_T("setVideoRectangle"));
            _module_.Unregister(_T("currentVideoMode"));
            _module_.Unregister(_T("contentProtected"));
            _module_.Unregister(_T("getSupportedGameFeatures"));
            _module_.Unregister(_T("getGameFeatureStatus"));
            _module_.Unregister(_T("getVRRFrameRate"));
        }

        namespace Event {

            // Event: 'gameFeatureStatusUpdate' - Triggered whenever game feature(ALLM) status changes for an HDMI Input
            static void GameFeatureStatusUpdate(const JSONRPC& _module_, const JsonData::AVInput::GameFeatureStatusUpdateParamsData& params)
            {
                _module_.Notify(_T("gameFeatureStatusUpdate"), params);
            }

            // Event: 'gameFeatureStatusUpdate' - Triggered whenever game feature(ALLM) status changes for an HDMI Input
            static void GameFeatureStatusUpdate(const JSONRPC& _module_, const Core::JSON::DecSInt32& id, const Core::JSON::String& gameFeature,
                     const Core::JSON::Boolean& mode)
            {
                JsonData::AVInput::GameFeatureStatusUpdateParamsData _params_;
                _params_.Id = id;
                _params_.GameFeature = gameFeature;
                _params_.Mode = mode;

                GameFeatureStatusUpdate(_module_, _params_);
            }

            // Event: 'gameFeatureStatusUpdate' - Triggered whenever game feature(ALLM) status changes for an HDMI Input
            static void GameFeatureStatusUpdate(const JSONRPC& _module_, const int32_t& id, const string& gameFeature, const bool& mode)
            {
                JsonData::AVInput::GameFeatureStatusUpdateParamsData _params_;
                _params_.Id = id;
                _params_.GameFeature = gameFeature;
                _params_.Mode = mode;

                GameFeatureStatusUpdate(_module_, _params_);
            }

            // Event: 'aviContentTypeUpdate' - Triggered whenever AV Infoframe content type changes for an HDMI Input
            static void AviContentTypeUpdate(const JSONRPC& _module_, const JsonData::AVInput::AviContentTypeUpdateParamsData& params)
            {
                _module_.Notify(_T("aviContentTypeUpdate"), params);
            }

            // Event: 'aviContentTypeUpdate' - Triggered whenever AV Infoframe content type changes for an HDMI Input
            static void AviContentTypeUpdate(const JSONRPC& _module_, const Core::JSON::DecSInt32& id, const Core::JSON::DecSInt32& aviContentType)
            {
                JsonData::AVInput::AviContentTypeUpdateParamsData _params_;
                _params_.Id = id;
                _params_.AviContentType = aviContentType;

                AviContentTypeUpdate(_module_, _params_);
            }

            // Event: 'aviContentTypeUpdate' - Triggered whenever AV Infoframe content type changes for an HDMI Input
            static void AviContentTypeUpdate(const JSONRPC& _module_, const int32_t& id, const int32_t& aviContentType)
            {
                JsonData::AVInput::AviContentTypeUpdateParamsData _params_;
                _params_.Id = id;
                _params_.AviContentType = aviContentType;

                AviContentTypeUpdate(_module_, _params_);
            }

            // Event: 'onSignalChanged' - Triggered whenever the signal status changes for an HDMI/Composite Input
            static void OnSignalChanged(const JSONRPC& _module_, const JsonData::AVInput::OnSignalChangedParamsData& params)
            {
                _module_.Notify(_T("onSignalChanged"), params);
            }

            // Event: 'onSignalChanged' - Triggered whenever the signal status changes for an HDMI/Composite Input
            static void OnSignalChanged(const JSONRPC& _module_, const Core::JSON::DecSInt32& id, const Core::JSON::String& locator,
                     const Core::JSON::String& signalStatus)
            {
                JsonData::AVInput::OnSignalChangedParamsData _params_;
                _params_.Id = id;
                _params_.Locator = locator;
                _params_.SignalStatus = signalStatus;

                OnSignalChanged(_module_, _params_);
            }

            // Event: 'onSignalChanged' - Triggered whenever the signal status changes for an HDMI/Composite Input
            static void OnSignalChanged(const JSONRPC& _module_, const int32_t& id, const string& locator, const string& signalStatus)
            {
                JsonData::AVInput::OnSignalChangedParamsData _params_;
                _params_.Id = id;
                _params_.Locator = locator;
                _params_.SignalStatus = signalStatus;

                OnSignalChanged(_module_, _params_);
            }

            // Event: 'onInputStatusChanged' - Triggered whenever the status changes for an HDMI/Composite Input
            static void OnInputStatusChanged(const JSONRPC& _module_, const JsonData::AVInput::OnInputStatusChangedParamsData& params)
            {
                _module_.Notify(_T("onInputStatusChanged"), params);
            }

            // Event: 'onInputStatusChanged' - Triggered whenever the status changes for an HDMI/Composite Input
            static void OnInputStatusChanged(const JSONRPC& _module_, const Core::JSON::DecSInt32& id, const Core::JSON::String& locator,
                     const Core::JSON::String& status, const Core::JSON::DecSInt32& plane)
            {
                JsonData::AVInput::OnInputStatusChangedParamsData _params_;
                _params_.Id = id;
                _params_.Locator = locator;
                _params_.Status = status;
                _params_.Plane = plane;

                OnInputStatusChanged(_module_, _params_);
            }

            // Event: 'onInputStatusChanged' - Triggered whenever the status changes for an HDMI/Composite Input
            static void OnInputStatusChanged(const JSONRPC& _module_, const int32_t& id, const string& locator, const string& status, const int32_t& plane)
            {
                JsonData::AVInput::OnInputStatusChangedParamsData _params_;
                _params_.Id = id;
                _params_.Locator = locator;
                _params_.Status = status;
                _params_.Plane = plane;

                OnInputStatusChanged(_module_, _params_);
            }

            // Event: 'videoStreamInfoUpdate' - Triggered whenever there is an update in HDMI/Composite Input video stream info
            static void VideoStreamInfoUpdate(const JSONRPC& _module_, const JsonData::AVInput::VideoStreamInfoUpdateParamsData& params)
            {
                _module_.Notify(_T("videoStreamInfoUpdate"), params);
            }

            // Event: 'videoStreamInfoUpdate' - Triggered whenever there is an update in HDMI/Composite Input video stream info
            static void VideoStreamInfoUpdate(const JSONRPC& _module_, const Core::JSON::DecSInt32& id, const Core::JSON::String& locator,
                     const Core::JSON::DecSInt32& width, const Core::JSON::DecSInt32& height, const Core::JSON::Boolean& progressive, const Core::JSON::DecSInt32& frameRateN,
                     const Core::JSON::DecSInt32& frameRateD)
            {
                JsonData::AVInput::VideoStreamInfoUpdateParamsData _params_;
                _params_.Id = id;
                _params_.Locator = locator;
                _params_.Width = width;
                _params_.Height = height;
                _params_.Progressive = progressive;
                _params_.FrameRateN = frameRateN;
                _params_.FrameRateD = frameRateD;

                VideoStreamInfoUpdate(_module_, _params_);
            }

            // Event: 'videoStreamInfoUpdate' - Triggered whenever there is an update in HDMI/Composite Input video stream info
            static void VideoStreamInfoUpdate(const JSONRPC& _module_, const int32_t& id, const string& locator, const int32_t& width, const int32_t& height,
                     const bool& progressive, const int32_t& frameRateN, const int32_t& frameRateD)
            {
                JsonData::AVInput::VideoStreamInfoUpdateParamsData _params_;
                _params_.Id = id;
                _params_.Locator = locator;
                _params_.Width = width;
                _params_.Height = height;
                _params_.Progressive = progressive;
                _params_.FrameRateN = frameRateN;
                _params_.FrameRateD = frameRateD;

                VideoStreamInfoUpdate(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JAVInput

} // namespace Exchange

} // namespace WPEFramework

