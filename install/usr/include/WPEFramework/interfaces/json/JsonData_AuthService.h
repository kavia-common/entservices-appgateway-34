// C++ classes for AuthService API JSON-RPC API.
// Generated automatically from 'IAuthService.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAuthService.h>

namespace WPEFramework {

namespace JsonData {

    namespace AuthService {

        // Common classes
        //

        class ReadyParamsInfo : public Core::JSON::Container {
        public:
            ReadyParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
            }

            bool IsValid() const
            {
                return (true);
            }

            ReadyParamsInfo(const ReadyParamsInfo&) = delete;
            ReadyParamsInfo& operator=(const ReadyParamsInfo&) = delete;

        public:
            Core::JSON::String Status; // - in - string
        }; // class ReadyParamsInfo

        class SetContentAccessTokenParamsInfo : public Core::JSON::Container {
        public:
            SetContentAccessTokenParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("token"), &Token);
                Add(_T("expires"), &Expires);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetContentAccessTokenParamsInfo(const SetContentAccessTokenParamsInfo&) = delete;
            SetContentAccessTokenParamsInfo& operator=(const SetContentAccessTokenParamsInfo&) = delete;

        public:
            Core::JSON::String Token; // - in - string
            Core::JSON::DecUInt32 Expires; // - in - uint32_t
        }; // class SetContentAccessTokenParamsInfo

        class SuccessMsgResultInfo : public Core::JSON::Container {
        public:
            SuccessMsgResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            SuccessMsgResultInfo(const Exchange::IAuthService::SuccessMsgResult& _other)
                : Core::JSON::Container()
            {
                Message = _other.message;
                Success = _other.success;
                _Init();
            }

            SuccessMsgResultInfo& operator=(const Exchange::IAuthService::SuccessMsgResult& _rhs)
            {
                Message = _rhs.message;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::SuccessMsgResult() const
            {
                Exchange::IAuthService::SuccessMsgResult _value{};
                _value.message = Message;
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
                Add(_T("message"), &Message);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String Message; // Sets device id
            Core::JSON::Boolean Success; // Sets device id
        }; // class SuccessMsgResultInfo

        class SuccessResultInfo : public Core::JSON::Container {
        public:
            SuccessResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            SuccessResultInfo(const Exchange::IAuthService::SuccessResult& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            SuccessResultInfo& operator=(const Exchange::IAuthService::SuccessResult& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::SuccessResult() const
            {
                Exchange::IAuthService::SuccessResult _value{};
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
            Core::JSON::Boolean Success; // Lets the Auth Service know that the device's activation is started
        }; // class SuccessResultInfo

        // Method params/result classes
        //

        class ActivationStatusResultData : public Core::JSON::Container {
        public:
            ActivationStatusResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            ActivationStatusResultData(const Exchange::IAuthService::ActivationStatusResult& _other)
                : Core::JSON::Container()
            {
                Status = _other.status;
                Success = _other.success;
                _Init();
            }

            ActivationStatusResultData& operator=(const Exchange::IAuthService::ActivationStatusResult& _rhs)
            {
                Status = _rhs.status;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::ActivationStatusResult() const
            {
                Exchange::IAuthService::ActivationStatusResult _value{};
                _value.status = Status;
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
                Add(_T("status"), &Status);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String Status; // Returns the activation status
            Core::JSON::Boolean Success; // Returns the activation status
        }; // class ActivationStatusResultData

        class AdvtOptOutResultData : public Core::JSON::Container {
        public:
            AdvtOptOutResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            AdvtOptOutResultData(const Exchange::IAuthService::AdvtOptOutResult& _other)
                : Core::JSON::Container()
            {
                AdvtOptOut = _other.advtOptOut;
                Success = _other.success;
                _Init();
            }

            AdvtOptOutResultData& operator=(const Exchange::IAuthService::AdvtOptOutResult& _rhs)
            {
                AdvtOptOut = _rhs.advtOptOut;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::AdvtOptOutResult() const
            {
                Exchange::IAuthService::AdvtOptOutResult _value{};
                _value.advtOptOut = AdvtOptOut;
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
                Add(_T("advtOptOut"), &AdvtOptOut);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::Boolean AdvtOptOut; // Returns advtOptOut
            Core::JSON::Boolean Success; // Returns advtOptOut
        }; // class AdvtOptOutResultData

        class GetAlternateIdsResultData : public Core::JSON::Container {
        public:
            GetAlternateIdsResultData()
                : Core::JSON::Container()
            {
                Add(_T("alternateIds"), &AlternateIds);
                AlternateIds.SetQuoted(false);
                Add(_T("message"), &Message);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetAlternateIdsResultData(const GetAlternateIdsResultData&) = delete;
            GetAlternateIdsResultData& operator=(const GetAlternateIdsResultData&) = delete;

        public:
            Core::JSON::String AlternateIds; // - out/json - string
            Core::JSON::String Message; // Returns alternate IDs as key/value pairs
            Core::JSON::Boolean Success; // - out - bool
        }; // class GetAlternateIdsResultData

        class GetAuthTokenParamsData : public Core::JSON::Container {
        public:
            GetAuthTokenParamsData()
                : Core::JSON::Container()
            {
                Add(_T("forceNew"), &ForceNew);
                Add(_T("recoverRenewal"), &RecoverRenewal);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetAuthTokenParamsData(const GetAuthTokenParamsData&) = delete;
            GetAuthTokenParamsData& operator=(const GetAuthTokenParamsData&) = delete;

        public:
            Core::JSON::Boolean ForceNew; // - in - bool
            Core::JSON::Boolean RecoverRenewal; // Returns the authorization token
        }; // class GetAuthTokenParamsData

        class GetAuthTokenResultData : public Core::JSON::Container {
        public:
            GetAuthTokenResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetAuthTokenResultData(const Exchange::IAuthService::GetAuthTokenResult& _other)
                : Core::JSON::Container()
            {
                Status = _other.status;
                Token = _other.token;
                Expires = _other.expires;
                ClientId = _other.clientId;
                MessageId = _other.messageId;
                ImageName = _other.imageName;
                Success = _other.success;
                _Init();
            }

            GetAuthTokenResultData& operator=(const Exchange::IAuthService::GetAuthTokenResult& _rhs)
            {
                Status = _rhs.status;
                Token = _rhs.token;
                Expires = _rhs.expires;
                ClientId = _rhs.clientId;
                MessageId = _rhs.messageId;
                ImageName = _rhs.imageName;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::GetAuthTokenResult() const
            {
                Exchange::IAuthService::GetAuthTokenResult _value{};
                _value.status = Status;
                _value.token = Token;
                _value.expires = Expires;
                _value.clientId = ClientId;
                _value.messageId = MessageId;
                _value.imageName = ImageName;
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
                Add(_T("status"), &Status);
                Add(_T("token"), &Token);
                Add(_T("expires"), &Expires);
                Add(_T("clientId"), &ClientId);
                Add(_T("messageId"), &MessageId);
                Add(_T("imageName"), &ImageName);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::DecSInt32 Status; // Returns the authorization token
            Core::JSON::String Token; // Returns the authorization token
            Core::JSON::DecUInt32 Expires; // Returns the authorization token
            Core::JSON::String ClientId; // Returns the authorization token
            Core::JSON::String MessageId; // Returns the authorization token
            Core::JSON::String ImageName; // Returns the authorization token
            Core::JSON::Boolean Success; // Returns the authorization token
        }; // class GetAuthTokenResultData

        class GetBootstrapPropResultData : public Core::JSON::Container {
        public:
            GetBootstrapPropResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetBootstrapPropResultData(const Exchange::IAuthService::GetBootstrapPropResult& _other)
                : Core::JSON::Container()
            {
                NtpHost = _other.ntpHost;
                Message = _other.message;
                Success = _other.success;
                _Init();
            }

            GetBootstrapPropResultData& operator=(const Exchange::IAuthService::GetBootstrapPropResult& _rhs)
            {
                NtpHost = _rhs.ntpHost;
                Message = _rhs.message;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::GetBootstrapPropResult() const
            {
                Exchange::IAuthService::GetBootstrapPropResult _value{};
                _value.ntpHost = NtpHost;
                _value.message = Message;
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
                Add(_T("ntpHost"), &NtpHost);
                Add(_T("message"), &Message);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String NtpHost; // Returns the bootstrap property associated with the current partnerId
            Core::JSON::String Message; // Returns the bootstrap property associated with the current partnerId
            Core::JSON::Boolean Success; // Returns the bootstrap property associated with the current partnerId
        }; // class GetBootstrapPropResultData

        class GetBootstrapPropertyParamsData : public Core::JSON::Container {
        public:
            GetBootstrapPropertyParamsData()
                : Core::JSON::Container()
            {
                Add(_T("bootstrapProperty"), &BootstrapProperty);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetBootstrapPropertyParamsData(const GetBootstrapPropertyParamsData&) = delete;
            GetBootstrapPropertyParamsData& operator=(const GetBootstrapPropertyParamsData&) = delete;

        public:
            Core::JSON::String BootstrapProperty; // - in - string
        }; // class GetBootstrapPropertyParamsData

        class GetCustomPropertiesResultData : public Core::JSON::Container {
        public:
            GetCustomPropertiesResultData()
                : Core::JSON::Container()
            {
                Add(_T("customProperties"), &CustomProperties);
                CustomProperties.SetQuoted(false);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetCustomPropertiesResultData(const GetCustomPropertiesResultData&) = delete;
            GetCustomPropertiesResultData& operator=(const GetCustomPropertiesResultData&) = delete;

        public:
            Core::JSON::String CustomProperties; // - out/json - string
            Core::JSON::Boolean Success; // - out - bool
        }; // class GetCustomPropertiesResultData

        class GetDeviceIdResultData : public Core::JSON::Container {
        public:
            GetDeviceIdResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetDeviceIdResultData(const Exchange::IAuthService::GetDeviceIdResult& _other)
                : Core::JSON::Container()
            {
                DeviceId = _other.deviceId;
                PartnerId = _other.partnerId;
                Success = _other.success;
                _Init();
            }

            GetDeviceIdResultData& operator=(const Exchange::IAuthService::GetDeviceIdResult& _rhs)
            {
                DeviceId = _rhs.deviceId;
                PartnerId = _rhs.partnerId;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::GetDeviceIdResult() const
            {
                Exchange::IAuthService::GetDeviceIdResult _value{};
                _value.deviceId = DeviceId;
                _value.partnerId = PartnerId;
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
                Add(_T("deviceId"), &DeviceId);
                Add(_T("partnerId"), &PartnerId);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String DeviceId; // Returns the device (receiver) id
            Core::JSON::String PartnerId; // Returns the device (receiver) id
            Core::JSON::Boolean Success; // Returns the device (receiver) id
        }; // class GetDeviceIdResultData

        class GetDeviceInfoResultData : public Core::JSON::Container {
        public:
            GetDeviceInfoResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetDeviceInfoResultData(const Exchange::IAuthService::GetDeviceInfoResult& _other)
                : Core::JSON::Container()
            {
                DeviceInfo = _other.deviceInfo;
                Success = _other.success;
                _Init();
            }

            GetDeviceInfoResultData& operator=(const Exchange::IAuthService::GetDeviceInfoResult& _rhs)
            {
                DeviceInfo = _rhs.deviceInfo;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::GetDeviceInfoResult() const
            {
                Exchange::IAuthService::GetDeviceInfoResult _value{};
                _value.deviceInfo = DeviceInfo;
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
                Add(_T("deviceInfo"), &DeviceInfo);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String DeviceInfo; // Returns device info - Deprecated
            Core::JSON::Boolean Success; // Returns device info - Deprecated
        }; // class GetDeviceInfoResultData

        class GetExpResultData : public Core::JSON::Container {
        public:
            GetExpResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetExpResultData(const Exchange::IAuthService::GetExpResult& _other)
                : Core::JSON::Container()
            {
                Experience = _other.experience;
                Success = _other.success;
                _Init();
            }

            GetExpResultData& operator=(const Exchange::IAuthService::GetExpResult& _rhs)
            {
                Experience = _rhs.experience;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::GetExpResult() const
            {
                Exchange::IAuthService::GetExpResult _value{};
                _value.experience = Experience;
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
                Add(_T("experience"), &Experience);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String Experience; // Returns the experience
            Core::JSON::Boolean Success; // Returns the experience
        }; // class GetExpResultData

        class GetInfoResultData : public Core::JSON::Container {
        public:
            GetInfoResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetInfoResultData(const Exchange::IAuthService::GetInfoResult& _other)
                : Core::JSON::Container()
            {
                Version = _other.version;
                Host = _other.host;
                Aspath = _other.aspath;
                Asmode = _other.asmode;
                MinRenew = _other.minRenew;
                MaxRenew = _other.maxRenew;
                Success = _other.success;
                _Init();
            }

            GetInfoResultData& operator=(const Exchange::IAuthService::GetInfoResult& _rhs)
            {
                Version = _rhs.version;
                Host = _rhs.host;
                Aspath = _rhs.aspath;
                Asmode = _rhs.asmode;
                MinRenew = _rhs.minRenew;
                MaxRenew = _rhs.maxRenew;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::GetInfoResult() const
            {
                Exchange::IAuthService::GetInfoResult _value{};
                _value.version = Version;
                _value.host = Host;
                _value.aspath = Aspath;
                _value.asmode = Asmode;
                _value.minRenew = MinRenew;
                _value.maxRenew = MaxRenew;
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
                Add(_T("version"), &Version);
                Add(_T("host"), &Host);
                Add(_T("aspath"), &Aspath);
                Add(_T("asmode"), &Asmode);
                Add(_T("minRenew"), &MinRenew);
                Add(_T("maxRenew"), &MaxRenew);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String Version; // Returns the STB Auth Service info
            Core::JSON::String Host; // Returns the STB Auth Service info
            Core::JSON::String Aspath; // Returns the STB Auth Service info
            Core::JSON::String Asmode; // Returns the STB Auth Service info
            Core::JSON::DecUInt32 MinRenew; // Returns the STB Auth Service info
            Core::JSON::DecUInt32 MaxRenew; // Returns the STB Auth Service info
            Core::JSON::Boolean Success; // Returns the STB Auth Service info
        }; // class GetInfoResultData

        class GetLostAndFoundAccessTokenResultData : public Core::JSON::Container {
        public:
            GetLostAndFoundAccessTokenResultData()
                : Core::JSON::Container()
            {
                Add(_T("lostAndFoundAccessToken"), &LostAndFoundAccessToken);
                LostAndFoundAccessToken.SetQuoted(false);
                Add(_T("message"), &Message);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetLostAndFoundAccessTokenResultData(const GetLostAndFoundAccessTokenResultData&) = delete;
            GetLostAndFoundAccessTokenResultData& operator=(const GetLostAndFoundAccessTokenResultData&) = delete;

        public:
            Core::JSON::String LostAndFoundAccessToken; // Returns the stored Lost and Found access token (LFAT) if one is available
            Core::JSON::String Message; // Returns the stored Lost and Found access token (LFAT) if one is available
            Core::JSON::Boolean Success; // Returns the stored Lost and Found access token (LFAT) if one is available
        }; // class GetLostAndFoundAccessTokenResultData

        class GetServiceAccessTokenResultData : public Core::JSON::Container {
        public:
            GetServiceAccessTokenResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetServiceAccessTokenResultData(const Exchange::IAuthService::GetServiceAccessTokenResult& _other)
                : Core::JSON::Container()
            {
                Status = _other.status;
                Token = _other.token;
                Expires = _other.expires;
                Success = _other.success;
                Message = _other.message;
                _Init();
            }

            GetServiceAccessTokenResultData& operator=(const Exchange::IAuthService::GetServiceAccessTokenResult& _rhs)
            {
                Status = _rhs.status;
                Token = _rhs.token;
                Expires = _rhs.expires;
                Success = _rhs.success;
                Message = _rhs.message;
                return (*this);
            }

            operator Exchange::IAuthService::GetServiceAccessTokenResult() const
            {
                Exchange::IAuthService::GetServiceAccessTokenResult _value{};
                _value.status = Status;
                _value.token = Token;
                _value.expires = Expires;
                _value.success = Success;
                _value.message = Message;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("status"), &Status);
                Add(_T("token"), &Token);
                Add(_T("expires"), &Expires);
                Add(_T("success"), &Success);
                Add(_T("message"), &Message);
            }

        public:
            Core::JSON::DecSInt32 Status; // Returns the service access token
            Core::JSON::String Token; // Returns the service access token
            Core::JSON::DecUInt32 Expires; // Returns the service access token
            Core::JSON::Boolean Success; // Returns the service access token
            Core::JSON::String Message; // Returns the service access token
        }; // class GetServiceAccessTokenResultData

        class GetServiceAccountIdResultData : public Core::JSON::Container {
        public:
            GetServiceAccountIdResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetServiceAccountIdResultData(const Exchange::IAuthService::GetServiceAccountIdResult& _other)
                : Core::JSON::Container()
            {
                ServiceAccountId = _other.serviceAccountId;
                Success = _other.success;
                _Init();
            }

            GetServiceAccountIdResultData& operator=(const Exchange::IAuthService::GetServiceAccountIdResult& _rhs)
            {
                ServiceAccountId = _rhs.serviceAccountId;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::GetServiceAccountIdResult() const
            {
                Exchange::IAuthService::GetServiceAccountIdResult _value{};
                _value.serviceAccountId = ServiceAccountId;
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
                Add(_T("serviceAccountId"), &ServiceAccountId);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String ServiceAccountId; // Returns the service account ID
            Core::JSON::Boolean Success; // Returns the service account ID
        }; // class GetServiceAccountIdResultData

        class GetSessionTokenResultData : public Core::JSON::Container {
        public:
            GetSessionTokenResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetSessionTokenResultData(const Exchange::IAuthService::GetSessionTokenResult& _other)
                : Core::JSON::Container()
            {
                Status = _other.status;
                Token = _other.token;
                Expires = _other.expires;
                ClientId = _other.clientId;
                MessageId = _other.messageId;
                Success = _other.success;
                Message = _other.message;
                _Init();
            }

            GetSessionTokenResultData& operator=(const Exchange::IAuthService::GetSessionTokenResult& _rhs)
            {
                Status = _rhs.status;
                Token = _rhs.token;
                Expires = _rhs.expires;
                ClientId = _rhs.clientId;
                MessageId = _rhs.messageId;
                Success = _rhs.success;
                Message = _rhs.message;
                return (*this);
            }

            operator Exchange::IAuthService::GetSessionTokenResult() const
            {
                Exchange::IAuthService::GetSessionTokenResult _value{};
                _value.status = Status;
                _value.token = Token;
                _value.expires = Expires;
                _value.clientId = ClientId;
                _value.messageId = MessageId;
                _value.success = Success;
                _value.message = Message;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("status"), &Status);
                Add(_T("token"), &Token);
                Add(_T("expires"), &Expires);
                Add(_T("clientId"), &ClientId);
                Add(_T("messageId"), &MessageId);
                Add(_T("success"), &Success);
                Add(_T("message"), &Message);
            }

        public:
            Core::JSON::DecSInt32 Status; // Returns the session token
            Core::JSON::String Token; // Returns the session token
            Core::JSON::DecUInt32 Expires; // Returns the session token
            Core::JSON::String ClientId; // Returns the session token
            Core::JSON::String MessageId; // Returns the session token
            Core::JSON::Boolean Success; // Returns the session token
            Core::JSON::String Message; // Returns the session token
        }; // class GetSessionTokenResultData

        class GetTransitionDataResultData : public Core::JSON::Container {
        public:
            GetTransitionDataResultData()
                : Core::JSON::Container()
            {
                Add(_T("transitionData"), &TransitionData);
                TransitionData.SetQuoted(false);
                Add(_T("message"), &Message);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetTransitionDataResultData(const GetTransitionDataResultData&) = delete;
            GetTransitionDataResultData& operator=(const GetTransitionDataResultData&) = delete;

        public:
            Core::JSON::String TransitionData; // - out/json - string
            Core::JSON::String Message; // Returns the transition data
            Core::JSON::Boolean Success; // - out - string
        }; // class GetTransitionDataResultData

        class GetXDeviceIdResultData : public Core::JSON::Container {
        public:
            GetXDeviceIdResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetXDeviceIdResultData(const Exchange::IAuthService::GetXDeviceIdResult& _other)
                : Core::JSON::Container()
            {
                XDeviceId = _other.xDeviceId;
                Success = _other.success;
                Message = _other.message;
                _Init();
            }

            GetXDeviceIdResultData& operator=(const Exchange::IAuthService::GetXDeviceIdResult& _rhs)
            {
                XDeviceId = _rhs.xDeviceId;
                Success = _rhs.success;
                Message = _rhs.message;
                return (*this);
            }

            operator Exchange::IAuthService::GetXDeviceIdResult() const
            {
                Exchange::IAuthService::GetXDeviceIdResult _value{};
                _value.xDeviceId = XDeviceId;
                _value.success = Success;
                _value.message = Message;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("xDeviceId"), &XDeviceId);
                Add(_T("success"), &Success);
                Add(_T("message"), &Message);
            }

        public:
            Core::JSON::String XDeviceId; // Returns the xDevice ID
            Core::JSON::Boolean Success; // Returns the xDevice ID
            Core::JSON::String Message; // Returns the xDevice ID
        }; // class GetXDeviceIdResultData

        class GetxifaIdResultData : public Core::JSON::Container {
        public:
            GetxifaIdResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            GetxifaIdResultData(const Exchange::IAuthService::GetxifaIdResult& _other)
                : Core::JSON::Container()
            {
                XifaId = _other.xifaId;
                Success = _other.success;
                _Init();
            }

            GetxifaIdResultData& operator=(const Exchange::IAuthService::GetxifaIdResult& _rhs)
            {
                XifaId = _rhs.xifaId;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::GetxifaIdResult() const
            {
                Exchange::IAuthService::GetxifaIdResult _value{};
                _value.xifaId = XifaId;
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
                Add(_T("xifaId"), &XifaId);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String XifaId; // Returns xifaId
            Core::JSON::Boolean Success; // Returns xifaId
        }; // class GetxifaIdResultData

        class OnActivationStatusChangedParamsData : public Core::JSON::Container {
        public:
            OnActivationStatusChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("oldActivationStatus"), &OldActivationStatus);
                Add(_T("newActivationStatus"), &NewActivationStatus);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnActivationStatusChangedParamsData(const OnActivationStatusChangedParamsData&) = delete;
            OnActivationStatusChangedParamsData& operator=(const OnActivationStatusChangedParamsData&) = delete;

        public:
            Core::JSON::String OldActivationStatus; // status
            Core::JSON::String NewActivationStatus; // The Activation status changed has changed.
        }; // class OnActivationStatusChangedParamsData

        class OnPartnerIdChangedParamsData : public Core::JSON::Container {
        public:
            OnPartnerIdChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("oldPartnerId"), &OldPartnerId);
                Add(_T("newPartnerId"), &NewPartnerId);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnPartnerIdChangedParamsData(const OnPartnerIdChangedParamsData&) = delete;
            OnPartnerIdChangedParamsData& operator=(const OnPartnerIdChangedParamsData&) = delete;

        public:
            Core::JSON::String OldPartnerId; // Previous partner ID
            Core::JSON::String NewPartnerId; // New partner ID
        }; // class OnPartnerIdChangedParamsData

        class OnServiceAccountIdChangedParamsData : public Core::JSON::Container {
        public:
            OnServiceAccountIdChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("oldServiceAccountId"), &OldServiceAccountId);
                Add(_T("newServiceAccountId"), &NewServiceAccountId);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnServiceAccountIdChangedParamsData(const OnServiceAccountIdChangedParamsData&) = delete;
            OnServiceAccountIdChangedParamsData& operator=(const OnServiceAccountIdChangedParamsData&) = delete;

        public:
            Core::JSON::String OldServiceAccountId; // Id
            Core::JSON::String NewServiceAccountId; // Id
        }; // class OnServiceAccountIdChangedParamsData

        class SetAdvtOptOutParamsData : public Core::JSON::Container {
        public:
            SetAdvtOptOutParamsData()
                : Core::JSON::Container()
            {
                Add(_T("advtOptOut"), &AdvtOptOut);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetAdvtOptOutParamsData(const SetAdvtOptOutParamsData&) = delete;
            SetAdvtOptOutParamsData& operator=(const SetAdvtOptOutParamsData&) = delete;

        public:
            Core::JSON::Boolean AdvtOptOut; // - in - string
        }; // class SetAdvtOptOutParamsData

        class SetAlternateIdsParamsData : public Core::JSON::Container {
        public:
            SetAlternateIdsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("alternateIds"), &AlternateIds);
                AlternateIds.SetQuoted(false);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetAlternateIdsParamsData(const SetAlternateIdsParamsData&) = delete;
            SetAlternateIdsParamsData& operator=(const SetAlternateIdsParamsData&) = delete;

        public:
            Core::JSON::String AlternateIds; // - in/json - string
        }; // class SetAlternateIdsParamsData

        class SetAuthIdTokenParamsData : public Core::JSON::Container {
        public:
            SetAuthIdTokenParamsData()
                : Core::JSON::Container()
            {
                Add(_T("authIdToken"), &AuthIdToken);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetAuthIdTokenParamsData(const SetAuthIdTokenParamsData&) = delete;
            SetAuthIdTokenParamsData& operator=(const SetAuthIdTokenParamsData&) = delete;

        public:
            Core::JSON::String AuthIdToken; // Sets the authorization ID token
        }; // class SetAuthIdTokenParamsData

        class SetCustomPropertiesParamsData : public Core::JSON::Container {
        public:
            SetCustomPropertiesParamsData()
                : Core::JSON::Container()
            {
                Add(_T("customProperties"), &CustomProperties);
                CustomProperties.SetQuoted(false);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetCustomPropertiesParamsData(const SetCustomPropertiesParamsData&) = delete;
            SetCustomPropertiesParamsData& operator=(const SetCustomPropertiesParamsData&) = delete;

        public:
            Core::JSON::String CustomProperties; // - in/json - string
        }; // class SetCustomPropertiesParamsData

        class SetDeviceIdParamsData : public Core::JSON::Container {
        public:
            SetDeviceIdParamsData()
                : Core::JSON::Container()
            {
                Add(_T("deviceId"), &DeviceId);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetDeviceIdParamsData(const SetDeviceIdParamsData&) = delete;
            SetDeviceIdParamsData& operator=(const SetDeviceIdParamsData&) = delete;

        public:
            Core::JSON::String DeviceId; // - in - string
        }; // class SetDeviceIdParamsData

        class SetExperienceParamsData : public Core::JSON::Container {
        public:
            SetExperienceParamsData()
                : Core::JSON::Container()
            {
                Add(_T("experience"), &Experience);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetExperienceParamsData(const SetExperienceParamsData&) = delete;
            SetExperienceParamsData& operator=(const SetExperienceParamsData&) = delete;

        public:
            Core::JSON::String Experience; // Sets the experience
        }; // class SetExperienceParamsData

        class SetLostAndFoundAccessTokenParamsData : public Core::JSON::Container {
        public:
            SetLostAndFoundAccessTokenParamsData()
                : Core::JSON::Container()
            {
                Add(_T("lostAndFoundAccessToken"), &LostAndFoundAccessToken);
                LostAndFoundAccessToken.SetQuoted(false);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetLostAndFoundAccessTokenParamsData(const SetLostAndFoundAccessTokenParamsData&) = delete;
            SetLostAndFoundAccessTokenParamsData& operator=(const SetLostAndFoundAccessTokenParamsData&) = delete;

        public:
            Core::JSON::String LostAndFoundAccessToken; // - in opaque json - string
        }; // class SetLostAndFoundAccessTokenParamsData

        class SetPartnerIdParamsData : public Core::JSON::Container {
        public:
            SetPartnerIdParamsData()
                : Core::JSON::Container()
            {
                Add(_T("partnerId"), &PartnerId);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetPartnerIdParamsData(const SetPartnerIdParamsData&) = delete;
            SetPartnerIdParamsData& operator=(const SetPartnerIdParamsData&) = delete;

        public:
            Core::JSON::String PartnerId; // - in - string
        }; // class SetPartnerIdParamsData

        class SetPartnerIdResultData : public Core::JSON::Container {
        public:
            SetPartnerIdResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            SetPartnerIdResultData(const Exchange::IAuthService::SetPartnerIdResult& _other)
                : Core::JSON::Container()
            {
                Error = _other.error;
                Success = _other.success;
                _Init();
            }

            SetPartnerIdResultData& operator=(const Exchange::IAuthService::SetPartnerIdResult& _rhs)
            {
                Error = _rhs.error;
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IAuthService::SetPartnerIdResult() const
            {
                Exchange::IAuthService::SetPartnerIdResult _value{};
                _value.error = Error;
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
                Add(_T("error"), &Error);
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::String Error; // Sets partner id
            Core::JSON::Boolean Success; // Sets partner id
        }; // class SetPartnerIdResultData

        class SetServiceAccessTokenParamsData : public Core::JSON::Container {
        public:
            SetServiceAccessTokenParamsData()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
                Add(_T("token"), &Token);
                Add(_T("expires"), &Expires);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetServiceAccessTokenParamsData(const SetServiceAccessTokenParamsData&) = delete;
            SetServiceAccessTokenParamsData& operator=(const SetServiceAccessTokenParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Status; // - in - int32_t
            Core::JSON::String Token; // - in - string
            Core::JSON::DecUInt32 Expires; // Sets the service access token
        }; // class SetServiceAccessTokenParamsData

        class SetServiceAccountIdParamsData : public Core::JSON::Container {
        public:
            SetServiceAccountIdParamsData()
                : Core::JSON::Container()
            {
                Add(_T("serviceAccountId"), &ServiceAccountId);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetServiceAccountIdParamsData(const SetServiceAccountIdParamsData&) = delete;
            SetServiceAccountIdParamsData& operator=(const SetServiceAccountIdParamsData&) = delete;

        public:
            Core::JSON::String ServiceAccountId; // Sets the service account ID
        }; // class SetServiceAccountIdParamsData

        class SetSessionTokenParamsData : public Core::JSON::Container {
        public:
            SetSessionTokenParamsData()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
                Add(_T("token"), &Token);
                Add(_T("expires"), &Expires);
                Add(_T("clientId"), &ClientId);
                Add(_T("messageId"), &MessageId);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetSessionTokenParamsData(const SetSessionTokenParamsData&) = delete;
            SetSessionTokenParamsData& operator=(const SetSessionTokenParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Status; // - in - int32_t
            Core::JSON::String Token; // - in - string
            Core::JSON::DecUInt32 Expires; // Sets the session token
            Core::JSON::String ClientId; // - in - string
            Core::JSON::String MessageId; // Sets the session token
        }; // class SetSessionTokenParamsData

        class SetXDeviceIdParamsData : public Core::JSON::Container {
        public:
            SetXDeviceIdParamsData()
                : Core::JSON::Container()
            {
                Add(_T("xDeviceId"), &XDeviceId);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetXDeviceIdParamsData(const SetXDeviceIdParamsData&) = delete;
            SetXDeviceIdParamsData& operator=(const SetXDeviceIdParamsData&) = delete;

        public:
            Core::JSON::String XDeviceId; // - in - string
        }; // class SetXDeviceIdParamsData

        class SetXifaIdParamsData : public Core::JSON::Container {
        public:
            SetXifaIdParamsData()
                : Core::JSON::Container()
            {
                Add(_T("xifaId"), &XifaId);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetXifaIdParamsData(const SetXifaIdParamsData&) = delete;
            SetXifaIdParamsData& operator=(const SetXifaIdParamsData&) = delete;

        public:
            Core::JSON::String XifaId; // - in - string
        }; // class SetXifaIdParamsData

    } // namespace AuthService

} // namespace JsonData

}

