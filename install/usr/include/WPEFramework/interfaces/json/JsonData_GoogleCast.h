// C++ classes for GoogleCast API JSON-RPC API.
// Generated automatically from 'IGoogleCast.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IGoogleCast.h>

namespace WPEFramework {

namespace JsonData {

    namespace GoogleCast {

        // Common classes
        //

        class CastStatusInfo : public Core::JSON::Container {
        public:
            CastStatusInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            CastStatusInfo(const Exchange::IGoogleCast::CastStatus& _other)
                : Core::JSON::Container()
            {
                CastBuildNumber = _other.castBuildNumber;
                CastState = _other.castState;
                _Init();
            }

            CastStatusInfo& operator=(const Exchange::IGoogleCast::CastStatus& _rhs)
            {
                CastBuildNumber = _rhs.castBuildNumber;
                CastState = _rhs.castState;
                return (*this);
            }

            operator Exchange::IGoogleCast::CastStatus() const
            {
                Exchange::IGoogleCast::CastStatus _value{};
                _value.castBuildNumber = CastBuildNumber;
                _value.castState = CastState;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("cast_build_number"), &CastBuildNumber);
                Add(_T("cast_state"), &CastState);
            }

        public:
            Core::JSON::String CastBuildNumber; // Build number of the currently running Cast shell.
            Core::JSON::EnumType<Exchange::IGoogleCast::CastState> CastState; // Current cast shell state.
        }; // class CastStatusInfo

        // Method params/result classes
        //

    } // namespace GoogleCast

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IGoogleCast::CastState)

}

