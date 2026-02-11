// Generated automatically from 'IAnalytics.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_Analytics.h"
#include <interfaces/IAnalytics.h>

namespace WPEFramework {

namespace Exchange {

    namespace JAnalytics {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IAnalytics* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JAnalytics"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'SendEvent' - Send an event to the analytics server
            _module_.Register<JsonData::Analytics::SendEventParamsInfo, void>(_T("SendEvent"), 
                [_impl_](const JsonData::Analytics::SendEventParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _eventName{params.EventName};
                    const string _eventVersion{params.EventVersion};
                    const string _eventSource{params.EventSource};
                    const string _eventSourceVersion{params.EventSourceVersion};
                    std::list<string> _elements;
                    auto _Iterator = params.CetList.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>* const _cetList{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>>(_elements)};
                    const uint64_t _epochTimestamp{params.EpochTimestamp};
                    const uint64_t _uptimeTimestamp{params.UptimeTimestamp};
                    const string _appId{params.AppId};
                    const string _eventPayload{params.EventPayload};
                    const string _additionalContext{params.AdditionalContext};

                    ASSERT(_cetList != nullptr); 

                    if ((_cetList != nullptr)) {
                        _errorCode = _impl_->SendEvent(_eventName, _eventVersion, _eventSource, _eventSourceVersion, _cetList, _epochTimestamp,
                                 _uptimeTimestamp, _appId, _eventPayload, _additionalContext);
                        _cetList->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    return (_errorCode);
                });

            // Method: 'sendEvent' - Send an event to the analytics server
            _module_.Register<JsonData::Analytics::SendEventParamsInfo, void>(_T("sendEvent"), 
                [_impl_](const JsonData::Analytics::SendEventParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _eventName{params.EventName};
                    const string _eventVersion{params.EventVersion};
                    const string _eventSource{params.EventSource};
                    const string _eventSourceVersion{params.EventSourceVersion};
                    std::list<string> _elements;
                    auto _Iterator = params.CetList.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>* const _cetList{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>>(_elements)};
                    const uint64_t _epochTimestamp{params.EpochTimestamp};
                    const uint64_t _uptimeTimestamp{params.UptimeTimestamp};
                    const string _appId{params.AppId};
                    const string _eventPayload{params.EventPayload};
                    const string _additionalContext{params.AdditionalContext};

                    ASSERT(_cetList != nullptr); 

                    if ((_cetList != nullptr)) {
                        _errorCode = _impl_->SendEvent(_eventName, _eventVersion, _eventSource, _eventSourceVersion, _cetList, _epochTimestamp,
                                 _uptimeTimestamp, _appId, _eventPayload, _additionalContext);
                        _cetList->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("SendEvent"));
            _module_.Unregister(_T("sendEvent"));
        }

        POP_WARNING()

    } // namespace JAnalytics

} // namespace Exchange

} // namespace WPEFramework

