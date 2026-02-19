// C++ classes for NativeJS API JSON-RPC API.
// Generated automatically from 'INativeJS.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/INativeJS.h>

namespace WPEFramework {

namespace JsonData {

    namespace NativeJS {

        // Method params/result classes
        //

        class CreateApplicationParamsData : public Core::JSON::Container {
        public:
            CreateApplicationParamsData()
                : Core::JSON::Container()
            {
                Add(_T("options"), &Options);
            }

            bool IsValid() const
            {
                return (true);
            }

            CreateApplicationParamsData(const CreateApplicationParamsData&) = delete;
            CreateApplicationParamsData& operator=(const CreateApplicationParamsData&) = delete;

        public:
            Core::JSON::String Options; // Additional options for creating the application.
        }; // class CreateApplicationParamsData

        class RunApplicationParamsData : public Core::JSON::Container {
        public:
            RunApplicationParamsData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
                Add(_T("url"), &Url);
            }

            bool IsValid() const
            {
                return (true);
            }

            RunApplicationParamsData(const RunApplicationParamsData&) = delete;
            RunApplicationParamsData& operator=(const RunApplicationParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 Id; // The ID for the application to run.
            Core::JSON::String Url; // URL for the application to run.
        }; // class RunApplicationParamsData

        class RunJavaScriptParamsData : public Core::JSON::Container {
        public:
            RunJavaScriptParamsData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
                Add(_T("code"), &Code);
            }

            bool IsValid() const
            {
                return (true);
            }

            RunJavaScriptParamsData(const RunJavaScriptParamsData&) = delete;
            RunJavaScriptParamsData& operator=(const RunJavaScriptParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 Id; // The ID for the code to run.
            Core::JSON::String Code; // run a NativeJS code.
        }; // class RunJavaScriptParamsData

        class TerminateApplicationParamsData : public Core::JSON::Container {
        public:
            TerminateApplicationParamsData()
                : Core::JSON::Container()
            {
                Add(_T("id"), &Id);
            }

            bool IsValid() const
            {
                return (true);
            }

            TerminateApplicationParamsData(const TerminateApplicationParamsData&) = delete;
            TerminateApplicationParamsData& operator=(const TerminateApplicationParamsData&) = delete;

        public:
            Core::JSON::DecUInt32 Id; // The ID of the application to destroy.
        }; // class TerminateApplicationParamsData

    } // namespace NativeJS

} // namespace JsonData

}

