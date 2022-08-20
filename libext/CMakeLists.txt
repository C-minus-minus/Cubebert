include(ExternalProject)

ExternalProject_Add(
  RaspicamDownload
  PREFIX libext
  GIT_REPOSITORY https://github.com/pdfkpb/raspicam
  GIT_TAG origin/adding-include-dir
  INSTALL_COMMAND cmake -E echo "Skipping install step."
)


#SET(RASPICAM_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libext/src/RaspicamDownload/include)
#SET(RASPICAM_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/libext/src/RaspicamDownload-build/src)

#add_library(raspicam SHARED IMPORTED)
#set_target_properties(
#  raspicam
#  PROPERTIES
#  IMPORTED_LOCATION
#  ${RASPICAM_LIB_DIR}/libraspicam.so
#)

ExternalProject_Add(
  pico-neopixel
  PREFIX libext
  GIT_REPOSITORY https://github.com/pdfkpb/pi-pico-adafruit-neopixels
  SOURCE_SUBDIR pico_neopixels
  BUILD_COMMAND cmake -E echo "Skipping build step."
  INSTALL_COMMAND cmake -E echo "Skipping install step."
)
