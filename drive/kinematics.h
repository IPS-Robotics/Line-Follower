#ifndef KINEMATICS_H
    #define KINEMATICS_H

// ===== CONSTANTS =====

#define PI 3.14159265358979323846f

// ===== STRUCTS =====

typedef struct {
    float left;
    float right;
} kin_output_t;


// ===== API =====

void kin_init(float max_rpm, float wheel_diameter, float wheel_dist);
kin_output_t kin_calculate_rpm(float linear_vel, float angular_vel);

#endif