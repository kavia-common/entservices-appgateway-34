// Generated automatically from 'IDownloadManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_DownloadManager.h"
#include <interfaces/IDownloadManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JDownloadManager {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IDownloadManager* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JDownloadManager"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'download' - Download Start downloading a file from a specified URL with custom options
            _module_.Register<JsonData::DownloadManager::DownloadParamsData, Core::JSON::String>(_T("download"), 
                [_impl_](const JsonData::DownloadManager::DownloadParamsData& params, Core::JSON::String& downloadId) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _url{params.Url};
                    const Exchange::IDownloadManager::Options _options(params.Options);
                    string _downloadId{};

                    _errorCode = _impl_->Download(_url, _options, _downloadId);

                    if (_errorCode == Core::ERROR_NONE) {
                        downloadId = _downloadId;
                    }

                    return (_errorCode);
                });

            // Method: 'pause' - Pause an active download session
            _module_.Register<JsonData::DownloadManager::PauseParamsInfo, void>(_T("pause"), 
                [_impl_](const JsonData::DownloadManager::PauseParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};

                    _errorCode = _impl_->Pause(_downloadId);

                    return (_errorCode);
                });

            // Method: 'resume' - Resume a paused download session
            _module_.Register<JsonData::DownloadManager::PauseParamsInfo, void>(_T("resume"), 
                [_impl_](const JsonData::DownloadManager::PauseParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};

                    _errorCode = _impl_->Resume(_downloadId);

                    return (_errorCode);
                });

            // Method: 'cancel' - Cancel an ongoing download session
            _module_.Register<JsonData::DownloadManager::PauseParamsInfo, void>(_T("cancel"), 
                [_impl_](const JsonData::DownloadManager::PauseParamsInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};

                    _errorCode = _impl_->Cancel(_downloadId);

                    return (_errorCode);
                });

            // Method: 'delete' - Delete a downloaded file from the system using its locator path
            _module_.Register<JsonData::DownloadManager::DeleteParamsData, void>(_T("delete"), 
                [_impl_](const JsonData::DownloadManager::DeleteParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _fileLocator{params.FileLocator};

                    _errorCode = _impl_->Delete(_fileLocator);

                    return (_errorCode);
                });

            // Method: 'progress' - Progress Query current download progress
            _module_.Register<JsonData::DownloadManager::PauseParamsInfo, Core::JSON::DecUInt8>(_T("progress"), 
                [_impl_](const JsonData::DownloadManager::PauseParamsInfo& params, Core::JSON::DecUInt8& percent) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};
                    uint8_t _percent{};

                    _errorCode = _impl_->Progress(_downloadId, _percent);

                    if (_errorCode == Core::ERROR_NONE) {
                        percent = _percent;
                    }

                    return (_errorCode);
                });

            // Method: 'getStorageDetails' - GetStorageDetails Get information about storage space availability
            _module_.Register<void, JsonData::DownloadManager::GetStorageDetailsResultData>(_T("getStorageDetails"), 
                [_impl_](JsonData::DownloadManager::GetStorageDetailsResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    uint32_t _quotaKb{};
                    uint32_t _usedKb{};

                    _errorCode = _impl_->GetStorageDetails(_quotaKb, _usedKb);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.QuotaKb = _quotaKb;
                        result.UsedKb = _usedKb;
                    }

                    return (_errorCode);
                });

            // Method: 'rateLimit' - RateLimit Set rate limiting for a specific download session
            _module_.Register<JsonData::DownloadManager::RateLimitParamsData, void>(_T("rateLimit"), 
                [_impl_](const JsonData::DownloadManager::RateLimitParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};
                    const uint32_t _limit{params.Limit};

                    _errorCode = _impl_->RateLimit(_downloadId, _limit);

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("download"));
            _module_.Unregister(_T("pause"));
            _module_.Unregister(_T("resume"));
            _module_.Unregister(_T("cancel"));
            _module_.Unregister(_T("delete"));
            _module_.Unregister(_T("progress"));
            _module_.Unregister(_T("getStorageDetails"));
            _module_.Unregister(_T("rateLimit"));
        }

        namespace Event {

            // Event: 'onAppDownloadStatus' - OnAppDownloadStatus Callback for status changes of app downloads
            static void OnAppDownloadStatus(const JSONRPC& _module_, const JsonData::DownloadManager::OnAppDownloadStatusParamsData& params)
            {
                _module_.Notify(_T("onAppDownloadStatus"), params);
            }

            // Event: 'onAppDownloadStatus' - OnAppDownloadStatus Callback for status changes of app downloads
            static void OnAppDownloadStatus(const JSONRPC& _module_, const Core::JSON::String& downloadStatus)
            {
                JsonData::DownloadManager::OnAppDownloadStatusParamsData _params_;
                _params_.DownloadStatus = downloadStatus;

                OnAppDownloadStatus(_module_, _params_);
            }

            // Event: 'onAppDownloadStatus' - OnAppDownloadStatus Callback for status changes of app downloads
            static void OnAppDownloadStatus(const JSONRPC& _module_, const string& downloadStatus)
            {
                JsonData::DownloadManager::OnAppDownloadStatusParamsData _params_;
                _params_.DownloadStatus = downloadStatus;

                OnAppDownloadStatus(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JDownloadManager

} // namespace Exchange

} // namespace WPEFramework

