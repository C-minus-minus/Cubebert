#include <iostream>
#include <sstream>
#include <chrono>
#include "CubeMath.h"
#include "TableManager.h"
#include "CubeSearch.h"
#include "algorithm_optimiser.h"

using namespace std::chrono;

int main() {

    //  Display welcome message
    std::cout << "Starting CubeSolver 3...\n\n";

    // int arr[] = {0, 1, 2, 3, 4};
    // std::cout<<CubeMath::permuationCoordinate(arr, 5);
    // return 0;

    // StickerCube* cube = new StickerCube();
    // cube->applyMove("D2");
    // std::cout<<cube->getPhase2Side1Coordinate()<<"\n";
    // cube->applyMove("D2");
    // std::cout<<cube->getPhase2Side1Coordinate();
    // return 0;

    //  Create look up tables to enable very fast searching of the state graph
    std::cout << "Generating lookup tables...\n\n";
    TableManager* tableManager = TableManager::getInstance();
    std::cout<<"generation complete\n";

    

    int max = 0;
    int min = 0;
    for(int i=0;i<CubeConstants::PHASE_2_MAX_SIDE_COORDINATE;i++) {
        for(int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            max = std::max(max, tableManager->getInstance()->phase2Side1MoveTable[i][move]);
            min = std::min(min, tableManager->getInstance()->phase2Side1MoveTable[i][move]);
        }
    }
    std::cout<<"Max side 1 coord is: "<<max<<"\n";
    std::cout<<"Min side 1 coord is: "<<min<<"\n";

    int maxE = 0;
    int minE = 0;
    for(int i=0;i<CubeConstants::PHASE_2_MAX_SIDE_COORDINATE;i++) {
        for(int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            maxE = std::max(maxE, tableManager->getInstance()->phase2Side2MoveTable[i][move]);
            minE = std::min(minE, tableManager->getInstance()->phase2Side2MoveTable[i][move]);
        }
    }
    std::cout<<"Max side 2 coord is: "<<maxE<<"\n";
    std::cout<<"Min side 2 coord is: "<<minE<<"\n";
  

    // StickerCube* stickerCube = new StickerCube();
    // stickerCube->applyMove("");
    // std::cout<< "1: "<< stickerCube->getPhase2Bar1Coordinate()<<"\n";
    // std::cout<< "2: "<< stickerCube->getPhase2Bar2Coordinate()<<"\n";
    // std::cout<< "3: "<< stickerCube->getPhase2Bar3Coordinate()<<"\n";
    // std::cout<< "4: "<< stickerCube->getPhase2Bar4Coordinate()<<"\n";
    // return 0;

    int max1 = 0;
    double avg1 = 0;
    for(int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        max1 = std::min(tableManager->getInstance()->phase2Side1PruningTable[i],max1);
        avg1 += tableManager->getInstance()->phase2Side1PruningTable[i];
    }
    int max2 = 0;
    double avg2 = 0;
    for(int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        max2 = std::max(tableManager->getInstance()->phase2Side2PruningTable[i],max2);
        avg2 += tableManager->getInstance()->phase2Side2PruningTable[i];
    }
    // int max3 = 0;
    // double avg3 = 0;
    // for(int i = 0; i < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; i++) {
    //     max3 = std::max(tableManager->getInstance()->phase2EdgePruningTable[i],max3);
    //     avg3 += tableManager->getInstance()->phase2EdgePruningTable[i];
    // }
    std::cout<<"\nThe furthest side1 prune is: "<<max1;
    std::cout<<"\nThe average side1 prune is: "<<avg1 / CubeConstants::PHASE_2_MAX_SIDE_COORDINATE;

    std::cout<<"\nThe furthest side2 prune is: "<<max2;
    std::cout<<"\nThe average side2 prune is: "<<avg2 / CubeConstants::PHASE_2_MAX_SIDE_COORDINATE;
    return;

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
        StickerCube* scrambleCubeE = new StickerCube(scramble);
        StickerCube* scrambleCubeF = new StickerCube(scramble);

        //  solve phase 1
        std::cout << "\nStarting phase 1...\n";
        std::string phase1Solution = CubeSearch::getPhase1Solution(scrambleCube);
        //std::cout << phase1Solution << "\n";

        //  apply phase 1  solution to scrambled cube
        scrambleCube->applyScramble(phase1Solution);
        scrambleCubeE->applyScramble(phase1Solution);
        scrambleCubeF->applyScramble(phase1Solution);


        //  solve phase 2
        std::cout << "Starting phase 2...\n";
        auto start = high_resolution_clock::now();
        std::string phase2Solution = CubeSearch::getPhase2Solution(scrambleCube);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Time taken by function: "<< duration.count() << " microseconds\n";

        //  solve phase 2
        std::cout << "Starting phase 2E...\n";
        start = high_resolution_clock::now();
        phase2Solution = CubeSearch::getPhase2SolutionE(scrambleCubeE);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        std::cout << "Time taken by functionE: "<< duration.count() << " microseconds\n";

        //  solve phase 2
        std::cout << "Starting phase 2F...\n";
        start = high_resolution_clock::now();
        phase2Solution = CubeSearch::getPhase2SolutionF(scrambleCubeF);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        std::cout << "Time taken by functionF: "<< duration.count() << " microseconds\n";

        //  output complete solution
        std::cout << "Solution " << phase1Solution << phase2Solution << "\n";
        
        //  output efficient rotations
        std::cout << "\nSolution With Optimal Rotations " << convertTo4Arm(phase1Solution + phase2Solution) << "\n";
    }

    
}