// Generated automatically from 'IFirmwareDownload.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_FirmwareDownload.h"
#include <interfaces/IFirmwareDownload.h>

namespace WPEFramework {

namespace Exchange {

    namespace JFirmwareDownload {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IFirmwareDownload* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JFirmwareDownload"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getDownloadedFirmwareInfo' - Returns information about firmware downloads
            _module_.Register<void, JsonData::FirmwareDownload::GetDownloadedFirmwareInfoResultData>(_T("getDownloadedFirmwareInfo"), 
                [_impl_](JsonData::FirmwareDownload::GetDownloadedFirmwareInfoResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _currentFWVersion{};
                    string _downloadedFWVersion{};
                    string _downloadedFWLocation{};
                    bool _isRebootDeferred{};

                    _errorCode = _impl_->GetDownloadedFirmwareInfo(_currentFWVersion, _downloadedFWVersion, _downloadedFWLocation, _isRebootDeferred);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.CurrentFWVersion = _currentFWVersion;
                        result.DownloadedFWVersion = _downloadedFWVersion;
                        result.DownloadedFWLocation = _downloadedFWLocation;
                        result.IsRebootDeferred = _isRebootDeferred;
                    }

                    return (_errorCode);
                });

            // Method: 'getFirmwareDownloadPercent' - Gets the current download percentage
            _module_.Register<void, JsonData::FirmwareDownload::FirmwareDownloadPercentData>(_T("getFirmwareDownloadPercent"), 
                [_impl_](JsonData::FirmwareDownload::FirmwareDownloadPercentData& firmwareDownloadPercent) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IFirmwareDownload::FirmwareDownloadPercent _firmwareDownloadPercent{};

                    _errorCode = _impl_->GetFirmwareDownloadPercent(_firmwareDownloadPercent);

                    if (_errorCode == Core::ERROR_NONE) {
                        firmwareDownloadPercent = _firmwareDownloadPercent;
                    }

                    return (_errorCode);
                });

            // Method: 'searchFirmware' - Search for any available firmware ( in the remote server - for ex
            _module_.Register<void, void>(_T("searchFirmware"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->SearchFirmware();

                    return (_errorCode);
                });

            // Method: 'getDownloadState' - Retrieve the current state of the download process
            _module_.Register<void, JsonData::FirmwareDownload::FirmwareDownloadStateData>(_T("getDownloadState"), 
                [_impl_](JsonData::FirmwareDownload::FirmwareDownloadStateData& downloadState) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IFirmwareDownload::FirmwareDownloadState _downloadState{};

                    _errorCode = _impl_->GetDownloadState(_downloadState);

                    if (_errorCode == Core::ERROR_NONE) {
                        downloadState = _downloadState;
                    }

                    return (_errorCode);
                });

            // Method: 'getDownloadFailureReason' - Gets the last firmware download failure reason
            _module_.Register<void, JsonData::FirmwareDownload::DownloadFailureReasonData>(_T("getDownloadFailureReason"), 
                [_impl_](JsonData::FirmwareDownload::DownloadFailureReasonData& downloadFailureReason) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IFirmwareDownload::DownloadFailureReason _downloadFailureReason{};

                    _errorCode = _impl_->GetDownloadFailureReason(_downloadFailureReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        downloadFailureReason = _downloadFailureReason;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getDownloadedFirmwareInfo"));
            _module_.Unregister(_T("getFirmwareDownloadPercent"));
            _module_.Unregister(_T("searchFirmware"));
            _module_.Unregister(_T("getDownloadState"));
            _module_.Unregister(_T("getDownloadFailureReason"));
        }

        namespace Event {

            // Event: 'onFirmwareAvailable' - Triggered when the SearchFirmware asynchronous method is invoked
            static void OnFirmwareAvailable(const JSONRPC& _module_, const JsonData::FirmwareDownload::OnFirmwareAvailableParamsData& params)
            {
                _module_.Notify(_T("onFirmwareAvailable"), params);
            }

            // Event: 'onFirmwareAvailable' - Triggered when the SearchFirmware asynchronous method is invoked
            static void OnFirmwareAvailable(const JSONRPC& _module_, const Core::JSON::DecSInt32& searchStatus, const Core::JSON::String& serverResponse,
                     const Core::JSON::Boolean& firmwareAvailable, const Core::JSON::String& firmwareVersion, const Core::JSON::Boolean& rebootImmediately)
            {
                JsonData::FirmwareDownload::OnFirmwareAvailableParamsData _params_;
                _params_.SearchStatus = searchStatus;
                _params_.ServerResponse = serverResponse;
                _params_.FirmwareAvailable = firmwareAvailable;
                _params_.FirmwareVersion = firmwareVersion;
                _params_.RebootImmediately = rebootImmediately;

                OnFirmwareAvailable(_module_, _params_);
            }

            // Event: 'onFirmwareAvailable' - Triggered when the SearchFirmware asynchronous method is invoked
            static void OnFirmwareAvailable(const JSONRPC& _module_, const int32_t& searchStatus, const string& serverResponse, const bool& firmwareAvailable,
                     const string& firmwareVersion, const bool& rebootImmediately)
            {
                JsonData::FirmwareDownload::OnFirmwareAvailableParamsData _params_;
                _params_.SearchStatus = searchStatus;
                _params_.ServerResponse = serverResponse;
                _params_.FirmwareAvailable = firmwareAvailable;
                _params_.FirmwareVersion = firmwareVersion;
                _params_.RebootImmediately = rebootImmediately;

                OnFirmwareAvailable(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JFirmwareDownload

} // namespace Exchange

} // namespace WPEFramework

