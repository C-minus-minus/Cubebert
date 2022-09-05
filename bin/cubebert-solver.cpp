#include <iostream>
#include <sstream>
#include <chrono>
#include "TableManager.h"
#include "CubeSearch.h"
#include "algorithm_optimiser.h"

using namespace std::chrono;

int main() {

    //  Display welcome message
    std::cout << "Starting CubeSolver 3...\n\n";

    //  Create look up tables to enable very fast searching of the state graph
    std::cout << "Generating lookup tables...\n\n";
    TableManager* tableManager = TableManager::getInstance();
    std::cout<<"generation complete\n";

    // int max = 0;
    // for(int i=0;i<CubeConstants::PHASE_2_MAX_BAR1_COORDINATE;i++) {
    //     for(int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
    //         max = std::min(max, tableManager->getInstance()->phase2Bar1MoveTable[i][move]);
    //     }
    // }
    // std::cout<<max;
    // return 0;

    // StickerCube* stickerCube = new StickerCube();
    //stickerCube->applyMove("D2 R' B2 F D2 F2 U2 L2 D2 U2 F U2 B D R' F D B2 R' U'");
    // std::cout<< "1: "<< stickerCube->getPhase2Bar1Coordinate()<<"\n";
    // std::cout<< "2: "<< stickerCube->getPhase2Bar2Coordinate()<<"\n";
    // std::cout<< "3: "<< stickerCube->getPhase2Bar3Coordinate()<<"\n";
    // std::cout<< "4: "<< stickerCube->getPhase2Bar4Coordinate()<<"\n";
    // return 0;

    // int max1 = 0;
    // double avg1 = 0;
    // for(int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
    //     max1 = std::min(tableManager->getInstance()->phase2Bar4PruningTable[i],max1);
    //     avg1 += tableManager->getInstance()->phase2Bar4PruningTable[i];
    // }
    // int max2 = 0;
    // double avg2 = 0;
    // for(int i = 0; i < CubeConstants::PHASE_2_MAX_CORNER_COORDINATE; i++) {
    //     max2 = std::max(tableManager->getInstance()->phase2CornerPruningTable[i],max2);
    //     avg2 += tableManager->getInstance()->phase2CornerPruningTable[i];
    // }
    // int max3 = 0;
    // double avg3 = 0;
    // for(int i = 0; i < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; i++) {
    //     max3 = std::max(tableManager->getInstance()->phase2EdgePruningTable[i],max3);
    //     avg3 += tableManager->getInstance()->phase2EdgePruningTable[i];
    // }
    // std::cout<<"\nThe furthest prune is: "<<max1;
    // std::cout<<"\nThe average prune is: "<<avg1 / CubeConstants::PHASE_2_MAX_BAR1_COORDINATE;

    // std::cout<<"\nThe furthest prune is: "<<max2;
    // std::cout<<"\nThe average prune is: "<<avg2 / CubeConstants::PHASE_2_MAX_CORNER_COORDINATE;

    // std::cout<<"\nThe furthest prune is: "<<max3;
    // std::cout<<"\nThe average prune is: "<<avg3 / CubeConstants::PHASE_2_MAX_EDGE_COORDINATE;
    //return 0;

    while(true) {
        //  Get scramble from user
        std::cout << "Please enter a scramble (standard notation separated via spaces): ";
        std::string scramble;
        std::getline(std::cin, scramble);

        //  Apply scramble to clean cube
        StickerCube* scrambleCube = new StickerCube(scramble);

        //  solve phase 1
        std::cout << "\nStarting phase 1...\n";
        std::string phase1Solution = CubeSearch::getPhase1Solution(scrambleCube);
        //std::cout << phase1Solution << "\n";

        //  apply phase 1  solution to scrambled cube
        scrambleCube->applyScramble(phase1Solution);


        //  solve phase 2
        std::cout << "Starting phase 2...\n\n";
        //
        auto start = high_resolution_clock::now();
        //
        std::string phase2Solution = CubeSearch::getPhase2SolutionE(scrambleCube);
        //
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
    
        std::cout << "Time taken by function: "
            << duration.count() << " microseconds\n";
        //

        //  output complete solution
        std::cout << "Solution " << phase1Solution << phase2Solution << "\n";
        
        //  output efficient rotations
        std::cout << "\nSolution With Optimal Rotations " << convertTo4Arm(phase1Solution + phase2Solution) << "\n";
    }

    
}