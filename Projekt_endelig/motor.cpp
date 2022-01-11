/*
 * Motorstyring.c
 *
 * Created: 08-12-2021 16:41:09
 *  Author: Mathi
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motor.h"

void initMotorPWMandToggle() {
	/*	void initMotor()
	Parametre: Ingen
	Returværdi: Ingen
	Beskrivelse: Klargøre ben på til udgang og pwm mode(PWM PortL ben 5)(Toggle PortL ben 6)
	*/
	DDRL = 0xFF;
	PORTL &= 0b00000000;
	TCCR5A = 0b00001011;
	TCCR5B = 0b00000011;
	OCR5C = 0;

}

void forward(char speed, char delayActivation, char duaration) {
	/*	void forward()
		Parametre: Speed bestemmer start hastighed
		Returværdi: Ingen
		Beskrivelse: Sætter bilensmotor retning til fremad og sætter en start hastighed

	*/

	if (delayActivation > 0) {
		delay(duaration);
	}

	PORTL &= 0b00100000;
	OCR5C = (speed * 10);
}

void backward(char speed, char delayActivation, char duaration) {
	/*  void backward ()
		Parametre: Speed bestemmer start hastighed
		Returværdi: Ingen
		Beskrivelse: Sætter bilensmotor retning til bagud og sætter en start hastighed som kommer fra (speed)
	*/
	if (delayActivation > 0) {
		delay(duaration);
	}

	PORTL |= 0b00110000;
	OCR5C = (speed * 10);
}


void stop() {
	/*  void stop()
		Parametre: Ingen
		Returværdi: Ingen
		Beskrivelse: Slukker PWM signal og slukker accelerations timeren
	*/
	OCR5C = 0;
}

void delay(char duaration) {
	TCCR4A = 0b00000000;
	TCCR4B = 0b00000101;
	TCNT4 = duaration * (15625 / 2);

	while ((TIFR4 & (1 << 0)) == 0)
	{
	}

	TCCR4B = 0b00000000;
	TIFR4 = 1 << 0;
}
