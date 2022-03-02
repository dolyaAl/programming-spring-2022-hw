#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cmath>
using namespace std;

double pi = acos(-1);

double* sin_c = new double[10000000];
double* sin_p = new double[10000000];

void sin_consistently(int n)
{
	double t = omp_get_wtime();
	for (int i = 0; i <= n; ++i)
	{
		sin_c[i] = sin(pi * i / (2 * n));
	}
	cout << "Time cons: " << omp_get_wtime() - t << endl;
}

void sin_parallel(int n)
{
	double t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n / 2; i++)
			{
				sin_p[i] = sin(pi * i / (2 * n));
			}
		}
#pragma omp section
		{
			for (int i = n / 2; i <= n; i++)
			{
				sin_p[i] = sin(pi * i / (2 * n));
			}
		}
	}
	cout << "Time par: " << omp_get_wtime() - t << endl;
}

double pi_arctg_cons(int n)
{
	return 0;
}

double pi_arctg_par(int n)
{
	return 0;
}

int main()
{
	int n = 0;
	cin >> n;
	sin_consistently(n);
	sin_parallel(n);
	return EXIT_SUCCESS;
}