set(LIB_NAME Logger)

add_library(${LIB_NAME} logger.cpp)

target_include_directories(
    ${LIB_NAME}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS ${LIB_NAME} DESTINATION lib)
