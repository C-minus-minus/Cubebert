add_subdirectory(CubeSolver)

include(CheckIncludeFile)

check_include_file(raspicam/raspicam.h HAS_RASPICAM)
if(HAS_RASPICAM)
    add_subdirectory(CubeRecognition)
endif()

check_include_file(pigpio.h HAS_PIGS)
if(HAS_PIGS)
    add_subdirectory(Firmware)
endif()