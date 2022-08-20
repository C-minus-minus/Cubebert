set(BIN_NAME cubebert-firmware)

add_executable(${BIN_NAME} cubebert-firmware.cpp)

target_compile_features(${BIN_NAME} PUBLIC cxx_std_11)

link_directories(${CMAKE_BINARY_DIR}/libext/pico-neopixel-prefix/)

target_link_libraries(
  ${BIN_NAME}
  PUBLIC pico-neopixel
)

add_dependencies(
  ${BIN_NAME}
  pico-neopixel
)

install(TARGETS ${BIN_NAME} DESTINATION sbin)
