#ifndef FIPC_H
#define FIPC_H

#include "i2c.h"

#include <string>

class FIPC {
public:
    FIPC();
    ~FIPC();

    void home();
    void grab(std::string face);
    void rotate(std::string moves);

private:
    FILE *m_i2cFile;
};

#endif // FIPC_H
