/*
 * CFile1.c
 *
 * Created: 06-12-2021 11:06:08
 *  Author: Boergeiam
 */
#include "lys_styring.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void initLights()
{
	DDRB = 0xFF;	//Initialize portB as output
	PORTB = 0;		//LEDs off
	interruptEnable();
}

void interruptEnable()
{
	sei();
	TIMSK1 = 0b00000001;	//enable timer 1 overflow
	TCNT1 = 65536 - 34286;	//timer for BrakeLightDelay
	TCCR1A = 0b00000000;	//timer1 Normal mode 1

	TIMSK0 = 0b00000010; //enable interrupt compare match A
	//TCCR0B=0b00000100; //256 prescaler
	OCR0A = 204; //80% dutycycle rear lights

}

void toggleFront()
{					//bit 6 used for front lights
	if (PINB == PINB & ~0b1000000) //if Front are off
	{
		PORTB = PINB ^ 0b10000000; //then turn them on
	}
	else
	{
		PORTB = PINB & ~0b10000000; //else turn them off
	}
}

void onFront()
{
	PORTB = 0b10000000;
}

void brakeRearOn()
{
	TCCR0A = 0b00000000;//disable PWM timer, and Enable single high out bit7
	PORTB = PINB ^ 0b01000000; //set bit 7 to 1, to turn on lights

}
void brakeRearOff()
{
	TCCR1B = 0b00000100;	//enable timer with 256 prescaler and wait for overflow
}


void driveRear()
{
	TCCR0A = 0b10000001; //Start of PWM 
	TCCR0B = 0b00000100; //256 prescaler
}

void rearOff()
{
	TCCR0A = 0b00000000; //turn PWM off
	TCCR0B = 0b00000000; //turn timer off
	PORTB = PINB & ~0b01000000; // turn Rear off
}
