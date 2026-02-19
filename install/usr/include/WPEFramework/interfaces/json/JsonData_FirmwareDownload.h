// C++ classes for FirmwareDownload API JSON-RPC API.
// Generated automatically from 'IFirmwareDownload.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IFirmwareDownload.h>

namespace WPEFramework {

namespace JsonData {

    namespace FirmwareDownload {

        // Method params/result classes
        //

        class DownloadFailureReasonData : public Core::JSON::Container {
        public:
            DownloadFailureReasonData()
                : Core::JSON::Container()
            {
                _Init();
            }

            DownloadFailureReasonData(const Exchange::IFirmwareDownload::DownloadFailureReason& _other)
                : Core::JSON::Container()
            {
                FailureReason = _other.failureReason;
                _Init();
            }

            DownloadFailureReasonData& operator=(const Exchange::IFirmwareDownload::DownloadFailureReason& _rhs)
            {
                FailureReason = _rhs.failureReason;
                return (*this);
            }

            operator Exchange::IFirmwareDownload::DownloadFailureReason() const
            {
                Exchange::IFirmwareDownload::DownloadFailureReason _value{};
                _value.failureReason = FailureReason;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("failureReason"), &FailureReason);
            }

        public:
            Core::JSON::String FailureReason; // firmware download failure reason
        }; // class DownloadFailureReasonData

        class FirmwareDownloadStateData : public Core::JSON::Container {
        public:
            FirmwareDownloadStateData()
                : Core::JSON::Container()
            {
                _Init();
            }

            FirmwareDownloadStateData(const Exchange::IFirmwareDownload::FirmwareDownloadState& _other)
                : Core::JSON::Container()
            {
                DownloadState = _other.downloadState;
                _Init();
            }

            FirmwareDownloadStateData& operator=(const Exchange::IFirmwareDownload::FirmwareDownloadState& _rhs)
            {
                DownloadState = _rhs.downloadState;
                return (*this);
            }

            operator Exchange::IFirmwareDownload::FirmwareDownloadState() const
            {
                Exchange::IFirmwareDownload::FirmwareDownloadState _value{};
                _value.downloadState = DownloadState;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("downloadState"), &DownloadState);
            }

        public:
            Core::JSON::String DownloadState; // current state of the download process
        }; // class FirmwareDownloadStateData

        class GetDownloadedFirmwareInfoResultData : public Core::JSON::Container {
        public:
            GetDownloadedFirmwareInfoResultData()
                : Core::JSON::Container()
            {
                Add(_T("currentFWVersion"), &CurrentFWVersion);
                Add(_T("downloadedFWVersion"), &DownloadedFWVersion);
                Add(_T("downloadedFWLocation"), &DownloadedFWLocation);
                Add(_T("isRebootDeferred"), &IsRebootDeferred);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetDownloadedFirmwareInfoResultData(const GetDownloadedFirmwareInfoResultData&) = delete;
            GetDownloadedFirmwareInfoResultData& operator=(const GetDownloadedFirmwareInfoResultData&) = delete;

        public:
            Core::JSON::String CurrentFWVersion; // The current firmware version
            Core::JSON::String DownloadedFWVersion; // The downloaded firmware version
            Core::JSON::String DownloadedFWLocation; // The location of the downloaded firmware
            Core::JSON::Boolean IsRebootDeferred; // Whether the device should be rebooted
        }; // class GetDownloadedFirmwareInfoResultData

        class FirmwareDownloadPercentData : public Core::JSON::Container {
        public:
            FirmwareDownloadPercentData()
                : Core::JSON::Container()
            {
                _Init();
            }

            FirmwareDownloadPercentData(const Exchange::IFirmwareDownload::FirmwareDownloadPercent& _other)
                : Core::JSON::Container()
            {
                DownloadPercent = _other.downloadPercent;
                _Init();
            }

            FirmwareDownloadPercentData& operator=(const Exchange::IFirmwareDownload::FirmwareDownloadPercent& _rhs)
            {
                DownloadPercent = _rhs.downloadPercent;
                return (*this);
            }

            operator Exchange::IFirmwareDownload::FirmwareDownloadPercent() const
            {
                Exchange::IFirmwareDownload::FirmwareDownloadPercent _value{};
                _value.downloadPercent = DownloadPercent;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("downloadPercent"), &DownloadPercent);
            }

        public:
            Core::JSON::DecUInt32 DownloadPercent; // Current download percentage (0-100)
        }; // class FirmwareDownloadPercentData

        class OnFirmwareAvailableParamsData : public Core::JSON::Container {
        public:
            OnFirmwareAvailableParamsData()
                : Core::JSON::Container()
            {
                Add(_T("searchStatus"), &SearchStatus);
                Add(_T("serverResponse"), &ServerResponse);
                Add(_T("firmwareAvailable"), &FirmwareAvailable);
                Add(_T("firmwareVersion"), &FirmwareVersion);
                Add(_T("rebootImmediately"), &RebootImmediately);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnFirmwareAvailableParamsData(const OnFirmwareAvailableParamsData&) = delete;
            OnFirmwareAvailableParamsData& operator=(const OnFirmwareAvailableParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 SearchStatus; // Status of the firmware search operation
            Core::JSON::String ServerResponse; // Response message from the server
            Core::JSON::Boolean FirmwareAvailable; // Indicates whether new firmware is available
            Core::JSON::String FirmwareVersion; // Version string of the available firmware
            Core::JSON::Boolean RebootImmediately; // Indicates whether immediate reboot is required
        }; // class OnFirmwareAvailableParamsData

    } // namespace FirmwareDownload

} // namespace JsonData

}

