/*
 * buttons.c
 *
 * Created: 06/07/2022 23:47:05
 *  Author: William Hak
 */ 

#include "buttons.h"
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/delay.h>

volatile sw_statusflag_t buttonflag = {0};

void buttons_init(void){
//initialize buttons
	DDRB |= (1<<PORTB5);
	
	DDRC &= ~(BUT0 | BUT1 | BUT2);
	//enable pullup
	PORTC |= BUT0 | BUT1 | BUT2;
	
	//enable interrupt
	PCICR |= PCIE1;
	PCMSK1 |= (1<<PCINT8) | (1<<PCINT9) | (1<<PCINT10);
}

ISR(PCINT1_vect){//button interrupt, and set flag for button
	 //check which button was pressed.
	if(!((BUT0_PIN & BUT0) == BUT0)){
		 buttonflag.button0 = 1;//if Button on PINC0 is pressed
	}
	if(!((BUT1_PIN & BUT1) == BUT1)){ 
		buttonflag.button1 = 1;
	}
	if(!((BUT2_PIN & BUT2) == BUT2)){ 
		buttonflag.button2 = 1;
	}
}
