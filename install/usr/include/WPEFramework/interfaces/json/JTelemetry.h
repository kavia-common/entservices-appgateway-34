// Generated automatically from 'ITelemetry.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_Telemetry.h"
#include <interfaces/ITelemetry.h>

namespace WPEFramework {

namespace Exchange {

    namespace JTelemetry {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ITelemetry* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JTelemetry"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setReportProfileStatus' - Sets the status of telemetry reporting
            _module_.Register<JsonData::Telemetry::SetReportProfileStatusParamsData, void>(_T("setReportProfileStatus"), 
                [_impl_](const JsonData::Telemetry::SetReportProfileStatusParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _status{params.Status};

                    _errorCode = _impl_->SetReportProfileStatus(_status);

                    return (_errorCode);
                });

            // Method: 'logApplicationEvent' - Logs an application
            _module_.Register<JsonData::Telemetry::LogApplicationEventParamsData, void>(_T("logApplicationEvent"), 
                [_impl_](const JsonData::Telemetry::LogApplicationEventParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _eventName{params.EventName};
                    const string _eventValue{params.EventValue};

                    _errorCode = _impl_->LogApplicationEvent(_eventName, _eventValue);

                    return (_errorCode);
                });

            // Method: 'uploadReport' - Uploading of telemetry report
            _module_.Register<void, void>(_T("uploadReport"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->UploadReport();

                    return (_errorCode);
                });

            // Method: 'abortReport' - Abort report upload
            _module_.Register<void, void>(_T("abortReport"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->AbortReport();

                    return (_errorCode);
                });

            // Method: 'setOptOutTelemetry' - Sets the telemetry opt-out status
            _module_.Register<JsonData::Telemetry::SetOptOutTelemetryParamsData, JsonData::Telemetry::TelemetrySuccessData>(_T("setOptOutTelemetry"), 
                [_impl_](const JsonData::Telemetry::SetOptOutTelemetryParamsData& params,
                         JsonData::Telemetry::TelemetrySuccessData& successResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const bool _optOut{params.OptOut};
                    Exchange::ITelemetry::TelemetrySuccess _successResult{};

                    _errorCode = _impl_->SetOptOutTelemetry(_optOut, _successResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        successResult = _successResult;
                    }

                    return (_errorCode);
                });

            // Method: 'isOptOutTelemetry' - Checks the telemetry opt-out status
            _module_.Register<void, JsonData::Telemetry::IsOptOutTelemetryResultData>(_T("isOptOutTelemetry"), 
                [_impl_](JsonData::Telemetry::IsOptOutTelemetryResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    bool _optOut{};
                    bool _success{};

                    _errorCode = _impl_->IsOptOutTelemetry(_optOut, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.OptOut = _optOut;
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setReportProfileStatus"));
            _module_.Unregister(_T("logApplicationEvent"));
            _module_.Unregister(_T("uploadReport"));
            _module_.Unregister(_T("abortReport"));
            _module_.Unregister(_T("setOptOutTelemetry"));
            _module_.Unregister(_T("isOptOutTelemetry"));
        }

        namespace Event {

            // Event: 'onReportUpload' - Triggered by callback from Telemetry after report uploading
            static void OnReportUpload(const JSONRPC& _module_, const JsonData::Telemetry::OnReportUploadParamsData& params)
            {
                _module_.Notify(_T("onReportUpload"), params);
            }

            // Event: 'onReportUpload' - Triggered by callback from Telemetry after report uploading
            static void OnReportUpload(const JSONRPC& _module_, const Core::JSON::String& telemetryUploadStatus)
            {
                JsonData::Telemetry::OnReportUploadParamsData _params_;
                _params_.TelemetryUploadStatus = telemetryUploadStatus;

                OnReportUpload(_module_, _params_);
            }

            // Event: 'onReportUpload' - Triggered by callback from Telemetry after report uploading
            static void OnReportUpload(const JSONRPC& _module_, const string& telemetryUploadStatus)
            {
                JsonData::Telemetry::OnReportUploadParamsData _params_;
                _params_.TelemetryUploadStatus = telemetryUploadStatus;

                OnReportUpload(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JTelemetry

} // namespace Exchange

} // namespace WPEFramework

