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

    int subPixelCount = m_camera->getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB);
    int pixelCount = subPixelCount / 3;
    int width = m_camera->getWidth();
    int height = m_camera->getHeight();

    unsigned char *data = new unsigned char[subPixelCount];
    m_camera->retrieve(data);

    //std::ofstream outFile("cube.ppm", std::ios::binary);
    //outFile << "P6\n" << width <<" "<< height << " 255\n";
    //outFile.write ((char*) data, subPixelCount);

    int pixelsProcessed = 0;
    ColorMath::RGB **pixel1D = new ColorMath::RGB*[pixelCount];
    for(int i=0; i < subPixelCount; i += 3) {
        ColorMath::RGB *pixel = new ColorMath::RGB;
        pixel->red = data[i];
        pixel->green = data[i+1];
        pixel->blue = data[i+2];

        pixel1D[pixelsProcessed] = pixel;
        ++pixelsProcessed;
    }

    // We're done with our RAW values
    delete data;

    ColorMath::RGB ***imgObj = new ColorMath::RGB**[width];
    for(int x=0; x<width; ++x) {
        imgObj[x] = new ColorMath::RGB*[height];
        for(int y=0; y<height; ++y) {
            imgObj[x][y] = pixel1D[(x * width) + y];
        }
    }

    ColorMath::RGB* testColor = ColorMath::subsample(imgObj, 0, 0);
    std::cout << "Red: " << (int)testColor->red << '\n';
    std::cout << "Green: " << (int)testColor->green << '\n';
    std::cout << "Blue: " << (int)testColor->blue << '\n';
}
