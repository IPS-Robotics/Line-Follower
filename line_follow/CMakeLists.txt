# Define what files are part of this module
add_library( line_follow
    line_follow.c
    line_follow.h
)

# Define what dependencies this module has from the core SDK
target_link_libraries(line_follow
    hardware_gpio
    pico_stdlib
)

# Add this module to CMake
target_include_directories(line_follow PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")