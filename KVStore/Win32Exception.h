#pragma once

#include <Windows.h>
#include <string>
#include "Exception.h"

class Win32Exception : public Exception {
public:
    Win32Exception(const DWORD errorCode, const std::wstring &errorMessage, const Exception *innerException)
        : Exception(errorMessage, innerException)
    {
        this->p_errorCode = errorCode;
    }

    Win32Exception(const DWORD errorCode, const Exception *innerException)
        : Win32Exception(errorCode, L"", innerException)
    {
    }

    Win32Exception(const DWORD errorCode, const std::wstring &errorMessage)
        : Win32Exception(errorCode, errorMessage, NULL)
    {
    }

    std::wstring GetExceptionType() override {
        return L"Win32Exception";
    }

    std::wstring GetErrorMessage() override {
        return Exception::GetErrorMessage() + L", ErrorCode: " + std::to_wstring(p_errorCode);
    }

private:
    DWORD p_errorCode;
};
