#include "comms.h"
#include "../common.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "pwm.pio.h"

static PIO pio;
static uint offset;

void comms_init() 
{
    stdio_init_all();
    pio = pio0;
    offset = pio_add_program(pio, &pwm_program);
    pwm_program_init(pio, 0, offset,  RECIEVER_PIN_CH1);
    pwm_program_init(pio, 1, offset, RECIEVER_PIN_CH2);
    pwm_program_init(pio, 2, offset, RECIEVER_PIN_CH3);
    pwm_program_init(pio, 3, offset, RECIEVER_PIN_CH4);
}


static float read_pluse(uint sm) 
{
    uint32_t raw = pio_sm_get_blocking(pio, sm);
    //uint16_t high_count = raw >> 16;
    uint16_t low_count = raw & 0xFFFF;
    //uint16_t high_ticks = 0xFFFF - high_count;
    uint16_t low_ticks = 0xFFFF - low_count;
    //printf("Low Tick: %d\n", low_ticks);
    return low_ticks * 0.032f;
}

comms_output_state comms_read_CH() 
{
    float CH1_OUTPUT = read_pluse(0);
    float CH2_OUTPUT = read_pluse(1);
    float CH3_OUTPUT = read_pluse(2);
    float CH4_OUTPUT = read_pluse(3);

    comms_output_state comms_state;

    comms_state.ch1_output = CLAMP((read_pluse(0) - 1500) / 500, -1.0f, 1.0f);
    comms_state.ch2_output = CLAMP((read_pluse(1) - 1500) / 500, -1.0f, 1.0f);

    comms_state.ch3_output = CLAMP((int)(read_pluse(2) / 1500), 0, 1);
    comms_state.ch4_output = CLAMP((int)(read_pluse(3) / 1500), 0, 1);
    /*
    printf("CH1 microseconds: %.1f \n", CH1_OUTPUT);
    printf("CH2 microseconds: %.1f \n", CH2_OUTPUT);
    printf("CH3 microseconds: %.1f \n", CH3_OUTPUT);
    printf("CH4 microseconds: %.1f \n", CH4_OUTPUT);

    printf("CH1 throttle value %.2f \n", comms_state.ch1_output);
    printf("CH2 steering value %.2f \n", comms_state.ch2_output);
    */
    printf("CH3 microseconds: %.1f \n", CH3_OUTPUT);
    printf("CH4 microseconds: %.1f \n", CH4_OUTPUT);

    printf("CH3 : %d \n", comms_state.ch3_output);
    printf("CH4 : %d \n", comms_state.ch4_output);

    return comms_state;
}