// C++ classes for ScreenCapture API JSON-RPC API.
// Generated automatically from 'IScreenCapture.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IScreenCapture.h>

namespace WPEFramework {

namespace JsonData {

    namespace ScreenCapture {

        // Common classes
        //

        class ResultInfo : public Core::JSON::Container {
        public:
            ResultInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            ResultInfo(const Exchange::IScreenCapture::Result& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            ResultInfo& operator=(const Exchange::IScreenCapture::Result& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IScreenCapture::Result() const
            {
                Exchange::IScreenCapture::Result _value{};
                _value.success = Success;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::Boolean Success; // Takes a screenshot and uploads it to the specified URL
        }; // class ResultInfo

        // Method params/result classes
        //

        class SendScreenshotParamsData : public Core::JSON::Container {
        public:
            SendScreenshotParamsData()
                : Core::JSON::Container()
            {
                Add(_T("callGUID"), &CallGUID);
            }

            bool IsValid() const
            {
                return (true);
            }

            SendScreenshotParamsData(const SendScreenshotParamsData&) = delete;
            SendScreenshotParamsData& operator=(const SendScreenshotParamsData&) = delete;

        public:
            Core::JSON::String CallGUID; // -  A unique identifier of a call. The identifier is used to find a corresponding uploadComplete event
        }; // class SendScreenshotParamsData

        class UploadCompleteParamsData : public Core::JSON::Container {
        public:
            UploadCompleteParamsData()
                : Core::JSON::Container()
            {
                Add(_T("status"), &Status);
                Add(_T("message"), &Message);
                Add(_T("call_guid"), &Call_guid);
            }

            bool IsValid() const
            {
                return (true);
            }

            UploadCompleteParamsData(const UploadCompleteParamsData&) = delete;
            UploadCompleteParamsData& operator=(const UploadCompleteParamsData&) = delete;

        public:
            Core::JSON::Boolean Status; // - in - boolean
            Core::JSON::String Message; // - in - string
            Core::JSON::String Call_guid; // - in - string
        }; // class UploadCompleteParamsData

        class UploadScreenCaptureParamsData : public Core::JSON::Container {
        public:
            UploadScreenCaptureParamsData()
                : Core::JSON::Container()
            {
                Add(_T("url"), &Url);
                Add(_T("callGUID"), &CallGUID);
            }

            bool IsValid() const
            {
                return (true);
            }

            UploadScreenCaptureParamsData(const UploadScreenCaptureParamsData&) = delete;
            UploadScreenCaptureParamsData& operator=(const UploadScreenCaptureParamsData&) = delete;

        public:
            Core::JSON::String Url; // - in - string
            Core::JSON::String CallGUID; // - in - string
        }; // class UploadScreenCaptureParamsData

    } // namespace ScreenCapture

} // namespace JsonData

}

