#include "comms.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pwm.pio.h"

static PIO pio;
static uint offset;

void comms_init() {
    stdio_init_all();
    pio = pio0;
    offset = pio_add_program(pio, &pwm_program);
    pwm_program_init(pio, 0, offset,  RECIEVER_PIN_CH1);
    pwm_program_init(pio, 1, offset, RECIEVER_PIN_CH2);
    pwm_program_init(pio, 2, offset, RECIEVER_PIN_CH3);
    pwm_program_init(pio, 3, offset, RECIEVER_PIN_CH4);
}

static float read_pluse(uint sm) {
    uint32_t raw = pio_sm_get_blocking(pio, sm);
    uint16_t high_count = raw >> 16;
    uint16_t high_ticks = 0xFFFF - high_count;
    return high_ticks * 0.024f;
}

void comms_read_CH() {
    float CH1_value = read_pluse(0);
    float CH2_value = read_pluse(1);
    float CH3_value = read_pluse(2);
    float CH4_value = read_pluse(3);

    printf("CH3 PWM value %d", CH3_value);
}