// Generated automatically from 'IHdmiCecSource.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_HdmiCecSource.h"
#include <interfaces/IHdmiCecSource.h>

namespace WPEFramework {

namespace Exchange {

    namespace JHdmiCecSource {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IHdmiCecSource* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JHdmiCecSource"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getActiveSourceStatus' - Gets the status if the device is the current active source
            _module_.Register<void, JsonData::HdmiCecSource::GetActiveSourceStatusResultData>(_T("getActiveSourceStatus"), 
                [_impl_](JsonData::HdmiCecSource::GetActiveSourceStatusResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _status{};
                    bool _success{};

                    _errorCode = _impl_->GetActiveSourceStatus(_status, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Status = _status;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getEnabled' - Gets the status of the HDMI CEC source
            _module_.Register<void, JsonData::HdmiCecSource::GetEnabledResultInfo>(_T("getEnabled"), 
                [_impl_](JsonData::HdmiCecSource::GetEnabledResultInfo& result) -> uint32_t {
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

            // Method: 'getOSDName' - Gets the OSD name of the HDMI CEC source
            _module_.Register<void, JsonData::HdmiCecSource::GetOSDNameResultData>(_T("getOSDName"), 
                [_impl_](JsonData::HdmiCecSource::GetOSDNameResultData& result) -> uint32_t {
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

            // Method: 'getOTPEnabled' - Gets the OTP enabled status of the HDMI CEC source
            _module_.Register<void, JsonData::HdmiCecSource::GetEnabledResultInfo>(_T("getOTPEnabled"), 
                [_impl_](JsonData::HdmiCecSource::GetEnabledResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _enabled{};
                    bool _success{};

                    _errorCode = _impl_->GetOTPEnabled(_enabled, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Enabled = _enabled;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getVendorId' - Gets the vendor ID of the HDMI CEC source
            _module_.Register<void, JsonData::HdmiCecSource::GetVendorIdResultData>(_T("getVendorId"), 
                [_impl_](JsonData::HdmiCecSource::GetVendorIdResultData& result) -> uint32_t {
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

            // Method: 'performOTPAction' - Performs the OTP action
            _module_.Register<void, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo>(_T("performOTPAction"), 
                [_impl_](JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSource::HdmiCecSourceSuccess _success{};

                    _errorCode = _impl_->PerformOTPAction(_success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'sendKeyPressEvent' - Sends a key press event to the HDMI CEC device
            _module_.Register<JsonData::HdmiCecSource::SendKeyPressEventParamsData, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo>(_T("sendKeyPressEvent"), 
                [_impl_](const JsonData::HdmiCecSource::SendKeyPressEventParamsData& params,
                         JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _logicalAddress{params.LogicalAddress};
                    const uint32_t _keyCode{params.KeyCode};
                    Exchange::IHdmiCecSource::HdmiCecSourceSuccess _success{};

                    _errorCode = _impl_->SendKeyPressEvent(_logicalAddress, _keyCode, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'sendStandbyMessage' - Sends a standby message to another CEC device
            _module_.Register<void, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo>(_T("sendStandbyMessage"), 
                [_impl_](JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IHdmiCecSource::HdmiCecSourceSuccess _success{};

                    _errorCode = _impl_->SendStandbyMessage(_success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setEnabled' - Sets the status of the HDMI CEC source
            _module_.Register<JsonData::HdmiCecSource::SetEnabledParamsInfo, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo>(_T("setEnabled"), 
                [_impl_](const JsonData::HdmiCecSource::SetEnabledParamsInfo& params, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};
                    Exchange::IHdmiCecSource::HdmiCecSourceSuccess _success{};

                    _errorCode = _impl_->SetEnabled(_enabled, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setOSDName' - Sets the OSD name of the HDMI CEC source
            _module_.Register<JsonData::HdmiCecSource::SetOSDNameParamsData, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo>(_T("setOSDName"), 
                [_impl_](const JsonData::HdmiCecSource::SetOSDNameParamsData& params, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _name{params.Name};
                    Exchange::IHdmiCecSource::HdmiCecSourceSuccess _success{};

                    _errorCode = _impl_->SetOSDName(_name, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setOTPEnabled' - Sets the OTP enabled status of the HDMI CEC source
            _module_.Register<JsonData::HdmiCecSource::SetEnabledParamsInfo, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo>(_T("setOTPEnabled"), 
                [_impl_](const JsonData::HdmiCecSource::SetEnabledParamsInfo& params, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _enabled{params.Enabled};
                    Exchange::IHdmiCecSource::HdmiCecSourceSuccess _success{};

                    _errorCode = _impl_->SetOTPEnabled(_enabled, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'setVendorId' - Sets the vendor ID of the HDMI CEC source
            _module_.Register<JsonData::HdmiCecSource::SetVendorIdParamsData, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo>(_T("setVendorId"), 
                [_impl_](const JsonData::HdmiCecSource::SetVendorIdParamsData& params, JsonData::HdmiCecSource::HdmiCecSourceSuccessInfo& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _vendorid{params.Vendorid};
                    Exchange::IHdmiCecSource::HdmiCecSourceSuccess _success{};

                    _errorCode = _impl_->SetVendorId(_vendorid, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getDeviceList' - Gets the list of devices connected to the HDMI CEC source
            _module_.Register<void, JsonData::HdmiCecSource::GetDeviceListResultData>(_T("getDeviceList"), 
                [_impl_](JsonData::HdmiCecSource::GetDeviceListResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    uint32_t _numberofdevices{};
                    ::WPEFramework::RPC::IIteratorType<IHdmiCecSource::HdmiCecSourceDevices, ID_HDMI_CEC_SOURCE_DEVICE_LIST_ITERATOR>* _deviceList{};
                    bool _success{};

                    _errorCode = _impl_->GetDeviceList(_numberofdevices, _deviceList, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Numberofdevices = _numberofdevices;

                        if (_deviceList != nullptr) {
                            Exchange::IHdmiCecSource::HdmiCecSourceDevices _deviceListItem_{};
                            while (_deviceList->Next(_deviceListItem_) == true) { result.DeviceList.Add() = _deviceListItem_; }
                            _deviceList->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getActiveSourceStatus"));
            _module_.Unregister(_T("getEnabled"));
            _module_.Unregister(_T("getOSDName"));
            _module_.Unregister(_T("getOTPEnabled"));
            _module_.Unregister(_T("getVendorId"));
            _module_.Unregister(_T("performOTPAction"));
            _module_.Unregister(_T("sendKeyPressEvent"));
            _module_.Unregister(_T("sendStandbyMessage"));
            _module_.Unregister(_T("setEnabled"));
            _module_.Unregister(_T("setOSDName"));
            _module_.Unregister(_T("setOTPEnabled"));
            _module_.Unregister(_T("setVendorId"));
            _module_.Unregister(_T("getDeviceList"));
        }

        namespace Event {

            // Event: 'onDeviceAdded' - Notifies when CEC device added to CEC network
            static void OnDeviceAdded(const JSONRPC& _module_, const JsonData::HdmiCecSource::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onDeviceAdded"), params);
            }

            // Event: 'onDeviceAdded' - Notifies when CEC device added to CEC network
            static void OnDeviceAdded(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceAdded(_module_, _params_);
            }

            // Event: 'onDeviceAdded' - Notifies when CEC device added to CEC network
            static void OnDeviceAdded(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceAdded(_module_, _params_);
            }

            // Event: 'onDeviceRemoved' - Notifies when CEC device removed from CEC network
            static void OnDeviceRemoved(const JSONRPC& _module_, const JsonData::HdmiCecSource::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onDeviceRemoved"), params);
            }

            // Event: 'onDeviceRemoved' - Notifies when CEC device removed from CEC network
            static void OnDeviceRemoved(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceRemoved(_module_, _params_);
            }

            // Event: 'onDeviceRemoved' - Notifies when CEC device removed from CEC network
            static void OnDeviceRemoved(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceRemoved(_module_, _params_);
            }

            // Event: 'onDeviceInfoUpdated' - Notifies when CEC device info updated
            static void OnDeviceInfoUpdated(const JSONRPC& _module_, const JsonData::HdmiCecSource::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onDeviceInfoUpdated"), params);
            }

            // Event: 'onDeviceInfoUpdated' - Notifies when CEC device info updated
            static void OnDeviceInfoUpdated(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceInfoUpdated(_module_, _params_);
            }

            // Event: 'onDeviceInfoUpdated' - Notifies when CEC device info updated
            static void OnDeviceInfoUpdated(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnDeviceInfoUpdated(_module_, _params_);
            }

            // Event: 'onActiveSourceStatusUpdated' - Notifies when the active source status is updated
            static void OnActiveSourceStatusUpdated(const JSONRPC& _module_, const JsonData::HdmiCecSource::OnActiveSourceStatusUpdatedParamsData& params)
            {
                _module_.Notify(_T("onActiveSourceStatusUpdated"), params);
            }

            // Event: 'onActiveSourceStatusUpdated' - Notifies when the active source status is updated
            static void OnActiveSourceStatusUpdated(const JSONRPC& _module_, const Core::JSON::Boolean& status)
            {
                JsonData::HdmiCecSource::OnActiveSourceStatusUpdatedParamsData _params_;
                _params_.Status = status;

                OnActiveSourceStatusUpdated(_module_, _params_);
            }

            // Event: 'onActiveSourceStatusUpdated' - Notifies when the active source status is updated
            static void OnActiveSourceStatusUpdated(const JSONRPC& _module_, const bool& status)
            {
                JsonData::HdmiCecSource::OnActiveSourceStatusUpdatedParamsData _params_;
                _params_.Status = status;

                OnActiveSourceStatusUpdated(_module_, _params_);
            }

            // Event: 'standbyMessageReceived' - Notifies when CEC standby message received from the other CEC device
            static void StandbyMessageReceived(const JSONRPC& _module_, const JsonData::HdmiCecSource::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("standbyMessageReceived"), params);
            }

            // Event: 'standbyMessageReceived' - Notifies when CEC standby message received from the other CEC device
            static void StandbyMessageReceived(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                StandbyMessageReceived(_module_, _params_);
            }

            // Event: 'standbyMessageReceived' - Notifies when CEC standby message received from the other CEC device
            static void StandbyMessageReceived(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                StandbyMessageReceived(_module_, _params_);
            }

            // Event: 'onKeyReleaseEvent' - Notifies when a key release CEC message is received from other CEC device
            static void OnKeyReleaseEvent(const JSONRPC& _module_, const JsonData::HdmiCecSource::OnDeviceAddedParamsInfo& params)
            {
                _module_.Notify(_T("onKeyReleaseEvent"), params);
            }

            // Event: 'onKeyReleaseEvent' - Notifies when a key release CEC message is received from other CEC device
            static void OnKeyReleaseEvent(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnKeyReleaseEvent(_module_, _params_);
            }

            // Event: 'onKeyReleaseEvent' - Notifies when a key release CEC message is received from other CEC device
            static void OnKeyReleaseEvent(const JSONRPC& _module_, const int32_t& logicalAddress)
            {
                JsonData::HdmiCecSource::OnDeviceAddedParamsInfo _params_;
                _params_.LogicalAddress = logicalAddress;

                OnKeyReleaseEvent(_module_, _params_);
            }

            // Event: 'onKeyPressEvent' - Notifies when a key press CEC message is received from other CEC device
            static void OnKeyPressEvent(const JSONRPC& _module_, const JsonData::HdmiCecSource::OnKeyPressEventParamsData& params)
            {
                _module_.Notify(_T("onKeyPressEvent"), params);
            }

            // Event: 'onKeyPressEvent' - Notifies when a key press CEC message is received from other CEC device
            static void OnKeyPressEvent(const JSONRPC& _module_, const Core::JSON::DecSInt32& logicalAddress, const Core::JSON::DecSInt32& keyCode)
            {
                JsonData::HdmiCecSource::OnKeyPressEventParamsData _params_;
                _params_.LogicalAddress = logicalAddress;
                _params_.KeyCode = keyCode;

                OnKeyPressEvent(_module_, _params_);
            }

            // Event: 'onKeyPressEvent' - Notifies when a key press CEC message is received from other CEC device
            static void OnKeyPressEvent(const JSONRPC& _module_, const int32_t& logicalAddress, const int32_t& keyCode)
            {
                JsonData::HdmiCecSource::OnKeyPressEventParamsData _params_;
                _params_.LogicalAddress = logicalAddress;
                _params_.KeyCode = keyCode;

                OnKeyPressEvent(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JHdmiCecSource

} // namespace Exchange

} // namespace WPEFramework

