// Generated automatically from 'IGoogleCast.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_GoogleCast.h"
#include <interfaces/IGoogleCast.h>

namespace WPEFramework {

namespace Exchange {

    namespace JGoogleCast {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IGoogleCast* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JGoogleCast"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Property: 'getCastStatus' - Status of cast shell interfacing via Cast control API (r/o)
            _module_.Register<void, JsonData::GoogleCast::CastStatusInfo>(_T("getCastStatus"), 
                [_impl_](JsonData::GoogleCast::CastStatusInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IGoogleCast::CastStatus _result{};

                    _errorCode = _impl_->GetCastStatus(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Property: 'cast_status' - Status of cast shell interfacing via Cast control API (r/o)
            _module_.Register<void, JsonData::GoogleCast::CastStatusInfo>(_T("cast_status"), 
                [_impl_](JsonData::GoogleCast::CastStatusInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    // read-only property get
                    Exchange::IGoogleCast::CastStatus _result{};

                    _errorCode = _impl_->GetCastStatus(_result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getCastStatus"));
            _module_.Unregister(_T("cast_status"));
        }

        namespace Event {

            // Event: 'onStatusChanged' - Notifies that the GoogleCast status changed
            static void OnStatusChanged(const JSONRPC& _module_)
            {
                _module_.Notify(_T("onStatusChanged"));
                _module_.Notify(_T("onStatusChange"));
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JGoogleCast

} // namespace Exchange

} // namespace WPEFramework

