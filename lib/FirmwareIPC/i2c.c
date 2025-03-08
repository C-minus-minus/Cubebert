#include "i2c.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <stdint.h>

int i2c_errno = 0;

char *get_i2c_error() {
    switch (i2c_errno) {
        case 0:
            return "No error";
        case I2C_EIO:
            return "I/O error";
        case I2C_ENXIO:
            return "No such device or address";
        case I2C_EBUSY:
            return "Device or resource busy";
        case I2C_EAGAIN:
            return "Resource temporarily unavailable";
        default:
            return "Unknown error";
    }
}

FILE *open_i2c_device(const char *device) {
    FILE *file = fopen(device, "r+");
    if (!file) {
        i2c_errno = I2C_EIO;
        return NULL;
    }

    int file_desc = fileno(file);
    if (ioctl(file_desc, I2C_SLAVE, 0x42) < 0) {
        i2c_errno = I2C_ENXIO;
        fclose(file);
        return NULL;
    }

    return file;
}

void close_i2c_device(FILE *file) {
    fclose(file);
}

void write_i2c(FILE *file, const char *data, size_t length) {
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    messages[0].addr = 0x42;
    messages[0].flags = 0;
    messages[0].len = length;
    messages[0].buf = (uint8_t *)data;
    packets.msgs = messages;
    packets.nmsgs = 1;
    if (ioctl(fileno(file), I2C_RDWR, &packets) < 0) {
        i2c_errno = I2C_EIO;
        return;
    }

}

void read_i2c(FILE *file, char *buffer, size_t length) {
    // Read data from I2C device
    // buffer[0] = 0x00; // Register address to read from
    // if (write(file, buffer, 1) != 1) {
    //     printf("Failed to write to the i2c bus");
    //     close(file);
    //     return 1;
    // }

    if (read(fileno(file), buffer, length) != length) {
        i2c_errno = I2C_EIO;
        return;
    }
}