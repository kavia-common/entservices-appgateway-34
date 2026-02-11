// Generated automatically from 'IAppPackageManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_PackageHandler.h"
#include <interfaces/IAppPackageManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JPackageHandler {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IPackageHandler* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JPackageHandler"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'lock' - Lock
            _module_.Register<JsonData::PackageHandler::LockParamsData, JsonData::PackageHandler::LockResultData>(_T("lock"), 
                [_impl_](const JsonData::PackageHandler::LockParamsData& params, JsonData::PackageHandler::LockResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _packageId{params.PackageId};
                    const string _version{params.Version};
                    const Exchange::IPackageHandler::LockReason _lockReason{params.LockReason};
                    uint32_t _lockId{};
                    string _unpackedPath{};
                    Exchange::RuntimeConfig _configMetadata{};
                    ::WPEFramework::RPC::IIteratorType<IPackageHandler::AdditionalLock, ID_PACKAGE_LOCK_ITERATOR>* _appMetadata{};

                    _errorCode = _impl_->Lock(_packageId, _version, _lockReason, _lockId, _unpackedPath, _configMetadata, _appMetadata);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.LockId = _lockId;
                        result.UnpackedPath = _unpackedPath;
                        result.ConfigMetadata = _configMetadata;

                        if (_appMetadata != nullptr) {
                            Exchange::IPackageHandler::AdditionalLock _appMetadataItem_{};
                            while (_appMetadata->Next(_appMetadataItem_) == true) { result.AppMetadata.Add() = _appMetadataItem_; }
                            _appMetadata->Release();
                        }
                    }

                    return (_errorCode);
                });

            // Method: 'unlock' - Unlock
            _module_.Register<JsonData::PackageHandler::AdditionalLockInfo, void>(_T("unlock"), 
                [_impl_](const JsonData::PackageHandler::AdditionalLockInfo& params) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _packageId{params.PackageId};
                    const string _version{params.Version};

                    _errorCode = _impl_->Unlock(_packageId, _version);

                    return (_errorCode);
                });

            // Method: 'getLockedInfo' - GetLockedInfo
            _module_.Register<JsonData::PackageHandler::AdditionalLockInfo, JsonData::PackageHandler::GetLockedInfoResultData>(_T("getLockedInfo"), 
                [_impl_](const JsonData::PackageHandler::AdditionalLockInfo& params, JsonData::PackageHandler::GetLockedInfoResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _packageId{params.PackageId};
                    const string _version{params.Version};
                    string _unpackedPath{};
                    Exchange::RuntimeConfig _configMetadata{};
                    string _gatewayMetadataPath{};
                    bool _locked{};

                    _errorCode = _impl_->GetLockedInfo(_packageId, _version, _unpackedPath, _configMetadata, _gatewayMetadataPath, _locked);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.UnpackedPath = _unpackedPath;
                        result.ConfigMetadata = _configMetadata;
                        result.GatewayMetadataPath = _gatewayMetadataPath;
                        result.Locked = _locked;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("lock"));
            _module_.Unregister(_T("unlock"));
            _module_.Unregister(_T("getLockedInfo"));
        }

        POP_WARNING()

    } // namespace JPackageHandler

} // namespace Exchange

} // namespace WPEFramework

