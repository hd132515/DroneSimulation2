#pragma once

#include "DroneInterface.h"

#define BUFFER_SIZE 1024

class BluetoothModule
{
public:
	BluetoothModule();
private:
	unsigned char stream_data[BUFFER_SIZE];
	int write_pos;
	int read_pos;
public:
	int add_data(void* data, int size);
	int pull_data(void* data, int size);

};