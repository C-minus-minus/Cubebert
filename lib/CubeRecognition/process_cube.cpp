#include "process_cube.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>

#define WIDTH 1920
#define HEIGHT 1920

ProcessCube::ProcessCube() {
}

ProcessCube::~ProcessCube() {
}

void ProcessCube::captureSide(int side) {
    // Create a drop process that calls rpicam-still
    // to take a picture and save it to a file
    std::string filename = "side_" + std::to_string(side) + ".rgb";
    std::string command = "rpicam-still --immediate -e rgb -n -o " + filename + 
        " --width " + std::to_string(WIDTH) + 
        " --height " + std::to_string(HEIGHT) + 
        " -q 100 --autofocus-on-capture --mode 32:32:8:U";

    int result = system(command.c_str());
    if(result != 0) {
        std::cerr << "Error taking picture: " << result << '\n';
        return;
    }

    std::cout << "Captured side " << side << '\n';

    // Read the file into a buffer
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if(!file) {
        std::cerr << "Error opening file: " << filename << '\n';
        return;
    }

    std::cout << "Reading file " << filename << '\n';

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    char *data = new char[size];
    if(!file.read(data, size)) {
        std::cerr << "Error reading file: " << filename << '\n';
        return;
    }

    std::cout << "Processing file " << filename << '\n';

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
    delete data;

    std::cout << "Creating 2D array\n";

    ColorMath::RGB ***imgObj = new ColorMath::RGB**[HEIGHT];
    for(int y=0; y<HEIGHT; ++y) {
        imgObj[y] = new ColorMath::RGB*[WIDTH];
        for(int x=0; x<WIDTH; ++x) {
            imgObj[y][x] = pixel1D[x + (y * HEIGHT)];
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