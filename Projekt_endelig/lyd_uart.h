/****************************************
* "uart_int.h":                         *
* Header file for Mega2560 UART driver. *
* Using UART 0.                         *
* If parameter Rx_Int <> 0 :            *
* Receiver interrupt will be enabled    *
*****************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char RX_Int);
unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);
void soundStart();
void soundReflex();
void soundEnd();
void volumeMax();
/****************************************/
