#pragma once

#include <string>
#include "Exception.h"

namespace KVStore {
    namespace Common {
        class ArgumentException : public Exception {
        public:
            ArgumentException(const std::wstring &errorMessage, const Exception *innerException)
                : Exception(errorMessage, innerException)
            {
            }

            ArgumentException(const std::wstring &errorMessage)
                : ArgumentException(errorMessage, NULL)
            {
            }

            std::wstring GetExceptionType() override {
                return L"ArgumentException";
            }
        };
    }
}

