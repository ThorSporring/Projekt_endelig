// 
// 
// 

#include "driveControl.h"
#include "motor.h"
#include "lyd_uart.h"
#include "lys_styring.h"
#include <util/delay.h>

//DriveControl har til opgave at fører os igennem banen. Der er i alt 11 brikker på banen. De 2 første værdier i switchen benyttes til andre ting
//Der forekommer et interrupt når bilen tændes, derfor er case 1 tom
//Bilen starter med at køre når en reflexbrik bliver viftet foran reflexdetektoren, altså kommer switchen på case 2

void driveControl(unsigned int reflexCounter)
{
	switch (reflexCounter)
	{
	case 1: //START
		soundStart();
		onFront();
		_delay_ms(100);
		toggleFront();
		_delay_ms(100);
		toggleFront();
		_delay_ms(100);
		toggleFront();
		driveRear();
		forward(35,0,0);
		
		break;

	case 2: //FØRSTE EFTER STARTLINJE
		forward(65,0,0);
		soundReflex();
		//break;

	case 3: //LIGE FOR BAKKEN
		soundReflex();
		//backLightControl(100);		//tænder bremselys
		//forward(50);				//bremser

		//backLightControl(50);		//slukker bremselys
		break;

	case 4:							//TOPPEN AF BAKKEN
		soundReflex();
		
		brakeRearOn();
		brakeRearOn();
		stop();
	
		forward(15,0,0);

		
		break;

	case 5:								//FØRSTE EFTER BAKKEN
		soundReflex();
		forward(40,0,0);
		
		//forward(100);
		break;

	case 6:								//2. EFTER BAKKEN
		soundReflex();
		break;

	case 7:								//STOP OG KØR BAGLÆNS
		soundReflex();
		brakeRearOn();
		brakeRearOff();
		stop();
		backward(100,0,0);
		break;

	case 8:								//HER SKAL DER INTET SKE
		soundReflex();

		break;

	case 9:								//Kør forlæns igen
		soundReflex();
		brakeRearOn();
		brakeRearOff();
		stop();
		forward(100,0,0);				
		break;

	case 10:
		soundReflex();

		break;

	case 11:
		soundReflex();
		break;

	case 12:								//Målstrej
		stop();
		backward(100, 0, 0);
		stop();
		toggleFront();
		rearOff();
		break;

	default:
		rearOff();
		//tager højde for hvis reflexCounter er andre værdier end 0-11
		//errorLedSequence();		//en funktion der viser en fejlkode på en given led
		break;
	}

}
