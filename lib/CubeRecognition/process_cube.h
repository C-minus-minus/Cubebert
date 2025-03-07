#ifndef PROCESS_CUBE_H
#define PROCESS_CUBE_H

#include "color_math.h"

class ProcessCube {
public:
    ProcessCube();
    ~ProcessCube();

    void captureSide(int side);

    int** zeCube(); 

private:
    ColorMath::CIELAB *m_ciePalette[6];
    ColorMath::CIELAB *m_cieCubeSides[6][9];
};

#endif // ESTIMATED_CUBE_H