#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
#define SAFE_DELETE(p) do{ delete p; p = NULL;} while(0)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class A {
public:
	virtual void print() {
		cout << "i am father" << endl;
	}
private:
	int data1_;
};
class B :public A{
public:
	virtual void print() {
		cout << "i am son" << endl;
	}
private:
	int data2_;
};
using namespace std;
int main() 
{
	int a = 0;
	//A *obj = new B();
	//obj->print();
	//A obj1;
	//B obj2;
	//obj1 = obj2;
	//obj1.print();
	auto p = &a;
	if (NULL != p) SAFE_DELETE(p);
	else {

	}
	std::allocator<
	system("pause");
	return 0;
}