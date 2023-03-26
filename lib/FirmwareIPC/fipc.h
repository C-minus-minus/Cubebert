#ifndef FIPC_H
#define FIPC_H

#define SERIAL_PORT "/dev/ttyACM0"
#define FILE_MODE "r+"

#include <string>

class FIPC {
public:
    FIPC();
    ~FIPC();

    void sendCommand(std::string cmd);

private:
};

#endif // FIPC_H