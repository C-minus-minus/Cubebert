#include "estimated_cube.h"

#include <iostream>
#include <fstream>

EstimatedCube::EstimatedCube() {
    m_camera = new raspicam::RaspiCam();
}

EstimatedCube::~EstimatedCube() {
    endCapture();
    delete m_camera;
}

void EstimatedCube::beginCapture() {
    m_camera->setFormat(raspicam::RASPICAM_FORMAT_RGB);
    m_camera->open();
}

void EstimatedCube::endCapture() {
    m_camera->release();
}

void EstimatedCube::captureSide(int side) {
    m_camera->grab();
    unsigned char *data = new unsigned char[m_camera->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    m_camera->retrieve(data);


    for(int i=0; i<m_camera->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB) / 3; i += 3) {
        RGB pixel;
        pixel.red = data[i];
        pixel.green = data[i+1];
        pixel.blue = data[i+2];

        CIELAB *lab = rgb2CIE(pixel);
        //m_cieCubeSides[side]
    }

    delete data;
}