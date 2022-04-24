#include<iostream>
#include<omp.h>
#include<cmath>

using namespace std;

void print(double** arr, int lines, int columns)
{
	for (int i = 0; i < lines; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void divide(double** arr, int line_index, int line_length, double coef)
{
	for (int i = 0; i < line_length; ++i)
	{
		arr[line_index][i] /= coef;
	}
}

void subtract(double** arr, int line_index1, int line_index2, int line_length, double coef)
{
	for (int i = 0; i < line_length; ++i)
	{
		arr[line_index1][i] -= arr[line_index2][i]*coef;
	}
}

int column_max(double** arr, int column_index, int lines)
{
	int max_index = column_index;
	for (int i = column_index; i < lines; ++i)
	{
		if (abs(arr[i][column_index]) > abs(arr[max_index][column_index]))
		{
			max_index = i;
		}
	}
	return max_index;
}
void swap(double* line_i, double* line_max)
{
	double* temp = line_i;
	line_i = line_max;
	line_max = temp;
}

void transform_posl(double** arr, int lines, int columns)
{
	for (int i = 0; i < columns - 1; ++i)
	{
		swap(arr[i], arr[column_max(arr, i, lines)]);
		divide(arr, i, columns, arr[i][i]);
		for (int j = 0; j < lines; ++j)
		{
			if (j != i)
			{
				subtract(arr, j, i, columns, arr[j][i]);
			}
		}
	}
}

void transform_parl(double** arr, int lines, int columns)
{

	for (int i = 0; i < columns - 1; ++i)
	{
		swap(arr[i], arr[column_max(arr, i, lines)]);
		divide(arr, i, columns, arr[i][i]);
#pragma omp parallel for schedule(static, 5)
		for (int j = 0; j < lines; ++j)
		{
			if (j != i)
			{
				subtract(arr, j, i, columns, arr[j][i]);
			}
		}
	}
}

int main()
{
	int lines = 0;
	int columns = 0;
	cout << "equations number" << endl;
	cin >> lines;
	columns = lines + 1;
	double** arr_posl = new double* [lines];
	double** arr_parl = new double* [lines];
	for (int i = 0; i < lines; ++i)
	{
		arr_posl[i] = new double[columns];
		arr_parl[i] = new double[columns];
	}
	cout << "cin >> matrix" << endl;
	for (int i = 0; i < lines; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			cin >> arr_posl[i][j];
			arr_parl[i][j] = arr_posl[i][j];
		}
	}
	cout << endl;
	transform_posl(arr_posl, lines, columns);
	double t = omp_get_wtime();
	transform_posl(arr_posl, lines, columns);
	cout << "Time posl:" << omp_get_wtime() - t << endl;
	print(arr_posl, lines, columns);
	t = omp_get_wtime();
	transform_posl(arr_parl, lines, columns);
	cout << "Time parl:" << omp_get_wtime() - t << endl;
	print(arr_parl, lines, columns);
	return 0;
}