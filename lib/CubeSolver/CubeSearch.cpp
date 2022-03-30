#include "CubeSearch.h"

/**
* Uses iterative deepening A* to find an algorithm to solve phase 1
* @param scrambledCube - scrambled cube you want to solve
* @return - Algorithm to solve phase 1 of the cube
*/
std::string CubeSearch::getPhase1Solution(StickerCube* scrambledCube) {

    //  Get raw phase 1 coordinates from cube state
    int phase1EdgeCoordinate = scrambledCube->getPhase1EdgeCoordinate();
    int phase1CornerCoordinate = scrambledCube->getPhase1CornerCoordinate();
    int phase1UDSliceCoordinate = scrambledCube->getPhase1UdsliceCoordinate(); 

    //  Incrementally check deeper and deeper into the search tree
    std::vector<std::string> solution;
    for (int goalDepth = 0; goalDepth < CubeConstants::MAX_PHASE_1_DEPTH; goalDepth++) {

        //  search for solution at this depth
        if(CubeSearch::phase1IterativeDeepeningAStar(
            phase1EdgeCoordinate,
            phase1CornerCoordinate,
            phase1UDSliceCoordinate,
            goalDepth,
            0,
            &solution
        )) {
            break;
        }
    }

    std::string solutionString = "";
    for (int i = solution.size() - 1; i >= 0; i--) {
        solutionString += " " + solution[i];
    }
    return solutionString;
}

/**
* Checks to see if there is a solution to phase 1 at the specified depth
* @param edgeCoord - phase 1 edge orientation coordinate
* @param cornerCoord - phase 1 edge orientation coordinate
* @param sliceCoord - phase 1 UDSlice partial permutation coordinate
* @param goalDepth - The maximum depth we want to search this time through
* @param currDepth - The current search depth
* @param solution - empty vector to store the solution when we find it
* @return - If it exists at this depth, this will return the algorithm to solve phase 1, returns an empty string otherwise
**/
bool CubeSearch::phase1IterativeDeepeningAStar(int edgeCoord, int cornerCoord, int sliceCoord, int goalDepth, int currDepth, std::vector<std::string>* solution) {

    //  calculate a lower bound for the amount of moves it will take to solve from here
    int lowerBound = std::max(
        TableManager::getInstance()->phase1EdgePruningTable[edgeCoord],
        std::max(
            TableManager::getInstance()->phase1CornerPruningTable[cornerCoord],
            TableManager::getInstance()->phase1UdslicePruningTable[sliceCoord]
        )
    );

    //  if it's still possible to solve phase 1 before we reach our goal depth
    if (currDepth + lowerBound <= goalDepth) {

        //  try all moves
        for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {

            //  calculate new cube state after move
            int currEdge = TableManager::getInstance()->phase1EdgeMoveTable[edgeCoord][move];
            int currCorner = TableManager::getInstance()->phase1CornerMoveTable[cornerCoord][move];
            int currSlice = TableManager::getInstance()->phase1UdsliceMoveTable[sliceCoord][move];

            //  check if we solved the cube, else dive deeper
            if (currEdge == 0 && currCorner == 0 && currSlice == 0) {
                solution->push_back(CubeConstants::PHASE_1_MOVES[move]);
                return true;
            }
            else if(phase1IterativeDeepeningAStar(currEdge, currCorner, currSlice, goalDepth, currDepth + 1, solution)) {
                solution->push_back(CubeConstants::PHASE_1_MOVES[move]);
                return true;
            }
        }
    }
    return false;
}

/**
     * Uses iterative deepening A* to find an algorithm to solve phase 2
     * @param scrambledCube - cube state after phase 1 has been executed
     * @return - Algorithm to solve phase 2 of the cube
     */
std::string CubeSearch::getPhase2Solution(StickerCube* scrambledCube) {

    //  Get raw phase 2 coordinates from cube state
    int phase2EdgeCoordinate = scrambledCube->getPhase2EdgeCoordinate();
    int phase2CornerCoordinate = scrambledCube->getPhase2CornerCoordinate();
    int phase2UDSliceCoordinate = scrambledCube->getPhase2UdsliceCoordinate();

    //  Incrementally check deeper and deeper into the search tree
    std::vector<std::string> solution;
    for (int goalDepth = 0; goalDepth < CubeConstants::MAX_PHASE_2_DEPTH; goalDepth++) {

        //  search for solution at this depth
        if(CubeSearch::phase2IterativeDeepeningAStar(
            phase2EdgeCoordinate,
            phase2CornerCoordinate,
            phase2UDSliceCoordinate,
            goalDepth,
            0,
            &solution
        )) {
            break;
        }
    }


    std::string solutionString = "";
    for (int i = solution.size() - 1; i >= 0; i--) {
        solutionString += " " + solution[i];
    }
    return solutionString;
}

/**
 * Checks to see if there is a solution to phase 2 at the specified depth
 * @param edgeCoord - phase 2 edge orientation coordinate
 * @param cornerCoord - phase 2 edge orientation coordinate
 * @param sliceCoord - phase 2 UDSlice partial permutation coordinate
 * @param goalDepth - The maximum depth we want to search this time through
 * @param currDepth - The current search depth
 * @param solution - empty vector to store the solution when we find it
 * @return - If it exists at this depth, this will return the algorithm to solve phase 2, returns an empty string otherwise
 */
bool CubeSearch::phase2IterativeDeepeningAStar(int edgeCoord, int cornerCoord, int sliceCoord, int goalDepth, int currDepth, std::vector<std::string>* solution) {

    //  calculate a lower bound for the amount of moves it will take to solve from here
    int lowerBound = std::max(
        TableManager::getInstance()->phase2EdgePruningTable[edgeCoord],
        std::max(
            TableManager::getInstance()->phase2CornerPruningTable[cornerCoord],
            TableManager::getInstance()->phase2UdslicePruningTable[sliceCoord]
        )
    );

    //  if it's still possible to solve phase 2 before we reach our goal depth
    if (currDepth + lowerBound <= goalDepth) {

        //  try all moves
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {

            //  calculate new cube state after move
            int currEdge = TableManager::getInstance()->phase2EdgeMoveTable[edgeCoord][move];
            int currCorner = TableManager::getInstance()->phase2CornerMoveTable[cornerCoord][move];
            int currSlice = TableManager::getInstance()->phase2UdsliceMoveTable[sliceCoord][move];

            //  check if we solved the cube, else dive deeper
            if (currEdge == 0 && currCorner == 0 && currSlice == 0) {
                solution->push_back(CubeConstants::PHASE_2_MOVES[move]);
                return true;
            }
            else if(phase2IterativeDeepeningAStar(currEdge, currCorner, currSlice, goalDepth, currDepth + 1, solution)) {
                solution->push_back(CubeConstants::PHASE_2_MOVES[move]);
                return true;
            }
        }
    }
    return false;
}