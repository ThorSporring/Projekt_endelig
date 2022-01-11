// 
// 
// 

#include "driveControl.h"
#include "motor.h"

//DriveControl har til opgave at f�rer os igennem banen. Der er i alt 11 brikker p� banen. De 2 f�rste v�rdier i switchen benyttes til andre ting
//Der forekommer et interrupt n�r bilen t�ndes, derfor er case 1 tom
//Bilen starter med at k�re n�r en reflexbrik bliver viftet foran reflexdetektoren, alts� kommer switchen p� case 2

void driveControl(unsigned int reflexCounter)
{
	switch (reflexCounter)
	{
	case 1: //START

		//soundStart();
		forward(35,0,0);
		//backLightControl(50);
		break;

	case 2: //F�RSTE EFTER STARTLINJE

		forward(65,0,0);
		//soundReflex();
		//break;

	case 3: //LIGE FOR BAKKEN
		
		//soundReflex();
		//backLightControl(100);		//t�nder bremselys
		//forward(50);				//bremser

		//backLightControl(50);		//slukker bremselys
		break;

	case 4:				//TOPPEN AF BAKKEN
		stop();
	
		forward(15,0,0);

		//soundReflex();
		break;

	case 5:	//F�RSTE EFTER BAKKEN
		forward(40,0,0);
		//soundReflex();
		//forward(100);
		break;

	case 6:	//2. EFTER BAKKEN

		//soundReflex();
		break;

	case 7:	//STOP OG K�R BAGL�NS


		stop();
		backward(60,0,0);
		break;

	case 8: //HER SKAL DER INTET SKE


		break;

	case 9: //K�r forl�ns igen

		stop();
		forward(100,0,0);				
		break;

	case 10:


		break;

	case 11:

		break;

	case 12:	//M�lstrej
		stop();
		backward(60, 0, 0);
		stop();

		break;

	default:
		//tager h�jde for hvis reflexCounter er andre v�rdier end 0-11
		//errorLedSequence();		//en funktion der viser en fejlkode p� en given led
		break;
	}

}
