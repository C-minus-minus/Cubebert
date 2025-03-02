include(${CMAKE_SOURCE_DIR}/libext/raspicam.cmake.in)
include_directories(${RASPICAM_INCLUDE_DIR})

set(LIB_NAME CubeRecognition)

add_library(${LIB_NAME} estimated_cube.cpp color_math.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCAMERA REQUIRED libcamera)

target_include_directories(
  ${LIB_NAME}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${LIBCAMERA_INCLUDE_DIRS}
)

target_link_libraries(
  ${LIB_NAME}
  PRIVATE ${LIBCAMERA_LIBRARIES}  
)

install(TARGETS CubeRecognition DESTINATION lib)
