set(LIB_NAME CubeRecognition)

add_library(${LIB_NAME} estimated_cube.cpp color_math.cpp)

include(../../libext/pico_sdk_import.cmake)
include(../../libext/pico_extras_import.cmake)

pico_sdk_init()

include(FetchContent)
FetchContent_Declare(
  raspicam
  GIT_REPOSITORY https://github.com/cedricve/raspicam.git
  GIT_TAG        651c56418a5a594fc12f1414eb14f2b899729cb1
)
FetchContent_MakeAvailable(raspicam)

FetchContent_Declare(
  pico-neopixel
  GIT_REPOSITORY https://github.com/pdfkpb/pico-neopixel.git
  GIT_TAG        4a9ae19991bc8841942c62305bf8b5595d2acc15
)
FetchContent_MakeAvailable(pico-neopixel)

target_include_directories(
  ${LIB_NAME}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${LIB_NAME}
  raspicam
  pico_stdlib
  pico_neopixel
)

add_dependencies(
  ${LIB_NAME}
  raspicam
  pico_neopixel
)

install(TARGETS CubeRecognition DESTINATION lib)

pico_add_extra_outputs(CubeRecognition)
