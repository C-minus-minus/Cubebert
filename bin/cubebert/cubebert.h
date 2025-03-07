#ifndef CUBEBERT_H
#define CUBEBERT_H

#include "fipc.h"
#include "process_cube.h"
#include "TableManager.h"

class Cubebert {
public:
    Cubebert();
    ~Cubebert();

    void solve();

private:
    FIPC* m_fipc;
    TableManager* m_tableManager;
    ProcessCube* m_processCube;
};

#endif