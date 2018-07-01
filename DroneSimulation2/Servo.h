#pragma once

#include "DroneInterface.h"

class Servo
{
public:
	Servo();
private:
	float output;
public:
	void write(float value);
	float get_output();
};