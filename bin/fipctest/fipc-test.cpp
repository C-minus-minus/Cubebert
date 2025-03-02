#include "i2c.h"

#include <string>

int main() {
    FILE *file = open_i2c_device("/dev/i2c-1");
    if (file == NULL) {
        return 1;
    }

    std::string data = "Solve,F;";
    write_i2c(file, (uint8_t *)data.c_str(), data.size());

    close_i2c_device(file);
    return 0;
}