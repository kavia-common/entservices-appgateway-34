// C++ classes for RuntimeManagerDelegate API JSON-RPC API.
// Generated automatically from 'IGoogleCast.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IGoogleCast.h>

namespace WPEFramework {

namespace JsonData {

    namespace GoogleCast {

        namespace RuntimeManagerDelegate {

            // Method params/result classes
            //

            class OnIntentChangedParamsData : public Core::JSON::Container {
            public:
                class IntentData : public Core::JSON::Container {
                public:
                    class IntentContextData : public Core::JSON::Container {
                    public:
                        IntentContextData()
                            : Core::JSON::Container()
                        {
                            _Init();
                        }

                        IntentContextData(const Exchange::IGoogleCast::IRuntimeManagerDelegate::IntentContext& _other)
                            : Core::JSON::Container()
                        {
                            Source = _other.source;
                            _Init();
                        }

                        IntentContextData& operator=(const Exchange::IGoogleCast::IRuntimeManagerDelegate::IntentContext& _rhs)
                        {
                            Source = _rhs.source;
                            return (*this);
                        }

                        operator Exchange::IGoogleCast::IRuntimeManagerDelegate::IntentContext() const
                        {
                            Exchange::IGoogleCast::IRuntimeManagerDelegate::IntentContext _value{};
                            _value.source = Source;
                            return (_value);
                        }

                        bool IsValid() const
                        {
                            return (true);
                        }

                    private:
                        void _Init()
                        {
                            Add(_T("source"), &Source);
                        }

                    public:
                        Core::JSON::String Source; // Source of the intent.
                    }; // class IntentContextData

                    IntentData()
                        : Core::JSON::Container()
                    {
                        _Init();
                    }

                    IntentData(const Exchange::IGoogleCast::IRuntimeManagerDelegate::Intent& _other)
                        : Core::JSON::Container()
                    {
                        Action = _other.action;
                        Context = _other.context;
                        Data = _other.data;
                        _Init();
                    }

                    IntentData& operator=(const Exchange::IGoogleCast::IRuntimeManagerDelegate::Intent& _rhs)
                    {
                        Action = _rhs.action;
                        Context = _rhs.context;
                        if (_rhs.data.empty() == false)
                            Data = _rhs.data;
                        return (*this);
                    }

                    operator Exchange::IGoogleCast::IRuntimeManagerDelegate::Intent() const
                    {
                        Exchange::IGoogleCast::IRuntimeManagerDelegate::Intent _value{};
                        _value.action = Action;
                        _value.context = Context;
                        _value.data = Data;
                        return (_value);
                    }

                    bool IsValid() const
                    {
                        return (true);
                    }

                private:
                    void _Init()
                    {
                        Add(_T("action"), &Action);
                        Add(_T("context"), &Context);
                        Add(_T("data"), &Data);
                        Data.SetQuoted(false);
                    }

                public:
                    Core::JSON::EnumType<Exchange::IGoogleCast::IRuntimeManagerDelegate::IntentAction> Action; // Specifies the intent action to launch,
                            //  close or destroy the app runtime instance.
                    OnIntentChangedParamsData::IntentData::IntentContextData Context; // Intent context.
                    Core::JSON::String Data; // An array of launch arguments to forward to app runtime instance as is.
                }; // class IntentData

                OnIntentChangedParamsData()
                    : Core::JSON::Container()
                {
                    Add(_T("appId"), &AppId);
                    Add(_T("inactive"), &Inactive);
                    Add(_T("intent"), &Intent);
                }

                bool IsValid() const
                {
                    return (true);
                }

                OnIntentChangedParamsData(const OnIntentChangedParamsData&) = delete;
                OnIntentChangedParamsData& operator=(const OnIntentChangedParamsData&) = delete;

            public:
                Core::JSON::String AppId; // Durable application id.
                Core::JSON::Boolean Inactive; // Indicates pre-launch(off screen) request.
                OnIntentChangedParamsData::IntentData Intent; // A Firebolt compliant navigation intent.
            }; // class OnIntentChangedParamsData

        } // namespace RuntimeManagerDelegate

    } // namespace GoogleCast

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IGoogleCast::CastState)
ENUM_CONVERSION_HANDLER(Exchange::IGoogleCast::IRuntimeManagerDelegate::IntentAction)

}

