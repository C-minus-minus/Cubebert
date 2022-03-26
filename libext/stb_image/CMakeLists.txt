add_library(libstb_image stb_image.h)

target_include_directories(
    libstb_image
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS libstb_image DESTINATION lib)
install(FILES stb_image.h DESTINATION include)
