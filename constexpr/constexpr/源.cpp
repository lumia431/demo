#include<iostream>
#include<string>
#include<vector>
#include <array>
using namespace std;
//普通的if语句：
//>每次控制到达时都会评估其状况,如果有的话
//>确定要执行的两个子语句中的哪一个,跳过另一个子语句
//>无论在运行时实际选择哪个子语句,都要求两个子语句格式正确
//
//if constexpr声明：
//
//>一旦提供了所有必要的模板参数,就会在编译时评估其条件
//>确定要编译的两个子语句中的哪一个,丢弃另一个子语句
//>不要求丢弃的子语句格式良好
template <int N, int... Ns>
auto sum()
{
	if constexpr (0 == sizeof...(Ns))
		return N;
	else
		return N + sum<Ns...>();
}

template<typename ...Ns>
auto sum(Ns... ns) 
{
	return (ns + ...);//折叠表达式
}

template<typename T>
auto to_string(T t)
{
	if constexpr (std::is_integral<T>::value)
		return std::to_string(t);
	else
		return t;
}

vector<int> *ptr1 = new vector<int>{ 1, 2, 3 };
vector<int> *ptr2 = new vector<int>{ 4, 5, 6 };

template<bool flag>
inline void fun(vector<int> *tmp)
{
	if (flag)
		swap(tmp, ptr1);
	else
		swap(tmp, ptr2);
}
// pow前面写的那个constexpr并不表明pow要返回一个const值，它表明的是如果base和exp是编译期常量，pow的返回结果
// 就可以当一个编译期常量使用；如果base和exp中有一个不是编译期常量，则pow的返回结果就将在执行期计算
constexpr int pow(int base, int exp) noexcept // pow is a constexpr func that never throws
{
	return (exp == 0 ? 1 : base * pow(base, exp - 1)); // C++11
	//auto result = 1; // C++14
	//for (int i = 0; i < exp; ++i) result *= base;
	//return result;
}

auto readFromDB(const std::string& str) { return 1; }

class Point15 {
public:
	constexpr Point15(double xVal = 0, double yVal = 0) noexcept : x(xVal), y(yVal) {}
	constexpr double xValue() const noexcept { return x; }
	constexpr double yValue() const noexcept { return y; }
	void setX(double newX) noexcept { x = newX; }
	//constexpr void setX(double newX) noexcept { x = newX; } // C++14
	void setY(double newY) noexcept { y = newY; }
	//constexpr void setY(double newY) noexcept { y = newY; } // C++14
private:
	double x, y;
};

constexpr Point15 midpoint(const Point15& p1, const Point15& p2) noexcept
{
	return { (p1.xValue() + p2.xValue()) / 2, (p1.yValue() + p2.yValue()) / 2 }; // call constexpr member function
}

int test_item_15()
{
	const int sz = 5; // non-constexpr variable
	//constexpr auto arraySize1 = sz; // error, sz's value not known at compilation
	//std::array<int, sz> data1; // error, sz's value not known at compilation
	constexpr auto arraySize2 = 10; // fine, 10 is a compile-time constant
	std::array<int, arraySize2> data2; // fine, arraySize2 is constexpr

	// 注意：const对象不一定经由编译器已知值来初始化
	constexpr auto arraySize3 = sz; // fine, arraySize3 is const copy of sz,arraySize3是sz的一个const副本
	std::array<int ,arraySize3> data3; // error, arraySize3.s value not known at compilation
	//所有constexpr对象都是const对象，但并非所有的const对象都是constexpr对象。如果你想让编译器提供保证，
	//让变量拥有一个值，用于要求编译期常量的语境，那么能达到这个目的的工具是constexpr，而非const。
	constexpr auto numConds = 5;
	std::array<int, pow(3, numConds)> results; // results has 3^numConds elements

	auto base = readFromDB("base"); // get these values at runtime
	auto exp = readFromDB("exponent");
	auto baseToExp = pow(base, exp); // call pow function at runtime

	constexpr Point15 p1(9.4, 27.7); // fine, "runs" constexpr constructor during compilation
	constexpr Point15 p2(28.8, 5.3);

	const auto mid = midpoint(p1, p2); // 使用constexpr函数的结果来初始化constexpr对象

	return 0;
}
int main()
{
	//vector<int> *a = new vector<int>({ 7,8,9 });
	//vector<int> *b= new vector<int>({ 7,8,9 });
	//fun<true>(a);
	//fun<false>(b);
	auto Sum = sum<1, 2, 5, 6>();
	//string s1 = "1.2";
	//string s2 = "1.2";
	//string s3 = "1.2";
	//string s4 = "1.2";
	//auto str= sum(1,2,3,4.3);
	//auto s = to_string(1.5);
	//cout << Sum << endl;
	test_item_15();
	system("pause");
	return 0;
}
