#pragma once

#include "CommonTypes.h"

namespace KVStore {
    namespace Utils {
        uint64 ConvertEndian64(uint64 num) {
            uint64 ret = 0;
            const static uint64 mask = 0x00000000000000ff;

            ret |= num & mask;
            ret <<= 8;
            num >>= 8;

            ret |= num & mask;
            ret <<= 8;
            num >>= 8;

            ret |= num & mask;
            ret <<= 8;
            num >>= 8;

            ret |= num & mask;
            ret <<= 8;
            num >>= 8;

            ret |= num & mask;
            ret <<= 8;
            num >>= 8;

            ret |= num & mask;
            ret <<= 8;
            num >>= 8;

            ret |= num & mask;
            ret <<= 8;
            num >>= 8;

            ret |= num & mask;

            return ret;
        }
    }
}
