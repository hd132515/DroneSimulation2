#pragma once

class Servo;
class BluetoothModule;
class Accelerometer;


class DroneInfoAcceptor
{

};

class DroneInfoDonor
{
public:
	DroneInfoDonor(DroneInfoAcceptor& _info_acceptor);
private:
	DroneInfoAcceptor& info_acceptor;

	Servo* motor_arr;
	BluetoothModule* blmodule;
	Accelerometer* accelerometer;

public:
};