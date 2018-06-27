#pragma once

#include <d3dx9.h>
#include <stdlib.h>
#include "Vector.h"
#include "Matrix.h"

float random();
float inverseMatrix(float* in, float* out, int rank);
float determinant(float* in, int rank);
float cofactor(float* in, int row, int col, int rank);

void matmul(float** ret, float* a, float* b, int a_r, int a_c, int b_r, int b_c);

//1-dimensionised Matrix's Index for Square Matrix
int I(int row, int col, int rank);
//1-dimensionised Matrix's Index for Matrix
int I(int row, int col, int r, int c);
void row_exchange(float* in, int row, int col, int r1, int r2);
void row_multiply(float* in, int row, int col, int r, double constant);
void row_summation(float* in, int row, int col, int r_from, int r_to, double constant);
void gauss_jordan_elimination(float* in, int row, int col);
/*
--out
resolution(resolution pointer's pointer), res_row(resolution matrix row number), res_col(resolution matrix column number)
indep_start(independence variable's number)
--in
factors(At Eq. Ax=b, A), f_row(A's row), f_col(A's column)
constants(At Eq. Ax=b, b), c_row(b's row), c_col(b's column)
*/
void solve_linear_equation(float** resolution, int* res_row, int* res_col, int* indep_start, float* factors,
	int f_row, int f_col, float* constants, int c_row, int c_col);
