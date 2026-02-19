// C++ classes for DeviceDiagnostics API JSON-RPC API.
// Generated automatically from 'IDeviceDiagnostics.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IDeviceDiagnostics.h>

namespace WPEFramework {

namespace JsonData {

    namespace DeviceDiagnostics {

        // Method params/result classes
        //

        class AvDecoderStatusResultData : public Core::JSON::Container {
        public:
            AvDecoderStatusResultData()
                : Core::JSON::Container()
            {
                _Init();
            }

            AvDecoderStatusResultData(const Exchange::IDeviceDiagnostics::AvDecoderStatusResult& _other)
                : Core::JSON::Container()
            {
                AvDecoderStatus = _other.avDecoderStatus;
                _Init();
            }

            AvDecoderStatusResultData& operator=(const Exchange::IDeviceDiagnostics::AvDecoderStatusResult& _rhs)
            {
                AvDecoderStatus = _rhs.avDecoderStatus;
                return (*this);
            }

            operator Exchange::IDeviceDiagnostics::AvDecoderStatusResult() const
            {
                Exchange::IDeviceDiagnostics::AvDecoderStatusResult _value{};
                _value.avDecoderStatus = AvDecoderStatus;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("avDecoderStatus"), &AvDecoderStatus);
            }

        public:
            Core::JSON::String AvDecoderStatus; // Gets the most active status of audio/video decoder/pipeline
        }; // class AvDecoderStatusResultData

        class GetConfigurationParamsData : public Core::JSON::Container {
        public:
            GetConfigurationParamsData()
                : Core::JSON::Container()
            {
                Add(_T("names"), &Names);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetConfigurationParamsData(const GetConfigurationParamsData&) = delete;
            GetConfigurationParamsData& operator=(const GetConfigurationParamsData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> Names; // - in - String array of property names
        }; // class GetConfigurationParamsData

        class GetConfigurationResultData : public Core::JSON::Container {
        public:
            class ParamListData : public Core::JSON::Container {
            public:
                ParamListData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                ParamListData(const ParamListData& _other)
                    : Core::JSON::Container()
                    , Name(_other.Name)
                    , Value(_other.Value)
                {
                    _Init();
                }

                ParamListData& operator=(const ParamListData& _rhs)
                {
                    Name = _rhs.Name;
                    Value = _rhs.Value;
                    return (*this);
                }

                ParamListData(const Exchange::IDeviceDiagnostics::ParamList& _other)
                    : Core::JSON::Container()
                {
                    Name = _other.name;
                    Value = _other.value;
                    _Init();
                }

                ParamListData& operator=(const Exchange::IDeviceDiagnostics::ParamList& _rhs)
                {
                    Name = _rhs.name;
                    Value = _rhs.value;
                    return (*this);
                }

                operator Exchange::IDeviceDiagnostics::ParamList() const
                {
                    Exchange::IDeviceDiagnostics::ParamList _value{};
                    _value.name = Name;
                    _value.value = Value;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("name"), &Name);
                    Add(_T("value"), &Value);
                }

            public:
                Core::JSON::String Name;
                Core::JSON::String Value;
            }; // class ParamListData

            GetConfigurationResultData()
                : Core::JSON::Container()
            {
                Add(_T("paramList"), &ParamList);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetConfigurationResultData(const GetConfigurationResultData&) = delete;
            GetConfigurationResultData& operator=(const GetConfigurationResultData&) = delete;

        public:
            Core::JSON::ArrayType<GetConfigurationResultData::ParamListData> ParamList; // - out - specified properties and their values
            Core::JSON::Boolean Success; // - out - boolean
        }; // class GetConfigurationResultData

        class GetMilestonesResultData : public Core::JSON::Container {
        public:
            GetMilestonesResultData()
                : Core::JSON::Container()
            {
                Add(_T("milestones"), &Milestones);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetMilestonesResultData(const GetMilestonesResultData&) = delete;
            GetMilestonesResultData& operator=(const GetMilestonesResultData&) = delete;

        public:
            Core::JSON::ArrayType<Core::JSON::String> Milestones; // - out - A string [] of milestones
            Core::JSON::Boolean Success; // - out - boolean
        }; // class GetMilestonesResultData

        class LogMilestoneParamsData : public Core::JSON::Container {
        public:
            LogMilestoneParamsData()
                : Core::JSON::Container()
            {
                Add(_T("marker"), &Marker);
            }

            bool IsValid() const
            {
                return (true);
            }

            LogMilestoneParamsData(const LogMilestoneParamsData&) = delete;
            LogMilestoneParamsData& operator=(const LogMilestoneParamsData&) = delete;

        public:
            Core::JSON::String Marker; // - in - string
        }; // class LogMilestoneParamsData

        class OnAVDecoderStatusChangedParamsData : public Core::JSON::Container {
        public:
            OnAVDecoderStatusChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("avDecoderStatusChange"), &AvDecoderStatusChange);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAVDecoderStatusChangedParamsData(const OnAVDecoderStatusChangedParamsData&) = delete;
            OnAVDecoderStatusChangedParamsData& operator=(const OnAVDecoderStatusChangedParamsData&) = delete;

        public:
            Core::JSON::String AvDecoderStatusChange; // - in - string
        }; // class OnAVDecoderStatusChangedParamsData

    } // namespace DeviceDiagnostics

} // namespace JsonData

}

