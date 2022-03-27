#include "estimated_cube.h"

#include <iostream>

int main(int argc, char* argv[]) {
    EstimatedCube ec;
    ec.beginCapture();

    std::cout << "Starting Snapping\r\n";

    ec.captureSide(0);
    //ec.captureSide(1);
    //ec.captureSide(2);
    //ec.captureSide(3);
    //ec.captureSide(4);
    //ec.captureSide(5);

    ec.endCapture();

    return 0;
}
