#ifndef COMMS_H
#define COMMS_H

// ===== CONSTANTS =====

#define RECIEVER_PIN_CH1 6
#define RECIEVER_PIN_CH2 7
#define RECIEVER_PIN_CH3 8
#define RECIEVER_PIN_CH4 9

// ===== API =====

void comms_init();
void comms_read_CH();

#endif