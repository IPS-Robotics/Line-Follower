# Define what files are part of this module
add_library( comms
    comms.c
    comms.h
)

# Define what dependencies this module has from the core SDK
target_link_libraries(comms
    hardware_gpio
    pico_stdlib
)

# Add this module to CMake
target_include_directories(comms PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")