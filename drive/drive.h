#ifndef DRIVE_H
    #define DRIVE_H

#include "pico/stdlib.h"
#include "common.h"

// ===== CONSTANTS =====

#define M_LEFT_PWM_FWD 10 // PWM5A
#define M_LEFT_PWM_BWD 11 // PWM5B

#define M_RIGHT_PWM_FWD 12 // PWM6A
#define M_RIGHT_PWM_BWD 13 // PWM6B

// TODO: These are placeholders
#define WHEEL_DIAMETER 0.065f // 65mm
#define WHEEL_DISTANCE 0.15f  // 150mm

// ===== LF TUNING =====

#define LF_BASE_SPEED 0.4f
#define K_P 0.6f // Proportional gain
#define K_D 0.1f // Derivative gain

// ===== ENUMS =====

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

/// @brief Applies speed and steering controls to the motors.
/// @param speed Normalized speed value from the controller, where 1.0 is max forward speed, -1.0 is max reverse speed, and 0.0 is stop.
/// @param steering Normalized steering value from the controller, where 1.0 is max right turn, -1.0 is max left turn, and 0.0 is straight.
void drive_apply_controls(float speed, float steering);

/// @brief Calculates motor max RPM with V_MOT and KV.
/// @return Max RPM
float calculate_max_rpm(float motor_voltage, float motor_kv);

/// @brief Uses PID control to set steering based on sensor error. Updates modle state.
///        This depends on the `K_P` and `K_D` constants for tuning the PID control.
/// @param error Error from -1 (max left) to 1 (max right)
void drive_update_lf_state(float error);

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