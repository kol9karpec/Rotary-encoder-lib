#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart.h"
#include "timers.h"

#define ANALOG_PIN_8 0 //PCINT16
#define ANALOG_PIN_9 1 //PCINT17
#define ANALOG_PIN_10 2 //PCINT18

#define ENCODER_DT ANALOG_PIN_8
#define ENCODER_CLK ANALOG_PIN_9
#define ENCODER_SW ANALOG_PIN_10

#define ENCODER_DT_DDR DDRK
#define ENCODER_CLK_DDR DDRK
#define ENCODER_SW_DDR DDRK

#define ENCODER_DT_PORT PORTK
#define ENCODER_CLK_PORT PORTK
#define ENCODER_SW_PORT PORTK

#define ENCODER_DT_PIN PINK
#define ENCODER_CLK_PIN PINK
#define ENCODER_SW_PIN PINK

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

encoder_driver_t encoder_driver;

encoder_driver.rotate_right = \
		_default_rotate_right_func;
encoder_driver.rotate_left = \
		_default_rotate_left_func;
encoder_driver.button_click = \
		_default_button_click_func;

timer_tick = _process_data;

encoder_status_t encoder_status;

#endif //ROTARY_ENCODER_H