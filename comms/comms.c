#include "comms.h"
#include "../common.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"


static volatile uint32_t rise_time;
static volatile uint32_t pulse_width;

void comms_callback(uint gpio, uint32_t events){

    uint32_t event = gpio_get_irq_event_mask(RECIEVER_PIN_CH1);
    uint32_t now = time_us_32();

    if (event & GPIO_IRQ_EDGE_RISE){
        //gpio_acknowledge_irq(RECIEVER_PIN_CH1, GPIO_IRQ_EDGE_RISE);
        rise_time = now;
    } else {
        //gpio_acknowledge_irq(RECIEVER_PIN_CH1, GPIO_IRQ_EDGE_FALL);
        pulse_width = time_us_32() - rise_time;
    }

}

void comms_init() 
{
    stdio_init_all();
    printf("USB Started\n");
   
    uint pin = RECIEVER_PIN_CH1;
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    //gpio_pull_down(pin);

    printf("GPIO config done \n");


    gpio_set_irq_enabled_with_callback(
        pin, 
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, 
        true, &comms_callback);

    

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

comms_output_state comms_read_CH() 
{

    comms_output_state comms_state;

    comms_state.ch1_output = pulse_width;

    printf("Ch1:%lu \n",
       comms_state.ch1_output
    );

    sleep_ms(100);

    return comms_state;
}