#pragma once

#include "Win32Exception.h"
#include "Exception.h"

namespace KVStore {
    namespace IO {
        class IOException : public KVStore::Common::Win32Exception {
        public:
            IOException(const DWORD errorCode, const std::wstring &errorMessage, const Exception *innerException)
                : Win32Exception(errorCode, errorMessage, innerException)
            {
            }

            IOException(const DWORD errorCode, const Exception *innerException)
                : Win32Exception(errorCode, L"", innerException)
            {
            }

            IOException(const DWORD errorCode, const std::wstring &errorMessage)
                : Win32Exception(errorCode, errorMessage, NULL)
            {
            }

            std::wstring GetExceptionType() override {
                return L"IOException";
            }
        };
    }
}
