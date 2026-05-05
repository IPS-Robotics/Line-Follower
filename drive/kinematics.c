#include "kinematics.h"
#include <stdlib.h>

float linear_vel_x_mins_;
float linear_vel_y_mins_;
float angular_vel_z_mins_;
float circumference_;
float tangential_vel_;
float x_rpm_;
float y_rpm_;
float tan_rpm_;
int max_rpm_;
float wheel_dist_;

void kin_init(int max_rpm, float wheel_diameter, float wheel_dist)
{
    circumference_ = wheel_diameter * PI;
    max_rpm_ = max_rpm;
    wheel_dist_ = wheel_dist;
}

kin_velocities_t* kin_calculate_velocities(int motor1, int motor2)
{
    kin_velocities_t* vel = malloc(sizeof(kin_velocities_t));

    float average_rpm_x = (float)(motor1 + motor2) / 2; // RPM
    //convert revolutions per minute to revolutions per second
    float average_rps_x = average_rpm_x / 60; // RPS
    vel->x = (average_rps_x * circumference_); // m/s
    
    float average_rpm_a = (float)(motor2 - motor1) / 2;
    //convert revolutions per minute to revolutions per second
    float average_rps_a = average_rpm_a / 60;
    vel->theta =  (average_rps_a * circumference_) / (wheel_dist_ / 2);
    
    return vel;
}

kin_output_t* kin_calculate_rpm(float x_vel, float y_vel, float theta_vel)
{
  //convert m/s to m/min
  linear_vel_x_mins_ = x_vel * 60;
  linear_vel_y_mins_ = y_vel * 60;

  //convert rad/s to rad/min
  angular_vel_z_mins_ = theta_vel * 60;

  //Vt = ω * radius
  tangential_vel_ = angular_vel_z_mins_ * wheel_dist_;

  x_rpm_ = linear_vel_x_mins_ / circumference_;
  y_rpm_ = linear_vel_y_mins_ / circumference_;
  tan_rpm_ = tangential_vel_ / circumference_;

  kin_output_t* rpm = malloc(sizeof(kin_output_t));

  //calculate for the target motor RPM and direction
  //front-left motor
  rpm->motor1 = x_rpm_ - y_rpm_ - tan_rpm_;
  //rear-left motor
  rpm->motor3 = x_rpm_ + y_rpm_ - tan_rpm_;

  //front-right motor
  rpm->motor2 = x_rpm_ + y_rpm_ + tan_rpm_;
  //rear-right motor
  rpm->motor4 = x_rpm_ - y_rpm_ + tan_rpm_;

  return rpm;
}
