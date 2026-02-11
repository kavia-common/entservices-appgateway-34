// C++ classes for RDKWindowManager API JSON-RPC API.
// Generated automatically from 'IRDKWindowManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IRDKWindowManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace RDKWindowManager {

        // Common classes
        //

        class AddKeyInterceptParamsInfo : public Core::JSON::Container {
        public:
            AddKeyInterceptParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("intercept"), &Intercept);
            }

            bool IsValid() const
            {
                return (true);
            }

            AddKeyInterceptParamsInfo(const AddKeyInterceptParamsInfo&) = delete;
            AddKeyInterceptParamsInfo& operator=(const AddKeyInterceptParamsInfo&) = delete;

        public:
            Core::JSON::String Intercept; // JSON String format with the client/callSign, keyCode, modifiers
        }; // class AddKeyInterceptParamsInfo

        class AddKeyListenerParamsInfo : public Core::JSON::Container {
        public:
            AddKeyListenerParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("keyListeners"), &KeyListeners);
            }

            bool IsValid() const
            {
                return (true);
            }

            AddKeyListenerParamsInfo(const AddKeyListenerParamsInfo&) = delete;
            AddKeyListenerParamsInfo& operator=(const AddKeyListenerParamsInfo&) = delete;

        public:
            Core::JSON::String KeyListeners; // JSON String format containing the keylisteneres with keys(keyCode,nativekeyCode,modifiers,activate,
                    // propagate) and client/callSign
        }; // class AddKeyListenerParamsInfo

        class EnableInactivityReportingParamsInfo : public Core::JSON::Container {
        public:
            EnableInactivityReportingParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("enable"), &Enable);
            }

            bool IsValid() const
            {
                return (true);
            }

            EnableInactivityReportingParamsInfo(const EnableInactivityReportingParamsInfo&) = delete;
            EnableInactivityReportingParamsInfo& operator=(const EnableInactivityReportingParamsInfo&) = delete;

        public:
            Core::JSON::Boolean Enable; // flag to true/false the feature
        }; // class EnableInactivityReportingParamsInfo

        class OnConnectedParamsInfo : public Core::JSON::Container {
        public:
            OnConnectedParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("appInstanceId"), &AppInstanceId);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnConnectedParamsInfo(const OnConnectedParamsInfo&) = delete;
            OnConnectedParamsInfo& operator=(const OnConnectedParamsInfo&) = delete;

        public:
            Core::JSON::String AppInstanceId; // the identifier of the connected application
        }; // class OnConnectedParamsInfo

        class SetFocusParamsInfo : public Core::JSON::Container {
        public:
            SetFocusParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("client"), &Client);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetFocusParamsInfo(const SetFocusParamsInfo&) = delete;
            SetFocusParamsInfo& operator=(const SetFocusParamsInfo&) = delete;

        public:
            Core::JSON::String Client; // Sets the focus to the app with the app id
        }; // class SetFocusParamsInfo

        // Method params/result classes
        //

        class AddKeyInterceptsParamsData : public Core::JSON::Container {
        public:
            AddKeyInterceptsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("intercepts"), &Intercepts);
            }

            bool IsValid() const
            {
                return (true);
            }

            AddKeyInterceptsParamsData(const AddKeyInterceptsParamsData&) = delete;
            AddKeyInterceptsParamsData& operator=(const AddKeyInterceptsParamsData&) = delete;

        public:
            Core::JSON::String Intercepts; // JSON String format containing the array of key intercept(client/callSign, keyCode, modifiers) configuration
        }; // class AddKeyInterceptsParamsData

        class CreateDisplayParamsData : public Core::JSON::Container {
        public:
            CreateDisplayParamsData()
                : Core::JSON::Container()
            {
                Add(_T("displayParams"), &DisplayParams);
            }

            bool IsValid() const
            {
                return (true);
            }

            CreateDisplayParamsData(const CreateDisplayParamsData&) = delete;
            CreateDisplayParamsData& operator=(const CreateDisplayParamsData&) = delete;

        public:
            Core::JSON::String DisplayParams; // JSON String format with client,displayName,displayWidth,displayHeight,virtualDisplay,virtualWidth,
                    // virtualHeight,topmost,focus
        }; // class CreateDisplayParamsData

        class EnableDisplayRenderParamsData : public Core::JSON::Container {
        public:
            EnableDisplayRenderParamsData()
                : Core::JSON::Container()
            {
                Add(_T("client"), &Client);
                Add(_T("enable"), &Enable);
            }

            bool IsValid() const
            {
                return (true);
            }

            EnableDisplayRenderParamsData(const EnableDisplayRenderParamsData&) = delete;
            EnableDisplayRenderParamsData& operator=(const EnableDisplayRenderParamsData&) = delete;

        public:
            Core::JSON::String Client; // client name or application instance ID
            Core::JSON::Boolean Enable; // flag to true/false for controlling the wayland render
        }; // class EnableDisplayRenderParamsData

        class EnableInputEventsParamsData : public Core::JSON::Container {
        public:
            EnableInputEventsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("clients"), &Clients);
                Add(_T("enable"), &Enable);
            }

            bool IsValid() const
            {
                return (true);
            }

            EnableInputEventsParamsData(const EnableInputEventsParamsData&) = delete;
            EnableInputEventsParamsData& operator=(const EnableInputEventsParamsData&) = delete;

        public:
            Core::JSON::String Clients; // JSON String format with number of clients, enable:Flag to enable input events
            Core::JSON::Boolean Enable; // Enables KeyInputEvents for list of clients specified
        }; // class EnableInputEventsParamsData

        class GenerateKeyParamsData : public Core::JSON::Container {
        public:
            GenerateKeyParamsData()
                : Core::JSON::Container()
            {
                Add(_T("keys"), &Keys);
                Add(_T("client"), &Client);
            }

            bool IsValid() const
            {
                return (true);
            }

            GenerateKeyParamsData(const GenerateKeyParamsData&) = delete;
            GenerateKeyParamsData& operator=(const GenerateKeyParamsData&) = delete;

        public:
            Core::JSON::String Keys; // JSON String format representing the key(s)(keyCode,modifiers,delay,client/callSign) to generate
            Core::JSON::String Client; // Name of the client/callSign requesting the key generation.
        }; // class GenerateKeyParamsData

        class GetLastKeyInfoResultData : public Core::JSON::Container {
        public:
            GetLastKeyInfoResultData()
                : Core::JSON::Container()
            {
                Add(_T("keyCode"), &KeyCode);
                Add(_T("modifiers"), &Modifiers);
                Add(_T("timestampInSeconds"), &TimestampInSeconds);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetLastKeyInfoResultData(const GetLastKeyInfoResultData&) = delete;
            GetLastKeyInfoResultData& operator=(const GetLastKeyInfoResultData&) = delete;

        public:
            Core::JSON::DecUInt32 KeyCode; // Output parameter. The key code of the last pressed key.
            Core::JSON::DecUInt32 Modifiers; // Output parameter. The modifier flags
            Core::JSON::DecUInt64 TimestampInSeconds; // Output parameter. The timestamp (in seconds) when the last key press occurred.
        }; // class GetLastKeyInfoResultData

        class IgnoreKeyInputsParamsData : public Core::JSON::Container {
        public:
            IgnoreKeyInputsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("ignore"), &Ignore);
            }

            bool IsValid() const
            {
                return (true);
            }

            IgnoreKeyInputsParamsData(const IgnoreKeyInputsParamsData&) = delete;
            IgnoreKeyInputsParamsData& operator=(const IgnoreKeyInputsParamsData&) = delete;

        public:
            Core::JSON::Boolean Ignore; // flag stating whether key inputs ignored
        }; // class IgnoreKeyInputsParamsData

        class InjectKeyParamsData : public Core::JSON::Container {
        public:
            InjectKeyParamsData()
                : Core::JSON::Container()
            {
                Add(_T("keyCode"), &KeyCode);
                Add(_T("modifiers"), &Modifiers);
            }

            bool IsValid() const
            {
                return (true);
            }

            InjectKeyParamsData(const InjectKeyParamsData&) = delete;
            InjectKeyParamsData& operator=(const InjectKeyParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 KeyCode; // Key code to be injected, modifiers :  JSON String format with one or more modifiers
            Core::JSON::String Modifiers; // Simulates a key press event with optional modifiers.
        }; // class InjectKeyParamsData

        class KeyRepeatConfigParamsData : public Core::JSON::Container {
        public:
            KeyRepeatConfigParamsData()
                : Core::JSON::Container()
            {
                Add(_T("input"), &Input);
                Add(_T("keyConfig"), &KeyConfig);
            }

            bool IsValid() const
            {
                return (true);
            }

            KeyRepeatConfigParamsData(const KeyRepeatConfigParamsData&) = delete;
            KeyRepeatConfigParamsData& operator=(const KeyRepeatConfigParamsData&) = delete;

        public:
            Core::JSON::String Input; // input type (default/keyboard)
            Core::JSON::String KeyConfig; // JSON String format with enabled, initialDelay and repeatInterval
        }; // class KeyRepeatConfigParamsData

        class OnUserInactivityParamsData : public Core::JSON::Container {
        public:
            OnUserInactivityParamsData()
                : Core::JSON::Container()
            {
                Add(_T("minutes"), &Minutes);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnUserInactivityParamsData(const OnUserInactivityParamsData&) = delete;
            OnUserInactivityParamsData& operator=(const OnUserInactivityParamsData&) = delete;

        public:
            Core::JSON::Double Minutes; // notify how long user is inactive state
        }; // class OnUserInactivityParamsData

        class SetInactivityIntervalParamsData : public Core::JSON::Container {
        public:
            SetInactivityIntervalParamsData()
                : Core::JSON::Container()
            {
                Add(_T("interval"), &Interval);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetInactivityIntervalParamsData(const SetInactivityIntervalParamsData&) = delete;
            SetInactivityIntervalParamsData& operator=(const SetInactivityIntervalParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 Interval; // time interval set for inactivity
        }; // class SetInactivityIntervalParamsData

        class SetVisibleParamsData : public Core::JSON::Container {
        public:
            SetVisibleParamsData()
                : Core::JSON::Container()
            {
                Add(_T("client"), &Client);
                Add(_T("visible"), &Visible);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetVisibleParamsData(const SetVisibleParamsData&) = delete;
            SetVisibleParamsData& operator=(const SetVisibleParamsData&) = delete;

        public:
            Core::JSON::String Client; // client name or application instance ID
            Core::JSON::Boolean Visible; // boolean indicating the visibility status: `true` for visible, `false` for hide.
        }; // class SetVisibleParamsData

    } // namespace RDKWindowManager

} // namespace JsonData

}

