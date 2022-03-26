add_library(libBot axis_controller.cpp stepper_motor.cpp)

target_include_directories(
    libBot
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS libBot DESTINATION lib)
