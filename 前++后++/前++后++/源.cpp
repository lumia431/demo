#include <iostream>

using namespace std;
//关于重载前++ 和后++的问题
//这里使用类方法重载
struct T
{
	int a;
	T & operator ++()
	{
		(this->a)++;
		return *this;
	}
	const T operator ++(int)
	{
		const T temp = *this;
		this->a++;
		return temp;
	}
};


ostream& operator <<(ostream &os, const T &t)
{
	os << "a is " << t.a;
	return os;
}
int main()
{
	T t = { 1 };
	//t++返回的是t变化之前的副本，真正的t此时已经改变
	cout << t++ << endl;
	cout << t << endl;
	return 0;
}