#pragma once
#include <RH_ASK.h>
#include <SPI.h>
#include "motor.h"
class REMOTE_CONTROL
{
public:
	REMOTE_CONTROL();
	void calculateSpeedForward();
	void calculateSpeedBackward();
	void setButton(uint8_t *buf);
	void setSpeedValue(uint8_t* buf, uint8_t buflen);

	int getSpeedForward();
	int getSpeedBackward();
	bool buttonArray[4];
	int getSpeedValue();
	void init();
	void drive();
	void print();
private:
	RH_ASK rfDriver_;
	int speedValue_;
	int speedForward_;
	int speedBackward_;
	bool buttons_[4];

};

