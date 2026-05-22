#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "drive.h"
#include "comms.h"
#include "sensors.h"

#include "hardware/uart.h"

#define MOTOR_KV (8000/7.2f) // RPM per Volt
#define MOTOR_VOLTAGE 7.0f   // Volts

int main() {
    // Setup
    stdio_init_all();
    comms_init();
    
    // We initialize the WiFi as some functions (and inbuilt LED for some reason) require the WiFi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    // Initialize Drive Module (16-bit PWM)
    drive_init(calculate_max_rpm(MOTOR_VOLTAGE, MOTOR_KV), 2500, 2.5f);

    // Initialize Sensor Module
    s_init();

    // Variable
    sensor_dirs_t current_direction;
    sensor_dirs_t last_valid_direction;

    while (true){
        // Most basic robot control: turn 
        current_direction = s_is_on_line();
    }
}