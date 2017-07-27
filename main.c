#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "./headers/usart.h"
//#include "./headers/timers.h"
#include "./headers/rotary_encoder.h"

#define LED_BIT 7
#define LED_DDR DDRB
#define LED_PORT PORTB

void led_init();

int main(void) {

	USART0_init(BAUD_RATE(115200));
	led_init();

	encoder_init();
	//rotator_on();
	//button_on();

	while(1) {

	}

	//Unreachable
	return 0;
}

void led_init() {
	LED_DDR |= _BV(LED_BIT);
	LED_PORT |= _BV(LED_BIT);
}