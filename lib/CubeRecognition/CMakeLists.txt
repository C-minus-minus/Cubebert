add_library(CubeRecognition estimated_cube.cpp)

target_include_directories(
    CubeRecognition
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    CubeRecognition
    PUBLIC raspicam
)

install(TARGETS CubeRecognition DESTINATION lib)
