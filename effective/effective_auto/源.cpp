#include<iostream>
#include<array>
using namespace std;
//template<typename T>
//void f(ParamType param);

template<typename T>
void f(T& param) {} // param是个引用

template<typename T>
void f2(T* param) {} // param现在是个指针

template<typename T>
void f3(T&& param) {} // param现在是个万能引用

template<typename T>
void f4(T param) {} // param现在是按值传递

void test(int a) {
	cout << a << endl;
}

// 以编译期常量形式返回数组尺寸(该数组形参未起名字，因为我们只关系其含有的元素个数)
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept // 将该函数声明为constexpr，能够使得其返回值在编译期就可用。从而就可以在
{						   // 声明一个数组时，指定其尺寸和另一数组相同，而后者的尺寸则从花括号初始化式(braced initializer)计算得出
	return N;
}

void someFunc(int, double) {} // someFunc是个函数，其型别为void(int, double)

int test_item_1()
{
	//f(expr); // 已某表达式调用f
	//编译器通过实参推导模板参数类型和函数参数类型
	// 在编译期，编译器会通过expr推导两个型别：一个是T的型别，另一个是ParamType的型别，这两个型别往往不一样

	int x = 27; // x的型别是int
	const int cx = x; // cx的型别是const int
	const int& rx = x; // rx是x的型别为const int的引用

	f(x); // T的型别是int, param的型别是int&
	f(cx); // T的型别是const int, param的型别是const int&
	f(rx); // T的型别是const int, param的型别是const int&, 
	//注意：即使rx具有引用型别，T也并未被推导成一个引用，原因在于，rx的引用性(reference-ness)会在型别推导过程中被忽略

	const int* px = &x; // px is ptr to x as a const int
	f2(&x); // T is int, param's type is int*
	f2(px); // T is const int, param's type is const int*

	f3(x); // x is lvalue, so T is int&, param's type is also int&
	f3(cx); // cx is lvalue, so T is const int&, param's type is also const int&
	f3(rx); // rx is lvalue, so T is const int&, param's type is also const int&
	f3(27); // 27 is rvalue, so T is int, param's type is therefore int&&

	// param是个完全独立于cx和rx存在的对象----是cx和rx的一个副本
	f4(x); // T's and param's types are both int
	f4(cx); // T's and param's types are again both int
	f4(rx); // T's and param's types are still both int

	const char* const ptr = "Fun with pointers"; // ptr is const pointer to const object
	f4(ptr); // pass arg of type const char* const

	const char name[] = "J. P. Briggs"; // name's type is const char[13]
	const char* ptrToName = name; // array decays to pointer

	f4(name); // name is array, but T deduced as const char*
	f(name); // pass array to f, T的型别推导结果是const char[13], 而f的形参(该数组的一个引用)型别则被推导为const char (&)[13]

	int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
	fprintf(stdout, "array length: %d\n", arraySize(keyVals)); // 7
	int mappedVals[arraySize(keyVals)]; // mappedVals被指定与之相同
	std::array<int, arraySize(keyVals)> mappedVals2; // mappedVals2也指定为7个元素

	f4(someFunc); // param被推导为函数指针(ptr-to-func)，具体型别是void (*)(int, double)
	f(someFunc); // param被推导为函数引用(ref-to-func), 具体型别是void (&)(int, double)

	return 0;
}

int main() {
	int a = 1;
	const int& b = a;
	test(b);//此处引用性(reference-ness)被忽略
	test_item_1();
	return 0;
}