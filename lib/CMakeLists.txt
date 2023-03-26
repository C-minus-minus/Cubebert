add_subdirectory(CubeSolver)

if(IS_RPI)
  # add_subdirectory(CubeRecognition)
  add_subdirectory(FirmwareIPC)
endif()
