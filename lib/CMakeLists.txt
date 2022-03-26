# just append a new library to the list
add_subdirectory(CubeRecognition)
add_subdirectory(CubeSolver)

include(CheckIncludeFile)
check_include_file(pigpio.h HAS_PIGS)
if(HAS_PIGS)
    add_subdirectory(Firmware)
endif()