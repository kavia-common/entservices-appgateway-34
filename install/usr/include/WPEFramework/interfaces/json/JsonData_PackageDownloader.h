// C++ classes for PackageDownloader API JSON-RPC API.
// Generated automatically from 'IAppPackageManager.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IAppPackageManager.h>

namespace WPEFramework {

namespace JsonData {

    namespace PackageDownloader {

        // Common classes
        //

        class DownloadIdInfo : public Core::JSON::Container {
        public:
            DownloadIdInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            DownloadIdInfo(const Exchange::IPackageDownloader::DownloadId& _other)
                : Core::JSON::Container()
            {
                DownloadId = _other.downloadId;
                _Init();
            }

            DownloadIdInfo& operator=(const Exchange::IPackageDownloader::DownloadId& _rhs)
            {
                DownloadId = _rhs.downloadId;
                return (*this);
            }

            operator Exchange::IPackageDownloader::DownloadId() const
            {
                Exchange::IPackageDownloader::DownloadId _value{};
                _value.downloadId = DownloadId;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("downloadId"), &DownloadId);
            }

        public:
            Core::JSON::String DownloadId; // Download
        }; // class DownloadIdInfo

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
            Core::JSON::String FileLocator; // FileLocator
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

                OptionsData(const Exchange::IPackageDownloader::Options& _other)
                    : Core::JSON::Container()
                {
                    Priority = _other.priority;
                    Retries = _other.retries;
                    RateLimit = _other.rateLimit;
                    _Init();
                }

                OptionsData& operator=(const Exchange::IPackageDownloader::Options& _rhs)
                {
                    Priority = _rhs.priority;
                    Retries = _rhs.retries;
                    RateLimit = _rhs.rateLimit;
                    return (*this);
                }

                operator Exchange::IPackageDownloader::Options() const
                {
                    Exchange::IPackageDownloader::Options _value{};
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
                Core::JSON::Boolean Priority; // Priority
                Core::JSON::DecUInt32 Retries; // Retries
                Core::JSON::DecUInt64 RateLimit; // RateLimit
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
            Core::JSON::String Url; // Download url
            DownloadParamsData::OptionsData Options; // Download options
        }; // class DownloadParamsData

        class GetStorageInformationResultData : public Core::JSON::Container {
        public:
            GetStorageInformationResultData()
                : Core::JSON::Container()
            {
                Add(_T("quotaKb"), &QuotaKb);
                Add(_T("usedKb"), &UsedKb);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetStorageInformationResultData(const GetStorageInformationResultData&) = delete;
            GetStorageInformationResultData& operator=(const GetStorageInformationResultData&) = delete;

        public:
            Core::JSON::DecUInt32 QuotaKb; // Storage quota in kilobytes
            Core::JSON::DecUInt32 UsedKb; // Used storage in kilobytes
        }; // class GetStorageInformationResultData

        class ProgressInfoData : public Core::JSON::Container {
        public:
            ProgressInfoData()
                : Core::JSON::Container()
            {
                _Init();
            }

            ProgressInfoData(const Exchange::IPackageDownloader::ProgressInfo& _other)
                : Core::JSON::Container()
            {
                Progress = _other.progress;
                _Init();
            }

            ProgressInfoData& operator=(const Exchange::IPackageDownloader::ProgressInfo& _rhs)
            {
                Progress = _rhs.progress;
                return (*this);
            }

            operator Exchange::IPackageDownloader::ProgressInfo() const
            {
                Exchange::IPackageDownloader::ProgressInfo _value{};
                _value.progress = Progress;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("progress"), &Progress);
            }

        public:
            Core::JSON::DecUInt8 Progress; // Progress
        }; // class ProgressInfoData

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
            Core::JSON::String DownloadId; // Download id
            Core::JSON::DecUInt64 Limit; // Limit
        }; // class RateLimitParamsData

    } // namespace PackageDownloader

} // namespace JsonData

}

