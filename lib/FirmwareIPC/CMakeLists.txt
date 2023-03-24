set(LIB_NAME FirmwareIPC)

add_library(${LIB_NAME} fipc.cpp)

target_include_directories(
  ${LIB_NAME}
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
  ${LIB_NAME}
)

add_dependencies(
  ${LIB_NAME}
)

install(TARGETS ${LIB_NAME} DESTINATION lib)
