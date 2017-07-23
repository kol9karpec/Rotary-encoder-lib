#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DEF_SIZE 256

typedef struct ring_buffer_t {
	uint8_t data[DEF_SIZE];

	volatile uint8_t start;
	volatile uint8_t end;
} ring_buffer_t;

uint8_t push(uint8_t data, ring_buffer_t * ring_buffer);
uint8_t pop(volatile uint8_t * dest, ring_buffer_t * ring_buffer);
uint8_t is_empty(ring_buffer_t * ring_buffer);
void clean(ring_buffer_t * ring_buffer);

#endif //RING_BUFFER_H