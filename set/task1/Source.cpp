#include<iostream>
#include<set>

using namespace std;

void func_set_of_int()
{
	int x = 0;
	set<int> integer;
	while (cin >> x)
	{
		integer.insert(x);
	}
	cout << "sorted set of integer" << endl;
	for (int x : integer)
	{
		cout << x << " ";
	}
	cout << endl;
}
void func_set_of_reentered_int()
{
	int x = 0;
	set<int> integer;
	set<int> reentered;
	while (cin >> x)
	{
		if (integer.count(x) == 1)
		{
			reentered.insert(x);
		}
		integer.insert(x);
	}
	cout << "set of reentered integer" << endl;
	for (int x : reentered)
	{
		cout << x << " ";
	}
	cout << endl;
}
void func_set_of_double_entered_int()
{
	int x = 0;
	set<int> integer;
	set<int> double_entered;
	set<int> triple_entered;
	while (cin >> x)
	{
		if (integer.count(x) == 1 && double_entered.count(x) == 0)
		{
			double_entered.insert(x);
		}
		if (integer.count(x) == 1 && double_entered.count(x) == 1)
		{
			triple_entered.insert(x);
		}
		integer.insert(x);
	}
	cout << "set of double_entered integer" << endl;
	for (int x : double_entered)
	{
		if (triple_entered.count(x) == 0)
		{
			cout << x << " ";
		}
	}
	cout << endl;
}

template<class T>
set<T> func_union(set<T>& s1, set<T>& s2)
{
	set<T> res;
	for (auto x : s2)
	{
		res.insert(x);
	}
	for (auto x : s1)
	{
		res.insert(x);
	}
	return res;
}
template<class T>
void print(set<T>& s)
{
	for (auto x : s)
	{
		cout << x << " ";
	}
}

int main()
{
	//func_set_of_int();
	//func_set_of_reentered_int();
	func_set_of_double_entered_int();
	/*set<int> s1;
	set<int> s2;
	s1.insert(1);
	s1.insert(2);
	s1.insert(3);
	s2.insert(4);
	s2.insert(5);
	s2.insert(1);
	s2.insert(2);
	s2.insert(9);
	set<int> s = func_union(s1, s2);
	print(s);*/
	return 0;
}