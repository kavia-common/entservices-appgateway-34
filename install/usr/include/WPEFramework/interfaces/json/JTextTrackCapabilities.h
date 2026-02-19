// Generated automatically from 'ITextTrack.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_TextTrackCapabilities.h"
#include <interfaces/ITextTrack.h>

namespace WPEFramework {

namespace Exchange {

    namespace JTextTrackCapabilities {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ITextTrackCapabilities* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JTextTrackCapabilities"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getCapability' - Queries whether a specific TextTrack capability is supported by the implementation
            _module_.Register<JsonData::TextTrackCapabilities::GetCapabilityParamsData, Core::JSON::Boolean>(_T("getCapability"), 
                [_impl_](const JsonData::TextTrackCapabilities::GetCapabilityParamsData& params, Core::JSON::Boolean& hasCapability) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const Exchange::ITextTrackCapabilities::Capability _capability{params.Capability};
                    bool _hasCapability{};

                    _errorCode = _impl_->GetCapability(_capability, _hasCapability);

                    if (_errorCode == Core::ERROR_NONE) {
                        hasCapability = _hasCapability;
                    }

                    return (_errorCode);
                });

            // Method: 'getCapabilities' - Retrieves an iterator over all supported TextTrack capabilities
            _module_.Register<void, Core::JSON::ArrayType<Core::JSON::EnumType<Exchange::ITextTrackCapabilities::Capability>>>(_T("getCapabilities"), 
                [_impl_](Core::JSON::ArrayType<Core::JSON::EnumType<Exchange::ITextTrackCapabilities::Capability>>& capabilities) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<ITextTrackCapabilities::Capability, RPC::ID_VALUEITERATOR>* _capabilities{};

                    _errorCode = _impl_->GetCapabilities(_capabilities);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_capabilities != nullptr) {
                            Exchange::ITextTrackCapabilities::Capability _resultItem_{};
                            while (_capabilities->Next(_resultItem_) == true) { capabilities.Add() = _resultItem_; }
                            _capabilities->Release();
                        }
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getCapability"));
            _module_.Unregister(_T("getCapabilities"));
        }

        POP_WARNING()

    } // namespace JTextTrackCapabilities

} // namespace Exchange

} // namespace WPEFramework

