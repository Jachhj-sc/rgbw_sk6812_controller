/*
 * timer.c
 *
 * Created: 18/11/2021 23:41:57
 *  Author: william
 *
 * General description:
 * functions for creating timer counters and non blocking delays
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t time_ms = 0; //variable for keeping track of time

//interrupt
ISR(TIMER0_COMPA_vect){
	if (time_ms > 60000){
		time_ms = 0;
	}
	
		time_ms++;	
}

void init_timer0(void){
	TCCR0B |= (1<<CS01)|(1<<CS00);//set prescaler to /64
	OCR0A = 235;
	TIMSK0 |= (1<<OCIE0A);//enable ocr0A match interrupt
	TCCR0A |= (1<<WGM01);//clear timer on ocr0A match
}

uint16_t Get_time_ms(void){
	return time_ms;
}