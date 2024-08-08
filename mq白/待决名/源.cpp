#include<iostream>

template<class T>
struct X {
	void f(){}
};

template<class T>
struct Y :X<T>
{
	void t() {
		//如果不加this，它就是非待决名
		//它的绑定在这个模板定义这里就确定
		//待决名的名字查找是在实例化之后开始的
		this->f();
;	}
};

template<class T>
struct U {
	//using type = const T::value;//加入typename表示这是一个类型，不是某个变量，如果不加typename，造成歧义
	using type = typename const T::value;//加入typename表示这是一个类型，不是某个变量，如果不加typename，造成歧义
};

struct O {
	using value = int;
};

int main() {
	Y<int> y;
	y.t();
	U<O>::type a = 0;
}