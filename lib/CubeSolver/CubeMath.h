#pragma once
class CubeMath {

    public:
        static int factorial(int n);

        static int choose(int n, int k);

        static int permuationCoordinate(int* arr, int length);

    private:
        const static int factorialTable[];

        static int* countBits;
        static int* generateCountBits();
        static int naiveCountBits(int bits);
};