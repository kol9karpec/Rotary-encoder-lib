#ifndef TIMERS_H
#define TIMERS_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "usart.h"

#define GET_PRESICION_NS(prescaler) \
	(1000000000./((double)F_CPU/prescaler))

#define GET_PRESICION_US(prescaler) \
	(GET_PRESICION_NS(prescaler) / 1000.0)

#define GET_PRESICION_MS(prescaler) \
	(GET_PRESICION_US(prescaler) / 1000.0)

#define GET_MAX_NS(prescaler) \
	(GET_PRESICION_NS(prescaler)*65535.0)

#define GET_MAX_US(prescaler) \
	(GET_PRESICION_US(prescaler)*65535.0)

#define GET_MAX_MS(prescaler) \
	(GET_PRESICION_MS(prescaler)*65535.0)

typedef void (*timer_tick_func_t)(void);

void timer_init(void);

//up to 4_194_240_000 ns
void timer_start_ns(double ns);
void timer_start_us(double us);
void timer_start_ms(double ms);

void timer_stop(void);

void _def_timer_func(void);

extern timer_tick_func_t timer_tick;

#endif //TIMERS_H