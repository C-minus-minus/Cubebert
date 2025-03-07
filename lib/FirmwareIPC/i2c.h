#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

FILE *open_i2c_device(const char *device);
void close_i2c_device(FILE *file);
void write_i2c(FILE *file, const char *data, size_t length);
void read_i2c(FILE *file, const char *buffer, size_t length);

#ifdef __cplusplus
}
#endif

#endif // I2C_H