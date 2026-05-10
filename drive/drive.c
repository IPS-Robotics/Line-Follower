#include "drive.h"
#include "kinematics.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

motor_pins_t motor_left;
motor_pins_t motor_right;
uint16_t pwm_res; // The max number the PWM counter will count to before resetting to zero.

void drive_init(float max_rpm, uint16_t pwm_resolution, uint16_t pwm_clkdiv)
{
    pwm_res = pwm_resolution;
    kin_init(max_rpm, WHEEL_DIAMETER, WHEEL_DISTANCE, 16, 80);

    // PWM pins
    gpio_set_function(M_LEFT_PWM_FWD, GPIO_FUNC_PWM);
    gpio_set_function(M_RIGHT_PWM_FWD, GPIO_FUNC_PWM);
    gpio_set_function(M_LEFT_PWM_BWD, GPIO_FUNC_PWM);
    gpio_set_function(M_RIGHT_PWM_BWD, GPIO_FUNC_PWM);

    motor_left.motor = LEFT;
    init_motor(&motor_left, M_LEFT_PWM_FWD, M_LEFT_PWM_BWD);
    
    motor_right.motor = RIGHT;
    init_motor(&motor_right, M_RIGHT_PWM_FWD, M_RIGHT_PWM_BWD);

    pwm_set_wrap(motor_left.pwm_slice, pwm_res);
    pwm_set_wrap(motor_right.pwm_slice, pwm_res);

    pwm_set_clkdiv(motor_left.pwm_slice, pwm_clkdiv);
    pwm_set_clkdiv(motor_right.pwm_slice, pwm_clkdiv);
}

void drive_follow_arc(side_t direction, float speed, float radius)
{
    direction_t dir = (speed > 0 ? FORWARD : BACKWARD);
    float speed_abs = (speed > 0 ? speed : speed * -1);

    float omega = speed_abs * radius; // Angular velocity
    kin_output_t rpm_outputs = kin_calculate_rpm(speed_abs, omega);
    
    // TODO: Implement logic for turning both left and right (perhaps pass direction as an argument to kin_calculate_rpm?)
    // REMEMBER: Reversing also flips the direction
    drive_set_motors_pwm_and_dir(dir, rpm_outputs.left, rpm_outputs.right);
}

float calculate_max_rpm(float motor_voltage, float motor_kv)
{
    return motor_voltage * motor_kv;
}

void drive_stop_motor(side_t motor)
{
    motor_pins_t motor_pins = (motor == LEFT ? motor_left : motor_right);
    pwm_set_enabled(motor_pins.pwm_slice, false);
}

void init_motor(motor_pins_t* pins, uint gpio_fwd, uint gpio_bwd)
{
    pins->fwd_gpio = gpio_fwd;
    pins->bwd_gpio = gpio_bwd;

    pins->pwm_slice = pwm_gpio_to_slice_num(gpio_fwd);
    pins->pwm_fwd_chan = pwm_gpio_to_channel(gpio_fwd);
    pins->pwm_bwd_chan = pwm_gpio_to_channel(gpio_bwd);
}

void drive_set_motor_pwm_and_dir(side_t motor, direction_t dir, float duty_cycle_fraction)
{
    motor_pins_t motor_pins = (motor == LEFT ? motor_left : motor_right);
    uint level = pwm_res * duty_cycle_fraction;
    pwm_set_chan_level(motor_pins.pwm_slice, motor_pins.pwm_fwd_chan, level * (dir == FORWARD));
    pwm_set_chan_level(motor_pins.pwm_slice, motor_pins.pwm_bwd_chan, level * (dir == BACKWARD));
    pwm_set_enabled(motor_pins.pwm_slice, true);
}

void drive_set_motors_pwm_and_dir(direction_t dir, float fract_left, float fract_right)
{
    drive_set_motor_pwm_and_dir(LEFT, dir, fract_left);
    drive_set_motor_pwm_and_dir(RIGHT, dir, fract_right);
}

void drive_sync_motor_pwm_and_dir(direction_t dir, float duty_cycle_fraction)
{
    drive_set_motor_pwm_and_dir(LEFT, dir, duty_cycle_fraction);
    drive_set_motor_pwm_and_dir(RIGHT, dir, duty_cycle_fraction);
}
