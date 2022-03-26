add_library(CubeRecognition estimated_cube.cpp)

target_include_directories(
    CubeRecognition
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

# link against rapsicam
find_package(raspicam REQUIRED)
target_link_libraries(
    CubeRecognition
    ${raspicam_LIBS}
)

install(TARGETS CubeRecognition DESTINATION lib)
