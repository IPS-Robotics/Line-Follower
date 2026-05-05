#include "drive.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

uint pwm_left_slice;
uint pwm_right_slice;
uint16_t pwm_resolution; // The max number the PWM counter will count to before resetting to zero.

int drive_init(uint16_t pwm_res)
{
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

    pwm_resolution = pwm_res;
    pwm_left_slice = pwm_gpio_to_slice_num(M_LEFT_PWM);
    pwm_right_slice = pwm_gpio_to_slice_num(M_RIGHT_PWM);

    pwm_set_wrap(pwm_left_slice, pwm_res);
    pwm_set_wrap(pwm_right_slice, pwm_res);

    return 1;
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

void drive_sync_motor_pwm_and_dir(direction_t dir, float duty_cycle_fraction)
{
    drive_set_motor_pwm_and_dir(LEFT, dir, duty_cycle_fraction);
    drive_set_motor_pwm_and_dir(RIGHT, dir, duty_cycle_fraction);
}
