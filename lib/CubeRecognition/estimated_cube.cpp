#include "estimated_cube.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>

#define IMG_DIM 1920

EstimatedCube::EstimatedCube() {
    m_camera = new raspicam::RaspiCam();
    m_camera->setCaptureSize(IMG_DIM, IMG_DIM);
    m_camera->setRotation(90);
    m_camera->setISO(100);
    m_camera->setBrightness(44);
    m_camera->setSaturation(-10);
    m_camera->setAWB(raspicam::RASPICAM_AWB::RASPICAM_AWB_SUNLIGHT);
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

    std::string filepath;
    filepath += "cube";
    filepath += std::to_string(side);
    filepath += ".ppm";
    std::ofstream outFile(filepath, std::ios::binary);
    outFile << "P6\n" << width <<" "<< height << " 255\n";
    outFile.write((char*)data, subPixelCount);
    outFile.close();

    int pixelsProcessed = 0;
    ColorMath::RGB **pixel1D = new ColorMath::RGB*[pixelCount];
    for(int i=0; pixelsProcessed < pixelCount; i += 3) {
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

    std::cout << "Side[" << side << "] CIEL*A*B* Values\n";
    std::cout << std::fixed << std::setprecision(4);
    for(int y=0; y<3; ++y) {
        for(int x=0; x<3; ++x) {
            ColorMath::CIELAB* sampleColor = ColorMath::subsample(imgObj, (x * 960) - (64 * x), (y * 960) - (64 * y), 128, 128);
            m_cieCubeSides[side][x+(y*3)] = sampleColor;
            
            std::cout << '(' << sampleColor->lStar << ", " << sampleColor->aStar << ", " << sampleColor->bStar << ")\t";
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";

    m_ciePalette[side] = m_cieCubeSides[side][4];
}

int** EstimatedCube::zeCube() {
    int **outCube = new int*[6];

    auto matchColor = [](ColorMath::CIELAB* cielab, ColorMath::CIELAB** ref) {
        double lowest = ColorMath::deltaE(cielab, ref[0]);
        int lowestIdx = 0;
        for(int i=1; i<6; ++i) {
            double dE = ColorMath::deltaE(cielab, ref[i]);
            if(dE < lowest) {
                lowest = dE;
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
