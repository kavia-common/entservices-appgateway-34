// Generated automatically from 'IDeviceDiagnostics.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_DeviceDiagnostics.h"
#include <interfaces/IDeviceDiagnostics.h>

namespace WPEFramework {

namespace Exchange {

    namespace JDeviceDiagnostics {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IDeviceDiagnostics* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JDeviceDiagnostics"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'getConfiguration' - Gets the values associated with the corresponding property names
            _module_.Register<JsonData::DeviceDiagnostics::GetConfigurationParamsData,
                     JsonData::DeviceDiagnostics::GetConfigurationResultData>(_T("getConfiguration"), 
                [_impl_](const JsonData::DeviceDiagnostics::GetConfigurationParamsData& params,
                         JsonData::DeviceDiagnostics::GetConfigurationResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    std::list<string> _elements;
                    auto _Iterator = params.Names.Elements();
                    while (_Iterator.Next() == true) { _elements.push_back(_Iterator.Current()); }

                    ::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>* const _names{Core::Service<::WPEFramework::RPC::IteratorType<::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>>>::Create<::WPEFramework::RPC::IIteratorType<string,
                             RPC::ID_STRINGITERATOR>>(_elements)};
                    ::WPEFramework::RPC::IIteratorType<IDeviceDiagnostics::ParamList, ID_DEVICE_DIAGNOSTICS_PARAM_LIST_ITERATOR>* _paramList{};
                    bool _success{};

                    ASSERT(_names != nullptr); 

                    if ((_names != nullptr)) {
                        _errorCode = _impl_->GetConfiguration(_names, _paramList, _success);
                        _names->Release();
                    } else {
                        _errorCode = Core::ERROR_GENERAL;
                    }

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_paramList != nullptr) {
                            Exchange::IDeviceDiagnostics::ParamList _paramListItem_{};
                            while (_paramList->Next(_paramListItem_) == true) { result.ParamList.Add() = _paramListItem_; }
                            _paramList->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getMilestones' - Returns the list of milestones
            _module_.Register<void, JsonData::DeviceDiagnostics::GetMilestonesResultData>(_T("getMilestones"), 
                [_impl_](JsonData::DeviceDiagnostics::GetMilestonesResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    ::WPEFramework::RPC::IIteratorType<string, RPC::ID_STRINGITERATOR>* _milestones{};
                    bool _success{};

                    _errorCode = _impl_->GetMilestones(_milestones, _success);

                    if (_errorCode == Core::ERROR_NONE) {

                        if (_milestones != nullptr) {
                            string _milestonesItem_{};
                            while (_milestones->Next(_milestonesItem_) == true) { result.Milestones.Add() = _milestonesItem_; }
                            _milestones->Release();
                        }
                        result.Success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'logMilestone' - Log marker string to rdk milestones log
            _module_.Register<JsonData::DeviceDiagnostics::LogMilestoneParamsData, Core::JSON::Boolean>(_T("logMilestone"), 
                [_impl_](const JsonData::DeviceDiagnostics::LogMilestoneParamsData& params, Core::JSON::Boolean& success) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _marker{params.Marker};
                    bool _success{};

                    _errorCode = _impl_->LogMilestone(_marker, _success);

                    if (_errorCode == Core::ERROR_NONE) {
                        success = _success;
                    }

                    return (_errorCode);
                });

            // Method: 'getAVDecoderStatus' - Gets the most active status of audio/video decoder/pipeline
            _module_.Register<void, JsonData::DeviceDiagnostics::AvDecoderStatusResultData>(_T("getAVDecoderStatus"), 
                [_impl_](JsonData::DeviceDiagnostics::AvDecoderStatusResultData& AVDecoderStatus) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    Exchange::IDeviceDiagnostics::AvDecoderStatusResult _aVDecoderStatus{};

                    _errorCode = _impl_->GetAVDecoderStatus(_aVDecoderStatus);

                    if (_errorCode == Core::ERROR_NONE) {
                        AVDecoderStatus = _aVDecoderStatus;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("getConfiguration"));
            _module_.Unregister(_T("getMilestones"));
            _module_.Unregister(_T("logMilestone"));
            _module_.Unregister(_T("getAVDecoderStatus"));
        }

        namespace Event {

            // Event: 'onAVDecoderStatusChanged' - Triggered when the most active status of audio/video decoder/pipeline changes
            static void OnAVDecoderStatusChanged(const JSONRPC& _module_, const JsonData::DeviceDiagnostics::OnAVDecoderStatusChangedParamsData& params)
            {
                _module_.Notify(_T("onAVDecoderStatusChanged"), params);
            }

            // Event: 'onAVDecoderStatusChanged' - Triggered when the most active status of audio/video decoder/pipeline changes
            static void OnAVDecoderStatusChanged(const JSONRPC& _module_, const Core::JSON::String& avDecoderStatusChange)
            {
                JsonData::DeviceDiagnostics::OnAVDecoderStatusChangedParamsData _params_;
                _params_.AvDecoderStatusChange = avDecoderStatusChange;

                OnAVDecoderStatusChanged(_module_, _params_);
            }

            // Event: 'onAVDecoderStatusChanged' - Triggered when the most active status of audio/video decoder/pipeline changes
            static void OnAVDecoderStatusChanged(const JSONRPC& _module_, const string& avDecoderStatusChange)
            {
                JsonData::DeviceDiagnostics::OnAVDecoderStatusChangedParamsData _params_;
                _params_.AvDecoderStatusChange = avDecoderStatusChange;

                OnAVDecoderStatusChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JDeviceDiagnostics

} // namespace Exchange

} // namespace WPEFramework

