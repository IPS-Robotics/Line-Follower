#ifndef KINEMATICS_H
    #define KINEMATICS_H

#include "common.h"

// ===== CONSTANTS =====

#define PI 3.14159265358979323846f

// ===== MACROS =====

// Kinda a stupid piece of code, but hey, it works
#define CLAMP(x, min, max) ((x > max ? max : x) < min ? min : (x > max ? max : x))

// ===== STRUCTS =====

typedef struct {
    float left;
    float right;
} kin_output_t;

// ===== API =====

void kin_init(float max_motor_rpm, float wheel_diameter, float wheel_dist, int motor_teeth, int output_teeth);
kin_output_t kin_calculate_rpm(float linear_vel, float angular_vel, side_t side);

#endif