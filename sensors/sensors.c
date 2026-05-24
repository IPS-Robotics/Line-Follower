#include <stdio.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "sensors.h"

static float get_sensor_value(uint channel) //returns 0-1
{
    adc_select_input(channel);
    return ADC_CONVERT_VAL(adc_read());
}

sensor_dirs_t s_read_sensor_values()
{
    bool right = (get_sensor_value(RIGHT_SENSOR_CH) < BRIGHTNESS_THRESHOLD);
    bool middle = (get_sensor_value(MIDDLE_SENSOR_CH) < BRIGHTNESS_THRESHOLD);
    bool left = (get_sensor_value(LEFT_SENSOR_CH) < BRIGHTNESS_THRESHOLD);
    
    return (sensor_dirs_t){
        .right = right,
        .middle = middle,
        .left = left
    };
}

float s_get_error()
{
    // TODO: Return error
    // -1 - max left
    // +1 - max right
    return 0.0f;
}

void s_init()
{
    adc_init();
    adc_gpio_init(RIGHT_SENSOR_PIN);
    adc_gpio_init(LEFT_SENSOR_PIN);
    adc_gpio_init(MIDDLE_SENSOR_PIN);
}

