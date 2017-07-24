#include "../headers/timers.h"

//2^8 = 256
//2^16 = 65_536
//2^32 = 4_294_967_296

//1 tick with no prescaler = 62.5 ns
//Prescaler 1: (CSn2:0 = 001) 
//Range: 62.5 ns ... 4095.9375 us

//Prescaler 8: (CSn2:0 = 010) 
//Range: 0.5 us ... 32767.5 us

//Prescaler 64: (CSn2:0 = 011) 
//Range: 4 us ... 262.140 ms

//Prescaler 256: (CSn2:0 = 100) 
//Range: 16 us ... 1048.560 ms

//Prescaler 1024: (CSn2:0 = 101) 
//Range: 64 us ... 4194.240 ms

static uint16_t get_prescaler_ns(double ns) {
	uint16_t result_presc = 0; //result prescaler's value

	if(ns < GET_MAX_NS(1)) {
		result_presc = 1;
	} else if(ns < GET_MAX_NS(8)) {
		result_presc = 8;
	} else if(ns < GET_MAX_NS(64)) {
		result_presc = 64;
	} else if(ns < GET_MAX_NS(256)) {
		result_presc = 256;
	} else if(ns < GET_MAX_NS(1024)) {
		result_presc = 1024;
	}

	return result_presc;
}

static uint8_t get_csbits(uint16_t prescaler) {
	uint8_t result = 0;
	switch(prescaler) {
		case 1: {
			result = 1;
			break;
		}
		case 8: {
			result = 2;
			break;
		}
		case 64: {
			result = 3;
			break;
		}
		case 256: {
			result = 4;
			break;
		}
		case 1024: {
			result = 5;
			break;
		}
		default: {}
	}

	return result;
}

void timer_init() {
	//Setting Clear Timer on Compare Mode (WGMn3:0 = 0100)
	TCCR1A = 0;
	TCCR1B = 0;

	TCCR1B |= _BV(WGM12);
}

void timer_start_ns(double ns) {
	//Setting prescaler
	uint16_t prescaler = get_prescaler_ns(ns);
	uint16_t value = (uint16_t)(ns / GET_PRESICION_NS(prescaler));

	USART0_print("ns: %f\n",ns);
	USART0_print("prescaler: %d\n",prescaler);
	USART0_print("value: %d\n",value);
	USART0_print("csbits: %d\n",get_csbits(prescaler));

	OCR1A = value;

	//Starting timer
	TCCR1B = (TCCR1B & 0xF8) | get_csbits(prescaler);

	//Implement ISR(TIMER1_COMPA_vect)
}

void timer_start_us(double us) {
	USART0_print("us: %f\n",us);
	timer_start_ns(us*1000);
}

void timer_start_ms(double ms) {
	USART0_print("ms: %f\n",ms);
	timer_start_us(ms*1000);
}

void timer_stop() {
	TCCR1B &= (~_BV(CS10)) & (~_BV(CS11)) & (~_BV(CS12));
}