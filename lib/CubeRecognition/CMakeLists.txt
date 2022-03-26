add_library(CubeRecognition place_holder.cpp)

target_include_directories(
    CubeRecognition
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS CubeRecognition DESTINATION lib)
