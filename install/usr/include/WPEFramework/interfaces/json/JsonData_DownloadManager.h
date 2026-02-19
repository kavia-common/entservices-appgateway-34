// C++ classes for DownloadManager API JSON-RPC API.
// Generated automatically from 'IDownloadManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IDownloadManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace DownloadManager {

        // Common classes
        //

        class PauseParamsInfo : public Core::JSON::Container {
        public:
            PauseParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("downloadId"), &DownloadId);
            }

            bool IsValid() const
            {
                return (true);
            }

            PauseParamsInfo(const PauseParamsInfo&) = delete;
            PauseParamsInfo& operator=(const PauseParamsInfo&) = delete;

        public:
            Core::JSON::String DownloadId; // Unique identifier of the download to pause
        }; // class PauseParamsInfo

        // Method params/result classes
        //

        class DeleteParamsData : public Core::JSON::Container {
        public:
            DeleteParamsData()
                : Core::JSON::Container()
            {
                Add(_T("fileLocator"), &FileLocator);
            }

            bool IsValid() const
            {
                return (true);
            }

            DeleteParamsData(const DeleteParamsData&) = delete;
            DeleteParamsData& operator=(const DeleteParamsData&) = delete;

        public:
            Core::JSON::String FileLocator; // File path or locator of the file to be deleted
        }; // class DeleteParamsData

        class DownloadParamsData : public Core::JSON::Container {
        public:
            class OptionsData : public Core::JSON::Container {
            public:
                OptionsData()
                    : Core::JSON::Container()
                {
                    _Init();
                }

                OptionsData(const Exchange::IDownloadManager::Options& _other)
                    : Core::JSON::Container()
                {
                    Priority = _other.priority;
                    Retries = _other.retries;
                    RateLimit = _other.rateLimit;
                    _Init();
                }

                OptionsData& operator=(const Exchange::IDownloadManager::Options& _rhs)
                {
                    Priority = _rhs.priority;
                    Retries = _rhs.retries;
                    RateLimit = _rhs.rateLimit;
                    return (*this);
                }

                operator Exchange::IDownloadManager::Options() const
                {
                    Exchange::IDownloadManager::Options _value{};
                    _value.priority = Priority;
                    _value.retries = Retries;
                    _value.rateLimit = RateLimit;
                    return (_value);
                }

                bool IsValid() const
                {
                    return (true);
                }

            private:
                void _Init()
                {
                    Add(_T("priority"), &Priority);
                    Add(_T("retries"), &Retries);
                    Add(_T("rateLimit"), &RateLimit);
                }

            public:
                Core::JSON::Boolean Priority; // Adds the download request to either a priority queue (true) or regular queue (false)
                Core::JSON::DecUInt32 Retries; // Retries Number of retry attempts allowed for failed downloads (the default retries is 2)
                Core::JSON::DecUInt32 RateLimit; // RateLimit Maximum bandwidth allowed for the download (bytes per second)
            }; // class OptionsData

            DownloadParamsData()
                : Core::JSON::Container()
            {
                Add(_T("url"), &Url);
                Add(_T("options"), &Options);
            }

            bool IsValid() const
            {
                return (true);
            }

            DownloadParamsData(const DownloadParamsData&) = delete;
            DownloadParamsData& operator=(const DownloadParamsData&) = delete;

        public:
            Core::JSON::String Url; // URL from which the file is to be downloaded
            DownloadParamsData::OptionsData Options; // Options controlling download behavior
        }; // class DownloadParamsData

        class GetStorageDetailsResultData : public Core::JSON::Container {
        public:
            GetStorageDetailsResultData()
                : Core::JSON::Container()
            {
                Add(_T("quotaKb"), &QuotaKb);
                Add(_T("usedKb"), &UsedKb);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetStorageDetailsResultData(const GetStorageDetailsResultData&) = delete;
            GetStorageDetailsResultData& operator=(const GetStorageDetailsResultData&) = delete;

        public:
            Core::JSON::DecUInt32 QuotaKb; // Output parameter for total available quota in KB
            Core::JSON::DecUInt32 UsedKb; // Output parameter for currently used storage in KB
        }; // class GetStorageDetailsResultData

        class OnAppDownloadStatusParamsData : public Core::JSON::Container {
        public:
            OnAppDownloadStatusParamsData()
                : Core::JSON::Container()
            {
                Add(_T("downloadStatus"), &DownloadStatus);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnAppDownloadStatusParamsData(const OnAppDownloadStatusParamsData&) = delete;
            OnAppDownloadStatusParamsData& operator=(const OnAppDownloadStatusParamsData&) = delete;

        public:
            Core::JSON::String DownloadStatus; // : [JSON string] Download status of a queued download request, includes downloadId, fileLocator,
                    //  failReason (enum)
        }; // class OnAppDownloadStatusParamsData

        class RateLimitParamsData : public Core::JSON::Container {
        public:
            RateLimitParamsData()
                : Core::JSON::Container()
            {
                Add(_T("downloadId"), &DownloadId);
                Add(_T("limit"), &Limit);
            }

            bool IsValid() const
            {
                return (true);
            }

            RateLimitParamsData(const RateLimitParamsData&) = delete;
            RateLimitParamsData& operator=(const RateLimitParamsData&) = delete;

        public:
            Core::JSON::String DownloadId; // Unique identifier of the download
            Core::JSON::DecUInt32 Limit; // Maximum bandwidth in bytes per second (0 = unlimited)
        }; // class RateLimitParamsData

    } // namespace DownloadManager

} // namespace JsonData

}

