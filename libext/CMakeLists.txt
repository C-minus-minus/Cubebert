include(ExternalProject)

ExternalProject_Add(
  raspicam
  PREFIX libext
  GIT_REPOSITORY https://github.com/pdfkpb/raspicam
  GIT_TAG origin/adding-include-dir
  DOWNLOAD_NO_PROGRESS true
  INSTALL_COMMAND cmake -E echo "Skipping install step."
)

ExternalProject_Add(
  StepperDriver
  PREFIX libext
  GIT_REPOSITORY https://github.com/laurb9/StepperDriver
  SOURCE_SUBDIR src
  BUILD_COMMAND cmake -E echo "Skipping build step."
  INSTALL_COMMAND cmake -E echo "Skipping install step."
)

ExternalProject_Add(
  pico-neopixel
  PREFIX libext
  GIT_REPOSITORY https://github.com/pdfkpb/pi-pico-adafruit-neopixels
  SOURCE_SUBDIR pico_neopixels
  BUILD_COMMAND cmake -E echo "Skipping build step."
  INSTALL_COMMAND cmake -E echo "Skipping install step."
)
