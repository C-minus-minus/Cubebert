#pragma once
#include <iostream>
#include <map>

/**
 * Stores commonly used constants used in relation to the cube
 **/
class CubeConstants {
    
    public:

        //  Six sides on a cube with 9 stickers on each face
        static const int SIDE_COUNT;
        static const int STICKER_COUNT;

        //  Phase 1 will take at most 12 moves to complete, phase 2 could take up to 18
        static const int MAX_PHASE_1_DEPTH;
        static const int MAX_PHASE_2_DEPTH;

        //  Maximum coordinates possible for phase 1
        static const int PHASE_1_MAX_EDGE_COORDINATE;
        static const int PHASE_1_MAX_CORNER_COORDINATE;
        static const int PHASE_1_MAX_UDSLICE_COORDINATE;

        //  Maximum coordinates possible for phase 2
        static const int PHASE_2_MAX_EDGE_COORDINATE;
        static const int PHASE_2_MAX_CORNER_COORDINATE;
        static const int PHASE_2_MAX_UDSLICE_COORDINATE;
        static const int PHASE_2_MAX_BAR1_COORDINATE;

        //  Legal moves for phase 1
        static const int PHASE_1_MOVE_COUNT;
        static const std::string PHASE_1_MOVES[];
        static const std::string PHASE_1_ANTIMOVES[];
        static const std::string PHASE_1_X_ROTATE_MOVES[];
        static const std::string PHASE_1_Z_ROTATE_MOVES[];

        //  Legal moves for phase 2
        static const int PHASE_2_MOVE_COUNT;
        static const std::string PHASE_2_MOVES[];
        static const std::string PHASE_2_ANTIMOVES[];

        static int** createEdgeOrderTable();
        static int** EDGE_ORDER_TABLE;

        static int*** createCornerOrderTable();
        static int*** CORNER_ORDER_TABLE;

        static int** createUdsliceOrderTable();
        static int** UDSLICE_ORDER_TABLE;
};