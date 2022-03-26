#ifndef ESTIMATED_CUBE_H
#define ESTIMATED_CUBE_H

#include <raspicam/raspicam.h>

class EstimatedCube {
public:
    EstimatedCube();
    ~EstimatedCube();

    void beginCapture();
    void endCapture();
    void captureSide();
private:
    raspicam::RaspiCam *m_camera;
};

#endif // ESTIMATED_CUBE_H
