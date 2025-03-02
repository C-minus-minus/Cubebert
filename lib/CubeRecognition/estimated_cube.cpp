#include "estimated_cube.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>

#define WIDTH 640
#define HEIGHT 640

EstimatedCube::EstimatedCube() : LibcameraApp() {
    // Initialize camera manager
    if (!camera_manager_) {
        std::cerr << "Failed to initialize camera manager" << std::endl;
        return;
    }

    // Configure camera settings through options
    Options options;
    options.width = WIDTH;
    options.height = HEIGHT;
    options.iso = 100;
    options.brightness = 0.44;  // Scale 0-1.0
    options.rotation = 90;
    
    // Set camera configuration
    configure(options);
}

EstimatedCube::~EstimatedCube() {
    endCapture();
}

void EstimatedCube::beginCapture() {
    // Start the camera
    if (start()) {
        std::cerr << "Failed to start camera" << std::endl;
        return;
    }
}

void EstimatedCube::endCapture() {
    stop();
}

void EstimatedCube::captureSide(int side) {
    // Capture a frame
    CompletedRequestPtr result = wait_for_request();
    if (!result) {
        std::cerr << "Failed to capture image" << std::endl;
        return;
    }

    // Get the RGB buffer
    const Stream *stream = app_.GetMainStream();
    const StreamInfo &info = app_.GetStreamInfo(stream);
    libcamera::Span<uint8_t> buffer = result->buffers[stream].data();

    // Convert buffer to RGB format
    unsigned char *data = new unsigned char[WIDTH * HEIGHT * 3];
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int yIndex = y * info.width + x;
            int uIndex = (y / 2) * (info.width / 2) + (x / 2);
            int vIndex = (y / 2) * (info.width / 2) + (x / 2);

            int Y = buffer[yIndex];
            int U = buffer[info.planes[0].length + uIndex] - 128;
            int V = buffer[info.planes[0].length + info.planes[1].length + vIndex] - 128;

            int R = Y + 1.402 * V;
            int G = Y - 0.344136 * U - 0.714136 * V;
            int B = Y + 1.772 * U;

            data[(y * IMG_DIM + x) * 3]     = std::clamp(R, 0, 255);
            data[(y * IMG_DIM + x) * 3 + 1] = std::clamp(G, 0, 255);
            data[(y * IMG_DIM + x) * 3 + 2] = std::clamp(B, 0, 255);
        }
    }

    // Save image and process colors
    std::string filepath = "cube" + std::to_string(side) + ".ppm";
    std::ofstream outFile(filepath, std::ios::binary);
    outFile << "P6\n" << IMG_DIM << " " << IMG_DIM << " 255\n";
    outFile.write((char*)data, IMG_DIM * IMG_DIM * 3);
    outFile.close();

    // Process the image data similarly to before
    int pixelCount = IMG_DIM * IMG_DIM;
    int pixelsProcessed = 0;
    ColorMath::RGB **pixel1D = new ColorMath::RGB*[pixelCount];
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
