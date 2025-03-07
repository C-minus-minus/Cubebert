set(BIN_NAME preprocessor)

add_executable(${BIN_NAME} preprocessor.cpp)

target_compile_features(${BIN_NAME} PUBLIC cxx_std_20)

target_link_libraries(
    ${BIN_NAME}
    PUBLIC CubeSolver
)

install(TARGETS ${BIN_NAME} DESTINATION sbin)
