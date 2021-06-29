/*
 * TestUno.c
 *
 * Created: 3/4/2021 22:51:08
 * Author : willi
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>

#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<PINB5);
	
    /* Replace with your application code */
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		_delay_ms(1000);
    }
}

