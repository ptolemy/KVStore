#pragma once

#include "IFile.h"
#include <Windows.h>
#include "IOException.h"

class WinPageFile : IFile 
{
public:
    WinPageFile(const std::wstring &fileName): m_fileName(fileName){
        m_hFile = CreateFile(
            m_fileName.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ,
            NULL,
            OPEN_ALWAYS,
            FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,
            NULL);

        if (m_hFile == INVALID_HANDLE_VALUE) {
            throw IOException(GetLastError(), L"Fail to open file: " + m_fileName);
        }
    }

    void Read(void *buffer, uint64 fileOffset, uint32 lengthToRead) override {
        OVERLAPPED overlap;
        memset(&overlap, 0, sizeof(OVERLAPPED));
        overlap.Offset = fileOffset;
        overlap.OffsetHigh = fileOffset >> 32;
        overlap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        DWORD ret;
        ReadFile(
            m_hFile,
            buffer,
            lengthToRead,
            NULL,
            &overlap);
        ret = GetLastError();
        if (ret != ERROR_IO_PENDING)
        {
            throw IOException(GetLastError(), L"Fail to start async write file: " + m_fileName);
        }

        DWORD length;
        if (!GetOverlappedResult(
            m_hFile,
            &overlap,
            &length,
            true))
        {
            throw IOException(GetLastError(), L"Fail to write file: " + m_fileName);
        }
    }

    void Write(void *buffer, uint64 fileOffset, uint32 lengthToWrite) override {
        OVERLAPPED overlap;
        memset(&overlap, 0, sizeof(OVERLAPPED));
        overlap.Offset = fileOffset;
        overlap.OffsetHigh = fileOffset >> 32;
        overlap.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

        DWORD ret;
        WriteFile(
            m_hFile,
            buffer,
            lengthToWrite,
            NULL,
            &overlap);
        ret = GetLastError();
        if (ret != ERROR_IO_PENDING)
        {
            throw IOException(GetLastError(), L"Fail to start async write file: " + m_fileName);
        }

        DWORD length;
        if (!GetOverlappedResult(
            m_hFile,
            &overlap,
            &length,
            true))
        {
            throw IOException(GetLastError(), L"Fail to write file: " + m_fileName);
        }
    }

private:
    HANDLE m_hFile;
    std::wstring m_fileName;
};