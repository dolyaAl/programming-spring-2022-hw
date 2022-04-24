#include<iostream>
#include<future>
#include<string>

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

double divide_17(string number, int threads)
{
	int res = 0;
	int temp_i = 0;
	string temp_s = "";
	int counter = 0;
	int cur_index = 0;
	while (cur_index < number.length())
	{
		counter = 0;
		while (temp_i < 17)
		{
			temp_s += number[cur_index + counter];
			temp_i = atoi(temp_s.c_str());
			counter++;
		}
		cur_index += counter;
		temp_i %= 17;
		temp_s = to_string(temp_i);
	}
	return temp_i;
}

int main()
{	
	/*future<double> f1 = async(pi_arctg, 10000000, 1, 10000000 / 2);
	future<double> f2 = async(pi_arctg, 10000000, 10000000 / 2 + 1, 10000000);
	cout << 4 * (f1.get() + f2.get());*/
	string number = "100";
	for (int i = 0; i < 17; ++i)
	{
		cout << number << " % 17 =";
		cout << divide_17(number, 1) << endl;
		number.push_back('0');
	}

	return 0;
}