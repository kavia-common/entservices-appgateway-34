// C++ classes for OCIContainer API JSON-RPC API.
// Generated automatically from 'IOCIContainer.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IOCIContainer.h>

namespace WPEFramework {

namespace JsonData {

    namespace OCIContainer {

        // Common classes
        //

        class GetContainerInfoParamsInfo : public Core::JSON::Container {
        public:
            GetContainerInfoParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetContainerInfoParamsInfo(const GetContainerInfoParamsInfo&) = delete;
            GetContainerInfoParamsInfo& operator=(const GetContainerInfoParamsInfo&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
        }; // class GetContainerInfoParamsInfo

        class OnContainerStartedParamsInfo : public Core::JSON::Container {
        public:
            OnContainerStartedParamsInfo()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("name"), &Name);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnContainerStartedParamsInfo(const OnContainerStartedParamsInfo&) = delete;
            OnContainerStartedParamsInfo& operator=(const OnContainerStartedParamsInfo&) = delete;

        public:
            Core::JSON::String ContainerId; // Notifies container is started
            Core::JSON::String Name; // Notifies container is started
        }; // class OnContainerStartedParamsInfo

        class StartContainerResultInfo : public Core::JSON::Container {
        public:
            StartContainerResultInfo()
                : Core::JSON::Container()
            {
                Add(_T("descriptor"), &Descriptor);
                Add(_T("success"), &Success);
                Add(_T("errorReason"), &ErrorReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            StartContainerResultInfo(const StartContainerResultInfo&) = delete;
            StartContainerResultInfo& operator=(const StartContainerResultInfo&) = delete;

        public:
            Core::JSON::DecSInt32 Descriptor; // Start the container from bundle
            Core::JSON::Boolean Success; // Start the container from bundle
            Core::JSON::String ErrorReason; // Start the container from bundle
        }; // class StartContainerResultInfo

        class StopContainerResultInfo : public Core::JSON::Container {
        public:
            StopContainerResultInfo()
                : Core::JSON::Container()
            {
                Add(_T("success"), &Success);
                Add(_T("errorReason"), &ErrorReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            StopContainerResultInfo(const StopContainerResultInfo&) = delete;
            StopContainerResultInfo& operator=(const StopContainerResultInfo&) = delete;

        public:
            Core::JSON::Boolean Success; // Stop the container
            Core::JSON::String ErrorReason; // Stop the container
        }; // class StopContainerResultInfo

        // Method params/result classes
        //

        class AnnotateParamsData : public Core::JSON::Container {
        public:
            AnnotateParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("key"), &Key);
                Add(_T("value"), &Value);
            }

            bool IsValid() const
            {
                return (true);
            }

            AnnotateParamsData(const AnnotateParamsData&) = delete;
            AnnotateParamsData& operator=(const AnnotateParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::String Key; // name of property
            Core::JSON::String Value; // property data
        }; // class AnnotateParamsData

        class ExecuteCommandParamsData : public Core::JSON::Container {
        public:
            ExecuteCommandParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("options"), &Options);
                Add(_T("command"), &Command);
            }

            bool IsValid() const
            {
                return (true);
            }

            ExecuteCommandParamsData(const ExecuteCommandParamsData&) = delete;
            ExecuteCommandParamsData& operator=(const ExecuteCommandParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::String Options; // Execute the command in container
            Core::JSON::String Command; // command to run in container
        }; // class ExecuteCommandParamsData

        class GetContainerInfoResultData : public Core::JSON::Container {
        public:
            GetContainerInfoResultData()
                : Core::JSON::Container()
            {
                Add(_T("info"), &Info);
                Info.SetQuoted(false);
                Add(_T("success"), &Success);
                Add(_T("errorReason"), &ErrorReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetContainerInfoResultData(const GetContainerInfoResultData&) = delete;
            GetContainerInfoResultData& operator=(const GetContainerInfoResultData&) = delete;

        public:
            Core::JSON::String Info; // Get the information about container
            Core::JSON::Boolean Success; // Get the information about container
            Core::JSON::String ErrorReason; // Get the information about container
        }; // class GetContainerInfoResultData

        class GetContainerStateResultData : public Core::JSON::Container {
        public:
            GetContainerStateResultData()
                : Core::JSON::Container()
            {
                Add(_T("state"), &State);
                Add(_T("success"), &Success);
                Add(_T("errorReason"), &ErrorReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetContainerStateResultData(const GetContainerStateResultData&) = delete;
            GetContainerStateResultData& operator=(const GetContainerStateResultData&) = delete;

        public:
            Core::JSON::EnumType<Exchange::IOCIContainer::ContainerState> State; // Get the state of container
            Core::JSON::Boolean Success; // Get the state of container
            Core::JSON::String ErrorReason; // Get the state of container
        }; // class GetContainerStateResultData

        class HibernateContainerParamsData : public Core::JSON::Container {
        public:
            HibernateContainerParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("options"), &Options);
            }

            bool IsValid() const
            {
                return (true);
            }

            HibernateContainerParamsData(const HibernateContainerParamsData&) = delete;
            HibernateContainerParamsData& operator=(const HibernateContainerParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::String Options; // Hibernate the container
        }; // class HibernateContainerParamsData

        class ListContainersResultData : public Core::JSON::Container {
        public:
            ListContainersResultData()
                : Core::JSON::Container()
            {
                Add(_T("containers"), &Containers);
                Containers.SetQuoted(false);
                Add(_T("success"), &Success);
                Add(_T("errorReason"), &ErrorReason);
            }

            bool IsValid() const
            {
                return (true);
            }

            ListContainersResultData(const ListContainersResultData&) = delete;
            ListContainersResultData& operator=(const ListContainersResultData&) = delete;

        public:
            Core::JSON::String Containers; // - out/json - string
            Core::JSON::Boolean Success; // Provide list of containers
            Core::JSON::String ErrorReason; // Provide list of containers
        }; // class ListContainersResultData

        class MountParamsData : public Core::JSON::Container {
        public:
            MountParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("source"), &Source);
                Add(_T("target"), &Target);
                Add(_T("type"), &Type);
                Add(_T("options"), &Options);
            }

            bool IsValid() const
            {
                return (true);
            }

            MountParamsData(const MountParamsData&) = delete;
            MountParamsData& operator=(const MountParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::String Source; // path source to mount
            Core::JSON::String Target; // mount target inside container
            Core::JSON::String Type; // type of mounting
            Core::JSON::String Options; // options for mounting
        }; // class MountParamsData

        class OnContainerFailedParamsData : public Core::JSON::Container {
        public:
            OnContainerFailedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("name"), &Name);
                Add(_T("error"), &Error);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnContainerFailedParamsData(const OnContainerFailedParamsData&) = delete;
            OnContainerFailedParamsData& operator=(const OnContainerFailedParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Notifies failure in container execution, only triggered for states start, stop, hibernate, wakeup.
            Core::JSON::String Name; // Notifies failure in container execution, only triggered for states start, stop, hibernate, wakeup.
            Core::JSON::DecUInt32 Error; // Notifies failure in container execution, only triggered for states start, stop, hibernate, wakeup.
        }; // class OnContainerFailedParamsData

        class OnContainerStateChangedParamsData : public Core::JSON::Container {
        public:
            OnContainerStateChangedParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("state"), &State);
            }

            bool IsValid() const
            {
                return (true);
            }

            OnContainerStateChangedParamsData(const OnContainerStateChangedParamsData&) = delete;
            OnContainerStateChangedParamsData& operator=(const OnContainerStateChangedParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Notifies state change of container
            Core::JSON::EnumType<Exchange::IOCIContainer::ContainerState> State; // Notifies state change of container
        }; // class OnContainerStateChangedParamsData

        class RemoveAnnotationParamsData : public Core::JSON::Container {
        public:
            RemoveAnnotationParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("key"), &Key);
            }

            bool IsValid() const
            {
                return (true);
            }

            RemoveAnnotationParamsData(const RemoveAnnotationParamsData&) = delete;
            RemoveAnnotationParamsData& operator=(const RemoveAnnotationParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::String Key; // name of property
        }; // class RemoveAnnotationParamsData

        class StartContainerParamsData : public Core::JSON::Container {
        public:
            StartContainerParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("bundlePath"), &BundlePath);
                Add(_T("command"), &Command);
                Add(_T("westerosSocket"), &WesterosSocket);
            }

            bool IsValid() const
            {
                return (true);
            }

            StartContainerParamsData(const StartContainerParamsData&) = delete;
            StartContainerParamsData& operator=(const StartContainerParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::String BundlePath; // path of application bundle
            Core::JSON::String Command; // Start the container from bundle
            Core::JSON::String WesterosSocket; // Start the container from bundle
        }; // class StartContainerParamsData

        class StartContainerFromDobbySpecParamsData : public Core::JSON::Container {
        public:
            StartContainerFromDobbySpecParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("dobbySpec"), &DobbySpec);
                Add(_T("command"), &Command);
                Add(_T("westerosSocket"), &WesterosSocket);
            }

            bool IsValid() const
            {
                return (true);
            }

            StartContainerFromDobbySpecParamsData(const StartContainerFromDobbySpecParamsData&) = delete;
            StartContainerFromDobbySpecParamsData& operator=(const StartContainerFromDobbySpecParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::String DobbySpec; // dobby specification as json string
            Core::JSON::String Command; // Start the container from dobby specification
            Core::JSON::String WesterosSocket; // Start the container from dobby specification
        }; // class StartContainerFromDobbySpecParamsData

        class StopContainerParamsData : public Core::JSON::Container {
        public:
            StopContainerParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("force"), &Force);
            }

            bool IsValid() const
            {
                return (true);
            }

            StopContainerParamsData(const StopContainerParamsData&) = delete;
            StopContainerParamsData& operator=(const StopContainerParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::Boolean Force; // Stop the container
        }; // class StopContainerParamsData

        class UnmountParamsData : public Core::JSON::Container {
        public:
            UnmountParamsData()
                : Core::JSON::Container()
            {
                Add(_T("containerId"), &ContainerId);
                Add(_T("target"), &Target);
            }

            bool IsValid() const
            {
                return (true);
            }

            UnmountParamsData(const UnmountParamsData&) = delete;
            UnmountParamsData& operator=(const UnmountParamsData&) = delete;

        public:
            Core::JSON::String ContainerId; // Identifier of container
            Core::JSON::String Target; // path to unmount from container
        }; // class UnmountParamsData

    } // namespace OCIContainer

} // namespace JsonData

// Enum conversion handlers
ENUM_CONVERSION_HANDLER(Exchange::IOCIContainer::ContainerState)

}

