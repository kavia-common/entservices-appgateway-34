// C++ classes for Analytics API JSON-RPC API.
// Generated automatically from 'IAnalytics.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAnalytics.h>

namespace WPEFramework {

namespace JsonData {

    namespace Analytics {

        // Common classes
        //

        class SendEventParamsInfo : public Core::JSON::Container {
        public:
            SendEventParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("eventName"), &EventName);
                Add(_T("eventVersion"), &EventVersion);
                Add(_T("eventSource"), &EventSource);
                Add(_T("eventSourceVersion"), &EventSourceVersion);
                Add(_T("cetList"), &CetList);
                Add(_T("epochTimestamp"), &EpochTimestamp);
                Add(_T("uptimeTimestamp"), &UptimeTimestamp);
                Add(_T("appId"), &AppId);
                Add(_T("eventPayload"), &EventPayload);
                Add(_T("additionalContext"), &AdditionalContext);
                AdditionalContext.SetQuoted(false);
            }

            bool IsValid() const
            {
                return (true);
            }

            SendEventParamsInfo(const SendEventParamsInfo&) = delete;
            SendEventParamsInfo& operator=(const SendEventParamsInfo&) = delete;

        public:
            Core::JSON::String EventName; // Name of the event
            Core::JSON::String EventVersion; // Version of the event
            Core::JSON::String EventSource; // Source of the event
            Core::JSON::String EventSourceVersion; // Version of the event source
            Core::JSON::ArrayType<Core::JSON::String> CetList; // List of CETs
            Core::JSON::DecUInt64 EpochTimestamp; // Epoch timestamp of the event
            Core::JSON::DecUInt64 UptimeTimestamp; // Uptime timestamp of the event
            Core::JSON::String AppId; // Durable App Id string
            Core::JSON::String EventPayload; // Payload of the event
            Core::JSON::String AdditionalContext; // Additional context for the event
        }; // class SendEventParamsInfo

        // Method params/result classes
        //

    } // namespace Analytics

} // namespace JsonData

}

