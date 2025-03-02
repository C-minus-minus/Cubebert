add_subdirectory(solver)
add_subdirectory(fipctest)
# add_subdirectory(eyes)

if(IS_RPI)
  add_subdirectory(firmware)
endif()
