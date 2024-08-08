#include<iostream>
#include<vector>
using namespace std;
//由于限定作用域的枚举型别是通过”enum class”声明的，所有有时它们也被称为枚举类。

//限定作用域的枚举型别带来的名字空间污染降低，已经是”应该优先选择它，而不是不限范围的枚举型别”的足够理由。
//但是限定作用域的枚举型别还有第二个优势：它的枚举量是更强型别的(strongly typed)。
//不限范围的枚举型别中的枚举量可以隐式转换到整数型别(并能够从此处进一步转换到浮点型别)。
//从限定作用域的枚举型别到任何其它型别都不存在隐式转换路径。
std::vector<std::size_t> primeFactors(std::size_t x) { return std::vector<std::size_t>(); }

enum class Status; // 前置声明, 默认底层型别(underlying type)是int
enum class Status2 : std::uint32_t; // Status2的底层型别是std::uint32_t
enum Color : std::uint8_t; // 不限范围的枚举型别的前置声明，底层型别是std::uint8_t

int test_item_10()
{
	enum Color1 { black, white, red }; // 不限范围的(unscoped)枚举型别：black, white, red所在作用域和Color1相同
	//auto white = false; // error, white already declared in this scope
	Color1 c1 = black;

	enum class Color2 { black2, white2, red2 }; // C++11, 限定作用域的(scoped)枚举型别:black2, white2, red2所在作用域被限定在Color2内
	auto white2 = false; // 没问题，范围内并无其它"white2"
	//Color2 c1 = black2; // 错误，范围内并无名为"black2"的枚举量
	Color2 c2 = Color2::black2; // fine
	auto c3 = Color2::black2; // also fine

	if (c1 < 14.5) // 将Color1型别和double型别值作比较,怪胎
		auto factors = primeFactors(c1);

	//if (c2 < 14.5) // 错误，不能将Color型别和double型别值作比较
	//	auto facotrs = primeFactors(c2); // 错误，不能将Color2型别传入要求std::size_t型别形参的函数

	return 0;
}
int main() {
	test_item_10();
	return 0;
}