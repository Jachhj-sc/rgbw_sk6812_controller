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

static uint32_t time_ms = 0; //variable for keeping track of time

//interrupt
ISR(TIMER0_COMPA_vect){
	time_ms++;
}

void init_timer0(void){
	TCCR0B |= (1<<CS01)|(1<<CS00);//set prescaler to /64
	OCR0A = (F_CPU/64000)-1;//CPU clock/(prescaler*1000)to get a frequency if 1ms/tick
	TIMSK0 |= (1<<OCIE0A);//enable ocr0A match interrupt
	TCCR0A |= (1<<WGM01);//clear timer on ocr0A match
}

uint32_t Get_time_ms(void){
	return time_ms;
}