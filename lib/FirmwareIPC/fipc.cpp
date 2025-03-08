#include "fipc.h"

#include "logger.h"

FIPC::FIPC() {
    m_i2cFile = open_i2c_device("/dev/i2c-1");
    if (!m_i2cFile) {
        Logger::instance()->error().message("Failed to open I2C device: " + std::string(get_i2c_error()));
    }
}

FIPC::~FIPC() {
    close_i2c_device(m_i2cFile);
}

void FIPC::home() {
    std::string homeInstruction = "Home";
    write_i2c(m_i2cFile, homeInstruction.c_str(), homeInstruction.length());

    //  Wait for the firmware to finish homing
    char buffer[1];
    read_i2c(m_i2cFile, buffer, 1);
    if (i2c_errno != I2C_NO_ERROR) {
        Logger::instance()->error().message("Failed to read from I2C device: " + std::string(get_i2c_error()));
    }
}

void FIPC::grab(std::string face) {
    std::string grabInstruction = "Grab," + face;
    write_i2c(m_i2cFile, grabInstruction.c_str(), grabInstruction.length());

    //  Wait for the firmware to finish grabbing
    char buffer[1];
    read_i2c(m_i2cFile, buffer, 1);
    if (i2c_errno != I2C_NO_ERROR) {
        Logger::instance()->error().message("Failed to read from I2C device: " + std::string(get_i2c_error()));
    }
}

void FIPC::rotate(std::string moves) {
    std::string rotationInstruction = "Rotate," + moves;
    write_i2c(m_i2cFile, rotationInstruction.c_str(), rotationInstruction.length());

    //  Wait for the firmware to finish rotating
    char buffer[1];
    read_i2c(m_i2cFile, buffer, 1);
    if (i2c_errno != I2C_NO_ERROR) {
        Logger::instance()->error().message("Failed to read from I2C device: " + std::string(get_i2c_error()));
    }
}