#include "comms.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "pwm.pio.h"

static PIO pio;
static uint offset;

void comms_init() {
    stdio_init_all()

    pio = pio0;
    offset = pio_add_program(pio, &pwm_program);

    pwm_program_init(pio, 9, offset,  RECIEVER_PIN_CH1);
    pwm_program_init(pio, 10, offset, RECIEVER_PIN_CH2);
    pwm_program_init(pio, 11, offset, RECIEVER_PIN_CH3);
    pwm_program_init(pio, 12, offset, RECIEVER_PIN_CH4);
}

static float read_pluse(uint sm) {

}