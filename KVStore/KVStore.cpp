// KVStore.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "CommonTypes.h"
#include "WinPageFile.h"
#include "IPage.h"

enum PageType {
    DataPage,
    LinkPage,
    MetadataPage
};

int main()
{
    try {
        UINT64 t = 0;
        WinPageFile file(L"test.txt");

        char array[512];
        for (int i = 0; i < 512; i++) {
            array[i] = 0x33;
        }

        file.Write(array, 1024, 512);
    }
    catch (Exception &e) {
        std::wcerr << e.GetMessage() << std::endl;
    }

    return 0;
}

