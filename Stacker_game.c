/*
 * $safeprojectname$.c
 *
 * Created: 10/3/2014 9:35:37 PM
 *  Author: Quentin
 */ 


#ifndef F_CPU
#define F_CPU 7372800UL // frequency of the atmega128a clock used to make delay work properly.
#endif
#include <util/delay.h>
#include <avr/io.h>
#include <avr/signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/iom128a.h>
#include <math.h>
#include "Interrupts_atmega128a.h"
#include "Ports_lib_atmega128a.h"
#include "LED_Matrix_atmega128a.h"
#include "USART0_atmega128a.h"
#include "Timer_atmega128a.h"
FILE transmit = FDEV_SETUP_STREAM(usart_put_char, NULL, _FDEV_SETUP_WRITE );
char Dig_1 = 0x01;
char Dig_2 = 0x02;
char Dig_3 = 0x03;
char Dig_4 = 0x04;
char Dig_5 = 0x05;
char Dig_6 = 0x06;
char Dig_7 = 0x07;
char Dig_8 = 0x08;
char Row_1 = 0x00;
char Row_2 = 0x00;
char Row_3 = 0x00;
char Row_4 = 0x00;
char Row_5 = 0x00;
char Row_6 = 0x00;
char Row_7 = 0x00;
char Row_8 = 0x00;
char Row_9 = 0x00;
char Row_10 = 0x00;
char Row_11 = 0x00;
char Row_12 = 0x00;
char Row_13 = 0x00;
char Row_14 = 0x00;
char Row_15 = 0x00;
char Row_16 = 0x00;
char Row1_1 = 0x00;
char Row2_2 = 0x00;
char Row3_3 = 0x00;
char Row4_4 = 0x00;
char Row5_5 = 0x00;
char Row6_6 = 0x00;
char Row7_7 = 0x00;
char Row8_8 = 0x00;
char Row9_9 = 0x00;
char Row10_10 = 0x00;
char Row11_11 = 0x00;
char Row12_12 = 0x00;
char Row13_13 = 0x00;
char Row14_14 = 0x00;
char Row15_15 = 0x00;
char Row16_16 = 0x00;
char Status1 = 0x00;
char Status2 = 0x00;
char Status3 = 0x00;
char Status4 = 0x00;
char Status11 = 0x00;
char Status22 = 0x00;
char Status33 = 0x00;
char Status44 = 0x00;
char comparison1 = 0x00;
char comparison2 = 0x00;
char compare = 0x80;
char Row_counter = 1;
char rotate_number = 0;
char rotate_sucess = 0;
char rotate_numberZ1 = 0;
char rotate_sucessZ1 = 0;
char rotate_numberZ2 = 0;
char rotate_sucessZ2 = 0;
char rotate_numberL1 = 0;
char rotate_sucessL1 = 0;
char rotate_numberL2 = 0;
char rotate_sucessL2 = 0;
char rotate_numberBAR = 0;
char rotate_sucessBAR = 0;
long int clear_counter = 0;
int clear_counter_Row1 = 0;
int clear_counter_Row2 = 0;
int clear_counter_Row3 = 0;
int clear_counter_Row4 = 0;
int clear_counter_Row5 = 0;
int clear_counter_Row6 = 0;
int clear_counter_Row7 = 0;
int clear_counter_Row8 = 0;
int clear_counter_Row9 = 0;
int clear_counter_Row10 = 0;
int clear_counter_Row11 = 0;
int clear_counter_Row12 = 0;
int clear_counter_Row13 = 0;
int clear_counter_Row14 = 0;
int clear_counter_Row15 = 0;
int clear_counter_Row16 = 0;
int occupy = 0;
int pause_var = 0;
long int Score_counter = 0;
int ii = 0;
int jj = 1;
int bb = 0;
int cc =0x00;
void Transmit2();
long int random_shape = 1;
long int delayVar = 500;
extern int a;
extern int b;
//Interrupt vector INT3 which is located on PIND3
ISR(INT0_vect)
{

}

//Interrupt vector INT2 which is located on PIND0
ISR(USART0_RX_vect)
{
	//random_shape = random_num();
	a = ((4*TCNT0 + 15)%10);
	b = ((2*TCNT0 + 10)%20);
	Status11 = Status1;
	Status22 = Status2;
	Status33 = Status3;
	cc = recieve_data0();
if(cc == 0x73)
{
	{ delayVar = 35;}
}
if((cc == 0x77 || cc == 0x61 || cc == 0x64) && jj != 0x7B)
{
	if (Row_counter == 1)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_16 - Status1)) == 0 && (Status2 << 1 & (Row_15 - Status2)) == 0 && (Status3 << 1 & (Row_14 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_16 - Status1)) == 0 && (Status2 >> 1 & (Row_15 - Status2)) == 0 && (Status3 >> 1 & (Row_14 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_15-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)	{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_14 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_15-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_16 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_14 & (Status2 & Status1)) == 0 && ((Row_16 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_16 - Status1)& (Status1>>1)) == 0 && ((Row_16 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_14 & (Status2 & Status1)) == 0 && ((Row_16 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_16 - Status1)& (Status1<<1)) == 0 && ((Row_16 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_14 - Status3) & Status3 << 1) == 0 && ((Row_14 - Status3) & Status3 << 2) == 0 && (Row_16 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_16 - Status1) & Status1 << 1) == 0 && ((Row_15 - Status2) & Status2 << 1) == 0 && ((Row_15 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_16 - Status1) & Status1 >> 1) == 0 && ((Row_16 - Status1) & Status1 >> 2) == 0 && (Row_14 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_14 - Status3) & Status3 >> 1) == 0 && ((Row_15 - Status2) & Status2 << 1) == 0 && ((Row_15 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_14 - Status3) & Status3 >> 1) == 0 && ((Row_14 - Status3) & Status3 >> 2) == 0 && (Row_16 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_16 - Status1) & Status1 >> 1) == 0 && ((Row_15 - Status2) & Status2 >> 1) == 0 && ((Row_15 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_16 - Status1) & Status1 << 1) == 0 && ((Row_16 - Status1) & Status3 << 2) == 0 && (Row_14 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_14 - Status3) & Status3 << 1) == 0 && ((Row_15 - Status2) & Status2 >> 1) == 0 && ((Row_15 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_15-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_14 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_16 = Row_16 - Status11;
		Row_15 = Row_15 - Status22;
		Row_14 = Row_14 - Status33;
		
		Row_16 = Status1 + Row_16;
		Row_15 = Status2 + Row_15;
		Row_14 = Status3 + Row_14;
		Transmit2();
	}
	
	if (Row_counter == 2)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_15 - Status1)) == 0 && (Status2 << 1 & (Row_14 - Status2)) == 0 && (Status3 << 1 & (Row_13 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1;}
		if (cc == 0x64 && (Status1 >> 1 & (Row_15 - Status1)) == 0 && (Status2 >> 1 & (Row_14 - Status2)) == 0 && (Status3 >> 1 & (Row_13 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_14-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)	{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_13 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_14-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}	
		if (cc == 0x77 && rotate_number == 4 && ((Row_15 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_13 & (Status2 & Status1)) == 0 && ((Row_15 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_15 - Status1)& (Status1>>1)) == 0 && ((Row_15 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_13 & (Status2 & Status1)) == 0 && ((Row_15 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_15 - Status1)& (Status1<<1)) == 0 && ((Row_15 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_13 - Status3) & Status3 << 1) == 0 && ((Row_13 - Status3) & Status3 << 2) == 0 && (Row_15 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_15 - Status1) & Status1 << 1) == 0 && ((Row_14 - Status2) & Status2 << 1) == 0 && ((Row_14 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_15 - Status1) & Status1 >> 1) == 0 && ((Row_15 - Status1) & Status1 >> 2) == 0 && (Row_13 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_13 - Status3) & Status3 >> 1) == 0 && ((Row_14 - Status2) & Status2 << 1) == 0 && ((Row_14 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_13 - Status3) & Status3 >> 1) == 0 && ((Row_13 - Status3) & Status3 >> 2) == 0 && (Row_15 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_15 - Status1) & Status1 >> 1) == 0 && ((Row_14 - Status2) & Status2 >> 1) == 0 && ((Row_14 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_15 - Status1) & Status1 << 1) == 0 && ((Row_15 - Status1) & Status3 << 2) == 0 && (Row_13 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_13 - Status3) & Status3 << 1) == 0 && ((Row_14 - Status2) & Status2 >> 1) == 0 && ((Row_14 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_14-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_13 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_15 = Row_15 - Status11;
		Row_14 = Row_14 - Status22;
		Row_13 = Row_13 - Status33;
		
		Row_15 = Status1 + Row_15;
		Row_14 = Status2 + Row_14;
		Row_13 = Status3 + Row_13;
		Transmit2();
	}
	
	if (Row_counter == 3)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_14 - Status1)) == 0 && (Status2 << 1 & (Row_13 - Status2)) == 0 && (Status3 << 1 & (Row_12 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1;}
		if (cc == 0x64 && (Status1 >> 1 & (Row_14 - Status1)) == 0 && (Status2 >> 1 & (Row_13 - Status2)) == 0 && (Status3 >> 1 & (Row_12 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_13-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)	{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_12 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_13-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_14 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_12 & (Status2 & Status1)) == 0 && ((Row_14 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_14 - Status1)& (Status1>>1)) == 0 && ((Row_14 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_12 & (Status2 & Status1)) == 0 && ((Row_14 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_14 - Status1)& (Status1<<1)) == 0 && ((Row_14 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_12 - Status3) & Status3 << 1) == 0 && ((Row_12 - Status3) & Status3 << 2) == 0 && (Row_14 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_14 - Status1) & Status1 << 1) == 0 && ((Row_13 - Status2) & Status2 << 1) == 0 && ((Row_13 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_14 - Status1) & Status1 >> 1) == 0 && ((Row_14 - Status1) & Status1 >> 2) == 0 && (Row_12 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_12 - Status3) & Status3 >> 1) == 0 && ((Row_13 - Status2) & Status2 << 1) == 0 && ((Row_13 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_12 - Status3) & Status3 >> 1) == 0 && ((Row_12 - Status3) & Status3 >> 2) == 0 && (Row_14 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_14 - Status1) & Status1 >> 1) == 0 && ((Row_13 - Status2) & Status2 >> 1) == 0 && ((Row_13 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_14 - Status1) & Status1 << 1) == 0 && ((Row_14 - Status1) & Status3 << 2) == 0 && (Row_12 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_12 - Status3) & Status3 << 1) == 0 && ((Row_13 - Status2) & Status2 >> 1) == 0 && ((Row_13 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_13-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_12 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_14 = Row_14 - Status11;
		Row_13 = Row_13 - Status22;
		Row_12 = Row_12 - Status33;
		
		Row_14 = Status1 + Row_14;
		Row_13 = Status2 + Row_13;
		Row_12 = Status3 + Row_12;
		Transmit2();
	}
	
	if (Row_counter == 4)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_13 - Status1)) == 0 && (Status2 << 1 & (Row_12 - Status2)) == 0 && (Status3 << 1 & (Row_11 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_13 - Status1)) == 0 && (Status2 >> 1 & (Row_12 - Status2)) == 0 && (Status3 >> 1 & (Row_11 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_12-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)	{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_11 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_12-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_13 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_11 & (Status2 & Status1)) == 0 && ((Row_13 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_13 - Status1)& (Status1>>1)) == 0 && ((Row_13 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}			
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_11 & (Status2 & Status1)) == 0 && ((Row_13 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_13 - Status1)& (Status1<<1)) == 0 && ((Row_13 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_11 - Status3) & Status3 << 1) == 0 && ((Row_11 - Status3) & Status3 << 2) == 0 && (Row_13 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_13 - Status1) & Status1 << 1) == 0 && ((Row_12 - Status2) & Status2 << 1) == 0 && ((Row_12 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_13 - Status1) & Status1 >> 1) == 0 && ((Row_13 - Status1) & Status1 >> 2) == 0 && (Row_11 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_11 - Status3) & Status3 >> 1) == 0 && ((Row_12 - Status2) & Status2 << 1) == 0 && ((Row_12 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_11 - Status3) & Status3 >> 1) == 0 && ((Row_11 - Status3) & Status3 >> 2) == 0 && (Row_13 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_13 - Status1) & Status1 >> 1) == 0 && ((Row_12 - Status2) & Status2 >> 1) == 0 && ((Row_12 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_13 - Status1) & Status1 << 1) == 0 && ((Row_13 - Status1) & Status3 << 2) == 0 && (Row_11 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_11 - Status3) & Status3 << 1) == 0 && ((Row_12 - Status2) & Status2 >> 1) == 0 && ((Row_12 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_12-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_11 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_13 = Row_13 - Status11;
		Row_12 = Row_12 - Status22;
		Row_11 = Row_11 - Status33;
		
		Row_13 = Status1 + Row_13;
		Row_12 = Status2 + Row_12;
		Row_11 = Status3 + Row_11;
		Transmit2();
	}
	
	if (Row_counter == 5)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_12 - Status1)) == 0 && (Status2 << 1 & (Row_11 - Status2)) == 0 && (Status3 << 1 & (Row_10 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1;}
		if (cc == 0x64 && (Status1 >> 1 & (Row_12 - Status1)) == 0 && (Status2 >> 1 & (Row_11 - Status2)) == 0 && (Status3 >> 1 & (Row_10 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_11-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)	{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_10 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_11-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_12 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_10 & (Status2 & Status1)) == 0 && ((Row_12 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_12 - Status1)& (Status1>>1)) == 0 && ((Row_12 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_10 & (Status2 & Status1)) == 0 && ((Row_12 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_12 - Status1)& (Status1<<1)) == 0 && ((Row_12 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_10 - Status3) & Status3 << 1) == 0 && ((Row_10 - Status3) & Status3 << 2) == 0 && (Row_12 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_12 - Status1) & Status1 << 1) == 0 && ((Row_11 - Status2) & Status2 << 1) == 0 && ((Row_11 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_12 - Status1) & Status1 >> 1) == 0 && ((Row_12 - Status1) & Status1 >> 2) == 0 && (Row_10 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_10 - Status3) & Status3 >> 1) == 0 && ((Row_11 - Status2) & Status2 << 1) == 0 && ((Row_11 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_10 - Status3) & Status3 >> 1) == 0 && ((Row_10 - Status3) & Status3 >> 2) == 0 && (Row_12 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_12 - Status1) & Status1 >> 1) == 0 && ((Row_11 - Status2) & Status2 >> 1) == 0 && ((Row_11 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_12 - Status1) & Status1 << 1) == 0 && ((Row_12 - Status1) & Status3 << 2) == 0 && (Row_10 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_10 - Status3) & Status3 << 1) == 0 && ((Row_11 - Status2) & Status2 >> 1) == 0 && ((Row_11 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_11-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_10 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_12 = Row_12 - Status11;
		Row_11 = Row_11 - Status22;
		Row_10 = Row_10 - Status33;
		
		Row_12 = Status1 + Row_12;
		Row_11 = Status2 + Row_11;
		Row_10 = Status3 + Row_10;
		Transmit2();
	}
	
	if (Row_counter == 6)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_11 - Status1)) == 0 && (Status2 << 1 & (Row_10 - Status2)) == 0 && (Status3 << 1 & (Row_9 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1;}
		if (cc == 0x64 && (Status1 >> 1 & (Row_11 - Status1)) == 0 && (Status2 >> 1 & (Row_10 - Status2)) == 0 && (Status3 >> 1 & (Row_9 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_10-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)	{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_9 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_10-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_11 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_9 & (Status2 & Status1)) == 0 && ((Row_11 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_11 - Status1)& (Status1>>1)) == 0 && ((Row_11 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}			
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_9 & (Status2 & Status1)) == 0 && ((Row_11 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_11 - Status1)& (Status1<<1)) == 0 && ((Row_11 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_9 - Status3) & Status3 << 1) == 0 && ((Row_9 - Status3) & Status3 << 2) == 0 && (Row_11 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_11 - Status1) & Status1 << 1) == 0 && ((Row_10 - Status2) & Status2 << 1) == 0 && ((Row_10 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_11 - Status1) & Status1 >> 1) == 0 && ((Row_11 - Status1) & Status1 >> 2) == 0 && (Row_9 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_9 - Status3) & Status3 >> 1) == 0 && ((Row_10 - Status2) & Status2 << 1) == 0 && ((Row_10 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_9 - Status3) & Status3 >> 1) == 0 && ((Row_9 - Status3) & Status3 >> 2) == 0 && (Row_11 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_11 - Status1) & Status1 >> 1) == 0 && ((Row_10 - Status2) & Status2 >> 1) == 0 && ((Row_10 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_11 - Status1) & Status1 << 1) == 0 && ((Row_11 - Status1) & Status3 << 2) == 0 && (Row_9 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_9 - Status3) & Status3 << 1) == 0 && ((Row_10 - Status2) & Status2 >> 1) == 0 && ((Row_10 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_10-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_9 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_11 = Row_11 - Status11;
		Row_10 = Row_10 - Status22;
		Row_9 = Row_9 - Status33;
		
		Row_11 = Status1 + Row_11;
		Row_10 = Status2 + Row_10;
		Row_9 = Status3 + Row_9;
		Transmit2();
	}
	
	if (Row_counter == 7)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_10 - Status1)) == 0 && (Status2 << 1 & (Row_9 - Status2)) == 0 && (Status3 << 1 & (Row_8 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_10 - Status1)) == 0 && (Status2 >> 1 & (Row_9 - Status2)) == 0 && (Status3 >> 1 & (Row_8 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_9-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)		{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_8 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_9-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_10 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_8 & (Status2 & Status1)) == 0 && ((Row_10 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_10 - Status1)& (Status1>>1)) == 0 && ((Row_10 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}			
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_8 & (Status2 & Status1)) == 0 && ((Row_10 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_10 - Status1)& (Status1<<1)) == 0 && ((Row_10 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_8 - Status3) & Status3 << 1) == 0 && ((Row_8 - Status3) & Status3 << 2) == 0 && (Row_10 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_10 - Status1) & Status1 << 1) == 0 && ((Row_9 - Status2) & Status2 << 1) == 0 && ((Row_9 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_10 - Status1) & Status1 >> 1) == 0 && ((Row_10 - Status1) & Status1 >> 2) == 0 && (Row_8 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_8 - Status3) & Status3 >> 1) == 0 && ((Row_9 - Status2) & Status2 << 1) == 0 && ((Row_9 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_8 - Status3) & Status3 >> 1) == 0 && ((Row_8 - Status3) & Status3 >> 2) == 0 && (Row_10 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_10 - Status1) & Status1 >> 1) == 0 && ((Row_9 - Status2) & Status2 >> 1) == 0 && ((Row_9 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_10 - Status1) & Status1 << 1) == 0 && ((Row_10 - Status1) & Status3 << 2) == 0 && (Row_8 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_8 - Status3) & Status3 << 1) == 0 && ((Row_9 - Status2) & Status2 >> 1) == 0 && ((Row_9 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_9-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_8 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
			
		Row_10 = Row_10 - Status11;
		Row_9 = Row_9 - Status22;
		Row_8 = Row_8 - Status33;
		
		Row_10 = Status1 + Row_10;
		Row_9 = Status2 + Row_9;
		Row_8 = Status3 + Row_8;
		Transmit2();
	}
	
	if (Row_counter == 8)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_9 - Status1)) == 0 && (Status2 << 1 & (Row_8 - Status2)) == 0 && (Status3 << 1 & (Row_7 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_9 - Status1)) == 0 && (Status2 >> 1 & (Row_8 - Status2)) == 0 && (Status3 >> 1 & (Row_7 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_8-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)		{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_7 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_8-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_9 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_7 & (Status2 & Status1)) == 0 && ((Row_9 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_9 - Status1)& (Status1>>1)) == 0 && ((Row_9 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}			
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_7 & (Status2 & Status1)) == 0 && ((Row_9 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_9 - Status1)& (Status1<<1)) == 0 && ((Row_9 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_7 - Status3) & Status3 << 1) == 0 && ((Row_7 - Status3) & Status3 << 2) == 0 && (Row_9 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_9 - Status1) & Status1 << 1) == 0 && ((Row_8 - Status2) & Status2 << 1) == 0 && ((Row_8 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_9 - Status1) & Status1 >> 1) == 0 && ((Row_9 - Status1) & Status1 >> 2) == 0 && (Row_7 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_7 - Status3) & Status3 >> 1) == 0 && ((Row_8 - Status2) & Status2 << 1) == 0 && ((Row_8 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_7 - Status3) & Status3 >> 1) == 0 && ((Row_7 - Status3) & Status3 >> 2) == 0 && (Row_9 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_9 - Status1) & Status1 >> 1) == 0 && ((Row_8 - Status2) & Status2 >> 1) == 0 && ((Row_8 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_9 - Status1) & Status1 << 1) == 0 && ((Row_9 - Status1) & Status3 << 2) == 0 && (Row_7 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_7 - Status3) & Status3 << 1) == 0 && ((Row_8 - Status2) & Status2 >> 1) == 0 && ((Row_8 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_8-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_7 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_9 = Row_9 - Status11;
		Row_8 = Row_8 - Status22;
		Row_7 = Row_7 - Status33;
		
		Row_9 = Status1 + Row_9;
		Row_8 = Status2 + Row_8;
		Row_7 = Status3 + Row_7;
		Transmit2();
	}
	
	if (Row_counter == 9)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_8 - Status1)) == 0 && (Status2 << 1 & (Row_7 - Status2)) == 0 && (Status3 << 1 & (Row_6 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_8 - Status1)) == 0 && (Status2 >> 1 & (Row_7 - Status2)) == 0 && (Status3 >> 1 & (Row_6 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_7-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)		{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_6 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_7-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_8 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_6 & (Status2 & Status1)) == 0 && ((Row_8 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_8 - Status1)& (Status1>>1)) == 0 && ((Row_8 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}			
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_6 & (Status2 & Status1)) == 0 && ((Row_8 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_8 - Status1)& (Status1<<1)) == 0 && ((Row_8 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_6 - Status3) & Status3 << 1) == 0 && ((Row_6 - Status3) & Status3 << 2) == 0 && (Row_8 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_8 - Status1) & Status1 << 1) == 0 && ((Row_7 - Status2) & Status2 << 1) == 0 && ((Row_7 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_8 - Status1) & Status1 >> 1) == 0 && ((Row_8 - Status1) & Status1 >> 2) == 0 && (Row_6 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_6 - Status3) & Status3 >> 1) == 0 && ((Row_7 - Status2) & Status2 << 1) == 0 && ((Row_7 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_6 - Status3) & Status3 >> 1) == 0 && ((Row_6 - Status3) & Status3 >> 2) == 0 && (Row_8 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_8 - Status1) & Status1 >> 1) == 0 && ((Row_7 - Status2) & Status2 >> 1) == 0 && ((Row_7 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_8 - Status1) & Status1 << 1) == 0 && ((Row_8 - Status1) & Status3 << 2) == 0 && (Row_6 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_6 - Status3) & Status3 << 1) == 0 && ((Row_7 - Status2) & Status2 >> 1) == 0 && ((Row_7 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_7-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_6 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_8 = Row_8 - Status11;
		Row_7 = Row_7 - Status22;
		Row_6 = Row_6 - Status33;
		
		Row_8 = Status1 + Row_8;
		Row_7 = Status2 + Row_7;
		Row_6 = Status3 + Row_6;
		Transmit2();
	}
	
	if (Row_counter == 10)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_7 - Status1)) == 0 && (Status2 << 1 & (Row_6 - Status2)) == 0 && (Status3 << 1 & (Row_5 - Status3)) == 0  && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1;}
		if (cc == 0x64 && (Status1 >> 1 & (Row_7 - Status1)) == 0 && (Status2 >> 1 & (Row_6 - Status2)) == 0 && (Status3 >> 1 & (Row_5 - Status3)) == 0  && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_6-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)		{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_5 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_6-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_7 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_5 & (Status2 & Status1)) == 0 && ((Row_7 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_7 - Status1)& (Status1>>1)) == 0 && ((Row_7 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}			
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_5 & (Status2 & Status1)) == 0 && ((Row_7 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_7 - Status1)& (Status1<<1)) == 0 && ((Row_7 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_5 - Status3) & Status3 << 1) == 0 && ((Row_5 - Status3) & Status3 << 2) == 0 && (Row_7 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_7 - Status1) & Status1 << 1) == 0 && ((Row_6 - Status2) & Status2 << 1) == 0 && ((Row_6 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_7 - Status1) & Status1 >> 1) == 0 && ((Row_7 - Status1) & Status1 >> 2) == 0 && (Row_5 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_5 - Status3) & Status3 >> 1) == 0 && ((Row_6 - Status2) & Status2 << 1) == 0 && ((Row_6 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_5 - Status3) & Status3 >> 1) == 0 && ((Row_5 - Status3) & Status3 >> 2) == 0 && (Row_7 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_7 - Status1) & Status1 >> 1) == 0 && ((Row_6 - Status2) & Status2 >> 1) == 0 && ((Row_6 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_7 - Status1) & Status1 << 1) == 0 && ((Row_7 - Status1) & Status3 << 2) == 0 && (Row_5 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_5 - Status3) & Status3 << 1) == 0 && ((Row_6 - Status2) & Status2 >> 1) == 0 && ((Row_6 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_6-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_5 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_7 = Row_7 - Status11;
		Row_6 = Row_6 - Status22;
		Row_5 = Row_5 - Status33;
		
		Row_7 = Status1 + Row_7;
		Row_6 = Status2 + Row_6;
		Row_5 = Status3 + Row_5;
		Transmit2();
	}
	
	if (Row_counter == 11)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_6 - Status1)) == 0 && (Status2 << 1 & (Row_5 - Status2)) == 0 && (Status3 << 1 & (Row_4 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_6 - Status1)) == 0 && (Status2 >> 1 & (Row_5 - Status2)) == 0 && (Status3 >> 1 & (Row_4 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_5-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)		{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_4 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_5-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_6 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}	
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_4 & (Status2 & Status1)) == 0 && ((Row_6 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_6 - Status1)& (Status1>>1)) == 0 && ((Row_6 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_4 & (Status2 & Status1)) == 0 && ((Row_6 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_6 - Status1)& (Status1<<1)) == 0 && ((Row_6 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_4 - Status3) & Status3 << 1) == 0 && ((Row_4 - Status3) & Status3 << 2) == 0 && (Row_6 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_6 - Status1) & Status1 << 1) == 0 && ((Row_5 - Status2) & Status2 << 1) == 0 && ((Row_5 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_6 - Status1) & Status1 >> 1) == 0 && ((Row_6 - Status1) & Status1 >> 2) == 0 && (Row_4 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_4 - Status3) & Status3 >> 1) == 0 && ((Row_5 - Status2) & Status2 << 1) == 0 && ((Row_5 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_4 - Status3) & Status3 >> 1) == 0 && ((Row_4 - Status3) & Status3 >> 2) == 0 && (Row_6 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_6 - Status1) & Status1 >> 1) == 0 && ((Row_5 - Status2) & Status2 >> 1) == 0 && ((Row_5 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_6 - Status1) & Status1 << 1) == 0 && ((Row_6 - Status1) & Status3 << 2) == 0 && (Row_4 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_4 - Status3) & Status3 << 1) == 0 && ((Row_5 - Status2) & Status2 >> 1) == 0 && ((Row_5 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_5-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_4 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_6 = Row_6 - Status11;
		Row_5 = Row_5 - Status22;
		Row_4 = Row_4 - Status33;
		
		Row_6 = Status1 + Row_6;
		Row_5 = Status2 + Row_5;
		Row_4 = Status3 + Row_4;
		Transmit2();
	}
	
	if (Row_counter == 12)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_5 - Status1)) == 0 && (Status2 << 1 & (Row_4 - Status2)) == 0 && (Status3 << 1 & (Row_3 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_5 - Status1)) == 0 && (Status2 >> 1 & (Row_4 - Status2)) == 0 && (Status3 >> 1 & (Row_3 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_4-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)		{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_3 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_4-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_5 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_3 & (Status2 & Status1)) == 0 && ((Row_5 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_5 - Status1)& (Status1>>1)) == 0 && ((Row_5 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}			
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_3 & (Status2 & Status1)) == 0 && ((Row_5 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_5 - Status1)& (Status1<<1)) == 0 && ((Row_5 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_3 - Status3) & Status3 << 1) == 0 && ((Row_3 - Status3) & Status3 << 2) == 0 && (Row_5 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_5 - Status1) & Status1 << 1) == 0 && ((Row_4 - Status2) & Status2 << 1) == 0 && ((Row_4 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_5 - Status1) & Status1 >> 1) == 0 && ((Row_5 - Status1) & Status1 >> 2) == 0 && (Row_3 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_3 - Status3) & Status3 >> 1) == 0 && ((Row_4 - Status2) & Status2 << 1) == 0 && ((Row_4 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_3 - Status3) & Status3 >> 1) == 0 && ((Row_3 - Status3) & Status3 >> 2) == 0 && (Row_5 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_5 - Status1) & Status1 >> 1) == 0 && ((Row_4 - Status2) & Status2 >> 1) == 0 && ((Row_4 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_5 - Status1) & Status1 << 1) == 0 && ((Row_5 - Status1) & Status3 << 2) == 0 && (Row_3 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_3 - Status3) & Status3 << 1) == 0 && ((Row_4 - Status2) & Status2 >> 1) == 0 && ((Row_4 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_4-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_3 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_5 = Row_5 - Status11;
		Row_4 = Row_4 - Status22;
		Row_3 = Row_3 - Status33;
		
		Row_5 = Status1 + Row_5;
		Row_4 = Status2 + Row_4;
		Row_3 = Status3 + Row_3;
		Transmit2();
	}
	
	if (Row_counter == 13)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_4 - Status1)) == 0 && (Status2 << 1 & (Row_3 - Status2)) == 0 && (Status3 << 1 & (Row_2 - Status3)) == 0 && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1;}
		if (cc == 0x64 && (Status1 >> 1 & (Row_4 - Status1)) == 0 && (Status2 >> 1 & (Row_3 - Status2)) == 0 && (Status3 >> 1 & (Row_2 - Status3)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_3-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)		{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_2 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_3-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_4 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}			
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_2 & (Status2 & Status1)) == 0 && ((Row_4 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_4 - Status1)& (Status1>>1)) == 0 && ((Row_4 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_2 & (Status2 & Status1)) == 0 && ((Row_4 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_4 - Status1)& (Status1<<1)) == 0 && ((Row_4 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_2 - Status3) & Status3 << 1) == 0 && ((Row_2 - Status3) & Status3 << 2) == 0 && (Row_4 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_4 - Status1) & Status1 << 1) == 0 && ((Row_3 - Status2) & Status2 << 1) == 0 && ((Row_3 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_4 - Status1) & Status1 >> 1) == 0 && ((Row_4 - Status1) & Status1 >> 2) == 0 && (Row_2 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_2 - Status3) & Status3 >> 1) == 0 && ((Row_3 - Status2) & Status2 << 1) == 0 && ((Row_3 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_2 - Status3) & Status3 >> 1) == 0 && ((Row_2 - Status3) & Status3 >> 2) == 0 && (Row_4 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_4 - Status1) & Status1 >> 1) == 0 && ((Row_3 - Status2) & Status2 >> 1) == 0 && ((Row_3 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_4 - Status1) & Status1 << 1) == 0 && ((Row_4 - Status1) & Status3 << 2) == 0 && (Row_2 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_2 - Status3) & Status3 << 1) == 0 && ((Row_3 - Status2) & Status2 >> 1) == 0 && ((Row_3 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_3-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_2 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_4 = Row_4 - Status11;
		Row_3 = Row_3 - Status22;
		Row_2 = Row_2 - Status33;
		
		Row_4 = Status1 + Row_4;
		Row_3 = Status2 + Row_3;
		Row_2 = Status3 + Row_2;
		Transmit2();
	}
	
	if (Row_counter == 14)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_3 - Status1)) == 0 && (Status2 << 1 & (Row_2 - Status2)) == 0 && (Status3 << 1 & (Row_1 - Status3)) == 0  && Status1 < 128 && Status2 < 128 && Status3 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; Status3 = Status3 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_3 - Status1)) == 0 && (Status2 >> 1 & (Row_2 - Status2)) == 0 && (Status3 >> 1 & (Row_1 - Status3)) == 0  && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1 && (Status3 & 0x01)  != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; Status3 = Status3 >> 1; }
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1 && (((Row_2-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0x03)		{Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 2 &&  ((Row_1 & Status1) == 0 )){Status1 = Status1; Status2 = (Status2 - (Status1*2)); Status3 = Status1; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3 && (((Row_2-Status2) & (Status2 + (Status1/2))) == 0 ) && Status2 != 0xC0){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4 && ((Row_3 & Status3) == 0 )){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}		
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape1 rotate
		if (cc == 0x77 && rotate_numberZ1 == 1 && (Row_1 & (Status2 & Status1)) == 0 && ((Row_3 - Status1) & ((Status1 << 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 << 2) & Status2); Status2 = Status2; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_numberZ1 == 2 && ((Row_3 - Status1)& (Status1>>1)) == 0 && ((Row_3 - Status1)& (Status1>>2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 >> 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ1 = 1;}
		if (cc == 0x77 && rotate_sucessZ1 == 1){++rotate_numberZ1; rotate_sucessZ1 = 0;}
		if (rotate_numberZ1 == 3){rotate_numberZ1 = 1;}	
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Z shape2 rotate
		if (cc == 0x77 && rotate_numberZ2 == 1 && (Row_1 & (Status2 & Status1)) == 0 && ((Row_3 - Status1) & ((Status1 >> 2) & Status2)) == 0){ Status3 = (Status2 & Status1); Status1 = ((Status1 >> 2) & Status2); Status2 = Status2; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_numberZ2 == 2 && ((Row_3 - Status1)& (Status1<<1)) == 0 && ((Row_3 - Status1)& (Status1<<2)) == 0 && Status2 != 0x03  && Status2 != 0xC0){Status1 = ((Status1 << 2) | Status3); Status2 = Status2; Status3 = 0x00; rotate_sucessZ2 = 1;}
		if (cc == 0x77 && rotate_sucessZ2 == 1){++rotate_numberZ2; rotate_sucessZ2 = 0;}
		if (rotate_numberZ2 == 3){rotate_numberZ2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape1 rotate
		if (cc == 0x77 && rotate_numberL1 == 1 && ((Row_1 - Status3) & Status3 << 1) == 0 && ((Row_1 - Status3) & Status3 << 2) == 0 && (Row_3 & Status3 <<1) == 0){Status1 = Status3 << 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 2 && Status2 != 0x01 && ((Row_3 - Status1) & Status1 << 1) == 0 && ((Row_2 - Status2) & Status2 << 1) == 0 && ((Row_2 - Status2) & Status2 >> 1) == 0){Status1 = Status1 << 1; Status2 = Status3 + (Status2 >> 1); Status3 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 3 && ((Row_3 - Status1) & Status1 >> 1) == 0 && ((Row_3 - Status1) & Status3 >> 2) == 0 && (Row_1 & Status1 >>1) == 0){Status3 = Status1 >> 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_numberL1 == 4 && Status2 != 0x80 && ((Row_1 - Status3) & Status3 >> 1) == 0 && ((Row_2 - Status2) & Status2 << 1) == 0 && ((Row_2 - Status2) & Status2 >> 1) == 0){Status3 = Status3 >> 1; Status2 = Status1 + (Status2 << 1); Status1 = 0;rotate_sucessL1 = 1;}
		if (cc == 0x77 && rotate_sucessL1 == 1){++rotate_numberL1; rotate_sucessL1 = 0;}
		if (rotate_numberL1 == 5){rotate_numberL1 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//L shape2 rotate
		if (cc == 0x77 && rotate_numberL2 == 1 && ((Row_1 - Status3) & Status3 >> 1) == 0 && ((Row_1 - Status3) & Status3 >> 2) == 0 && (Row_3 & Status3 >>1) == 0){Status1 = Status3 >> 1; Status3 = Status2 - Status3; Status2 = Status1; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 2 && Status2 != 0x80 && ((Row_3 - Status1) & Status1 >> 1) == 0 && ((Row_2 - Status2) & Status2 >> 1) == 0 && ((Row_2 - Status2) & Status2 << 1) == 0){Status1 = Status1 >> 1; Status2 = Status3 + (Status2 << 1); Status3 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 3 && ((Row_3 - Status1) & Status1 << 1) == 0 && ((Row_3 - Status1) & Status3 << 2) == 0 && (Row_1 & Status1 <<1) == 0){Status3 = Status1 << 1; Status1 = Status2 - Status1; Status2 = Status3; rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_numberL2 == 4 && Status2 != 0x01 && ((Row_1 - Status3) & Status3 << 1) == 0 && ((Row_2 - Status2) & Status2 >> 1) == 0 && ((Row_2 - Status2) & Status2 << 1) == 0){Status3 = Status3 << 1; Status2 = Status1 + (Status2 >> 1); Status1 = 0;rotate_sucessL2 = 1;}
		if (cc == 0x77 && rotate_sucessL2 == 1){++rotate_numberL2; rotate_sucessL2 = 0;}
		if (rotate_numberL2 == 5){rotate_numberL2 = 1;}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Bar shape rotate
		if (cc == 0x77 && rotate_numberBAR == 1 && (((Row_2-Status2) & (Status2 + (Status1/2) + (Status1*2))) == 0 ) && Status2 != 0x01 && Status2 != 0x80)	{Status1 = 0; Status2 = (Status2 + (Status2/2)+ (Status2*2)); Status3 = 0x00; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_numberBAR == 2 &&  ((Row_1 & (Status2 << 1 & Status2 >> 1)) == 0 )){Status1 = (Status2 << 1 & Status2 >> 1); Status2 = (Status2 - (Status1*2)-(Status1/2)); Status3 = Status1; rotate_sucessBAR = 1;}
		if (cc == 0x77 && rotate_sucessBAR == 1){++rotate_numberBAR; rotate_sucessBAR = 0;}
		if (rotate_numberBAR == 3){rotate_numberBAR = 1;}
		
		Row_3 = Row_3 - Status11;
		Row_2 = Row_2 - Status22;
		Row_1 = Row_1 - Status33;
		
		Row_3 = Status1 + Row_3;
		Row_2 = Status2 + Row_2;
		Row_1 = Status3 + Row_1;
		Transmit2();
	}
	
	if (Row_counter == 15 && Status3 == 0)
	{
		if (cc == 0x61 && (Status1 << 1 & (Row_2 - Status1)) == 0 && (Status2 << 1 & (Row_1 - Status2)) == 0 && Status1 < 128 && Status2 < 128){Status1 = Status1 << 1; Status2 = Status2 << 1; }
		if (cc == 0x64 && (Status1 >> 1 & (Row_2 - Status1)) == 0 && (Status2 >> 1 & (Row_1 - Status2)) == 0 && (Status1 & 0x01) != 1 && (Status2 & 0x01) != 1){Status1 = Status1 >> 1; Status2 = Status2 >> 1; }
	/*	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//T shape rotate
		if (cc == 0x77 && rotate_number == 1){Status1 = Status1; Status2 = (Status2 + (Status1/2)); Status3 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 3){Status2 =  (Status2 + (Status1*2)); Status3 = Status1; Status1 = 0x00; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_number == 4){Status1 = Status3; Status2 = (Status2 - (Status1/2)); Status3 = Status3; rotate_sucess = 1;}
		if (cc == 0x77 && rotate_sucess == 1){++rotate_number; rotate_sucess = 0;}
		if (rotate_number == 5){rotate_number = 1;}			*/
		Row_2 = Row_2 - Status11;
		Row_1 = Row_1 - Status22;
		
		Row_2 = Status1 + Row_2;
		Row_1 = Status2 + Row_1;
		Transmit2();
	}

}
}
void T_shape2(void)
{
	Status3 = Status2 ;
	Status2 = Status1;
	Status1 = 0x00;
	rotate_number = 4;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
}
void L_shape12(void)
{
	Status3 = Status2 ;
	Status2 = Status1;
	Status1 = 0x00;
	rotate_number = 0;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 1;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
}
void L_shape22(void)
{
	Status3 = Status2 ;
	Status2 = Status1;
	Status1 = 0x00;
	rotate_number = 0;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 1;
	rotate_numberBAR = 0;
}
void Bar_shape2(void)
{
	Status3 = Status2 ;
	Status2 = Status1;
	Status1 = 0x00;
	
	rotate_number = 0;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 2;
}
void T_shape(void)
{
	Status1 = 0x38;
	Status2 = 0x10;
	Status3 = 0x00;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
	rotate_number = 0;
}

void L_shape1(void)
{
	Status1 = 0x1C;
	Status2 = 0x04;
	Status3 = 0x00;
	
	rotate_number = 0;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
}

void L_shape2(void)
{
	Status1 = 0x1C;
	Status2 = 0x10;
	Status3 = 0x00;
	
	rotate_number = 0;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
}

void Box_shape(void)
{
	Status1 = 0x18;
	Status2 = 0x18;
	Status3 = 0x00;
	rotate_number = 0;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
}

void Bar_shape(void)
{
	Status1 = 0x1C;
	Status2 = 0x00;
	Status3 = 0x00;
	
	rotate_number = 0;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
}

void Z_shape1(void)
{
	Status1 = 0x0C;
	Status2 = 0x18;
	Status3 = 0x00;
	
	rotate_number = 0;
	rotate_numberZ1 = 1;
	rotate_numberZ2 = 0;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
}

void Z_shape2(void)
{
	Status1 = 0x30;
	Status2 = 0x18;
	Status3 = 0x00;
	
	rotate_number = 0;
	rotate_numberZ1 = 0;
	rotate_numberZ2 = 1;
	rotate_numberL1 = 0;
	rotate_numberL2 = 0;
	rotate_numberBAR = 0;
}


void altDelay(void)
{	
	sei();
	while(delayVar > 0)
	{
	if (delayVar <= 35){cli();}
	_delay_ms(1);
	--delayVar;
	}
}

void Transmit(void)
{
	SPI_MasterTransmit(Dig_1); SPI_MasterTransmit(Row_8);
	SPI_MasterTransmit(Dig_1); SPI_MasterTransmit(Row_16);
	latch();
	
	SPI_MasterTransmit(Dig_2); SPI_MasterTransmit(Row_7);
	SPI_MasterTransmit(Dig_2); SPI_MasterTransmit(Row_15);
	latch();
	
	SPI_MasterTransmit(Dig_3); SPI_MasterTransmit(Row_6);
	SPI_MasterTransmit(Dig_3); SPI_MasterTransmit(Row_14);
	latch();
	
	SPI_MasterTransmit(Dig_4); SPI_MasterTransmit(Row_5);
	SPI_MasterTransmit(Dig_4); SPI_MasterTransmit(Row_13);
	latch();
	
	SPI_MasterTransmit(Dig_5); SPI_MasterTransmit(Row_4);
	SPI_MasterTransmit(Dig_5); SPI_MasterTransmit(Row_12);
	latch();
	
	SPI_MasterTransmit(Dig_6); SPI_MasterTransmit(Row_3);
	SPI_MasterTransmit(Dig_6); SPI_MasterTransmit(Row_11);
	latch();
	
	SPI_MasterTransmit(Dig_7); SPI_MasterTransmit(Row_2);
	SPI_MasterTransmit(Dig_7); SPI_MasterTransmit(Row_10);
	latch();
	
	SPI_MasterTransmit(Dig_8); SPI_MasterTransmit(Row_1);
	SPI_MasterTransmit(Dig_8); SPI_MasterTransmit(Row_9);
	latch();
	
	if (Score_counter<= 3000){delayVar = 500;}
	if (Score_counter<= 10000 && Score_counter > 3000){delayVar = 350;}
	if (Score_counter<= 26000 && Score_counter > 10000){delayVar = 300;}
	if (Score_counter<= 46000 && Score_counter > 26000){delayVar = 250;}
	if (Score_counter<= 2147483647 && Score_counter > 46000){delayVar = 200;}

		altDelay();
}

void Transmit2(void)
{
	SPI_MasterTransmit(Dig_1); SPI_MasterTransmit(Row_8);
	SPI_MasterTransmit(Dig_1); SPI_MasterTransmit(Row_16);
	latch();
	
	SPI_MasterTransmit(Dig_2); SPI_MasterTransmit(Row_7);
	SPI_MasterTransmit(Dig_2); SPI_MasterTransmit(Row_15);
	latch();
	
	SPI_MasterTransmit(Dig_3); SPI_MasterTransmit(Row_6);
	SPI_MasterTransmit(Dig_3); SPI_MasterTransmit(Row_14);
	latch();
	
	SPI_MasterTransmit(Dig_4); SPI_MasterTransmit(Row_5);
	SPI_MasterTransmit(Dig_4); SPI_MasterTransmit(Row_13);
	latch();
	
	SPI_MasterTransmit(Dig_5); SPI_MasterTransmit(Row_4);
	SPI_MasterTransmit(Dig_5); SPI_MasterTransmit(Row_12);
	latch();
	
	SPI_MasterTransmit(Dig_6); SPI_MasterTransmit(Row_3);
	SPI_MasterTransmit(Dig_6); SPI_MasterTransmit(Row_11);
	latch();
	
	SPI_MasterTransmit(Dig_7); SPI_MasterTransmit(Row_2);
	SPI_MasterTransmit(Dig_7); SPI_MasterTransmit(Row_10);
	latch();
	
	SPI_MasterTransmit(Dig_8); SPI_MasterTransmit(Row_1);
	SPI_MasterTransmit(Dig_8); SPI_MasterTransmit(Row_9);
	latch();
	
}

void press_function(void)
{
	Transmit2();
	Row_16 = Row_15;
	Row_15 = Row_14;
	Row_14 = Row_13;
	Row_13 = Row_12;
	Row_12 = Row_11;
	Row_11 = Row_10;
	Row_10 = Row_9;
	Row_9 = Row_8;
	Row_8 = Row_7;
	Row_7 = Row_6;
	Row_6 = Row_5;
	Row_5 = Row_4;
	Row_4 = Row_3;
	Row_3 = Row_2;
	Row_2 = Row_1;
	_delay_ms(100);
}
void clear_all(void)
{
	Row_1 = 0x00; Row_2 = 0x00; Row_3 = 0x00; Row_4 = 0x00; Row_5 = 0x00; Row_6 = 0x00; Row_7 = 0x00; Row_8 = 0x00;
	Row_9 = 0x00; Row_10 = 0x00; Row_11 = 0x00; Row_12 = 0x00; Row_13 = 0x00; Row_14 = 0x00; Row_15 = 0x00; Row_16 = 0x00; Transmit2();
}
void press(void)
{
	int BSL = 0x01;
	int BSR = 0x80;
	int animation_loop = 0;
	clear_all();
while(cc != 0x20)
	{
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x00; if (cc != 0x20){press_function();}	
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x10 << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x10 << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x00; if (cc != 0x20){press_function();}
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x00; if (cc != 0x20){press_function();}
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x14 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x18 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x14 << 3; if (cc != 0x20){press_function();}	
	Row_1 = 0x00; if (cc != 0x20){press_function();}
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x08 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x00; if (cc != 0x20){press_function();}
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x10 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x04 << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x1C << 3; if (cc != 0x20){press_function();}
	Row_1 = 0x00; if (cc != 0x20){press_function();}	
	if (cc != 0x20){press_function();} if (cc != 0x20){press_function();} 
	if (cc != 0x20){press_function();} if (cc != 0x20){press_function();} 
	if (cc != 0x20){press_function();} if (cc != 0x20){press_function();} 
	if (cc != 0x20){press_function();} if (cc != 0x20){press_function();} 
	if (cc != 0x20){press_function();} if (cc != 0x20){press_function();}
	random_shape = random_num();}
	
	while(animation_loop < 3)
	{
	Row_1 = BSL; Row_2 = BSR;
	Row_3 = BSL; Row_4 = BSR;
	Row_5 = BSL; Row_6 = BSR;
	Row_7 = BSL; Row_8 = BSR;
	Row_9 = BSL; Row_10 = BSR;
	Row_11 = BSL; Row_12 = BSR;
	Row_13 = BSL; Row_14 = BSR;
	Row_15 = BSL; Row_16 = BSR; Transmit2(); _delay_ms(150);
	BSL = (BSL << 1) + 0x01;
	BSR = (BSR >> 1) + 0x80;
	++ animation_loop;
	} animation_loop = 0;
	
	while(animation_loop < 9)
	{
		Row_1 = BSL; Row_2 = BSR;
		Row_3 = BSL; Row_4 = BSR;
		Row_5 = BSL; Row_6 = BSR;
		Row_7 = BSL; Row_8 = BSR;
		Row_9 = BSL; Row_10 = BSR;
		Row_11 = BSL; Row_12 = BSR;
		Row_13 = BSL; Row_14 = BSR;
		Row_15 = BSL; Row_16 = BSR; Transmit2(); _delay_ms(150);
		BSL = (BSL << 1) ;
		BSR = (BSR >> 1) ;
		++ animation_loop;
	}
	_delay_ms(300);
	
}
void Clear_Row(void)
{

	if (Row_1 == 0xFF){++clear_counter;	clear_counter_Row1 = 1;}
	if (Row_2 == 0xFF){++clear_counter;	clear_counter_Row2 = 1;}
	if (Row_3 == 0xFF){++clear_counter;	clear_counter_Row3 = 1;}
	if (Row_4 == 0xFF){++clear_counter;	clear_counter_Row4 = 1;}
	if (Row_5 == 0xFF){++clear_counter;	clear_counter_Row5 = 1;}
	if (Row_6 == 0xFF){++clear_counter;	clear_counter_Row6 = 1;}
	if (Row_7 == 0xFF){++clear_counter;	clear_counter_Row7 = 1;}
	if (Row_8 == 0xFF){++clear_counter;	clear_counter_Row8 = 1;}
	if (Row_9 == 0xFF){++clear_counter;	clear_counter_Row9 = 1;}
	if (Row_10 == 0xFF){++clear_counter; clear_counter_Row10 = 1;}
	if (Row_11 == 0xFF){++clear_counter; clear_counter_Row11 = 1;}
	if (Row_12 == 0xFF){++clear_counter; clear_counter_Row12 = 1;}
	if (Row_13 == 0xFF){++clear_counter; clear_counter_Row13 = 1;}
	if (Row_14 == 0xFF){++clear_counter; clear_counter_Row14 = 1;}
	if (Row_15 == 0xFF){++clear_counter; clear_counter_Row15 = 1;}
	if (Row_16 == 0xFF){++clear_counter; clear_counter_Row16 = 1;}
		
while(bb<=4)
{		
	if(clear_counter_Row16 == 1){Row_16 = 0x00;}
	if(clear_counter_Row15 == 1){Row_15 = 0x00;}
	if(clear_counter_Row14 == 1){Row_14 = 0x00;}
	if(clear_counter_Row13 == 1){Row_13 = 0x00;}
	if(clear_counter_Row12 == 1){Row_12 = 0x00;}
	if(clear_counter_Row11 == 1){Row_11 = 0x00;}
	if(clear_counter_Row10 == 1){Row_10 = 0x00;}
	if(clear_counter_Row9 == 1){Row_9 = 0x00;}
	if(clear_counter_Row8 == 1){Row_8 = 0x00;}
	if(clear_counter_Row7 == 1){Row_7 = 0x00;}
	if(clear_counter_Row6 == 1){Row_6 = 0x00;}
	if(clear_counter_Row5 == 1){Row_5 = 0x00;}
	if(clear_counter_Row4 == 1){Row_4 = 0x00;}
	if(clear_counter_Row3 == 1){Row_3 = 0x00;}
	if(clear_counter_Row2 == 1){Row_2 = 0x00;}
	if(clear_counter_Row1 == 1){Row_1 = 0x00;}
	Transmit2(); _delay_ms(50);
	if(clear_counter_Row16 == 1){Row_16 = 0xFF;}
	if(clear_counter_Row15 == 1){Row_15 = 0xFF;}
	if(clear_counter_Row14 == 1){Row_14 = 0xFF;}
	if(clear_counter_Row13 == 1){Row_13 = 0xFF;}
	if(clear_counter_Row12 == 1){Row_12 = 0xFF;}
	if(clear_counter_Row11 == 1){Row_11 = 0xFF;}
	if(clear_counter_Row10 == 1){Row_10 = 0xFF;}
	if(clear_counter_Row9 == 1){Row_9 = 0xFF;}
	if(clear_counter_Row8 == 1){Row_8 = 0xFF;}
	if(clear_counter_Row7 == 1){Row_7 = 0xFF;}
	if(clear_counter_Row6 == 1){Row_6 = 0xFF;}
	if(clear_counter_Row5 == 1){Row_5 = 0xFF;}
	if(clear_counter_Row4 == 1){Row_4 = 0xFF;}
	if(clear_counter_Row3 == 1){Row_3 = 0xFF;}
	if(clear_counter_Row2 == 1){Row_2 = 0xFF;}
	if(clear_counter_Row1 == 1){Row_1 = 0xFF;}
	Transmit2(); _delay_ms(50);
	++bb;
}
	bb = 0;
	
	if(clear_counter_Row16 == 1)
	{
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row15 == 1)
	{
		Row_15 = Row_16;
		Row_16 = 0x00; 
	}
	
	if(clear_counter_Row14 == 1)
	{
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row13 == 1)
	{
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row12 == 1)
	{
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row11 == 1)
	{
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row10 == 1)
	{
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row9 == 1)
	{
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row8 == 1)
	{
		Row_8 = Row_9;
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row7 == 1)
	{
		Row_7 = Row_8;
		Row_8 = Row_9;
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row6 == 1)
	{
		Row_6 = Row_7;
		Row_7 = Row_8;
		Row_8 = Row_9;
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row5 == 1)
	{
		Row_5 = Row_6;
		Row_6 = Row_7;
		Row_7 = Row_8;
		Row_8 = Row_9;
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row4 == 1)
	{
		Row_4 = Row_5;
		Row_5 = Row_6;
		Row_6 = Row_7;
		Row_7 = Row_8;
		Row_8 = Row_9;
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row3 == 1)
	{
		Row_3 = Row_4;
		Row_4 = Row_5;
		Row_5 = Row_6;
		Row_6 = Row_7;
		Row_7 = Row_8;
		Row_8 = Row_9;
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row2 == 1)
	{
		Row_2 = Row_3;
		Row_3 = Row_4;
		Row_4 = Row_5;
		Row_5 = Row_6;
		Row_6 = Row_7;
		Row_7 = Row_8;
		Row_8 = Row_9;
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	
	if(clear_counter_Row1 == 1)
	{
		Row_1 = Row_2;
		Row_2 = Row_3;
		Row_3 = Row_4;
		Row_4 = Row_5;
		Row_5 = Row_6;
		Row_6 = Row_7;
		Row_7 = Row_8;
		Row_8 = Row_9;
		Row_9 = Row_10;
		Row_10 = Row_11;
		Row_11 = Row_12;
		Row_12 = Row_13;
		Row_13 = Row_14;
		Row_14 = Row_15;
		Row_15 = Row_16;
		Row_16 = 0x00;
	}
	 clear_counter_Row1 = 0;
	 clear_counter_Row2 = 0;
	 clear_counter_Row3 = 0;
	 clear_counter_Row4 = 0;
	 clear_counter_Row5 = 0;
	 clear_counter_Row6 = 0;
	 clear_counter_Row7 = 0;
	 clear_counter_Row8 = 0;
	 clear_counter_Row9 = 0;
	 clear_counter_Row10 = 0;
	 clear_counter_Row11 = 0;
	 clear_counter_Row12 = 0;
	 clear_counter_Row13 = 0;
	 clear_counter_Row14 = 0;
	 clear_counter_Row15 = 0;
	 clear_counter_Row16 = 0;
	 
	 if (Score_counter<= 3000)
	 {
		 if (clear_counter == 1){clear_counter = (clear_counter * 200); }
		 if (clear_counter == 2){clear_counter = (clear_counter * 300); }
		 if (clear_counter == 3){clear_counter = (clear_counter * 400); }
	 }
	 
	 if (Score_counter<= 10000 && Score_counter > 3000)
	 {
		 if (clear_counter == 1){clear_counter = (clear_counter * 500); }
		 if (clear_counter == 2){clear_counter = (clear_counter * 600); }
		 if (clear_counter == 3){clear_counter = (clear_counter * 700); }
	 }
	 
	 if (Score_counter<= 26000 && Score_counter > 10000)
		{
			if (clear_counter == 1){clear_counter = (clear_counter * 800); }
			if (clear_counter == 2){clear_counter = (clear_counter * 900); }
			if (clear_counter == 3){clear_counter = (clear_counter * 1000);}
		}
	 if (Score_counter<= 46000 && Score_counter > 26000)
		{
			if (clear_counter == 1){clear_counter = (clear_counter * 1100); }
			if (clear_counter == 2){clear_counter = (clear_counter * 1200); }
			if (clear_counter == 3){clear_counter = (clear_counter * 1300); }
		}
	 if (Score_counter<= 2147483647 && Score_counter > 46000)
		 {
			 if (clear_counter == 1){clear_counter = (clear_counter * 1400); }
			 if (clear_counter == 2){clear_counter = (clear_counter * 1500); }
			 if (clear_counter == 3){clear_counter = (clear_counter * 1600); }
		 }
	Score_counter = Score_counter + clear_counter;
	printf("\r%ld",Score_counter);
	clear_counter = 0;
}
void Pause(void)
{
	Row1_1 = Row_1;
	Row2_2 = Row_2;
	Row3_3 = Row_3;
	Row4_4 = Row_4;
	Row5_5 = Row_5;
	Row6_6 = Row_6;
	Row7_7 = Row_7;
	Row8_8 = Row_8;
	Row9_9 = Row_9;
	Row10_10 = Row_10;
	Row11_11 = Row_11;
	Row12_12 = Row_12;
	Row13_13 = Row_13;
	Row14_14 = Row_14;
	Row15_15 = Row_15;
	Row16_16 = Row_16;
	
		
		while(jj >= 0x7A)
		{
		sei();
		jj = 0x7B;	
		Row_1 = 0x00;
		Row_2 = 0x00;
		Row_3 = 0x00;
		Row_4 = 0x00;
		Row_5 = 0x00;
		Row_6 = 0x00;
		Row_7 = 0x00;
		Row_8 = 0x00;
		Row_9 = 0x00;
		Row_10 = 0x00;
		Row_11 = 0x00;
		Row_12 = 0x00;
		Row_13 = 0x00;
		Row_14 = 0x00;
		Row_15 = 0x00;
		Row_16 = 0x00;
		if (jj == 0x7A || jj == 0) {jj = 0; cli();} else Transmit2();_delay_ms(75);
		if (jj == 0x7A || jj == 0) {jj = 0; cli();} else Transmit2();_delay_ms(75);
		if (jj == 0x7A || jj == 0) {jj = 0; cli();} else Transmit2();_delay_ms(75);
		Row_1 = Row1_1;
		Row_2 = Row2_2;
		Row_3 = Row3_3;
		Row_4 = Row4_4;
		Row_5 = Row5_5;
		Row_6 = Row6_6;
		Row_7 = Row7_7;
		Row_8 = Row8_8;
		Row_9 = Row9_9;
		Row_10 = Row10_10;
		Row_11 = Row11_11;
		Row_12 = Row12_12;
		Row_13 = Row13_13;
		Row_14 = Row14_14;
		Row_15 = Row15_15;
		Row_16 = Row16_16;
		if (jj == 0x7A || jj == 0) {jj = 0; cli();} else Transmit2();_delay_ms(175);
		if (jj == 0x7A || jj == 0) {jj = 0; cli(); } else Transmit2();_delay_ms(175);
		if (jj == 0x7A || jj == 0) {jj = 0; cli();} else Transmit2();_delay_ms(150);
		}
		//sei();
}
//////////////////////////////////////////////
//Main program
int main(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;
	DDRB = 0b00010000;
	PORTB = 0b11101111;
	long long int zz = 0;
							
	Timer_initialize();
	USART_initialize0();
	SPI_MasterInit();
	LED_Matrix_init();
	Interrupt_initialize();
	stdout = &transmit;

	PB_0 = 0;
loop:
	press();
	clear_all();
	if(zz == 0){printf("Score\n"); ++zz;}
	printf("\r%ld             ",Score_counter);
	_delay_ms(300);
	cc = 0;
start:	
	while (1)
	{
	///////////////////////////////////////////////////////////////////////////
	//Random shapes section
	if (random_shape >= 0 && random_shape < 10 ) {T_shape();}
	if (random_shape >= 10 && random_shape < 20 ) {Z_shape1();}
	if (random_shape >= 20 && random_shape < 30 ) {Z_shape2();}
	if (random_shape >= 30 && random_shape < 40 ) {Box_shape();}
	if (random_shape >= 40 && random_shape < 50 ) {Bar_shape();}
	if (random_shape >= 50 && random_shape < 60 ) {L_shape1();}
	if (random_shape >= 60 && random_shape < 70 ) {L_shape2();}
	if (random_shape >= 70 && random_shape < 80 ) {Bar_shape();}	
	if (random_shape >= 80 && random_shape < 90 ) {Bar_shape();}
	if (random_shape >= 90 && random_shape < 100 ) {Z_shape1();}
	if (random_shape >= 100 && random_shape < 110 ) {Box_shape();}
	if (random_shape >= 110 && random_shape < 120 ) {L_shape1();}
	if (random_shape >= 120 && random_shape < 130 ) {T_shape();}
	if (random_shape >= 130 && random_shape < 140 ) {L_shape2();}
	if (random_shape >= 140 && random_shape < 150 ) {Bar_shape();}	
	if (random_shape >= 150 && random_shape < 160 ) {L_shape2();}
	if (random_shape >= 160 && random_shape < 170 ) {Bar_shape();}
	if (random_shape >= 170 && random_shape < 180 ) {T_shape();}
	if (random_shape >= 180 && random_shape < 190 ) {Box_shape();}
	if (random_shape >= 190 && random_shape < 200 ) {L_shape1();}
	if (random_shape >= 200 && random_shape < 210 ) {Z_shape1();}
	if (random_shape >= 210 && random_shape < 220 ) {Bar_shape();}
	if (random_shape >= 220 && random_shape < 230 ) {Z_shape2();}
	if (random_shape >= 230 && random_shape < 240 ) {Bar_shape();}
	if (random_shape >= 240 && random_shape < 250 ) {Box_shape();}
	if (random_shape >= 250 && random_shape <= 255 ) {T_shape();}
//////////////////////////////////////////////////////////////////////////////////////
//Check to see if there is a game over
if((Status1 & Row_16) != 0 || (Status2 & Row_15) != 0)
{	
	cli();
	Row_16 = Status1 | Row_16;
	Row_15 = Status2 | Row_15;
	Transmit2();
	_delay_ms(1000);
	
	Row_16 = 0xFF; Transmit2(); _delay_ms(200);
	Row_16 = 0x00; Row_15 = 0xFF; Transmit2(); _delay_ms(200);
	Row_15 = 0x00; Row_14 = 0xFF; Transmit2(); _delay_ms(200);
	Row_14 = 0x00; Row_13 = 0xFF; Transmit2(); _delay_ms(200);
	Row_13 = 0x00; Row_12 = 0xFF; Transmit2(); _delay_ms(200);
	Row_12 = 0x00; Row_11 = 0xFF; Transmit2(); _delay_ms(200);
	Row_11 = 0x00; Row_10 = 0xFF; Transmit2(); _delay_ms(200);
	Row_10 = 0x00; Row_9 = 0xFF; Transmit2(); _delay_ms(200);
	Row_9 = 0x00; Row_8 = 0xFF; Transmit2(); _delay_ms(200);
	Row_8 = 0x00; Row_7 = 0xFF; Transmit2(); _delay_ms(200);
	Row_7 = 0x00; Row_6 = 0xFF; Transmit2(); _delay_ms(200);
	Row_6 = 0x00; Row_5 = 0xFF; Transmit2(); _delay_ms(200);
	Row_5 = 0x00; Row_4 = 0xFF; Transmit2(); _delay_ms(200);
	Row_4 = 0x00; Row_3 = 0xFF; Transmit2(); _delay_ms(200);
	Row_3 = 0x00; Row_2 = 0xFF; Transmit2(); _delay_ms(200);
	Row_2 = 0x00; Row_1 = 0xFF; Transmit2(); _delay_ms(200);
	Row_1 = 0x00; Transmit2(); _delay_ms(200);
	sei();
	clear_counter = 0;
	Score_counter = 0;
	goto loop;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Top	
	Row_16 = Status1 + Row_16;	
	Row_15 = Status2 + Row_15;	
	Row_14 = Status3 + Row_14;		
	Transmit();
	cli();
	++Row_counter;
	
				while(ii <= 7)
				{
				if (Status3 == 0)
					comparison1 = Status1 & compare;
					comparison2 = (Row_15-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
				if (Status3 == 0)
				{
					while(ii <= 7)
					{
						comparison1 = Status2 & compare;
						comparison2 = Row_14 & compare;
						
						if ((comparison1 & comparison2) != 0) {occupy = 1;}
						++ii;
						compare = compare >> 1;
						}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					}
					else
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = (Row_14 - Status3) & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
							while(ii <= 7)
							{
								comparison1 = Status3 & compare;
								comparison2 = Row_13 & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ONE	
////////////////////////////////////////////////////////////
//alternate spin for t shape
if ((Status1 == 0xE0 && Status2 == 0x40 && Status3 == 0x00) ||
	(Status1 == 0x70 && Status2 == 0x20 && Status3 == 0x00) ||
	(Status1 == 0x38 && Status2 == 0x10 && Status3 == 0x00) ||
	(Status1 == 0x1C && Status2 == 0x08 && Status3 == 0x00) ||
	(Status1 == 0x0E && Status2 == 0x04 && Status3 == 0x00) ||
	(Status1 == 0x07 && Status2 == 0x02 && Status3 == 0x00) ||
	(Status1 == 0xE0 && Status2 == 0x20 && Status3 == 0x00) ||
	(Status1 == 0x70 && Status2 == 0x10 && Status3 == 0x00) ||
	(Status1 == 0x38 && Status2 == 0x08 && Status3 == 0x00) ||
	(Status1 == 0x1C && Status2 == 0x04 && Status3 == 0x00) ||
	(Status1 == 0x0E && Status2 == 0x02 && Status3 == 0x00) ||
	(Status1 == 0x07 && Status2 == 0x01 && Status3 == 0x00) ||
	(Status1 == 0xE0 && Status2 == 0x80 && Status3 == 0x00) ||
	(Status1 == 0x70 && Status2 == 0x40 && Status3 == 0x00) ||
	(Status1 == 0x38 && Status2 == 0x20 && Status3 == 0x00) ||
	(Status1 == 0x1C && Status2 == 0x10 && Status3 == 0x00) ||
	(Status1 == 0x0E && Status2 == 0x08 && Status3 == 0x00) ||
	(Status1 == 0x07 && Status2 == 0x04 && Status3 == 0x00) ||
	(Status1 == 0xE0 && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x70 && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x38 && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x1C && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x0E && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x07 && Status2 == 0x00 && Status3 == 0x00))
{
	Row_counter = 1;
	Row_16 = Row_16 - Status1;
	Row_15 = Row_15 - Status2;
	Row_14 = Row_14 - Status3;
	
if ((Status1 == 0xE0 && Status2 == 0x40 && Status3 == 0x00) ||
	(Status1 == 0x70 && Status2 == 0x20 && Status3 == 0x00) ||
	(Status1 == 0x38 && Status2 == 0x10 && Status3 == 0x00) ||
	(Status1 == 0x1C && Status2 == 0x08 && Status3 == 0x00) ||
	(Status1 == 0x0E && Status2 == 0x04 && Status3 == 0x00) ||
	(Status1 == 0x07 && Status2 == 0x02 && Status3 == 0x00) ){T_shape2();}
	
if ((Status1 == 0xE0 && Status2 == 0x20 && Status3 == 0x00) ||
	(Status1 == 0x70 && Status2 == 0x10 && Status3 == 0x00) ||
	(Status1 == 0x38 && Status2 == 0x08 && Status3 == 0x00) ||
	(Status1 == 0x1C && Status2 == 0x04 && Status3 == 0x00) ||
	(Status1 == 0x0E && Status2 == 0x02 && Status3 == 0x00) ||
	(Status1 == 0x07 && Status2 == 0x01 && Status3 == 0x00) ){L_shape12();}	
		
if ((Status1 == 0xE0 && Status2 == 0x80 && Status3 == 0x00) ||
	(Status1 == 0x70 && Status2 == 0x40 && Status3 == 0x00) ||
	(Status1 == 0x38 && Status2 == 0x20 && Status3 == 0x00) ||
	(Status1 == 0x1C && Status2 == 0x10 && Status3 == 0x00) ||
	(Status1 == 0x0E && Status2 == 0x08 && Status3 == 0x00) ||
	(Status1 == 0x07 && Status2 == 0x04 && Status3 == 0x00) ){L_shape22();}
if ((Status1 == 0xE0 && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x70 && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x38 && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x1C && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x0E && Status2 == 0x00 && Status3 == 0x00) ||
	(Status1 == 0x07 && Status2 == 0x00 && Status3 == 0x00) ){Bar_shape2();}
	
	Row_16 = Status1 + Row_16;
	Row_15 = Status2 + Row_15;
	Row_14 = Status3 + Row_14;
	sei();
	Transmit(); Pause();
	cli();
	++Row_counter;
	while(ii <= 7)
	{
		if (Status3 == 0)
		comparison1 = Status1 & compare;
		comparison2 = (Row_15-Status2) & compare;
		if ((comparison1 & comparison2) != 0) {occupy = 1;}
		++ii;
		compare = compare >> 1;
		}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
		if (Status3 == 0)
		{
			while(ii <= 7)
			{
				comparison1 = Status2 & compare;
				comparison2 = Row_14 & compare;
				
				if ((comparison1 & comparison2) != 0) {occupy = 1;}
				++ii;
				compare = compare >> 1;
				}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
			}
			else
			{
				while(ii <= 7)
				{
					comparison1 = Status2 & compare;
					comparison2 = (Row_14 - Status3) & compare;
					
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					
					while(ii <= 7)
					{
						comparison1 = Status3 & compare;
						comparison2 = Row_13 & compare;
						
						if ((comparison1 & comparison2) != 0) {occupy = 1;}
						++ii;
						compare = compare >> 1;
						}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					}
				}
//////////////////////////////////////////////////////////////
/////
	Row_16 = Row_16 - Status1;
	Row_15 = Row_15 - Status2;
	Row_14 = Row_14 - Status3;
	
	Row_15 = Status1 + Row_15;
	Row_14 = Status2 + Row_14;
	Row_13 = Status3 + Row_13;
	sei();
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_14-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
				if (Status3 == 0)
				{
					while(ii <= 7)
					{
						comparison1 = Status2 & compare;
						comparison2 = Row_13 & compare;
						
						if ((comparison1 & comparison2) != 0) {occupy = 1;}
						++ii;
						compare = compare >> 1;
						}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					}
					else
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = (Row_13 - Status3) & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
							
							while(ii <= 7)
							{
								comparison1 = Status3 & compare;
								comparison2 = Row_12 & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
							}
				
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TWO
	Row_15 = Row_15 - Status1;
	Row_14 = Row_14 - Status2;
	Row_13 = Row_13 - Status3;
	
	Row_14 = Row_14 + Status1;
	Row_13 = Row_13 + Status2;
	Row_12 = Row_12 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_13-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_12 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_12 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_11 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//THREE	
	Row_14 = Row_14 - Status1;
	Row_13 = Row_13 - Status2;
	Row_12 = Row_12 - Status3;
	
	Row_13 = Row_13 + Status1;
	Row_12 = Row_12 + Status2;
	Row_11 = Row_11 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_12-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_11 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_11 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_10 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FOUR	
	Row_13 = Row_13 - Status1;
	Row_12 = Row_12 - Status2;
	Row_11 = Row_11 - Status3;
	
	Row_12 = Row_12 + Status1;
	Row_11 = Row_11 + Status2;
	Row_10 = Row_10 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_11-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_10 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_10 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_9 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FIVE	
	Row_12 = Row_12 - Status1;
	Row_11 = Row_11 - Status2;
	Row_10 = Row_10 - Status3;
	
	Row_11 = Row_11 + Status1;
	Row_10 = Row_10 + Status2;
	Row_9 = Row_9 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_10-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row();goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_9 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_9 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_8 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SIX	
	Row_11 = Row_11 - Status1;
	Row_10 = Row_10 - Status2;
	Row_9 = Row_9 - Status3;
	
	Row_10 = Row_10 + Status1;
	Row_9 = Row_9 + Status2;
	Row_8 = Row_8 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_9-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_8 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_8 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_7 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SEVEN	
	Row_10 = Row_10 - Status1;
	Row_9 = Row_9 - Status2;
	Row_8 = Row_8 - Status3;
	
	Row_9 = Row_9 + Status1;
	Row_8 = Row_8 + Status2;
	Row_7 = Row_7 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_8-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_7 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_7 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_6 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EIGHT	
	Row_9 = Row_9 - Status1;
	Row_8 = Row_8 - Status2;
	Row_7 = Row_7 - Status3;
	
	Row_8 = Row_8 + Status1;
	Row_7 = Row_7 + Status2;
	Row_6 = Row_6 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_7-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_6 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_6 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_5 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//NINE	
	Row_8 = Row_8 - Status1;
	Row_7 = Row_7 - Status2;
	Row_6 = Row_6 - Status3;
	
	Row_7 = Row_7 + Status1;
	Row_6 = Row_6 + Status2;
	Row_5 = Row_5 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_6-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_5 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_5 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_4 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TEN	
	Row_7 = Row_7 - Status1;
	Row_6 = Row_6 - Status2;
	Row_5 = Row_5 - Status3;
	
	Row_6 = Row_6 + Status1;
	Row_5 = Row_5 + Status2;
	Row_4 = Row_4 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_5-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_4 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_4 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_3 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ELEVEN
	Row_6 = Row_6 - Status1;
	Row_5 = Row_5 - Status2;
	Row_4 = Row_4 - Status3;
	
	Row_5 = Row_5 + Status1;
	Row_4 = Row_4 + Status2;
	Row_3 = Row_3 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_4-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					if (Status3 == 0)
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = Row_3 & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
						}
						else
						{
							while(ii <= 7)
							{
								comparison1 = Status2 & compare;
								comparison2 = (Row_3 - Status3) & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								
								while(ii <= 7)
								{
									comparison1 = Status3 & compare;
									comparison2 = Row_2 & compare;
									
									if ((comparison1 & comparison2) != 0) {occupy = 1;}
									++ii;
									compare = compare >> 1;
									}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
								}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TWELVE
	Row_5 = Row_5 - Status1;
	Row_4 = Row_4 - Status2;
	Row_3 = Row_3 - Status3;
	
	Row_4 = Row_4 + Status1;
	Row_3 = Row_3 + Status2;
	Row_2 = Row_2 + Status3;
	Transmit(); Pause();
	++Row_counter;
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_3-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
				if (Status3 == 0)
				{
					while(ii <= 7)
					{
						comparison1 = Status2 & compare;
						comparison2 = Row_2 & compare;
						
						if ((comparison1 & comparison2) != 0) {occupy = 1;}
						++ii;
						compare = compare >> 1;
						}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					}
					else
					{
						while(ii <= 7)
						{
							comparison1 = Status2 & compare;
							comparison2 = (Row_2 - Status3) & compare;
							
							if ((comparison1 & comparison2) != 0) {occupy = 1;}
							++ii;
							compare = compare >> 1;
							}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
							
							while(ii <= 7)
							{
								comparison1 = Status3 & compare;
								comparison2 = Row_1 & compare;
								
								if ((comparison1 & comparison2) != 0) {occupy = 1;}
								++ii;
								compare = compare >> 1;
								}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
							}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//THIRTEEN
	Row_4 = Row_4 - Status1;
	Row_3 = Row_3 - Status2;
	Row_2 = Row_2 - Status3;

	
	Row_3 = Row_3 + Status1;
	Row_2 = Row_2 + Status2;
	Row_1 = Row_1 + Status3;
	Transmit(); Pause();
	++Row_counter;
	
				while(ii <= 7)
				{
					comparison1 = Status1 & compare;
					comparison2 = (Row_2-Status2) & compare;
					if ((comparison1 & comparison2) != 0) {occupy = 1;}
					++ii;
					compare = compare >> 1;
					}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
				if (Status3 == 0)
				{
					while(ii <= 7)
					{
						comparison1 = Status2 & compare;
						comparison2 = Row_1 & compare;
						
						if ((comparison1 & comparison2) != 0) {occupy = 1;}
						++ii;
						compare = compare >> 1;
						}ii = 0; compare = 0x80; if (occupy == 1){occupy = 0; Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;}
					}
					else
					{
						Row_counter = 1; random_shape = random_num(); Score_counter = Score_counter + (255 - TCNT0); Clear_Row(); goto start;
							}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FOURTEEN	
	Row_3 = Row_3 - Status1;
	Row_2 = Row_2 - Status2;
	Row_1 = Row_1 - Status3;
	
	Row_2 = Row_2 + Status1;
	Row_1 = Row_1 + Status2;
	Transmit(); Pause();
	Row_counter = 1;
	random_shape = random_num();
	Score_counter = Score_counter + (255 - TCNT0); Clear_Row();
	}
					}
				