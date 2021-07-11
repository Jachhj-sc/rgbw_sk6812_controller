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
char usart_RxChar();						/* Data receiving function */
void usart_TxChar(unsigned char data);					/* Data transmitting function */
void usart_SendString(unsigned char *str);				/* Send string of USART data function */
void usart_SendValueToText(uint8_t val);
void usart_BluetoothChanger(unsigned char Data_in);			/* Makes the micro controller send values */
void usart_ReceiveString(unsigned char *str);
void usart_ReceiveValue(unsigned char *hex);
void usart_clearRxBuff();
#endif