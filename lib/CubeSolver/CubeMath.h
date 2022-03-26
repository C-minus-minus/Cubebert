#pragma once
class CubeMath {

    public:
        static int factorial(int n);

        static int choose(int n, int k);

    private:
        const static int factorialTable[];
};