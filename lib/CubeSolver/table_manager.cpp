#include "table_manager.h"

#include <filesystem>

void TableManager::generateTables() {
    this->generatePhase1MoveTables();
    this->generatePhase1PruningTables();
    this->generatePhase2MoveTables();
    this->generatePhase2PruningTables();
}

void TableManager::generatePhase1EdgeMoveTable(StickerCube* cube, int coord, int depth) {
    if (this->phase1EdgeMoveTable[coord][0] == -1) {
        for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {
            cube->applyMove(CubeConstants::PHASE_1_MOVES[move]);
            int newCoord = cube->getPhase1EdgeCoordinate();
            phase1EdgeMoveTable[coord][move] = newCoord;
            generatePhase1EdgeMoveTable(cube, newCoord, depth + 1);
            cube->applyMove(CubeConstants::PHASE_1_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase1CornerMoveTable(StickerCube* cube, int coord, int depth) {
    if (this->phase1CornerMoveTable[coord][0] == -1) {
        for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {
            cube->applyMove(CubeConstants::PHASE_1_MOVES[move]);
            int newCoord = cube->getPhase1CornerCoordinate();
            this->phase1CornerMoveTable[coord][move] = newCoord;
            this->generatePhase1CornerMoveTable(cube, newCoord, depth + 1);
            cube->applyMove(CubeConstants::PHASE_1_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase1UdsliceMoveTable(StickerCube* cube, int coord, int depth) {
    if (this->phase1UdsliceMoveTable[coord][0] == -1) {
        for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {
            cube->applyMove(CubeConstants::PHASE_1_MOVES[move]);
            int newCoord = cube->getPhase1UdsliceCoordinate();
            this->phase1UdsliceMoveTable[coord][move] = newCoord;
            this->generatePhase1UdsliceMoveTable(cube, newCoord, depth + 1);
            cube->applyMove(CubeConstants::PHASE_1_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase2EdgeMoveTable() {
    for (int coord = 0; coord < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; coord++) {
        StickerCube* stickerCube = StickerCube::fromEdgePermutation(coord);
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            stickerCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            this->phase2EdgeMoveTable[coord][move] = stickerCube->getPhase2EdgeCoordinate();
            stickerCube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
        }
        delete stickerCube;
    }
}

void TableManager::generatePhase2CornerMoveTable() {
    for (int coord = 0; coord < CubeConstants::PHASE_2_MAX_CORNER_COORDINATE; coord++) {
        StickerCube* stickerCube = StickerCube::fromCornerPermutation(coord);
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            stickerCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            this->phase2CornerMoveTable[coord][move] = stickerCube->getPhase2CornerCoordinate();
            stickerCube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase2UdsliceMoveTable() {

    for (int coord = 0; coord < CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE; coord++) {
        StickerCube* stickerCube = StickerCube::fromUDSlice(coord);
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            stickerCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            this->phase2UdsliceMoveTable[coord][move] = stickerCube->getPhase2UdsliceCoordinate();
            stickerCube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase2Side1MoveTable() {

    std::queue<int> que;
    std::unordered_map<int, StickerCube*> map;
    StickerCube* stickerCube = new StickerCube();
    map.emplace(stickerCube->getPhase2Side1Coordinate(), stickerCube);
    que.emplace(stickerCube->getPhase2Side1Coordinate());
    int count = 0;
    while(!que.empty()) {
        int coord = que.front();
        count++;
        if(count % 100000 == 0) {
            std::cout<< (count / 3000000.0)*100<<"%\n";
        }
        StickerCube* currCube = map[coord];
        que.pop();
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            currCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            int newCoord = currCube->getPhase2Side1Coordinate();
            if(map.find(newCoord) == map.end()) {
                que.emplace(newCoord);
                map[newCoord] = new StickerCube(currCube->getCubeState());
            }
            this->phase2Side1MoveTable[coord][move] = newCoord;
            currCube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase2Side2MoveTable() {

    std::queue<int> que;
    std::unordered_map<int, StickerCube*> map;
    StickerCube* stickerCube = new StickerCube();
    map.emplace(stickerCube->getPhase2Side2Coordinate(), stickerCube);
    que.emplace(stickerCube->getPhase2Side2Coordinate());
    int count = 0;
    while(!que.empty()) {
        int coord = que.front();
        count++;
        if(count % 100000 == 0) {
            std::cout<< (count / 3000000.0)*100<<"%\n";
        }
        StickerCube* currCube = map[coord];
        que.pop();
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            currCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            int newCoord = currCube->getPhase2Side2Coordinate();
            if(map.find(newCoord) == map.end()) {
                que.emplace(newCoord);
                map[newCoord] = new StickerCube(currCube->getCubeState());
            }
            this->phase2Side2MoveTable[coord][move] = newCoord;
            currCube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase1MoveTables() {

    //  Allocate memory for tables
    this->phase1EdgeMoveTable = new int*[CubeConstants::PHASE_1_MAX_EDGE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_EDGE_COORDINATE; i++) {
        this->phase1EdgeMoveTable[i] = new int[CubeConstants::PHASE_1_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            this->phase1EdgeMoveTable[i][a] = -1;
        }
    }
    this->phase1CornerMoveTable = new int*[CubeConstants::PHASE_1_MAX_CORNER_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_CORNER_COORDINATE; i++) {
        this->phase1CornerMoveTable[i] = new int[CubeConstants::PHASE_1_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            this->phase1CornerMoveTable[i][a] = -1;
        }
    }
    this->phase1UdsliceMoveTable = new int*[CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE; i++) {
        this->phase1UdsliceMoveTable[i] = new int[CubeConstants::PHASE_1_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            this->phase1UdsliceMoveTable[i][a] = -1;
        }
    }

    //  Generate move tables using DFS
    StickerCube* solvedCube = new StickerCube();
    this->generatePhase1UdsliceMoveTable(solvedCube, 0, 0);
    this->generatePhase1EdgeMoveTable(solvedCube, 0, 0);
    this->generatePhase1CornerMoveTable(solvedCube, 0, 0);
}

void TableManager::generatePhase2MoveTables() {

    this->phase2EdgeMoveTable = new int*[CubeConstants::PHASE_2_MAX_EDGE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; i++) {
        this->phase2EdgeMoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2EdgeMoveTable[i][a] = -1;
        }
    }
    this->phase2CornerMoveTable = new int*[CubeConstants::PHASE_2_MAX_CORNER_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_CORNER_COORDINATE; i++) {
        this->phase2CornerMoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2CornerMoveTable[i][a] = -1;
        }
    }
    this->phase2UdsliceMoveTable = new int*[CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE; i++) {
        this->phase2UdsliceMoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT] ;
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2UdsliceMoveTable[i][a] = -1;
        }
    }
    this->phase2Side1MoveTable = new int*[CubeConstants::PHASE_2_MAX_SIDE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        this->phase2Side1MoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2Side1MoveTable[i][a] = -1;
        }
    }
    this->phase2Side2MoveTable = new int*[CubeConstants::PHASE_2_MAX_SIDE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        this->phase2Side2MoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2Side2MoveTable[i][a] = -1;
        }
    }

    this->generatePhase2EdgeMoveTable();
    this->generatePhase2CornerMoveTable();
    this->generatePhase2UdsliceMoveTable();

    std::cout<<"Starting side 1 move table\n";
    this->generatePhase2Side1MoveTable();
    std::cout<<"Starting side 2 move table\n";
    this->generatePhase2Side2MoveTable();
}

void TableManager::generatePhase1EdgePruningTable() {

    this->phase1EdgePruningTable = new int[CubeConstants::PHASE_1_MAX_EDGE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_EDGE_COORDINATE; i++) {
        this->phase1EdgePruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 0));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase1EdgePruningTable[curr->value] == -1) {
            this->phase1EdgePruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {
                int coord = this->phase1EdgeMoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase1CornerPruningTable() {

    this->phase1CornerPruningTable = new int[CubeConstants::PHASE_1_MAX_CORNER_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_CORNER_COORDINATE; i++) {
        this->phase1CornerPruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 0));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase1CornerPruningTable[curr->value] == -1) {
            this->phase1CornerPruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {
                int coord = this->phase1CornerMoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase1UDSlicePruningTable() {

    this->phase1UdslicePruningTable = new int[CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE; i++) {
        this->phase1UdslicePruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 0));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase1UdslicePruningTable[curr->value] == -1) {
            this->phase1UdslicePruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {
                int coord = this->phase1UdsliceMoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase2EdgePruningTable() {

    this->phase2EdgePruningTable = new int[CubeConstants::PHASE_2_MAX_EDGE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; i++) {
        this->phase2EdgePruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 0));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2EdgePruningTable[curr->value] == -1) {
            this->phase2EdgePruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2EdgeMoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase2CornerPruningTable() {

    this->phase2CornerPruningTable = new int[CubeConstants::PHASE_2_MAX_CORNER_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_CORNER_COORDINATE; i++) {
        this->phase2CornerPruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 0));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2CornerPruningTable[curr->value] == -1) {
            this->phase2CornerPruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2CornerMoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase2UDSlicePruningTable() {

    this->phase2UdslicePruningTable = new int[CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE; i++) {
        this->phase2UdslicePruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 0));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2UdslicePruningTable[curr->value] == -1) {
            this->phase2UdslicePruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2UdsliceMoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase2Side1PruningTable() {
    this->phase2Side1PruningTable = new int[CubeConstants::PHASE_2_MAX_SIDE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        this->phase2Side1PruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 1882720));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2Side1PruningTable[curr->value] == -1) {
            this->phase2Side1PruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2Side1MoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase2Side2PruningTable() {
    this->phase2Side2PruningTable = new int[CubeConstants::PHASE_2_MAX_SIDE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        this->phase2Side2PruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 115989));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2Side2PruningTable[curr->value] == -1) {
            this->phase2Side2PruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2Side2MoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase1PruningTables() {
    this->generatePhase1EdgePruningTable();
    this->generatePhase1CornerPruningTable();
    this->generatePhase1UDSlicePruningTable();
}

void TableManager::generatePhase2PruningTables() {
    this->generatePhase2EdgePruningTable();
    this->generatePhase2CornerPruningTable();
    this->generatePhase2UDSlicePruningTable();

    std::cout<<"Starting side 1 prunning table\n";
    this->generatePhase2Side1PruningTable();
    std::cout<<"Starting side 2 prunning table\n";
    this->generatePhase2Side2PruningTable();
}

void TableManager::writeTablesToFile() {
    std::filesystem::path tablesDir("tables");
    if (!std::filesystem::exists(tablesDir)) {
        std::cout << "Creating tables directory\n";
        std::filesystem::create_directories(tablesDir);
    }

    this->writeMoveTablesToFile();
    this->writePruningTablesToFile();
}

void TableManager::readTablesFromFile() {

    this->readMoveTablesFromFile();
    this->readPruningTablesFromFile();
}

void TableManager::writeMoveTablesToFile() {

    //  write phase1EdgeMoveTable to file
    writeMoveTableToFile("tables/Phase1EdgeMoveTable.txt", this->phase1EdgeMoveTable, CubeConstants::PHASE_1_MAX_EDGE_COORDINATE, CubeConstants::PHASE_1_MOVE_COUNT);

    //  write phase1CornerMoveTable to file
    writeMoveTableToFile("tables/Phase1CornerMoveTable.txt", this->phase1CornerMoveTable, CubeConstants::PHASE_1_MAX_CORNER_COORDINATE, CubeConstants::PHASE_1_MOVE_COUNT);

    //  write phase1UdsliceMoveTable to file
    writeMoveTableToFile("tables/Phase1UdsliceMoveTable.txt", this->phase1UdsliceMoveTable, CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE, CubeConstants::PHASE_1_MOVE_COUNT);

    //  write phase2EdgeMoveTable to file
    writeMoveTableToFile("tables/Phase2EdgeMoveTable.txt", this->phase2EdgeMoveTable, CubeConstants::PHASE_2_MAX_EDGE_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);

    //  write phase1CornerMoveTable to file
    writeMoveTableToFile("tables/Phase2CornerMoveTable.txt", this->phase2CornerMoveTable, CubeConstants::PHASE_2_MAX_CORNER_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);

    //  write phase1UdsliceMoveTable to file
    writeMoveTableToFile("tables/Phase2UdsliceMoveTable.txt", this->phase2UdsliceMoveTable, CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);

    //  write phase2Side1MoveTable to file
    writeMoveTableToFile("tables/Phase2Side1MoveTable.txt", this->phase2Side1MoveTable, CubeConstants::PHASE_2_MAX_SIDE_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);

    //  write phase2Side2MoveTable to file
    writeMoveTableToFile("tables/Phase2Side2MoveTable.txt", this->phase2Side2MoveTable, CubeConstants::PHASE_2_MAX_SIDE_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);
}

void TableManager::writeMoveTableToFile(std::string fileName, int** moveTable, int size, int moveCount) {
    std::cout << "Writing move table to file: " << fileName << "\n";
    //  write move table to file
    std::ofstream moveTableFile(fileName);
    for (int i = 0; i < size; i++) {
        for (int a = 0; a < moveCount; a++) {
            moveTableFile << moveTable[i][a] << "\n";
        }
    }
    moveTableFile.close();
}

void TableManager::writePruningTablesToFile() {
    
    //  write phase1EdgePrunningTable to file
    writePruningTableToFile("tables/Phase1EdgePruningTable.txt", this->phase1EdgePruningTable, CubeConstants::PHASE_1_MAX_EDGE_COORDINATE);

    //  write phase1CornerPrunningTable to file
    writePruningTableToFile("tables/Phase1CornerPruningTable.txt", this->phase1CornerPruningTable, CubeConstants::PHASE_1_MAX_CORNER_COORDINATE);

    //  write phase1UdslicePrunningTable to file
    writePruningTableToFile("tables/Phase1UdslicePruningTable.txt", this->phase1UdslicePruningTable, CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE);

    //  write phase2EdgePrunningTable to file
    writePruningTableToFile("tables/Phase2EdgePruningTable.txt", this->phase2EdgePruningTable, CubeConstants::PHASE_2_MAX_EDGE_COORDINATE);

    //  write phase2CornerPrunningTable to file
    writePruningTableToFile("tables/Phase2CornerPruningTable.txt", this->phase2CornerPruningTable, CubeConstants::PHASE_2_MAX_CORNER_COORDINATE);

    //  write phase2UdslicePrunningTable to file
    writePruningTableToFile("tables/Phase2UdslicePruningTable.txt", this->phase2UdslicePruningTable, CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE);

    //  write side 1 prunning table to file
    writePruningTableToFile("tables/Side1PruningTable.txt", this->phase2Side1PruningTable, CubeConstants::PHASE_2_MAX_SIDE_COORDINATE);

    //  write side 2 prunning table to file
    writePruningTableToFile("tables/Side2PruningTable.txt", this->phase2Side2PruningTable, CubeConstants::PHASE_2_MAX_SIDE_COORDINATE);
}

void TableManager::writePruningTableToFile(std::string fileName, int* pruningTable, int size) {
    //  write prunning table to file
    std::ofstream pruningTableFile(fileName);
    for (int i = 0; i < size; i++) {
        pruningTableFile << pruningTable[i] << "\n";
    }
    pruningTableFile.close();
}

void TableManager::readMoveTablesFromFile() {

    //  read phase1EdgeMoveTable from file
    readMoveTableFromFile("tables/Phase1EdgeMoveTable.txt", &this->phase1EdgeMoveTable, CubeConstants::PHASE_1_MAX_EDGE_COORDINATE, CubeConstants::PHASE_1_MOVE_COUNT);

    //  read phase1CornerMoveTable from file
    readMoveTableFromFile("tables/Phase1CornerMoveTable.txt", &this->phase1CornerMoveTable, CubeConstants::PHASE_1_MAX_CORNER_COORDINATE, CubeConstants::PHASE_1_MOVE_COUNT);

    //  read phase1UdsliceMoveTable from file
    readMoveTableFromFile("tables/Phase1UdsliceMoveTable.txt", &this->phase1UdsliceMoveTable, CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE, CubeConstants::PHASE_1_MOVE_COUNT);

    //  read phase2EdgeMoveTable from file
    readMoveTableFromFile("tables/Phase2EdgeMoveTable.txt", &this->phase2EdgeMoveTable, CubeConstants::PHASE_2_MAX_EDGE_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);

    //  read phase2CornerMoveTable from file
    readMoveTableFromFile("tables/Phase2CornerMoveTable.txt", &this->phase2CornerMoveTable, CubeConstants::PHASE_2_MAX_CORNER_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);

    //  read phase2UdsliceMoveTable from file
    readMoveTableFromFile("tables/Phase2UdsliceMoveTable.txt", &this->phase2UdsliceMoveTable, CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);

    //  read phase2Side1MoveTable from file
    readMoveTableFromFile("tables/Phase2Side1MoveTable.txt", &this->phase2Side1MoveTable, CubeConstants::PHASE_2_MAX_SIDE_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);

    //  read phase2Side2MoveTable from file
    readMoveTableFromFile("tables/Phase2Side2MoveTable.txt", &this->phase2Side2MoveTable, CubeConstants::PHASE_2_MAX_SIDE_COORDINATE, CubeConstants::PHASE_2_MOVE_COUNT);
}

void TableManager::readMoveTableFromFile(std::string fileName, int*** moveTable, int size, int moveCount) {

    //  read move table from file
    std::string line;
    std::ifstream moveTableFile(fileName);
    *moveTable = new int*[size];
    for (int i = 0; i < size; i++) {
        (*moveTable)[i] = new int[moveCount];
        for (int a = 0; a < moveCount; a++) {
            std::getline(moveTableFile, line);
            (*moveTable)[i][a] = std::stoi(line);
        }
    }
    moveTableFile.close();
}

void TableManager::readPruningTablesFromFile() {

    //  read phase1EdgePruningTable from file
    this->readPruningTableFromFile("tables/Phase1EdgePruningTable.txt", &this->phase1EdgePruningTable, CubeConstants::PHASE_1_MAX_EDGE_COORDINATE);

    //  read phase1CornerPruningTable from file
    this->readPruningTableFromFile("tables/Phase1CornerPruningTable.txt", &this->phase1CornerPruningTable, CubeConstants::PHASE_1_MAX_CORNER_COORDINATE);

    //  read phase1CornerPruningTable from file
    this->readPruningTableFromFile("tables/Phase1UdslicePruningTable.txt", &this->phase1UdslicePruningTable, CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE);

    //  read phase2EdgePruningTable from file
    this->readPruningTableFromFile("tables/Phase2EdgePruningTable.txt", &this->phase2EdgePruningTable, CubeConstants::PHASE_2_MAX_EDGE_COORDINATE);
    
    //  read phase2CornerPruningTable from file
    this->readPruningTableFromFile("tables/Phase2CornerPruningTable.txt", &this->phase2CornerPruningTable, CubeConstants::PHASE_2_MAX_CORNER_COORDINATE);
    
    //  read phase2UdslicePruningTable from file
    this->readPruningTableFromFile("tables/Phase2UdslicePruningTable.txt", &this->phase2UdslicePruningTable, CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE);
    
    //  read side 1 prunning table from file
    this->readPruningTableFromFile("tables/Side1PruningTable.txt", &this->phase2Side1PruningTable, CubeConstants::PHASE_2_MAX_SIDE_COORDINATE);
    
    //  read side 2 prunning table from file
    this->readPruningTableFromFile("tables/Side2PruningTable.txt", &this->phase2Side2PruningTable, CubeConstants::PHASE_2_MAX_SIDE_COORDINATE);
}

void TableManager::readPruningTableFromFile(std::string fileName, int** pruningTable, int size) {

    //  read prunning table from file
    std::string line;
    std::ifstream pruningTableFile(fileName);
    *pruningTable = new int[size];
    for (int i = 0; i < size; i++) {
        std::getline(pruningTableFile, line);
        (*pruningTable)[i] = std::stoi(line);
    }
    pruningTableFile.close();
}