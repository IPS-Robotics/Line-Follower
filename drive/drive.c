#include "drive.h"
#include "kinematics.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

uint pwm_left_slice;
uint pwm_right_slice;
uint16_t pwm_resolution; // The max number the PWM counter will count to before resetting to zero.

int drive_init(float max_rpm, uint16_t pwm_resolution)
{
    kin_init(max_rpm, WHEEL_DIAMETER, WHEEL_DISTANCE);

    // Direction pins
    gpio_init(M_LEFT_DIR);
    gpio_init(M_RIGHT_DIR);

    gpio_set_dir(M_LEFT_DIR, GPIO_OUT);
    gpio_set_dir(M_RIGHT_DIR, GPIO_OUT);

    gpio_put(M_LEFT_DIR, 0);
    gpio_put(M_RIGHT_DIR, 0);

    // PWM pins
    gpio_set_function(M_LEFT_PWM, GPIO_FUNC_PWM);
    gpio_set_function(M_RIGHT_PWM, GPIO_FUNC_PWM);

    pwm_resolution = pwm_resolution;
    pwm_left_slice = pwm_gpio_to_slice_num(M_LEFT_PWM);
    pwm_right_slice = pwm_gpio_to_slice_num(M_RIGHT_PWM);

    pwm_set_wrap(pwm_left_slice, pwm_resolution);
    pwm_set_wrap(pwm_right_slice, pwm_resolution);

    return 1;
}

void drive_follow_arc(float speed, float radius)
{
    float omega = speed * radius; // Angular velocity
    kin_output_t rpm_outputs = kin_calculate_rpm(speed, omega);
    drive_set_motors_pwm_and_dir(FORWARD, rpm_outputs.left, rpm_outputs.right);
}

float calculate_max_rpm(float motor_voltage, float motor_kv)
{
    return motor_voltage * motor_kv;
}

void drive_set_motor_pwm_and_dir(motor_t motor, direction_t dir, float duty_cycle_fraction)
{
    uint pwm_slice = (motor == LEFT ? pwm_left_slice : pwm_right_slice);
    uint gpio = (motor == LEFT ? M_LEFT_DIR : M_RIGHT_DIR);
    uint pwm_chan = pwm_gpio_to_channel(motor == LEFT ? M_LEFT_PWM : M_RIGHT_PWM);

    // TODO: Ensure the direction enum matches the hardware
    gpio_put(gpio, (bool)dir);

    pwm_set_chan_level(pwm_slice, pwm_chan, pwm_resolution * duty_cycle_fraction);
    pwm_set_enabled(pwm_slice, true);
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
