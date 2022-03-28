#include "estimated_cube.h"

#include <iostream>

int main(int argc, char* argv[]) {
    EstimatedCube ec;
    ec.beginCapture();

    std::cout << "Starting Snapping\r\n";

    int n;

    std::cout << "Enter a number between every picture\n";
    for(int i=0; i<6; ++i) {
        std::cout << "Please: ";
        std::cin >> n;
        ec.captureSide(i);
    }

    ec.endCapture();

    int **zeCube = ec.zeCube();
    for(int side=0; side<6; ++side) {
        std::cout << "\n\nSide: " << side << "\n";
        for(int y=0; y<3; ++y) {
            for(int x=0; x<3; ++x) {
                std::cout << zeCube[side][x + (y * 3)];
                if(x == 2)
                    std::cout << '|';
            }
            std::cout << "\n";
        }
    }

    return 0;
}
