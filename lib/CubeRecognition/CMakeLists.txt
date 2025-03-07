set(LIB_NAME CubeRecognition)

add_library(${LIB_NAME} process_cube.cpp color_math.cpp)

target_include_directories(
  ${LIB_NAME}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

# target_link_libraries(
#   ${LIB_NAME}
# )

install(TARGETS CubeRecognition DESTINATION lib)
