#include "estimated_cube.h"

#include <iostream>

int main(int argc, char* argv[]) {
    EstimatedCube ec;
    ec.beginCapture();

    std::cout << "Starting Snapping\r\n";

    ec.captureSide();
    ec.captureSide();
    ec.captureSide();
    ec.captureSide();
    ec.captureSide();
    ec.captureSide();

    ec.endCapture();

    return 0;
}
