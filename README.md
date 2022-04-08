# Cubebert
## _Versatile Open Source Rubiks Cube Solving Robot_

[![Cubebert](https://assets.owlhouse.io/cubebert/logo.png)](cubebert.owlhouse.io)

Cubebert is a Rubiks Cube solving robot with one goal in mind, it's cool and because we can... and you can too! This can be built on RPi, GNU/Linux, Windows, and probably MacOS with one caveat; Only the whole thing can be built on RPi due to the necessary dependencies.

## Features
- Color Pattern Detection
- Kociemba 2 Phase + 4 Arm Optimization
- Fuck You

## Prerequisites
- Raspberry Pi >= 3
- RPi Pico
- CMake >= 3.10
- [raspicam](https://github.com/rmsalinas/raspicam)

## Ze Code

```sh
git clone https://github.com/C-minus-minus/Cubebert.git
mkdir Cubebert/build
cd Cubebert/build
cmake ..
make
```
