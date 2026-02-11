// Generated automatically from 'ISharedStorage.h'. DO NOT EDIT.

#pragma once

#include "Module.h"
#include "JsonData_SharedStorageCache.h"
#include <interfaces/ISharedStorage.h>

namespace WPEFramework {

namespace Exchange {

    namespace JSharedStorageCache {

        namespace Version {

            constexpr uint8_t Major = 1;
            constexpr uint8_t Minor = 0;
            constexpr uint8_t Patch = 0;

        } // namespace Version

        using JSONRPC = PluginHost::JSONRPC;

        PUSH_WARNING(DISABLE_WARNING_UNUSED_FUNCTIONS)

        static void Register(JSONRPC& _module_, ISharedStorageCache* _impl_)
        {
            ASSERT(_impl_ != nullptr);

            _module_.RegisterVersion(_T("JSharedStorageCache"), Version::Major, Version::Minor, Version::Patch);

            // Register methods and properties...

            // Method: 'flushCache' - Flushes the device cache
            _module_.Register<void, void>(_T("flushCache"), 
                [_impl_]() -> uint32_t {
                    uint32_t _errorCode = Core::ERROR_NONE;

                    _errorCode = _impl_->FlushCache();

                    return (_errorCode);
                });

        }

        static void Unregister(JSONRPC& _module_)
        {
            // Unregister methods and properties...
            _module_.Unregister(_T("flushCache"));
        }

        POP_WARNING()

    } // namespace JSharedStorageCache

} // namespace Exchange

} // namespace WPEFramework

