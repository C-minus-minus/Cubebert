add_library(libSolver CubeConstants.cpp CubeMath.cpp CubeSearch.cpp StickerCube.cpp TableManager.cpp)

target_include_directories(
    libSolver
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS libSolver DESTINATION lib)
