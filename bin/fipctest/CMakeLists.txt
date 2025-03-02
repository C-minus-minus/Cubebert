set(BIN_NAME fipc-test)

add_executable(${BIN_NAME} fipc-test.cpp)

target_compile_features(${BIN_NAME} PUBLIC cxx_std_20)

target_link_libraries(
    ${BIN_NAME}
    PUBLIC FirmwareIPC
)

install(TARGETS ${BIN_NAME} DESTINATION sbin)
