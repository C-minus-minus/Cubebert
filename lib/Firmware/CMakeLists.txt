add_library(Firmware axis_controller.cpp stepper_motor.cpp)

target_include_directories(
    Firmware
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS Firmware DESTINATION lib)
