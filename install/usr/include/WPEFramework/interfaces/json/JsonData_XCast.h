// C++ classes for XCast API JSON-RPC API.
// Generated automatically from 'IXCast.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IXCast.h>

namespace WPEFramework {

namespace JsonData {

    namespace XCast {

        // Common classes
        //

        class OnApplicationStopRequestParamsInfo : public Core::JSON::Container {
        public:
            OnApplicationStopRequestParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("applicationName"), &AppName);
                Add(_T("applicationId"), &AppID);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnApplicationStopRequestParamsInfo(const OnApplicationStopRequestParamsInfo&) = delete;
            OnApplicationStopRequestParamsInfo& operator=(const OnApplicationStopRequestParamsInfo&) = delete;

        public:
            Core::JSON::String AppName; // Triggered when the cast service receives a stop request from a client
            Core::JSON::String AppID; // Triggered when the cast service receives a stop request from a client
        }; // class OnApplicationStopRequestParamsInfo

        class XCastSuccessInfo : public Core::JSON::Container {
        public:
            XCastSuccessInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            XCastSuccessInfo(const Exchange::IXCast::XCastSuccess& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            XCastSuccessInfo& operator=(const Exchange::IXCast::XCastSuccess& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IXCast::XCastSuccess() const
            {
                Exchange::IXCast::XCastSuccess _value{};
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
            Core::JSON::Boolean Success; // true if the request was successful, false otherwise
        }; // class XCastSuccessInfo

        // Method params/result classes
        //

        class GetEnabledResultData : public Core::JSON::Container {
        public:
            GetEnabledResultData()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetEnabledResultData(const GetEnabledResultData&) = delete;
            GetEnabledResultData& operator=(const GetEnabledResultData&) = delete;

        public:
            Core::JSON::Boolean Enabled; // true for enabled or false for disabled
            Core::JSON::Boolean Success; // Whether the request succeeded
        }; // class GetEnabledResultData

        class GetFriendlyNameResultData : public Core::JSON::Container {
        public:
            GetFriendlyNameResultData()
                : Core::JSON::Container()
            {
                Add(_T("friendlyname"), &Friendlyname);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetFriendlyNameResultData(const GetFriendlyNameResultData&) = delete;
            GetFriendlyNameResultData& operator=(const GetFriendlyNameResultData&) = delete;

        public:
            Core::JSON::String Friendlyname; // The friendly name of the device which used to display on the client device list
            Core::JSON::Boolean Success; // Whether the request succeeded
        }; // class GetFriendlyNameResultData

        class GetManufacturerNameResultData : public Core::JSON::Container {
        public:
            GetManufacturerNameResultData()
                : Core::JSON::Container()
            {
                Add(_T("manufacturer"), &Manufacturername);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetManufacturerNameResultData(const GetManufacturerNameResultData&) = delete;
            GetManufacturerNameResultData& operator=(const GetManufacturerNameResultData&) = delete;

        public:
            Core::JSON::String Manufacturername; // Returns the manufacturer name set by setManufacturerName API
            Core::JSON::Boolean Success; // Whether the request succeeded
        }; // class GetManufacturerNameResultData

        class GetModelNameResultData : public Core::JSON::Container {
        public:
            GetModelNameResultData()
                : Core::JSON::Container()
            {
                Add(_T("model"), &Modelname);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetModelNameResultData(const GetModelNameResultData&) = delete;
            GetModelNameResultData& operator=(const GetModelNameResultData&) = delete;

        public:
            Core::JSON::String Modelname; // Returns the model name set by setModelName API
            Core::JSON::Boolean Success; // Whether the request succeeded
        }; // class GetModelNameResultData

        class GetProtocolVersionResultData : public Core::JSON::Container {
        public:
            GetProtocolVersionResultData()
                : Core::JSON::Container()
            {
                Add(_T("version"), &ProtocolVersion);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetProtocolVersionResultData(const GetProtocolVersionResultData&) = delete;
            GetProtocolVersionResultData& operator=(const GetProtocolVersionResultData&) = delete;

        public:
            Core::JSON::String ProtocolVersion; // Returns the DIAL protocol version supported by the server
            Core::JSON::Boolean Success; // Whether the request succeeded
        }; // class GetProtocolVersionResultData

        class GetStandbyBehaviorResultData : public Core::JSON::Container {
        public:
            GetStandbyBehaviorResultData()
                : Core::JSON::Container()
            {
                Add(_T("standbybehavior"), &Standbybehavior);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetStandbyBehaviorResultData(const GetStandbyBehaviorResultData&) = delete;
            GetStandbyBehaviorResultData& operator=(const GetStandbyBehaviorResultData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IXCast::StandbyBehavior> Standbybehavior; // whether to remain active or inactive during standby mode (must be one of the following: active, inactive)
            Core::JSON::Boolean Success; // Whether the request succeeded
        }; // class GetStandbyBehaviorResultData

        class OnApplicationLaunchRequestParamsData : public Core::JSON::Container {
        public:
            OnApplicationLaunchRequestParamsData()
                : Core::JSON::Container()
            {
                Add(_T("applicationName"), &AppName);
                Add(_T("parameter"), &Parameter);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnApplicationLaunchRequestParamsData(const OnApplicationLaunchRequestParamsData&) = delete;
            OnApplicationLaunchRequestParamsData& operator=(const OnApplicationLaunchRequestParamsData&) = delete;

        public:
            Core::JSON::String AppName; // Triggered when the cast service receives a launch request from a client with launch params
            Core::JSON::String Parameter; // Application launch string
        }; // class OnApplicationLaunchRequestParamsData

        class OnApplicationLaunchRequestWithParamParamsData : public Core::JSON::Container {
        public:
            OnApplicationLaunchRequestWithParamParamsData()
                : Core::JSON::Container()
            {
                Add(_T("applicationName"), &AppName);
                Add(_T("strPayLoad"), &StrPayLoad);
                Add(_T("strQuery"), &StrQuery);
                Add(_T("strAddDataUrl"), &StrAddDataUrl);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnApplicationLaunchRequestWithParamParamsData(const OnApplicationLaunchRequestWithParamParamsData&) = delete;
            OnApplicationLaunchRequestWithParamParamsData& operator=(const OnApplicationLaunchRequestWithParamParamsData&) = delete;

        public:
            Core::JSON::String AppName; // Triggered when the cast service receives a launch request from a client with launch params
            Core::JSON::String StrPayLoad; // Payload string to be passed to the application
            Core::JSON::String StrQuery; // Query string to be appended in launch request
            Core::JSON::String StrAddDataUrl; // Additional data URL to be passed to the application
        }; // class OnApplicationLaunchRequestWithParamParamsData

        class RegisterApplicationsParamsData : public Core::JSON::Container {
        public:
            class ApplicationInfoData : public Core::JSON::Container {
            public:
                ApplicationInfoData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                ApplicationInfoData(const ApplicationInfoData& _other)
                    : Core::JSON::Container()
                    , AppName(_other.AppName)
                    , Prefixes(_other.Prefixes)
                    , Cors(_other.Cors)
                    , Query(_other.Query)
                    , Payload(_other.Payload)
                    , AllowStop(_other.AllowStop)
                {
                    _Init();
                }

                ApplicationInfoData& operator=(const ApplicationInfoData& _rhs)
                {
                    AppName = _rhs.AppName;
                    Prefixes = _rhs.Prefixes;
                    Cors = _rhs.Cors;
                    Query = _rhs.Query;
                    Payload = _rhs.Payload;
                    AllowStop = _rhs.AllowStop;
                    return (*this);
                }

                ApplicationInfoData(const Exchange::IXCast::ApplicationInfo& _other)
                    : Core::JSON::Container()
                {
                    AppName = _other.appName;
                    Prefixes = _other.prefixes;
                    Cors = _other.cors;
                    Query = _other.query;
                    Payload = _other.payload;
                    AllowStop = _other.allowStop;
                    _Init();
                }

                ApplicationInfoData& operator=(const Exchange::IXCast::ApplicationInfo& _rhs)
                {
                    AppName = _rhs.appName;
                    Prefixes = _rhs.prefixes;
                    Cors = _rhs.cors;
                    Query = _rhs.query;
                    Payload = _rhs.payload;
                    AllowStop = _rhs.allowStop;
                    return (*this);
                }

                operator Exchange::IXCast::ApplicationInfo() const
                {
                    Exchange::IXCast::ApplicationInfo _value{};
                    _value.appName = AppName;
                    _value.prefixes = Prefixes;
                    _value.cors = Cors;
                    _value.query = Query;
                    _value.payload = Payload;
                    _value.allowStop = AllowStop;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("name"), &AppName);
                    Add(_T("prefix"), &Prefixes);
                    Add(_T("cors"), &Cors);
                    Add(_T("query"), &Query);
                    Add(_T("payload"), &Payload);
                    Add(_T("allowStop"), &AllowStop);
                }

            public:
                Core::JSON::String AppName; // Application name in request URI must have exact match to one of the names. Otherwise,
                        //  matching prefix is needed. If the application name in request URI does not match any names or prefixes, then the request shall fail
                Core::JSON::String Prefixes; // If the application name in request URI does not match the appname given here,
                        //  it must contain some prefix.If the application name in request URI does not match the appnames or prefix, then the request shall fail
                Core::JSON::String Cors; // origin allowed for the application. This must not be empty
                Core::JSON::String Query; // query string that need to be appended in launch request
                Core::JSON::String Payload; // optional payload string that need to be appended in launch request
                Core::JSON::DecSInt32 AllowStop; // is the application (matching name list or prefix list) allowed to stop (no PID presence) after launched
            }; // class ApplicationInfoData

            RegisterApplicationsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("applications"), &AppInfoList);
            }

            bool IsValid() const
            {
                return (true);
            }

            RegisterApplicationsParamsData(const RegisterApplicationsParamsData&) = delete;
            RegisterApplicationsParamsData& operator=(const RegisterApplicationsParamsData&) = delete;

        public:
            Core::JSON::ArrayType<RegisterApplicationsParamsData::ApplicationInfoData> AppInfoList; // Registers an application
        }; // class RegisterApplicationsParamsData

        class SetApplicationStateParamsData : public Core::JSON::Container {
        public:
            SetApplicationStateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("applicationName"), &ApplicationName);
                Add(_T("state"), &State);
                Add(_T("applicationId"), &ApplicationId);
                Add(_T("error"), &Error);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetApplicationStateParamsData(const SetApplicationStateParamsData&) = delete;
            SetApplicationStateParamsData& operator=(const SetApplicationStateParamsData&) = delete;

        public:
            Core::JSON::String ApplicationName; // Registered application name
            Core::JSON::EnumType<Exchange::IXCast::State> State; // Application state
            Core::JSON::String ApplicationId; // Application instance ID
            Core::JSON::EnumType<Exchange::IXCast::ErrorCode> Error; // Error string, if any
        }; // class SetApplicationStateParamsData

        class SetEnabledParamsData : public Core::JSON::Container {
        public:
            SetEnabledParamsData()
                : Core::JSON::Container()
            {
                Add(_T("enabled"), &Enabled);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetEnabledParamsData(const SetEnabledParamsData&) = delete;
            SetEnabledParamsData& operator=(const SetEnabledParamsData&) = delete;

        public:
            Core::JSON::Boolean Enabled; // Enable or disable XCAST service
        }; // class SetEnabledParamsData

        class SetFriendlyNameParamsData : public Core::JSON::Container {
        public:
            SetFriendlyNameParamsData()
                : Core::JSON::Container()
            {
                Add(_T("friendlyname"), &Friendlyname);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetFriendlyNameParamsData(const SetFriendlyNameParamsData&) = delete;
            SetFriendlyNameParamsData& operator=(const SetFriendlyNameParamsData&) = delete;

        public:
            Core::JSON::String Friendlyname; // The friendly name of the device which used to display on the client device list
        }; // class SetFriendlyNameParamsData

        class SetManufacturerNameParamsData : public Core::JSON::Container {
        public:
            SetManufacturerNameParamsData()
                : Core::JSON::Container()
            {
                Add(_T("manufacturer"), &Manufacturername);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetManufacturerNameParamsData(const SetManufacturerNameParamsData&) = delete;
            SetManufacturerNameParamsData& operator=(const SetManufacturerNameParamsData&) = delete;

        public:
            Core::JSON::String Manufacturername; // Sets the manufacturer name of the device
        }; // class SetManufacturerNameParamsData

        class SetModelNameParamsData : public Core::JSON::Container {
        public:
            SetModelNameParamsData()
                : Core::JSON::Container()
            {
                Add(_T("model"), &Modelname);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetModelNameParamsData(const SetModelNameParamsData&) = delete;
            SetModelNameParamsData& operator=(const SetModelNameParamsData&) = delete;

        public:
            Core::JSON::String Modelname; // Sets the model name of the device
        }; // class SetModelNameParamsData

        class SetStandbyBehaviorParamsData : public Core::JSON::Container {
        public:
            SetStandbyBehaviorParamsData()
                : Core::JSON::Container()
            {
                Add(_T("standbybehavior"), &Standbybehavior);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetStandbyBehaviorParamsData(const SetStandbyBehaviorParamsData&) = delete;
            SetStandbyBehaviorParamsData& operator=(const SetStandbyBehaviorParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IXCast::StandbyBehavior> Standbybehavior; // whether to remain active or inactive during standby mode (must be one of the following: active, inactive)
        }; // class SetStandbyBehaviorParamsData

        class UnregisterApplicationsParamsData : public Core::JSON::Container {
        public:
            UnregisterApplicationsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("applications"), &Applications);
            }

            bool IsValid() const
            {
                return (true);
            }

            UnregisterApplicationsParamsData(const UnregisterApplicationsParamsData&) = delete;
            UnregisterApplicationsParamsData& operator=(const UnregisterApplicationsParamsData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> Applications; // One or more application name to unregister
        }; // class UnregisterApplicationsParamsData

    } // namespace XCast

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IXCast::State)
ENUM_CONVERSION_HANDLER(Exchange::IXCast::ErrorCode)
ENUM_CONVERSION_HANDLER(Exchange::IXCast::StandbyBehavior)

}

