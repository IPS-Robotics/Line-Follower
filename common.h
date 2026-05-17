#ifndef COMMON_H
    #define COMMON_H

// Common header file with shared types and definitions used by multiple modules.
// This is to avoid circular dependencies and keep code organized.

// ===== MACROS =====

// Kinda a stupid piece of code, but hey, it works
#define CLAMP(x, min, max) ((x > max ? max : x) < min ? min : (x > max ? max : x))


// ===== STRUCTS =====

typedef enum {
    LEFT,
    RIGHT
} side_t;


#endif