#include <iostream>
#include <sstream>
#include "TableManager.h"
#include "CubeSearch.h"

int main() {

    //  Display welcome message
    std::cout << "Starting CubeSolver 2...\n";

    //  Create look up tables to enable very fast searching of the state graph
    std::cout << "Generating lookup tables...\n";
    TableManager* tableManager = TableManager::getInstance();

    //  Get scramble from user
    std::cout << "Please enter a scramble (standard notation separated via spaces): ";
    std::string scramble;
    std::getline(std::cin, scramble);

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