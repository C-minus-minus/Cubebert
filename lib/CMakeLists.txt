add_subdirectory(CubeSolver)

include(CheckIncludeFile)

if(EXISTS /usr/local/include/raspicam)
    add_subdirectory(CubeRecognition)
endif()

check_include_file(pigpio.h HAS_PIGS)
if(HAS_PIGS)
    add_subdirectory(Firmware)
endif()
