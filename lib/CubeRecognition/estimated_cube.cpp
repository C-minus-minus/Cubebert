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

void EstimatedCube::captureSide() {
    m_camera->grab();
    unsigned char *data = new unsigned char[m_camera->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
    m_camera->retrieve(data);
    std::ofstream outFile ( "raspicam_image.ppm",std::ios::binary );
    outFile << "P6\n" << m_camera->getWidth() << " " << m_camera->getHeight() << " 255\n";
    outFile.write ( ( char* ) data, m_camera->getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ) );
    delete data;
}
