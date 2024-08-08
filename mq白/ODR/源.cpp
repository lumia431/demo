#include <iostream>
using namespace std;
#include <string>
class A
{
public:
	A(int a) :m_A(a) {}
	int m_A;
	static const int m_B = 1;
	static void show()
	{
		cout << "静态成员函数show的调用m_B=" << m_B << endl;//静态成员函数访问静态成员变量
	}
	static void fun()
	{
		cout << "静态成员函数fun的调用" << endl;
		show();//静态成员函数调用静态成员函数
	}
};

const int& f(const int& r)
{
	return r;
}

//int Person::m_B = 10;//类外分配空间，在全局区
int main()
{
	int n = 1 ? (1, A::m_B) // S::x 在此处未被 ODR 使用
		: 0;  // S::x 在此处被 ODR 使用：需要一个定义
	//静态变量，是在编译阶段就分配空间，对象还没有创建时，就已经分配空间。
	//静态成员变量必须在类中声明，在类外定义。
	//静态数据成员不属于某个对象，在为对象分配空间中不包括静态成员所占空间。
	return 0;
}
