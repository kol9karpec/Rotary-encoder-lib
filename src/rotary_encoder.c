#include "../headers/rotary_encoder.h"

volatile uint8_t processing = 0;

void encoder_init(void) {
	ENCODER_DT_DDR &= ~_BV(ENCODER_DT);
	ENCODER_CLK_DDR &= ~_BV(ENCODER_CLK);
	ENCODER_SW_DDR &= ~_BV(ENCODER_SW);

	ENCODER_DT_PORT |= _BV(ENCODER_DT);
	ENCODER_CLK_PORT |= _BV(ENCODER_CLK);
	ENCODER_SW_PORT |= _BV(ENCODER_SW);

	PCICR |= _BV(PCIE2);
	PCMSK2 |= _BV(PCINT16) | _BV(PCINT18);

	timer_init();

	//Implement correspoding ISR()
}

void rotator_on(void) {
	PCMSK2 |= _BV(PCINT16);
}

void rotator_off(void) {
	PCMSK2 &= ~_BV(PCINT16);
}

void button_on(void) {
	PCMSK2 |= _BV(PCINT18);
}

void button_off(void) {
	PCMSK2 &= ~_BV(PCINT18);
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
			ENCODER_DT_PIN & _BV(ENCODER_DT);

	encoder_cur_status.CLK_PIN = \
			ENCODER_CLK_PIN & _BV(ENCODER_CLK);

	encoder_cur_status.SW_PIN = \
			ENCODER_SW_PIN & _BV(ENCODER_SW);

	if((encoder_status.DT_PIN == 0) && \
		(encoder_cur_status.DT_PIN == 1)) {
		if(encoder_cur_status.CLK_PIN) {
			(*encoder_driver.rotate_right)();
		} else {
			(*encoder_driver.rotate_left)();
		}
	} else if((encoder_status.SW_PIN == 0) && \
		(encoder_cur_status.SW_PIN == 1)) {
		(*encoder_driver.button_click)();
	}

	//saving status
	encoder_status.DT_PIN = encoder_cur_status.DT_PIN;
	encoder_status.CLK_PIN = encoder_cur_status.CLK_PIN;
	encoder_status.SW_PIN = encoder_cur_status.SW_PIN;	
	processing = 0;	
}

ISR(PCINT2_vect) {
	if(!processing) {
		timer_start_ns(500);
		processing = 1;
	}
}