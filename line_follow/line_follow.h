#ifndef SENSORS_H
    #define SENSORS_H

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

// =--= STRUCTS =--=

typedef struct {
    bool right;
    bool middle;
    bool left;
} sensor_dirs_t;


// =--= FUNCTIONS =--=
void s_main();

sensor_dirs_t s_is_on_line()


#endif