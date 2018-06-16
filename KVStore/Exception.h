#pragma once

#include <iostream>

namespace KVStore {
    namespace Common {
        class Exception
        {
        public:
            Exception(const std::wstring &errMessage, const Exception *innerException) :
                errorMessage(errMessage)
            {
                this->innerException = innerException;
            }

            Exception(const std::wstring &errMessage) : Exception(errMessage, NULL)
            { }

            ~Exception() {
                if (this->innerException != NULL) {
                    delete this->innerException;
                    this->innerException = NULL;
                }
            }

            virtual std::wstring GetErrorMessage() {
                return GetExceptionType() + L": " + errorMessage;
            }

            std::wstring GetMessage() {
                std::wstring ret = GetErrorMessage();
                const Exception *cur = this;
                while (cur->innerException) {
                    ret += L"\r\n -> " + GetErrorMessage();
                    cur = cur->innerException;
                }

                return ret;
            }

            virtual std::wstring GetExceptionType() {
                return L"Exception";
            }

        private:
            const Exception *innerException;
            std::wstring errorMessage;
        };
    }
}


