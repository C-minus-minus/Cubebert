add_library(ClawControl fingers.cpp wrist.cpp)

target_include_directories(
    ClawControl
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS ClawControl DESTINATION lib)
