# cubebert-bot binary

include(CheckIncludeFile)
check_include_file(pigpio.h HAS_PIGS)
if(HAS_PIGS)
    add_executable(cubebert-bot cubebert-bot.cpp)

    target_compile_features(cubebert-bot PUBLIC cxx_std_11)

    target_link_libraries(
        cubebert-bot
        PUBLIC Firmware
        PUBLIC -lrt
        PUBLIC -lpigpio
    )

    install(TARGETS cubebert-bot DESTINATION sbin)
endif()

# cubebert-solver binary
add_executable(cubebert-solver cubebert-solver.cpp)

target_compile_features(cubebert-solver PUBLIC cxx_std_11)

target_link_libraries(
    cubebert-solver
    PUBLIC CubeSolver
)

target_include_directories(
    cubebert-solver
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS cubebert-solver DESTINATION sbin)
