/*
 * knobs.c
 *
 * Created: 09/07/2021 14:49:54
 *  Author: William
 */ 
#include "knobs.h"
#include <avr/io.h>
#include "../math_map/math_map.h"


#define knob1_Channel ADC4D
#define knob2_Channel ADC5D


void knobs_init(void){
	//set pc4 & 5 to input
	DDRC &= ~( (1<<PORTC4) | (1<<PORTC5) );


	ADMUX |= (1<<REFS0);//set reference voltage to Vcc
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	ADCSRB |= (1<<ADTS1);//set ADC auto trigger mode to Ext Interrupt
	
}

uint16_t knobs_getPos1(void){
	//while((ADCSRA & (1<<ADSC)));//wait for conversion to finish
	//update input channel
	ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));//reset mux
	ADMUX |= knob1_Channel;
	
	ADCSRA |= (1<<ADSC);//start conversion
	
	while((ADCSRA & (1<<ADSC)));//wait for conversion to finish

	return mapi(ADC, 0, 1023, 0, 255);
}

uint16_t knobs_getPos2(void){
	//while((ADCSRA & (1<<ADSC)));//wait for conversion to finish
	//update input channel
	ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));//reset mux
	ADMUX |= knob2_Channel;
		
	ADCSRA |= (1<<ADSC);//start conversion
	
	while((ADCSRA & (1<<ADSC)));//wait for conversion to finish
	
	return mapi(ADC, 0, 1023, 0, 255);
}