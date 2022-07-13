/*
 * knobs.c
 *
 * Created: 09/07/2021 14:49:54
 *  Author: William
 */ 
#include "knob.h"
#include <avr/io.h>
#include "../math_map/math_map.h"
#include <math.h>

#define knob1_Channel ADC4D
#define knob2_Channel ADC5D



void knob_init(void){
	//set pc4 & 5 to input
	KNOB0_DDR &= ~( KNOB0_MASK | KNOB1_MASK );

	ADMUX |= (1<<REFS0);//set reference voltage to Vcc
	ADCSRA |=  (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);;//Analog to digital converter enable, AD start conversion
	ADCSRB |= (1<<ADTS1);//set ADC auto trigger mode to Ext Interrupt
	
}

uint16_t knob_getPos(uint8_t knob_shift){
	//while((ADCSRA & (1<<ADSC)));//wait for conversion to finish
	//update input channel
	ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3));//reset mux
	ADMUX |= knob_shift;
	
	ADCSRA |= (1<<ADSC);//start conversion
	
	while((ADCSRA & (1<<ADSC)));//wait for conversion to finish

	return ADC;
}
