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


static float read_duty_cycle(uint state_machine)
{
    uint32_t raw = pio_sm_get_blocking(pio, state_machine);
    uint32_t high_count = raw >> 16;
    uint32_t low_count  = raw & 0xFFFF;

    uint32_t high_ticks = 0xFFFF - high_count;
    uint32_t low_ticks  = 0xFFFF - low_count;

    //printf("LOW: %u HIGH: %u \n", low_ticks, high_ticks);

    uint32_t total_ticks = high_ticks + low_ticks;

    float total = (float)high_ticks / (float)total_ticks * 100.0f;

    return total;
}

comms_output_state comms_read_CH() 
{
    //int CH1_OUTPUT = read_duty_cycle(0);
    int CH2_OUTPUT = read_duty_cycle(1);
    int CH3_OUTPUT = read_duty_cycle(2) > 25.4f ? 1 : 0;
    int CH4_OUTPUT = read_duty_cycle(3) > 25.4f ? 1 : 0;

    comms_output_state comms_state;

    sleep_ms(100);


    printf("Ch2 Output %d \n", CH2_OUTPUT);
    /*
    printf("Ch3 Outout %d ", CH3_OUTPUT);
    printf("CH4 Output %d \n", CH4_OUTPUT);
    */

    return comms_state;
}