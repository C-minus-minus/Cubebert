# Cubebert

Cubebert is a Rubiks Cube solving robot with one goal in mind, it's cool and because we can... and you can too! This can be built on RPi, GNU/Linux, Windows, and probably MacOS with one caveat; Only the whole thing can be built on RPi due to the necessary dependencies.

## Features
- Color Pattern Detection
- Kociemba 2 Phase + 4 Arm Optimization

## Getting Started

### Prerequisites
- Raspberry Pi >= 3
- RPi Pico
- CMake >= 3.10
- [raspicam](https://github.com/rmsalinas/raspicam)

### Building
```sh
mkdir build
cd build

cmake ..

# RPi/GNU Linux
make

# Windows
MSBuild.exe Cubebert.sln
```

### Running
```sh
# RPi/GNU Linux
./bin/cubebert-<program>

# Windows
.\bin\Debug\cubebert-<program>.exe
```

## License

This project is licensed under the MIT License - see the LICENSE file for details

## Acknowledgments

Inspiration, code snippets, etc.
* [Herbet Kociemba](http://kociemba.org/cube.htm) Two Phase Algorithm
* [Geoffrey Hunter @ mbedded.ninja](https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/) Serial Port Base Code
