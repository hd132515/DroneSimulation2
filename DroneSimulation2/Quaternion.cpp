#include "stdafx.h"
#include "Quaternion.h"
#include "Vector.h"
#include <math.h>

Quaternion::Quaternion() : w(0.f), x(0.f), y(0.f), z(0.f)
{
}

Quaternion::Quaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z)
{
}

void Quaternion::rotater(Vector3& axis, float angle)
{
	Vector3 s_n_axis;
	if (axis.length() != 0.f)
		s_n_axis = sinf(angle / 2.f) * axis / axis.length();
	w = cosf(angle / 2.f);
	x = s_n_axis._1;
	y = s_n_axis._2;
	z = s_n_axis._3;
}

void Quaternion::toEuler(float& roll, float& pitch, float& yaw)
{
	// roll (x-axis rotation)
	float sinr = +2.0f * (w * x + y * z);
	float cosr = +1.0f - 2.0f * (x * x + y * y);
	roll = atan2f(sinr, cosr);

	// pitch (y-axis rotation)
	float sinp = +2.0f * (w * y - z * x);
	if (fabs(sinp) >= 1)
		pitch = copysignf(3.141592f / 2, sinp); // use 90 degrees if out of range
	else
		pitch = asinf(sinp);

	// yaw (z-axis rotation)
	float siny = +2.0f * (w * z + x * y);
	float cosy = +1.0f - 2.0f * (y * y + z * z);
	yaw = atan2f(siny, cosy);
}

Quaternion Quaternion::operator+(Quaternion& q)
{
	Quaternion ret;
	ret.w = w + q.w;
	ret.x = x + q.x;
	ret.y = y + q.y;
	ret.z = z + q.z;
	return ret;
}

Quaternion Quaternion::operator-()
{
	return (*this) * -1.f;
}

Quaternion Quaternion::operator-(Quaternion& q)
{
	return (*this) + (-q);
}

Quaternion Quaternion::operator*(float c)
{
	Quaternion ret;
	ret.w = w * c;
	ret.x = x * c;
	ret.y = y * c;
	ret.z = z * c;
	return ret;
}

void Quaternion::operator+=(Quaternion& q)
{
	Quaternion ret;
	ret = (*this) + q;
	(*this) = ret;
}

Quaternion Quaternion::conjugate()
{
	Quaternion ret;
	ret.w = w;
	ret.x = -x;
	ret.y = -y;
	ret.z = -z;
	return ret;
}

Quaternion Quaternion::normalize()
{
	Quaternion q = (*this);
	float magnitude = q.magnitude();
	if (magnitude != 0.f)
	{
		q.w = w / magnitude;
		q.x = x / magnitude;
		q.y = y / magnitude;
		q.z = z / magnitude;
	}

	return q;
}

float Quaternion::magnitude()
{
	return sqrtf(w*w + x*x + y*y + z*z);
}

Matrix3x3 Quaternion::to_matrix()
{
	Matrix3x3 ret;
	ret._11 = 1 - 2 * y*y - 2 * z*z; ret._12 = 2 * x*y - 2 * w*z;		ret._13 = 2 * x*z + 2*w*y;
	ret._21 = 2 * x*y + 2 * w*z;	 ret._22 = 1 - 2 * x*x - 2 * z*z;	ret._23 = 2 * y*z - 2 * w*x;
	ret._31 = 2 * x*z - 2 * w*y;	 ret._32 = 2 * y*z + 2 * w*x;		ret._33 = 1 - 2 * x*x - 2 * y*y;
	return ret;
}

Quaternion Quaternion::multiply(Quaternion& left, Quaternion& right)
{
	Quaternion res;
	Vector3 left_u(left.x, left.y, left.z);
	Vector3 right_u(right.x, right.y, right.z);

	res.w = left.w * right.w - Vector3::dot(left_u, right_u);
	Vector3 res_u = left.w*right_u + right.w*left_u + Vector3::cross(left_u, right_u);

	res.x = res_u._1;
	res.y = res_u._2;
	res.z = res_u._3;
	return res;
}

Quaternion operator*(float left, Quaternion& right)
{
	return right * left;
}