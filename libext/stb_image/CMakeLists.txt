add_library(stb_image stb_image.h)

set_target_properties(stb_image PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
    stb_image
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS stb_image DESTINATION lib)
install(FILES stb_image.h DESTINATION include)
