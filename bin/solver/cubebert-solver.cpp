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

    //  Create look up tables to enable very fast searching of the state graph
    std::cout << "Generating lookup tables...\n\n";
    TableManager* tableManager = TableManager::getInstance();
    std::cout<<"generation complete\n";

    while(true) {
        //  Get scramble from user
        std::cout << "Please enter a scramble (standard notation separated via spaces): ";
        std::string scramble;
        std::getline(std::cin, scramble);

        //  Apply scramble to clean cube
        StickerCube* scrambleCube = new StickerCube(scramble);
        StickerCube* scrambleCubeF = new StickerCube(scramble);

        //  solve phase 1
        std::cout << "\nStarting phase 1...\n";
        std::string phase1Solution = CubeSearch::getPhase1Solution(scrambleCube);

        //  apply phase 1  solution to scrambled cube
        scrambleCube->applyScramble(phase1Solution);
        scrambleCubeF->applyScramble(phase1Solution);


        // //  solve phase 2
        // std::cout << "Starting phase 2...\n";
        // auto start = high_resolution_clock::now();
        // std::string phase2Solution = CubeSearch::getPhase2Solution(scrambleCube);
        // auto stop = high_resolution_clock::now();
        // auto duration = duration_cast<microseconds>(stop - start);
        // std::cout << "Time taken by function: "<< duration.count() << " microseconds\n";

        //  solve phase 2
        std::cout << "Starting phase 2F...\n";
        auto start = high_resolution_clock::now();
        std::string phase2Solution = CubeSearch::getPhase2SolutionF(scrambleCubeF);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << "Time taken by functionF: "<< duration.count() << " microseconds\n";

        //  output complete solution
        std::cout << "Solution " << phase1Solution << phase2Solution << "\n";
        
        //  output efficient rotations
        std::cout << "\nSolution With Optimal Rotations " << convertTo4Arm(phase1Solution + phase2Solution) << "\n";
    }

    
}