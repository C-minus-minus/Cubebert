#pragma once
#include <algorithm>
#include "StickerCube.h"
#include "CubeMath.h"
#include "TableManager.h"

/**
 * Cube Search handles the actual solving of the rubik's cube.
 * Solving the cube is a graph traversal problem. The goal is to
 * find a path from one node to another. The search algorithm
 * implemented is called iterative deepening A*.
 */ 
class CubeSearch {

    public:

        /**
         * Uses iterative deepening A* to find an algorithm to solve phase 1
         * @param scrambledCube - scrambled cube you want to solve
         * @return - Algorithm to solve phase 1 of the cube
         */
        static std::string getPhase1Solution(StickerCube* scrambledCube);

        /**
         * Uses iterative deepening A* to find an algorithm to solve phase 2
         * @param scrambledCube - cube state after phase 1 has been executed
         * @return - Algorithm to solve phase 2 of the cube
         */
        static std::string getPhase2Solution(StickerCube* scrambledCube);

        /**
         * Uses iterative deepening A* to find an algorithm to solve phase 2
         * @param scrambledCube - cube state after phase 1 has been executed
         * @return - Algorithm to solve phase 2 of the cube
         */
        static std::string getPhase2SolutionE(StickerCube* scrambledCube);

    private:

        /**
         * Checks to see if there is a solution to phase 1 at the specified depth
         * @param edgeCoord - phase 1 edge orientation coordinate
         * @param cornerCoord - phase 1 edge orientation coordinate
         * @param sliceCoord - phase 1 UDSlice partial permutation coordinate
         * @param goalDepth - The maximum depth we want to search this time through
         * @param currDepth - The current search depth
         * @param solution - empty vector to store the solution when we find it
         * @return - If it exists at this depth, this will return the algorithm to solve phase 1, returns an empty string otherwise
         */
        static bool phase1IterativeDeepeningAStar(TableManager *instance, int edgeCoord, int cornerCoord, int sliceCoord, int goalDepth, int currDepth, std::vector<std::string>* solution);
 
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
        static bool phase2IterativeDeepeningAStar(TableManager *instance, int edgeCoord, int cornerCoord, int sliceCoord, int goalDepth, int currDepth, std::vector<std::string>* solution);

        /**
         * Checks to see if there is a solution to phase 2 at the specified depth
         * @param edgeCoord - phase 2 edge orientation coordinate
         * @param cornerCoord - phase 2 edge orientation coordinate
         * @param sliceCoord - phase 2 UDSlice partial permutation coordinate
         * @param bar1Coord - phase 2 bar1 permutation coordinate
         * * @param bar2Coord - phase 2 bar1 permutation coordinate
         * * @param bar3Coord - phase 2 bar1 permutation coordinate
         * * @param bar4Coord - phase 2 bar1 permutation coordinate
         * @param goalDepth - The maximum depth we want to search this time through
         * @param currDepth - The current search depth
         * @param solution - empty vector to store the solution when we find it
         * @return - If it exists at this depth, this will return the algorithm to solve phase 2, returns an empty string otherwise
         */
        static bool phase2IterativeDeepeningAStarE(TableManager *instance, int edgeCoord, int cornerCoord, int sliceCoord, int bar1Coord, int bar2Coord, int bar3Coord, int bar4Coord, int goalDepth, int currDepth, std::vector<std::string>* solution);

};

