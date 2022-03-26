#include "CubeMath.h"

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