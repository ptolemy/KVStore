#pragma once

#include "CommonTypes.h"

namespace KVStore {
    namespace IO {
        class IFile {
        public:
            virtual void Read(void *buffer, uint64 fileOffset, uint32 lengthToRead) = 0;
            virtual void Write(void *buffer, uint64 fileOffset, uint32 lengthToWrite) = 0;
        };
    }
}

