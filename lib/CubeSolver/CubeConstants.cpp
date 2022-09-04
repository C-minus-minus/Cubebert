#include "CubeConstants.h"

//  Six sides on a cube with 9 stickers on each face
const int CubeConstants::SIDE_COUNT = 6;
const int CubeConstants::STICKER_COUNT = 9;

const int CubeConstants::PHASE_1_MOVE_COUNT = 18;
const int CubeConstants::PHASE_2_MOVE_COUNT = 10;

//  Phase 1 will take at most 12 moves to complete, phase 2 could take up to 18
const int CubeConstants::MAX_PHASE_1_DEPTH = 12;
const int CubeConstants::MAX_PHASE_2_DEPTH = 18;

//  Maximum coordinates possible for phase 1
const int CubeConstants::PHASE_1_MAX_EDGE_COORDINATE = 2048;
const int CubeConstants::PHASE_1_MAX_CORNER_COORDINATE = 2187;
const int CubeConstants::PHASE_1_MAX_UDSLICE_COORDINATE = 495;

//  Maximum coordinates possible for phase 2
const int CubeConstants::PHASE_2_MAX_EDGE_COORDINATE = 40320;
const int CubeConstants::PHASE_2_MAX_CORNER_COORDINATE = 40320;
const int CubeConstants::PHASE_2_MAX_UDSLICE_COORDINATE = 24;
const int CubeConstants::PHASE_2_MAX_BAR1_COORDINATE = 3136;

const std::string CubeConstants::PHASE_1_MOVES[] = {
            "U", "U'", "U2",
            "L", "L'", "L2",
            "R", "R'", "R2",
            "D", "D'", "D2",
            "F", "F'", "F2",
            "B", "B'", "B2"
};

//  Moves to reverse legal moves in phase 1
const std::string CubeConstants::PHASE_1_ANTIMOVES[] = {
        "U'", "U", "U2",
        "L'", "L", "L2",
        "R'", "R", "R2",
        "D'", "D", "D2",
        "F'", "F", "F2",
        "B'", "B", "B2"
};

const std::string CubeConstants::PHASE_1_X_ROTATE_MOVES[] = {
        "B", "B'", "B2",
        "L", "L'", "L2",
        "R", "R'", "R2",
        "F", "F'", "F2",
        "U", "U'", "U2",
        "D", "D'", "D2"
};

const std::string CubeConstants::PHASE_1_Z_ROTATE_MOVES[] = {
        "R", "R'", "R2",
        "U", "U'", "U2",
        "D", "D'", "D2",
        "L", "L'", "L2",
        "F", "F'", "F2",
        "B", "B'", "B2"
};

//  Legal moves for phase 2
const std::string CubeConstants::PHASE_2_MOVES[] = {
        "U", "U'", "U2", "L2", "R2",
        "D", "D'", "D2", "F2", "B2"
};

//  Moves to reverse legal moves in phase 1
const std::string CubeConstants::PHASE_2_ANTIMOVES[] = {
        "U'", "U", "U2", "L2", "R2",
        "D'", "D", "D2", "F2", "B2"
};

int** CubeConstants::EDGE_ORDER_TABLE = CubeConstants::createEdgeOrderTable();
//const std::map<std::string, int> CubeConstants::EDGE_ORDER_TABLE = CubeConstants::createEdgeOrderTable();
int** CubeConstants::createEdgeOrderTable() {
    
    const int firstSticker[] = { 0, 0, 0, 0, 3, 2, 3, 1, 1, 2, 2, 1 };
    const int secondSticker[] = { 5, 2, 4, 1, 4, 3, 5, 3, 4, 4, 5, 5 };
    int** table = new int* [6];
    for (int i = 0; i < 6; i++) {
        table[i] = new int[6];
    }
    for (int i = 0; i < 12; i++) {
        table[firstSticker[i]][secondSticker[i]] = i;
        table[secondSticker[i]][firstSticker[i]] = i;
    }
    return table;
    /*
    const int edgeCount = 12;
    const std::string edge[] = {"05","02","04","01","34","23","35","13","14","24","25","15"};
    std::map<std::string, int> edgeOrderTable;
    for (int i = 0; i < edgeCount; i++) {
        edgeOrderTable[edge[i]] = i;
    }
    return edgeOrderTable;*/

}

int*** CubeConstants::CORNER_ORDER_TABLE = CubeConstants::createCornerOrderTable();
int*** CubeConstants::createCornerOrderTable() {
    
    int firstSticker[] = {0, 0, 0, 0, 1, 2, 2, 1};
    int secondSticker[] = {1, 2, 2, 1, 3, 3, 3, 3};
    int thirdSticker[] = { 5, 5, 4, 4, 4, 4, 5, 5 };

    int*** table = new int** [6];
    for (int i = 0; i < 6; i++) {
        table[i] = new int* [6];
        for (int a = 0; a < 6; a++) {
            table[i][a] = new int[6];
        }
    }
    for (int i = 0; i < 8; i++) {
        table[firstSticker[i]][secondSticker[i]][thirdSticker[i]] = i;
        table[firstSticker[i]][thirdSticker[i]][secondSticker[i]] = i;
        table[secondSticker[i]][firstSticker[i]][thirdSticker[i]] = i;
        table[secondSticker[i]][thirdSticker[i]][firstSticker[i]] = i;
        table[thirdSticker[i]][firstSticker[i]][secondSticker[i]] = i;
        table[thirdSticker[i]][secondSticker[i]][firstSticker[i]] = i;
    }
    return table;
    /*const int cornerCount = 8;
    const std::string corner[] = { "015","025","024","014","134","234","235","135" };
    std::map<std::string, int> cornerOrderTable;
    for (int i = 0; i < cornerCount; i++) {
        cornerOrderTable[corner[i]] = i;
    }
    return cornerOrderTable;*/
}

int** CubeConstants::UDSLICE_ORDER_TABLE = CubeConstants::createUdsliceOrderTable();
int** CubeConstants::createUdsliceOrderTable() {

    const int firstSticker[] = { 1, 2, 2, 1 };
    const int secondSticker[] = { 4, 4, 5, 5 };

    int** table = new int* [6];
    for (int i = 0; i < 6; i++) {
        table[i] = new int[6];
    }
    for (int i = 0; i < 4; i++) {
        table[firstSticker[i]][secondSticker[i]] = i;
        table[secondSticker[i]][firstSticker[i]] = i;
    }
    return table;
    /*
    const int cornerCount = 4;
    const std::string corner[] = { "14","24","25","15" };
    std::map<std::string, int> cornerOrderTable;
    for (int i = 0; i < cornerCount; i++) {
        cornerOrderTable[corner[i]] = i;
    }
    return cornerOrderTable;
    */
}