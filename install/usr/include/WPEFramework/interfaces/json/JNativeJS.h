// Generated automatically from 'INativeJS.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_NativeJS.h"
#include <interfaces/INativeJS.h>

namespace WPEFramework {

namespace Exchange {

    namespace JNativeJS {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, INativeJS* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JNativeJS"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'createApplication' - Create a NativeJS application
            _module_.Register<JsonData::NativeJS::CreateApplicationParamsData, Core::JSON::DecUInt32>(_T("createApplication"), 
                [_impl_](const JsonData::NativeJS::CreateApplicationParamsData& params, Core::JSON::DecUInt32& id) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _options{params.Options};
                    uint32_t _id{};

                    _errorCode = _impl_->CreateApplication(_options, _id);

                    if (_errorCode == Core::ERROR_NONE) {
                        id = _id;
                    }

                    return (_errorCode);
                });

            // Method: 'runApplication' - run a NativeJS application
            _module_.Register<JsonData::NativeJS::RunApplicationParamsData, void>(_T("runApplication"), 
                [_impl_](const JsonData::NativeJS::RunApplicationParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _id{params.Id};
                    const string _url{params.Url};

                    _errorCode = _impl_->RunApplication(_id, _url);

                    return (_errorCode);
                });

            // Method: 'runJavaScript' - run a NativeJS code
            _module_.Register<JsonData::NativeJS::RunJavaScriptParamsData, void>(_T("runJavaScript"), 
                [_impl_](const JsonData::NativeJS::RunJavaScriptParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _id{params.Id};
                    const string _code{params.Code};

                    _errorCode = _impl_->RunJavaScript(_id, _code);

                    return (_errorCode);
                });

            // Method: 'getApplications' - Get details of existing plugin
            _module_.Register<void, void>(_T("getApplications"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->GetApplications();

                    return (_errorCode);
                });

            // Method: 'terminateApplication' - Destroy a running NativeJS application
            _module_.Register<JsonData::NativeJS::TerminateApplicationParamsData, void>(_T("terminateApplication"), 
                [_impl_](const JsonData::NativeJS::TerminateApplicationParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const uint32_t _id{params.Id};

                    _errorCode = _impl_->TerminateApplication(_id);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("createApplication"));
            _module_.Unregister(_T("runApplication"));
            _module_.Unregister(_T("runJavaScript"));
            _module_.Unregister(_T("getApplications"));
            _module_.Unregister(_T("terminateApplication"));
        }

        POP_WARNING()

    } // namespace JNativeJS

} // namespace Exchange

} // namespace WPEFramework

