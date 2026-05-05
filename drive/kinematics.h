#ifndef KINEMATICS_H
    #define KINEMATICS_H

// Kinematics implementation ported to C from the original C++ code by Linorobot:
// https://github.com/linorobot/kinematics/tree/master
// This code was designed for a 4-wheeled robot but can be adapted for a 2-wheel configuration as well.

// ===== CONSTANTS =====

#define PI 3.14159265358979323846f

// ===== STRUCTS =====

typedef struct {
    int motor1;
    int motor2;
    int motor3;
    int motor4;
} kin_output_t;

typedef struct {
    float x;
    float y;
    float theta;
} kin_velocities_t;

// ===== API =====

void kin_init(int max_rpm, float wheel_diameter, float wheel_dist);
kin_velocities_t* kin_calculate_velocities(int motor1, int motor2);
kin_output_t* kin_calculate_rpm(float x_vel, float y_vel, float theta_vel);

#endif