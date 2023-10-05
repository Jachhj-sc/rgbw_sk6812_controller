/*
 * buttons.c
 *
 * Created: 06/07/2022 23:47:05
 *  Author: William Hak
 */ 

#include "buttons.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

volatile sw_statusflag_t buttonFlag = {0};

void buttons_init(void){
//initialize buttons
	DDRB |= (1<<PORTB5);
	
	DDRC &= ~(BUT0_MASK | BUT1_MASK | BUT2_MASK);
	//enable pullup
	PORTC |= BUT0_MASK | BUT1_MASK | BUT2_MASK;
	
	//enable interrupt
	PCICR |= (1<<PCIE1);
	
	PCMSK1 |= (1<<PCINT8) | (1<<PCINT9) | (1<<PCINT10);
}

ISR(PCINT1_vect){//button interrupt, and set flag for button
	 //check which button was pressed.
	if(!((BUT0_PIN & BUT0_MASK) == BUT0_MASK)){
		 buttonFlag.button0 = 1;//if Button on PINC0 is pressed
	}
	if(!((BUT1_PIN & BUT1_MASK) == BUT1_MASK)){ 
		buttonFlag.button1 = 1;
	}
	if(!((BUT2_PIN & BUT2_MASK) == BUT2_MASK)){ 
		buttonFlag.button2 = 1;
	}
}
