#pragma once

#include "Vector.h"
#include "Matrix.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(float _w, float _x, float _y, float _z);
public:
	float w, x, y, z;
public:
	Quaternion operator+(Quaternion& right);
	Quaternion operator-();
	Quaternion operator-(Quaternion& right);
	Quaternion operator*(float c);

	void operator+=(Quaternion& right);
	
	Quaternion normalize();
	Quaternion conjugate();
	float magnitude();
	Matrix3x3 to_matrix();
	void rotater(Vector3& axis, float angle);
	void toEuler(float& roll, float& pitch, float& yaw);
public:
	static Quaternion multiply(Quaternion& left, Quaternion& right);
};

Quaternion operator*(float left, Quaternion& right);