#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "drive.h"

int main() {
    // Setup
    stdio_init_all();
    
    // We initialize the WiFi as some functions (and inbuilt LED for some reason) require the WiFi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed");
        return -1;
    }

    // Initialize Drive Module - maximum possible PWM resolution
    drive_init(0xFFFF);

    // Set both motors forward - useful for testing later (illegal use of internal function but its testing so its ok)
    drive_sync_motor_pwm_and_dir(FORWARD, 0.5f); // 50% speed

    // Loop
    while (1) {

    }
}