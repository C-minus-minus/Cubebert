# cubebert-bot binary]
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

    # cubebert-eyes binary
    add_executable(cubebert-eyes cubebert-eyes.cpp)

    target_compile_features(cubebert-eyes PUBLIC cxx_std_11)

    target_link_libraries(
        cubebert-eyes
        PUBLIC libstb_image
        PUBLIC CubeRecognition
    )

    install(TARGETS cubebert-eyes DESTINATION sbin)
endif()

# cubebert-solver binary
add_executable(cubebert-solver cubebert-solver.cpp)

target_compile_features(cubebert-solver PUBLIC cxx_std_11)

target_link_libraries(
    cubebert-solver
    PUBLIC CubeSolver
)

install(TARGETS cubebert-solver DESTINATION sbin)
