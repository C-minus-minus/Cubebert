# just append a new library to the list
include(CheckIncludeFile)
check_include_file(pigpio.h HAS_PIGS)
if(HAS_PIGS)
    add_subdirectory(bot)
endif()

add_subdirectory(solver)
