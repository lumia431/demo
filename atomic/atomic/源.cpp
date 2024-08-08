#define For(n) for(int index = 0 ; index < n; ++index)
#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>
int t = 0;
std::atomic<int> at = 0;

std::atomic_flag lock = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_numer(int x)
{
	//test_and_set, 如果atomic_flag对象被设置，则返回true; 如果atomic_flag对象未被设置，则设置之，返回false
	//clear.清楚atomic_flag对象
	while (lock.test_and_set())
	{
		stream << "thread#" << x << "";
		lock.clear();
	}
}

void thread1()
{
	For(1000000)
	{
		at.store(at.load(std::memory_order::memory_order_acq_rel) + 1);
	}
}

void thread2()
{
	For(1000000)
	{
		at.store(at.load(std::memory_order::memory_order_acq_rel) + 1);
	}
}

int main()
{
	std::vector<int>v{ 1,2,3,4,5 };
	v.reserve(10);
	std::cout << v.capacity() << std::endl;
	std::vector<int>(v).swap(v);
	std::cout << v.capacity() << std::endl;
	//std::thread t1(thread1);
	//std::thread t2(thread2);
	//t1.join();
	//t2.join();
	//std::cout << at << std::endl;
	//std::vector<std::thread> ths;
	//for (int i = 0; i < 10; i++)
	//	ths.push_back(std::thread(append_numer, i));
	//for (int i = 0; i < 10; i++)
	//	ths[i].join();
	//std::cout << stream.str();
	return 0;
}