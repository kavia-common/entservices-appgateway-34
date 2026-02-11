// Generated automatically from 'IWarehouse.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_Warehouse.h"
#include <interfaces/IWarehouse.h>

namespace WPEFramework {

namespace Exchange {

    namespace JWarehouse {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IWarehouse* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JWarehouse"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'executeHardwareTest' - Starts a hardware test on the device
            _module_.Register<void, JsonData::Warehouse::WarehouseSuccessData>(_T("executeHardwareTest"), 
                [_impl_](JsonData::Warehouse::WarehouseSuccessData& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IWarehouse::WarehouseSuccess _success{};

                    _errorCode = _impl_->ExecuteHardwareTest(_success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getHardwareTestResults' - Returns the results of the last hardware test
            _module_.Register<void, JsonData::Warehouse::GetHardwareTestResultsResultData>(_T("getHardwareTestResults"), 
                [_impl_](JsonData::Warehouse::GetHardwareTestResultsResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _success{};
                    string _testResults{};

                    _errorCode = _impl_->GetHardwareTestResults(_success, _testResults);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.TestResults = _testResults;
                    }

                    return (_errorCode);
                });

            // Method: 'internalReset' - Invokes the internal reset script, which reboots the Warehouse service
            _module_.Register<JsonData::Warehouse::InternalResetParamsData, JsonData::Warehouse::WarehouseSuccessErrInfo>(_T("internalReset"), 
                [_impl_](const JsonData::Warehouse::InternalResetParamsData& params, JsonData::Warehouse::WarehouseSuccessErrInfo& successErr) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _passPhrase{params.PassPhrase};
                    Exchange::IWarehouse::WarehouseSuccessErr _successErr{};

                    _errorCode = _impl_->InternalReset(_passPhrase, _successErr);

                    if (_errorCode == Core::ERROR_NONE) {
                        successErr = _successErr;
                    }

                    return (_errorCode);
                });

            // Method: 'isClean' - Checks the locations on the device where customer data may be stored
            _module_.Register<JsonData::Warehouse::IsCleanParamsData, JsonData::Warehouse::IsCleanResultData>(_T("isClean"), 
                [_impl_](const JsonData::Warehouse::IsCleanParamsData& params, JsonData::Warehouse::IsCleanResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const int32_t _age{params.Age};
                    bool _clean{};
                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _files{};
                    bool _success{};
                    string _error{};

                    _errorCode = _impl_->IsClean(_age, _clean, _files, _success, _error);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Clean = _clean;

                        if (_files != nullptr) {
                            string _filesItem_{};
                            while (_files->Next(_filesItem_) == true) { result.Files.Add() = _filesItem_; }
                            _files->Release();
                        }
                        result.Success = _success;
                        result.Error = _error;
                    }

                    return (_errorCode);
                });

            // Method: 'lightReset' - Resets the application data
            _module_.Register<void, JsonData::Warehouse::WarehouseSuccessErrInfo>(_T("lightReset"), 
                [_impl_](JsonData::Warehouse::WarehouseSuccessErrInfo& successErr) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IWarehouse::WarehouseSuccessErr _successErr{};

                    _errorCode = _impl_->LightReset(_successErr);

                    if (_errorCode == Core::ERROR_NONE) {
                        successErr = _successErr;
                    }

                    return (_errorCode);
                });

            // Method: 'resetDevice' - Resets the STB to the warehouse state
            _module_.Register<JsonData::Warehouse::ResetDeviceParamsData, JsonData::Warehouse::WarehouseSuccessErrInfo>(_T("resetDevice"), 
                [_impl_](const JsonData::Warehouse::ResetDeviceParamsData& params, JsonData::Warehouse::WarehouseSuccessErrInfo& successErr) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _suppressReboot{params.SuppressReboot};
                    const string _resetType{params.ResetType};
                    Exchange::IWarehouse::WarehouseSuccessErr _successErr{};

                    _errorCode = _impl_->ResetDevice(_suppressReboot, _resetType, _successErr);

                    if (_errorCode == Core::ERROR_NONE) {
                        successErr = _successErr;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("executeHardwareTest"));
            _module_.Unregister(_T("getHardwareTestResults"));
            _module_.Unregister(_T("internalReset"));
            _module_.Unregister(_T("isClean"));
            _module_.Unregister(_T("lightReset"));
            _module_.Unregister(_T("resetDevice"));
        }

        namespace Event {

            // Event: 'resetDone' - Notifies subscribers about the status of the warehouse reset operation
            static void ResetDone(const JSONRPC& _module_, const JsonData::Warehouse::WarehouseSuccessErrInfo& params)
            {
                _module_.Notify(_T("resetDone"), params);
            }

            // Event: 'resetDone' - Notifies subscribers about the status of the warehouse reset operation
            static void ResetDone(const JSONRPC& _module_, const Core::JSON::Boolean& success, const Core::JSON::String& error)
            {
                JsonData::Warehouse::WarehouseSuccessErrInfo _params_;
                _params_.Success = success;
                _params_.Error = error;

                ResetDone(_module_, _params_);
            }

            // Event: 'resetDone' - Notifies subscribers about the status of the warehouse reset operation
            static void ResetDone(const JSONRPC& _module_, const bool& success, const string& error)
            {
                JsonData::Warehouse::WarehouseSuccessErrInfo _params_;
                _params_.Success = success;
                _params_.Error = error;

                ResetDone(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JWarehouse

} // namespace Exchange

} // namespace WPEFramework

