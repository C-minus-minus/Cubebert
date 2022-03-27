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

private:
    raspicam::RaspiCam *m_camera;

    ColorMath::CIELAB *m_cieCubeSides[6];
};

#endif // ESTIMATED_CUBE_H
