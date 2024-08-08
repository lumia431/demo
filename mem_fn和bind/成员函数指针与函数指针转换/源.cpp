#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;
int fun(int &a)
{
	cout << a << endl;
	return a;
}
class test {
public:
	test(int i) {
		run2();
	}
	void run(function<int(int &)>f)
	{
		int b = 1;
		f(b);
		/*memcpy_s(&f,sizeof(f), &cf, sizeof(fun));*/
		//auto a = std::bind(&print, this);
		//fun f = a;
		//f();    //³É¹¦
		//f = reinterpret_cast<void(*)()>(test::print);
		//auto n = m;
	}
	int run2()
	{
		std::cout << "haha" << std::endl;
		return 0;
	}
	int m = 1;
};

int main()
{
	//auto a = bind(fun,std::placeholders::_1);
	//int b = 1;
	//test t;
	//t.run(a);
	//vector<test*> v;
	//v.resize(2);
	//std::for_each(v.begin(), v.end(), std::mem_fun(&test::run2));
	test t{1};
	auto f1 = std::mem_fn(&test::run2);
	auto f2 = std::bind(&test::run2,t);
	f1(t);
	f2();
	system("pause");
	return 0;
}
