include(${CMAKE_SOURCE_DIR}/libext/raspicam.cmake.in)
include_directories(${RASPICAM_INCLUDE_DIR})

set(LIB_NAME CubeRecognition)

add_library(${LIB_NAME} estimated_cube.cpp color_math.cpp)

#target_include_directories(
#  ${LIB_NAME}
#  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
#)

target_link_libraries(
  ${LIB_NAME}
  PUBLIC raspicam
)

add_dependencies(
  ${LIB_NAME}
  RaspicamDownload
)

install(TARGETS CubeRecognition DESTINATION lib)
