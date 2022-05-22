#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<future>
#include<random>
#include<queue>
#include<condition_variable>

using namespace std;

queue<int> object;
bool work1 = true;
bool work2 = true;
vector<int> v1, v2;
// v1 -- производство, v2 Ц потребление

mt19937 mt;
uniform_int_distribution<int> r(0, 100'000);

mutex m;
condition_variable cv;

bool flag()
{
	return !object.empty();
}

void factory()
{
	int object_i = 0;
	while (work1)
	{
		if (flag())
		{
			this_thread::sleep_for(100ms);
		}
		else
		{
			object_i = r(mt);
			object.push(object_i);
			v1.push_back(object_i);
		}
	}
}
void consumer()
{
	while (work2)
	{
		if (!flag())
		{
			this_thread::sleep_for(100ms);
		}
		else
		{
			v2.push_back(object.front());
			object.pop();
		}
	}
}
void check_all()
{
	thread fact_1(factory);
	thread fact_2(factory);

	thread cons_1(consumer);
	thread cons_2(consumer);
	thread cons_3(consumer);

	this_thread::sleep_for(1s);

	work1 = false;

	fact_1.join();
	fact_2.join();

	work2 = false;

	cons_1.join();
	cons_2.join();
	cons_3.join();

	for (auto x : v1)
	{
		cout << x << " ";
	}
	cout << endl;
	for (auto x : v2)
	{
		cout << x << " ";
	}
	cout << endl;
}

void factory_m()
{
	int object_i = 0;
	while (work1)
	{
		m.lock();
		if (flag())
		{
			m.unlock();
			this_thread::sleep_for(100ms);
		}
		else
		{
			object_i = r(mt);
			object.push(object_i);
			v1.push_back(object_i);
			m.unlock();
		}
	}
}
void consumer_m()
{
	while (work2)
	{
		m.lock();
		if (!flag())
		{
			m.unlock();
			this_thread::sleep_for(100ms);
		}
		else
		{
			v2.push_back(object.front());
			object.pop();
			m.unlock();
		}
	}
}
void check_all_m()
{
	thread fact_1(factory_m);
	thread fact_2(factory_m);

	thread cons_1(consumer_m);
	thread cons_2(consumer_m);
	thread cons_3(consumer_m);

	this_thread::sleep_for(1s);

	work1 = false;

	fact_1.join();
	fact_2.join();

	work2 = false;

	cons_1.join();
	cons_2.join();
	cons_3.join();

	for (auto x : v1)
	{
		cout << x << " ";
	}
	cout << endl;
	for (auto x : v2)
	{
		cout << x << " ";
	}
	cout << endl;
}

void factory_cv()
{
	int object_i = 0;
	while (work1)
	{
		if (flag())
		{
			m.unlock();
			this_thread::sleep_for(100ms);
		}
		else
		{
			object_i = r(mt);
			object.push(object_i);
			v1.push_back(object_i);
			cv.notify_one();
		}
	}
}
void consumer_cv()
{
	while (work2)
	{
		unique_lock<mutex> l(m);
		cv.wait(l, flag);
		if (!flag())
		{
			this_thread::sleep_for(100ms);
		}
		else
		{
			v2.push_back(object.front());
			object.pop();
		}
	}
}
void check_all_cv()
{
	thread fact_1(factory_m);
	thread fact_2(factory_m);

	thread cons_1(consumer_m);
	thread cons_2(consumer_m);
	thread cons_3(consumer_m);

	this_thread::sleep_for(1s);

	work1 = false;

	fact_1.join();
	fact_2.join();

	work2 = false;

	cons_1.join();
	cons_2.join();
	cons_3.join();

	for (auto x : v1)
	{
		cout << x << " ";
	}
	cout << endl;
	for (auto x : v2)
	{
		cout << x << " ";
	}
	cout << endl;
}

int main()
{
	//check_all();
	//check_all_m();
	check_all_cv();

	return 0;
}