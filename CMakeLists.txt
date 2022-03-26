cmake_minimum_required(VERSION 3.10)

# set the project name
project(Cubebert VERSION 0.1)

add_subdirectory(bin)
add_subdirectory(lib)
add_subdirectory(libext)
add_subdirectory(test)

target_compile_features(Cubebert PUBLIC cxx_std_11)

# Setup packaging information
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${Cubebert_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Cubebert_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
