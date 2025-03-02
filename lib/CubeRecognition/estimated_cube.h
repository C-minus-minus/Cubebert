#ifndef ESTIMATED_CUBE_H
#define ESTIMATED_CUBE_H

#include "color_math.h"
#include <libcamera/libcamera.h>

class EstimatedCube :public libcamera::LibcameraApp {
public:
    EstimatedCube();
    ~EstimatedCube();

    void beginCapture();
    void endCapture();
    void captureSide(int side);

    int** zeCube(); 

private:
    std::unique_ptr<libcamera::Camera> m_camera;
    libcamera::Stream *m_stream;
    std::unique_ptr<libcamera::Request> m_request;


    ColorMath::CIELAB *m_ciePalette[6];
    ColorMath::CIELAB *m_cieCubeSides[6][9];
};

#endif // ESTIMATED_CUBE_H
