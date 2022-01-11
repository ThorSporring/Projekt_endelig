// 
// 
// 

#include "driveControl.h"
#include "motor.h"

//DriveControl har til opgave at fører os igennem banen. Der er i alt 11 brikker på banen. De 2 første værdier i switchen benyttes til andre ting
//Der forekommer et interrupt når bilen tændes, derfor er case 1 tom
//Bilen starter med at køre når en reflexbrik bliver viftet foran reflexdetektoren, altså kommer switchen på case 2

void driveControl(unsigned int reflexCounter)
{
	switch (reflexCounter)
	{
	case 1: //START

		//soundStart();
		forward(35,0,0);
		//backLightControl(50);
		break;

	case 2: //FØRSTE EFTER STARTLINJE

		forward(65,0,0);
		//soundReflex();
		//break;

	case 3: //LIGE FOR BAKKEN
		
		//soundReflex();
		//backLightControl(100);		//tænder bremselys
		//forward(50);				//bremser

		//backLightControl(50);		//slukker bremselys
		break;

	case 4:				//TOPPEN AF BAKKEN
		stop();
	
		forward(15,0,0);

		//soundReflex();
		break;

	case 5:	//FØRSTE EFTER BAKKEN
		forward(40,0,0);
		//soundReflex();
		//forward(100);
		break;

	case 6:	//2. EFTER BAKKEN

		//soundReflex();
		break;

	case 7:	//STOP OG KØR BAGLÆNS


		stop();
		backward(60,0,0);
		break;

	case 8: //HER SKAL DER INTET SKE


		break;

	case 9: //Kør forlæns igen

		stop();
		forward(100,0,0);				
		break;

	case 10:


		break;

	case 11:

		break;

	case 12:	//Målstrej
		stop();
		backward(60, 0, 0);
		stop();

		break;

	default:
		//tager højde for hvis reflexCounter er andre værdier end 0-11
		//errorLedSequence();		//en funktion der viser en fejlkode på en given led
		break;
	}

}
