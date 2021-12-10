/*
 *	usart.c
 *
 *	Author: William Hak
 *   Date : July 11, 2021
 */
#include "../boardinf.h"
#include "usart.h"						/* Include USART header file */
#include <string.h>
#include <avr/interrupt.h>
#include <stdlib.h>


void usart_Init(unsigned long BAUDRATE)				/* USART initialize function */
{
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);				/* Enable USART transmitter and receiver */
	UCSR0C |= (1 << UCPOL0)| (1 << UCSZ00) | (1 << UCSZ01);	/* Write USCRC for 8 bit data and 1 stop bit */
	UBRR0L = BAUD_PRESCALE(BAUDRATE);							/* Load UBRRL with lower 8 bit of prescale value */
	UBRR0H = (BAUD_PRESCALE(BAUDRATE) >> 8);					/* Load UBRRH with upper 8 bit of prescale value */
	UCSR0B |= (1<<RXCIE0);//enable interrupt 
}

char usart_RxChar()									/* Data receiving function */
{
	while (!(UCSR0A & (1 << RXC0)));					/* Wait until new data receive */
	return(UDR0);									/* Get and return received data */
}

void usart_TxChar(char data)						/* Data transmitting function */
{
	while (!(UCSR0A & (1<<UDRE0)));					/* Wait until data transmit and buffer get empty */
	UDR0 = data;										/* Write data to be transmitting in UDR */

}

/*
* This function gets a string of characters from the USART.
* The string is placed in the array pointed to by str.
*
* - This function uses the function ReceiveByte() to get a byte
* from the usart.
* - If the received byte is equal to '\n' (Line Feed),
* the function returns.
* - The array is terminated with ?\0?.
*/

void usart_ReceiveString(char *str)
{
	uint8_t t = 0;

	while ((str[t++] = usart_RxChar()) != '\n');
	
	str[t] = '\0';
}

void usart_ReceiveFirstValue(char *hex)
{
	uint8_t t = 0;
	uint8_t Buff[10];
	
	while ((Buff[t] = (uint8_t)usart_RxChar()) != '\n')
	{
		t++;
	}
	Buff[t] = '\0';
	*hex = Buff[0];//only return the first received byte, discard the rest.
}

void usart_SendValueToText(uint8_t val){
	char buff[20];
	itoa(val, buff, 10);

//append \n after the number
	int a = 0;
	while (buff[++a] != '\0');
	buff[a] = '\n';
	buff[a+1] = '\0';
	
	int i = 0;
	while(buff[i] != '\0'){
		usart_TxChar((char)buff[i++]);
	}
	
		
}

void usart_SendString(char *str)									/* Send string of USART data function */
{
	int i = 0;
	while (str[i] != '\0'){
		usart_TxChar(str[i++]);					/* Send each char of string till the NULL */
	}
}
