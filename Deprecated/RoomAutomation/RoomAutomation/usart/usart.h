/*
 *	usart.h
 *
 *	Author: William Hak
 *   Date : July 11, 2021
 */
#ifndef usart_H_FILE_H_				/* Define library H file if not defined */
#define usart_H_FILE_H_

#include <avr/io.h>							/* Include AVR std. library file */
#define BAUD_PRESCALE(x) (((F_CPU / (x * 16UL))) - 1)	/* Define prescale value */ //x = baudrate
#define settings 5
#define BL_BUFFERSIZE 10

void usart_Init(unsigned long BAUDRATE);				/* USART initialize function */
char usart_RxChar();									/* Raw data receiving function */
void usart_TxChar(char data);					/* Raw data transmitting function */
void usart_SendString(char *str);				/* Send string of USART data function */
void usart_SendValueToText(uint8_t val);				/* Send a value converted into ascii plus a \n*/
void usart_ReceiveString(char *str);			/* Receive a string*/
void usart_ReceiveFirstValue(char *hex);		/* Receive the first byte in the incoming stream and discard the rest*/
#endif