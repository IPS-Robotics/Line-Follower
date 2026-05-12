# Define what files are part of this module
add_library( drive
    drive.h
    drive.c
    kinematics.h
    kinematics.c
)

# Define what dependencies this module has from the core SDK
target_link_libraries(drive
    hardware_gpio
    hardware_pwm
    pico_stdlib
)

# Add this module to CMake
target_include_directories(drive PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)