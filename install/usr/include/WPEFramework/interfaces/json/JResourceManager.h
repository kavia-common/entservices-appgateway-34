// Generated automatically from 'IResourceManager.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_ResourceManager.h"
#include <interfaces/IResourceManager.h>

namespace WPEFramework {

namespace Exchange {

    namespace JResourceManager {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IResourceManager* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JResourceManager"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'setAVBlocked' - Sets AV blocking status for an application
            _module_.Register<JsonData::ResourceManager::SetAVBlockedParamsData, JsonData::ResourceManager::SetAVBlockedResultInfo>(_T("setAVBlocked"), 
                [_impl_](const JsonData::ResourceManager::SetAVBlockedParamsData& params,
                         JsonData::ResourceManager::SetAVBlockedResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    const bool _blocked{params.Blocked};
                    Exchange::IResourceManager::SetAVBlockedResult _result{};

                    _errorCode = _impl_->SetAVBlocked(_appId, _blocked, _result);

                    if (_errorCode == Core::ERROR_NONE) {
                        result = _result;
                    }

                    return (_errorCode);
                });

            // Method: 'getBlockedAVApplications' - Gets list of applications with blocked AV access
            _module_.Register<void, JsonData::ResourceManager::GetBlockedAVApplicationsResultData>(_T("getBlockedAVApplications"), 
                [_impl_](JsonData::ResourceManager::GetBlockedAVApplicationsResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _clients{};
                    bool _success{};

                    _errorCode = _impl_->GetBlockedAVApplications(_clients, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_clients != nullptr) {
                            string _clientsItem_{};
                            while (_clients->Next(_clientsItem_) == true) { result.Clients.Add() = _clientsItem_; }
                            _clients->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'reserveTTSResource' - Reserves TTS resource for a single application
            _module_.Register<JsonData::ResourceManager::ReserveTTSResourceParamsData,
                     JsonData::ResourceManager::SetAVBlockedResultInfo>(_T("reserveTTSResource"), 
                [_impl_](const JsonData::ResourceManager::ReserveTTSResourceParamsData& params,
                         JsonData::ResourceManager::SetAVBlockedResultInfo& ttsResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _appId{params.AppId};
                    Exchange::IResourceManager::TTSResult _ttsResult{};

                    _errorCode = _impl_->ReserveTTSResource(_appId, _ttsResult);

                    if (_errorCode == Core::ERROR_NONE) {
                        ttsResult = _ttsResult;
                    }

                    return (_errorCode);
                });

            // Method: 'reserveTTSResourceForApps' - Reserves TTS resource for multiple applications
            _module_.Register<JsonData::ResourceManager::ReserveTTSResourceForAppsParamsData,
                     JsonData::ResourceManager::SetAVBlockedResultInfo>(_T("reserveTTSResourceForApps"), 
                [_impl_](const JsonData::ResourceManager::ReserveTTSResourceForAppsParamsData& params,
                         JsonData::ResourceManager::SetAVBlockedResultInfo& ttsResult) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    std::list<string> _elements;
                    auto _Iterator = params.Appids.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>* const _appids{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>>(_elements)};
                    Exchange::IResourceManager::TTSResult _ttsResult{};

                    ASSERT(_appids != nullptr); 

                    if ((_appids != nullptr)) {
                        _errorCode = _impl_->ReserveTTSResourceForApps(_appids, _ttsResult);
                        _appids->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    if (_errorCode == Core::ERROR_NONE) {
                        ttsResult = _ttsResult;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("setAVBlocked"));
            _module_.Unregister(_T("getBlockedAVApplications"));
            _module_.Unregister(_T("reserveTTSResource"));
            _module_.Unregister(_T("reserveTTSResourceForApps"));
        }

        POP_WARNING()

    } // namespace JResourceManager

} // namespace Exchange

} // namespace WPEFramework

