// C++ classes for LifecycleManagerState API JSON-RPC API.
// Generated automatically from 'ILifecycleManagerState.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/ILifecycleManagerState.h>

namespace WPEFramework {

namespace JsonData {

    namespace LifecycleManagerState {

        // Method params/result classes
        //

        class AppReadyParamsData : public Core::JSON::Container {
        public:
            AppReadyParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
            }

            bool IsValid() const
            {
                return (true);
            }

            AppReadyParamsData(const AppReadyParamsData&) = delete;
            AppReadyParamsData& operator=(const AppReadyParamsData&) = delete;

        public:
            Core::JSON::String AppId; // Response api call to appInitializing API
        }; // class AppReadyParamsData

        class CloseAppParamsData : public Core::JSON::Container {
        public:
            CloseAppParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("closeReason"), &CloseReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            CloseAppParamsData(const CloseAppParamsData&) = delete;
            CloseAppParamsData& operator=(const CloseAppParamsData&) = delete;

        public:
            Core::JSON::String AppId; // close the app
            Core::JSON::EnumType<Exchange::ILifecycleManagerState::AppCloseReason> CloseReason; // closed reason for application
        }; // class CloseAppParamsData

        class OnAppLifecycleStateChangedParamsData : public Core::JSON::Container {
        public:
            OnAppLifecycleStateChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("appInstanceId"), &AppInstanceId);
                Add(_T("oldLifecycleState"), &OldLifecycleState);
                Add(_T("newLifecycleState"), &NewLifecycleState);
                Add(_T("navigationIntent"), &NavigationIntent);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppLifecycleStateChangedParamsData(const OnAppLifecycleStateChangedParamsData&) = delete;
            OnAppLifecycleStateChangedParamsData& operator=(const OnAppLifecycleStateChangedParamsData&) = delete;

        public:
            Core::JSON::String AppId; // Notifies the new state
            Core::JSON::String AppInstanceId; // Notifies the new state
            Core::JSON::EnumType<Exchange::ILifecycleManager::LifecycleState> OldLifecycleState; // Notifies the new state
            Core::JSON::EnumType<Exchange::ILifecycleManager::LifecycleState> NewLifecycleState; // Notifies the new state
            Core::JSON::String NavigationIntent; // Notifies the new state
        }; // class OnAppLifecycleStateChangedParamsData

        class StateChangeCompleteParamsData : public Core::JSON::Container {
        public:
            StateChangeCompleteParamsData()
                : Core::JSON::Container()
            {
                Add(_T("appId"), &AppId);
                Add(_T("stateChangedId"), &StateChangedId);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            StateChangeCompleteParamsData(const StateChangeCompleteParamsData&) = delete;
            StateChangeCompleteParamsData& operator=(const StateChangeCompleteParamsData&) = delete;

        public:
            Core::JSON::String AppId; // Response api call to appLifecycleStateChanged API
            Core::JSON::DecUInt32 StateChangedId; // state changed identifier
            Core::JSON::Boolean Success; // Response api call to appLifecycleStateChanged API
        }; // class StateChangeCompleteParamsData

    } // namespace LifecycleManagerState

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::ILifecycleManagerState::AppCloseReason)
ENUM_CONVERSION_HANDLER(Exchange::ILifecycleManager::LifecycleState)

}

