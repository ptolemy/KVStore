#pragma once

#include "IPage.h"
#include "IPageManager.h"
#include "Models.h"
#include "ArgumentException.h"

using namespace KVStore::DataStructure;

namespace KVStore {
    class BPlusTree {
    public:
        BPlusTree(const IPageManager &pManager): m_pageManager(pManager) 
        {}

        void Set(const Key &key, const Value &value) {

        }

        const Value Get(const Key &key) {

        }

        void Remove(const Key &key) {

        }

        bool Exists(const Key &key) {

        }

    private:
        const IPageManager &m_pageManager;
    };

    class IndexNode {
    public:
        IndexNode(PPhysicalPage page, IKeyComparer *comparer) 
            : m_comparer(comparer)
        {
            IndexPage p;
            m_linkedPage = (PIndexPage)page;
        }

        // If return true, outputLinkedEntryHeader is the found entry
        // If false 
        //      if outputLinkedEntryHeader.KeyLength > 0, then outputLinkedEntryHeader is the next bigger entry
        //      if outputLinkedEntryHeader.KeyLength == 0, then key is bigger than all the entries in this page
        bool TryFindKey(const Key &key, IndexEntryHeader &outputLinkedEntryHeader) 
        {
            PIndexEntryHeader ptr = NULL;
            bool ret = TryFindKeyImpl(key, ptr);

            outputLinkedEntryHeader.KeyLength = 0;
            outputLinkedEntryHeader.Son.PageId = 0;

            if (ret) {
                outputLinkedEntryHeader = *ptr;
            }

            return ret;
        }

        bool InsertEntry(const Key &key, const PageId &pid) {
            if (GetFreeSpaceSize() < sizeof(IndexEntryHeader) + key.KeyLength)
                throw KVStore::Common::ArgumentException(L"Not enough space left in this page");

            PIndexEntryHeader leh;
            bool find = TryFindKeyImpl(key, leh);

            // TODO:
            int sizeToInsert = sizeof(IndexEntryHeader) + key.KeyLength;
            memcpy((byte*)leh + sizeToInsert, leh, PageSize - ((byte*)leh - (byte*)m_linkedPage + GetFreeSpaceSize()));

            IndexEntryHeader nEntryHeader;
            nEntryHeader.KeyLength = key.KeyLength;
            nEntryHeader.Son = pid;
            memcpy(leh, &nEntryHeader, sizeof(nEntryHeader));
            memcpy((byte*)leh + sizeof(nEntryHeader), key.Key, key.KeyLength);
        }

        bool RemoveEntry(const Key &key) {
            PIndexEntryHeader leh;
            bool find = TryFindKeyImpl(key, leh);

            if (!find) {
                throw KVStore::Common::ArgumentException(L"Key not found in this page");
            }

            int sizeToFree = sizeof(IndexEntryHeader) + leh->KeyLength;
            int remainingOffsetInPage = (byte*)leh + sizeToFree - (byte*)m_linkedPage;
            int remainingSize = PageSize - remainingOffsetInPage - GetFreeSpaceSize();
            memcpy(leh, (byte*)m_linkedPage + remainingOffsetInPage, remainingSize);

            m_linkedPage->LPageHeader.PageHeader.FreeBytes += sizeToFree;
            memset((byte*)m_linkedPage + PageSize - GetFreeSpaceSize(),
                0, 
                m_linkedPage->LPageHeader.PageHeader.FreeBytes);
        }

        bool CloneTo(PPhysicalPage page) {
            memcpy(page, m_linkedPage, PageSize);
        }

        uint16 GetFreeSpaceSize() {
            return m_linkedPage->LPageHeader.PageHeader.FreeBytes;
        }


    private:
        PIndexPage m_linkedPage;
        IKeyComparer *m_comparer;

        bool TryFindKeyImpl(const Key &key, PIndexEntryHeader &outputLinkedEntryHeader) {
            outputLinkedEntryHeader = NULL;

            byte *cur = (byte*)m_linkedPage->Data;
            int left = sizeof(m_linkedPage->Data);

            while (left > sizeof(IndexEntryHeader)) {
                PIndexEntryHeader entryHeader = (PIndexEntryHeader)cur;
                if (entryHeader->KeyLength <= 0)
                    return false;

                Key ek = Key(entryHeader->KeyLength, cur + sizeof(IndexEntryHeader));
                int32 cmp = m_comparer->Compare(key, ek);

                if (cmp == 0) {
                    outputLinkedEntryHeader = entryHeader;
                    return true;
                }
                if (cmp > 0) {
                    outputLinkedEntryHeader = entryHeader;
                    return false;
                }

                cur += sizeof(IndexEntryHeader) + entryHeader->KeyLength;
                left -= sizeof(IndexEntryHeader) + entryHeader->KeyLength;
            }

            return false;
        }
    };
}
