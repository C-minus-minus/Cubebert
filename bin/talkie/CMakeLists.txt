set(BIN_NAME cubebert-talkie)

add_executable(${BIN_NAME} ${BIN_NAME}.cpp)

target_compile_features(${BIN_NAME} PUBLIC cxx_std_11)

target_link_libraries(
    ${BIN_NAME}
    PUBLIC FirmwareIPC
)

install(TARGETS ${BIN_NAME} DESTINATION sbin)
