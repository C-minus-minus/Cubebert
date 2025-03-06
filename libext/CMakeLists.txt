if(IS_RPI)
  include(ExternalProject)

  ExternalProject_Add(
    pico-neopixel
    PREFIX libext
    GIT_REPOSITORY https://github.com/pdfkpb/pi-pico-adafruit-neopixels
    SOURCE_SUBDIR pico_neopixels
    BUILD_COMMAND cmake -E echo "Skipping build step."
    INSTALL_COMMAND cmake -E echo "Skipping install step."
  )
endif()