#include<iostream>
#include<string>
#include<vector>
#include <map>
#include <thread>
#include <functional>

using namespace std;

struct MyStruct
{
	typedef int Int;
	int valu = 1;
};

float Test(int i)
{
	return 1;
}
template <class T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type foo(T t)
{
	static_assert(0, "abv");
	return t;
}
template <class T>
typename T::Int foo1(T t)
{
	return t.value;
}
template <typename T, typename Enable = void>
struct check;

template <typename T>
struct check<T, typename std::enable_if<T::value>::type> {
	static constexpr bool value = T::value;
};

template <class T>
int foo2(T t)
{
	if constexpr (is_integral<T>::value)
	{
		return t;
	}
	else
	{
		cout << typeid(T).name() << endl;
		return 0;
	}
}
//获取最大的整数
template <size_t arg, size_t... rest>
struct IntegerMax;

template <size_t arg>
struct IntegerMax<arg> : std::integral_constant<size_t, arg>
{
};

template <size_t arg1, size_t arg2, size_t... rest>
struct IntegerMax<arg1, arg2, rest...> : std::integral_constant<size_t, arg1 >= arg2 ? IntegerMax<arg1, rest...>::value :
	IntegerMax<arg2, rest...>::value >
{
};

class Plus
{
public:
	int plus(int a, int b)
	{
		return a + b;
	}
};

template<typename R, typename A0, typename T>
class function<R(T::*)(A0) >
{
public:
	typedef R(T::*fun)(A0);
	function(fun p, T* pthis) :m_ptr(p), m_pThis(pthis) {}

	R operator()(A0 a) { (m_pThis->*m_ptr)(a); }
	fun m_ptr;
	T* m_pThis;
};
class CA
{
public:
	void Fun(int a) { cout << a; }
};

void SplitString(const std::string& s, std::vector<std::string> &v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;

	while (std::string::npos != pos2)
	{
		auto it = v.end();
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}
int main()
{
	//thread t1(b);
	//thread t2(test);
	//t1.detach();
	//t2.detach();
	//extern int t;
	//thread t1([]() {
	//	while (true)
	//	{
	//		t += 1;
	//		Sleep(1000);
	//	}
	//	});
	//t1.detach();
	//extern void test();
	//test();
	//while (1);
	//A a;
	//B b;
	//thread t1(&A::testA,a);
	//thread t2(&B::testB,b);
	//t1.detach();
	//t2.detach();
	//auto f6 = foo<int>(1);
	const int abc = 100;
	char arr[abc];
	MyStruct m;
	auto a1 = foo1<MyStruct>(m);
	check<MyStruct>c();
	constexpr auto flag = true;
	//typedef conditional<flag, A, B>::type Ty;//三目运算，正确取前者，反之取后者
	//Ty a;
	typedef std::decay<float(int)>::type F;
	F f1 = *Test;
	//auto i = f(1);
	//auto a1 = foo("y");
	auto a2 = foo2("tr");
	typedef std::integral_constant<int, 1> one_t;

	cout << "one_t::value: " << one_t::value << endl;
	cout << "one_t::type::value: " << one_t::type::value << endl;
	auto a3 =IntegerMax<1, 5, 5, 2, 3, 35, 5, 65632>::value;
	function<int(Plus&, int, int)> f = &Plus::plus;
	//function<int(const Plus,int, int)> f = &Plus::plus;
	system("pause");
	return 0;
}
