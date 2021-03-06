// KVStore.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>
#include "CommonTypes.h"
#include "WinPageFile.h"
#include "IPage.h"
#include "Models.h"

using namespace std;
using namespace KVStore;
using namespace KVStore::IO;
using namespace KVStore::Common;
using namespace KVStore::DataStructure;

int DirectByteArrayCompare(const Key &left, const Key &right) {
    int cmpLength = min(left.KeyLength, right.KeyLength);

    char *pleft = (char *)left.Key;
    char *pright = (char *)right.Key;

    for (int i = 0; i < cmpLength; i++) {
        char left = *pleft++;
        char right = *pright++;
        if (left < right)
            return -1;
        if (left > right)
            return 1;
    }

    return left.KeyLength == right.KeyLength ? 0 : (left.KeyLength < left.KeyLength ? -1 : 1);
}

int main()
{
    ////try {
    ////    UINT64 t = 0;
    ////    WinPageFile file(L"test.txt");

    ////    char array[512];
    ////    for (int i = 0; i < 512; i++) {
    ////        array[i] = 0x33;
    ////    }

    ////    file.Write(array, 1024, 512);
    ////}
    ////catch (Exception &e) {
    ////    std::wcerr << e.GetMessage() << std::endl;
    ////}

    //char array1[65536] = { 0,1,2,3,4,5,6,7 };
    //char array2[65536] = { 1,1,2,3,4,0,0,0 };

    ////memset(array1, 0, 65536);
    ////memset(array2, 0, 65536);

    //Key left;
    //left.KeyLength = 65535;
    //left.Key = array1;

    //Key right;
    //right.KeyLength = 65535;
    //right.Key = array2;

    //std::clock_t start = std::clock();

    ////for (int i = 0; i < 10000; i++) {
    ////    BinaryAscKeyComparer::Instance.Compare(left, right);

    ////    //DirectByteArrayCompare64(left, right);
    ////}   

    //std::clock_t end = std::clock();
    //cout << (end - start) << " ms" << endl;

    //cout << DirectByteArrayCompare(left, right) << endl;
    //cout << BinaryAscKeyComparer::Instance.Compare(left, right) << endl;


    cout << sizeof(PageType) << endl;
    cout << sizeof(PhysicalPage) << endl;



    return 0;
}

