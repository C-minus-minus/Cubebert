#include "cubebert.h"

#include "algorithm_optimiser.h"
#include "process_cube.h"
#include "sticker_cube.h"

#include <iostream>

Cubebert::Cubebert() {
    m_logger = Logger::instance();

    m_logger->info().message("Initializing Cubebert");

    m_logger->info().message("Initializing Firmware");
    m_fipc = new FIPC();
    m_fipc->home();

    m_logger->info().message("Initializing TableManager");
    m_tableManager = new TableManager();

    m_logger->info().message("Populating lookup tables");
    m_tableManager->readTablesFromFile();

    m_logger->info().message("Initializing CubeSearch");
    m_cubeSearch = new CubeSearch(m_tableManager);

    m_logger->info().message("Initializing ProcessCube");
    m_processCube = new ProcessCube();
}

Cubebert::~Cubebert() {
    delete m_fipc;
    delete m_tableManager;
    delete m_processCube;
}

void Cubebert::solve() {
    m_logger->info().message("Starting Solver");
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
    
    m_logger->info().message("Starting Phase 1");
    std::string phase1Solution = m_cubeSearch->getPhase1Solution(scrambleCube);
    scrambleCube->applyScramble(phase1Solution);

    m_logger->info().message("Starting Phase 2");
    std::string phase2Solution = m_cubeSearch->getPhase2Solution(scrambleCube);

    m_logger->info().message("Solution: " + phase1Solution + phase2Solution);

    std::string optimalRotations = convertTo4Arm(phase1Solution + phase2Solution);
    m_logger->info().message("Solution for Bot: " + optimalRotations);

    m_fipc->rotate(phase1Solution + phase2Solution);
}

int main(int argc, char* argv[]) {
    Cubebert cubebert;

    cubebert.solve();
}
