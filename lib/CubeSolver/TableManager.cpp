#include "TableManager.h"

//  FILE FLAGS
const bool TableManager::WRITE_TABLES_TO_FILE = false;
const bool TableManager::READ_TABLES_FROM_FILE = false;

TableManager* TableManager::instance = NULL;

TableManager::TableManager() {

    if(READ_TABLES_FROM_FILE) {
        this->readTablesFromFile();
    } else {
        this->generatePhase1MoveTables();
        this->generatePhase1PruningTables();
        this->generatePhase2MoveTables();
        this->generatePhase2PruningTables();
        if(WRITE_TABLES_TO_FILE) {
            this->writeTablesToFile();
        }
    }
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

void TableManager::generatePhase2Bar1MoveTable(StickerCube* cube, int coord, int depth) {
    // if (this->phase2Bar1MoveTable[coord][0] == -1) {
    //     for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
    //         cube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
    //         int newCoord = cube->getPhase2Bar1Coordinate();
    //         this->phase2Bar1MoveTable[coord][move] = newCoord;
    //         this->generatePhase2Bar1MoveTable(cube, newCoord, depth + 1);
    //         cube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
    //     }
    // }
    // this->phase1EdgePruningTable = new int[CubeConstants::PHASE_1_MAX_EDGE_COORDINATE];
    // for (int i = 0; i < CubeConstants::PHASE_1_MAX_EDGE_COORDINATE; i++) {
    //     this->phase1EdgePruningTable[i] = -1;
    // }

    // std::queue<SearchNode*> que;
    // que.emplace(new SearchNode(0, 0));
    // while (!que.empty()) {
    //     SearchNode* curr = que.front();
    //     que.pop();
    //     if (this->phase1EdgePruningTable[curr->value] == -1) {
    //         this->phase1EdgePruningTable[curr->value] = curr->depth;
    //         for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {
    //             int coord = this->phase1EdgeMoveTable[curr->value][move];
    //             que.emplace(new SearchNode(curr->depth + 1, coord));
    //         }
    //     }
    // }

    std::queue<int> que;
    std::unordered_map<int, StickerCube*> map;
    map.emplace(coord, new StickerCube(cube->getCubeState()));
    que.emplace(coord);
    while(!que.empty()) {
        coord = que.front();
        StickerCube* currCube = map[coord];
        que.pop();
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            currCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            int newCoord = currCube->getPhase2Bar1Coordinate();
            if(map.find(newCoord) == map.end()) {
                que.emplace(newCoord);
                map[newCoord] = new StickerCube(currCube->getCubeState());
            }
            this->phase2Bar1MoveTable[coord][move] = newCoord;
            currCube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
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

void TableManager::generatePhase2Bar2MoveTable(StickerCube* cube, int coord, int depth) {
    // if (this->phase2Bar2MoveTable[coord][0] == -1) {
    //     for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
    //         cube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
    //         int newCoord = cube->getPhase2Bar2Coordinate();
    //         this->phase2Bar2MoveTable[coord][move] = newCoord;
    //         this->generatePhase2Bar2MoveTable(cube, newCoord, depth + 1);
    //         cube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
    //     }
    // }
    std::queue<int> que;
    std::unordered_map<int, StickerCube*> map;
    map.emplace(coord, new StickerCube(cube->getCubeState()));
    que.emplace(coord);
    while(!que.empty()) {
        coord = que.front();
        StickerCube* currCube = map[coord];
        que.pop();
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            currCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            int newCoord = currCube->getPhase2Bar2Coordinate();
            if(map.find(newCoord) == map.end()) {
                que.emplace(newCoord);
                map[newCoord] = new StickerCube(currCube->getCubeState());
            }
            this->phase2Bar2MoveTable[coord][move] = newCoord;
            currCube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase2Bar3MoveTable(StickerCube* cube, int coord, int depth) {
    // if (this->phase2Bar3MoveTable[coord][0] == -1) {
    //     for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
    //         cube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
    //         int newCoord = cube->getPhase2Bar3Coordinate();
    //         this->phase2Bar3MoveTable[coord][move] = newCoord;
    //         this->generatePhase2Bar3MoveTable(cube, newCoord, depth + 1);
    //         cube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
    //     }
    // }
    std::queue<int> que;
    std::unordered_map<int, StickerCube*> map;
    map.emplace(coord, new StickerCube(cube->getCubeState()));
    que.emplace(coord);
    while(!que.empty()) {
        coord = que.front();
        StickerCube* currCube = map[coord];
        que.pop();
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            currCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            int newCoord = currCube->getPhase2Bar3Coordinate();
            if(map.find(newCoord) == map.end()) {
                que.emplace(newCoord);
                map[newCoord] = new StickerCube(currCube->getCubeState());
            }
            this->phase2Bar3MoveTable[coord][move] = newCoord;
            currCube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
        }
    }
}

void TableManager::generatePhase2Bar4MoveTable(StickerCube* cube, int coord, int depth) {
    // if (this->phase2Bar4MoveTable[coord][0] == -1) {
    //     for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
    //         cube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
    //         int newCoord = cube->getPhase2Bar4Coordinate();
    //         this->phase2Bar4MoveTable[coord][move] = newCoord;
    //         this->generatePhase2Bar4MoveTable(cube, newCoord, depth + 1);
    //         cube->applyMove(CubeConstants::PHASE_2_ANTIMOVES[move]);
    //     }
    // }
    std::queue<int> que;
    std::unordered_map<int, StickerCube*> map;
    map.emplace(coord, new StickerCube(cube->getCubeState()));
    que.emplace(coord);
    while(!que.empty()) {
        coord = que.front();
        StickerCube* currCube = map[coord];
        que.pop();
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
            currCube->applyMove(CubeConstants::PHASE_2_MOVES[move]);
            int newCoord = currCube->getPhase2Bar4Coordinate();
            if(map.find(newCoord) == map.end()) {
                que.emplace(newCoord);
                map[newCoord] = new StickerCube(currCube->getCubeState());
            }
            this->phase2Bar4MoveTable[coord][move] = newCoord;
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

    this->phase2Bar1MoveTable = new int*[CubeConstants::PHASE_2_MAX_BAR1_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
        this->phase2Bar1MoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2Bar1MoveTable[i][a] = -1;
        }
    }

    this->phase2Bar2MoveTable = new int*[CubeConstants::PHASE_2_MAX_BAR1_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
        this->phase2Bar2MoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2Bar2MoveTable[i][a] = -1;
        }
    }

    this->phase2Bar3MoveTable = new int*[CubeConstants::PHASE_2_MAX_BAR1_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
        this->phase2Bar3MoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2Bar3MoveTable[i][a] = -1;
        }
    }

    this->phase2Bar4MoveTable = new int*[CubeConstants::PHASE_2_MAX_BAR1_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
        this->phase2Bar4MoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            this->phase2Bar4MoveTable[i][a] = -1;
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

    this->generatePhase2EdgeMoveTable();
    this->generatePhase2CornerMoveTable();
    this->generatePhase2UdsliceMoveTable();
    StickerCube* solvedCube = new StickerCube();
    this->generatePhase2Bar1MoveTable(solvedCube, solvedCube->getPhase2Bar1Coordinate(), 0);
    this->generatePhase2Bar2MoveTable(solvedCube, solvedCube->getPhase2Bar2Coordinate(), 0);
    this->generatePhase2Bar3MoveTable(solvedCube, solvedCube->getPhase2Bar3Coordinate(), 0);
    this->generatePhase2Bar4MoveTable(solvedCube, solvedCube->getPhase2Bar4Coordinate(), 0);

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

void TableManager::generatePhase2Bar1PruningTable() {
    
    this->phase2Bar1PruningTable = new int[CubeConstants::PHASE_2_MAX_BAR1_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
        this->phase2Bar1PruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 9127));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2Bar1PruningTable[curr->value] == -1) {
            this->phase2Bar1PruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2Bar1MoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase2Bar2PruningTable() {
    
    this->phase2Bar2PruningTable = new int[CubeConstants::PHASE_2_MAX_BAR1_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
        this->phase2Bar2PruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 7669));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2Bar2PruningTable[curr->value] == -1) {
            this->phase2Bar2PruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2Bar2MoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase2Bar3PruningTable() {
    
    this->phase2Bar3PruningTable = new int[CubeConstants::PHASE_2_MAX_BAR1_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
        this->phase2Bar3PruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 4389));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2Bar3PruningTable[curr->value] == -1) {
            this->phase2Bar3PruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2Bar3MoveTable[curr->value][move];
                que.emplace(new SearchNode(curr->depth + 1, coord));
            }
        }
    }
}

void TableManager::generatePhase2Bar4PruningTable() {
    
    this->phase2Bar4PruningTable = new int[CubeConstants::PHASE_2_MAX_BAR1_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_BAR1_COORDINATE; i++) {
        this->phase2Bar4PruningTable[i] = -1;
    }

    std::queue<SearchNode*> que;
    que.emplace(new SearchNode(0, 225));
    while (!que.empty()) {
        SearchNode* curr = que.front();
        que.pop();
        if (this->phase2Bar4PruningTable[curr->value] == -1) {
            this->phase2Bar4PruningTable[curr->value] = curr->depth;
            for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {
                int coord = this->phase2Bar4MoveTable[curr->value][move];
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
    // this->generatePhase2Bar1PruningTable();
    // this->generatePhase2Bar2PruningTable();
    // this->generatePhase2Bar3PruningTable();
    // this->generatePhase2Bar4PruningTable();

    std::cout<<"Starting side 1 prunning table\n";
    this->generatePhase2Side1PruningTable();
    std::cout<<"Starting side 2 prunning table\n";
    this->generatePhase2Side2PruningTable();
}

void TableManager::writeTablesToFile() {

    this->writePhase1MoveTablesToFile();
    this->writePhase2MoveTablesToFile();
    this->writePhase1PruningTablesToFile();
    this->writePhase2PruningTablesToFile();
}

void TableManager::readTablesFromFile() {

    this->readPhase1MoveTablesFromFile();
    this->readPhase2MoveTablesFromFile();
    this->readPhase1PruningTablesFromFile();
    this->readPhase2PruningTablesFromFile();
}

void TableManager::writePhase1MoveTablesToFile() {

    //  write phase1EdgeMoveTable to file
    std::ofstream phase1EdgeMoveTableFile("tables/Phase1EdgeMoveTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_EDGE_COORDINATE; i++) {
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            phase1EdgeMoveTableFile << phase1EdgeMoveTable[i][a] << "\n";
        }
    }
    phase1EdgeMoveTableFile.close();

    //  write phase1CornerMoveTable to file
    std::ofstream phase1CornerMoveTableFile("tables/Phase1CornerMoveTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_CORNER_COORDINATE; i++) {
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            phase1CornerMoveTableFile << phase1CornerMoveTable[i][a] << "\n";
        }
    }
    phase1CornerMoveTableFile.close();

    //  write phase1UdsliceMoveTable to file
    std::ofstream phase1UdsliceMoveTableFile("tables/Phase1UdsliceMoveTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE; i++) {
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            phase1UdsliceMoveTableFile << phase1UdsliceMoveTable[i][a] << "\n";
        }
    }
    phase1UdsliceMoveTableFile.close();
}

void TableManager::writePhase2MoveTablesToFile() {

    //  write phase2EdgeMoveTable to file
    std::ofstream phase2EdgeMoveTableFile("tables/Phase2EdgeMoveTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; i++) {
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            phase2EdgeMoveTableFile << phase2EdgeMoveTable[i][a] << "\n";
        }
    }
    phase2EdgeMoveTableFile.close();

    //  write phase1CornerMoveTable to file
    std::ofstream phase2CornerMoveTableFile("tables/Phase2CornerMoveTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_CORNER_COORDINATE; i++) {
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            phase2CornerMoveTableFile << phase2CornerMoveTable[i][a] << "\n";
        }
    }
    phase2CornerMoveTableFile.close();

    //  write phase1UdsliceMoveTable to file
    std::ofstream phase2UdsliceMoveTableFile("tables/Phase2UdsliceMoveTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE; i++) {
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            phase2UdsliceMoveTableFile << phase2UdsliceMoveTable[i][a] << "\n";
        }
    }
    phase2UdsliceMoveTableFile.close();

    //  write phase2Side1MoveTable to file
    std::ofstream phase2Side1MoveTableFile("tables/Phase2Side1MoveTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            phase2Side1MoveTableFile << phase2Side1MoveTable[i][a] << "\n";
        }
    }
    phase2Side1MoveTableFile.close();

    //  write phase2Side2MoveTable to file
    std::ofstream phase2Side2MoveTableFile("tables/Phase2Side2MoveTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            phase2Side2MoveTableFile << phase2Side2MoveTable[i][a] << "\n";
        }
    }
    phase2Side2MoveTableFile.close();
}

void TableManager::writePhase1PruningTablesToFile() {
    
    //  write phase1EdgePrunningTable to file
    std::ofstream phase1EdgePruningTableFile("tables/Phase1EdgePruningTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_EDGE_COORDINATE; i++) {
        phase1EdgePruningTableFile << phase1EdgePruningTable[i] << "\n";
    }
    phase1EdgePruningTableFile.close();

    //  write phase1CornerPrunningTable to file
    std::ofstream phase1CornerPruningTableFile("tables/Phase1CornerPruningTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_CORNER_COORDINATE; i++) {
        phase1CornerPruningTableFile << phase1CornerPruningTable[i] << "\n";
    }
    phase1CornerPruningTableFile.close();

    //  write phase1UdslicePrunningTable to file
    std::ofstream phase1UdslicePruningTableFile("tables/Phase1UdslicePruningTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE; i++) {
        phase1UdslicePruningTableFile << phase1UdslicePruningTable[i] << "\n";
    }
    phase1UdslicePruningTableFile.close();
}

void TableManager::writePhase2PruningTablesToFile() {

    //  write phase2EdgePrunningTable to file
    std::ofstream phase2EdgePruningTableFile("tables/Phase2EdgePruningTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; i++) {
        phase2EdgePruningTableFile << phase2EdgePruningTable[i] << "\n";
    }
    phase2EdgePruningTableFile.close();

    //  write phase2CornerPrunningTable to file
    std::ofstream phase2CornerPruningTableFile("tables/Phase2CornerPruningTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_CORNER_COORDINATE; i++) {
        phase2CornerPruningTableFile << phase2CornerPruningTable[i] << "\n";
    }
    phase2CornerPruningTableFile.close();

    //  write phase2UdslicePrunningTable to file
    std::ofstream phase2UdslicePruningTableFile("tables/Phase2UdslicePruningTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE; i++) {
        phase2UdslicePruningTableFile << phase2UdslicePruningTable[i] << "\n";
    }
    phase2UdslicePruningTableFile.close();

    //  write side 1 prunning table to file
    std::ofstream side1PruningTableFile("tables/Side1PruningTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        side1PruningTableFile << phase2Side1PruningTable[i] << "\n";
    }
    side1PruningTableFile.close();

    //  write side 2 prunning table to file
    std::ofstream side2PruningTableFile("tables/Side2PruningTable.txt");
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        side2PruningTableFile << phase2Side2PruningTable[i] << "\n";
    }
    side2PruningTableFile.close();
}

void TableManager::readPhase1MoveTablesFromFile() {

    //  read phase1EdgeMoveTable from file
    std::ifstream phase1EdgeMoveTableFile("tables/Phase1EdgeMoveTable.txt");
    std::string line;
    this->phase1EdgeMoveTable = new int*[CubeConstants::PHASE_1_MAX_EDGE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_EDGE_COORDINATE; i++) {
        this->phase1EdgeMoveTable[i] = new int[CubeConstants::PHASE_1_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            std::getline(phase1EdgeMoveTableFile, line);
            this->phase1EdgeMoveTable[i][a] = std::stoi(line);
        }
    }
    phase1EdgeMoveTableFile.close();

    //  read phase1CornerMoveTable from file
    std::ifstream phase1CornerMoveTableFile("tables/Phase1CornerMoveTable.txt");
    this->phase1CornerMoveTable = new int*[CubeConstants::PHASE_1_MAX_CORNER_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_CORNER_COORDINATE; i++) {
        this->phase1CornerMoveTable[i] = new int[CubeConstants::PHASE_1_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            std::getline(phase1CornerMoveTableFile, line);
            this->phase1CornerMoveTable[i][a] = std::stoi(line);
        }
    }
    phase1CornerMoveTableFile.close();

    //  read phase1UdsliceMoveTable from file
    std::ifstream phase1UdsliceMoveTableFile("tables/Phase1UdsliceMoveTable.txt");
    this->phase1UdsliceMoveTable = new int*[CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE; i++) {
        this->phase1UdsliceMoveTable[i] = new int[CubeConstants::PHASE_1_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_1_MOVE_COUNT; a++) {
            std::getline(phase1UdsliceMoveTableFile, line);
            this->phase1UdsliceMoveTable[i][a] = std::stoi(line);
        }
    }
    phase1UdsliceMoveTableFile.close();
}

void TableManager::readPhase2MoveTablesFromFile() {

    //  read phase2EdgeMoveTable from file
    std::ifstream phase2EdgeMoveTableFile("tables/Phase2EdgeMoveTable.txt");
    std::string line;
    this->phase2EdgeMoveTable = new int*[CubeConstants::PHASE_2_MAX_EDGE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; i++) {
        this->phase2EdgeMoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            std::getline(phase2EdgeMoveTableFile, line);
            this->phase2EdgeMoveTable[i][a] = std::stoi(line);
        }
    }
    phase2EdgeMoveTableFile.close();

    //  read phase2CornerMoveTable from file
    std::ifstream phase2CornerMoveTableFile("tables/Phase2CornerMoveTable.txt");
    this->phase2CornerMoveTable = new int*[CubeConstants::PHASE_2_MAX_CORNER_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_CORNER_COORDINATE; i++) {
        this->phase2CornerMoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            std::getline(phase2CornerMoveTableFile, line);
            this->phase2CornerMoveTable[i][a] = std::stoi(line);
        }
    }
    phase2CornerMoveTableFile.close();

    //  read phase2UdsliceMoveTable from file
    std::ifstream phase2UdsliceMoveTableFile("tables/Phase2UdsliceMoveTable.txt");
    this->phase2UdsliceMoveTable = new int*[CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE; i++) {
        this->phase2UdsliceMoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            std::getline(phase2UdsliceMoveTableFile, line);
            this->phase2UdsliceMoveTable[i][a] = std::stoi(line);
        }
    }
    phase2UdsliceMoveTableFile.close();

    //  read phase2Side1MoveTable from file
    std::ifstream phase2Side1MoveTableFile("tables/Phase2Side1MoveTable.txt");
    this->phase2Side1MoveTable = new int*[CubeConstants::PHASE_2_MAX_SIDE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        this->phase2Side1MoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            std::getline(phase2Side1MoveTableFile, line);
            this->phase2Side1MoveTable[i][a] = std::stoi(line);
        }
    }
    phase2Side1MoveTableFile.close();

    //  read phase2Side2MoveTable from file
    std::ifstream phase2Side2MoveTableFile("tables/Phase2Side2MoveTable.txt");
    this->phase2Side2MoveTable = new int*[CubeConstants::PHASE_2_MAX_SIDE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        this->phase2Side2MoveTable[i] = new int[CubeConstants::PHASE_2_MOVE_COUNT];
        for (int a = 0; a < CubeConstants::PHASE_2_MOVE_COUNT; a++) {
            std::getline(phase2Side2MoveTableFile, line);
            this->phase2Side2MoveTable[i][a] = std::stoi(line);
        }
    }
    phase2Side2MoveTableFile.close();
}

void TableManager::readPhase1PruningTablesFromFile() {

    //  read phase1EdgePruningTable from file
    std::ifstream phase1EdgePruningTableFile("tables/Phase1EdgePruningTable.txt");
    std::string line;
    this->phase1EdgePruningTable = new int[CubeConstants::PHASE_1_MAX_EDGE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_EDGE_COORDINATE; i++) {
        std::getline(phase1EdgePruningTableFile, line);
        this->phase1EdgePruningTable[i] = std::stoi(line);
    }
    phase1EdgePruningTableFile.close();

    //  read phase1CornerPruningTable from file
    std::ifstream phase1CornerPruningTableFile("tables/Phase1CornerPruningTable.txt");
    this->phase1CornerPruningTable = new int[CubeConstants::PHASE_1_MAX_CORNER_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_CORNER_COORDINATE; i++) {
        std::getline(phase1CornerPruningTableFile, line);
        this->phase1CornerPruningTable[i] = std::stoi(line);
    }
    phase1CornerPruningTableFile.close();

    //  read phase1UdslicePruningTable from file
    std::ifstream phase1UdslicePruningTableFile("tables/Phase1UdslicePruningTable.txt");
    this->phase1UdslicePruningTable = new int[CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE; i++) {
        std::getline(phase1UdslicePruningTableFile, line);
        this->phase1UdslicePruningTable[i] = std::stoi(line);
    }
    phase1UdslicePruningTableFile.close();
}

void TableManager::readPhase2PruningTablesFromFile() {

    //  read phase2EdgePruningTable from file
    std::ifstream phase2EdgePruningTableFile("tables/Phase2EdgePruningTable.txt");
    std::string line;
    this->phase2EdgePruningTable = new int[CubeConstants::PHASE_2_MAX_EDGE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_EDGE_COORDINATE; i++) {
        std::getline(phase2EdgePruningTableFile, line);
        this->phase2EdgePruningTable[i] = std::stoi(line);
    }
    phase2EdgePruningTableFile.close();

    //  read phase2CornerPruningTable from file
    std::ifstream phase2CornerPruningTableFile("tables/Phase2CornerPruningTable.txt");
    this->phase2CornerPruningTable = new int[CubeConstants::PHASE_2_MAX_CORNER_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_CORNER_COORDINATE; i++) {
        std::getline(phase2CornerPruningTableFile, line);
        this->phase2CornerPruningTable[i] = std::stoi(line);
    }
    phase2CornerPruningTableFile.close();

    //  read phase2UdslicePruningTable from file
    std::ifstream phase2UdslicePruningTableFile("tables/Phase2UdslicePruningTable.txt");
    this->phase2UdslicePruningTable = new int[CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE; i++) {
        std::getline(phase2UdslicePruningTableFile, line);
        this->phase2UdslicePruningTable[i] = std::stoi(line);
    }
    phase2UdslicePruningTableFile.close();

    //  read side 1 prunning table from file
    std::ifstream side1PruningTableFile("tables/Side1PruningTable.txt");
    this->phase2Side1PruningTable = new int[CubeConstants::PHASE_2_MAX_SIDE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        std::getline(side1PruningTableFile, line);
        this->phase2Side1PruningTable[i] = std::stoi(line);
    }
    side1PruningTableFile.close();

    //  read side 2 prunning table from file
    std::ifstream side2PruningTableFile("tables/Side2PruningTable.txt");
    this->phase2Side2PruningTable = new int[CubeConstants::PHASE_2_MAX_SIDE_COORDINATE];
    for (int i = 0; i < CubeConstants::PHASE_2_MAX_SIDE_COORDINATE; i++) {
        std::getline(side2PruningTableFile, line);
        this->phase2Side2PruningTable[i] = std::stoi(line);
    }
    side2PruningTableFile.close();
}