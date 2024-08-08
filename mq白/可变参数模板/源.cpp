#include<iostream>
using namespace std;
//一定要有一个空f作为递归调用的出口，严格意义上这不叫作递归
//因为递归是自己调用自己，模板递归每次的参数都不一样，不能算作同一个函数
//模板一定要实例化成具体的函数才有用
void f()
{
}


template<typename T, typename ... Args>
void f(T t, Args... args)
{
	cout << t << endl;
	//编译器if可以避免空f
	//if constexpr (sizeof...(args)) 
	f(args...);
}


/* First instantiated from: insights.cpp:16 */
//编译器会根据实例化生成不同的版本
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<int, const char*, int>(int t, const char* __args1, int __args2)
{
	std::cout.operator<<(t).operator<<(std::endl);
	f(__args1, __args2);
}
#endif


/* First instantiated from: insights.cpp:11 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<const char*, int>(const char* t, int __args1)
{
	std::operator<<(std::cout, t).operator<<(std::endl);
	f(__args1);
}
#endif


/* First instantiated from: insights.cpp:11 */
#ifdef INSIGHTS_USE_TEMPLATE
template<>
void f<int>(int t)
{
	std::cout.operator<<(t).operator<<(std::endl);
	f();
}
#endif
;


int main()
{
	f(1, "2", 3);
	int a = 0;
	int&& a1 = a++;
	system("pause");
	return 0;
}
