#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "timers.h"

#define D_PIN_12 6 //PCINT6
#define D_PIN_11 5 //PCINT5
#define D_PIN_10 4 //PCINT4

#define ENCODER_DT D_PIN_12
#define ENCODER_CLK D_PIN_11
#define ENCODER_SW D_PIN_10

#define ENCODER_DT_DDR DDRB
#define ENCODER_CLK_DDR DDRB
#define ENCODER_SW_DDR DDRB

#define ENCODER_DT_PORT PORTB
#define ENCODER_CLK_PORT PORTB
#define ENCODER_SW_PORT PORTB

#define ENCODER_DT_PIN PINB
#define ENCODER_CLK_PIN PINB
#define ENCODER_SW_PIN PINB

typedef struct {
	void (*rotate_right)(void);
	void (*rotate_left)(void);
	void (*button_click)(void);
} encoder_driver_t;

typedef struct {
	volatile uint8_t DT_PIN;
	volatile uint8_t CLK_PIN;
	volatile uint8_t SW_PIN;
} encoder_status_t;

void encoder_init(void);
void rotator_on(void);
void rotator_off(void);
void button_on(void);
void button_off(void);

volatile uint8_t processing;

void _default_rotate_right_func(void);
void _default_rotate_left_func(void);
void _default_button_click_func(void);
void _process_data(void);

extern encoder_driver_t encoder_driver;
/*
encoder_driver.rotate_right = \
		_default_rotate_right_func;
encoder_driver.rotate_left = \
		_default_rotate_left_func;
encoder_driver.button_click = \
		_default_button_click_func;
*/

encoder_status_t encoder_status;

#endif //ROTARY_ENCODER_H