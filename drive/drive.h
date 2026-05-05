#ifndef DRIVE_H
    #define DRIVE_H

#include <stdint.h>

// ===== CONSTANTS =====

#define M_LEFT_PWM 10 // PWM5A
#define M_LEFT_DIR 11

#define M_RIGHT_PWM 12 // PWM6A
#define M_RIGHT_DIR 13

// TODO: These are placeholders
#define WHEEL_DIAMETER 0.065f // 65mm
#define WHEEL_DISTANCE 0.15f  // 150mm

// ===== ENUMS =====

typedef enum {
    LEFT,
    RIGHT
} motor_t;

typedef enum {
    FORWARD,
    BACKWARD
} direction_t;

// ===== API =====

int drive_init(float max_rpm, uint16_t pwm_resolution);
void drive_follow_arc(float speed, float radius);
float calculate_max_rpm(float motor_voltage, float motor_kv);

// ===== INTERNAL =====

void drive_set_motor_pwm_and_dir(motor_t motor, direction_t dir, float duty_cycle_fraction);
void drive_set_motors_pwm_and_dir(direction_t dir, float fract_left, float fract_right);
void drive_sync_motor_pwm_and_dir(direction_t dir, float duty_cycle_fraction);

#endif