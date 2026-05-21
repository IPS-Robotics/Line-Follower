#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "line_follow.h"

static float convert_adc(uint reading)
{
    return reading * ADC_CONVERT_VAL;
}

void lf_main()
{
    adc_init();
    adc_gpio_init(RIGHT_SENSOR);
    adc_select_input(RIGHT_SENSOR_CH);
    uint adc_raw;

    while (true){
        adc_raw = adc_read();
        // remove the comment later!!!!!

        //printf("%.2f\n", convert_adc(adc_raw));
        sleep_ms(10);
    }
}