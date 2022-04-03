#include "estimated_cube.h"

// Solver
#include "sticker_cube.h"
#include "TableManager.h"

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

    StickerCube *cube = new StickerCube(zeCube);

    TableManager* tableManager = TableManager::getInstance();

    //  solve phase 1
    std::cout << "\nStarting phase 1...\n";
    std::string phase1Solution = CubeSearch::getPhase1Solution(scrambleCube);
    //std::cout << phase1Solution << "\n";

    //  apply phase 1  solution to scrambled cube
    scrambleCube->applyScramble(phase1Solution);

    //  solve phase 2
    std::cout << "Starting phase 2...\n\n";
    std::string phase2Solution = CubeSearch::getPhase2Solution(scrambleCube);

    //  output complete solution
    std::cout << "Solution " << phase1Solution << phase2Solution << "\n";
    
    //  output efficient rotations
    std::cout << "\nSolution With Optimal Rotations " << convertTo4Arm(phase1Solution + phase2Solution) << "\n";

    return 0;
}
