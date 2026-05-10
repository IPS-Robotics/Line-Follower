#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "Pwm.pio.h"

#define CH1 9
#define CH2 10
#define CH3 11
#define CH4 12

static PIO pio;
static uint offset;

void comms(void) {
    stdio_init_all()

    pio = pio0;
    offset = pio_add_program(pio, &pwm_program);

    pwm_program_init(pio, 9, offset, CH1);
    pwm_program_init(pio, 10, offset, CH2);
    pwm_program_init(pio, 11, offset, CH3);
    pwm_program_init(pio, 12, offset, CH4);
}

static float Read_Pluse(uint sm) {

}