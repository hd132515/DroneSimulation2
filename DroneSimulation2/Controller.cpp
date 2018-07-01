#include "stdafx.h"
#include "Controller.h"
#include "ControlCommands.h"

Controller::Controller(Servo* _motor_array, BluetoothModule& _blmodule, Accelerometer& _accelerometer) : 
	motor_array(_motor_array), blmodule(_blmodule), accelerometer(_accelerometer), ready(false), last_command(-1)
{
}

void Controller::start()
{
	ready = true;
}

void Controller::stop()
{
	ready = false;
}

void Controller::loop()
{
	if (!ready) return;

	short command_data;
	int bl_readed = blmodule.pull_data(&command_data, sizeof(short));

	if (bl_readed <= 0)
		command_data = last_command;

	if (command_data == CMD_INIT_MOTOR)
	{
		for (auto i = 0; i < NUM_MOTOR; i++)
		{
			motor_array[i].write(0.f);
		}
	}
	else
	{
		char main_command = CMD_MAIN(command_data);
		if (main_command == CMD_MAIN_AUTO)
		{
		}
		else if (main_command == CMD_MAIN_MAN)
		{
			char sub_command = CMD_SUB(command_data);
			if (sub_command == CMD_SUB_MOVE)
			{
				char move_command = CMD_MOVE(command_data);
				if (move_command == CMD_MOVE_UP)
				{
					for (auto i = 0; i < NUM_MOTOR; i++)
					{
						motor_array[i].write(4.5f);
					}
				}
				else if (move_command == CMD_MOVE_DOWN)
				{
				}
				else if (move_command == CMD_MOVE_AXIS1)
				{
				}
				else if (move_command == CMD_MOVE_AXIS2)
				{
				}
			}
			else if (sub_command == CMD_SUB_STABLE)
			{
			}
		}
		else if (main_command == CMD_MAIN_LAND)
		{
		}
		else if (main_command == CMD_MAIN_FACTORFIND)
		{
		}
		last_command = command_data;
	}
}