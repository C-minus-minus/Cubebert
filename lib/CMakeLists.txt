add_subdirectory(CubeSolver)

include(CheckIncludeFile)

#find_path(HAS_RASPICAM raspicam.h PATHS /usr/local/include/raspicam)
#if(HAS_RASPICAM)
    add_subdirectory(CubeRecognition)
#endif()

check_include_file(pigpio.h HAS_PIGS)
if(HAS_PIGS)
    add_subdirectory(Firmware)
endif()
