// C++ classes for HomeKitTV API JSON-RPC API.
// Generated automatically from 'HomeKitTV.json'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>

namespace WPEFramework {

namespace JsonData {

    namespace HomeKitTVJSONRPC {

        // Common classes
        //

        class SetCurrentInputSourceResultInfo : public Core::JSON::Container {
        public:
            SetCurrentInputSourceResultInfo()
                : Core::JSON::Container()
            {
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetCurrentInputSourceResultInfo(const SetCurrentInputSourceResultInfo&) = delete;
            SetCurrentInputSourceResultInfo& operator=(const SetCurrentInputSourceResultInfo&) = delete;

        public:
            Core::JSON::Boolean Success; // Request Airplay to set the current Input-Source
        }; // class SetCurrentInputSourceResultInfo

        // Method params/result classes
        //

        class GetConnectionStatusResultData : public Core::JSON::Container {
        public:
            GetConnectionStatusResultData()
                : Core::JSON::Container()
            {
                Add(_T("paired"), &Paired);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetConnectionStatusResultData(const GetConnectionStatusResultData&) = delete;
            GetConnectionStatusResultData& operator=(const GetConnectionStatusResultData&) = delete;

        public:
            Core::JSON::Boolean Paired; // Request whether the AirPlay capable Apple companion device is paired (true) or unpaired (false) with this HomeKit Television Accessory device.
            Core::JSON::Boolean Success; // Request whether the AirPlay capable Apple companion device is paired (true) or unpaired (false) with this HomeKit Television Accessory device.
        }; // class GetConnectionStatusResultData

        class GetEnabledStatusResultData : public Core::JSON::Container {
        public:
            GetEnabledStatusResultData()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetEnabledStatusResultData(const GetEnabledStatusResultData&) = delete;
            GetEnabledStatusResultData& operator=(const GetEnabledStatusResultData&) = delete;

        public:
            Core::JSON::Boolean Enabled; // Return the status of Airplay On/Off
            Core::JSON::Boolean Success; // Return the status of Airplay On/Off
        }; // class GetEnabledStatusResultData

        class OnAppStateChangeRequestParamsData : public Core::JSON::Container {
        public:
            class IntentData : public Core::JSON::Container {
            public:
                class SectionNameData : public Core::JSON::Container {
                public:
                    SectionNameData()
                        : Core::JSON::Container()
                    {
                        Add(_T("sectionName"), &SectionName);
                    }

                    bool IsValid() const
                    {
                        return (true);
                    }

                    SectionNameData(const SectionNameData&) = delete;
                    SectionNameData& operator=(const SectionNameData&) = delete;

                public:
                    Core::JSON::String SectionName; // String representing launch parameters
                }; // class SectionNameData

                class SourceData : public Core::JSON::Container {
                public:
                    SourceData()
                        : Core::JSON::Container()
                    {
                        Add(_T("source"), &Source);
                    }

                    bool IsValid() const
                    {
                        return (true);
                    }

                    SourceData(const SourceData&) = delete;
                    SourceData& operator=(const SourceData&) = delete;

                public:
                    Core::JSON::String Source; // String representing the reason for triggering the section
                }; // class SourceData

                IntentData()
                    : Core::JSON::Container()
                {
                    Add(_T("action"), &Action);
                    Add(_T("data"), &Data);
                    Add(_T("context"), &Context);
                }

                bool IsValid() const
                {
                    return (true);
                }

                IntentData(const IntentData&) = delete;
                IntentData& operator=(const IntentData&) = delete;

            public:
                Core::JSON::String Action; // Intent action
                OnAppStateChangeRequestParamsData::IntentData::SectionNameData Data; // Intent's data
                OnAppStateChangeRequestParamsData::IntentData::SourceData Context; // App State Change Intent Context Object
            }; // class IntentData

            OnAppStateChangeRequestParamsData()
                : Core::JSON::Container()
            {
                Add(_T("origin"), &Origin);
                Add(_T("intent"), &Intent);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppStateChangeRequestParamsData(const OnAppStateChangeRequestParamsData&) = delete;
            OnAppStateChangeRequestParamsData& operator=(const OnAppStateChangeRequestParamsData&) = delete;

        public:
            Core::JSON::String Origin; // Origin of app state change request
            OnAppStateChangeRequestParamsData::IntentData Intent; // App State change intent object
        }; // class OnAppStateChangeRequestParamsData

        class OnConnectionStatusChangedParamsData : public Core::JSON::Container {
        public:
            OnConnectionStatusChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("paired"), &Paired);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnConnectionStatusChangedParamsData(const OnConnectionStatusChangedParamsData&) = delete;
            OnConnectionStatusChangedParamsData& operator=(const OnConnectionStatusChangedParamsData&) = delete;

        public:
            Core::JSON::Boolean Paired; // HomeKit Pairing status
        }; // class OnConnectionStatusChangedParamsData

        class OnEnabledStatusChangedParamsData : public Core::JSON::Container {
        public:
            OnEnabledStatusChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnEnabledStatusChangedParamsData(const OnEnabledStatusChangedParamsData&) = delete;
            OnEnabledStatusChangedParamsData& operator=(const OnEnabledStatusChangedParamsData&) = delete;

        public:
            Core::JSON::Boolean Enabled; // Airplay setting status changed between On or Off
        }; // class OnEnabledStatusChangedParamsData

        class OnInputSourceChangedParamsData : public Core::JSON::Container {
        public:
            OnInputSourceChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sourceType"), &SourceType);
                Add(_T("portId"), &PortId);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnInputSourceChangedParamsData(const OnInputSourceChangedParamsData&) = delete;
            OnInputSourceChangedParamsData& operator=(const OnInputSourceChangedParamsData&) = delete;

        public:
            Core::JSON::String SourceType; // Type of inputsource hdmi, composite, Airplay
            Core::JSON::DecUInt32 PortId; // Port ID of Input source
        }; // class OnInputSourceChangedParamsData

        class OnairplayerrorParamsData : public Core::JSON::Container {
        public:
            OnairplayerrorParamsData()
                : Core::JSON::Container()
            {
                Add(_T("errordata"), &Errordata);
                Add(_T("errorid"), &Errorid);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnairplayerrorParamsData(const OnairplayerrorParamsData&) = delete;
            OnairplayerrorParamsData& operator=(const OnairplayerrorParamsData&) = delete;

        public:
            Core::JSON::String Errordata; // Details of the failure
            Core::JSON::DecUInt32 Errorid; // Failure code
        }; // class OnairplayerrorParamsData

        class RequestAppLaunchParamsData : public Core::JSON::Container {
        public:
            RequestAppLaunchParamsData()
                : Core::JSON::Container()
            {
                Add(_T("origin"), &Origin);
                Add(_T("reason"), &Reason);
            }

            bool IsValid() const
            {
                return (true);
            }

            RequestAppLaunchParamsData(const RequestAppLaunchParamsData&) = delete;
            RequestAppLaunchParamsData& operator=(const RequestAppLaunchParamsData&) = delete;

        public:
            Core::JSON::String Origin; // Origin of the launch Request
            Core::JSON::String Reason; // Reason to request Airplay app UI, e.g., to display Airplay curtain page or Airlay & HomeKit settings
        }; // class RequestAppLaunchParamsData

        class SetAppContainerIPAddressData : public Core::JSON::Container {
        public:
            SetAppContainerIPAddressData()
                : Core::JSON::Container()
            {
                Add(_T("ipaddress"), &Ipaddress);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetAppContainerIPAddressData(const SetAppContainerIPAddressData&) = delete;
            SetAppContainerIPAddressData& operator=(const SetAppContainerIPAddressData&) = delete;

        public:
            Core::JSON::String Ipaddress; // IP Address of Application container
        }; // class SetAppContainerIPAddressData

        class SetCurrentInputSourceParamsData : public Core::JSON::Container {
        public:
            SetCurrentInputSourceParamsData()
                : Core::JSON::Container()
            {
                Add(_T("sourceName"), &SourceName);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetCurrentInputSourceParamsData(const SetCurrentInputSourceParamsData&) = delete;
            SetCurrentInputSourceParamsData& operator=(const SetCurrentInputSourceParamsData&) = delete;

        public:
            Core::JSON::String SourceName; // Selected Input-Source using IR Remote.
        }; // class SetCurrentInputSourceParamsData

    } // namespace HomeKitTVJSONRPC

} // namespace JsonData

}

