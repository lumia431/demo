#include <iostream>
#include<list>
#include<map>
struct S
{
	double num1;
	long num2;
};

S foo(int arg1, double arg2)
{
	double result1 = arg1 * arg2;
	long result2 = arg2 / arg1;
	return { result1, result2 };//返回结构体S对象
};


/*
 * 例子：循环遍历
 */
template<typename T, typename U>
struct MyStruct
{
	T key;
	U value;
};

int main()
{
	auto a = foo(10, 20.2);
	auto[num1, num2] = a;//自动推导num1为double，num2为long
	auto&[num1, num2] = a;//可以绑定引用
	num1 = 1;
	return 0;
	std::list<MyStruct<int, double>> Container1;
	std::map<int, MyStruct<long long, char>> Container2;
	for (auto[key, value] : Container1)
	{
		//key为int类型，value为double类型
	}
	for (auto[key, value] : Container2)
	{
		//key为int类型，value为MyStruct<long long, char>类型
		//value1为long long类型，value2为char类型
		auto[value1, value2] = value;
	}
	return 0;
}
