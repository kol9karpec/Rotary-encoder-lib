#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "./headers/usart.h"

#define LED_BIT 7
#define LED_DDR DDRB
#define LED_PORT PORTB

#define GET_BIT(r,n) ((r >> n)&1)

int main(void) {

	USART0_init(BAUD_RATE(115200));

	while(1) {
		
		
		_delay_ms(1000);
	}

	//Unreachable
	return 0;
}