#include "TableManager.h"

TableManager* TableManager::instance = NULL;

TableManager::TableManager() {

    this->generatePhase1MoveTables();
    this->generatePhase1PruningTables();
    this->generatePhase2MoveTables();
    std::cout << "boom";
    this->generatePhase2PruningTables();
    std::cout << "pow";
}

TableManager* TableManager::getInstance() {
    if (TableManager::instance == NULL) {
        TableManager::instance = new TableManager();
    }
    return TableManager::instance;
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

    ////  populate tables with -1 to start
    //int** tables[] = {this->phase1EdgeMoveTable, this->phase1CornerMoveTable, this->phase1UdsliceMoveTable};
    //const int maxCoordinateLength = 3;
    //const int maxCoordinate[] = {
    //        CubeConstants::PHASE_1_MAX_EDGE_COORDINATE,
    //        CubeConstants::PHASE_1_MAX_CORNER_COORDINATE,
    //        CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE
    //};
    //for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {
    //    for (int table = 0; table < maxCoordinateLength; table++) {
    //        for (int coord = 0; coord < maxCoordinate[table]; coord++) {
    //            tables[table][coord][move] = -1;
    //        }
    //    }
    //}
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
    
    /*
    for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
        int** tables[] = {this->phase2EdgeMoveTable, this->phase2CornerMoveTable, this->phase2UdsliceMoveTable};
        const int maxCoordinateSize = 3;
        int maxCoordinate[] = {
                CubeConstants::PHASE_2_MAX_EDGE_COORDINATE,
                CubeConstants::PHASE_2_MAX_CORNER_COORDINATE,
                CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE
        };
        for (int table = 0; table < maxCoordinateSize; table++) {
            for (int coord = 0; coord < maxCoordinate[table]; coord++) {
                tables[table][coord][move] = -1;
            }
        }
    }*/

    std::cout << "zero";
    this->generatePhase2EdgeMoveTable();
    std::cout << "uno";
    this->generatePhase2CornerMoveTable();
    std::cout << "dos";
    this->generatePhase2UdsliceMoveTable();
    std::cout << "tress";
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

void TableManager::generatePhase1PruningTables() {
    this->generatePhase1EdgePruningTable();
    this->generatePhase1CornerPruningTable();
    this->generatePhase1UDSlicePruningTable();
}

void TableManager::generatePhase2PruningTables() {
    std::cout << "meowwerwer";
    this->generatePhase2EdgePruningTable();
    std::cout << "Moo";
    this->generatePhase2CornerPruningTable();
    std::cout << "spine";
    this->generatePhase2UDSlicePruningTable();
    std::cout << "book";
}