set(BIN_NAME cubebert-firmware)

add_executable(${BIN_NAME} cubebert-firmware.cpp)

target_compile_features(${BIN_NAME} PUBLIC cxx_std_11)

# target_link_libraries(
#   ${BIN_NAME}
# )

# add_dependencies(
#   ${BIN_NAME}
# )

install(TARGETS ${BIN_NAME} DESTINATION sbin)
