#ifndef CUBEBERT_H
#define CUBEBERT_H

#include "fipc.h"
#include "logger.h"
#include "process_cube.h"
#include "table_manager.h"
#include "cube_search.h"

class Cubebert {
public:
    Cubebert();
    ~Cubebert();

    void solve();

private:
    Logger* m_logger;

    FIPC* m_fipc;
    TableManager* m_tableManager;
    CubeSearch* m_cubeSearch;
    ProcessCube* m_processCube;
};

#endif