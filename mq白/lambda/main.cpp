#include<iostream>
#include<string>
#include<format>
using namespace std;

struct A
{
	auto operator ()() { cout << 2 << endl; }
};
struct B
{
	auto operator ()() const { ++data_; }
private:
	int& data_;
};

template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts)
{
	if constexpr (sizeof...(ts) > 0)
	{
		return [&](auto ...para) {
			return t(concat(ts...)(para...));
		};
	}
	else
	{
		return t;
	}
}
int main() {
	auto one = [] {return "one"; };//此处的小括号可以省略
	auto two = []() -> std::string {return "one"; };//此处的小括号不可以省略
	auto a1 = one();
	auto a2 = two();
	auto p2 = [] <typename T> (T && f) { f(); };//c++20
	p2(one);
	p2(std::move(one));
	[] <typename T> (T && f) { f(); }(two);
	A()();
	int num{};
	//auto p3 = [num]() {++num};//如果不加mutable，默认的重载()成员函数是const的
	auto p3 = [num]() mutable {++num; cout << num << endl; };//如果不加mutable，默认的重载()成员函数是const的
	auto pp = [&num]() {++num; cout << num << endl; };//但是引用是可以修改的，引用的常量性由引用绑定的对象的常量性来决定。如果引用绑定到一个非 const 对象上，那么您可以在 const 成员函数中通过引用修改该对象，因为引用仅提供了对对象的访问，而不会影响对象本身的常量性。
	p3();
	cout << num << endl;
	auto p4 = [=] {};//用到了就捕获，比如在函数体用到了num就捕获num
	cout << sizeof(p4) << endl;//1,因为啥都没用到
	cout << sizeof(p3) << endl;//4
	constexpr int c = [] {return 3; }();//隐式constexpr
	constexpr int cc = []() constexpr {return 3; }();//显式constexpr
	auto three = [](int i) {return i * 3; };
	auto four = [](int i) {return i * 4; };
	auto f = concat(three, four, std::plus<int>{});
	auto rs = f(1, 2);
}