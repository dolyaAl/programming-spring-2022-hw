#include <iostream>
#include <map>

using namespace std;

template<typename T, typename E>
void print(map<T, E> &m)
{
	for (auto x : m)
	{
		cout << x.first << "->" << x.second << endl;
	}
}

void func1()
{
	map<int, int> m;
	int x = 0;
	while (cin >> x)
	{
		m[x] += 1;
	}
	print(m);
}

map<int, int> func2()
{
	map<int, int> m;
	int n = 0;
	int x = 0;
	int y = 0;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> x >> y;
		m[x] = y;
	}
	
	print(m);
	return m;
}

void func3()
{
	map<int, int> m;
	m = func2();
	int x = 0;
	while (cin >> x)
	{
		m.count(x) != 0 ? cout << m[x] << endl : cout << x << endl;
	}
}

template<typename T, typename E>
map<T, E> func4(map<T, E> m1, map<T, E> m2)
{
	map<T, E> res;
	for (auto x : m1)
	{
		res[x.first] = x.second + m2[x.first];
	}
	print(res);
	return res;
}

template<typename T, typename E, typename K>
map<T, K> func5(map<T, E> m1, map<E, K> m2)
{
	map<T, K> res;
	for (auto x : m1)
	{
		res[x.first] = m2[x.second];
	}
	print(res);
	return res;
}

int main()
{	
	map<int, int> s1 = func2();
	map<int, int> s2 = func2();
	func5(s1, s2);
	return 0;
}