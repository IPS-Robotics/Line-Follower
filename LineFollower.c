#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "drive.h"

#define MOTOR_KV (8000/7.2f) // RPM per Volt
#define MOTOR_VOLTAGE 7.0f   // Volts

int main() {
    // Setup
    stdio_init_all();
    
    // We initialize the WiFi as some functions (and inbuilt LED for some reason) require the WiFi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    // Initialize Drive Module (16-bit PWM)
    drive_init(calculate_max_rpm(MOTOR_VOLTAGE, MOTOR_KV), 2500, 2.5f);

    drive_follow_arc(0.3f, 0.5f); // Follow an arc with 0.3 m/s speed and 0.5 m radius
    sleep_ms(3000);
    drive_stop_motor(LEFT);
    drive_stop_motor(RIGHT);
    
    drive_follow_arc(-0.2f, 0.2f); // Follow an arc backwards with 0.2 m/s speed and 0.2 m radius
    sleep_ms(3000);
    drive_stop_motor(LEFT);
    drive_stop_motor(RIGHT);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1); // Turn on the WiFi LED to indicate we're done with the test

    // Loop
    while (1) {
    }
}