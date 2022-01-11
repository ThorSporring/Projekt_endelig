#pragma once


//initialize timer 3 til normal mode

void initTimer();

//start timer3 og aktiver interrupt. Variable N er 65536 - N.
// Alts� hvor den skal st� p� trappen

void startTimerInt(unsigned int N);

//stopper timer3, deaktiverer interrupts og fjerner overflowflaget 

void stopTimerInt();

#pragma once
