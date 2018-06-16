#pragma once

#include "CommonTypes.h"
#include "IPage.h"

namespace KVStore{
    typedef struct K{
        uint16 KeyLength;
        void *Key;

        K() {}

        K(uint16 l, void *ptr) {
            KeyLength = l;
            Key = ptr;
        }
    } Key, *PKey;

    typedef struct V {
        uint32 ValueLength;
        const void * const Value;

        V(uint32 vLen, void *ptr): ValueLength(vLen), Value(ptr) 
        { }
    } Value, *PValue;

    // And key entry stored in page consist of KeyLength + PageId + KeyData
    // Define slot -> 8 byte aligned. That a 8kb page should contain 64 slot
    // Each key entry was consist of 1 ~ 8 slot. Thus a page could contain 8~64 key entries.
    const static uint16 MaxKeyLength = 1024 - sizeof(KVStore::DataStructure::PageId) - sizeof(uint16);

    class IKeyComparer {
    public:
        virtual int32 Compare(const Key &left, const Key &right) = 0;
    };

    // Dictionary Order Comparer
    class BinaryAscKeyComparer: IKeyComparer 
    {
    public:
        static BinaryAscKeyComparer Instance;

        int32 Compare(const Key &left, const Key &right) override;
    };
}