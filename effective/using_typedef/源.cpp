#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
class Widget9 {};

typedef void (*FP1)(int, const std::string&);
using FP2 = void (*)(int, const std::string&);

//别名模板
template<typename T>
using MyAllocList1 = std::list<T/*, MyAlloc<T>*/>; // C++11,  MyAllocList1<T>是std::list<T, MyAlloc<T>>的同义词

template<typename T>
struct MyAllocList2 { // MyAllocList<T>::type 是std::list<T, MyAlloc<T>>的同义词
	typedef std::list<T/*, MyAlloc<T>*/> type;
};

template<typename T>
class Widget9_2 { // Widget9_2<T>含一个MyAllocList2<T>型别的数据成员
private:
	typename MyAllocList2<T>::type list; // MyAllocList2<T>::type代表一个依赖于模板型别形参(T)的型别，所以MyAllocList2<T>::type称为带依赖型别，C++中规则之一就是带依赖型别必须前面加个typename
};

template<typename T>
class Widget9_1 {
private:
	//别名声明可以模板化(这种情况下它们被称为别名模板，alias template)，typedef就不行。
	MyAllocList1<T> list; // 不再有"typename"和"::type"
};

int test_item_9()
{
	typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS1;
	using UPtrMapSS2 = std::unique_ptr<std::unordered_map<std::string, std::string>>; // C++11, alias declaration

	MyAllocList1<Widget9> lw1;
	MyAllocList2<Widget9>::type lw2;
	typedef const char cc;
	std::remove_const<cc>::type a; // char a
	std::remove_const<const char*>::type b; // const char* b

	typedef int&& rval_int;
	typedef std::remove_reference<int>::type A;

	//std::remove_const<T>::type // C++11: const T --> T
	//std::remove_const_t<T>     // C++14中的等价物
	//template<class T>
	//using remove_const_t = typename remove_const<T>::type;

	//std::remove_reference<T>::type // C++11: T&/T&& --> T
	//std::remove_reference_t<T>     // C++14中的等价物
	//template<class T>
	//using remove_reference_t = typename remove_reference<T>::type;

	return 0;
}
int main() {
	return 0;
}