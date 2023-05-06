#include "fipc.h"

int main(int argc, char* argv[]) {
    FIPC* fipc = new FIPC();

    fipc->sendCommand("^Solve,Hello!&*");

    return 0;
}
