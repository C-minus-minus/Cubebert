#include "estimated_cube.h"

int main(int argc, char* argv[]) {
    EstimatedCube ec;
    ec.beginCapture();
    ec.captureSide();
    ec.endCapture();

    return 0;
}