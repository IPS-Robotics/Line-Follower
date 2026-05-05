#include "kinematics.h"
#include <stdlib.h>

float wheel_circumference;
float wheel_distance;
float max_rpm;

void kin_init(float max_rpm, float wheel_diameter, float wheel_dist)
{
    wheel_circumference = wheel_diameter * PI;
    wheel_distance = wheel_dist;
    max_rpm = max_rpm;
}

kin_output_t kin_calculate_rpm(float linear_vel, float angular_vel)
{
    kin_output_t output = {0};

    float v_left = linear_vel - (angular_vel * wheel_distance / 2.0f);
    float v_right = linear_vel + (angular_vel * wheel_distance / 2.0f);

    float rpm_left = v_left / wheel_circumference * 60.0f;
    float rpm_right = v_right / wheel_circumference * 60.0f;

    // Convert to duty cycle fraction
    output.left = rpm_left / max_rpm;
    output.right = rpm_right / max_rpm;

    return output;
}


