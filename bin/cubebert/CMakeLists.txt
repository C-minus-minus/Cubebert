set(BIN_NAME cubebert)

add_executable(${BIN_NAME} cubebert.cpp)

target_compile_features(${BIN_NAME} PUBLIC cxx_std_20)

target_link_libraries(
  ${BIN_NAME}
  PUBLIC CubeRecognition
  PUBLIC CubeSolver
  PUBLIC FirmwareIPC
)

install(TARGETS ${BIN_NAME} DESTINATION sbin)
