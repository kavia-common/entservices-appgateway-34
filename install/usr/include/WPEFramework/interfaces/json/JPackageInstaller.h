// Generated automatically from 'IAppPackageManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_PackageInstaller.h"
#include <interfaces/IAppPackageManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JPackageInstaller {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IPackageInstaller* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JPackageInstaller"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'install' - Install
            _module_.Register<JsonData::PackageInstaller::InstallParamsData, Core::JSON::EnumType<Exchange::IPackageInstaller::FailReason>>(_T("install"), 
                [_impl_](const JsonData::PackageInstaller::InstallParamsData& params,
                         Core::JSON::EnumType<Exchange::IPackageInstaller::FailReason>& failReason) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _packageId{params.PackageId};
                    const string _version{params.Version};
                    std::list<Exchange::IPackageInstaller::KeyValue> _elements;
                    auto _Iterator = params.AdditionalMetadata.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<IPackageInstaller::KeyValue,
                             ID_PACKAGE_KEY_VALUE_ITERATOR>* const _additionalMetadata{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<IPackageInstaller::KeyValue,
                             ID_PACKAGE_KEY_VALUE_ITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<IPackageInstaller::KeyValue, ID_PACKAGE_KEY_VALUE_ITERATOR>>(_elements)};
                    const string _fileLocator{params.FileLocator};
                    Exchange::IPackageInstaller::FailReason _failReason{};

                    ASSERT(_additionalMetadata != nullptr); 

                    if ((_additionalMetadata != nullptr)) {
                        _errorCode = _impl_->Install(_packageId, _version, _additionalMetadata, _fileLocator, _failReason);
                        _additionalMetadata->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    if (_errorCode == Core::ERROR_NONE) {
                        failReason = _failReason;
                    }

                    return (_errorCode);
                });

            // Method: 'uninstall' - Uninstall
            _module_.Register<JsonData::PackageInstaller::UninstallParamsData, Core::JSON::String>(_T("uninstall"), 
                [_impl_](const JsonData::PackageInstaller::UninstallParamsData& params, Core::JSON::String& errorReason) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _packageId{params.PackageId};
                    string _errorReason{};

                    _errorCode = _impl_->Uninstall(_packageId, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        errorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'listPackages' - ListPackages
            _module_.Register<void, Core::JSON::ArrayType<JsonData::PackageInstaller::PackageData>>(_T("listPackages"), 
                [_impl_](Core::JSON::ArrayType<JsonData::PackageInstaller::PackageData>& packages) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<IPackageInstaller::Package, ID_PACKAGE_ITERATOR>* _packages{};

                    _errorCode = _impl_->ListPackages(_packages);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_packages != nullptr) {
                            Exchange::IPackageInstaller::Package _resultItem_{};
                            while (_packages->Next(_resultItem_) == true) { packages.Add() = _resultItem_; }
                            _packages->Release();
                        }
                    }

                    return (_errorCode);
                });

            // Method: 'config' - Config
            _module_.Register<JsonData::PackageInstaller::ConfigParamsInfo, JsonData::PackageInstaller::RuntimeConfigInfo>(_T("config"), 
                [_impl_](const JsonData::PackageInstaller::ConfigParamsInfo& params,
                         JsonData::PackageInstaller::RuntimeConfigInfo& configMetadata) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _packageId{params.PackageId};
                    const string _version{params.Version};
                    Exchange::RuntimeConfig _configMetadata{};

                    _errorCode = _impl_->Config(_packageId, _version, _configMetadata);

                    if (_errorCode == Core::ERROR_NONE) {
                        configMetadata = _configMetadata;
                    }

                    return (_errorCode);
                });

            // Method: 'packageState' - PackageState
            _module_.Register<JsonData::PackageInstaller::ConfigParamsInfo, Core::JSON::EnumType<Exchange::IPackageInstaller::InstallState>>(_T("packageState"),
                     
                [_impl_](const JsonData::PackageInstaller::ConfigParamsInfo& params,
                         Core::JSON::EnumType<Exchange::IPackageInstaller::InstallState>& state) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _packageId{params.PackageId};
                    const string _version{params.Version};
                    Exchange::IPackageInstaller::InstallState _state{};

                    _errorCode = _impl_->PackageState(_packageId, _version, _state);

                    if (_errorCode == Core::ERROR_NONE) {
                        state = _state;
                    }

                    return (_errorCode);
                });

            // Method: 'getConfigForPackage' - getConfigForPackage
            _module_.Register<JsonData::PackageInstaller::GetConfigForPackageParamsData,
                     JsonData::PackageInstaller::GetConfigForPackageResultData>(_T("getConfigForPackage"), 
                [_impl_](const JsonData::PackageInstaller::GetConfigForPackageParamsData& params,
                         JsonData::PackageInstaller::GetConfigForPackageResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _fileLocator{params.FileLocator};
                    string _id{};
                    string _version{};
                    Exchange::RuntimeConfig _config{};

                    _errorCode = _impl_->GetConfigForPackage(_fileLocator, _id, _version, _config);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Id = _id;
                        result.Version = _version;
                        result.Config = _config;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("install"));
            _module_.Unregister(_T("uninstall"));
            _module_.Unregister(_T("listPackages"));
            _module_.Unregister(_T("config"));
            _module_.Unregister(_T("packageState"));
            _module_.Unregister(_T("getConfigForPackage"));
        }

        namespace Event {

            // Event: 'onAppInstallationStatus' - Signal changes on the status
            static void OnAppInstallationStatus(const JSONRPC& _module_, const JsonData::PackageInstaller::OnAppInstallationStatusParamsData& params)
            {
                _module_.Notify(_T("onAppInstallationStatus"), params);
            }

            // Event: 'onAppInstallationStatus' - Signal changes on the status
            static void OnAppInstallationStatus(const JSONRPC& _module_, const Core::JSON::String& jsonresponse)
            {
                JsonData::PackageInstaller::OnAppInstallationStatusParamsData _params_;
                _params_.Jsonresponse = jsonresponse;

                OnAppInstallationStatus(_module_, _params_);
            }

            // Event: 'onAppInstallationStatus' - Signal changes on the status
            static void OnAppInstallationStatus(const JSONRPC& _module_, const string& jsonresponse)
            {
                JsonData::PackageInstaller::OnAppInstallationStatusParamsData _params_;
                _params_.Jsonresponse = jsonresponse;

                OnAppInstallationStatus(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JPackageInstaller

} // namespace Exchange

} // namespace WPEFramework

