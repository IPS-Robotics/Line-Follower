#ifndef COMMS_H
    #define COMMS_H

// ===== CONSTANTS =====

#define RECIEVER_PIN_CH1 6
#define RECIEVER_PIN_CH2 7
#define RECIEVER_PIN_CH3 8
#define RECIEVER_PIN_CH4 9

// ===== STRUCTS =====

typedef struct {
    float ch1_output;
    float ch2_output;
    int ch3_output;
    int ch4_output;
} comms_output_state_t;

// ===== API =====

void comms_init();
comms_output_state_t comms_read_CH();

#endif