#include "estimated_cube.h"

#include <iostream>
#include <fstream>

#define IMG_DIM 1920

EstimatedCube::EstimatedCube() {
    m_camera = new raspicam::RaspiCam();
    m_camera->setCaptureSize(IMG_DIM, IMG_DIM);
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

    std::ofstream outFile ( "cube.ppm",std::ios::binary );
    outFile<<"P6\n"<<m_camera->getWidth() <<" "<<m_camera->getHeight() <<" 255\n";
    outFile.write ( ( char* ) data, m_camera->getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );

    for(int i=0; i<m_camera->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB) / 3; i += 3) {
        ColorMath::RGB pixel;
        pixel.red = data[i];
        pixel.green = data[i+1];
        pixel.blue = data[i+2];

//        ColorMath::CIELAB *lab = ColorMath::rgb2CIE(pixel);
        //m_cieCubeSides[side]
    }

    delete data;
}
