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

void update(char *instruct); /* this function is called when a interrupt triggers and there needs to be something updated immediately*/


ISR(USART_RX_vect){
	static char strbuff[20];
	usart_ReceiveString(strbuff);
	update(strbuff);
}

void update(char *instruct){
	instruct[1] = 0;
	
	
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
	
	usart_SendString("boot successful");
	
	while (1){

		
	}
	return 0;
}

