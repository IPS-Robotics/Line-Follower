#include "kinematics.h"
#include <stdlib.h>

float wheel_circumference;
float wheel_distance;
float max_rpm;
float gear_ratio;

void kin_init(float max_motor_rpm, float wheel_diameter, float wheel_dist, int motor_teeth, int output_teeth)
{
    wheel_circumference = wheel_diameter * PI;
    wheel_distance = wheel_dist;
    max_motor_rpm = max_motor_rpm;
    gear_ratio = (float)output_teeth/(float)motor_teeth;
}

kin_output_t kin_calculate_rpm(float linear_vel, float angular_vel)
{
    kin_output_t output = {0};

    float v_left = linear_vel - (angular_vel * wheel_distance / 2.0f);
    float v_right = linear_vel + (angular_vel * wheel_distance / 2.0f);

    float rpm_wheel_left = v_left / wheel_circumference * 60.0f;
    float rpm_wheel_right = v_right / wheel_circumference * 60.0f;

    float rpm_motor_left = rpm_wheel_left * gear_ratio;
    float rpm_motor_right = rpm_wheel_right * gear_ratio;

    // Convert to duty cycle fraction (clamp to ensure we don't go over 1, which would be bad)
    output.left = CLAMP(rpm_motor_left / max_rpm, 0, 1);
    output.right = CLAMP(rpm_motor_right / max_rpm, 0, 1);

    return output;
}


