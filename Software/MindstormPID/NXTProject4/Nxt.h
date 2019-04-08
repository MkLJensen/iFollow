#pragma once
#include <NXT++.h>
#include <stdio.h>

class Nxt {
public:
	Nxt();
	void playTone(int frequency_Hz, int duration_ms);
	void Pause(int duration_ms);
	void InitSonar(int port);
	int ReadSonar(int port);
	void ChangeSpeed(int portLeft, int portRight, int powerLeft, int powerRight);
	void Nxt::StopMotor(int portLeft, int portRight, int brake);
	~Nxt();
};