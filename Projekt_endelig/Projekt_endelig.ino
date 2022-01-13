

#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <RH_ASK.h>
#include <SPI.h>
#include "Timer3_driver.h"
#include "driveControl.h"
#include "motor.h"
//#include "led.h"
#include "lyd_uart.h"
#include "lys_styring.h"

#define BUTTON1 3
#define BUTTON2 4
#define BUTTON3 5
#define BUTTON4 6

#define ROCKET_SWITCH 22					//Rocket switch PIN

#define TIMER_N 53036						//Timer trappe værdi. 

//*******************************************************************************//
RH_ASK rfDriver;							//Reciever driver objekt
volatile unsigned char reflexCounter = 0;	//Global variable for placement of car
volatile int hold = -1;
volatile bool state = true;					//Bool state used to control the variable in interrupt routines
/****************************************************************/
// LOCAL FUNCTIONS
void initPortForInt();						//Initialize interrupts
/****************************************************************/



//interrupt rutine for the first reflex
//The routine starts the timer and adds 1 to reflexCounter
void INT0Handler()
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
void INT1Handler()
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


// Interrupt/timer routines for light control
ISR(TIMER1_OVF_vect)
{
	PORTB = PINB & ~0b01000000;
	TCCR1B = 0b00000000; //Stop timer 1 (no clock)
	TIFR1 = 0b00000001;  //Reset Timer 1 Overflow flag
	driveRear(); //call normal lights
	Serial.print("Hej");
}

ISR(TIMER0_COMPA_vect)
{
	PORTB = PINB ^ 0b01000000;  //turn lights on on compare
}


//Setup of all ports and drivers
void setup()
{
	Serial.begin(9600);

	//init ports for interrupts
	//initPortForInt();
	attachInterrupt(digitalPinToInterrupt(21), INT0Handler, RISING);
	attachInterrupt(digitalPinToInterrupt(20), INT1Handler, RISING);
	//init timer for reflex
	initTimer();
	
	//Init motor control
	initMotorPWMandToggle();
	
	//Init light control
	initLights();
	
	//init reciever
	rfDriver.init();
	//Init sound control
	InitUART(9600, 8, 0);
	volumeMax();
	
	//Init global interrupt
	sei();			
	//make sure it starts at 0
	reflexCounter = 0;
	
}


void loop()
{
	//KØR BANEN
	/*while (0)
	{
		if (hold != reflexCounter)
		{
			driveControl(reflexCounter);
			hold++;
			Serial.print(reflexCounter);
			Serial.print(hold);
		}
	}*/
	/*
	
	/*************************************/
	// TEST TIL REMOTE CONTROL
	while (1)
	{
		// Set buffer to size of expected message
		uint8_t buf[9];
		uint8_t buflen = sizeof(buf);
		if (rfDriver.recv(buf, &buflen))
		{
			const char speed[3] = { buf[0],buf[1],buf[2] };
			int speedValue = atoi(speed);
			int speedForward = speedValue - 200;
			int speedBackward = 200 - speedValue;

			if (speedValue > 210)
			{
				forward(speedForward, 0, 0);
			}
			else if (speedValue < 203 && 195 < speedValue)
			{
				stop();
			}
			else if (speedValue < 190)
			{
				backward(speedBackward, 0, 0);
			}
			Serial.print("\nForward speed: ");
			Serial.print(speedForward);
			Serial.print("\nBackward speed:");
			Serial.print(speedBackward);

			if (buf[BUTTON1] - '0' == 1)
			{
				soundStart();
			}
			if (buf[BUTTON2] - '0' == 1)
			{
				soundReflex();
			}
			if (buf[BUTTON3] - '0' == 1)
			{
				soundEnd();
			}
			if (buf[BUTTON4] - '0' == 1)
			{
				toggleFront();
			}
		}
	}
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
	//Enable INT1, INT0 interrupt
	
	//EIMSK |= 0b00000011;
	
	//Enable rising edge interrupt request for INT 1 and INT 0						
	
	//EICRA |= 0b00001111;
	
	//Init Timer interrupts og prescaler
}