#ifndef COMMON_H
    #define COMMON_H

#include <stdbool.h>

// Common header file with shared types and definitions used by multiple modules.
// This is to avoid circular dependencies and keep code organized.

// ===== MACROS =====

// Kinda a stupid piece of code, but hey, it works
#define CLAMP(x, min, max) ((x > max ? max : x) < min ? min : (x > max ? max : x))

// ===== ENUMS =====

typedef enum {
    LEFT,
    RIGHT
} side_t;

typedef enum {
    RC_MODE,
    LF_MODE
} control_mode_t;

// ===== STRUCTS =====

typedef struct {
    bool right;
    bool middle;
    bool left;
} sensor_dirs_t;

#endif