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
            TableManager::getInstance(),
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
bool CubeSearch::phase1IterativeDeepeningAStar(TableManager *instance, int edgeCoord, int cornerCoord, int sliceCoord, int goalDepth, int currDepth, std::vector<std::string>* solution) {
    //  calculate a lower bound for the amount of moves it will take to solve from here
    int lowerBound = std::max(
        instance->phase1EdgePruningTable[edgeCoord],
        std::max(
            instance->phase1CornerPruningTable[cornerCoord],
            instance->phase1UdslicePruningTable[sliceCoord]
        )
    );

    //  if it's still possible to solve phase 1 before we reach our goal depth
    if (currDepth + lowerBound <= goalDepth) {

        //  try all moves
        for (int move = 0; move < CubeConstants::PHASE_1_MOVE_COUNT; move++) {

            //  calculate new cube state after move
            int currEdge = instance->phase1EdgeMoveTable[edgeCoord][move];
            int currCorner = instance->phase1CornerMoveTable[cornerCoord][move];
            int currSlice = instance->phase1UdsliceMoveTable[sliceCoord][move];

            //  check if we solved the cube, else dive deeper
            if (currEdge == 0 && currCorner == 0 && currSlice == 0) {
                solution->push_back(CubeConstants::PHASE_1_MOVES[move]);
                return true;
            }
            else if(phase1IterativeDeepeningAStar(instance, currEdge, currCorner, currSlice, goalDepth, currDepth + 1, solution)) {
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
        //std::cout<<"Curr Phase 2 Depth: "<<goalDepth<<"\n";
        //  search for solution at this depth
        if(CubeSearch::phase2IterativeDeepeningAStar(
            TableManager::getInstance(),
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
bool CubeSearch::phase2IterativeDeepeningAStar(TableManager *instance, int edgeCoord, int cornerCoord, int sliceCoord, int goalDepth, int currDepth, std::vector<std::string>* solution) {
    //  calculate a lower bound for the amount of moves it will take to solve from here
    int lowerBound = std::max(
        instance->phase2EdgePruningTable[edgeCoord],
        std::max(
            instance->phase2CornerPruningTable[cornerCoord],
            instance->phase2UdslicePruningTable[sliceCoord]
        )
    );

    //  if it's still possible to solve phase 2 before we reach our goal depth
    if (currDepth + lowerBound <= goalDepth) {

        //  try all moves
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {

            //  calculate new cube state after move
            int currEdge = instance->phase2EdgeMoveTable[edgeCoord][move];
            int currCorner = instance->phase2CornerMoveTable[cornerCoord][move];
            int currSlice = instance->phase2UdsliceMoveTable[sliceCoord][move];

            //  check if we solved the cube, else dive deeper
            if (currEdge == 0 && currCorner == 0 && currSlice == 0) {
                solution->push_back(CubeConstants::PHASE_2_MOVES[move]);
                return true;
            }
            else if(phase2IterativeDeepeningAStar(instance, currEdge, currCorner, currSlice, goalDepth, currDepth + 1, solution)) {
                solution->push_back(CubeConstants::PHASE_2_MOVES[move]);
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
std::string CubeSearch::getPhase2SolutionE(StickerCube* scrambledCube) {

    //  Get raw phase 2 coordinates from cube state
    int phase2EdgeCoordinate = scrambledCube->getPhase2EdgeCoordinate();
    int phase2CornerCoordinate = scrambledCube->getPhase2CornerCoordinate();
    int phase2UDSliceCoordinate = scrambledCube->getPhase2UdsliceCoordinate();
    int phase2Bar1Coordinate = scrambledCube->getPhase2Bar1Coordinate();
    int phase2Bar2Coordinate = scrambledCube->getPhase2Bar2Coordinate();
    int phase2Bar3Coordinate = scrambledCube->getPhase2Bar3Coordinate();
    int phase2Bar4Coordinate = scrambledCube->getPhase2Bar4Coordinate();

    //  Incrementally check deeper and deeper into the search tree
    std::vector<std::string> solution;
    for (int goalDepth = 0; goalDepth < CubeConstants::MAX_PHASE_2_DEPTH; goalDepth++) {
        //std::cout<<"Curr Phase 2 Depth: "<<goalDepth<<"\n";

        //  search for solution at this depth
        if(CubeSearch::phase2IterativeDeepeningAStarE(
            TableManager::getInstance(),
            phase2EdgeCoordinate,
            phase2CornerCoordinate,
            phase2UDSliceCoordinate,
            phase2Bar1Coordinate,
            phase2Bar2Coordinate,
            phase2Bar3Coordinate,
            phase2Bar4Coordinate,
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
 * @param bar1Coord - phase 2 bar1 permutation coordinate
 * @param goalDepth - The maximum depth we want to search this time through
 * @param currDepth - The current search depth
 * @param solution - empty vector to store the solution when we find it
 * @return - If it exists at this depth, this will return the algorithm to solve phase 2, returns an empty string otherwise
 */
bool CubeSearch::phase2IterativeDeepeningAStarE(TableManager *instance, int edgeCoord, int cornerCoord, int sliceCoord, int bar1Coord, int bar2Coord, int bar3Coord, int bar4Coord, int goalDepth, int currDepth, std::vector<std::string>* solution) {
    //  calculate a lower bound for the amount of moves it will take to solve from here
    int lowerBound = std::max(
        instance->phase2EdgePruningTable[edgeCoord],
        std::max(
            instance->phase2CornerPruningTable[cornerCoord],
            std::max(
                instance->phase2UdslicePruningTable[sliceCoord],
                std::max(
                    instance->phase2Bar1PruningTable[bar1Coord],
                    std::max(
                        instance->phase2Bar2PruningTable[bar2Coord],
                        std::max(
                            instance->phase2Bar3PruningTable[bar3Coord],
                            instance->phase2Bar4PruningTable[bar4Coord]
                        )
                    )
                )
            )
        )
    );

    //  if it's still possible to solve phase 2 before we reach our goal depth
    if (currDepth + lowerBound <= goalDepth) {

        //  try all moves
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {

            //  calculate new cube state after move
            int currEdge = instance->phase2EdgeMoveTable[edgeCoord][move];
            int currCorner = instance->phase2CornerMoveTable[cornerCoord][move];
            int currSlice = instance->phase2UdsliceMoveTable[sliceCoord][move];
            int currBar1 = instance->phase2Bar1MoveTable[bar1Coord][move];
            int currBar2 = instance->phase2Bar2MoveTable[bar2Coord][move];
            int currBar3 = instance->phase2Bar3MoveTable[bar3Coord][move];
            int currBar4 = instance->phase2Bar4MoveTable[bar4Coord][move];

            //  check if we solved the cube, else dive deeper
            if (currEdge == 0 && currCorner == 0 && currSlice == 0) {
                solution->push_back(CubeConstants::PHASE_2_MOVES[move]);
                return true;
            }
            else if(phase2IterativeDeepeningAStarE(instance, currEdge, currCorner, currSlice, currBar1, currBar2, currBar3, currBar4, goalDepth, currDepth + 1, solution)) {
                solution->push_back(CubeConstants::PHASE_2_MOVES[move]);
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
std::string CubeSearch::getPhase2SolutionF(StickerCube* scrambledCube) {

    //  Get raw phase 2 coordinates from cube state
    int phase2EdgeCoordinate = scrambledCube->getPhase2EdgeCoordinate();
    int phase2CornerCoordinate = scrambledCube->getPhase2CornerCoordinate();
    int phase2UDSliceCoordinate = scrambledCube->getPhase2UdsliceCoordinate();
    int phase2Side1Coordinate = scrambledCube->getPhase2Side1Coordinate();
    int phase2Side2Coordinate = scrambledCube->getPhase2Side2Coordinate();

    //  Incrementally check deeper and deeper into the search tree
    std::vector<std::string> solution;
    for (int goalDepth = 0; goalDepth < CubeConstants::MAX_PHASE_2_DEPTH; goalDepth++) {
        //std::cout<<"Curr Phase 2 Depth: "<<goalDepth<<"\n";

        //  search for solution at this depth
        if(CubeSearch::phase2IterativeDeepeningAStarF(
            TableManager::getInstance(),
            phase2EdgeCoordinate,
            phase2CornerCoordinate,
            phase2UDSliceCoordinate,
            phase2Side1Coordinate,
            phase2Side2Coordinate,
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
 * @param bar1Coord - phase 2 bar1 permutation coordinate
 * @param goalDepth - The maximum depth we want to search this time through
 * @param currDepth - The current search depth
 * @param solution - empty vector to store the solution when we find it
 * @return - If it exists at this depth, this will return the algorithm to solve phase 2, returns an empty string otherwise
 */
bool CubeSearch::phase2IterativeDeepeningAStarF(TableManager *instance, int edgeCoord, int cornerCoord, int sliceCoord, int side1Coord, int side2Coord, int goalDepth, int currDepth, std::vector<std::string>* solution) {
    //  calculate a lower bound for the amount of moves it will take to solve from here
    int lowerBound = std::max(
        instance->phase2EdgePruningTable[edgeCoord],
        std::max(
            instance->phase2CornerPruningTable[cornerCoord],
            std::max(
                instance->phase2UdslicePruningTable[sliceCoord],
                std::max(
                    instance->phase2Side1PruningTable[side1Coord],
                    instance->phase2Side2PruningTable[side2Coord]
                )
            )
        )
    );

    //  if it's still possible to solve phase 2 before we reach our goal depth
    if (currDepth + lowerBound <= goalDepth) {

        //  try all moves
        for (int move = 0; move < CubeConstants::PHASE_2_MOVE_COUNT; move++) {

            //  calculate new cube state after move
            int currEdge = instance->phase2EdgeMoveTable[edgeCoord][move];
            int currCorner = instance->phase2CornerMoveTable[cornerCoord][move];
            int currSlice = instance->phase2UdsliceMoveTable[sliceCoord][move];
            int currSide1 = instance->phase2Side1MoveTable[side1Coord][move];
            int currSide2 = instance->phase2Side2MoveTable[side2Coord][move];

            //  check if we solved the cube, else dive deeper
            if (currEdge == 0 && currCorner == 0 && currSlice == 0) {
                solution->push_back(CubeConstants::PHASE_2_MOVES[move]);
                return true;
            }
            else if(phase2IterativeDeepeningAStarF(instance, currEdge, currCorner, currSlice, currSide1, currSide2, goalDepth, currDepth + 1, solution)) {
                solution->push_back(CubeConstants::PHASE_2_MOVES[move]);
                return true;
            }
        }
    }
    return false;
}
