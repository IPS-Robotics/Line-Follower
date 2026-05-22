# Define what files are part of this module
add_library( sensors
    sensors.c
    sensors.h
)

# Define what dependencies this module has from the core SDK
target_link_libraries(sensors
    hardware_gpio
    pico_stdlib
    hardware_adc
)

# Add this module to CMake
target_include_directories(sensors PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")