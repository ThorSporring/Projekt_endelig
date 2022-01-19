// 
// 
// 

#include "driveControl.h"
#include "motor.h"
#include "lyd_uart.h"
#include "lys_styring.h"
#include <util/delay.h>

//DriveControl har til opgave at f�rer os igennem banen. Der er i alt 11 brikker p� banen. De 2 f�rste v�rdier i switchen benyttes til andre ting
//Der forekommer et interrupt n�r bilen t�ndes, derfor er case 1 tom
//Bilen starter med at k�re n�r en reflexbrik bliver viftet foran reflexdetektoren, alts� kommer switchen p� case 2

void driveControl(unsigned int reflexCounter)
{
	switch (reflexCounter)
	{
	case 1: //START
		brakeRearOn();
		brakeRearOff();
		soundStart();
		_delay_ms(200);
		onFront();
		_delay_ms(100);
		toggleFront();
		_delay_ms(100);
		toggleFront();
		_delay_ms(100);
		toggleFront();
		_delay_ms(300);
		toggleFront();
		driveRear();
		forward(50,0,0);
		
		break;

	case 2: //F�RSTE EFTER STARTLINJE
		soundReflex();
		forward(80,1,0.7);
		
		//break;

	case 3: //LIGE FOR BAKKEN
		soundReflex();
		break;

	case 4:							//TOPPEN AF BAKKEN
		soundReflex();
		
		brakeRearOn();
		brakeRearOff();
		stop();
	
		forward(15,0,0);

		
		break;

	case 5:								//F�RSTE EFTER BAKKEN
		soundReflex();
		forward(60,0,0);
		
		//forward(100);
		break;

	case 6:								//2. EFTER BAKKEN
		soundReflex();
		break;

	case 7:								//STOP OG K�R BAGL�NS
		soundReflex();
		brakeRearOn();
		brakeRearOff();
		stop();
		backward(100,0,0);
		break;

	case 8:								//HER SKAL DER INTET SKE
		soundReflex();

		break;

	case 9:								//K�r forl�ns igen
		soundReflex();
				
		break;

	case 10:
		soundReflex();
		brakeRearOn();
		brakeRearOff();
		stop();
		forward(100, 0, 0);
		break;

	case 11:
		soundReflex();
		break;
	case 12:
		soundReflex();
		break;
	case 13:								//M�lstrej
		soundEnd();
		brakeRearOn();
		brakeRearOff();
		backward(100, 0, 0);
		stop();
		_delay_ms(2000);
		toggleFront();
		rearOff();
		break;

	default:
		rearOff();
		//tager h�jde for hvis reflexCounter er andre v�rdier end 0-11
		//errorLedSequence();		//en funktion der viser en fejlkode p� en given led
		break;
	}

}
