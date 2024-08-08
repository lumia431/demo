//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;
//std::shared_ptr<spdlog::logger> m_logger;
int main() {
	//1、const引用可读不可改，与绑定对象是否为const无关；非const引用可读可改，只可与非const对象绑定
	int val = 1024;
	const int& ir = val;
	val++;//我们仍然可以通过val直接改变其值
	ir++;//通过ir来改变val的值，编译时会出错

	const int ival = 1024;
	const int& refVal = ival; // ok: both reference and object are const
	int& ref2 = ival;            // 非const引用只可与非const对象绑定

	//2、非const引用只能绑定到与该引用同类型的对象，const引用则可以绑定到不同但相关的类型的对象或绑定到左值，
	//同时const引用可以初始化为不同类型的对象或者初始化为右值，如字面值常量
	//它的原理是编译器为了实现引用，必须生成一个临时对象，将该对象的值置入临时对象中，
	//引用实际上指向该对象（对该引用的操作就是对该临时对象的操作），但用户不能访问它。
	int i = 42;
	// legal for const references only
	const int& r = 42;//初始化为右值
	const int& r2 = r + i;//同样的初始化对于非const引用却是不合法的，而且会导致编译时错误。
	double dval = 3.14;
	const int& ri = dval;//不同类型对象

	//3.const引用和非const引用在内存中的对比
	//例如const引用：

	const int t = 9;
	const int& k = t;
	cout << &k << endl;//0012FF6C
	cout << &t << endl;//0012FF74

	//例如非const引用：
	int t1 = 9;
	int& k1 = t1;
	cout << &k1 << endl;//0012FF74
	cout << &t1 << endl;//0012FF74
	//原因是const引用引入了一个用户看不到的临时对象
	system("pause");
	return 0;
}