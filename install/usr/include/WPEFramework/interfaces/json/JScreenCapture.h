// Generated automatically from 'IScreenCapture.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_ScreenCapture.h"
#include <interfaces/IScreenCapture.h>

namespace WPEFramework {

namespace Exchange {

    namespace JScreenCapture {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IScreenCapture* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JScreenCapture"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'uploadScreenCapture' - Takes a screenshot and uploads it to the specified URL
            _module_.Register<JsonData::ScreenCapture::UploadScreenCaptureParamsData, JsonData::ScreenCapture::ResultInfo>(_T("uploadScreenCapture"), 
                [_impl_](const JsonData::ScreenCapture::UploadScreenCaptureParamsData& params, JsonData::ScreenCapture::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _url{params.Url};
                    const string _callGUID{params.CallGUID};
                    Exchange::IScreenCapture::Result _result{};

                    _errorCode = _impl_->UploadScreenCapture(_url, _callGUID, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'sendScreenshot' - Takes a screenshot and uploads it to the specified URL
            _module_.Register<JsonData::ScreenCapture::SendScreenshotParamsData, JsonData::ScreenCapture::ResultInfo>(_T("sendScreenshot"), 
                [_impl_](const JsonData::ScreenCapture::SendScreenshotParamsData& params, JsonData::ScreenCapture::ResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _callGUID{params.CallGUID};
                    Exchange::IScreenCapture::Result _result{};

                    _errorCode = _impl_->SendScreenshot(_callGUID, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("uploadScreenCapture"));
            _module_.Unregister(_T("sendScreenshot"));
        }

        namespace Event {

            // Event: 'uploadComplete' - Triggered after uploading a screen capture
            static void UploadComplete(const JSONRPC& _module_, const JsonData::ScreenCapture::UploadCompleteParamsData& params)
            {
                _module_.Notify(_T("uploadComplete"), params);
            }

            // Event: 'uploadComplete' - Triggered after uploading a screen capture
            static void UploadComplete(const JSONRPC& _module_, const Core::JSON::Boolean& status, const Core::JSON::String& message,
                     const Core::JSON::String& call_guid)
            {
                JsonData::ScreenCapture::UploadCompleteParamsData _params_;
                _params_.Status = status;
                _params_.Message = message;
                _params_.Call_guid = call_guid;

                UploadComplete(_module_, _params_);
            }

            // Event: 'uploadComplete' - Triggered after uploading a screen capture
            static void UploadComplete(const JSONRPC& _module_, const bool& status, const string& message, const string& call_guid)
            {
                JsonData::ScreenCapture::UploadCompleteParamsData _params_;
                _params_.Status = status;
                _params_.Message = message;
                _params_.Call_guid = call_guid;

                UploadComplete(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JScreenCapture

} // namespace Exchange

} // namespace WPEFramework

