cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

# set the project name
project(Cubebert VERSION 0.0.1)

execute_process(
    COMMAND uname -m
    OUTPUT_VARIABLE ARCHITECTURE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message(STATUS "Detected architecture: ${ARCHITECTURE}")

if(ARCHITECTURE MATCHES "^(aarch64|arm)")
# Check if this is specifically a Raspberry Pi
execute_process(
    COMMAND grep -q "Raspberry Pi" /proc/cpuinfo
    RESULT_VARIABLE IS_NOT_RPI
    OUTPUT_QUIET
    ERROR_QUIET
)

if(IS_NOT_RPI EQUAL 0)
    message(STATUS "Building for Raspberry Pi")
    set(IS_RPI TRUE)
else()
    message(STATUS "Building for ARM architecture (not Raspberry Pi)")
    set(IS_RPI FALSE)
endif()
else()
    message(STATUS "Building for non-ARM architecture")
    set(IS_RPI FALSE)
endif()

add_subdirectory(bin)
add_subdirectory(lib)

# Setup packaging information
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${Cubebert_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Cubebert_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
