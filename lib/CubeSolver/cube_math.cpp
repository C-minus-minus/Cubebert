#include "cube_math.h"

//  O(1) lookups for factorial up to n = 12
const int CubeMath::factorialTable[] =
    { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800 };

int CubeMath::factorial(int n) {
    return CubeMath::factorialTable[n];
}

int CubeMath::choose(int n, int k) {
    return CubeMath::factorialTable[n] /
        (CubeMath::factorialTable[k] * CubeMath::factorialTable[n - k]);
}

int CubeMath::permuationCoordinate(int* arr, int length) {

    // int mask = 0;
    // int* lemarCode = new int[length];
    // for(int i=0; i < length;i++) {
    //     lemarCode[i] = arr[i] - countBits[mask>>(length - arr[i])];
    //     mask |= 1<<(length - arr[i] - 1);
    // }

    // int permuationCoordinate = 0;
    // for(int i = 0, base = length - 1; i < length; i++, base--) {
    //     permuationCoordinate += lemarCode[i] * CubeMath::factorial(base);
    // }
    
    // return permuationCoordinate;
    int mask = 0;
    int permuationCoordinate = 0;
    for(int i=0, base = length - 1; i < length; i++, base--) {
        permuationCoordinate += 
            (arr[i] - countBits[mask>>(length - arr[i])]) * CubeMath::factorial(base);
        mask |= 1<<(length - arr[i] - 1);
    }
    return permuationCoordinate;

}

int* CubeMath::countBits = CubeMath::generateCountBits();

int* CubeMath::generateCountBits() {

    int* countBits = new int[4096];
    for(int i = 0; i < 4096; i++) {
        countBits[i] = naiveCountBits(i);
    }
    return countBits;
}

int CubeMath::naiveCountBits(int bits) {

    int bitCount = 0;
    for(int i=0;i<12;i++) {
        if((bits >> i) & 1) {
            bitCount++;
        }
    }
    return bitCount;
}

