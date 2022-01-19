

#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "REMOTE_CONTROL.h"
#include "Timer3_driver.h"
#include "driveControl.h"
#include "motor.h"
//#include "led.h"
#include "lyd_uart.h"
#include "lys_styring.h"

#define BUTTON1 0
#define BUTTON2 1
#define BUTTON3 2
#define BUTTON4 3

#define ROCKET_SWITCH 22					//Rocket switch PIN

#define TIMER_N 53036						//Timer trappe værdi. 

//*******************************************************************************//
volatile unsigned char reflexCounter = 0;	//Global variable for placement of car
volatile int hold = -1;
volatile bool state = true;					//Bool state used to control the variable in interrupt routines
		
REMOTE_CONTROL rcBil;							//Reciever driver objekt
uint8_t buf[9];									// Set buffer to size of expected message
uint8_t buflen = sizeof(buf);
/****************************************************************/
// LOCAL FUNCTIONS
void initPortForInt();						//Initialize interrupts
void initSystem();
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
}

ISR(TIMER0_COMPA_vect)
{
	PORTB = PINB ^ 0b01000000;  //turn lights on on compare
}


//Setup of all ports and drivers
void setup()
{
	initSystem();
}


void loop()
{
	//DRIVE CONTROL
	while (digitalRead(ROCKET_SWITCH) == 0)
	{
		if (hold != reflexCounter)
		{
			driveControl(reflexCounter);
			hold++;
		}
	}
	
	/*************************************/
	//REMOTE CONTROL
	
	rearOff();
	rcBil.init();
	
	while (digitalRead(ROCKET_SWITCH) == 1)
	{
		
		rcBil.setSpeedValue(buf,buflen);				//calculates and gets the value read from the reciever
												//gets the button array
		rcBil.setButton(buf);
		
		rcBil.drive();									//executes the drive command
		
		rcBil.print();
		

		if (rcBil.buttonArray[BUTTON1] == true)
		{
			toggleFront();
		}
		if (rcBil.buttonArray[BUTTON2] == true)
		{
			soundReflex();
		}
		if (rcBil.buttonArray[BUTTON3] == true)
		{
			soundCompliment();
		}
		if (rcBil.buttonArray[BUTTON4] == true)
		{
			soundStart();
		}
		
		
	}
	rearOff();
	reflexCounter = 0;
	hold = 0;
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
	
	attachInterrupt(digitalPinToInterrupt(21), INT0Handler, RISING);
	attachInterrupt(digitalPinToInterrupt(20), INT1Handler, RISING);
	
	//Init Timer interrupts og prescaler
}
void initSystem()
{
	Serial.begin(9600);
	//init ports for interrupts
	initPortForInt();

	//init timer for reflex
	initTimer();

	//Init motor control
	initMotorPWMandToggle();

	//Init light control
	initLights();
	

	//init reciever
	//Init sound control
	InitUART(9600, 8, 0);
	volumeMax();

	//Init global interrupt
	sei();
	//make sure it starts at 0
	reflexCounter = 0;


}