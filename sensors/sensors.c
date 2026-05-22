#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "line_follow.h"

static float get_sensor_value(uint channel) //returns 0-1
{
    adc_select_input(channel);
    return ADC_CONVERT_VAL(adc_read());
}

sensor_dirs_t s_is_on_line()
{
    bool right = (get_sensor_value(RIGHT_SENSOR_CH) < BRIGHTNESS_THRESHOLD;)
    bool middle = (get_sensor_value(MIDDLE_SENSOR_CH) < BRIGHTNESS_THRESHOLD);
    bool left = (get_sensor_value(LEFT_SENSOR_CH) < BRIGHTNESS_THRESHOLD);
    
    return (sensor_dirs_t){
        .right = right,
        .middle = middle,
        .left = left
    };
}

void s_main()
{
    adc_init();
    adc_gpio_init(RIGHT_SENSOR);
    adc_gpio_init(LEFT_SENSOR);
    adc_gpio_init(MIDDLE_SENSOR);

    while (true) {
        printf("%.2f\n", get_sensor_value(RIGHT_SENSOR_CH));
        sleep_ms(10);
    }
}

