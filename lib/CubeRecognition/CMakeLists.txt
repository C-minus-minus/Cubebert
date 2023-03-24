set(LIB_NAME CubeRecognition)

add_library(${LIB_NAME} estimated_cube.cpp color_math.cpp)

include(FetchContent)
FetchContent_Declare(
  raspicam
  GIT_REPOSITORY https://github.com/cedricve/raspicam.git
  GIT_TAG        651c56418a5a594fc12f1414eb14f2b899729cb1
)
FetchContent_MakeAvailable(raspicam)

target_include_directories(
  ${LIB_NAME}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${LIB_NAME}
  raspicam
)

add_dependencies(
  ${LIB_NAME}
  raspicam
)

install(TARGETS CubeRecognition DESTINATION lib)

pico_add_extra_outputs(CubeRecognition)
