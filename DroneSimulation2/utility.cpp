#include "stdafx.h"
#include "utility.h"
#include <memory.h>
#include <math.h>
#include <float.h>

float random()
{
	static int randval = 0;
	int currentrand;
	while (randval == (currentrand = rand()));
	randval = currentrand;
	return (randval % 1024) / 1024.f;
}

float inverseMatrix(float* in, float* out, int rank)
{
	float det = determinant(in, rank);
	if (det != 0.f)
	{
		for (int r = 1; r <= rank; r++)
		{
			for (int c = 1; c <= rank; c++)
			{
				out[I(r, c, rank)] = cofactor(in, c, r, rank) / det;
			}
		}
	}
	return det;
}

float determinant(float* in, int rank)
{
	if (rank == 2)
	{
		return in[I(1, 1, 2)] * in[I(2, 2, 2)] - in[I(1, 2, 2)] * in[I(2, 1, 2)];
	}
	else
	{
		float retval = 0.f;
		for (int r = 1; r <= rank; r++)
		{
			retval += in[I(r, 1, rank)] * cofactor(in, r, 1, rank);
		}
		return retval;
	}
}

float cofactor(float* in, int row, int col, int rank)
{
	float* comat = new float[(rank - 1) * (rank - 1)];

	int row_back = 0;
	for (int r = 1; r <= rank; r++)
	{
		int col_back = 0;
		if (r == row)
		{
			row_back++;
			continue;
		}
		for (int c = 1; c <= rank; c++)
		{
			if (c == col)
			{
				col_back++;
				continue;
			}
			comat[I(r - row_back, c - col_back, rank - 1)] = in[I(r, c, rank)];
		}
	}

	float retval = powf(-1.f, (float)(row + col)) * determinant(comat, rank - 1);
	delete[] comat;
	return retval;
}

void matmul(float** ret, float* a, float* b, int a_r, int a_c, int b_r, int b_c)
{
	if (a_c != b_r)
	{
		*ret = NULL;
		return;
	}

	if (*ret == NULL)
	{
		*ret = new float[a_r * b_c];
		memset(*ret, 0, sizeof(float)*a_r*b_c);
	}

	for (int r = 1; r <= a_r; r++)
	{
		for (int c = 1; c <= b_c; c++)
		{
			for (int i = 1; i <= a_c; i++)
			{
				float val = a[I(a_r, a_c, r, i)] * b[I(b_r, b_c, i, c)];
				(*ret)[I(a_r, b_c, r, c)] += fabs(val) >= FLT_EPSILON ? val : 0.f;
			}
		}
	}
}

int I(int row, int col, int rank)
{
	return (row - 1) * rank + (col - 1);
}


int I(int row, int col, int r, int c)
{
	return (r - 1) * col + (c - 1);
}

void row_exchange(float* in, int row, int col, int r1, int r2)
{
	float temp;
	for (int c = 1; c <= col; c++)
	{
		temp = in[I(row, col, r1, c)];
		in[I(row, col, r1, c)] = in[I(row, col, r2, c)];
		in[I(row, col, r2, c)] = temp;
	}
}

void row_multiply(float* in, int row, int col, int r, double constant)
{
	for (int c = 1; c <= col; c++)
	{
		double val = (double)in[I(row, col, r, c)];
		double res = val * constant;
		in[I(row, col, r, c)] = (float)res;
	}
}

void row_summation(float* in, int row, int col, int r_from, int r_to, double constant)
{
	for (int c = 1; c <= col; c++)
	{
		double t_val = (double)in[I(row, col, r_to, c)];
		double f_val = (double)in[I(row, col, r_from, c)];
		double res = t_val + f_val * constant;
		in[I(row, col, r_to, c)] = (float)res;
	}
}

int pivot_col(float* in, int row, int col, int r)
{
	int pc = 1;
	for (; pc <= col && in[I(row, col, r, pc)] == 0.f; pc++);
	return pc;
}

void gauss_jordan_elimination(float* in, int row, int col)
{
	int ended_row = row;
	//gauss(downward)
	for (int std_r = 1; std_r <= row; std_r++)
	{
		//find min pivot row and min pivot col from standard row
		int min_pc_r = std_r;
		int min_pc = pivot_col(in, row, col, std_r);
		for (int r = std_r; r <= row; r++)
		{
			int pc_val = pivot_col(in, row, col, r);
			if (min_pc > pc_val) {
				min_pc = pc_val;
				min_pc_r = r;
			}
		}

		if (min_pc > col) //cannot find not null row
		{
			ended_row = std_r - 1;
			break;
		}
		else if (std_r != min_pc_r)//standard row's pivot column is not minimum. exchange row
		{
			row_exchange(in, row, col, std_r, min_pc_r);
		}

		//eliminiation
		int std_pivot_col = pivot_col(in, row, col, std_r);
		double std_pivot_val = (double)in[I(row, col, std_r, std_pivot_col)];
		for (int r = std_r + 1; r <= row; r++)
		{
			int r_pivot_col = pivot_col(in, row, col, r);
			if (r_pivot_col > col)continue;

			double r_pivot_val = (double)in[I(row, col, r, r_pivot_col)];
			if (fabs(r_pivot_val) >= FLT_EPSILON) //r_pivot_val != 0.f
			{
				row_summation(in, row, col, std_r, r, -r_pivot_val / std_pivot_val);
			}
			in[I(row, col, r, r_pivot_col)] = 0.f;
		}
	}

	//jordan(upward) elimination, clearing
	for (int std_r = ended_row; std_r >= 1; std_r--)
	{
		int std_pivot_col = pivot_col(in, row, col, std_r);
		double std_pivot_val = (double)in[I(row, col, std_r, std_pivot_col)];
		for (int r = std_r - 1; r >= 1; r--)
		{
			double r_target_val = (double)in[I(row, col, r, std_pivot_col)];
			if (fabs(r_target_val) >= FLT_EPSILON) //r_target_val != 0.f
			{
				row_summation(in, row, col, std_r, r, -r_target_val / std_pivot_val);
				in[I(row, col, r, std_pivot_col)] = 0.f;
			}
		}

		row_multiply(in, row, col, std_r, 1 / std_pivot_val);
	}
}

/*
--out
resolution
res_row
res_col
indep_start
--in
factors
f_row
f_col
constants
c_row
c_col
*/
void solve_linear_equation(float** resolution, int* res_row, int* res_col, int* indep_start, float* factors,
	int f_row, int f_col, float* constants, int c_row, int c_col)
{
	if (f_row == c_row && c_col == 1)
	{
		int a_row = f_row;
		int a_col = f_col + c_col;
		float* matrix = new float[a_row * a_col];
		for (int r = 1; r <= a_row; r++)
		{
			for (int c = 1; c <= a_col; c++)
			{
				if (c <= a_col - c_col)
					matrix[I(a_row, a_col, r, c)] = factors[I(f_row, f_col, r, c)];
				else
					matrix[I(a_row, a_col, r, c)] = constants[I(c_row, c_col, r, 1)];
			}
		}

		gauss_jordan_elimination(matrix, a_row, a_col);

		int fc;
		for (fc = 1; fc <= a_col && fc <= a_row; fc++)
		{
			if (matrix[I(a_row, a_col, fc, fc)] == 0.f)break;
		}
		*indep_start = fc;
		int indep_end = f_col;
		*res_row = indep_end - *indep_start + 1 + 1;
		*res_col = f_col;
		*resolution = new float[*res_row * *res_col];
		memset(*resolution, 0, sizeof(float) * *res_row * *res_col);

		for (int r = 1; r <= *res_row; r++)
		{
			for (int c = 1; c <= *res_col; c++)
			{
				if (r != *res_row)//비율 행
				{
					if (c == *indep_start + (r - 1))//독립 문자 비율 = 1
					{
						(*resolution)[I(*res_row, *res_col, r, c)] = 1.f;
					}
					else if (c <= a_row)//의존 문자 비율
					{
						(*resolution)[I(*res_row, *res_col, r, c)] =
							-matrix[I(a_row, a_col, c, *indep_start + (r - 1))];
					}
				}
				else//마지막 행 : 상수행
				{
					if (c <= a_row)
						(*resolution)[I(*res_row, *res_col, r, c)] = matrix[I(a_row, a_col, c, a_col)];
					else
						(*resolution)[I(*res_row, *res_col, r, c)] = 0.f;
				}
			}
		}

		delete[] matrix;
	}
	else
	{
		*resolution = NULL;
	}
}