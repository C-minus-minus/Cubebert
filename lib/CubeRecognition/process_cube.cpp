#include "process_cube.h"

#include "logger.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1920

#define SUBSAMPLE_WIDTH 64
#define SUBSAMPLE_HEIGHT 64
#define SUBSAMPLE_OFFSET_X 960
#define SUBSAMPLE_OFFSET_Y 960

ProcessCube::ProcessCube() {
}

ProcessCube::~ProcessCube() {
}

void ProcessCube::captureSide(int side) {
    Logger *logger = Logger::instance();

    std::string filename = "side_" + std::to_string(side) + ".rgb";
    std::string command = "rpicam-still --immediate -v 0 -e rgb -n -o " + filename + 
        " --width " + std::to_string(WIDTH) + 
        " --height " + std::to_string(HEIGHT) + 
        " -q 100 --autofocus-on-capture --mode 32:32:8:U";

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        logger->error().message("Error opening pipe");
        return;
    }
    
    // Close the pipe without reading output
    int result = pclose(pipe);
    if (result != 0) {
        logger->error().message("Error capturing image");
        return;
    }

    logger->info().message("Captured side " + std::to_string(side) + " to " + filename);

    // Read the file into a buffer
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if(!file) {
        logger->error().message("Error opening file: " + filename);
        return;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    char *data = new char[size];
    if(!file.read(data, size)) {
        logger->error().message("Error reading file: " + filename);
        delete[] data;
        return;
    }

    logger->info().message("Read " + std::to_string(size) + " bytes from " + filename);

    int pixelCount = WIDTH * HEIGHT;
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
    delete[] data;

    ColorMath::RGB ***imgObj = new ColorMath::RGB**[HEIGHT];
    for(int y=0; y<HEIGHT; ++y) {
        imgObj[y] = new ColorMath::RGB*[WIDTH];
        for(int x=0; x<WIDTH; ++x) {
            imgObj[y][x] = pixel1D[x + (y * HEIGHT)];
        }
    }

    logger->debug().message("Converted image to 2D array");
    logger->debug().message("Subsampling image...");
    for(int y=0; y<3; ++y) {
        for(int x=0; x<3; ++x) {
            ColorMath::CIELAB* sampleColor = ColorMath::subsample(
                imgObj,
                (x * SUBSAMPLE_OFFSET_X) - (SUBSAMPLE_WIDTH * x),
                (y * SUBSAMPLE_OFFSET_Y) - (SUBSAMPLE_HEIGHT * y),
                128, 128);
            m_cieCubeSides[side][x+(y*3)] = sampleColor;
            
            logger->debug().message("Subsampled side " + std::to_string(side) + " at (" + std::to_string(x) + ", " + std::to_string(y) + ") to (" +
                std::to_string(sampleColor->lStar) + ", " +
                std::to_string(sampleColor->aStar) + ", " +
                std::to_string(sampleColor->bStar) + ")");
        }
    }
    m_ciePalette[side] = m_cieCubeSides[side][4];
}

int** ProcessCube::zeCube() {
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