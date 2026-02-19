// Generated automatically from 'IAppGateway.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_AppGatewayResolver.h"
#include <interfaces/IAppGateway.h>

namespace WPEFramework {

namespace Exchange {

    namespace JAppGatewayResolver {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IAppGatewayResolver* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JAppGatewayResolver"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'configure' - Adds additional Resolution paths to the gateway
            _module_.Register<JsonData::AppGatewayResolver::ConfigureParamsData, void>(_T("configure"), 
                [_impl_](const JsonData::AppGatewayResolver::ConfigureParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    std::list<string> _elements;
                    auto _Iterator = params.Paths.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>* const _paths{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>>(_elements)};

                    ASSERT(_paths != nullptr); 

                    if ((_paths != nullptr)) {
                        _errorCode = _impl_->Configure(_paths);
                        _paths->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("configure"));
        }

        POP_WARNING()

    } // namespace JAppGatewayResolver

} // namespace Exchange

} // namespace WPEFramework

