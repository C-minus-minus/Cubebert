add_subdirectory(solver)

if(IS_RPI)
  add_subdirectory(eyes)
  add_subdirectory(firmware)
endif()
