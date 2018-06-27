#include "stdafx.h"
#include "Matrix.h"
#include "Vector.h"
#include "utility.h"
#include <memory>

Matrix3x3::Matrix3x3()
{
	memset(mat, 0, sizeof(float) * 9);
}

Matrix3x3::Matrix3x3(float* matrix)
{
	for (int r = 1; r <= 3; r++)
	{
		for (int c = 1; c <= 3; c++)
		{
			mat[r-1][c-1] = matrix[I(r, c, 3)];
		}
	}
}

Matrix3x3 Matrix3x3::operator+(Matrix3x3& right)
{
	Matrix3x3 ret;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ret.mat[i][j] = mat[i][j] + right.mat[i][j];
		}
	}

	return ret;
}

Matrix3x3 Matrix3x3::operator-()
{
	Matrix3x3 ret;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ret.mat[i][j] = -mat[i][j];
		}
	}

	return ret;
}

Matrix3x3 Matrix3x3::operator-(Matrix3x3& right)
{
	return (*this) + (-right);
}

Matrix3x3 Matrix3x3::operator*(float right)
{
	Matrix3x3 ret;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ret.mat[i][j] = mat[i][j] * right;
		}
	}

	return ret;
}

Matrix3x3 Matrix3x3::operator*(Matrix3x3& right)
{
	Matrix3x3 ret;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int x = 0; x < 3; x++)
			{
				ret.mat[i][j] += mat[i][x] * right.mat[x][j];
			}
		}
	}

	return ret;
}

Vector3 Matrix3x3::operator*(Vector3& right)
{
	Vector3 ret;

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			ret.vec[j] += mat[j][i] * right.vec[i];
		}
	}

	return ret;
}

Matrix3x3 Matrix3x3::operator/(float right)
{
	return (*this) * (1/right);
}

void Matrix3x3::operator+=(Matrix3x3& right)
{
	(*this) = (*this) + right;
}

void Matrix3x3::operator-=(Matrix3x3& right)
{
	(*this) = (*this) - right;
}

void Matrix3x3::operator*=(float right)
{
	(*this) = (*this) * right;
}

void Matrix3x3::operator/=(float right)
{
	(*this) = (*this) / right;
}

Matrix3x3 Matrix3x3::transpose()
{
	Matrix3x3 ret;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ret.mat[i][j] = mat[j][i];
		}
	}
	
	return ret;
}

float Matrix3x3::determinant()
{
	return _11 * (_22*_33 - _23*_32) - _12*(_21*_33 - _23*_31) + _13*(_21*_32 - _22*_31);
}

float Matrix3x3::C(int i, int j)
{
	float newmat[4];
	int el = 0;

	for (int x = 0; x < 3; x++)
	{
		if (x == i) continue;
		for (int y = 0; y < 3; y++)
		{
			if (y == j)	continue;
			newmat[el++] = mat[x][y];
		}
	}

	return powf(-1.f, (float)(i + j + 2)) * (newmat[0] * newmat[3] - newmat[1] * newmat[2]);
}

Matrix3x3 Matrix3x3::inverse(float* det)
{
	Matrix3x3 ret;

	*det = determinant();
	if (*det == 0) return ret;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			ret.mat[i][j] = C(j, i);
		}
	}
	
	ret /= *det;
	return ret;
}

Matrix3x3 Matrix3x3::rotation(Vector3& axis, float angle)
{
	Matrix3x3 mat;
	if(axis.length() != 0.f)
		axis /= axis.length();
	mat._11 = cosf(angle) + axis._1*axis._1*(1 - cosf(angle));
	mat._12 = axis._1*axis._2*(1 - cosf(angle)) - axis._3*sinf(angle);
	mat._13 = axis._1*axis._3*(1 - cosf(angle)) + axis._2*sinf(angle);
	mat._21 = axis._2*axis._1*(1 - cosf(angle)) + axis._3*sinf(angle);
	mat._22 = cosf(angle) + axis._2*axis._2*(1 - cosf(angle));
	mat._23 = axis._2*axis._3*(1 - cosf(angle)) - axis._1*sinf(angle);
	mat._31 = axis._3*axis._1*(1 - cosf(angle)) - axis._2*sinf(angle);
	mat._32 = axis._3*axis._2*(1 - cosf(angle)) + axis._1*sinf(angle);
	mat._33 = cosf(angle) + axis._3*axis._3*(1 - cosf(angle));
	return mat;
}

Matrix3x3 Matrix3x3::star(Vector3& vec)
{
	Matrix3x3 mat;
	mat._11 = 0.f;
	mat._12 = -vec._3;
	mat._13 = vec._2;
	mat._21 = vec._3;
	mat._22 = 0.f;
	mat._23 = -vec._1;
	mat._31 = -vec._2;
	mat._32 = vec._1;
	mat._33 = 0.f;

	return mat;
}