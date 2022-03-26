#ifndef ESTIMATED_CUBE_H
#define ESTIMATED_CUBE_H

#define RASPISTILL_BIN "/usr/bin/raspistill"

class EstimatedCube {
public:
    EstimatedCube();
    ~EstimatedCube();

    void beginCapture();
    void captureSide();
private:
};

#endif // ESTIMATED_CUBE_H
