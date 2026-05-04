#ifndef DRIVE
    #define DRIVE

#include <stdint.h>

// ===== CONSTANTS =====

#define M_LEFT_PWM 10 // PWM5A
#define M_LEFT_DIR 11

#define M_RIGHT_PWM 12 // PWM6A
#define M_RIGHT_DIR 13

// ===== ENUMS =====

typedef enum Motor {
    LEFT,
    RIGHT
} motor_t;

typedef enum Direction {
    FORWARD,
    BACKWARD
} direction_t;

// ===== API =====

int drive_init(uint16_t pwm_resolution);

// ===== INTERNAL =====

void drive_set_motor_pwm_and_dir(motor_t motor, direction_t dir, float duty_cycle_fraction);
void drive_sync_motor_pwm_and_dir(direction_t dir, float duty_cycle_fraction);

#endif