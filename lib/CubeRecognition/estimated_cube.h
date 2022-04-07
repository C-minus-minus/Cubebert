#ifndef ESTIMATED_CUBE_H
#define ESTIMATED_CUBE_H

#include "color_math.h"

#include <raspicam/raspicam.h>

class EstimatedCube {
public:
    EstimatedCube();
    ~EstimatedCube();

    void beginCapture();
    void endCapture();
    void captureSide(int side);

    int** zeCube(); 

private:
    raspicam::RaspiCam *m_camera;

    ColorMath::CIELAB *m_ciePalette[6];
    ColorMath::CIELAB *m_cieCubeSides[6][9];
};

#endif // ESTIMATED_CUBE_H
