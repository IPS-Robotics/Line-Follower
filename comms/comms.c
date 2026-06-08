#include "comms.h"
#include "../common.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

static volatile uint32_t rise_time[4];
static volatile uint32_t pulse_width[4];

static void comms_callback(uint gpio, uint32_t events)
{
    uint32_t now = time_us_32();

    int ch = gpio - 6;
/*
    int ch = -1;
    if (gpio == RECIEVER_PIN_CH1){
        ch = 0;
    } else if (gpio == RECIEVER_PIN_CH2){
        ch = 1;
    } else if (gpio == RECIEVER_PIN_CH3){
        ch = 2;
    } else if (gpio == RECIEVER_PIN_CH4){
        ch = 3;
    }
*/
    if (ch < 0 && ch > 4){
        return;
    }
    

    if (events & GPIO_IRQ_EDGE_RISE){
        //gpio_acknowledge_irq(RECIEVER_PIN_CH1, GPIO_IRQ_EDGE_RISE);
        rise_time[ch] = now;
    } 
    if (events & GPIO_IRQ_EDGE_FALL){
        //gpio_acknowledge_irq(RECIEVER_PIN_CH1, GPIO_IRQ_EDGE_FALL);
        pulse_width[ch] = time_us_32() - rise_time[ch];
    }
}

void comms_init() 
{

    gpio_set_irq_callback(comms_callback);
    irq_set_enabled(IO_IRQ_BANK0, true);

    for (int i = 0; i < 4; i++)
    {
        uint pin = RECIEVER_PIN_CH1 + i;
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_down(pin); 


    gpio_set_irq_enabled(pin,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true);
   
    }
    //printf("GPIO config done \n");
    //printf("IRQ set up \n");
}

static float normalize(uint32_t pulse, float min_val, float max_val){
    float x = (float)pulse;

    return ((x - min_val) / (max_val - min_val)) * 2.0f - 1.0f;
}

comms_output_state_t comms_read_CH() 
{
    comms_output_state_t comms_state;

    comms_state.ch1_output = normalize(pulse_width[0], 1000, 2000);
    comms_state.ch2_output = normalize(pulse_width[1], 1250, 1750);
    comms_state.ch3_output = pulse_width[2] > 1500? 1 : 0;
    comms_state.ch4_output = pulse_width[3] > 1500? 1 : 0;

    printf("CH1 output: %.2f CH2 output: %.2f CH3 output: %d CH4 output: %d \n", 
        comms_state.ch1_output,
        comms_state.ch2_output, 
        comms_state.ch3_output, 
        comms_state.ch4_output);

    sleep_ms(100);

    return comms_state;
}