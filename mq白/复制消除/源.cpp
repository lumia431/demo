#include<iostream>
using namespace std;
class A {
public:
    A() {
        cout << "constructor" << endl;
    }

    A(const A& rhs) {
        cout << "copy constructor" << endl;
    }

    A(A&& rhs) {
        cout << "move constructor" << endl;
    }

    A& operator=(const A& rhs) {
        cout << "copy assignment operator" << endl;
        return *this;
    }

    A& operator=(A&& rhs) {
        cout << "move assignment operator" << endl;
        return *this;
    }

    ~A() {
        cout << "destructor" << endl;
    }
};

A f1() {
	return A();
}

A f2() {
    A a;
    return a;
}
//查阅 cppreference 得知，C++ 中存在 复制消除 的特性：
//在满足以下任一条件时，编译器将省略类对象的复制和移动构造，导致零复制的按值传递语义：
//在 return 语句中，当操作数是一个与函数返回类型相同的类类型的纯右值时
//在对象的初始化中，当初始化器表达式是一个与变量类型相同的类类型的纯右值时
int main() {
	std::cout << "Hello World!\n";
	//A obj = f1();复制消除，只调用一次默认构造，一次析构
	A obj = f2();//默认构造、移动构造、两次析构
    //A a = A(A()); //复制消除，只调用一次默认构造，一次析构
}