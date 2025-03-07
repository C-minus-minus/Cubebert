// Solver
#include "process_cube.h"

#include "algorithm_optimiser.h"
#include "cube_search.h"
#include "sticker_cube.h"
#include "table_manager.h"

#include <iostream>

int main(int argc, char* argv[]) {
    ProcessCube pc;
    std::cout << "Starting Snapping\r\n";

    int n;
    std::cout << "Enter a number between every picture\n";
    for(int i=0; i<6; ++i) {
        std::cout << "Please: ";
        std::cin >> n;
        pc.captureSide(i);
    }

    int **zeCube = pc.zeCube();
    for(int side=0; side<6; ++side) {
        std::cout << "\n\nSide: " << side << "\n";
        for(int y=0; y<3; ++y) {
            for(int x=0; x<3; ++x) {
                std::cout << zeCube[side][x + (y * 3)];
            }
            std::cout << "\n";
        }
    }

    std::cout << "Enter -1 if this cube detection is invalid: ";
    std::cin >> n;

    if(n != -1) {

    StickerCube *scrambleCube = new StickerCube(zeCube);

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
}

    return 0;
}
