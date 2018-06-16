#include "Models.h"
#include "Utils.h"
#include <algorithm>

KVStore::BinaryAscKeyComparer KVStore::BinaryAscKeyComparer::Instance = BinaryAscKeyComparer();

int32 KVStore::BinaryAscKeyComparer::Compare(const Key &left, const Key &right) 
{
    if (left.KeyLength == right.KeyLength == 0)
        return 0;

    if (left.KeyLength == 0)
        return -1;

    if (right.KeyLength == 0)
        return 1;

    uint16 sizeToCompare = min(left.KeyLength, right.KeyLength);
    uint64 *leftCompareNumber = (uint64 *)left.Key;
    uint64 *rightCompareNumber = (uint64 *)right.Key;

    while (sizeToCompare >= 24) {
        if (*leftCompareNumber != *rightCompareNumber)
            break;

        if (*(leftCompareNumber + 1) != *(rightCompareNumber + 1)) {
            leftCompareNumber += 1;
            rightCompareNumber += 1;
            break;
        }

        if (*(leftCompareNumber + 2) != *(rightCompareNumber + 2)) {
            leftCompareNumber += 2;
            rightCompareNumber += 2;
            break;
        }

        leftCompareNumber += 3;
        rightCompareNumber += 3;
        sizeToCompare -= 24;
    }

    // left != right or size < 24
    if (sizeToCompare < 24) {
        while (sizeToCompare >= 8) {
            if (*leftCompareNumber != *rightCompareNumber)
                break;

            leftCompareNumber++;
            rightCompareNumber++;
            sizeToCompare -= 8;
        }
    }

    uint64 lNum = 0;
    uint64 rNum = 0;
    memcpy(&lNum, leftCompareNumber, min(sizeof(uint64), sizeToCompare));
    memcpy(&rNum, rightCompareNumber, min(sizeof(uint64), sizeToCompare));

    lNum = KVStore::Utils::ConvertEndian64(lNum);
    rNum = KVStore::Utils::ConvertEndian64(rNum);
    if (lNum < rNum)
        return -1;
    else if (lNum > rNum)
        return 1;
    else if (left.KeyLength < right.KeyLength)
        return -1;
    else if (left.KeyLength > right.KeyLength)
        return 1;
    return 0;
}