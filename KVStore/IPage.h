#pragma once

#include "CommonTypes.h"

namespace KVStore {
    namespace DataStructure {
        // DataStructure for the B+ Tree
        const static uint64 PageSize = 8192;

        typedef enum: byte {
            MetadataPageType,
            IndexPageType,
            IndexLeafPageType,
            DataPageType,
        } PageType;

        typedef struct {
            uint32 PageId;
            uint32 Version;
        } PageId, *PPageId;

        typedef struct {
            PageId Id;
            PageType Type;  // 1byte
            uint16 FreeBytes;
            byte Reserved[5];
        } PageHeader, *PPageHeader;

        typedef struct {
            PageHeader PHeader;
            byte Data[PageSize - sizeof(PageHeader)];
        } PhysicalPage, *PPhysicalPage;


        /*
            Linked Page Struct should be like:
            |<-     Header(8byte)        ->|<-          Entry1                 ->|<-          Entry2                 ->| .......  Entry n ->| NotUsed |
            | Type | Reserved | FatherPage | SonPage1 | KeyLength1 | ... Key1 ...| SonPage2 | KeyLength2 | ... Key2 ...| ......| ...Key n...| NotUsed |
        */

        typedef struct{
            PageHeader PageHeader;
            PageId Father; // 8 byte
        } IndexPageHeader, *PIndexPageHeader;

        typedef struct {
            IndexPageHeader LPageHeader;
            byte Data[PageSize - sizeof(IndexPageHeader)];
        } IndexPage, *PIndexPage;

        typedef struct {
            PageId Son;    // Point to Next Level Page
            uint16 KeyLength;
        } IndexEntryHeader, *PIndexEntryHeader;
         
        typedef struct {
            IndexPageHeader IndexPageHeader;
            PageId RightPage;
        } IndexLeafPageHeader, *PIndexLeafPageHeader;

        typedef struct {
            PageId PageId;
            uint16 PageOffset;
        } DataItemLink;

        typedef struct {
            DataItemLink DataLink;
            uint16 KeyLength;
        } IndexLeafEntryHeader;

        typedef struct DateItemHeader {
            uint16 DataSegmentSize;
        } DateItemHeader;
    }
}
