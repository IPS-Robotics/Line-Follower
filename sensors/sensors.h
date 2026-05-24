#ifndef SENSORS_H
    #define SENSORS_H

#include "common.h"

// =--= MACROS =--=
    
#define ADC_CONVERT_VAL(x) (x) * (3.3 / ( (1 << 12) - 1))

// =--= CONSTANTS =--=

#define BRIGHTNESS_THRESHOLD 0.5

// =--= PINS =--=

#define RIGHT_SENSOR_PIN 26
#define RIGHT_SENSOR_CH 0

#define MIDDLE_SENSOR_PIN 28
#define MIDDLE_SENSOR_CH 3

#define LEFT_SENSOR_PIN 27
#define LEFT_SENSOR_CH 1

// =--= FUNCTIONS =--=
void s_init();

sensor_dirs_t s_read_sensor_values();
float s_get_error();

#endif