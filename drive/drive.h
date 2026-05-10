#ifndef DRIVE_H
    #define DRIVE_H

#include "pico/stdlib.h"

// ===== CONSTANTS =====

#define M_LEFT_PWM_FWD 10 // PWM5A
#define M_LEFT_PWM_BWD 11 // PWM5B

#define M_RIGHT_PWM_FWD 12 // PWM6A
#define M_RIGHT_PWM_BWD 13 // PWM6B

// TODO: These are placeholders
#define WHEEL_DIAMETER 0.065f // 65mm
#define WHEEL_DISTANCE 0.15f  // 150mm

// ===== ENUMS =====

typedef enum {
    LEFT,
    RIGHT
} side_t;

typedef enum {
    FORWARD,
    BACKWARD
} direction_t;


// ===== STRUCTS =====

typedef struct {
    side_t motor;
    uint fwd_gpio;
    uint bwd_gpio;
    uint pwm_slice;
    uint pwm_fwd_chan;
    uint pwm_bwd_chan;
} motor_pins_t;

// ===== API =====

/// @brief Initializes the drive module
/// @param max_rpm Max RPM of both motors. Calculate with `calculate_max_rpm`.
/// @param pwm_resolution Maximum PWM count before wrapping. 1000-4000 range.
/// @param pwm_clkdiv Clock divider for PWM, use to match frequency to ~20kHz.
void drive_init(float max_rpm, uint16_t pwm_resolution, uint16_t pwm_clkdiv);

/// @brief Start differential drive to follow an arc
/// @param speed Linear speed in m/s
/// @param radius Radius of arc in m.
/// @param direction Whether to turn left or right
void drive_follow_arc(side_t direction, float speed, float radius);

/// @brief Calculates motor max RPM with V_MOT and KV.
/// @return Max RPM
float calculate_max_rpm(float motor_voltage, float motor_kv);

void drive_stop_motor(side_t motor);

// ===== INTERNAL =====

/// @brief Fills all fields in `pins` with the correct values. 
/// @param pins Pointer to `motor_pins_t` struct.
/// @param gpio_fwd Forward pin. Must be the same PWM slice as `gpio_bwd`.
/// @param gpio_bwd Backward pin.
void init_motor(motor_pins_t* pins, uint gpio_fwd, uint gpio_bwd);

void drive_set_motor_pwm_and_dir(side_t motor, direction_t dir, float duty_cycle_fraction);
void drive_set_motors_pwm_and_dir(direction_t dir, float fract_left, float fract_right);
void drive_sync_motor_pwm_and_dir(direction_t dir, float duty_cycle_fraction);

#endif