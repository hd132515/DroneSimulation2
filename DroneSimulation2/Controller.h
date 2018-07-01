#pragma once

#define NUM_MOTOR 4

#include "Accelerometer.h"
#include "Servo.h"
#include "BluetoothModule.h"

class Controller
{
public:
	Controller(Servo* _motor_array, BluetoothModule& _blmodule, Accelerometer& _accelerometer);
private:
	bool ready;
	short last_command;
	Servo* motor_array;
	BluetoothModule& blmodule;
	Accelerometer& accelerometer;

public:

	void start();
	void stop();

	void loop();
};