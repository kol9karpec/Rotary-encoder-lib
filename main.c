//Connect encoder as follows:
//CLK - Digital pin 21
//DT - Digital pin 20
//SW - Digital pin 19
//Ground

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>

#include "./headers/usart.h"

#define LED_BIT 7
#define LED_DDR DDRB
#define LED_PORT PORTB

#define DPIN12 6
#define DPIN11 5
#define DPIN21 INT0
#define DPIN20 INT1
#define DPIN19 INT2

#define ENCODER_IN1 DPIN21
#define ENCODER_IN2 DPIN20
#define ENCODER_BUTTON DPIN19
#define ENCODER_IN1_DDR DDRD
#define ENCODER_IN2_DDR DDRD
#define ENCODER_BUTTON_DDR DDRD
#define ENCODER_BUTTON_PORT PORTD
#define ENCODER_IN1_PORT PORTD
#define ENCODER_IN2_PORT PORTD
#define ENCODER_IN1_PIN PIND
#define ENCODER_IN2_PIN PIND
#define ENCODER_BUTTON_PIN PIND

#define GET_BIT(r,n) ((r >> n)&1)

int main(void) {

	USART0_init(BAUD_RATE(115200));

	while(1) {
		USART0_print("It works!\n");
		_delay_ms(1000);
	}


	return 0;
}