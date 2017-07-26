#include "../headers/usart.h"

ring_buffer_t transmit_buffer;
ring_buffer_t receive_buffer;

volatile uint8_t isContinue = 0;

void USART0_init(uint16_t baud_rate) {
	SREG &= ~_BV(7);
	//Setting baud rate
	UBRR0 = baud_rate;

	//Enabling double speed mode
	UCSR0A = (_BV(U2X0) & DSPEED_MODE);

	//Setting up frame format
	//Setting character size to 8
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);

	//Enabling transmitter and receiver
	UCSR0B = _BV(TXEN0) | _BV(RXEN0) | _BV(RXCIE0);

	clean(&transmit_buffer);
	clean(&receive_buffer);
	isContinue = 0;

	SREG |= _BV(7);
}
/*
static int uart_putchar(char c, FILE *stream);
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
 
static int uart_putchar(char c, FILE *stream)
{
   if (c == '\n')
      uart_putchar('\r', stream);
 	while(!GET_BIT(UCSR0A,UDRE0)) {}
   UDR0 = c;
   return 0;
}
*/
uint8_t USART0_print(const char * format, ...) {
	while(isContinue) {}

	uint8_t result = 1;

	//stdout = &mystdout;

	va_list arg_list; 

	char * result_str = (char*)(malloc(DEF_SIZE*sizeof(char)));
	uint8_t _strlen = 0;
	uint8_t i = 0;

	va_start(arg_list,format); //saving list of arguments
	vsnprintf(result_str,DEF_SIZE-1,format,arg_list); //generating final string
	//printf("printf: %s",result_str);
	va_end(arg_list);
	_strlen = strlen(result_str);

	for(i=0 ; i<_strlen ; i++) {
		if(!push((uint8_t)(result_str[i]),&transmit_buffer)) {
			result = 0;
			clean(&transmit_buffer);
			break;
		}
	}

	free(result_str);	

	if(_strlen != 0) {
		isContinue = pop(&UDR0,&transmit_buffer);
		UCSR0B |= _BV(UDRIE0);
	}

	return result;
}

ISR(USART0_UDRE_vect) {
	UCSR0B &= ~_BV(UDRIE0);
	if(isContinue) {
		UCSR0B |= _BV(UDRIE0);
		isContinue = pop(&UDR0,&transmit_buffer);		
	}
}

ISR(USART0_RX_vect) {
	push((UDR0-128),&receive_buffer);
}