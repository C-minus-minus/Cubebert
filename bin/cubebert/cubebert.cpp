#include "cubebert.h"

#include "algorithm_optimiser.h"
#include "process_cube.h"
#include "sticker_cube.h"

#include <iostream>

Cubebert::Cubebert() {
    std::cout << "Initializing Cubebert\n";

    std::cout << "Initializing Firmware\n";
    m_fipc = new FIPC();
    m_fipc->home();

    std::cout << "Initializing TableManager\n";
    m_tableManager = new TableManager();
    m_tableManager->readTablesFromFile();

    m_cubeSearch = new CubeSearch(m_tableManager);

    std::cout << "Initializing ProcessCube\n";
    m_processCube = new ProcessCube();
}

Cubebert::~Cubebert() {
    delete m_fipc;
    delete m_tableManager;
    delete m_processCube;
}

void Cubebert::solve() {
    std::cout << "Starting Snapping\n";
    m_processCube->captureSide(0);
    m_fipc->rotate("X");
    m_processCube->captureSide(1);
    m_fipc->rotate("X");
    m_processCube->captureSide(2);
    m_fipc->rotate("X");
    m_processCube->captureSide(3);
    m_fipc->rotate("X Z");
    m_processCube->captureSide(4);
    m_fipc->rotate("Z2");
    m_processCube->captureSide(5);
    m_fipc->rotate("Z");

    int **zeCube = m_processCube->zeCube();

    StickerCube *scrambleCube = new StickerCube(zeCube);
    
    std::cout << "\nStarting phase 1...\n";
    std::string phase1Solution = m_cubeSearch->getPhase1Solution(scrambleCube);
    scrambleCube->applyScramble(phase1Solution);

    std::cout << "Starting phase 2...\n";
    std::string phase2Solution = m_cubeSearch->getPhase2Solution(scrambleCube);

    std::cout << "Solution: " << phase1Solution << phase2Solution << "\n";

    std::string optimalRotations = convertTo4Arm(phase1Solution + phase2Solution);
    std::cout << "Solution for Bot: " << optimalRotations << "\n";

    m_fipc->rotate(phase1Solution + phase2Solution);
}

int main(int argc, char* argv[]) {
    Cubebert cubebert;

    cubebert.solve();
}
