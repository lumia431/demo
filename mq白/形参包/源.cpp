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

void h(int* a, double* b,const char** c) {
	cout << *a << endl;
	cout << *b << endl;
	cout << *c << endl;
}

template<class ...Us> void f(Us... args) {
	cout << sizeof...(args) << endl;
	h(args...);
	return;
}
template<class ...Ts> void g(Ts... args) {
	f(&args...); // “&args...” 是包展开
	// “&args” 是其模式
}
int main() {
	g(1, 0.2, "a");
	system("pause");
	return 0;
}