
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

int f() {
	return 6;
}

void f2(int&&) {

}

void f3(const int&) {

}

int main() {
	//右值引用的作用是将一个右值，将右值直接转换为左值，在C++里，通常产生了右值以后，必须将右值拷贝到一个左值才能保存
	//，但这个拷贝如果是面对大型容器多次拷贝，会产生大量的资源损耗，而直接将右值转换为左值，则节省这些损耗，
	//此时，将右值转换为左值的操作成为移动构造
	int&& p = f();//值类别是表达式的分类，f()这个表达式值类别是右值，所以我们可以创建一个右值引用绑定到该右值上
	int p = f();
	//int& p = f();//error，非常量（左值）引用的初始值必须为左值，不能用一个左值引用绑定一个右值
	const int& p2 = f();//常量左值引用可以接收右值（纯右值、亡值）

	//decltype会根据表达式的值类别推导不同的类型
	//a) 如果 表达式 的值类别是亡值，将会 decltype 产生 T&&；
	//b) 如果 表达式 的值类别是左值，将会 decltype 产生 T& ；
	//c) 如果 表达式 的值类别是纯右值，将会 decltype 产生 T。
	using T = decltype((42));//此处推导42为int（T）,即纯右值
	using T2 = decltype((f())); //此处推导42为int（T），纯右值
	int a = 0;
	using T3 = decltype((a));//此处推导a为int&（T&），左值
	using T4 = decltype((int&&)(a));//此处推导a为int&&（T&&），亡值
	using T5 = decltype(std::move(a));//此处推导a为int&&（T&&），亡值
	//f2(a);//无法将右值引用绑定到左值
	//f2(p);//无法将右值引用绑定到左值

	f3(a);
	f3(p);
	f3(6);
	f3(std::move(a));

	system("pause");
	return 0;
}