set(LIB_NAME CubeSolver)

add_library(
    ${LIB_NAME}
    cube_constants.cpp
    cube_math.cpp
    cube_search.cpp
    sticker_cube.cpp
    table_manager.cpp
)

target_include_directories(
    ${LIB_NAME}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS CubeSolver DESTINATION lib)
