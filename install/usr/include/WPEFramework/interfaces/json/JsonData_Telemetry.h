// C++ classes for Telemetry API JSON-RPC API.
// Generated automatically from 'ITelemetry.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ITelemetry.h>

namespace WPEFramework {

namespace JsonData {

    namespace Telemetry {

        // Method params/result classes
        //

        class IsOptOutTelemetryResultData : public Core::JSON::Container {
        public:
            IsOptOutTelemetryResultData()
                : Core::JSON::Container()
            {
                Add(_T("Opt-Out"), &OptOut);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            IsOptOutTelemetryResultData(const IsOptOutTelemetryResultData&) = delete;
            IsOptOutTelemetryResultData& operator=(const IsOptOutTelemetryResultData&) = delete;

        public:
            Core::JSON::Boolean OptOut; // Checks the telemetry opt-out status.
            Core::JSON::Boolean Success; // - out - boolean
        }; // class IsOptOutTelemetryResultData

        class LogApplicationEventParamsData : public Core::JSON::Container {
        public:
            LogApplicationEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("eventName"), &EventName);
                Add(_T("eventValue"), &EventValue);
            }

            bool IsValid() const
            {
                return (true);
            }

            LogApplicationEventParamsData(const LogApplicationEventParamsData&) = delete;
            LogApplicationEventParamsData& operator=(const LogApplicationEventParamsData&) = delete;

        public:
            Core::JSON::String EventName; // - in - string
            Core::JSON::String EventValue; // - in - string
        }; // class LogApplicationEventParamsData

        class OnReportUploadParamsData : public Core::JSON::Container {
        public:
            OnReportUploadParamsData()
                : Core::JSON::Container()
            {
                Add(_T("telemetryUploadStatus"), &TelemetryUploadStatus);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnReportUploadParamsData(const OnReportUploadParamsData&) = delete;
            OnReportUploadParamsData& operator=(const OnReportUploadParamsData&) = delete;

        public:
            Core::JSON::String TelemetryUploadStatus; // - in - string
        }; // class OnReportUploadParamsData

        class SetOptOutTelemetryParamsData : public Core::JSON::Container {
        public:
            SetOptOutTelemetryParamsData()
                : Core::JSON::Container()
            {
                Add(_T("Opt-Out"), &OptOut);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetOptOutTelemetryParamsData(const SetOptOutTelemetryParamsData&) = delete;
            SetOptOutTelemetryParamsData& operator=(const SetOptOutTelemetryParamsData&) = delete;

        public:
            Core::JSON::Boolean OptOut; // Sets the telemetry opt-out status.
        }; // class SetOptOutTelemetryParamsData

        class TelemetrySuccessData : public Core::JSON::Container {
        public:
            TelemetrySuccessData()
                : Core::JSON::Container()
            {
                _Init();
            }

            TelemetrySuccessData(const Exchange::ITelemetry::TelemetrySuccess& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            TelemetrySuccessData& operator=(const Exchange::ITelemetry::TelemetrySuccess& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::ITelemetry::TelemetrySuccess() const
            {
                Exchange::ITelemetry::TelemetrySuccess _value{};
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
            Core::JSON::Boolean Success; // Sets the telemetry opt-out status.
        }; // class TelemetrySuccessData

        class SetReportProfileStatusParamsData : public Core::JSON::Container {
        public:
            SetReportProfileStatusParamsData()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetReportProfileStatusParamsData(const SetReportProfileStatusParamsData&) = delete;
            SetReportProfileStatusParamsData& operator=(const SetReportProfileStatusParamsData&) = delete;

        public:
            Core::JSON::String Status; // - in - string
        }; // class SetReportProfileStatusParamsData

    } // namespace Telemetry

} // namespace JsonData

}

