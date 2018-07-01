#include "stdafx.h"
#include "DroneInterface.h"
#include "Servo.h"
#include "BluetoothModule.h"


DroneInfoDonor::DroneInfoDonor(DroneInfoAcceptor& _info_acceptor) : info_acceptor(_info_acceptor)
{
}