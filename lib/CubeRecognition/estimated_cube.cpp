#include "estimated_cube.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>

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

    char* file;
    sprintf(file, "cube%d.ppm", side);
    std::ofstream outFile(file, std::ios::binary);
    outFile << "P6\n" << width <<" "<< height << " 255\n";
    outFile.write((char*) data, subPixelCount);

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

    ColorMath::RGB ***imgObj = new ColorMath::RGB**[height];
    for(int y=0; y<height; ++y) {
        imgObj[y] = new ColorMath::RGB*[width];
        for(int x=0; x<width; ++x) {
            imgObj[y][x] = pixel1D[x + (y * height)];
        }
    }

    for(int y=0; y<3; ++y) {
        for(int x=0; x<3; ++x) {
            ColorMath::RGB* testColor = ColorMath::subsample(imgObj, (x * 960) - (32 * x), (y * 960) - (32 * y));
            m_cieCubeSides[side][x+(y*3)] = ColorMath::rgb2cie(testColor);
            delete testColor;
        }
    }

    m_ciePalette[side] = m_cieCubeSides[side][5];
}

int** EstimatedCube::zeCube() {
    int **outCube = new int*[6];

    auto matchColor = [](ColorMath::CIELAB* cielab, ColorMath::CIELAB** ref) {
        int lowest = 2147483647;
        int lowestIdx = 2147483647;
        for(int i=0; i<6; ++i) {
            int deltaE = abs(ref[i]->lStar - cielab->lStar) + abs(ref[i]->aStar - cielab->aStar) + abs(ref[i]->bStar - cielab->bStar);
            if(deltaE < lowest) {
                lowest = deltaE;
                lowestIdx = i;
            }
        }
        return lowestIdx;
    };

    for(int side=0; side<6; ++side) {
        outCube[side] = new int[9];
        for(int cubie=0; cubie<9; ++cubie) {
            int color =  matchColor(m_cieCubeSides[side][cubie], m_ciePalette);
            outCube[side][cubie] = color;
        }
    }

    return outCube;
}
