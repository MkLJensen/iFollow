#pragma comment( lib, "NXT++.lib" )
#include <NXT++.h>
#include <stdio.h>
#include "Nxt.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void updateScreen(float, float, int);

float error, sig, last_error, integral, derivative, control;
float kp = 2.80;
float ki = 0.05;
float kd = 0.05;
float goal = 30;

int sonarLeft = 3;
int sonarRight = 0;
int motorLeft = 1;
int motorRight = 0;

void handleKey();

int main()
{
	Nxt myNxt;

	myNxt.InitSonar(sonarLeft);
	myNxt.InitSonar(sonarRight);

	while (1)
	{
		sig = (myNxt.ReadSonar(sonarLeft)+myNxt.ReadSonar(sonarRight))/2;
		handleKey();
		updateScreen(control,sig,error);

		/*Calculate Error (P)*/
		error = goal - sig;

		/*Calculate integral (I)*/
		integral += error;

		/*Calculate the derivative (D)*/
		derivative = error - last_error;

		/*Calculate the control variable*/
		control = (kp*error) + (ki*integral) + (kd*derivative);

		/*Limit control*/
		if (control > 100) control = 100;
		else if (control < -100) control = -100;

		/*Adjust variable*/
		//sig += control;

		/*Save last error*/
		last_error = error;

		/*Choose wether to move foward or reverse*/
		myNxt.ChangeSpeed(motorLeft,motorRight,-control,-control);
	}
}

void handleKey()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (sig > -360.0) sig -= 10.0;
		else sig = -360.0;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (sig < 360.0) sig += 10.0;
		else sig = 360.0;

	}
	if (GetAsyncKeyState(0x50))
	{
		kp += 0.01;

	}
	if (GetAsyncKeyState(0x49))
	{
		ki += 0.01;

	}
	if (GetAsyncKeyState(0x44))
	{
		kd += 0.01;
	}
}

void updateScreen(float x, float y, int z)
{
	system("cls");
	cout << x << '\n';
	cout << "Sensor: " << y << '\n';
	cout << "Error: " << z << '\n';
	cout << "P: " << kp << '\n';
	cout << "I: " << ki << '\n';
	cout << "D: " << kd << '\n';
}
