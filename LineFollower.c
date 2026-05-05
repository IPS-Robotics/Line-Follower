#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "drive.h"

#define MOTOR_KV (8000/7.2f) // RPM per Volt
#define MOTOR_VOLTAGE 7.2f   // Volts

int main() {
    // Setup
    stdio_init_all();
    
    // We initialize the WiFi as some functions (and inbuilt LED for some reason) require the WiFi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    // Initialize Drive Module (16-bit PWM)
    drive_init(calculate_max_rpm(MOTOR_VOLTAGE, MOTOR_KV), 65535);

    drive_follow_arc(0.2f, 0.25f); // Follow an arc with 0.2 m/s speed and 0.25 m radius

    // Loop
    while (1) {

    }
}