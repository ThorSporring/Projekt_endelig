

#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <RH_ASK.h>
#include <SPI.h>
#include "Timer3_driver.h"
#include "driveControl.h"
#include "motor.h"
#include "led.h"


#define ROCKET_SWITCH 22					//Rocket switch PIN

#define TIMER_N 53036						//Timer trappe værdi. 

//*******************************************************************************//
/****************************************************************/
RH_ASK rfDriver;							//Reciever driver objekt
volatile unsigned char reflexCounter = 0;	//Global variable for placement of car
volatile bool state = true;					//Bool state used to control the variable in interrupt routines
/****************************************************************/
void initportforint();
/****************************************************************/


//interrupt rutine for the first reflex
//The routine starts the timer and adds 1 to reflexCounter

ISR(INT1_vect)
{
	if (state)
	{
		state = false;
		startTimerInt(TIMER_N);
		reflexCounter++;
	}
}

//interrupt rutine for the second reflex
//The routine starts the timer and adds 1 to reflexCounter
ISR(INT3_vect)
{
	if (state)
	{
		state = false;
		startTimerInt(TIMER_N);
		reflexCounter++;
	}
}

//Timer overflow routine, to ensure two inputs can't enter at the same time
//Stops timer at sets state to true
ISR(TIMER3_OVF_vect)
{
	stopTimerInt();
	state = true;
}


//Setup of all ports and drivers
void setup()
{
	//init reciever
	rfDriver.init();
	//Init portB for leds on shield
	initLEDport();
	//init ports for interrupts
	initPortForInt();
	//init timer for reflex
	initTimer();
	//Init motor control
	initMotorPWMandToggle();
	//Init light control
	
	//Init sound control
	
	//Init global interrupt
	sei();		
	Serial.begin(9600);
	
	//Led sequence that assures car is ready to go
	initOkay();
	//make sure it starts at 0
	reflexCounter = 0;
}


void loop()
{
	while (1)
	{
		driveControl(reflexCounter);

	}
	/*
	while (1)
	{
		
		uint8_t buf[9];
		uint8_t buflen = sizeof(buf);
	
		// Check if received packet is correct size
		if (rfDriver.recv(buf, &buflen))
		{


				// Message received with valid checksum
				Serial.print("Message Received: ");
				Serial.println((char*)buf);

			unsigned char speed[3] = {buf[0],buf[1],buf[2]};
			unsigned char buttonPressed[3] = { (buf[3] - '0'),(buf[4] - '0'), (buf[5] - '0') };
			int sumOfSpeed = atoi(speed);
			if (sumOfSpeed > 200)
			{
				forward((sumOfSpeed-100)/2, 0, 0);
				Serial.print("forward: ");
				Serial.print(sumOfSpeed);
				Serial.print("\n");
			}
			if (sumOfSpeed < 200)
			{
				backward((sumOfSpeed-100)/2, 0, 0);
				Serial.print("backward: ");
				Serial.print(sumOfSpeed);
				Serial.print("\n");
			}
			for (int i = 0; i <= 2; i++)
			{
				Serial.print("Button nr. ");
				Serial.print(i);
				Serial.print("\n");
				Serial.print(buttonPressed[i]);
				Serial.print("\n");
			}

			// Message received with valid checksum
			Serial.print("Message Received: ");
			for (int i = 0; i <= 8; i++)
			{
				Serial.print(buf[i] - '0');
				Serial.print(" ");
			}
		}*/

}




void initPortForInt()
{
	//init PORT D pin til input
	DDRD = 0;

	//Pin 46 (PD3) benyttes til INT 3
	//Pin 45 (PD2) benyttes til INT 2

	DDRE = 0;


	//init PORT A pins til input
	DDRA = 0;
	//Pin 22 (PA0) benyttes til Rocket_switch. Bestemmelse af driveControl eller remoteControl
	//initialise interrupt
	//Enable INT2, INT3 interrupt
	EIMSK |= 0b00001100;
	//Enable rising edge interrupt request for INT 2 and INT 3						
	EICRA |= 0b11110000;
	//Init Timer interrupts og prescaler
}