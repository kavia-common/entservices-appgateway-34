// Generated automatically from 'IAppPackageManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_PackageDownloader.h"
#include <interfaces/IAppPackageManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JPackageDownloader {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IPackageDownloader* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JPackageDownloader"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'download' - Download
            _module_.Register<JsonData::PackageDownloader::DownloadParamsData, JsonData::PackageDownloader::DownloadIdInfo>(_T("download"), 
                [_impl_](const JsonData::PackageDownloader::DownloadParamsData& params, JsonData::PackageDownloader::DownloadIdInfo& downloadId) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _url{params.Url};
                    const Exchange::IPackageDownloader::Options _options(params.Options);
                    Exchange::IPackageDownloader::DownloadId _downloadId{};

                    _errorCode = _impl_->Download(_url, _options, _downloadId);

                    if (_errorCode == Core::ERROR_NONE) {
                        downloadId = _downloadId;
                    }

                    return (_errorCode);
                });

            // Method: 'pause' - Pause
            _module_.Register<JsonData::PackageDownloader::DownloadIdInfo, void>(_T("pause"), 
                [_impl_](const JsonData::PackageDownloader::DownloadIdInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};

                    _errorCode = _impl_->Pause(_downloadId);

                    return (_errorCode);
                });

            // Method: 'resume' - Resume
            _module_.Register<JsonData::PackageDownloader::DownloadIdInfo, void>(_T("resume"), 
                [_impl_](const JsonData::PackageDownloader::DownloadIdInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};

                    _errorCode = _impl_->Resume(_downloadId);

                    return (_errorCode);
                });

            // Method: 'cancel' - Cancel
            _module_.Register<JsonData::PackageDownloader::DownloadIdInfo, void>(_T("cancel"), 
                [_impl_](const JsonData::PackageDownloader::DownloadIdInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};

                    _errorCode = _impl_->Cancel(_downloadId);

                    return (_errorCode);
                });

            // Method: 'delete' - Delete
            _module_.Register<JsonData::PackageDownloader::DeleteParamsData, void>(_T("delete"), 
                [_impl_](const JsonData::PackageDownloader::DeleteParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _fileLocator{params.FileLocator};

                    _errorCode = _impl_->Delete(_fileLocator);

                    return (_errorCode);
                });

            // Method: 'progress' - Progress
            _module_.Register<JsonData::PackageDownloader::DownloadIdInfo, JsonData::PackageDownloader::ProgressInfoData>(_T("progress"), 
                [_impl_](const JsonData::PackageDownloader::DownloadIdInfo& params, JsonData::PackageDownloader::ProgressInfoData& progress) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};
                    Exchange::IPackageDownloader::ProgressInfo _progress{};

                    _errorCode = _impl_->Progress(_downloadId, _progress);

                    if (_errorCode == Core::ERROR_NONE) {
                        progress = _progress;
                    }

                    return (_errorCode);
                });

            // Method: 'getStorageInformation' - GetStorageInformation
            _module_.Register<void, JsonData::PackageDownloader::GetStorageInformationResultData>(_T("getStorageInformation"), 
                [_impl_](JsonData::PackageDownloader::GetStorageInformationResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    uint32_t _quotaKb{};
                    uint32_t _usedKb{};

                    _errorCode = _impl_->GetStorageInformation(_quotaKb, _usedKb);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.QuotaKb = _quotaKb;
                        result.UsedKb = _usedKb;
                    }

                    return (_errorCode);
                });

            // Method: 'rateLimit' - RateLimit
            _module_.Register<JsonData::PackageDownloader::RateLimitParamsData, void>(_T("rateLimit"), 
                [_impl_](const JsonData::PackageDownloader::RateLimitParamsData& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _downloadId{params.DownloadId};
                    const uint64_t _limit{params.Limit};

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
            _module_.Unregister(_T("getStorageInformation"));
            _module_.Unregister(_T("rateLimit"));
        }

        POP_WARNING()

    } // namespace JPackageDownloader

} // namespace Exchange

} // namespace WPEFramework

