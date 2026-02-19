// C++ classes for Amazon API JSON-RPC API.
// Generated automatically from 'IAmazonPrime.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAmazonPrime.h>

namespace WPEFramework {

namespace JsonData {

    namespace Amazon {

        // Common classes
        //

        class SetDeepLinkParamsInfo : public Core::JSON::Container {
        public:
            SetDeepLinkParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("command"), &Command);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetDeepLinkParamsInfo(const SetDeepLinkParamsInfo&) = delete;
            SetDeepLinkParamsInfo& operator=(const SetDeepLinkParamsInfo&) = delete;

        public:
            Core::JSON::String Command; // : app Deeplink command
        }; // class SetDeepLinkParamsInfo

        // Method params/result classes
        //

        class StateChangeParamsData : public Core::JSON::Container {
        public:
            StateChangeParamsData()
                : Core::JSON::Container()
            {
                Add(_T("state"), &State);
            }

            bool IsValid() const
            {
                return (true);
            }

            StateChangeParamsData(const StateChangeParamsData&) = delete;
            StateChangeParamsData& operator=(const StateChangeParamsData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IAmazon::State> State; // current state of amazon prime
        }; // class StateChangeParamsData

    } // namespace Amazon

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IAmazon::State)

}

