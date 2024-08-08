#define For(n) for(int index=0;index<n;++index)
#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <windows.h>
using namespace std;
int a = 0;
//void f(int *a)
//{
//	int index = 0;
//	while (true)
//	{
//		*a = index;
//		index++;
//		Sleep(100);
//	}
//}
void f(int &a)
{
	int index = 0;
	while (true)
	{
		cout << a << endl;
		Sleep(1000);
	}
}
void Test()
{
	int &b = a;
	//std::thread th = std::thread([b]() {
	//	while (1)
	//	{
	//		b++;
	//		cout << b << endl;
	//		Sleep(1000);
	//	}
	//	});
	//th.detach();
	std::thread th = std::thread([&b]() {
		while (1)
		{
			cout << b << endl;
			Sleep(1000);
		}
		});
	th.detach();
}
class MyClass
{
public:
	MyClass(int data);
	~MyClass();
	void Run();
private:
	int m_data;
	thread m_thr;
};

MyClass::MyClass(int data):m_data(data)
{
}

MyClass::~MyClass()
{
}
void MyClass::Run()
{
	auto thr = thread([this]() {
		while (1)
		{
			cout << m_data << endl;
			Sleep(30000);
		}
		});
	thr.detach();
}
void Mythread()
{
	//auto m = new MyClass(1);
	//m->Run();
	MyClass m(1);
	m.Run();
}

void Thr1()
{
	int index = 0;
	while (index++ < 10)
	{
		//cout << "1" << endl;
		Sleep(1000);
	}
}

void Thr2()
{
	while (true)
	{
		cout << "2" << endl;
		Sleep(1000);
	}
}

int main()
{
	//int a = 0;
	//int *b = &a;
	//thread thr(f,b);
	//thr.detach();
	//while (1)
	//{
	//	cout << *b << endl;
	//	Sleep(1000);
	//}
	//int a = 0;
	//thread thr(f,ref(a));//对于传引用的函数，这一步行不通，要换成ref()
	//thr.detach();
	//while (1)
	//{
	//	a++;
	//	Sleep(1000);
	//}
	//thread thr(Mythread);
	//thr.detach();
	//For(100)
	//{
	//	if (index == 20)
	//	{

	//	}
	//	Sleep(1000);
	//}
	//mutex m;
	//vector<int>v{ 1,2 };
	//For(2)
	//{
	//	thread t([&]() {
	//		int a = index;
	//		while (true)
	//		{

	//			m.lock();
	//			cout << v[a] << endl;
	//			m.unlock();
	//			Sleep(1000);
	//		}
	//	});
	//	t.detach();
	//}
	//while (true)
	//{

	//}
	thread th1(Thr1);
	th1.detach();
	//Sleep(3000);
	//thread th2(Thr2);
	while (true)
	{
		cout << "thr " << th1.joinable() << endl;
		Sleep(1000);
	}
	//th2.join();
	return 0;
}