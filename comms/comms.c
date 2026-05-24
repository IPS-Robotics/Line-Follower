#include "comms.h"
#include "../common.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

static volatile uint32_t rise_time;
static volatile uint32_t pulse_width;

static void comms_callback(uint gpio, uint32_t events)
{
    uint32_t now = time_us_32();

    if (events & GPIO_IRQ_EDGE_RISE){
        //gpio_acknowledge_irq(RECIEVER_PIN_CH1, GPIO_IRQ_EDGE_RISE);
        rise_time = now;
    } 
    if (events & GPIO_IRQ_EDGE_FALL){
        //gpio_acknowledge_irq(RECIEVER_PIN_CH1, GPIO_IRQ_EDGE_FALL);
        pulse_width = time_us_32() - rise_time;
    }
}

void comms_init() 
{
    uint pin = RECIEVER_PIN_CH1;
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_down(pin);

    printf("GPIO config done \n");

    gpio_set_irq_callback(comms_callback);
    irq_set_enabled(IO_IRQ_BANK0, true);

    gpio_set_irq_enabled(pin,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true);
   
    printf("IRQ set up \n");
    

/*
    for (int i = 0; i < 4; i++)
    {
        uint pin = RECIEVER_PIN_CH1 + i;
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_down(pin);

        if (i == 0)
        {
            gpio_set_irq_enabled_with_callback(pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &comms_callback);
        } else{

        gpio_set_irq_enabled(
            pin, 
            GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, 
            true);
        }
    }
*/

}

comms_output_state_t comms_read_CH() 
{
    comms_output_state_t comms_state;

    comms_state.ch1_output = pulse_width;

    printf("CH1 output: %d\n", comms_state.ch1_output);

    sleep_ms(100);

    return comms_state;
}