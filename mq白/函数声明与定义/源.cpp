//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<thread>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;
//std::shared_ptr<spdlog::logger> m_logger;

void f(int, int, int = 10);//默认参数顺序错误也会报错
void f(int, int = 8, int);
void f(int a = 6, int b, int c){
	cout << a << '\t' << b << '\t' << c << '\n';
}

void f2(int a, ...);//变长实参
void f2(int, int, int = 10);
void f2(int, int = 8, int);
void f2(int a = 6, int b, int c) {
	cout << a << '\t' << b << '\t' << c << '\n';
}

//返回值为int的函数指针
void f3(int(void));
void f3(int()) {

}

void f4(int(*)/*函数声明的形参符号随便写，写*也好，写ABCD也好都表示同一个函数*/(int, int));
void f4(int(lumia)(int, int)) {
	cout << lumia(1, 2) << endl;
}

//丢弃顶层限定符，还是表示同一个函数
//如果丢弃底层限定符，则不是
//void f5(const int*);//报错有多个重载
void f5(int* const);
void f5(int* volatile);
void f5(int* n) {
	cout << n << endl;
}

//如果类型是“T 的数组”或“T 的未知边界数组”，那么它会被替换成类型“指向 T 的指针”
//以下声明指代的都是同一个函数
void f6(int[]);
void f6(int*);
void f6(int* const);
void f6(int[10]);
void f6(int* p) {
	cout << p << endl;
}

struct F
{
	auto operator()(){

	}
};

int main() {
	f();
	f2();
	f3([] {return 6; });
	f4([](int a, int b) {return a + b; });
	f5(nullptr);
	f6(nullptr);
	cout << boolalpha << is_same_v<void(int* const), void(int[10])> << endl;
	//thread t(F());//此时括号中的F()会被当成返回值为F的函数指针
	thread t{ F() };//用{}消除歧义
	system("pause");
	return 0;
}