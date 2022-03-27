#include "estimated_cube.h"

#include <iostream>

int main(int argc, char* argv[]) {
    EstimatedCube ec;
    ec.beginCapture();

    std::cout << "Starting Snapping\r\n";

    int n;

    std::cout << "Enter a number between every picture";
    std::cin >> n;
    ec.captureSide(0);
    std::cin >> n;
    ec.captureSide(1);
    std::cin >> n;
    ec.captureSide(2);
    std::cin >> n;
    ec.captureSide(3);
    std::cin >> n;
    ec.captureSide(4);
    std::cin >> n;
    ec.captureSide(5);

    ec.endCapture();

    int **zeCube = ec.zeCube();
    for(int side=0; side<6; ++side) {
        std::cout << "\n\nSide: " << side << "\n";
        for(int y=0; y<3; ++y) {
            for(int x=0; x<3; ++x) {
                std::cout << zeCube[y][x];
                if(x == 2)
                    std::cout << '|';
            }
            std::cout << "\n";
        }
    }

    return 0;
}
