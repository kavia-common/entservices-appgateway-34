// C++ classes for Browser CookieJar API JSON-RPC API.
// Generated automatically from 'CookieJar.json'. DO NOT EDIT.

// Note: This code is inherently not thread safe. If required, proper synchronisation must be added.

#pragma once

#include <core/JSON.h>

namespace WPEFramework {

namespace JsonData {

    namespace BrowserCookieJar {

        // Method params/result classes
        //

        class CookiejarData : public Core::JSON::Container {
        public:
            CookiejarData()
                : Core::JSON::Container()
            {
                Add(_T("version"), &Version);
                Add(_T("checksum"), &Checksum);
                Add(_T("payload"), &Payload);
            }

            bool IsValid() const
            {
                return (true);
            }

            CookiejarData(const CookiejarData&) = delete;
            CookiejarData& operator=(const CookiejarData&) = delete;

        public:
            Core::JSON::DecUInt32 Version; // Version of payload format
            Core::JSON::DecUInt32 Checksum; // The checksum of the string used for payload creation
            Core::JSON::String Payload; // Base64 string representation of compressed and encrypted cookies
        }; // class CookiejarData

    } // namespace BrowserCookieJar

} // namespace JsonData

}

