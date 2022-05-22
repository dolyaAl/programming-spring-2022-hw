#include<iostream>
#include<future>
#include<string>
#include<map>
#include<vector>

using namespace std;

double f(double x)
{
	return 1 / (1 + x * x);
}
double pi_arctg(int n, int a, int b)
{
	double sum = 0;
	for (int i = a; i <= b; ++i)
	{
		sum += f((2.0 * i - 1) / (2.0 * n));
	}
	return sum/n;
}

void fill_string(string& s)
{
	int a = rand() % 9 + 1;
	s.push_back(a + '0');
	for (int i = 0; i < 9999; ++i)
	{
		s.push_back(rand() % 10 + '0');
	}
	
}
int divide_17_posl(string s, int a, int b)
{
	map<int, int> dict = { {0,15},{1,14},{2,4},{3,6},{4,9},{5,5},{6,16},{7,7},{8,2},{9,3},{10,13},{11,11},{12,8},{13,12},{14,1},{15,10} };
	int i = a;
	int num = 0;
	long long sum = 0;
	while (i < b)
	{
		num = s[i] - '0';
		sum += num*dict[(s.size() - 3 - i) % 16];
		++i;
	}
	return sum%17;
}
int divide_17_par(string s, int threads)
{
	vector<future<int>> funct(threads);
	int step = s.size() / threads;
	int a = 0;
	int b = 0;
	int i = 0;
	while (i < threads - 1)
	{
		b = a + step;
		funct[i] = async(divide_17_posl, s, a, b);
		a += step;
		++i;
	}
	funct[i] = async(divide_17_posl, s, a, s.size());
	++i;

	int sum = 0;
	for (int j = 0; j < i; ++j)
	{
		sum += funct[j].get();
	}

	return sum%17;
}

int main()
{	
	future<double> f1 = async(pi_arctg, 10000000, 1, 10000000 / 2);
	future<double> f2 = async(pi_arctg, 10000000, 10000000 / 2 + 1, 10000000);
	cout << 4 * (f1.get() + f2.get());
	string s;
	fill_string(s);
	cout << (divide_17_posl(s, 0, s.size() / 2) + divide_17_posl(s, s.size() / 2, s.size())) % 17 << endl;
	cout << divide_17_posl(s, 0, s.size()) << endl;
	cout << divide_17_par(s, 3) << endl;



	return 0;
}