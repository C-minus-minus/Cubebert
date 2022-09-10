#pragma once
#include <iostream>
#include <queue>
#include <unordered_map>
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

        //  experimental move tables
        int** phase2Bar1MoveTable;
        int** phase2Bar2MoveTable;
        int** phase2Bar3MoveTable;
        int** phase2Bar4MoveTable;
        int** phase2Side1MoveTable;
        int** phase2Side2MoveTable;

        //  Phase 2 pruning tables
        int* phase2EdgePruningTable;
        int* phase2CornerPruningTable;
        int* phase2UdslicePruningTable;

        //  experimental prune tables
        int* phase2Bar1PruningTable;
        int* phase2Bar2PruningTable;
        int* phase2Bar3PruningTable;
        int* phase2Bar4PruningTable;
        int* phase2Side1PruningTable;
        int* phase2Side2PruningTable;
        
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
        void generatePhase2Bar1MoveTable(StickerCube* cube, int coord, int depth);
        void generatePhase2Bar2MoveTable(StickerCube* cube, int coord, int depth);
        void generatePhase2Bar3MoveTable(StickerCube* cube, int coord, int depth);
        void generatePhase2Bar4MoveTable(StickerCube* cube, int coord, int depth);
        void generatePhase2Side1MoveTable();
        void generatePhase2Side2MoveTable();

        void generatePhase1PruningTables();
        void generatePhase1EdgePruningTable();
        void generatePhase1CornerPruningTable();
        void generatePhase1UDSlicePruningTable();

        void generatePhase2PruningTables();
        void generatePhase2EdgePruningTable();
        void generatePhase2CornerPruningTable();
        void generatePhase2UDSlicePruningTable();
        void generatePhase2Bar1PruningTable();
        void generatePhase2Bar2PruningTable();
        void generatePhase2Bar3PruningTable();
        void generatePhase2Bar4PruningTable();
        void generatePhase2Side1PruningTable();
        void generatePhase2Side2PruningTable();

        class SearchNode {
            public:
                int depth, value;
                SearchNode(int depth, int value) {
                    this->depth = depth;
                    this->value = value;
                }
        };
};