#include "fipc.h"

FIPC::FIPC() {
    m_i2cFile = open_i2c_device("/dev/i2c-1");
}

FIPC::~FIPC() {
    close_i2c_device(m_i2cFile);
}

void FIPC::home() {
    std::string homeInstruction = "Home";
    write_i2c(m_i2cFile, homeInstruction.c_str(), homeInstruction.length());
}

void FIPC::grab(std::string face) {
    std::string grabInstruction = "Grab," + face;
    write_i2c(m_i2cFile, grabInstruction.c_str(), grabInstruction.length());   
}

void FIPC::rotate(std::string moves) {
    std::string rotationInstruction = "Rotate," + moves;
    write_i2c(m_i2cFile, rotationInstruction.c_str(), rotationInstruction.length());
}