#pragma once

class Matrix3x3;

class Vector3
{
public:
	union{
		float vec[3];
		struct{
			float _1, _2, _3;
		};
	};
public:
	Vector3();
	Vector3(float _1_, float _2_, float _3_);
public:
	Vector3 operator+(Vector3& right);
	Vector3 operator-();
	Vector3 operator-(Vector3& right);
	Vector3 operator*(float right);
	Vector3 operator*(Matrix3x3& right);
	Vector3 operator/(float right);

	void operator+=(Vector3& right);
	void operator-=(Vector3& right);
	void operator*=(float right);
	void operator/=(float right);

	static float dot(Vector3& left, Vector3& right);
	static Vector3 cross(Vector3& left, Vector3& right);

	float length();
	Vector3 getNorm();
};

Vector3 operator*(float left, Vector3& right);