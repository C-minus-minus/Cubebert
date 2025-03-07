#include "fipc.h"

FIPC::FIPC() {
    m_i2cFile = open_i2c_device("/dev/i2c-1");
}

FIPC::~FIPC() {
    close_i2c_device(m_i2cFile);
}

void FIPC::home() {
    uint8_t data[1] = { 0x00 };
    write_i2c(m_i2cFile, data, 1);
}

void FIPC::grab(std::string face) {
    uint8_t data[1] = { 0x01 };
    write_i2c(m_i2cFile, data, 1);
}

void FIPC::rotate(std::string moves) {
    uint8_t data[2] = { 0x02, static_cast<uint8_t>(moves[0]) };
    write_i2c(m_i2cFile, data, 2);
}