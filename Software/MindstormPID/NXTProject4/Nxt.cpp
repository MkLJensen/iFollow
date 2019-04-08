#include <NXT++.h>
#include <stdio.h>
#include "Nxt.h"

Nxt::Nxt(){
	if (!Open())
	{
		printf("\nHovsa, der er da vist fejl i forbindelsen\n");
		exit(1);
	}

	printf("\nHej med dig min dejlige ven\n");
	}

void Nxt::InitSonar(int port) {
	if (port < 0 || port>3) {
		printf("\nWrong port number for sonar\n");
		exit(1);
	}
	SetSonar(port);
}

int Nxt::ReadSonar(int port) {
	return GetSonarValue(port);
}

void Nxt::ChangeSpeed(int portLeft,int portRight, int powerLeft, int powerRight) {
	if(powerLeft<0) {
		SetReverse(portLeft, -powerLeft);
	}
	else {
		SetForward(portLeft, powerLeft);
	}
	if (powerRight<0) {
		SetReverse(portRight, -powerRight);
	}
	else {
		SetForward(portRight, powerRight);
	}
}

void Nxt::StopMotor(int portLeft, int portRight, int brake) {
	Stop(portLeft, brake);
	Stop(portRight, brake);
}

void Nxt::playTone(int frequency_Hz, int duration_ms) {
	if (200 < frequency_Hz <= 8000) {
		if (0 < duration_ms) {
			PlayTone(frequency_Hz, duration_ms);
			Wait(duration_ms);
		}
		else {
			duration_ms = 0;
		}
	}
	else if(frequency_Hz<200) {
		frequency_Hz = 200;
	}
	else if(frequency_Hz>8001){
		frequency_Hz = 8000;
	}
		
	}
	
void Nxt::Pause(int duration_ms) {
	if (0 < duration_ms) {
		Wait(duration_ms);
	}
	else {
		duration_ms = 0;
	}
}

Nxt::~Nxt() {
	printf("Ses.\n");
	Close();
	}