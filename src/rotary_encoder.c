#include "../headers/rotary_encoder.h"

volatile uint8_t processing = 0;

encoder_driver_t encoder_driver = \
	{_default_rotate_right_func,
		_default_rotate_left_func,
	_default_button_click_func};

timer_tick_func_t timer_tick = _process_data;

void encoder_init(void) {
	ENCODER_DT_DDR &= ~_BV(ENCODER_DT);
	ENCODER_CLK_DDR &= ~_BV(ENCODER_CLK);
	ENCODER_SW_DDR &= ~_BV(ENCODER_SW);
	
	ENCODER_DT_PORT |= _BV(ENCODER_DT);
	ENCODER_CLK_PORT |= _BV(ENCODER_CLK);
	ENCODER_SW_PORT |= _BV(ENCODER_SW);
	
	PCICR |= _BV(PCIE0);
	PCMSK0 = _BV(PCINT6) | _BV(PCINT4);

	encoder_status.DT_PIN = 0;
	encoder_status.SW_PIN = 0;

	timer_init();
}

void rotator_on(void) {
	PCMSK2 |= _BV(PCINT6);
}

void rotator_off(void) {
	PCMSK2 &= ~_BV(PCINT6);
}

void button_on(void) {
	PCMSK2 |= _BV(PCINT4);
}

void button_off(void) {
	PCMSK2 &= ~_BV(PCINT4);
}

void _default_rotate_right_func(void) {
	USART0_print("Right!\n");
}

void _default_rotate_left_func(void) {
	USART0_print("Left!\n");
}

void _default_button_click_func(void) {
	USART0_print("Button clicked!\n");
}

void _process_data(void) {
	timer_stop();

	//reading encoder pins status
	encoder_status_t encoder_cur_status;
	encoder_cur_status.DT_PIN = \
			(ENCODER_DT_PIN & _BV(ENCODER_DT)) ? 1 : 0;

	encoder_cur_status.CLK_PIN = \
			(ENCODER_CLK_PIN & _BV(ENCODER_CLK)) ? 1 : 0;

	encoder_cur_status.SW_PIN = \
			(ENCODER_SW_PIN & _BV(ENCODER_SW)) ? 1 : 0;

	if((encoder_status.DT_PIN == 0) && \
		(encoder_cur_status.DT_PIN == 1)) {
		if(encoder_cur_status.CLK_PIN) {
			(*encoder_driver.rotate_right)();
		} else {
			(*encoder_driver.rotate_left)();
		}
	} 
	if((encoder_cur_status.SW_PIN == 0) && \
		(encoder_status.SW_PIN == 1)) {
		(*encoder_driver.button_click)();

	}

	//saving status
	encoder_status.DT_PIN = encoder_cur_status.DT_PIN;
	encoder_status.CLK_PIN = encoder_cur_status.CLK_PIN;
	encoder_status.SW_PIN = encoder_cur_status.SW_PIN;
	//USART0_print("Called process data!\n");
	//USART0_print("Status: DT: %u CLK: %u SW: %u\n",encoder_status.DT_PIN,encoder_status.CLK_PIN,encoder_status.SW_PIN);
	processing = 0;	
}

ISR(PCINT0_vect) {
	if(!processing) {
		timer_start_ns(500);
		processing = 1;
	}
}