#ifndef TABLE_MANAGER_H
#define TABLE_MANAGER_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include "sticker_cube.h"
#include <fstream>

class TableManager {

	public:
        void generateTables();
        void writeTablesToFile();
        void readTablesFromFile();

         //  FILE FLAGS
        static const bool WRITE_TABLES_TO_FILE;
        static const bool READ_TABLES_FROM_FILE;

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
        int** phase2Side1MoveTable;
        int** phase2Side2MoveTable;

        //  Phase 2 pruning tables
        int* phase2EdgePruningTable;
        int* phase2CornerPruningTable;
        int* phase2UdslicePruningTable;
        int* phase2Side1PruningTable;
        int* phase2Side2PruningTable;
        
        static TableManager* instance;
    
    private:

        //  Generation of phase 1 move tables
        void generatePhase1MoveTables();
        void generatePhase1EdgeMoveTable(StickerCube* cube, int coord, int depth);
        void generatePhase1CornerMoveTable(StickerCube* cube, int coord, int depth);
        void generatePhase1UdsliceMoveTable(StickerCube* cube, int coord, int depth);

        //  Generation of phase 2 move tables
        void generatePhase2MoveTables();
        void generatePhase2EdgeMoveTable();
        void generatePhase2CornerMoveTable();
        void generatePhase2UdsliceMoveTable();
        void generatePhase2Side1MoveTable();
        void generatePhase2Side2MoveTable();

        //  Generation of phase 1 prunning tables
        void generatePhase1PruningTables();
        void generatePhase1EdgePruningTable();
        void generatePhase1CornerPruningTable();
        void generatePhase1UDSlicePruningTable();

        //  Generation of phase 2 prunning tables
        void generatePhase2PruningTables();
        void generatePhase2EdgePruningTable();
        void generatePhase2CornerPruningTable();
        void generatePhase2UDSlicePruningTable();
        void generatePhase2Side1PruningTable();
        void generatePhase2Side2PruningTable();

        //  writes move and prunning tables to file
        void writeMoveTablesToFile();
        void writeMoveTableToFile(std::string fileName, int** moveTable, int size, int moveCount);
        void writePruningTablesToFile();
        void writePruningTableToFile(std::string fileName, int* pruningTable, int size);
        
        //  reads move and prunning tables from file
        void readMoveTablesFromFile();
        void readMoveTableFromFile(std::string fileName, int*** moveTable, int size, int moveCount);
        void readPruningTablesFromFile();
        void readPruningTableFromFile(std::string fileName, int** prunningTable, int size);

        //  Used in BFS when generating prunning tables
        class SearchNode {
            public:
                int depth, value;
                SearchNode(int depth, int value) {
                    this->depth = depth;
                    this->value = value;
                }
        };
};

#endif // TABLE_MANAGER_H
