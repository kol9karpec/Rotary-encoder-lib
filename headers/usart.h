#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ring_buffer.h"

#define LED_BIT 7
#define LED_DDR DDRB
#define LED_PORT PORTB 

#define GET_BIT(r,n) ((r >> n)&1)

//Declaration of buffers
extern ring_buffer_t transmit_buffer;
extern ring_buffer_t receive_buffer;
extern uint8_t isContinue;

#define DSPEED_MODE 0
#define BAUD_RATE(x) (F_CPU/((16/(int)pow(2.,DSPEED_MODE))*(x-1)))

void USART0_init(uint16_t baud_rate);
uint8_t USART0_print(const char * format, ...);

#endif //USART_H