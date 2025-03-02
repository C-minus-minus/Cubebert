#include "i2c.h"

#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <stdint.h>

FILE *open_i2c_device(const char *device) {
    FILE *file = fopen(device, "r+");
    if (!file) {
        printf("Failed to open I2C device\r\n");
        return NULL;
    }

    int file_desc = fileno(file);
    if (ioctl(file_desc, I2C_SLAVE, 0x42) < 0) {
        printf("Failed to acquire bus access and/or talk to slave\r\n");
        fclose(file);
        return NULL;
    }

    return file;
}

void close_i2c_device(FILE *file) {
    fclose(file);
}

void write_i2c(FILE *file, uint8_t *data, size_t length) {
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[1];

    messages[0].addr = 0x42;
    messages[0].flags = 0;
    messages[0].len = length;
    messages[0].buf = data;
    packets.msgs = messages;
    packets.nmsgs = 1;
    if (ioctl(fileno(file), I2C_RDWR, &packets) < 0) {
        printf("Failed to write to I2C device\r\n");
    }

}

void read_i2c(FILE *file, uint8_t *buffer, size_t length) {
    // Read data from I2C device
    // buffer[0] = 0x00; // Register address to read from
    // if (write(file, buffer, 1) != 1) {
    //     printf("Failed to write to the i2c bus");
    //     close(file);
    //     return 1;
    // }

    if (read(fileno(file), buffer, length) != 1) {
        printf("Failed to read from the i2c bus\r\n");
    }
}