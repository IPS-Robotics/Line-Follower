#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "drive.h"
#include "comms.h"
#include "sensors.h"

#define MOTOR_KV (8000/7.2f) // RPM per Volt
#define MOTOR_VOLTAGE 7.0f   // Volts

static control_mode_t mode;

int main()
{
    // Setup
    stdio_init_all();
    printf("Program started");
    
    // Wait for USB to connect
    // What exactly is this for?
    // testing when IRQ when it was broken, u can remove now
    while (!stdio_usb_connected()) {
        sleep_ms(100);
        printf("... \n");
    }
    
    // Initialize Drive Module (16-bit PWM)
    drive_init(calculate_max_rpm(MOTOR_VOLTAGE, MOTOR_KV), 2500, 2.5f);
    
    // Initialize Sensor Module
    s_init();
    
    // Initialize Comms Module
    comms_init();

    // Start in RC mode 
    mode = RC_MODE;

    while (true) {
        // Read controller input
        comms_output_state_t controls = comms_read_CH();

        // Change control mode based on CH3

        // If RC, apply controls from CH1 and CH2

        // If LF, call PID update function
        if (mode == LF_MODE) {
            float error = s_get_error();
            drive_update_lf_state(error);
        }
    }
}