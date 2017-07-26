#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "./headers/usart.h"
#include "./headers/timers.h"

#define LED_BIT 7
#define LED_DDR DDRB
#define LED_PORT PORTB

#define GET_BIT(r,n) ((r >> n)&1)

void led_init();

volatile int counter = 0;

int main(void) {

	USART0_init(BAUD_RATE(115200));
	led_init();
	timer_init();

	timer_start_ms(1000);

	while(1) {

	}

	//Unreachable
	return 0;
}

ISR(TIMER1_COMPA_vect) {
	//USART0_print("Interrupt!\n");
	LED_PORT ^= _BV(LED_BIT);
	counter++;
	if(counter == 10) {
		timer_stop();
	}
}

void led_init() {
	LED_DDR |= _BV(LED_BIT);
	LED_PORT |= _BV(LED_BIT);
}