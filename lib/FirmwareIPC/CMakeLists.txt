set(LIB_NAME FirmwareIPC)

add_library(${LIB_NAME} i2c.c)

target_include_directories(
    ${LIB_NAME}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS ${LIB_NAME} DESTINATION lib)
