set(BIN_NAME cubebert-solver)

add_executable(${BIN_NAME} cubebert-solver.cpp)

target_compile_features(${BIN_NAME} PUBLIC cxx_std_11)

target_link_libraries(
    ${BIN_NAME}
    PUBLIC CubeSolver
)

install(TARGETS ${BIN_NAME} DESTINATION sbin)
