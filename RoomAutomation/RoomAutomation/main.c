/*
 * RoomAutomation.c
 *
 * Created: 08/07/2021 13:39:36
 * Author : William
 */ 
#include "boardinf.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <string.h>

#include "knobs/knobs.h"
#include "usart/usart.h"

#define MASK(x) (1 << x)


unsigned char strbuff[20];

ISR(USART_RX_vect){
	usart_ReceiveString(strbuff);
	usart_SendString(strbuff);//echo
	strcpy((char *)strbuff, "");
}


int main(void)
{
//  DDRB |= MASK(PORTB5);//enable pin 5 for output
// 	PORTB |= MASK(PORTB5);//set pin 5 to high

 	volatile int knobpos1 = 0;
	volatile long knobpos2 = 0;
	 
	 
	knobs_init();
	usart_Init(9600);
	
	sei();//enable uart interrupt
	while (1){

		knobpos1 = knobs_getPos1();
		
		usart_SendValueToText(knobpos1);
		
		
		//knobpos2 = knobs_getPos2();	
		_delay_ms(500);
		
	}
	return 0;
}

