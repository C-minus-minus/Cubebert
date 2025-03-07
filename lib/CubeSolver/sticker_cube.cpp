#include "sticker_cube.h"

StickerCube::StickerCube() {

    //  default cube to solved state
    this->cubeState = new int*[CubeConstants::SIDE_COUNT];
    for (int side = 0; side < CubeConstants::SIDE_COUNT; side++) {
        this->cubeState[side] = new int [CubeConstants::STICKER_COUNT];
        for (int sticker = 0; sticker < CubeConstants::STICKER_COUNT; sticker++) {
            this->cubeState[side][sticker] = side;
        }
    }
}

StickerCube::StickerCube(int** faces) {
    this->cubeState = new int*[CubeConstants::SIDE_COUNT];
    for (int side = 0; side < CubeConstants::SIDE_COUNT; side++) {
        this->cubeState[side] = new int[CubeConstants::STICKER_COUNT];
        for (int sticker = 0; sticker < CubeConstants::STICKER_COUNT; sticker++) {
            this->cubeState[side][sticker] = faces[side][sticker];
        }
    }
}

/**
* Builds a sticker cube from an array, and rotates the faces based on 'orientation' settings
* @param faces - 6x9 2D array representing cube state
* @param orientation - value at index N represents how many times side N needs rotate counter clockwise
**/
StickerCube::StickerCube(int** faces, int* orientation) {

    for(int side = 0; side < CubeConstants::SIDE_COUNT; side++) {

        for(int rotation = 0; rotation < orientation[side]; rotation++) {

            //  rotate side counter clockwise
            int corners[4] = {0, 2, 8, 6};
            int edges[4] = {1, 5, 7, 3};
            int bufferCorner = faces[side][corners[0]];
            int bufferEdge = faces[side][edges[0]];;
            for(int sticker = 0; sticker < 3; sticker++) {
                faces[side][corners[sticker]] = faces[side][corners[sticker + 1]];
                faces[side][edges[sticker]] = faces[side][edges[sticker + 1]];
            }
            faces[side][corners[3]] = bufferCorner;
            faces[side][edges[3]] = bufferEdge;
        }
    }

    this->cubeState = new int*[CubeConstants::SIDE_COUNT];
    for (int side = 0; side < CubeConstants::SIDE_COUNT; side++) {
        this->cubeState[side] = new int[CubeConstants::STICKER_COUNT];
        for (int sticker = 0; sticker < CubeConstants::STICKER_COUNT; sticker++) {
            this->cubeState[side][sticker] = faces[side][sticker];
        }
    }
}

StickerCube::StickerCube(std::string scramble) : StickerCube::StickerCube() {
    this->applyScramble(scramble);
}

StickerCube::~StickerCube() {
    for (int i = 0; i < CubeConstants::SIDE_COUNT; i++) {
        delete[] this->cubeState[i];
    }
    delete[] this->cubeState;
}

void StickerCube::applyScramble(std::string scramble) {

    std::stringstream scrambleStream(scramble);
    std::string currMove;

    while (scrambleStream >> currMove) {
        int turnTimes = currMove.length() <= 1 ? 3 : (currMove[1] == '2' ? 2 : 1);
        for (int i = 0; i < turnTimes; i++) {
            if (currMove == "U" || currMove == "U'" || currMove == "U2") {
                this->turnUp();
            }
            else if (currMove == "L" || currMove == "L'" || currMove == "L2") {
                this->turnLeft();
            }
            else if (currMove == "R" || currMove == "R'" || currMove == "R2") {
                this->turnRight();
            }
            else if (currMove == "D" || currMove == "D'" || currMove == "D2") {
                this->turnDown();
            }
            else if (currMove == "F" || currMove == "F'" || currMove == "F2") {
                this->turnFront();
            }
            else if (currMove == "B" || currMove == "B'" || currMove == "B2") {
                this->turnBack();
            }
        }
    }
}

void StickerCube::applyMove(std::string move) {
    if (move[0] == 'U') {
        this->turnUp();
        if (move == "U2") {
            this->turnUp();
        }
        else if(move == "U") {
            this->turnUp();
            this->turnUp();
        }
    }
    else if (move[0] == 'L') {
        this->turnLeft();
        if (move == "L2") {
            this->turnLeft();
        }
        else if (move == "L") {
            this->turnLeft();
            this->turnLeft();
        }
    }
    else if (move[0] == 'R') {
        this->turnRight();
        if (move == "R2") {
            this->turnRight();
        }
        else if (move == "R") {
            this->turnRight();
            this->turnRight();
        }
    }
    
    else if (move[0] == 'D') {
        this->turnDown();
        if (move == "D2") {
            this->turnDown();
        }
        else if (move == "D") {
            this->turnDown();
            this->turnDown();
        }
    }
    else if (move[0] == 'F') {
        this->turnFront();
        if (move == "F2") {
            this->turnFront();
        }
        else if (move == "F") {
            this->turnFront();
            this->turnFront();
        }
    }
    else if (move[0] == 'B') {
        this->turnBack();
        if (move == "B2") {
            this->turnBack();
        }
        else if (move == "B") {
            this->turnBack();
            this->turnBack();
        }
    }
}

int** StickerCube::getCubeState() {
    return this->cubeState;
}

void StickerCube::turnUp() {

    //  side of cube
    const int side = 0;

    //  outside coordinates
    const int outsideCorner1[] = {2, 2, 2, 2};
    const int outsideCorner2[] = {0, 0, 0, 0};
    const int outsideEdge[] = {1, 1, 1, 1};
    const int outsideSide[] = {5, 2, 4, 1};

    //  apply up side turn
    this->applyTurn(side, outsideCorner1, outsideCorner2, outsideEdge, outsideSide);
}

void StickerCube::turnLeft() {
    
    //  inside coordinates
    const int side = 1;

    //  outside coordinates
    const int outsideCorner1[] = {0, 0, 0, 8};
    const int outsideCorner2[] = {6, 6, 6, 2};
    const int outsideEdge[] = {3, 3, 3, 5};
    const int outsideSide[] = {0, 4, 3, 5};

    //  apply left side turn
    this->applyTurn(side, outsideCorner1, outsideCorner2, outsideEdge, outsideSide);
}

void StickerCube::turnRight() {

    //  inside coordinates
    const int side = 2;

    //  outside coordinates
    const int outsideCorner1[] = {8, 0, 8, 8};
    const int outsideCorner2[] = {2, 6, 2, 2};
    const int outsideEdges[] = {5, 3, 5, 5};
    const int outsideSides[] = {0, 5, 3, 4};

    //  apply right side turn
    this->applyTurn(side, outsideCorner1, outsideCorner2, outsideEdges, outsideSides);
}

void StickerCube::turnDown() {

    //  side of cube
    const int side = 3;

    //  outside coordinates
    const int outsideCorner1[] = {6, 6, 6, 6};
    const int outsideCorner2[] = {8, 8, 8, 8};
    const int outsideEdge[] = {7, 7, 7, 7};
    const int outsideSide[] = {4, 2, 5, 1};

    //  apply down side turn
    this->applyTurn(side, outsideCorner1, outsideCorner2, outsideEdge, outsideSide);
}

void StickerCube::turnFront() {

    //  side of cube
    const int side = 4;

    //  outside coordinates
    const int outsideCorner1[] = {6, 0, 2, 8};
    const int outsideCorner2[] = {8, 6, 0, 2};
    const int outsideEdge[] = {7, 3, 1, 5};
    const int outsideSide[] = {0, 2, 3, 1};

    //  apply front side turn
    this->applyTurn(side, outsideCorner1, outsideCorner2, outsideEdge, outsideSide);
}

void StickerCube::turnBack() {

    //  side of cube
    const int side = 5;

    //  outside coordinates
    const int outsideCorner1[] = {0, 6, 8, 2};
    const int outsideCorner2[] = {2, 0, 6, 8};
    const int outsideEdge[] = {1, 3, 7, 5};
    const int outsideSide[] = {0, 1, 3, 2};

    //  apply back side turn
    this->applyTurn(side, outsideCorner1, outsideCorner2, outsideEdge, outsideSide);
}

void StickerCube::applyTurn(
    int side,
    const int* outsideCorner1,
    const int* outsideCorner2,
    const int* outsideEdge,
    const int* outsideSide) {

    const int corners[] = {0, 2, 8, 6};
    const int edges[] = {1, 5, 7, 3};

    const int firstCorner = this->cubeState[side][corners[0]];
    const int firstEdge = this->cubeState[side][edges[0]];
    const int firstOutsideCorner1 = this->cubeState[outsideSide[0]][outsideCorner1[0]];
    const int firstOutsideCorner2 = this->cubeState[outsideSide[0]][outsideCorner2[0]];
    const int firstOutsideEdge = this->cubeState[outsideSide[0]][outsideEdge[0]];

    for (int i = 0; i < 3; i++) {
        this->cubeState[side][corners[i]] = this->cubeState[side][corners[i + 1]];
        this->cubeState[side][edges[i]] = this->cubeState[side][edges[i + 1]];
        this->cubeState[outsideSide[i]][outsideCorner1[i]] = this->cubeState[outsideSide[i + 1]][outsideCorner1[i + 1]];
        this->cubeState[outsideSide[i]][outsideCorner2[i]] = this->cubeState[outsideSide[i + 1]][outsideCorner2[i + 1]];
        this->cubeState[outsideSide[i]][outsideEdge[i]] = this->cubeState[outsideSide[i + 1]][outsideEdge[i + 1]];
    }

    this->cubeState[side][corners[3]] = firstCorner;
    this->cubeState[side][edges[3]] = firstEdge;
    this->cubeState[outsideSide[3]][outsideCorner1[3]] = firstOutsideCorner1;
    this->cubeState[outsideSide[3]][outsideCorner2[3]] = firstOutsideCorner2;
    this->cubeState[outsideSide[3]][outsideEdge[3]] = firstOutsideEdge;
}

StickerCube* StickerCube::fromCornerPermutation(int coord) {

    const int cornerCount = 8;
    int perm[cornerCount];
    for (int i = 0; i < cornerCount; i++) {
        perm[i] = coord / (int)CubeMath::factorial(cornerCount - 1 - i);
        coord = coord % (int)CubeMath::factorial(cornerCount - 1 - i);
    }
    for (int i = cornerCount - 1; i > 0; i--) {
        for (int a = i - 1; a >= 0; a--) {
            if (perm[a] <= perm[i]) {
                perm[i]++;
            }
        }
    }

    int primarySticker[] = {0, 2, 8, 6, 0, 2, 8, 6};
    int primaryStickerSide[] = {0, 0, 0, 0, 3, 3, 3, 3};

    int secondarySticker[] = {0, 0, 0, 0, 8, 8, 8, 8};
    int secondaryStickerSide[] = {1, 5, 2, 4, 1, 4, 2, 5};

    int tertiarySticker[] = {2, 2, 2, 2, 6, 6, 6, 6};
    int tertiaryStickerSide[] = {5, 2, 4, 1, 4, 2, 5, 1};
    StickerCube* stickerCube = new StickerCube();
    for (int i = 0; i < cornerCount; i++) {
        stickerCube->cubeState[primaryStickerSide[i]][primarySticker[i]] = primaryStickerSide[perm[i]];
        stickerCube->cubeState[secondaryStickerSide[i]][secondarySticker[i]] = secondaryStickerSide[perm[i]];
        stickerCube->cubeState[tertiaryStickerSide[i]][tertiarySticker[i]] = tertiaryStickerSide[perm[i]];
    }
    return stickerCube;
}

StickerCube* StickerCube::fromEdgePermutation(int coord) {

    const int edgeCount = 8;
    int perm[edgeCount];
    for (int i = 0; i < edgeCount; i++) {
        perm[i] = coord / CubeMath::factorial(edgeCount - 1 - i);
        coord = coord % CubeMath::factorial(edgeCount - 1 - i);
    }
    for (int i = edgeCount - 1; i > 0; i--) {
        for (int a = i - 1; a >= 0; a--) {
            if (perm[a] <= perm[i]) {
                perm[i]++;
            }
        }
    }

    const int primarySticker[] = {1, 5, 7, 3, 1, 5, 7, 3};
    const int primaryStickerSide[] = {0, 0, 0, 0, 3, 3, 3, 3};

    const int secondarySticker[] = {1, 1, 1, 1, 7, 7, 7, 7};
    const int secondaryStickerSide[] = {5, 2, 4, 1, 4, 2, 5, 1};

    StickerCube* stickerCube = new StickerCube();
    for (int i = 0; i < edgeCount; i++) {
        stickerCube->cubeState[primaryStickerSide[i]][primarySticker[i]] = primaryStickerSide[perm[i]];
        stickerCube->cubeState[secondaryStickerSide[i]][secondarySticker[i]] = secondaryStickerSide[perm[i]];
    }
    return stickerCube;
}

StickerCube* StickerCube::fromUDSlice(int coord) {

    const int edgeCount = 4;
    int perm[edgeCount];
    for (int i = 0; i < edgeCount; i++) {
        perm[i] = coord / CubeMath::factorial(edgeCount - 1 - i);
        coord = coord % CubeMath::factorial(edgeCount - 1 - i);
    }
    for (int i = edgeCount - 1; i > 0; i--) {
        for (int a = i - 1; a >= 0; a--) {
            if (perm[a] <= perm[i]) {
                perm[i]++;
            }
        }
    }

    const int primarySticker[] = {3, 5, 3, 5};
    const int primaryStickerSide[] = {4, 4, 5, 5};

    const int secondarySticker[] = {5, 3, 5, 3};
    const int secondaryStickerSide[] = {1, 2, 2, 1};

    StickerCube* stickerCube = new StickerCube();
    for (int i = 0; i < edgeCount; i++) {
        stickerCube->cubeState[primaryStickerSide[i]][primarySticker[i]] = primaryStickerSide[perm[i]];
        stickerCube->cubeState[secondaryStickerSide[i]][secondarySticker[i]] = secondaryStickerSide[perm[i]];
    }
    return stickerCube;
}

/**
*Calculates a number in the range[0, 2 ^ 11 - 1]
* Each possible edge orientation state maps to a unique ID
* @param stickerCube - Cube on facelet level
* @return phase 1 edge orientation coordinate[0, 2048]
* */
int StickerCube::getPhase1EdgeCoordinate() {

    int phase1EdgeCoordinate = 0;

    int** cubeState = this->getCubeState();
    const int edgeCount = 11;
    const int primaryEdgeSide[] = { 0, 0, 0, 0, 3, 3, 3, 3, 4, 4, 5 };
    const int primaryEdgeSticker[] = { 1, 5, 7, 3, 1, 5, 7, 3, 3, 5, 3 };
    const int secondaryEdgeSide[] = { 5, 2, 4, 1, 4, 2, 5, 1, 1, 2, 2 };
    const int secondaryEdgeSticker[] = { 1, 1, 1, 1, 7, 7, 7, 7, 5, 3, 5 };
    for (int i = 0; i < edgeCount; i++) {

        const int primarySticker = cubeState[primaryEdgeSide[i]][primaryEdgeSticker[i]];
        const int secondarySticker = cubeState[secondaryEdgeSide[i]][secondaryEdgeSticker[i]];
        if (primarySticker == 1 || primarySticker == 2 ||
            ((primarySticker == 4 || primarySticker == 5) &&
                (secondarySticker == 0 || secondarySticker == 3))) {
            phase1EdgeCoordinate |= (1 << i);
        }
    }

    return phase1EdgeCoordinate;
}

/**
     * Calculates a number in the range [0, 3^7 - 1]
     * Each possible corner orientation state maps to a unique ID
     * @param stickerCube - Cube on facelet level
     * @return phase 1 corner orientation coordinate [0, 2187]
**/
int StickerCube::getPhase1CornerCoordinate() {

    int phase1CornerCoordinate = 0;

    int** cubeState = this->getCubeState();
    const int cornerCount = 7;
    const int primaryStickerSide[] = { 0, 0, 0, 0, 3, 3, 3 };
    const int primarySticker[] = { 0, 2, 8, 6, 0, 2, 8 };
    const int secondaryStickerSide[] = { 1, 5, 2, 4, 1, 4, 2 };
    const int secondarySticker[] = { 0, 0, 0, 0, 8, 8, 8 };
    for (int i = 0; i < cornerCount; i++) {

        int factor = 2;
        int currPrimarySticker = cubeState[primaryStickerSide[i]][primarySticker[i]];
        int currSecondarySticker = cubeState[secondaryStickerSide[i]][secondarySticker[i]];
        if (currPrimarySticker == 0 || currPrimarySticker == 3) {
            factor = 0;
        }
        else if (currSecondarySticker == 0 || currSecondarySticker == 3) {
            factor = 1;
        }
        phase1CornerCoordinate += factor * int(pow(3, i));
    }

    return phase1CornerCoordinate;
}

/**
* Calculates a number in the range [0, (12 choose 4)]
* Each possible UDSlice partial permutation state maps to a unique ID
* @param stickerCube - Cube on facelet level
* @return phase 1 UDSlice partial permutation coordinate [0, (12 choose 4)]
*/
int StickerCube::getPhase1UdsliceCoordinate() {
    
    int phase1UDSliceCoordinate = 0;

    int** cubeState = this->getCubeState();

    const int stickerCount = 12;
    const int primarySticker[] = { 1, 5, 7, 3, 1, 5, 7, 3, 3, 5, 3, 5 };
    const int primaryStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3, 4, 4, 5, 5 };

    const int secondarySticker[] = { 1, 1, 1, 1, 7, 7, 7, 7, 5, 3, 5, 3 };
    const int secondaryStickerSide[] = { 5, 2, 4, 1, 4, 2, 5, 1, 1, 2, 2, 1 };

    bool positions[12];
    for (int i = 0; i < 12; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryStickerSide[i]][primarySticker[i]];
        int sticker2 = cubeState[secondaryStickerSide[i]][secondarySticker[i]];

        if (sticker1 == 1 || sticker1 == 2) {
            if (sticker2 == 4 || sticker2 == 5) {
                positions[i] = true;
            }
        }
        else if (sticker1 == 4 || sticker1 == 5) {
            if (sticker2 == 1 || sticker2 == 2) {
                positions[i] = true;
            }
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase1UDSliceCoordinate += CubeMath::choose(n, k);
        }
    }

    return phase1UDSliceCoordinate;
}

/**
     * Calculates a number in the range [0, 8!]
     * Each possible edge permutation state maps to a unique ID
     * @param stickerCube - Cube on facelet level
     * @return phase 2 edge permutation coordinate [0, 8!]
 **/
int StickerCube::getPhase2EdgeCoordinate() {

    int phase2EdgeCoordinate = 0;
    int** cubeState = this->getCubeState();

    const int stickerCount = 8;
    const int primarySticker[] = { 1, 5, 7, 3, 1, 5, 7, 3 };
    const int primaryStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondarySticker[] = { 1, 1, 1, 1, 7, 7, 7, 7 };
    const int secondaryStickerSide[] = { 5, 2, 4, 1, 4, 2, 5, 1 };
    std::string key;
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryStickerSide[i]][primarySticker[i]];
        int sticker2 = cubeState[secondaryStickerSide[i]][secondarySticker[i]];

        /*key = sticker1 < sticker2 ?
            std::to_string(sticker1) + std::to_string(sticker2) : std::to_string(sticker2) + std::to_string(sticker1);
        */
        int order = CubeConstants::EDGE_ORDER_TABLE[sticker1][sticker2];
        //int order =  CubeConstants::EDGE_ORDER_TABLE.at(std::string(thing));
        int sum = 0;
        for (int a = 0; a < i; a++) {
            int sticker3 = cubeState[primaryStickerSide[a]][primarySticker[a]];
            int sticker4 = cubeState[secondaryStickerSide[a]][secondarySticker[a]];
            
            int currOrder = CubeConstants::EDGE_ORDER_TABLE[sticker3][sticker4];
            /*key = sticker3 < sticker4 ?
                std::to_string(sticker3) + std::to_string(sticker4) : std::to_string(sticker4) + std::to_string(sticker3);
            *///int currOrder = CubeConstants::EDGE_ORDER_TABLE.at(std::string(otherThing));
            if (currOrder < order) {
                sum++;
            }
        }
        phase2EdgeCoordinate += CubeMath::factorial(stickerCount - 1 - i) * (order - sum);
    }

    return phase2EdgeCoordinate;
}

/**
 * Calculates a number in the range [0, 8!]
 * Each possible corner permutation state maps to a unique ID
 * @param stickerCube - Cube on facelet level
 * @return phase 2 corner permutation coordinate [0, 8!]
 */
int StickerCube::getPhase2CornerCoordinate() {

    int phase2EdgeCoordinate = 0;
    int** cubeState = this->getCubeState();

    const int stickerCount = 8;
    const int primarySticker[] = { 0, 2, 8, 6, 0, 2, 8, 6 };
    const int primaryStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondarySticker[] = { 0, 0, 0, 0, 8, 8, 8, 8 };
    const int secondaryStickerSide[] = { 1, 5, 2, 4, 1, 4, 2, 5 };

    const int tertiarySticker[] = { 2, 2, 2, 2, 6, 6, 6, 6 };
    const int tertiaryStickerSide[] = { 5, 2, 4, 1, 4, 2, 5, 1 };

    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryStickerSide[i]][primarySticker[i]];
        int sticker2 = cubeState[secondaryStickerSide[i]][secondarySticker[i]];
        int sticker3 = cubeState[tertiaryStickerSide[i]][tertiarySticker[i]];
        int order = CubeConstants::CORNER_ORDER_TABLE[sticker1][sticker2][sticker3];
        int sum = 0;
        for (int a = 0; a < i; a++) {
            int sticker4 = cubeState[primaryStickerSide[a]][primarySticker[a]];
            int sticker5 = cubeState[secondaryStickerSide[a]][secondarySticker[a]];
            int sticker6 = cubeState[tertiaryStickerSide[a]][tertiarySticker[a]];
            int currOrder = CubeConstants::CORNER_ORDER_TABLE[sticker4][sticker5][sticker6];
            if (currOrder < order) {
                sum++;
            }
        }
        phase2EdgeCoordinate += CubeMath::factorial(stickerCount - 1 - i) * (order - sum);
    }

    return phase2EdgeCoordinate;
}

/**
 * Calculates a number in the range [0, 4!]
 * Each possible UDSlice permutation state maps to a unique ID
 * @param stickerCube - Cube on facelet level
 * @return phase 2 UDSlice permutation coordinate [0, 4!]
 */
int StickerCube::getPhase2UdsliceCoordinate() {

    int phase2UDSliceCoordinate = 0;

    int** cubeState = this->getCubeState();

    const int stickerCount = 4;
    const int primarySticker[] = { 3, 5, 3, 5 };
    const int primaryStickerSide[] = { 4, 4, 5, 5 };

    const int secondarySticker[] = { 5, 3, 5, 3 };
    const int secondaryStickerSide[] = { 1, 2, 2, 1 };
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryStickerSide[i]][primarySticker[i]];
        int sticker2 = cubeState[secondaryStickerSide[i]][secondarySticker[i]];
        int order = CubeConstants::UDSLICE_ORDER_TABLE[sticker1][sticker2];
        int sum = 0;
        for (int a = 0; a < i; a++) {
            int sticker3 = cubeState[primaryStickerSide[a]][primarySticker[a]];
            int sticker4 = cubeState[secondaryStickerSide[a]][secondarySticker[a]];
            
            int currOrder = CubeConstants::UDSLICE_ORDER_TABLE[sticker3][sticker4];
            if (currOrder < order) {
                sum++;
            }
        }
        phase2UDSliceCoordinate += CubeMath::factorial(stickerCount - 1 - i) * (order - sum);
    }

    return phase2UDSliceCoordinate;
}

/**
* Calculates a number in the range [0, (2 * (8 choose 2)) ^ 2]
* Each possible UDSlice partial permutation state maps to a unique ID
* @param stickerCube - Cube on facelet level
* @return phase 1 UDSlice partial permutation coordinate [0, (12 choose 4)]
*/
int StickerCube::getPhase2Bar1Coordinate() {
    
    int phase2Bar1EdgeCoordinate = 0;

    int** cubeState = this->getCubeState();

    //  EDGES

    // const int stickerCount = 12;
    // const int primarySticker[] = { 1, 5, 7, 3, 1, 5, 7, 3, 3, 5, 3, 5 };
    // const int primaryStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3, 4, 4, 5, 5 };
    const int stickerCount = 8;
    const int primaryEdgeSticker[] = { 7, 5, 1, 3, 7, 5, 1, 3 };
    const int primaryEdgeStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    // const int secondarySticker[] = { 1, 1, 1, 1, 7, 7, 7, 7, 5, 3, 5, 3 };
    // const int secondaryStickerSide[] = { 5, 2, 4, 1, 4, 2, 5, 1, 1, 2, 2, 1 };
    const int secondaryEdgeSticker[] = { 1, 1, 1, 1, 7, 7, 7, 7 };
    const int secondaryEdgeStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int goalEdgeSticker1PrimarySide = 0;
    const int goalEdgeSticker1SecondarySide = 4;

    const int goalEdgeSticker2PrimarySide = 0;
    const int goalEdgeSticker2SecondarySide = 2;

    int firstFound = -1;
    bool positions[8];
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryEdgeStickerSide[i]][primaryEdgeSticker[i]];
        int sticker2 = cubeState[secondaryEdgeStickerSide[i]][secondaryEdgeSticker[i]];

        if ( (goalEdgeSticker1PrimarySide == sticker1 && goalEdgeSticker1SecondarySide == sticker2)
            || (goalEdgeSticker1PrimarySide == sticker2 && goalEdgeSticker1SecondarySide == sticker1)) {
            if(firstFound == -1) {
                firstFound = 0;
            }
            positions[i] = true;
        }
        else if ( (goalEdgeSticker2PrimarySide == sticker1 && goalEdgeSticker2SecondarySide == sticker2)
            || (goalEdgeSticker2PrimarySide == sticker2 && goalEdgeSticker2SecondarySide == sticker1)) {
            if(firstFound == -1) {
                firstFound = 1;
            }
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar1EdgeCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar1EdgeCoordinate = phase2Bar1EdgeCoordinate + 28 * firstFound;

    //  Corners
    int phase2Bar1CornerCoordinate = 0;
    const int primaryCornerSticker[] = { 6, 8, 2, 0, 6, 8, 2, 0 };
    const int primaryCornerStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryCornerSticker[] = { 0, 0, 0, 0, 8, 8, 8, 8 };
    const int secondaryCornerStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int thirdCornerSticker[] = { 2, 2, 2, 2, 6, 6, 6, 6 };
    const int thirdCornerStickerSide[] = { 1, 4, 2, 5, 1, 5, 2, 4 };

    const int goalCornerSticker1PrimarySide = 0;
    const int goalCornerSticker1SecondarySide = 4;
    const int goalCornerSticker1ThirdSide = 1;

    const int goalCornerSticker2PrimarySide = 0;
    const int goalCornerSticker2SecondarySide = 2;
    const int goalCornerSticker2ThirdSide = 4;

    const int goalCornerSticker3PrimarySide = 0;
    const int goalCornerSticker3SecondarySide = 5;
    const int goalCornerSticker3ThirdSide = 2;
    firstFound = -1;
    int digit = 0;
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryCornerStickerSide[i]][primaryCornerSticker[i]];
        int sticker2 = cubeState[secondaryCornerStickerSide[i]][secondaryCornerSticker[i]];
        int sticker3 = cubeState[thirdCornerStickerSide[i]][thirdCornerSticker[i]];
        if(sticker1 == goalCornerSticker1PrimarySide 
            && sticker2 == goalCornerSticker1SecondarySide
            && sticker3 == goalCornerSticker1ThirdSide) {
            if(digit == 0) {
                firstFound = 0;
                digit++;
            }
            else if(digit == 1) {
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 0;
            // }
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker2PrimarySide 
            && sticker2 == goalCornerSticker2SecondarySide
            && sticker3 == goalCornerSticker2ThirdSide) {
            if(digit == 0) {
                firstFound = 2;
                digit++;
            }
            else if(digit == 1) {
                if(firstFound == 4) {
                    firstFound = 5;
                }
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 1;
            // }
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker3PrimarySide 
            && sticker2 == goalCornerSticker3SecondarySide
            && sticker3 == goalCornerSticker3ThirdSide) {
            if(digit == 0) {
                firstFound = 4;
                digit++;
            }
            else if(digit == 1) {
                if(firstFound == 0) {
                    firstFound = 1;
                } else if(firstFound == 2) {
                    firstFound = 3;
                }
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 1;
            // }
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar1CornerCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar1CornerCoordinate = phase2Bar1CornerCoordinate + 56 * firstFound;

    return phase2Bar1EdgeCoordinate * 336 + phase2Bar1CornerCoordinate ;
}

/**
* Calculates a number in the range [0, (2 * (8 choose 2)) ^ 2]
* Each possible UDSlice partial permutation state maps to a unique ID
* @param stickerCube - Cube on facelet level
* @return phase 1 UDSlice partial permutation coordinate [0, (12 choose 4)]
*/
int StickerCube::getPhase2Bar2Coordinate() {
    
    int phase2Bar2EdgeCoordinate = 0;

    int** cubeState = this->getCubeState();

    //  EDGES

    // const int stickerCount = 12;
    // const int primarySticker[] = { 1, 5, 7, 3, 1, 5, 7, 3, 3, 5, 3, 5 };
    // const int primaryStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3, 4, 4, 5, 5 };
    const int stickerCount = 8;
    const int primaryEdgeSticker[] = { 7, 5, 1, 3, 7, 5, 1, 3 };
    const int primaryEdgeStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    // const int secondarySticker[] = { 1, 1, 1, 1, 7, 7, 7, 7, 5, 3, 5, 3 };
    // const int secondaryStickerSide[] = { 5, 2, 4, 1, 4, 2, 5, 1, 1, 2, 2, 1 };
    const int secondaryEdgeSticker[] = { 1, 1, 1, 1, 7, 7, 7, 7 };
    const int secondaryEdgeStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int goalEdgeSticker1PrimarySide = 0;
    const int goalEdgeSticker1SecondarySide = 5;

    const int goalEdgeSticker2PrimarySide = 0;
    const int goalEdgeSticker2SecondarySide = 1;

    int firstFound = -1;
    bool positions[8];
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryEdgeStickerSide[i]][primaryEdgeSticker[i]];
        int sticker2 = cubeState[secondaryEdgeStickerSide[i]][secondaryEdgeSticker[i]];

        if ( (goalEdgeSticker1PrimarySide == sticker1 && goalEdgeSticker1SecondarySide == sticker2)
            || (goalEdgeSticker1PrimarySide == sticker2 && goalEdgeSticker1SecondarySide == sticker1)) {
            if(firstFound == -1) {
                firstFound = 0;
            }
            positions[i] = true;
        }
        else if ( (goalEdgeSticker2PrimarySide == sticker1 && goalEdgeSticker2SecondarySide == sticker2)
            || (goalEdgeSticker2PrimarySide == sticker2 && goalEdgeSticker2SecondarySide == sticker1)) {
            if(firstFound == -1) {
                firstFound = 1;
            }
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar2EdgeCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar2EdgeCoordinate = phase2Bar2EdgeCoordinate + 28 * firstFound;

    //  Corners
    int phase2Bar2CornerCoordinate = 0;
    const int primaryCornerSticker[] = { 6, 8, 2, 0, 6, 8, 2, 0 };
    const int primaryCornerStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryCornerSticker[] = { 0, 0, 0, 0, 8, 8, 8, 8 };
    const int secondaryCornerStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int thirdCornerSticker[] = { 2, 2, 2, 2, 6, 6, 6, 6 };
    const int thirdCornerStickerSide[] = { 1, 4, 2, 5, 1, 5, 2, 4 };

    const int goalCornerSticker1PrimarySide = 0;
    const int goalCornerSticker1SecondarySide = 5;
    const int goalCornerSticker1ThirdSide = 2;

    const int goalCornerSticker2PrimarySide = 0;
    const int goalCornerSticker2SecondarySide = 1;
    const int goalCornerSticker2ThirdSide = 5;

    const int goalCornerSticker3PrimarySide = 0;
    const int goalCornerSticker3SecondarySide = 4;
    const int goalCornerSticker3ThirdSide = 1;
    firstFound = -1;
    int digit = 0;
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryCornerStickerSide[i]][primaryCornerSticker[i]];
        int sticker2 = cubeState[secondaryCornerStickerSide[i]][secondaryCornerSticker[i]];
        int sticker3 = cubeState[thirdCornerStickerSide[i]][thirdCornerSticker[i]];
        if(sticker1 == goalCornerSticker1PrimarySide 
            && sticker2 == goalCornerSticker1SecondarySide
            && sticker3 == goalCornerSticker1ThirdSide) {
            if(digit == 0) {
                firstFound = 0;
                digit++;
            }
            else if(digit == 1) {
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 0;
            // }
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker2PrimarySide 
            && sticker2 == goalCornerSticker2SecondarySide
            && sticker3 == goalCornerSticker2ThirdSide) {
            if(digit == 0) {
                firstFound = 2;
                digit++;
            }
            else if(digit == 1) {
                if(firstFound == 4) {
                    firstFound = 5;
                }
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 1;
            // }
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker3PrimarySide 
            && sticker2 == goalCornerSticker3SecondarySide
            && sticker3 == goalCornerSticker3ThirdSide) {
            if(digit == 0) {
                firstFound = 4;
                digit++;
            }
            else if(digit == 1) {
                if(firstFound == 0) {
                    firstFound = 1;
                } else if(firstFound == 2) {
                    firstFound = 3;
                }
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 1;
            // }
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar2CornerCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar2CornerCoordinate = phase2Bar2CornerCoordinate + 56 * firstFound;

    return phase2Bar2EdgeCoordinate * 336 + phase2Bar2CornerCoordinate;
}

/**
* Calculates a number in the range [0, (2 * (8 choose 2)) ^ 2]
* Each possible UDSlice partial permutation state maps to a unique ID
* @param stickerCube - Cube on facelet level
* @return phase 1 UDSlice partial permutation coordinate [0, (12 choose 4)]
*/
int StickerCube::getPhase2Bar3Coordinate() {
    
    int phase2Bar3EdgeCoordinate = 0;

    int** cubeState = this->getCubeState();

    //  EDGES

    // const int stickerCount = 12;
    // const int primarySticker[] = { 1, 5, 7, 3, 1, 5, 7, 3, 3, 5, 3, 5 };
    // const int primaryStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3, 4, 4, 5, 5 };
    const int stickerCount = 8;
    const int primaryEdgeSticker[] = { 7, 5, 1, 3, 7, 5, 1, 3 };
    const int primaryEdgeStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    // const int secondarySticker[] = { 1, 1, 1, 1, 7, 7, 7, 7, 5, 3, 5, 3 };
    // const int secondaryStickerSide[] = { 5, 2, 4, 1, 4, 2, 5, 1, 1, 2, 2, 1 };
    const int secondaryEdgeSticker[] = { 1, 1, 1, 1, 7, 7, 7, 7 };
    const int secondaryEdgeStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int goalEdgeSticker1PrimarySide = 3;
    const int goalEdgeSticker1SecondarySide = 5;

    const int goalEdgeSticker2PrimarySide = 3;
    const int goalEdgeSticker2SecondarySide = 2;

    int firstFound = -1;
    bool positions[8];
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryEdgeStickerSide[i]][primaryEdgeSticker[i]];
        int sticker2 = cubeState[secondaryEdgeStickerSide[i]][secondaryEdgeSticker[i]];

        if ( (goalEdgeSticker1PrimarySide == sticker1 && goalEdgeSticker1SecondarySide == sticker2)
            || (goalEdgeSticker1PrimarySide == sticker2 && goalEdgeSticker1SecondarySide == sticker1)) {
            if(firstFound == -1) {
                firstFound = 0;
            }
            positions[i] = true;
        }
        else if ( (goalEdgeSticker2PrimarySide == sticker1 && goalEdgeSticker2SecondarySide == sticker2)
            || (goalEdgeSticker2PrimarySide == sticker2 && goalEdgeSticker2SecondarySide == sticker1)) {
            if(firstFound == -1) {
                firstFound = 1;
            }
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar3EdgeCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar3EdgeCoordinate = phase2Bar3EdgeCoordinate + 28 * firstFound;

    //  Corners
    int phase2Bar3CornerCoordinate = 0;
    const int primaryCornerSticker[] = { 6, 8, 2, 0, 6, 8, 2, 0 };
    const int primaryCornerStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryCornerSticker[] = { 0, 0, 0, 0, 8, 8, 8, 8 };
    const int secondaryCornerStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int thirdCornerSticker[] = { 2, 2, 2, 2, 6, 6, 6, 6 };
    const int thirdCornerStickerSide[] = { 1, 4, 2, 5, 1, 5, 2, 4 };

    const int goalCornerSticker1PrimarySide = 3;
    const int goalCornerSticker1SecondarySide = 5;
    const int goalCornerSticker1ThirdSide = 1;

    const int goalCornerSticker2PrimarySide = 3;
    const int goalCornerSticker2SecondarySide = 2;
    const int goalCornerSticker2ThirdSide = 5;

    const int goalCornerSticker3PrimarySide = 3;
    const int goalCornerSticker3SecondarySide = 4;
    const int goalCornerSticker3ThirdSide = 2;
    firstFound = -1;
    int digit = 0;
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryCornerStickerSide[i]][primaryCornerSticker[i]];
        int sticker2 = cubeState[secondaryCornerStickerSide[i]][secondaryCornerSticker[i]];
        int sticker3 = cubeState[thirdCornerStickerSide[i]][thirdCornerSticker[i]];
        if(sticker1 == goalCornerSticker1PrimarySide 
            && sticker2 == goalCornerSticker1SecondarySide
            && sticker3 == goalCornerSticker1ThirdSide) {
            if(digit == 0) {
                firstFound = 0;
                digit++;
            }
            else if(digit == 1) {
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 0;
            // }
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker2PrimarySide 
            && sticker2 == goalCornerSticker2SecondarySide
            && sticker3 == goalCornerSticker2ThirdSide) {
            if(digit == 0) {
                firstFound = 2;
                digit++;
            }
            else if(digit == 1) {
                if(firstFound == 4) {
                    firstFound = 5;
                }
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 1;
            // }
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker3PrimarySide 
            && sticker2 == goalCornerSticker3SecondarySide
            && sticker3 == goalCornerSticker3ThirdSide) {
            if(digit == 0) {
                firstFound = 4;
                digit++;
            }
            else if(digit == 1) {
                if(firstFound == 0) {
                    firstFound = 1;
                } else if(firstFound == 2) {
                    firstFound = 3;
                }
                digit++;
            }
            // if(firstFound == -1) {
            //     firstFound = 1;
            // }
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar3CornerCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar3CornerCoordinate = phase2Bar3CornerCoordinate + 56 * firstFound;

    return phase2Bar3EdgeCoordinate * 336 + phase2Bar3CornerCoordinate ;
}

/**
* Calculates a number in the range [0, (2 * (8 choose 2)) ^ 2]
* Each possible UDSlice partial permutation state maps to a unique ID
* @param stickerCube - Cube on facelet level
* @return phase 1 UDSlice partial permutation coordinate [0, (12 choose 4)]
*/
int StickerCube::getPhase2Bar4Coordinate() {
    
    // int phase2Bar4EdgeCoordinate = 0;

    // int** cubeState = this->getCubeState();

    // //  EDGES

    // // const int stickerCount = 12;
    // // const int primarySticker[] = { 1, 5, 7, 3, 1, 5, 7, 3, 3, 5, 3, 5 };
    // // const int primaryStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3, 4, 4, 5, 5 };
    // const int stickerCount = 8;
    // const int primaryEdgeSticker[] = { 7, 5, 1, 3, 7, 5, 1, 3 };
    // const int primaryEdgeStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    // // const int secondarySticker[] = { 1, 1, 1, 1, 7, 7, 7, 7, 5, 3, 5, 3 };
    // // const int secondaryStickerSide[] = { 5, 2, 4, 1, 4, 2, 5, 1, 1, 2, 2, 1 };
    // const int secondaryEdgeSticker[] = { 1, 1, 1, 1, 7, 7, 7, 7 };
    // const int secondaryEdgeStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    // const int goalEdgeSticker1PrimarySide = 3;
    // const int goalEdgeSticker1SecondarySide = 4;

    // const int goalEdgeSticker2PrimarySide = 3;
    // const int goalEdgeSticker2SecondarySide = 1;

    // int firstFound = -1;
    // bool positions[8];
    // for (int i = 0; i < stickerCount; i++) {
    //     positions[i] = 0;
    // }
    // for (int i = 0; i < stickerCount; i++) {

    //     int sticker1 = cubeState[primaryEdgeStickerSide[i]][primaryEdgeSticker[i]];
    //     int sticker2 = cubeState[secondaryEdgeStickerSide[i]][secondaryEdgeSticker[i]];

    //     if ( (goalEdgeSticker1PrimarySide == sticker1 && goalEdgeSticker1SecondarySide == sticker2)
    //         || (goalEdgeSticker1PrimarySide == sticker2 && goalEdgeSticker1SecondarySide == sticker1)) {
    //         if(firstFound == -1) {
    //             firstFound = 0;
    //         }
    //         positions[i] = true;
    //     }
    //     else if ( (goalEdgeSticker2PrimarySide == sticker1 && goalEdgeSticker2SecondarySide == sticker2)
    //         || (goalEdgeSticker2PrimarySide == sticker2 && goalEdgeSticker2SecondarySide == sticker1)) {
    //         if(firstFound == -1) {
    //             firstFound = 1;
    //         }
    //         positions[i] = true;
    //     }
    // }

    // for (int n = 0, k = -1; n < stickerCount; n++) {
    //     if (positions[n]) {
    //         k++;
    //     }
    //     else if (k != -1) {
    //         phase2Bar4EdgeCoordinate += CubeMath::choose(n, k);
    //     }
    // }
    // phase2Bar4EdgeCoordinate = phase2Bar4EdgeCoordinate + 28 * firstFound;

    // //  Corners
    // int phase2Bar4CornerCoordinate = 0;
    // const int primaryCornerSticker[] = { 6, 8, 2, 0, 6, 8, 2, 0 };
    // const int primaryCornerStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    // const int secondaryCornerSticker[] = { 0, 0, 0, 0, 8, 8, 8, 8 };
    // const int secondaryCornerStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    // const int thirdCornerSticker[] = { 2, 2, 2, 2, 6, 6, 6, 6 };
    // const int thirdCornerStickerSide[] = { 1, 4, 2, 5, 1, 5, 2, 4 };

    // const int goalCornerSticker1PrimarySide = 3;
    // const int goalCornerSticker1SecondarySide = 4;
    // const int goalCornerSticker1ThirdSide = 2;

    // const int goalCornerSticker2PrimarySide = 3;
    // const int goalCornerSticker2SecondarySide = 1;
    // const int goalCornerSticker2ThirdSide = 4;

    // const int goalCornerSticker3PrimarySide = 3;
    // const int goalCornerSticker3SecondarySide = 5;
    // const int goalCornerSticker3ThirdSide = 1;
    // firstFound = -1;
    // int digit = 0;
    // for (int i = 0; i < stickerCount; i++) {
    //     positions[i] = 0;
    // }
    // for (int i = 0; i < stickerCount; i++) {

    //     int sticker1 = cubeState[primaryCornerStickerSide[i]][primaryCornerSticker[i]];
    //     int sticker2 = cubeState[secondaryCornerStickerSide[i]][secondaryCornerSticker[i]];
    //     int sticker3 = cubeState[thirdCornerStickerSide[i]][thirdCornerSticker[i]];

        
    //     if(sticker1 == goalCornerSticker1PrimarySide 
    //         && sticker2 == goalCornerSticker1SecondarySide
    //         && sticker3 == goalCornerSticker1ThirdSide) {
    //         if(digit == 0) {
    //             firstFound = 0;
    //             digit++;
    //         }
    //         else if(digit == 1) {
    //             digit++;
    //         }
    //         // if(firstFound == -1) {
    //         //     firstFound = 0;
    //         // }
    //         positions[i] = true;
    //     }
    //     else if(sticker1 == goalCornerSticker2PrimarySide 
    //         && sticker2 == goalCornerSticker2SecondarySide
    //         && sticker3 == goalCornerSticker2ThirdSide) {
    //         if(digit == 0) {
    //             firstFound = 2;
    //             digit++;
    //         }
    //         else if(digit == 1) {
    //             if(firstFound == 4) {
    //                 firstFound = 5;
    //             }
    //             digit++;
    //         }
    //         // if(firstFound == -1) {
    //         //     firstFound = 1;
    //         // }
    //         positions[i] = true;
    //     }
    //     else if(sticker1 == goalCornerSticker3PrimarySide 
    //         && sticker2 == goalCornerSticker3SecondarySide
    //         && sticker3 == goalCornerSticker3ThirdSide) {
    //         if(digit == 0) {
    //             firstFound = 4;
    //             digit++;
    //         }
    //         else if(digit == 1) {
    //             if(firstFound == 0) {
    //                 firstFound = 1;
    //             } else if(firstFound == 2) {
    //                 firstFound = 3;
    //             }
    //             digit++;
    //         }
    //         // if(firstFound == -1) {
    //         //     firstFound = 1;
    //         // }
    //         positions[i] = true;
    //     }
    // }

    // for (int n = 0, k = -1; n < stickerCount; n++) {
    //     if (positions[n]) {
    //         k++;
    //     }
    //     else if (k != -1) {
    //         phase2Bar4CornerCoordinate += CubeMath::choose(n, k);
    //     }
    // }
    // phase2Bar4CornerCoordinate = phase2Bar4CornerCoordinate + 56 * firstFound;

    // return phase2Bar4EdgeCoordinate * 336 + phase2Bar4CornerCoordinate;

    int phase2Bar4EdgeCoordinate = 0;

    int** cubeState = this->getCubeState();

    //  EDGES
    const int stickerCount = 8;
    const int primaryEdgeSticker[] = { 7, 5, 1, 3, 7, 5, 1, 3 };
    const int primaryEdgeStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryEdgeSticker[] = { 1, 1, 1, 1, 7, 7, 7, 7 };
    const int secondaryEdgeStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int goalEdgeSticker1PrimarySide = 3;
    const int goalEdgeSticker1SecondarySide = 4;

    const int goalEdgeSticker2PrimarySide = 3;
    const int goalEdgeSticker2SecondarySide = 1;

    int edgePermutation[2];
    int permutationIndex = 0;
    bool positions[8];
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryEdgeStickerSide[i]][primaryEdgeSticker[i]];
        int sticker2 = cubeState[secondaryEdgeStickerSide[i]][secondaryEdgeSticker[i]];

        if ( goalEdgeSticker1PrimarySide == sticker1 && goalEdgeSticker1SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 0;
            permutationIndex++;
            positions[i] = true;
        }
        else if (goalEdgeSticker2PrimarySide == sticker1 && goalEdgeSticker2SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 1;
            permutationIndex++;
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar4EdgeCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar4EdgeCoordinate = phase2Bar4EdgeCoordinate + 28 * CubeMath::permuationCoordinate(edgePermutation, 2);

    //  Corners
    int phase2Bar4CornerCoordinate = 0;
    const int primaryCornerSticker[] = { 6, 8, 2, 0, 6, 8, 2, 0 };
    const int primaryCornerStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryCornerSticker[] = { 0, 0, 0, 0, 8, 8, 8, 8 };
    const int secondaryCornerStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int thirdCornerSticker[] = { 2, 2, 2, 2, 6, 6, 6, 6 };
    const int thirdCornerStickerSide[] = { 1, 4, 2, 5, 1, 5, 2, 4 };

    const int goalCornerSticker1PrimarySide = 3;
    const int goalCornerSticker1SecondarySide = 4;
    const int goalCornerSticker1ThirdSide = 2;

    const int goalCornerSticker2PrimarySide = 3;
    const int goalCornerSticker2SecondarySide = 1;
    const int goalCornerSticker2ThirdSide = 4;

    const int goalCornerSticker3PrimarySide = 3;
    const int goalCornerSticker3SecondarySide = 5;
    const int goalCornerSticker3ThirdSide = 1;
    
    int cornerPermutation[3];
    permutationIndex = 0;
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryCornerStickerSide[i]][primaryCornerSticker[i]];
        int sticker2 = cubeState[secondaryCornerStickerSide[i]][secondaryCornerSticker[i]];
        int sticker3 = cubeState[thirdCornerStickerSide[i]][thirdCornerSticker[i]];

        
        if(sticker1 == goalCornerSticker1PrimarySide 
            && sticker2 == goalCornerSticker1SecondarySide
            && sticker3 == goalCornerSticker1ThirdSide) {
            cornerPermutation[permutationIndex] = 0;
            permutationIndex++;
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker2PrimarySide 
            && sticker2 == goalCornerSticker2SecondarySide
            && sticker3 == goalCornerSticker2ThirdSide) {
            cornerPermutation[permutationIndex] = 1;
            permutationIndex++;
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker3PrimarySide 
            && sticker2 == goalCornerSticker3SecondarySide
            && sticker3 == goalCornerSticker3ThirdSide) {
            cornerPermutation[permutationIndex] = 2;
            permutationIndex++;
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar4CornerCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar4CornerCoordinate = phase2Bar4CornerCoordinate + 56 * CubeMath::permuationCoordinate(cornerPermutation, 3);

    return phase2Bar4EdgeCoordinate * 336 + phase2Bar4CornerCoordinate;
}

int StickerCube::getPhase2Side1Coordinate() {

    int phase2Bar4EdgeCoordinate = 0;

    int** cubeState = this->getCubeState();

    //  EDGES
    const int stickerCount = 8;
    const int primaryEdgeSticker[] = { 7, 5, 1, 3, 7, 5, 1, 3 };
    const int primaryEdgeStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryEdgeSticker[] = { 1, 1, 1, 1, 7, 7, 7, 7 };
    const int secondaryEdgeStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int goalEdgeSticker1PrimarySide = 3;
    const int goalEdgeSticker1SecondarySide = 4;

    const int goalEdgeSticker2PrimarySide = 3;
    const int goalEdgeSticker2SecondarySide = 1;

    const int goalEdgeSticker3PrimarySide = 3;
    const int goalEdgeSticker3SecondarySide = 5;

    const int goalEdgeSticker4PrimarySide = 3;
    const int goalEdgeSticker4SecondarySide = 2;

    int edgePermutation[4];
    int permutationIndex = 0;
    bool positions[8];
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryEdgeStickerSide[i]][primaryEdgeSticker[i]];
        int sticker2 = cubeState[secondaryEdgeStickerSide[i]][secondaryEdgeSticker[i]];

        if ( goalEdgeSticker1PrimarySide == sticker1 && goalEdgeSticker1SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 0;
            permutationIndex++;
            positions[i] = true;
        }
        else if (goalEdgeSticker2PrimarySide == sticker1 && goalEdgeSticker2SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 1;
            permutationIndex++;
            positions[i] = true;
        }
        else if (goalEdgeSticker3PrimarySide == sticker1 && goalEdgeSticker3SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 2;
            permutationIndex++;
            positions[i] = true;
        }
        else if (goalEdgeSticker4PrimarySide == sticker1 && goalEdgeSticker4SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 3;
            permutationIndex++;
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar4EdgeCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar4EdgeCoordinate = phase2Bar4EdgeCoordinate + 70 * CubeMath::permuationCoordinate(edgePermutation, 4);

    //  Corners
    int phase2Bar4CornerCoordinate = 0;
    const int primaryCornerSticker[] = { 6, 8, 2, 0, 6, 8, 2, 0 };
    const int primaryCornerStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryCornerSticker[] = { 0, 0, 0, 0, 8, 8, 8, 8 };
    const int secondaryCornerStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int thirdCornerSticker[] = { 2, 2, 2, 2, 6, 6, 6, 6 };
    const int thirdCornerStickerSide[] = { 1, 4, 2, 5, 1, 5, 2, 4 };

    const int goalCornerSticker1PrimarySide = 3;
    const int goalCornerSticker1SecondarySide = 4;
    const int goalCornerSticker1ThirdSide = 2;

    const int goalCornerSticker2PrimarySide = 3;
    const int goalCornerSticker2SecondarySide = 1;
    const int goalCornerSticker2ThirdSide = 4;

    const int goalCornerSticker3PrimarySide = 3;
    const int goalCornerSticker3SecondarySide = 5;
    const int goalCornerSticker3ThirdSide = 1;

    const int goalCornerSticker4PrimarySide = 3;
    const int goalCornerSticker4SecondarySide = 2;
    const int goalCornerSticker4ThirdSide = 5;
    
    int cornerPermutation[4];
    permutationIndex = 0;
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryCornerStickerSide[i]][primaryCornerSticker[i]];
        int sticker2 = cubeState[secondaryCornerStickerSide[i]][secondaryCornerSticker[i]];
        int sticker3 = cubeState[thirdCornerStickerSide[i]][thirdCornerSticker[i]];

        
        if(sticker1 == goalCornerSticker1PrimarySide 
            && sticker2 == goalCornerSticker1SecondarySide
            && sticker3 == goalCornerSticker1ThirdSide) {
            cornerPermutation[permutationIndex] = 0;
            permutationIndex++;
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker2PrimarySide 
            && sticker2 == goalCornerSticker2SecondarySide
            && sticker3 == goalCornerSticker2ThirdSide) {
            cornerPermutation[permutationIndex] = 1;
            permutationIndex++;
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker3PrimarySide 
            && sticker2 == goalCornerSticker3SecondarySide
            && sticker3 == goalCornerSticker3ThirdSide) {
            cornerPermutation[permutationIndex] = 2;
            permutationIndex++;
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker4PrimarySide 
            && sticker2 == goalCornerSticker4SecondarySide
            && sticker3 == goalCornerSticker4ThirdSide) {
            cornerPermutation[permutationIndex] = 3;
            permutationIndex++;
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar4CornerCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar4CornerCoordinate = phase2Bar4CornerCoordinate + 70 * CubeMath::permuationCoordinate(cornerPermutation, 4);

    return phase2Bar4EdgeCoordinate * 1680 + phase2Bar4CornerCoordinate;

}

int StickerCube::getPhase2Side2Coordinate() {
    
    int phase2Bar4EdgeCoordinate = 0;

    int** cubeState = this->getCubeState();

    //  EDGES
    const int stickerCount = 8;
    const int primaryEdgeSticker[] = { 7, 5, 1, 3, 7, 5, 1, 3 };
    const int primaryEdgeStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryEdgeSticker[] = { 1, 1, 1, 1, 7, 7, 7, 7 };
    const int secondaryEdgeStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int goalEdgeSticker1PrimarySide = 0;
    const int goalEdgeSticker1SecondarySide = 4;

    const int goalEdgeSticker2PrimarySide = 0;
    const int goalEdgeSticker2SecondarySide = 2;

    const int goalEdgeSticker3PrimarySide = 0;
    const int goalEdgeSticker3SecondarySide = 5;

    const int goalEdgeSticker4PrimarySide = 0;
    const int goalEdgeSticker4SecondarySide = 1;

    int edgePermutation[4];
    int permutationIndex = 0;
    bool positions[8];
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryEdgeStickerSide[i]][primaryEdgeSticker[i]];
        int sticker2 = cubeState[secondaryEdgeStickerSide[i]][secondaryEdgeSticker[i]];

        if ( goalEdgeSticker1PrimarySide == sticker1 && goalEdgeSticker1SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 0;
            permutationIndex++;
            positions[i] = true;
        }
        else if (goalEdgeSticker2PrimarySide == sticker1 && goalEdgeSticker2SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 1;
            permutationIndex++;
            positions[i] = true;
        }
        else if (goalEdgeSticker3PrimarySide == sticker1 && goalEdgeSticker3SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 2;
            permutationIndex++;
            positions[i] = true;
        }
        else if (goalEdgeSticker4PrimarySide == sticker1 && goalEdgeSticker4SecondarySide == sticker2) {
            edgePermutation[permutationIndex] = 3;
            permutationIndex++;
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar4EdgeCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar4EdgeCoordinate = phase2Bar4EdgeCoordinate + 70 * CubeMath::permuationCoordinate(edgePermutation, 4);

    //  Corners
    int phase2Bar4CornerCoordinate = 0;
    const int primaryCornerSticker[] = { 6, 8, 2, 0, 6, 8, 2, 0 };
    const int primaryCornerStickerSide[] = { 0, 0, 0, 0, 3, 3, 3, 3 };

    const int secondaryCornerSticker[] = { 0, 0, 0, 0, 8, 8, 8, 8 };
    const int secondaryCornerStickerSide[] = { 4, 2, 5, 1, 5, 2, 4, 1 };

    const int thirdCornerSticker[] = { 2, 2, 2, 2, 6, 6, 6, 6 };
    const int thirdCornerStickerSide[] = { 1, 4, 2, 5, 1, 5, 2, 4 };

    const int goalCornerSticker1PrimarySide = 0;
    const int goalCornerSticker1SecondarySide = 4;
    const int goalCornerSticker1ThirdSide = 1;

    const int goalCornerSticker2PrimarySide = 0;
    const int goalCornerSticker2SecondarySide = 2;
    const int goalCornerSticker2ThirdSide = 4;

    const int goalCornerSticker3PrimarySide = 0;
    const int goalCornerSticker3SecondarySide = 5;
    const int goalCornerSticker3ThirdSide = 2;

    const int goalCornerSticker4PrimarySide = 0;
    const int goalCornerSticker4SecondarySide = 1;
    const int goalCornerSticker4ThirdSide = 5;
    
    int cornerPermutation[4];
    permutationIndex = 0;
    for (int i = 0; i < stickerCount; i++) {
        positions[i] = 0;
    }
    for (int i = 0; i < stickerCount; i++) {

        int sticker1 = cubeState[primaryCornerStickerSide[i]][primaryCornerSticker[i]];
        int sticker2 = cubeState[secondaryCornerStickerSide[i]][secondaryCornerSticker[i]];
        int sticker3 = cubeState[thirdCornerStickerSide[i]][thirdCornerSticker[i]];

        
        if(sticker1 == goalCornerSticker1PrimarySide 
            && sticker2 == goalCornerSticker1SecondarySide
            && sticker3 == goalCornerSticker1ThirdSide) {
            cornerPermutation[permutationIndex] = 0;
            permutationIndex++;
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker2PrimarySide 
            && sticker2 == goalCornerSticker2SecondarySide
            && sticker3 == goalCornerSticker2ThirdSide) {
            cornerPermutation[permutationIndex] = 1;
            permutationIndex++;
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker3PrimarySide 
            && sticker2 == goalCornerSticker3SecondarySide
            && sticker3 == goalCornerSticker3ThirdSide) {
            cornerPermutation[permutationIndex] = 2;
            permutationIndex++;
            positions[i] = true;
        }
        else if(sticker1 == goalCornerSticker4PrimarySide 
            && sticker2 == goalCornerSticker4SecondarySide
            && sticker3 == goalCornerSticker4ThirdSide) {
            cornerPermutation[permutationIndex] = 3;
            permutationIndex++;
            positions[i] = true;
        }
    }

    for (int n = 0, k = -1; n < stickerCount; n++) {
        if (positions[n]) {
            k++;
        }
        else if (k != -1) {
            phase2Bar4CornerCoordinate += CubeMath::choose(n, k);
        }
    }
    phase2Bar4CornerCoordinate = phase2Bar4CornerCoordinate + 70 * CubeMath::permuationCoordinate(cornerPermutation, 4);

    return phase2Bar4EdgeCoordinate * 1680 + phase2Bar4CornerCoordinate;
}