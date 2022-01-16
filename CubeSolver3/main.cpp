#include <iostream>
#include <sstream>
#include "TableManager.h"
#include "CubeSearch.h"

int main() {

    StickerCube* cube = new StickerCube();
    cube->applyScramble("U B' D' F' U R' U B U' B2 R2 U2 F' R2 B' U2 D2 F U2 L2");
    std::cout << cube->getPhase2CornerCoordinate();
    exit(0);

    /*StickerCube* stickerCube = StickerCube::fromEdgePermutation(0);
    stickerCube->applyMove(CubeConstants::PHASE_1_MOVES[0]);
    std::cout << stickerCube->getPhase1EdgeCoordinate();
    exit(0);*/

    //int times = 40000;
    //StickerCube* stickerCube = StickerCube::fromEdgePermutation(0);
    //stickerCube->getPhase2EdgeCoordinate();
    ////exit(0);
    //for (int i = 0; i < times; i++) {
    //     
    //    //std::string s = std::to_string(123) + std::to_string(1222) + std::to_string(123);
    //    /*std::stringstream ss;
    //    ss << 12 << 23;
    //    ss.str();
    //    ss.str(std::string());*/
    //    
    //    for (int a = 0; a < 10; a++) {
    //        
    //        int b = stickerCube->getPhase2EdgeCoordinate();
    //    }
    //}
    //exit(0);

    //  Display welcome message
    std::cout << "Starting CubeSolver 2...\n";

    //  Create look up tables to enable very fast searching of the state graph
    std::cout << "Generating lookup tables...\n";
    TableManager* tableManager = TableManager::getInstance();

    //  Get scramble from user
    std::cout << "Please enter a scramble (standard notation separated via spaces): ";
    std::string scramble;
    std::cin >> scramble;

    //  Apply scramble to clean cube
    StickerCube* scrambleCube = new StickerCube(scramble);

    //  solve phase 1
    std::cout << "Starting phase 1...\n";
    std::string phase1Solution = CubeSearch::getPhase1Solution(scrambleCube);
    std::cout << phase1Solution << "\n";

    //  apply phase 1  solution to scrambled cube
    scrambleCube->applyScramble(phase1Solution);

    //  solve phase 2
    std::cout << "Starting phase 2...\n";
    std::string phase2Solution = CubeSearch::getPhase2Solution(scrambleCube);

    //  output complete solution
    std::cout << "Solution " << phase1Solution << " " << phase2Solution;

}