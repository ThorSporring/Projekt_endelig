#include <avr/io.h>
#include <avr/interrupt.h>

void initTimer()
{
	TCCR3A = 0b00000000;					//init timer3 til normal mode
	TCCR3B = 0b00000000;
}
void startTimerInt(unsigned int N)
{
	TCNT3 = N;		//trin
	TCCR3B |= 0b00000100;	//prescaler
	TIMSK3 |= 0b00000001;	//set interrupt
}

void stopTimerInt()
{
	TCCR3B &= 0b11111000;	//prescaler 0 (no clock)
	TIMSK3 &= 0b11111110;	//Deaktiver interrupt
	TIFR3 |= 0b00000001;	//Fjern overflow flag
}