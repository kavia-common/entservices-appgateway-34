// Generated automatically from 'IOCIContainer.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_OCIContainer.h"
#include <interfaces/IOCIContainer.h>

namespace WPEFramework {

namespace Exchange {

    namespace JOCIContainer {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, IOCIContainer* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JOCIContainer"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'listContainers' - Provide list of containers
            _module_.Register<void, JsonData::OCIContainer::ListContainersResultData>(_T("listContainers"), 
                [_impl_](JsonData::OCIContainer::ListContainersResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    string _containers{};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->ListContainers(_containers, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Containers = _containers;
                        result.Containers.SetQuoted(false);
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'getContainerInfo' - Get the information about container
            _module_.Register<JsonData::OCIContainer::GetContainerInfoParamsInfo, JsonData::OCIContainer::GetContainerInfoResultData>(_T("getContainerInfo"), 
                [_impl_](const JsonData::OCIContainer::GetContainerInfoParamsInfo& params,
                         JsonData::OCIContainer::GetContainerInfoResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    string _info{};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->GetContainerInfo(_containerId, _info, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Info = _info;
                        result.Info.SetQuoted(false);
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'getContainerState' - Get the state of container
            _module_.Register<JsonData::OCIContainer::GetContainerInfoParamsInfo, JsonData::OCIContainer::GetContainerStateResultData>(_T("getContainerState"), 
                [_impl_](const JsonData::OCIContainer::GetContainerInfoParamsInfo& params,
                         JsonData::OCIContainer::GetContainerStateResultData& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    Exchange::IOCIContainer::ContainerState _state{};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->GetContainerState(_containerId, _state, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.State = _state;
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'startContainer' - Start the container from bundle
            _module_.Register<JsonData::OCIContainer::StartContainerParamsData, JsonData::OCIContainer::StartContainerResultInfo>(_T("startContainer"), 
                [_impl_](const JsonData::OCIContainer::StartContainerParamsData& params, JsonData::OCIContainer::StartContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const string _bundlePath{params.BundlePath};
                    const string _command{params.Command};
                    const string _westerosSocket{params.WesterosSocket};
                    int32_t _descriptor{};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->StartContainer(_containerId, _bundlePath, _command, _westerosSocket, _descriptor, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Descriptor = _descriptor;
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'startContainerFromDobbySpec' - Start the container from dobby specification
            _module_.Register<JsonData::OCIContainer::StartContainerFromDobbySpecParamsData,
                     JsonData::OCIContainer::StartContainerResultInfo>(_T("startContainerFromDobbySpec"), 
                [_impl_](const JsonData::OCIContainer::StartContainerFromDobbySpecParamsData& params,
                         JsonData::OCIContainer::StartContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const string _dobbySpec{params.DobbySpec};
                    const string _command{params.Command};
                    const string _westerosSocket{params.WesterosSocket};
                    int32_t _descriptor{};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->StartContainerFromDobbySpec(_containerId, _dobbySpec, _command, _westerosSocket, _descriptor, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Descriptor = _descriptor;
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'stopContainer' - Stop the container
            _module_.Register<JsonData::OCIContainer::StopContainerParamsData, JsonData::OCIContainer::StopContainerResultInfo>(_T("stopContainer"), 
                [_impl_](const JsonData::OCIContainer::StopContainerParamsData& params, JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const bool _force{params.Force};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->StopContainer(_containerId, _force, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'pauseContainer' - Pause the container
            _module_.Register<JsonData::OCIContainer::GetContainerInfoParamsInfo, JsonData::OCIContainer::StopContainerResultInfo>(_T("pauseContainer"), 
                [_impl_](const JsonData::OCIContainer::GetContainerInfoParamsInfo& params,
                         JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->PauseContainer(_containerId, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'resumeContainer' - Resume the container
            _module_.Register<JsonData::OCIContainer::GetContainerInfoParamsInfo, JsonData::OCIContainer::StopContainerResultInfo>(_T("resumeContainer"), 
                [_impl_](const JsonData::OCIContainer::GetContainerInfoParamsInfo& params,
                         JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->ResumeContainer(_containerId, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'hibernateContainer' - Hibernate the container
            _module_.Register<JsonData::OCIContainer::HibernateContainerParamsData, JsonData::OCIContainer::StopContainerResultInfo>(_T("hibernateContainer"), 
                [_impl_](const JsonData::OCIContainer::HibernateContainerParamsData& params,
                         JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const string _options{params.Options};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->HibernateContainer(_containerId, _options, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'wakeupContainer' - Wakeup the container
            _module_.Register<JsonData::OCIContainer::GetContainerInfoParamsInfo, JsonData::OCIContainer::StopContainerResultInfo>(_T("wakeupContainer"), 
                [_impl_](const JsonData::OCIContainer::GetContainerInfoParamsInfo& params,
                         JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->WakeupContainer(_containerId, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'executeCommand' - Execute the command in container
            _module_.Register<JsonData::OCIContainer::ExecuteCommandParamsData, JsonData::OCIContainer::StopContainerResultInfo>(_T("executeCommand"), 
                [_impl_](const JsonData::OCIContainer::ExecuteCommandParamsData& params, JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const string _options{params.Options};
                    const string _command{params.Command};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->ExecuteCommand(_containerId, _options, _command, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'annotate' - Update container properties
            _module_.Register<JsonData::OCIContainer::AnnotateParamsData, JsonData::OCIContainer::StopContainerResultInfo>(_T("annotate"), 
                [_impl_](const JsonData::OCIContainer::AnnotateParamsData& params, JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const string _key{params.Key};
                    const string _value{params.Value};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->Annotate(_containerId, _key, _value, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'removeAnnotation' - Remove container property
            _module_.Register<JsonData::OCIContainer::RemoveAnnotationParamsData, JsonData::OCIContainer::StopContainerResultInfo>(_T("removeAnnotation"), 
                [_impl_](const JsonData::OCIContainer::RemoveAnnotationParamsData& params,
                         JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const string _key{params.Key};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->RemoveAnnotation(_containerId, _key, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'mount' - Mount a path in container
            _module_.Register<JsonData::OCIContainer::MountParamsData, JsonData::OCIContainer::StopContainerResultInfo>(_T("mount"), 
                [_impl_](const JsonData::OCIContainer::MountParamsData& params, JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const string _source{params.Source};
                    const string _target{params.Target};
                    const string _type{params.Type};
                    const string _options{params.Options};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->Mount(_containerId, _source, _target, _type, _options, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

            // Method: 'unmount' - Unmount a path in container
            _module_.Register<JsonData::OCIContainer::UnmountParamsData, JsonData::OCIContainer::StopContainerResultInfo>(_T("unmount"), 
                [_impl_](const JsonData::OCIContainer::UnmountParamsData& params, JsonData::OCIContainer::StopContainerResultInfo& result) -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    const string _containerId{params.ContainerId};
                    const string _target{params.Target};
                    bool _success{};
                    string _errorReason{};

                    _errorCode = _impl_->Unmount(_containerId, _target, _success, _errorReason);

                    if (_errorCode == Core::ERROR_NONE) {
                        result.Success = _success;
                        result.ErrorReason = _errorReason;
                    }

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("listContainers"));
            _module_.Unregister(_T("getContainerInfo"));
            _module_.Unregister(_T("getContainerState"));
            _module_.Unregister(_T("startContainer"));
            _module_.Unregister(_T("startContainerFromDobbySpec"));
            _module_.Unregister(_T("stopContainer"));
            _module_.Unregister(_T("pauseContainer"));
            _module_.Unregister(_T("resumeContainer"));
            _module_.Unregister(_T("hibernateContainer"));
            _module_.Unregister(_T("wakeupContainer"));
            _module_.Unregister(_T("executeCommand"));
            _module_.Unregister(_T("annotate"));
            _module_.Unregister(_T("removeAnnotation"));
            _module_.Unregister(_T("mount"));
            _module_.Unregister(_T("unmount"));
        }

        namespace Event {

            // Event: 'onContainerStarted' - Notifies container is started
            static void OnContainerStarted(const JSONRPC& _module_, const JsonData::OCIContainer::OnContainerStartedParamsInfo& params)
            {
                _module_.Notify(_T("onContainerStarted"), params);
            }

            // Event: 'onContainerStarted' - Notifies container is started
            static void OnContainerStarted(const JSONRPC& _module_, const Core::JSON::String& containerId, const Core::JSON::String& name)
            {
                JsonData::OCIContainer::OnContainerStartedParamsInfo _params_;
                _params_.ContainerId = containerId;
                _params_.Name = name;

                OnContainerStarted(_module_, _params_);
            }

            // Event: 'onContainerStarted' - Notifies container is started
            static void OnContainerStarted(const JSONRPC& _module_, const string& containerId, const string& name)
            {
                JsonData::OCIContainer::OnContainerStartedParamsInfo _params_;
                _params_.ContainerId = containerId;
                _params_.Name = name;

                OnContainerStarted(_module_, _params_);
            }

            // Event: 'onContainerStopped' - Notifies container is stopped
            static void OnContainerStopped(const JSONRPC& _module_, const JsonData::OCIContainer::OnContainerStartedParamsInfo& params)
            {
                _module_.Notify(_T("onContainerStopped"), params);
            }

            // Event: 'onContainerStopped' - Notifies container is stopped
            static void OnContainerStopped(const JSONRPC& _module_, const Core::JSON::String& containerId, const Core::JSON::String& name)
            {
                JsonData::OCIContainer::OnContainerStartedParamsInfo _params_;
                _params_.ContainerId = containerId;
                _params_.Name = name;

                OnContainerStopped(_module_, _params_);
            }

            // Event: 'onContainerStopped' - Notifies container is stopped
            static void OnContainerStopped(const JSONRPC& _module_, const string& containerId, const string& name)
            {
                JsonData::OCIContainer::OnContainerStartedParamsInfo _params_;
                _params_.ContainerId = containerId;
                _params_.Name = name;

                OnContainerStopped(_module_, _params_);
            }

            // Event: 'onContainerFailed' - Notifies failure in container execution, only triggered for states start, stop, hibernate, wakeup
            static void OnContainerFailed(const JSONRPC& _module_, const JsonData::OCIContainer::OnContainerFailedParamsData& params)
            {
                _module_.Notify(_T("onContainerFailed"), params);
            }

            // Event: 'onContainerFailed' - Notifies failure in container execution, only triggered for states start, stop, hibernate, wakeup
            static void OnContainerFailed(const JSONRPC& _module_, const Core::JSON::String& containerId, const Core::JSON::String& name,
                     const Core::JSON::DecUInt32& error)
            {
                JsonData::OCIContainer::OnContainerFailedParamsData _params_;
                _params_.ContainerId = containerId;
                _params_.Name = name;
                _params_.Error = error;

                OnContainerFailed(_module_, _params_);
            }

            // Event: 'onContainerFailed' - Notifies failure in container execution, only triggered for states start, stop, hibernate, wakeup
            static void OnContainerFailed(const JSONRPC& _module_, const string& containerId, const string& name, const uint32_t& error)
            {
                JsonData::OCIContainer::OnContainerFailedParamsData _params_;
                _params_.ContainerId = containerId;
                _params_.Name = name;
                _params_.Error = error;

                OnContainerFailed(_module_, _params_);
            }

            // Event: 'onContainerStateChanged' - Notifies state change of container
            static void OnContainerStateChanged(const JSONRPC& _module_, const JsonData::OCIContainer::OnContainerStateChangedParamsData& params)
            {
                _module_.Notify(_T("onContainerStateChanged"), params);
            }

            // Event: 'onContainerStateChanged' - Notifies state change of container
            static void OnContainerStateChanged(const JSONRPC& _module_, const Core::JSON::String& containerId,
                     const Core::JSON::EnumType<Exchange::IOCIContainer::ContainerState>& state)
            {
                JsonData::OCIContainer::OnContainerStateChangedParamsData _params_;
                _params_.ContainerId = containerId;
                _params_.State = state;

                OnContainerStateChanged(_module_, _params_);
            }

            // Event: 'onContainerStateChanged' - Notifies state change of container
            static void OnContainerStateChanged(const JSONRPC& _module_, const string& containerId, const Exchange::IOCIContainer::ContainerState& state)
            {
                JsonData::OCIContainer::OnContainerStateChangedParamsData _params_;
                _params_.ContainerId = containerId;
                _params_.State = state;

                OnContainerStateChanged(_module_, _params_);
            }

        } // namespace Event

        POP_WARNING()

    } // namespace JOCIContainer

} // namespace Exchange

} // namespace WPEFramework

