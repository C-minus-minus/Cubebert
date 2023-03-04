add_subdirectory(CubeSolver)

if(IS_RPI)
  add_subdirectory(ClawControl)
  add_subdirectory(CubeRecognition)
endif()
