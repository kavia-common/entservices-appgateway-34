// C++ classes for FrameRate API JSON-RPC API.
// Generated automatically from 'IFrameRate.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IFrameRate.h>

namespace WPEFramework {

namespace JsonData {

    namespace FrameRate {

        // Common classes
        //

        class OnDisplayFrameRateChangingParamsInfo : public Core::JSON::Container {
        public:
            OnDisplayFrameRateChangingParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("displayFrameRate"), &DisplayFrameRate);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnDisplayFrameRateChangingParamsInfo(const OnDisplayFrameRateChangingParamsInfo&) = delete;
            OnDisplayFrameRateChangingParamsInfo& operator=(const OnDisplayFrameRateChangingParamsInfo&) = delete;

        public:
            Core::JSON::String DisplayFrameRate; // - in - string
        }; // class OnDisplayFrameRateChangingParamsInfo

        // Method params/result classes
        //

        class GetDisplayFrameRateResultData : public Core::JSON::Container {
        public:
            GetDisplayFrameRateResultData()
                : Core::JSON::Container()
            {
                Add(_T("framerate"), &Framerate);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetDisplayFrameRateResultData(const GetDisplayFrameRateResultData&) = delete;
            GetDisplayFrameRateResultData& operator=(const GetDisplayFrameRateResultData&) = delete;

        public:
            Core::JSON::String Framerate; // - out - string
            Core::JSON::Boolean Success; // - out - boolean
        }; // class GetDisplayFrameRateResultData

        class GetFrmModeResultData : public Core::JSON::Container {
        public:
            GetFrmModeResultData()
                : Core::JSON::Container()
            {
                Add(_T("auto-frm-mode"), &FramerateMode);
                Add(_T("success"), &Success);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetFrmModeResultData(const GetFrmModeResultData&) = delete;
            GetFrmModeResultData& operator=(const GetFrmModeResultData&) = delete;

        public:
            Core::JSON::DecSInt32 FramerateMode; // Gets the current auto framerate mode.
            Core::JSON::Boolean Success; // - out - boolean
        }; // class GetFrmModeResultData

        class OnFpsEventParamsData : public Core::JSON::Container {
        public:
            OnFpsEventParamsData()
                : Core::JSON::Container()
            {
                Add(_T("average"), &Average);
                Add(_T("min"), &Min);
                Add(_T("max"), &Max);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnFpsEventParamsData(const OnFpsEventParamsData&) = delete;
            OnFpsEventParamsData& operator=(const OnFpsEventParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Average; // - in - int
            Core::JSON::DecSInt32 Min; // - in - int
            Core::JSON::DecSInt32 Max; // - in - int
        }; // class OnFpsEventParamsData

        class SetCollectionFrequencyParamsData : public Core::JSON::Container {
        public:
            SetCollectionFrequencyParamsData()
                : Core::JSON::Container()
            {
                Add(_T("frequency"), &Frequency);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetCollectionFrequencyParamsData(const SetCollectionFrequencyParamsData&) = delete;
            SetCollectionFrequencyParamsData& operator=(const SetCollectionFrequencyParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Frequency; // - in -  int
        }; // class SetCollectionFrequencyParamsData

        class SetDisplayFrameRateParamsData : public Core::JSON::Container {
        public:
            SetDisplayFrameRateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("framerate"), &Framerate);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetDisplayFrameRateParamsData(const SetDisplayFrameRateParamsData&) = delete;
            SetDisplayFrameRateParamsData& operator=(const SetDisplayFrameRateParamsData&) = delete;

        public:
            Core::JSON::String Framerate; // - in - string
        }; // class SetDisplayFrameRateParamsData

        class SetFrmModeParamsData : public Core::JSON::Container {
        public:
            SetFrmModeParamsData()
                : Core::JSON::Container()
            {
                Add(_T("frmmode"), &Frmmode);
            }

            bool IsValid() const
            {
                return (true);
            }

            SetFrmModeParamsData(const SetFrmModeParamsData&) = delete;
            SetFrmModeParamsData& operator=(const SetFrmModeParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Frmmode; // - in - int
        }; // class SetFrmModeParamsData

        class UpdateFpsParamsData : public Core::JSON::Container {
        public:
            UpdateFpsParamsData()
                : Core::JSON::Container()
            {
                Add(_T("newFpsValue"), &NewFpsValue);
            }

            bool IsValid() const
            {
                return (true);
            }

            UpdateFpsParamsData(const UpdateFpsParamsData&) = delete;
            UpdateFpsParamsData& operator=(const UpdateFpsParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 NewFpsValue; // - in - int
        }; // class UpdateFpsParamsData

    } // namespace FrameRate

} // namespace JsonData

}

