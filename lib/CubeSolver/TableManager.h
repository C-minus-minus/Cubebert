#pragma once
#include <iostream>
#include <queue>
#include "StickerCube.h"

class TableManager {

	public:

		TableManager();

        static TableManager* getInstance();

        //  Phase 1 move tables
        int** phase1EdgeMoveTable;
        int** phase1CornerMoveTable;
        int** phase1UdsliceMoveTable;

        //  Phase 1 pruning tables
        int* phase1EdgePruningTable;
        int* phase1CornerPruningTable;
        int* phase1UdslicePruningTable;

        //  Phase 2 move tables
        int** phase2EdgeMoveTable;
        int** phase2CornerMoveTable;
        int** phase2UdsliceMoveTable;

        //  Phase 2 pruning tables
        int* phase2EdgePruningTable;
        int* phase2CornerPruningTable;
        int* phase2UdslicePruningTable;
        static TableManager* instance;
    
    private:

        void generatePhase1MoveTables();
        void generatePhase1EdgeMoveTable(StickerCube* cube, int coord, int depth);
        void generatePhase1CornerMoveTable(StickerCube* cube, int coord, int depth);
        void generatePhase1UdsliceMoveTable(StickerCube* cube, int coord, int depth);

        void generatePhase2MoveTables();
        void generatePhase2EdgeMoveTable();
        void generatePhase2CornerMoveTable();
        void generatePhase2UdsliceMoveTable();

        void generatePhase1PruningTables();
        void generatePhase1EdgePruningTable();
        void generatePhase1CornerPruningTable();
        void generatePhase1UDSlicePruningTable();

        void generatePhase2PruningTables();
        void generatePhase2EdgePruningTable();
        void generatePhase2CornerPruningTable();
        void generatePhase2UDSlicePruningTable();

        class SearchNode {
            public:
                int depth, value;
                SearchNode(int depth, int value) {
                    this->depth = depth;
                    this->value = value;
                }
        };
};