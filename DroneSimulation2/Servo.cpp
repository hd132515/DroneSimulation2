#include "stdafx.h"
#include "Servo.h"

Servo::Servo() : output(0)
{
}

void Servo::write(float value)
{
	output = value;
}

float Servo::get_output()
{
	return output;
}