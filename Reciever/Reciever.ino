/*
 Name:		Reciever.ino
 Created:	1/13/2022 11:03:13 AM
 Author:	spott
*/
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rfDriver;

// the setup function runs once when you press reset or power the board
void setup() {
	rfDriver.init();
}

// the loop function runs over and over again until power down or reset
void loop() {
    // Set buffer to size of expected message
    uint8_t buf[9];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rfDriver.recv(buf, &buflen))
    {

        // Message received with valid checksum
        Serial.print("Message Received: ");
        Serial.println((char*)buf);
    }
}
