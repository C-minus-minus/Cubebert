#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int i2c_errno;

enum I2CError {
    I2C_NO_ERROR = 0,
    I2C_EIO = 1,
    I2C_ENXIO = 2,
    I2C_EBUSY = 3,
    I2C_EAGAIN = 4
};

char *get_i2c_error();

FILE *open_i2c_device(const char *device);
void close_i2c_device(FILE *file);
void write_i2c(FILE *file, const char *data, size_t length);
void read_i2c(FILE *file, char *buffer, size_t length);

#ifdef __cplusplus
}
#endif

#endif // I2C_H