/*
 * USART.c
 *
 * Created: 6/3/2013 2:02:42 AM
 *  Author: Quentin
 */ 
//This sets up the USART_1 for 9600 baud and it creates sub-functions
//to send and receive data.
//This FILE also redirects stdout from printf to the TX pin
//FILE transmit = FDEV_SETUP_STREAM(usart_put_char, NULL, _FDEV_SETUP_WRITE ); is necessary in the main file
//stdout=&stdout is necessary as wel

#include <util/delay.h>
#include <avr/io.h>
#include <avr/signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/iom128a.h>
#include <math.h>
unsigned char USART_data1;

unsigned char recieve_data1(void)
{
	
	while (! (UCSR1A &(1 << RXC1)));
	return UDR1;
}

void transmit_data1 (unsigned char data1)
{
	//Wait until the Transmitter is ready
	while (! (UCSR1A & (1 << UDRE1)) );

	//Sends out data
	UDR1 = data1;
}


void USART_initialize1( void)
{
	unsigned int UBBR = 47;

	//Put the upper part of the baud number here (bits 8 to 11)
	UBRR1H = (unsigned char) (UBBR >> 8);
	//Put the remaining part of the baud number here
	UBRR1L = (unsigned char) UBBR;

	//Enable the receiver and transmitter no parity and 1 stop bit
	UCSR1B = (1 << RXEN1) | (1 << TXEN1)| (1 << RXCIE1);
	UCSR1C = (0 << USBS1) | (3 << UCSZ10) |(0 << UPM11) | (0 <<UPM10);
}
void USART_De_initialze1(void)
{
	UCSR1B = (0 << RXEN1) | (0 << TXEN1)| (0 << RXCIE1);
	UCSR1C = (0 << USBS1) | (3 << UCSZ10) |(0 << UPM11) | (0 <<UPM10);
}
