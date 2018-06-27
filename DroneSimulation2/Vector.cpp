#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"
#include <memory>


Vector3::Vector3()
{
	memset(vec, 0, sizeof(float) * 3);
}

Vector3::Vector3(float _1_, float _2_, float _3_) : _1(_1_), _2(_2_), _3(_3_)
{
}

Vector3 Vector3::operator+(Vector3& right)
{
	Vector3 ret;
	for (int i = 0; i < 3; i++)
	{
		ret.vec[i] = vec[i] + right.vec[i];
	}
	return ret;
}

Vector3 Vector3::operator-()
{
	Vector3 ret;
	for (int i = 0; i < 3; i++)
	{
		ret.vec[i] = -vec[i];
	}
	return ret;
}

Vector3 Vector3::operator-(Vector3& right)
{
	return (*this) + (-right);
}

Vector3 Vector3::operator*(float right)
{
	Vector3 ret;
	for (int i = 0; i < 3; i++)
	{
		ret.vec[i] = vec[i] * right;
	}
	return ret;
}

Vector3 Vector3::operator*(Matrix3x3& right)
{
	Vector3 ret;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ret.vec[i] += vec[j] * right.mat[j][i];
		}
	}
	return ret;
}

Vector3 Vector3::operator/(float right)
{
	return (*this) * (1 / right);
}

void Vector3::operator+=(Vector3& right)
{
	(*this) = (*this) + right;
}

void Vector3::operator-=(Vector3& right)
{
	(*this) = (*this) - right;
}

void Vector3::operator*=(float right)
{
	(*this) = (*this) * right;
}

void Vector3::operator/=(float right)
{
	(*this) = (*this) / right;
}

float Vector3::dot(Vector3& left, Vector3& right)
{
	float ret = 0.f;
	for (int i = 0; i < 3; i++)
	{
		ret += left.vec[i] * right.vec[i];
	}
	return ret;
}

Vector3 Vector3::cross(Vector3& left, Vector3& right)
{
	Vector3 ret;
	ret._1 =   left._2 * right._3 - left._3 * right._2;
	ret._2 = -(left._1 * right._3 - left._3 * right._1);
	ret._3 =   left._1 * right._2 - left._2 * right._1;

	return ret;
}

float Vector3::length()
{
	return sqrt(_1*_1 + _2*_2 + _3*_3);
}

Vector3 Vector3::getNorm()
{
	if (length() - 0.f < 0.0000001f)
		return (*this);

	return (*this) / length();
}

Vector3 operator*(float left, Vector3& right)
{
	return right * left;
}