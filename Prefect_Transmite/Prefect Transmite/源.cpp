#pragma message( "Compiling " __FILE__ )         //显示被编译的文件
#pragma message( "Last modified on " __TIMESTAMP__ )     //文件最后一次修改的日期和时间 
#pragma warning( push, 4 )
#define For(n) for(int index=0;index<n;++index)
//#include "vld.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <set>
#include <array>
using namespace std;
// 比较接近C++11中std::move的示例实现,它不完全符合标准的所有细节
template<typename T> // in namespace std
typename std::remove_reference<T>::type&& move(T&& param)
{
	using ReturnType = typename std::remove_reference<T>::type&&; // 别名声明
	return static_cast<ReturnType>(param);
}

// C++14中比较接近的std::move示例实现
template<typename T> // C++14, still in namespace std
decltype(auto) move(T&& param)
{
	using ReturnType = std::remove_reference_t<T>&&;
	return static_cast<ReturnType>(param);
}

class Widget23 {};

void process(const Widget23& lvalArg) { fprintf(stderr, "process lvalues\n"); } // process lvalues
void process(Widget23&& rvalArg) { fprintf(stderr, "process rvalues\n"); } // process rvalues

template<typename T>
void logAndProcess(T&& param) // template that passes param to process
{
	process(std::forward<T>(param));
}

int test_item_23()
{
	Widget23 w;
	logAndProcess(w); // call with lvalue
	logAndProcess(std::move(w)); // call with rvalue

	return 0;
}
std::multiset<std::string> names; // global data structure

//void logAndAdd(const std::string& name) // 第一种实现方法
template<typename T>
void logAndAdd(T&& name) // universal reference，第二种实现方法
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point\n");
	names.emplace(name);
	//names.emplace(std::forward<T>(name));
}

std::string nameFromIdx(int idx) // 返回索引对应的名字
{
	return std::string("xxx");
}

void logAndAdd(int idx) // 新的重载函数
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point2\n");
	names.emplace(nameFromIdx(idx));
}

int test_item_26()
{
	std::string petName("Darla");

	logAndAdd(petName); // as before, copy lvalue into multiset
	logAndAdd(std::string("Persephone")); // move rvalue instead of copying it
	logAndAdd("Patty Dog"); // create std::string in multiset instead of copying a temporary std::string

	logAndAdd(22); // 调用形参型别为int的重载版本

	short nameIdx = 100;
	//logAndAdd(nameIdx); // error c2664, 形参型别为T&&的版本可以将T推导为short, 对于short型别的实参来说，万能引用产生了比int更好的匹配

	return 0;
}
std::multiset<std::string> names27; // global data structure
std::string nameFromIdx27(int idx) { return std::string("xxx"); }

template<typename T>
void logAndAddImpl(T&& name, std::false_type) // 非整型实参
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point: no int\n");
	names27.emplace(std::forward<T>(name));
}

void logAndAddImpl(int idx, std::true_type) // 整型实参
{
	auto now = std::chrono::system_clock::now();
	fprintf(stdout, "time point: int\n");
	names.emplace(nameFromIdx(idx));
}

template<typename T>
void logAndAdd27(T&& name) // name to data structure
{
	logAndAddImpl(std::forward<T>(name), std::is_integral<typename std::remove_reference<T>::type>());
}

class Person {
public:
	//template<typename T, typename = typename std::enable_if<!std::is_same<Person, typename std::decay<T>::type>::value>::type>
	//template<typename T, typename = typename std::enable_if<!std::is_base_of<Person, typename std::decay<T>::type>::value>::type> // 可使继承自Person的类，当调用基类的构造函数时走的是基类的拷贝或移动构造函数
	//template<typename T, typename = std::enable_if_t<!std::is_base_of<Person, std::decay_t<T>>::value>> // C++14
	template<typename T, typename = std::enable_if_t<!std::is_base_of<Person, std::decay_t<T>>::value &&
		!std::is_integral<std::remove_reference_t<T>>::value>> // C++14
		explicit Person(T&& n) // 只有指定的条件满足了才会启用此模板, constructor for string and args convertible to string
		: name(std::forward<T>(n))
	{
		// assert that a std::string can be created from a T object
		static_assert(std::is_constructible<std::string, T>::value, "Parameter n can't be used to construct a std::string");
	}

	explicit Person(int idx) // constructor for integral args
		: name(nameFromIdx27(idx)) {}

private:
	std::string name;
};
class MyClass
{
public:
	MyClass(string &str);
private:
	string m_str;

};

int test_item_27()
{
	// 注意：test_item_26()与test_item_27()实现的差异
	std::string petName("Darla");
	Person p2(petName);
	logAndAdd27(petName);
	logAndAdd27(std::string("Persephone"));
	logAndAdd27("Patty Dog");

	logAndAdd27(22);

	short nameIdx = 100;
	logAndAdd27(nameIdx);

	return 0;
}
int main()
{
	//test_item_23();
	/*test_item_27();*/
	std::vector<int> aw1(10000,1);
	// ... // put data into aw1
	// move aw1 into aw2. runs in linear time. all elements in aw1 are moved into aw2
	auto aw2 =(aw1);

	system("pause");
	return 0;
}

MyClass::MyClass(string & str)
{
	m_str = str;
}
