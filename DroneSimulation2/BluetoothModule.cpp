#include "stdafx.h"
#include "BluetoothModule.h"

BluetoothModule::BluetoothModule() : write_pos(0), read_pos(0)
{
}

int BluetoothModule::add_data(void* data, int size)
{
	if (data == nullptr) return -1;

	int remain = size + write_pos - BUFFER_SIZE;
	if (remain > read_pos)
	{
		return -2;
	}
	else if (remain < 0)
	{
		if (write_pos + size <= read_pos)
		{
			return -2;
		}
		else
		{
			memcpy(stream_data + write_pos, data, size);
			write_pos += size;
		}
	}
	else
	{
		memcpy(stream_data + write_pos, data, size - remain);
		memcpy(stream_data, data, remain);
		write_pos = remain;
	}

	return size;
}

int BluetoothModule::pull_data(void* data, int size)
{
	if (data == nullptr) return -1;

	int remain = size + read_pos - BUFFER_SIZE;
	if (remain > write_pos)
	{
		return -2;
	}
	else if (remain < 0)
	{
		if (read_pos + size > write_pos)
		{
			return -2;
		}
		else
		{
			memcpy(data, stream_data + read_pos, size);
			read_pos += size;
		}
	}
	else
	{
		memcpy(data, stream_data + read_pos, size - remain);
		memcpy(data, stream_data, remain);
		read_pos = remain;
	}

	return size;
}