add_library(CubeSolver CubeConstants.cpp CubeMath.cpp CubeSearch.cpp StickerCube.cpp TableManager.cpp)

target_include_directories(
    CubeSolver
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS CubeSolver DESTINATION lib)
