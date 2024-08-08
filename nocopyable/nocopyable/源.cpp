#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include"nocopyable.h"
using namespace std;

class A:public noncopyable {
public:
	A() { data_ = 0; }
	A(int a) {
		data_ = a;
	}
	A(A& a) {
		data_ = a.data_;
	}

private:
	int data_;
};


class Base:noncopyable {
public:
	Base() { cout << "Base Default Constructor" << endl; }
	Base(const Base&) { cout << "Base Copy Constructor" << endl; }
};
class Drived : public Base {
public:
	Drived() { cout << "Drived Default Constructor" << endl; }
	Drived(const Drived& d) {
		cout << "Drived Copy Constructor" << endl;
	}
};


int main() {
	A a(3);
	a.set(2);
	A b = a;//执行派生类的拷贝构造和拷贝赋值之前，要调用基类的拷贝构造和拷贝赋值
	//而由于基类的拷贝构造和拷贝赋值被delete掉了，所以编译失败

	//但此时派生类还可以自定义拷贝构造，因为如果派生类没有自定义拷贝构造，派生类执行拷贝构造之前，会执行基类的默认
	//拷贝构造；如果派生类自定义拷贝构造，派生类执行拷贝构造之前，会执行基类的默认构造，不是拷贝构造。
	Drived d1;
	Drived d2(d1);
	system("pause");
	return 0;
}