/*
 * RoomAutomation.c
 *
 * Created: 08/07/2021 13:39:36
 * Author : William
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "knobs/knobs.h"

#define MASK(x) (1 << x)

int main(void)
{
//  DDRB |= MASK(PORTB5);//enable pin 5 for output
// 	PORTB |= MASK(PORTB5);//set pin 5 to high

 	volatile int knobpos1 = 0;
	volatile long knobpos2 = 0;
	 
	knobs_init();
	
	while (1){

		knobpos1 = knobs_getPos1();	
		//knobpos2 = knobs_getPos2();	

		
	}
	return 0;
}

