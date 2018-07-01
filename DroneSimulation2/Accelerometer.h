#pragma once

#include "Vector.h"
#include "Matrix.h"

class Accelerometer
{
private:
	Vector3 in_ac;
public:
	void update(Vector3& outer_accel, Matrix3x3& orientation);
	Vector3& get_value();
};