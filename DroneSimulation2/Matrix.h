#pragma once

class Vector3;

class Matrix3x3
{
public:
	union {
		float mat[3][3];
		struct {
			float _11, _12, _13;
			float _21, _22, _23;
			float _31, _32, _33;
		};
	};
public:
	Matrix3x3();
	Matrix3x3(float* matrix);
public:
	Matrix3x3 operator+(Matrix3x3& right);
	Matrix3x3 operator-();
	Matrix3x3 operator-(Matrix3x3& right);
	Matrix3x3 operator*(float right);
	Matrix3x3 operator*(Matrix3x3& right);
	Vector3 operator*(Vector3& right);
	Matrix3x3 operator/(float right);

	void operator+=(Matrix3x3& right);
	void operator-=(Matrix3x3& right);
	void operator*=(float right);
	void operator/=(float right);

	Matrix3x3 transpose();
	float determinant();
	float C(int i, int j);
	Matrix3x3 inverse(float* det);

	static Matrix3x3 rotation(Vector3& axis, float angle);
	static Matrix3x3 star(Vector3& vec);
};