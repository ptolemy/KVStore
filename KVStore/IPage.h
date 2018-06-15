#pragma once

#include "CommonTypes.h"

class IPage {
public:
    const static uint64 PageSize = 8192;
};

typedef struct
{
    uint64 PageId;
    uint16 PageType;
    uint16 AvailableSize;    
    byte data[IPage::PageSize - sizeof(uint16) - sizeof(uint16) - sizeof(uint64)];
} OnDiskPage, *POnDiskPage;


typedef struct {
    uint64 PageId;
    uint16 KeyLength;
} EntryHeader, *PEntryHeader;

typedef struct {
    void *Key;
    uint16 KeyLength;
}Key, *PKey;

class LinkEntry 
{
    // Logically struct of LinkEntry: KeyLength(2byte) + NextPage + Key
public:
    LinkEntry(void *ptr): m_basePtr(ptr)
    { }

    uint16 GetKeySize() {

    }


private:
    void *m_basePtr;
};

// LinkPage, LeafPage, DataPage for B+Tree
//class 
