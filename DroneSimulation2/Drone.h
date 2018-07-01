#pragma once

#include "Accelerometer.h"
#include "Servo.h"
#include "BluetoothModule.h"
#include "GeneralObject.h"

class Drone : public GeneralObject, public PostUpdateFunc
{
public:
	Drone();
	~Drone();

private:
	Vector3 motorpos[4];
	Servo motor[4];
	BluetoothModule blmodule;
	Accelerometer accelerometer;

protected:
	virtual int prepare_scenenode(IDirect3DDevice9* pDev);
	virtual int prepare_body();
public:
	virtual void interaction(ForceList& forces, Body* body);
	virtual void post_update();

	Servo* get_motor_array();
	BluetoothModule& get_bluetooth();
	Accelerometer& get_accelerometer();
};