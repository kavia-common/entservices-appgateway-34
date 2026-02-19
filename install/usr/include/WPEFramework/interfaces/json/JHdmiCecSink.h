// Generated automatically from 'IHdmiCecSink.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_HdmiCecSink.h"
#include <interfaces/IHdmiCecSink.h>

namespace WPEFramework {

namespace Exchange {

    namespace JHdmiCecSink {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IHdmiCecSink* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JHdmiCecSink"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getActiveRoute' - Gets the Active Route(s) of the HDMI CEC Sink
            _module_.Register<void, JsonData::HdmiCecSink::GetActiveRouteResultData>(_T("getActiveRoute"), 
                [_impl_](JsonData::HdmiCecSink::GetActiveRouteResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _available{};
                    uint8_t _length{};
                    ::WPEFramework::RPC::IIteratorType<IHdmiCecSink::HdmiCecSinkActivePath, ID_HDMI_CEC_SINK_ACTIVE_PATH_ITERATOR>* _pathList{};
                    string _activeRoute{};
                    bool _success{};

                    _errorCode = _impl_->GetActiveRoute(_available, _length, _pathList, _activeRoute, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Available = _available;
                        result.Length = _length;

                        if (_pathList != nullptr) {
                            Exchange::IHdmiCecSink::HdmiCecSinkActivePath _pathListItem_{};
                            while (_pathList->Next(_pathListItem_) == true) { result.PathList.Add() = _pathListItem_; }
                            _pathList->Release();
                        }
                        result.ActiveRoute = _activeRoute;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getActiveSource' - Gets the status of the current active source
            _module_.Register<void, JsonData::HdmiCecSink::GetActiveSourceResultData>(_T("getActiveSource"), 
                [_impl_](JsonData::HdmiCecSink::GetActiveSourceResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _available{};
                    uint8_t _logicalAddress{};
                    string _physicalAddress{};
                    string _deviceType{};
                    string _cecVersion{};
                    string _osdName{};
                    string _vendorID{};
                    string _powerStatus{};
                    string _port{};
                    bool _success{};

                    _errorCode = _impl_->GetActiveSource(_available, _logicalAddress, _physicalAddress, _deviceType, _cecVersion, _osdName, _vendorID,
                             _powerStatus, _port, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Available = _available;
                        result.LogicalAddress = _logicalAddress;
                        result.PhysicalAddress = _physicalAddress;
                        result.DeviceType = _deviceType;
                        result.CecVersion = _cecVersion;
                        result.OsdName = _osdName;
                        result.VendorID = _vendorID;
                        result.PowerStatus = _powerStatus;
                        result.Port = _port;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getAudioDeviceConnectedStatus' - Gets audio device connected status
            _module_.Register<void, JsonData::HdmiCecSink::GetAudioDeviceConnectedStatusResultData>(_T("getAudioDeviceConnectedStatus"), 
                [_impl_](JsonData::HdmiCecSink::GetAudioDeviceConnectedStatusResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _connected{};
                    bool _success{};

                    _errorCode = _impl_->GetAudioDeviceConnectedStatus(_connected, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Connected = _connected;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getDeviceList' - Gets the list of devices connected to the HDMI CEC sink
            _module_.Register<void, JsonData::HdmiCecSink::GetDeviceListResultData>(_T("getDeviceList"), 
                [_impl_](JsonData::HdmiCecSink::GetDeviceListResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    uint32_t _numberofdevices{};
                    ::WPEFramework::RPC::IIteratorType<IHdmiCecSink::HdmiCecSinkDevices, ID_HDMI_CEC_SINK_DEVICE_LIST_ITERATOR>* _deviceList{};
                    bool _success{};

                    _errorCode = _impl_->GetDeviceList(_numberofdevices, _deviceList, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Numberofdevices = _numberofdevices;

                        if (_deviceList != nullptr) {
                            Exchange::IHdmiCecSink::HdmiCecSinkDevices _deviceListItem_{};
                            while (_deviceList->Next(_deviceListItem_) == true) { result.DeviceList.Add() = _deviceListItem_; }
                            _deviceList->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getEnabled' - Gets the status of the HDMI CEC Sink
            _module_.Register<void, JsonData::HdmiCecSink::GetEnabledResultData>(_T("getEnabled"), 
                [_impl_](JsonData::HdmiCecSink::GetEnabledResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _enabled{};
                    bool _success{};

                    _errorCode = _impl_->GetEnabled(_enabled, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Enabled = _enabled;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getOSDName' - Gets the OSD name of the HDMI CEC Sink
            _module_.Register<void, JsonData::HdmiCecSink::GetOSDNameResultData>(_T("getOSDName"), 
                [_impl_](JsonData::HdmiCecSink::GetOSDNameResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _name{};
                    bool _success{};

                    _errorCode = _impl_->GetOSDName(_name, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Name = _name;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getVendorId' - Gets the vendor ID of the HDMI CEC Sink
            _module_.Register<void, JsonData::HdmiCecSink::GetVendorIdResultData>(_T("getVendorId"), 
                [_impl_](JsonData::HdmiCecSink::GetVendorIdResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _vendorid{};
                    bool _success{};

                    _errorCode = _impl_->GetVendorId(_vendorid, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Vendorid = _vendorid;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'printDeviceList' - This is a helper debug command for developers
            _module_.Register<void, JsonData::HdmiCecSink::PrintDeviceListResultData>(_T("printDeviceList"), 
                [_impl_](JsonData::HdmiCecSink::PrintDeviceListResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _printed{};
                    bool _success{};

                    _errorCode = _impl_->PrintDeviceList(_printed, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Printed = _printed;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'requestActiveSource' - Request the active source in the network
            _module_.Register<void, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("requestActiveSource"), 
                [_impl_](JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->RequestActiveSource(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'requestShortAudioDescriptor' - Sends the CEC Request Short Audio Descriptor (SAD) message as an
            _module_.Register<void, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("requestShortAudioDescriptor"), 
                [_impl_](JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->RequestShortAudioDescriptor(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'sendAudioDevicePowerOnMessage' - This message is used to power on the connected audio device
            _module_.Register<void, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("sendAudioDevicePowerOnMessage"), 
                [_impl_](JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SendAudioDevicePowerOnMessage(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'sendGetAudioStatusMessage' - Sends the CEC <Give Audio Status> message to request the audio status
            _module_.Register<void, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("sendGetAudioStatusMessage"), 
                [_impl_](JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SendGetAudioStatusMessage(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'sendKeyPressEvent' - Sends the CEC <User Control Pressed> message when TV remote key is pressed
            _module_.Register<JsonData::HdmiCecSink::SendKeyPressEventParamsInfo, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("sendKeyPressEvent"), 
                [_impl_](const JsonData::HdmiCecSink::SendKeyPressEventParamsInfo& params,
                         JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _logicalAddress{params.LogicalAddress};
                    const uint32_t _keyCode{params.KeyCode};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SendKeyPressEvent(_logicalAddress, _keyCode, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'sendUserControlPressed' - Sends the CEC <User Control Pressed> message when TV remote key is pressed
            _module_.Register<JsonData::HdmiCecSink::SendKeyPressEventParamsInfo, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("sendUserControlPressed"), 
                [_impl_](const JsonData::HdmiCecSink::SendKeyPressEventParamsInfo& params,
                         JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _logicalAddress{params.LogicalAddress};
                    const uint32_t _keyCode{params.KeyCode};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SendUserControlPressed(_logicalAddress, _keyCode, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'sendUserControlReleased' - Sends the CEC <User Control Released> message when TV remote key is released
            _module_.Register<JsonData::HdmiCecSink::SendUserControlReleasedParamsData,
                     JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("sendUserControlReleased"), 
                [_impl_](const JsonData::HdmiCecSink::SendUserControlReleasedParamsData& params,
                         JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _logicalAddress{params.LogicalAddress};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SendUserControlReleased(_logicalAddress, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'sendStandbyMessage' - Sends the CEC <Standby> message to another CEC device
            _module_.Register<void, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("sendStandbyMessage"), 
                [_impl_](JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SendStandbyMessage(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setActivePath' - Sets the source device to active (setStreamPath)
            _module_.Register<JsonData::HdmiCecSink::SetActivePathParamsData, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setActivePath"), 
                [_impl_](const JsonData::HdmiCecSink::SetActivePathParamsData& params,
                         JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _activePath{params.ActivePath};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetActivePath(_activePath, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setActiveSource' - Sets the current active source as TV (physical address 0
            _module_.Register<void, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setActiveSource"), 
                [_impl_](JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetActiveSource(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setEnabled' - Sets the status of the HDMI CEC Sink
            _module_.Register<JsonData::HdmiCecSink::SetEnabledParamsInfo, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setEnabled"), 
                [_impl_](const JsonData::HdmiCecSink::SetEnabledParamsInfo& params, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetEnabled(_enabled, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setMenuLanguage' - Updates the internal data structure with the new menu Language and also broadcasts the <Set Menu Language> CEC message
            _module_.Register<JsonData::HdmiCecSink::SetMenuLanguageParamsData, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setMenuLanguage"), 
                [_impl_](const JsonData::HdmiCecSink::SetMenuLanguageParamsData& params,
                         JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _language{params.Language};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetMenuLanguage(_language, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setOSDName' - Sets the OSD name of the HDMI CEC Sink
            _module_.Register<JsonData::HdmiCecSink::SetOSDNameParamsData, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setOSDName"), 
                [_impl_](const JsonData::HdmiCecSink::SetOSDNameParamsData& params, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _name{params.Name};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetOSDName(_name, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setRoutingChange' - Changes routing while switching between HDMI inputs and TV
            _module_.Register<JsonData::HdmiCecSink::SetRoutingChangeParamsData, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setRoutingChange"), 
                [_impl_](const JsonData::HdmiCecSink::SetRoutingChangeParamsData& params,
                         JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _oldPort{params.OldPort};
                    const string _newPort{params.NewPort};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetRoutingChange(_oldPort, _newPort, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setupARCRouting' - Enable (or disable) HDMI-CEC Audio Return Channel (ARC) routing
            _module_.Register<JsonData::HdmiCecSink::SetEnabledParamsInfo, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setupARCRouting"), 
                [_impl_](const JsonData::HdmiCecSink::SetEnabledParamsInfo& params, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetupARCRouting(_enabled, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setVendorId' - Sets the vendor ID of the HDMI CEC Sink
            _module_.Register<JsonData::HdmiCecSink::SetVendorIdParamsData, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setVendorId"), 
                [_impl_](const JsonData::HdmiCecSink::SetVendorIdParamsData& params, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _vendorid{params.Vendorid};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetVendorId(_vendorid, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'setLatencyInfo' - Sets the Current Latency Values such as Video Latency, Latency Flags,
                    // Audio Output Compensated value and Audio Output Delay by sending <Report Current Latency> message for Dynamic Auto LipSync Feature
            _module_.Register<JsonData::HdmiCecSink::SetLatencyInfoParamsData, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("setLatencyInfo"), 
                [_impl_](const JsonData::HdmiCecSink::SetLatencyInfoParamsData& params,
                         JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _videoLatency{params.VideoLatency};
                    const string _lowLatencyMode{params.LowLatencyMode};
                    const string _audioOutputCompensated{params.AudioOutputCompensated};
                    const string _audioOutputDelay{params.AudioOutputDelay};
                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->SetLatencyInfo(_videoLatency, _lowLatencyMode, _audioOutputCompensated, _audioOutputDelay, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'requestAudioDevicePowerStatus' - Requests the audio device power status
            _module_.Register<void, JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo>(_T("requestAudioDevicePowerStatus"), 
                [_impl_](JsonData::HdmiCecSink::HdmiCecSinkSuccessInfo& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSink::HdmiCecSinkSuccess _successResult{};

                    _errorCode = _impl_->RequestAudioDevicePowerStatus(_successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getActiveRoute"));
            _module_.Unregister(_T("getActiveSource"));
            _module_.Unregister(_T("getAudioDeviceConnectedStatus"));
            _module_.Unregister(_T("getDeviceList"));
            _module_.Unregister(_T("getEnabled"));
            _module_.Unregister(_T("getOSDName"));
            _module_.Unregister(_T("getVendorId"));
            _module_.Unregister(_T("printDeviceList"));
            _module_.Unregister(_T("requestActiveSource"));
            _module_.Unregister(_T("requestShortAudioDescriptor"));
            _module_.Unregister(_T("sendAudioDevicePowerOnMessage"));
            _module_.Unregister(_T("sendGetAudioStatusMessage"));
            _module_.Unregister(_T("sendKeyPressEvent"));
            _module_.Unregister(_T("sendUserControlPressed"));
            _module_.Unregister(_T("sendUserControlReleased"));
            _module_.Unregister(_T("sendStandbyMessage"));
            _module_.Unregister(_T("setActivePath"));
            _module_.Unregister(_T("setActiveSource"));
            _module_.Unregister(_T("setEnabled"));
            _module_.Unregister(_T("setMenuLanguage"));
            _module_.Unregister(_T("setOSDName"));
            _module_.Unregister(_T("setRoutingChange"));
            _module_.Unregister(_T("setupARCRouting"));
            _module_.Unregister(_T("setVendorId"));
            _module_.Unregister(_T("setLatencyInfo"));
            _module_.Unregister(_T("requestAudioDevicePowerStatus"));
        }

        namespace Event {

            // Event: 'arcInitiationEvent' - Triggered when routing though the HDMI ARC port is successfully established
            static void ArcInitiationEvent(const JSONRPC& _module_, const JsonData::HdmiCecSink::ArcInitiationEventParamsInfo& params)
            {
                _module_.Notify(_T("arcInitiationEvent"), params);
            }

            // Event: 'arcInitiationEvent' - Triggered when routing though the HDMI ARC port is successfully established
            static void ArcInitiationEvent(const JSONRPC& _module_, const Core::JSON::String& status)
            {
                JsonData::HdmiCecSink::ArcInitiationEventParamsInfo _params_;
                _params_.Status = status;

                ArcInitiationEvent(_module_, _params_);
            }

            // Event: 'arcInitiationEvent' - Triggered when routing though the HDMI ARC port is successfully established
            static void ArcInitiationEvent(const JSONRPC& _module_, const string& status)
            {
                JsonData::HdmiCecSink::ArcInitiationEventParamsInfo _params_;
                _params_.Status = status;

                ArcInitiationEvent(_module_, _params_);
            }

            // Event: 'arcTerminationEvent' - Triggered when routing though the HDMI ARC port terminates
            static void ArcTerminationEvent(const JSONRPC& _module_, const JsonData::HdmiCecSink::ArcInitiationEventParamsInfo& params)
            {
                _module_.Notify(_T("arcTerminationEvent"), params);
            }

            // Event: 'arcTerminationEvent' - Triggered when routing though the HDMI ARC port terminates
            static void ArcTerminationEvent(const JSONRPC& _module_, const Core::JSON::String& status)
            {
                JsonData::HdmiCecSink::ArcInitiationEventParamsInfo _params_;
                _params_.Status = status;

                ArcTerminationEvent(_module_, _params_);
            }

            // Event: 'arcTerminationEvent' - Triggered when routing though the HDMI ARC port terminates
            static void ArcTerminationEvent(const JSONRPC& _module_, const string& status)
            {
                JsonData::HdmiCecSink::ArcInitiationEventParamsInfo _params_;
                _params_.Status = status;

                ArcTerminationEvent(_module_, _params_);
            }

            // Event: 'onActiveSourceChange' - Triggered when the active source device changes
            static void OnActiveSourceChange(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnActiveSourceChangeParamsInfo& params)
            {
                _module_.Notify(_T("onActiveSourceChange"), params);
            }

            // Event: 'onActiveSourceChange' - Triggered when the active source device changes
            static void OnActiveSourceChange(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress, const Core::JSON::String& physicalAddress)
            {
                JsonData::HdmiCecSink::OnActiveSourceChangeParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;
                _params_.PhysicalAddress = physicalAddress;

                OnActiveSourceChange(_module_, _params_);
            }

            // Event: 'onActiveSourceChange' - Triggered when the active source device changes
            static void OnActiveSourceChange(const JSONRPC& _module_, const int32_t& logicalAddress, const string& physicalAddress)
            {
                JsonData::HdmiCecSink::OnActiveSourceChangeParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;
                _params_.PhysicalAddress = physicalAddress;

                OnActiveSourceChange(_module_, _params_);
            }

            // Event: 'onDeviceAdded' - Triggered when a new device is added to the CEC network
            static void OnDeviceAdded(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onDeviceAdded"), params);
            }

            // Event: 'onDeviceAdded' - Triggered when a new device is added to the CEC network
            static void OnDeviceAdded(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceAdded(_module_, _params_);
            }

            // Event: 'onDeviceAdded' - Triggered when a new device is added to the CEC network
            static void OnDeviceAdded(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceAdded(_module_, _params_);
            }

            // Event: 'onDeviceInfoUpdated' - Triggered when device information changes
            static void OnDeviceInfoUpdated(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onDeviceInfoUpdated"), params);
            }

            // Event: 'onDeviceInfoUpdated' - Triggered when device information changes
            static void OnDeviceInfoUpdated(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceInfoUpdated(_module_, _params_);
            }

            // Event: 'onDeviceInfoUpdated' - Triggered when device information changes
            static void OnDeviceInfoUpdated(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceInfoUpdated(_module_, _params_);
            }

            // Event: 'onDeviceRemoved' - Triggered when a device is removed from the CEC network
            static void OnDeviceRemoved(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onDeviceRemoved"), params);
            }

            // Event: 'onDeviceRemoved' - Triggered when a device is removed from the CEC network
            static void OnDeviceRemoved(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceRemoved(_module_, _params_);
            }

            // Event: 'onDeviceRemoved' - Triggered when a device is removed from the CEC network
            static void OnDeviceRemoved(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceRemoved(_module_, _params_);
            }

            // Event: 'onImageViewOnMsg' - Triggered when an <Image View ON> CEC message is received from the source device
            static void OnImageViewOnMsg(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onImageViewOnMsg"), params);
            }

            // Event: 'onImageViewOnMsg' - Triggered when an <Image View ON> CEC message is received from the source device
            static void OnImageViewOnMsg(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnImageViewOnMsg(_module_, _params_);
            }

            // Event: 'onImageViewOnMsg' - Triggered when an <Image View ON> CEC message is received from the source device
            static void OnImageViewOnMsg(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnImageViewOnMsg(_module_, _params_);
            }

            // Event: 'onInActiveSource' - Triggered when the source is no longer active
            static void OnInActiveSource(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnActiveSourceChangeParamsInfo& params)
            {
                _module_.Notify(_T("onInActiveSource"), params);
            }

            // Event: 'onInActiveSource' - Triggered when the source is no longer active
            static void OnInActiveSource(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress, const Core::JSON::String& physicalAddress)
            {
                JsonData::HdmiCecSink::OnActiveSourceChangeParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;
                _params_.PhysicalAddress = physicalAddress;

                OnInActiveSource(_module_, _params_);
            }

            // Event: 'onInActiveSource' - Triggered when the source is no longer active
            static void OnInActiveSource(const JSONRPC& _module_, const int32_t& logicalAddress, const string& physicalAddress)
            {
                JsonData::HdmiCecSink::OnActiveSourceChangeParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;
                _params_.PhysicalAddress = physicalAddress;

                OnInActiveSource(_module_, _params_);
            }

            // Event: 'onTextViewOnMsg' - Triggered when a <Text View ON> CEC message is received from the source device
            static void OnTextViewOnMsg(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onTextViewOnMsg"), params);
            }

            // Event: 'onTextViewOnMsg' - Triggered when a <Text View ON> CEC message is received from the source device
            static void OnTextViewOnMsg(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnTextViewOnMsg(_module_, _params_);
            }

            // Event: 'onTextViewOnMsg' - Triggered when a <Text View ON> CEC message is received from the source device
            static void OnTextViewOnMsg(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnTextViewOnMsg(_module_, _params_);
            }

            // Event: 'onWakeupFromStandby' - Triggered when the TV is in standby mode and it receives <Image View ON>/ <Text View ON>/ <Active Source> CEC message from the connected source device
            static void OnWakeupFromStandby(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onWakeupFromStandby"), params);
            }

            // Event: 'onWakeupFromStandby' - Triggered when the TV is in standby mode and it receives <Image View ON>/ <Text View ON>/ <Active Source> CEC message from the connected source device
            static void OnWakeupFromStandby(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnWakeupFromStandby(_module_, _params_);
            }

            // Event: 'onWakeupFromStandby' - Triggered when the TV is in standby mode and it receives <Image View ON>/ <Text View ON>/ <Active Source> CEC message from the connected source device
            static void OnWakeupFromStandby(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnWakeupFromStandby(_module_, _params_);
            }

            // Event: 'reportAudioDeviceConnectedStatus' - Triggered when an audio device is added or removed
            static void ReportAudioDeviceConnectedStatus(const JSONRPC& _module_,
                     const JsonData::HdmiCecSink::ReportAudioDeviceConnectedStatusParamsData& params)
            {
                _module_.Notify(_T("reportAudioDeviceConnectedStatus"), params);
            }

            // Event: 'reportAudioDeviceConnectedStatus' - Triggered when an audio device is added or removed
            static void ReportAudioDeviceConnectedStatus(const JSONRPC& _module_, const Core::JSON::String& status,
                     const Core::JSON::String& audioDeviceConnected)
            {
                JsonData::HdmiCecSink::ReportAudioDeviceConnectedStatusParamsData _params_;
                _params_.Status = status;
                _params_.AudioDeviceConnected = audioDeviceConnected;

                ReportAudioDeviceConnectedStatus(_module_, _params_);
            }

            // Event: 'reportAudioDeviceConnectedStatus' - Triggered when an audio device is added or removed
            static void ReportAudioDeviceConnectedStatus(const JSONRPC& _module_, const string& status, const string& audioDeviceConnected)
            {
                JsonData::HdmiCecSink::ReportAudioDeviceConnectedStatusParamsData _params_;
                _params_.Status = status;
                _params_.AudioDeviceConnected = audioDeviceConnected;

                ReportAudioDeviceConnectedStatus(_module_, _params_);
            }

            // Event: 'reportAudioStatusEvent' - Triggered when CEC <Report Audio Status> message of device is received
            static void ReportAudioStatusEvent(const JSONRPC& _module_, const JsonData::HdmiCecSink::ReportAudioStatusEventParamsData& params)
            {
                _module_.Notify(_T("reportAudioStatusEvent"), params);
            }

            // Event: 'reportAudioStatusEvent' - Triggered when CEC <Report Audio Status> message of device is received
            static void ReportAudioStatusEvent(const JSONRPC& _module_, const Core::JSON::DecSInt32& muteStatus, const Core::JSON::DecSInt32& volumeLevel)
            {
                JsonData::HdmiCecSink::ReportAudioStatusEventParamsData _params_;
                _params_.MuteStatus = muteStatus;
                _params_.VolumeLevel = volumeLevel;

                ReportAudioStatusEvent(_module_, _params_);
            }

            // Event: 'reportAudioStatusEvent' - Triggered when CEC <Report Audio Status> message of device is received
            static void ReportAudioStatusEvent(const JSONRPC& _module_, const int32_t& muteStatus, const int32_t& volumeLevel)
            {
                JsonData::HdmiCecSink::ReportAudioStatusEventParamsData _params_;
                _params_.MuteStatus = muteStatus;
                _params_.VolumeLevel = volumeLevel;

                ReportAudioStatusEvent(_module_, _params_);
            }

            // Event: 'reportFeatureAbortEvent' - Triggered when CEC <Feature Abort> message of device is received
            static void ReportFeatureAbortEvent(const JSONRPC& _module_, const JsonData::HdmiCecSink::ReportFeatureAbortEventParamsData& params)
            {
                _module_.Notify(_T("reportFeatureAbortEvent"), params);
            }

            // Event: 'reportFeatureAbortEvent' - Triggered when CEC <Feature Abort> message of device is received
            static void ReportFeatureAbortEvent(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress, const Core::JSON::DecSInt32& opcode,
                     const Core::JSON::DecSInt32& FeatureAbortReason)
            {
                JsonData::HdmiCecSink::ReportFeatureAbortEventParamsData _params_;
                _params_.LogicalAddress = logicalAddress;
                _params_.Opcode = opcode;
                _params_.FeatureAbortReason = FeatureAbortReason;

                ReportFeatureAbortEvent(_module_, _params_);
            }

            // Event: 'reportFeatureAbortEvent' - Triggered when CEC <Feature Abort> message of device is received
            static void ReportFeatureAbortEvent(const JSONRPC& _module_, const int32_t& logicalAddress, const int32_t& opcode,
                     const int32_t& FeatureAbortReason)
            {
                JsonData::HdmiCecSink::ReportFeatureAbortEventParamsData _params_;
                _params_.LogicalAddress = logicalAddress;
                _params_.Opcode = opcode;
                _params_.FeatureAbortReason = FeatureAbortReason;

                ReportFeatureAbortEvent(_module_, _params_);
            }

            // Event: 'reportCecEnabledEvent' - Triggered when the HDMI-CEC is enabled
            static void ReportCecEnabledEvent(const JSONRPC& _module_, const JsonData::HdmiCecSink::ReportCecEnabledEventParamsData& params)
            {
                _module_.Notify(_T("reportCecEnabledEvent"), params);
            }

            // Event: 'reportCecEnabledEvent' - Triggered when the HDMI-CEC is enabled
            static void ReportCecEnabledEvent(const JSONRPC& _module_, const Core::JSON::String& cecEnable)
            {
                JsonData::HdmiCecSink::ReportCecEnabledEventParamsData _params_;
                _params_.CecEnable = cecEnable;

                ReportCecEnabledEvent(_module_, _params_);
            }

            // Event: 'reportCecEnabledEvent' - Triggered when the HDMI-CEC is enabled
            static void ReportCecEnabledEvent(const JSONRPC& _module_, const string& cecEnable)
            {
                JsonData::HdmiCecSink::ReportCecEnabledEventParamsData _params_;
                _params_.CecEnable = cecEnable;

                ReportCecEnabledEvent(_module_, _params_);
            }

            // Event: 'setSystemAudioModeEvent' - Triggered when CEC <Set System Audio Mode> message of device is received
            static void SetSystemAudioModeEvent(const JSONRPC& _module_, const JsonData::HdmiCecSink::SetSystemAudioModeEventParamsData& params)
            {
                _module_.Notify(_T("setSystemAudioModeEvent"), params);
            }

            // Event: 'setSystemAudioModeEvent' - Triggered when CEC <Set System Audio Mode> message of device is received
            static void SetSystemAudioModeEvent(const JSONRPC& _module_, const Core::JSON::String& audioMode)
            {
                JsonData::HdmiCecSink::SetSystemAudioModeEventParamsData _params_;
                _params_.AudioMode = audioMode;

                SetSystemAudioModeEvent(_module_, _params_);
            }

            // Event: 'setSystemAudioModeEvent' - Triggered when CEC <Set System Audio Mode> message of device is received
            static void SetSystemAudioModeEvent(const JSONRPC& _module_, const string& audioMode)
            {
                JsonData::HdmiCecSink::SetSystemAudioModeEventParamsData _params_;
                _params_.AudioMode = audioMode;

                SetSystemAudioModeEvent(_module_, _params_);
            }

            // Event: 'shortAudiodescriptorEvent' - Triggered when SAD is received from the connected audio device
            static void ShortAudiodescriptorEvent(const JSONRPC& _module_, const JsonData::HdmiCecSink::ShortAudiodescriptorEventParamsData& params)
            {
                _module_.Notify(_T("shortAudiodescriptorEvent"), params);
            }

            // Event: 'shortAudiodescriptorEvent' - Triggered when SAD is received from the connected audio device
            static void ShortAudiodescriptorEvent(const JSONRPC& _module_, const Core::JSON::String& shortAudioDescriptor)
            {
                JsonData::HdmiCecSink::ShortAudiodescriptorEventParamsData _params_;
                _params_.ShortAudioDescriptor = shortAudioDescriptor;

                ShortAudiodescriptorEvent(_module_, _params_);
            }

            // Event: 'shortAudiodescriptorEvent' - Triggered when SAD is received from the connected audio device
            static void ShortAudiodescriptorEvent(const JSONRPC& _module_, const string& shortAudioDescriptor)
            {
                JsonData::HdmiCecSink::ShortAudiodescriptorEventParamsData _params_;
                _params_.ShortAudioDescriptor = shortAudioDescriptor;

                ShortAudiodescriptorEvent(_module_, _params_);
            }

            // Event: 'standbyMessageReceived' - Triggered when the source device changes status to STANDBY
            static void StandbyMessageReceived(const JSONRPC& _module_, const JsonData::HdmiCecSink::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("standbyMessageReceived"), params);
            }

            // Event: 'standbyMessageReceived' - Triggered when the source device changes status to STANDBY
            static void StandbyMessageReceived(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                StandbyMessageReceived(_module_, _params_);
            }

            // Event: 'standbyMessageReceived' - Triggered when the source device changes status to STANDBY
            static void StandbyMessageReceived(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSink::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                StandbyMessageReceived(_module_, _params_);
            }

            // Event: 'reportAudioDevicePowerStatus' - Triggered when the source device changes
            static void ReportAudioDevicePowerStatus(const JSONRPC& _module_, const JsonData::HdmiCecSink::ReportAudioDevicePowerStatusParamsData& params)
            {
                _module_.Notify(_T("reportAudioDevicePowerStatus"), params);
            }

            // Event: 'reportAudioDevicePowerStatus' - Triggered when the source device changes
            static void ReportAudioDevicePowerStatus(const JSONRPC& _module_, const Core::JSON::DecSInt32& powerStatus)
            {
                JsonData::HdmiCecSink::ReportAudioDevicePowerStatusParamsData _params_;
                _params_.PowerStatus = powerStatus;

                ReportAudioDevicePowerStatus(_module_, _params_);
            }

            // Event: 'reportAudioDevicePowerStatus' - Triggered when the source device changes
            static void ReportAudioDevicePowerStatus(const JSONRPC& _module_, const int32_t& powerStatus)
            {
                JsonData::HdmiCecSink::ReportAudioDevicePowerStatusParamsData _params_;
                _params_.PowerStatus = powerStatus;

                ReportAudioDevicePowerStatus(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JHdmiCecSink

} // namespace Exchange

} // namespace WPEFramework

