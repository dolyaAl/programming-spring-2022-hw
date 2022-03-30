#include <iostream>
#include <cstdlib>
#include <omp.h>
#include <cmath>
#include <vector>

using namespace std;

/*double pi = acos(-1);
double* sin_c = new double[100000001];
double* sin_p = new double[100000001];
void sin_consistently(int n)
{
	double t = omp_get_wtime();
	for (int i = 0; i <= n; ++i)
	{
		sin_c[i] = sin(pi * i / (2.0 * n));
	}
	cout << "Time cons: " << omp_get_wtime() - t << endl;
}
void sin_parallel_2(int n)
{
	double t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n / 2; i++)
			{
				sin_p[i] = sin(pi * i / (double(2) * n));
			}
		}
#pragma omp section
		{
			for (int i = n / 2; i <= n; i++)
			{
				sin_p[i] = sin(pi * i / (double(2) * n));
			}
		}
	}
	cout << "Time par_2: " << omp_get_wtime() - t << endl;
}
void sin_parallel_4(int n)
{
	double t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n / 4; i++)
			{
				sin_p[i] = sin(pi * i / (double(2) * n));
			}
		}
#pragma omp section
		{
			for (int i = n / 4; i <= n/2; i++)
			{
				sin_p[i] = sin(pi * i / (double(2) * n));
			}
		}
#pragma omp section
		{
			for (int i = n / 2; i <= 3*n/4; i++)
			{
				sin_p[i] = sin(pi * i / (double(2) * n));
			}
		}
#pragma omp section
		{
			for (int i = 3 * n / 4; i <= n; i++)
			{
				sin_p[i] = sin(pi * i / (double(2) * n));
			}
		}
	}
	cout << "Time par_4: " << omp_get_wtime() - t << endl;
}

double f(double x)
{
	return 1 / (1 + x * x);
}
double pi_arctg_cons(int n)
{
	double sum = 0;
	double t = omp_get_wtime();
	for (int i = 1; i <= n; ++i)
	{
		sum += f((double(2) * i - 1) / (double(2) * n));
	}
	cout << "Time cons: " << omp_get_wtime() - t << endl;
	return 4*sum/n;
}
double pi_arctg_par_2(int n)
{
	double sum = 0;
	double t = omp_get_wtime();
#pragma omp parallel sections reduction(+:sum)
	{
#pragma omp section
		{
			for (int i = 1; i < n/2; ++i)
			{
				sum += f((double(2) * i - 1) / (double(2) * n));
			}
		}
#pragma omp section
		{
			for (int i = n/2; i <= n; ++i)
			{
				sum += f((double(2) * i - 1) / (double(2) * n));
			}
		}
	}
	cout << "Time par_2: " << omp_get_wtime() - t << endl;
	return 4 * sum / n;
}
double pi_arctg_par_4(int n)
{
	double sum = 0;
	double t = omp_get_wtime();
#pragma omp parallel sections reduction(+:sum)
	{
#pragma omp section
		{
			for (int i = 0; i < n / 4; i++)
			{
				sum += f((double(2) * i - 1) / (double(2) * n));
			}
		}
#pragma omp section
		{
			for (int i = n / 4; i < n / 2; i++)
			{
				sum += f((double(2) * i - 1) / (double(2) * n));
			}
		}
#pragma omp section
		{
			for (int i = n / 2; i < 3 * n / 4; i++)
			{
				sum += f((double(2) * i - 1) / (double(2) * n));
			}
		}
#pragma omp section
		{
			for (int i = 3 * n / 4; i <= n; i++)
			{
				sum += f((double(2) * i - 1) / (double(2) * n));
			}
		}
	}
	cout << "Time par_4: " << omp_get_wtime() - t << endl;
	return 4 * sum / n;
}*/

bool prime(int n)
{
	if (n == 1)
	{
		return false;
	}
	if (n % 2 == 0)
	{
		return false;
	}
	for (int i = 3; i * i <= n; i += 2)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return true;
}
int prime_count_cons(int n)
{
	double t = omp_get_wtime();
	int count = 0;
	for (int i = 1; i <= n; ++i)
	{
		count += prime(i);
	}
	cout << "Time cons: " << omp_get_wtime() - t << endl;
	return count;
}
int prime_count_par_2(int n)
{
	int count = 0;
	double t = omp_get_wtime();
#pragma omp parallel sections reduction(+:count)
	{
#pragma omp section
		{
			for (int i = 1; i < n; i += 4)
			{
				count += prime(i);
			}
		}
#pragma omp section
		{
			for (int i = 3; i <= n; i += 4)
			{
				count += prime(i);
			}
		}
	}
	cout << "Time par: " << omp_get_wtime() - t << endl;
	return count;
}
int prime_count_par_4(int n)
{
	int count = 0;
	double t = omp_get_wtime();
#pragma omp parallel sections reduction(+:count)
	{
#pragma omp section
		{
			for (int i = 1; i < n; i += 8)
			{
				count += prime(i);
			}
		}
#pragma omp section
		{
			for (int i = 3; i <= n; i += 8)
			{
				count += prime(i);
			}
		}
#pragma omp section
		{
			for (int i = 5; i <= n; i += 8)
			{
				count += prime(i);
			}
		}
#pragma omp section
		{
			for (int i = 7; i <= n; i += 8)
			{
				count += prime(i);
			}
		}
	}
	cout << "Time par: " << omp_get_wtime() - t << endl;
	return count;
}

struct Point
{
	double x;
	double y;
	double z;
	
	Point(double x = 0, double y = 0, double z = 0)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
double sqrt_dist(Point p1, Point p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) +
				(p1.y - p2.y) * (p1.y - p2.y) +
				(p1.z - p2.z) * (p1.z - p2.z);
}
void fill_points(vector<Point> &v)
{
	double x = 0;
	double y = 0;
	double z = 0;
	while (cin >> x)
	{
		cin >> y >> z;
		v.push_back(Point(x, y, z));
	}
}
double diam_cons(vector<Point> v)
{
	double diam = 0;
	double temp = 0;
	double t = omp_get_wtime();
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		for (auto j = i; j != v.end(); ++j)
		{
			temp = sqrt_dist(*i, *j);
			if (temp > diam)
			{
				diam = temp;
			}
		}
	}
	cout << "Time cons: " << omp_get_wtime() - t << endl;
	return sqrt(diam);
}
double diam_par_2(vector<Point> v)
{
	double temp = 0;
	double diam1 = 0;
	double diam2 = 0;
	vector<Point>::iterator k = v.begin();
	k += v.size() / 2;
	double t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (auto i = v.begin(); i != k; i++)
			{
				for (auto j = i; j != v.end(); j++)
				{
					temp = sqrt_dist(*i, *j);
					if (temp > diam1)
					{
						diam1 = temp;
					}
				}
			}
		}
#pragma omp section
		{
			for (auto i = k; i != v.end(); i++)
			{
				for (auto j = i; j != v.end(); j++)
				{
					temp = sqrt_dist(*i, *j);
					if (temp > diam2)
					{
						diam2 = temp;
					}
				}
			}
		}
	}
	cout << "Time par: " << omp_get_wtime() - t << endl;
	if (diam1 > diam2)
	{
		return diam1;
	}
	return diam2;
}
double diam_par_3(vector<Point> v)
{
	double t = omp_get_wtime();
	double diam1 = 0;
	double diam2 = 0;
	double diam3 = 0;
	double temp = 0;
	vector<Point>::iterator k = v.begin();
	k += v.size() / 2;
	
#pragma omp sections
	{
#pragma omp section
		{
			for (auto i = v.begin(); i != k; ++i)
			{
				for (auto j = i; j != k; ++j)
				{
					temp = sqrt_dist(*i, *j);
					if (temp > diam1)
					{
						diam1 = temp;
					}
				}
			}
		}
#pragma omp section
		{
			for (auto i = k; i != v.end(); ++i)
			{
				for (auto j = i; j != v.end(); ++j)
				{
					temp = sqrt_dist(*i, *j);
					if (temp > diam2)
					{
						diam2 = temp;
					}
				}
			}
		}
#pragma omp section
		{
			for (auto i = k; i != v.end(); ++i)
			{
				for (auto j = v.begin(); j != k; ++j)
				{
					temp = sqrt_dist(*i, *j);
					if (temp > diam3)
					{
						diam3 = temp;
					}
				}
			}
		}
	}
	cout << "Time par: " << omp_get_wtime() - t << endl;
	if (diam1 > diam2)
	{
		if (diam1 > diam3)
		{
			return diam1;
		}
	}
	else if (diam2 > diam3)
	{
		return diam2;
	}
	return diam3;
}
double diam_par_4(vector<Point> v)
{
	return 0;
}

bool indexValid(int x, int  y, int n, int k)
{
	return ((x >= 0 && x < n) && (y >= 0 && y < k));
}
int neightbros(int** field, int x, int y, int n, int k)
{
	int sum = 0;
	for (int i = x - 1; i <= x + 1; ++i)
	{
		for (int j = y - 1; j <= y + 1; ++j)
		{
			if(!(i == x && j == y) && indexValid(i, j, n, k))
			{
				sum += field[i][j];
			}
		}
	}
	return sum;
}
bool is_alive(int now, int neightbros)
{
	if (now == 1)
	{
		return neightbros < 2 ? false : neightbros > 3? false: true;
	}
	else
	{
		return neightbros == 3 ? true : false;
	}
}
void print(int** field, int n, int k)
{
	for (int j = 0; j < k; ++j)
	{
		for (int i = 0; i < n; ++i)
		{
			cout << field[i][j];
		}
		cout << endl;
	}
}
int** game_life_posl(int** field, int n, int k)
{
	int** new_gen = new int* [n];
	for (int i = 0; i < n; ++i)
	{
		new_gen[i] = new int[k] {0};
	}
	double t = omp_get_wtime();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			new_gen[i][j] = is_alive(field[i][j], neightbros(field, i, j, n, k));
		}
	}
	cout << "Time posl: " << omp_get_wtime() - t << endl;
	return new_gen;
}
int** game_life_par_2(int** field, int n, int k)
{
	int** new_gen = new int* [n];
	for (int i = 0; i < n; ++i)
	{
		new_gen[i] = new int[k] {0};
	}
	double t = omp_get_wtime();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n/2; ++i)
			{
				for (int j = 0; j < k; ++j)
				{
					new_gen[i][j] = is_alive(field[i][j], neightbros(field, i, j, n, k));
				}
			}
		}
#pragma omp section
		{
			for (int i = n/2; i < n; ++i)
			{
				for (int j = 0; j < k; ++j)
				{
					new_gen[i][j] = is_alive(field[i][j], neightbros(field, i, j, n, k));
				}
			}
		}
	}
	cout << "Time par_2: " << omp_get_wtime() - t << endl;
	return new_gen;
}

int main()
{
	//int n = 0;
	//cin >> n;

	//sin_consistently(n);
	//sin_parallel_2(n);
	//sin_parallel_4(n);

	//cout << pi_arctg_cons(n) << endl;
	//cout << pi_arctg_par_2(n) << endl;
	//cout << pi_arctg_par_4(n) << endl;

	//cout << prime_count_cons(n) << endl;
	//cout << prime_count_par_2(n) << endl;
	//cout << prime_count_par_4(n) << endl;

	//vector<Point> v;
	//fill_points(v);
	//cout << diam_cons(v) << endl;
	//cout << diam_par_2(v) << endl;
	//cout << diam_par_3(v) << endl;

	int n = 0;
	int k = 0;
	cin >> n >> k;
	int** field_1 = new int* [n];
	int** field_2;
	int** field_3;
	for (int i = 0; i < n; ++i)
	{
		field_1[i] = new int[k] {0};
	}
	//for (int j = 0; j < k; ++j)
	//{
	//	for (int i = 0; i < n; ++i)
	//	{
	//		cin >> field_1[i][j];
	//	}
	//}
	field_2 = game_life_posl(field_1, n, k);
	field_3 = game_life_par_2(field_1, n, k);
	//print(field_2, n, k);
	for (int i = 0; i < n; ++i)
	{
		delete[] field_1[i];
		delete[] field_2[i];
		delete[] field_3[i];
	}
	delete[] field_1;
	delete[] field_2;
	delete[] field_3;
	return EXIT_SUCCESS;
}






