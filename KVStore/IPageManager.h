#pragma once

#include "IPage.h"
#include <queue>
#include <hash_map>

using namespace std;
using namespace KVStore::DataStructure;

namespace KVStore {
    class IPageManager {
    public:
        virtual PPhysicalPage NewPage() = 0;
        virtual void UpdatePage(const PPhysicalPage &page) = 0;
        virtual PPhysicalPage GetPage(const PageId &pid) = 0;
        virtual void RemovePage(const PageId &pid) = 0;
    };

    // Simple implementation of IPageManager for test
    class SimpleMemoryPageManager : public IPageManager {
    public:
        SimpleMemoryPageManager(int initialPages = 16) 
        {
            for (int i = 0; i < initialPages; i++) {
                PPhysicalPage page = new PhysicalPage;
                memset(page, 0, sizeof(PhysicalPage));
                page->PHeader.Id.PageId = i;

                m_freePages.push(page->PHeader.Id);
                m_pageMaps[page->PHeader.Id] = page;
            }
        }

        PPhysicalPage NewPage() override {
            if (m_freePages.empty()) {
                m_managedPages++;
                PPhysicalPage page = new PhysicalPage;
                memset(page, 0, sizeof(PhysicalPage));
                page->PHeader.Id.PageId = m_managedPages;

                m_freePages.push(page->PHeader.Id);
                m_pageMaps[page->PHeader.Id] = page;
            }

            PageId pid = m_freePages.front();
            m_freePages.pop();
            return GetPage(pid);
        }

        void UpdatePage(const PPhysicalPage &page) override {
            // do nothing as the data in memory already updated;
        }

        PPhysicalPage GetPage(const PageId &pid) override {
            return m_pageMaps[pid];
        }

        void RemovePage(const PageId &pid) override {
            m_freePages.push(pid);
        }

        ~SimpleMemoryPageManager() {
            for (hash_map<PageId, PPhysicalPage>::iterator iter = m_pageMaps.begin();
                iter != m_pageMaps.end();
                iter++) 
            {
                delete iter->second;
            }
        }

    private:
        uint32 m_managedPages = 0;
        queue<PageId> m_freePages;
        hash_map<PageId, PPhysicalPage> m_pageMaps;
    };
}
