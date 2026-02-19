// C++ classes for SystemMode API JSON-RPC API.
// Generated automatically from 'ISystemMode.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ISystemMode.h>

namespace WPEFramework {

namespace JsonData {

    namespace SystemMode {

        // Common classes
        //

        class ClientActivatedParamsInfo : public Core::JSON::Container {
        public:
            ClientActivatedParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("callsign"), &Callsign);
                Add(_T("systemMode"), &SystemMode);
            }

            bool IsValid() const
            {
                return (true);
            }

            ClientActivatedParamsInfo(const ClientActivatedParamsInfo&) = delete;
            ClientActivatedParamsInfo& operator=(const ClientActivatedParamsInfo&) = delete;

        public:
            Core::JSON::String Callsign; // To put client plugin entry in map.
            Core::JSON::String SystemMode; // To put client plugin entry in map.
        }; // class ClientActivatedParamsInfo

        // Method params/result classes
        //

        class GetStateParamsData : public Core::JSON::Container {
        public:
            GetStateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("systemMode"), &SystemMode);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetStateParamsData(const GetStateParamsData&) = delete;
            GetStateParamsData& operator=(const GetStateParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISystemMode::SystemMode> SystemMode; // Gets the current state for a given system property
        }; // class GetStateParamsData

        class GetStateResultData : public Core::JSON::Container {
        public:
            GetStateResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetStateResultData(const Exchange::ISystemMode::GetStateResult& _other)
                : Core::JSON::Container()
            {
                State = _other.state;
                _Init();
            }

            GetStateResultData& operator=(const Exchange::ISystemMode::GetStateResult& _rhs)
            {
                State = _rhs.state;
                return (*this);
            }

            operator Exchange::ISystemMode::GetStateResult() const
            {
                Exchange::ISystemMode::GetStateResult _value{};
                _value.state = State;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("state"), &State);
            }

        public:
            Core::JSON::EnumType<Exchange::ISystemMode::State> State; // Gets the current state for a given system property
        }; // class GetStateResultData

        class RequestStateParamsData : public Core::JSON::Container {
        public:
            RequestStateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("systemMode"), &SystemMode);
                Add(_T("state"), &State);
            }

            bool IsValid() const
            {
                return (true);
            }

            RequestStateParamsData(const RequestStateParamsData&) = delete;
            RequestStateParamsData& operator=(const RequestStateParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::ISystemMode::SystemMode> SystemMode; // Requests a new system mode state in the device.  Thunder components asynchronously reconfigure themselves so the caller cannot be guaranteed a full state transition upon return.
            Core::JSON::EnumType<Exchange::ISystemMode::State> State; // Requests a new system mode state in the device.  Thunder components asynchronously reconfigure themselves so the caller cannot be guaranteed a full state transition upon return.
        }; // class RequestStateParamsData

    } // namespace SystemMode

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ISystemMode::SystemMode)
ENUM_CONVERSION_HANDLER(Exchange::ISystemMode::State)

}

