/*
 * buttons.h
 *
 * Created: 06/07/2022 23:47:15
 *  Author: William Hak
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_
#include <avr/io.h>
#include <avr/interrupt.h>

typedef struct  
{
	uint8_t button0;
	uint8_t button1;
	uint8_t button2;
} sw_statusflag_t;

extern volatile sw_statusflag_t buttonflag;

#define BUT0_SHIFT PINC0
#define BUT0 (1<<BUT0_SHIFT)
#define BUT0_PORT PORTC
#define BUT0_DDR DDRC
#define BUT0_PIN PINC

#define BUT1_SHIFT PINC1
#define BUT1 (1<<BUT1_SHIFT)
#define BUT1_PORT PORTC
#define BUT1_DDR DDRC
#define BUT1_PIN PINC

#define BUT2_SHIFT PINC2	
#define BUT2 (1<<BUT2_SHIFT)
#define BUT2_PORT PORTC
#define BUT2_DDR DDRC
#define BUT2_PIN PINC

void buttons_init(void);

#endif /* BUTTONS_H_ */