#include "stdafx.h"
#include "Accelerometer.h"

void Accelerometer::update(Vector3& outer_accel, Matrix3x3& orientation)
{
	in_ac = orientation.transpose() * outer_accel;
}

Vector3& Accelerometer::get_value()
{
	return in_ac;
}