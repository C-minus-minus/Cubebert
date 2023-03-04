cmake_minimum_required(VERSION 3.17)

# set the project name
project(
  Cubebert
  LANGUAGES C CXX ASM
  VERSION 0.0.1
)

# set compiler flags
# -Ofast - optimises as much as reasonably possible
set(CMAKE_CSTANDARD 11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

if(EXISTS /home/pi)
    set(IS_RPI true)
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
