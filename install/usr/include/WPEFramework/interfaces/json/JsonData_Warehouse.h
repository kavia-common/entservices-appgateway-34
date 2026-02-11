// C++ classes for Warehouse API JSON-RPC API.
// Generated automatically from 'IWarehouse.h'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>
#include <interfaces/IWarehouse.h>

namespace WPEFramework {

namespace JsonData {

    namespace Warehouse {

        // Common classes
        //

        class WarehouseSuccessErrInfo : public Core::JSON::Container {
        public:
            WarehouseSuccessErrInfo()
                : Core::JSON::Container()
            {
                _Init();
            }

            WarehouseSuccessErrInfo(const Exchange::IWarehouse::WarehouseSuccessErr& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                Error = _other.error;
                _Init();
            }

            WarehouseSuccessErrInfo& operator=(const Exchange::IWarehouse::WarehouseSuccessErr& _rhs)
            {
                Success = _rhs.success;
                Error = _rhs.error;
                return (*this);
            }

            operator Exchange::IWarehouse::WarehouseSuccessErr() const
            {
                Exchange::IWarehouse::WarehouseSuccessErr _value{};
                _value.success = Success;
                _value.error = Error;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("success"), &Success);
                Add(_T("error"), &Error);
            }

        public:
            Core::JSON::Boolean Success; // Invokes the internal reset script, which reboots the Warehouse service
            Core::JSON::String Error; // Invokes the internal reset script, which reboots the Warehouse service
        }; // class WarehouseSuccessErrInfo

        // Method params/result classes
        //

        class WarehouseSuccessData : public Core::JSON::Container {
        public:
            WarehouseSuccessData()
                : Core::JSON::Container()
            {
                _Init();
            }

            WarehouseSuccessData(const Exchange::IWarehouse::WarehouseSuccess& _other)
                : Core::JSON::Container()
            {
                Success = _other.success;
                _Init();
            }

            WarehouseSuccessData& operator=(const Exchange::IWarehouse::WarehouseSuccess& _rhs)
            {
                Success = _rhs.success;
                return (*this);
            }

            operator Exchange::IWarehouse::WarehouseSuccess() const
            {
                Exchange::IWarehouse::WarehouseSuccess _value{};
                _value.success = Success;
                return (_value);
            }

            bool IsValid() const
            {
                return (true);
            }

        private:
            void _Init()
            {
                Add(_T("success"), &Success);
            }

        public:
            Core::JSON::Boolean Success; // Starts a hardware test on the device
        }; // class WarehouseSuccessData

        class GetHardwareTestResultsResultData : public Core::JSON::Container {
        public:
            GetHardwareTestResultsResultData()
                : Core::JSON::Container()
            {
                Add(_T("success"), &Success);
                Add(_T("testResults"), &TestResults);
            }

            bool IsValid() const
            {
                return (true);
            }

            GetHardwareTestResultsResultData(const GetHardwareTestResultsResultData&) = delete;
            GetHardwareTestResultsResultData& operator=(const GetHardwareTestResultsResultData&) = delete;

        public:
            Core::JSON::Boolean Success; // - out - boolean
            Core::JSON::String TestResults; // - out - string
        }; // class GetHardwareTestResultsResultData

        class InternalResetParamsData : public Core::JSON::Container {
        public:
            InternalResetParamsData()
                : Core::JSON::Container()
            {
                Add(_T("passPhrase"), &PassPhrase);
            }

            bool IsValid() const
            {
                return (true);
            }

            InternalResetParamsData(const InternalResetParamsData&) = delete;
            InternalResetParamsData& operator=(const InternalResetParamsData&) = delete;

        public:
            Core::JSON::String PassPhrase; // - in - string
        }; // class InternalResetParamsData

        class IsCleanParamsData : public Core::JSON::Container {
        public:
            IsCleanParamsData()
                : Core::JSON::Container()
            {
                Add(_T("age"), &Age);
            }

            bool IsValid() const
            {
                return (true);
            }

            IsCleanParamsData(const IsCleanParamsData&) = delete;
            IsCleanParamsData& operator=(const IsCleanParamsData&) = delete;

        public:
            Core::JSON::DecSInt32 Age; // - in - integer
        }; // class IsCleanParamsData

        class IsCleanResultData : public Core::JSON::Container {
        public:
            IsCleanResultData()
                : Core::JSON::Container()
            {
                Add(_T("clean"), &Clean);
                Add(_T("files"), &Files);
                Add(_T("success"), &Success);
                Add(_T("error"), &Error);
            }

            bool IsValid() const
            {
                return (true);
            }

            IsCleanResultData(const IsCleanResultData&) = delete;
            IsCleanResultData& operator=(const IsCleanResultData&) = delete;

        public:
            Core::JSON::Boolean Clean; // - out - boolean
            Core::JSON::ArrayType<Core::JSON::String> Files; // - out - string [] of file locations for each file
            Core::JSON::Boolean Success; // - out - boolean
            Core::JSON::String Error; // -out - string
        }; // class IsCleanResultData

        class ResetDeviceParamsData : public Core::JSON::Container {
        public:
            ResetDeviceParamsData()
                : Core::JSON::Container()
            {
                Add(_T("suppressReboot"), &SuppressReboot);
                Add(_T("resetType"), &ResetType);
            }

            bool IsValid() const
            {
                return (true);
            }

            ResetDeviceParamsData(const ResetDeviceParamsData&) = delete;
            ResetDeviceParamsData& operator=(const ResetDeviceParamsData&) = delete;

        public:
            Core::JSON::Boolean SuppressReboot; // - in - bool
            Core::JSON::String ResetType; // - in - string
        }; // class ResetDeviceParamsData

    } // namespace Warehouse

} // namespace JsonData

}

