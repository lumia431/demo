#pragma message( "Compiling " __FILE__ )         //显示被编译的文件
#pragma message( "Last modified on " __TIMESTAMP__ )     //文件最后一次修改的日期和时间 
#pragma warning( push, 4 )
#define For(n) for(int index=0;index<n;++index)
#include<iostream>
#include<string>
#include<vector>
#include <map>
#include "A.h"
#include <windows.h>
using namespace std;
void test()
{
	A a(1);
}
class Rational24 {
public:
	Rational24(int numerator = 0, int denominator = 1) {
		n = numerator;
		d = denominator;
	} // 构造函数刻意不为explicit,允许int-to-Rational24隐式转换
	int numerator() const { return n; } // 分子(numerator)的访问函数
	int denominator() const { return d; } // 分母(denominator)的访问函数

	/*const Rational24 operator* (const Rational24& rhs) const
	{
		return Rational24(this->n * rhs.numerator(), this->d * rhs.denominator());
	}*/

private:
	int n, d;
};

const Rational24 operator* (const Rational24& lhs, const Rational24& rhs) // non-member函数
{
	return Rational24(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

int test_item_24()
{
	Rational24 r(1);
	Rational24 oneEighth(1, 8);
	Rational24 oneHalf(1, 2);
	Rational24 result = oneHalf * oneEighth; // 很好
	result = result * oneEighth; // 很好

	result = oneHalf * 2; // 很好,隐式类型转换(implicit type conversion)
	result = 2 * oneHalf; // 错误, only non-member function success

	// 以对应的函数形式重写上述两个式子
	//result = oneHalf.operator*(2); // 很好, only member function success
	//result = 2.operator*(oneHalf); // 错误, only non-member function success

	result = operator*(2, oneHalf); // 错误, only non-member function success

	return 0;
}
int main()
{
	//cout <<(int)( 10.1 / 2) << endl;
	//string str("lmy");
	//const char* ptr = "lmy";
	//auto buffer = new char[255];
	//cout << str.size() << endl;
	//cout << strlen(ptr) << endl;
	//cout << strlen(buffer) << endl;
	//map<string, int>m{ {"a",2} ,{"b",24} };
	//if (1 != m["a"])
	//{
	//	cout << 123 << endl;
	//}
	//map<string, int>m1{ {"a",2} };
	//m = m1;
	//cout << 1603691814 / 10 << endl;
	//vector<int>v{ 1,2,3,4,5 };
	//auto it = v.erase(v.begin() + 3);
	//string a = "helo";
	//string b(a.c_str(), 8);
	//For(5)
	//{
	//	cout << index << endl;
	//}
	//unsigned int j = 10;
	//int i = 0;
	//while ( --j,++i)
	//{
	//	cout << i << endl;
	//	cout << j << endl;
	//	Sleep(1000);
	//}
	test_item_24();
	system("pause");
	return 0;
}
#pragma warning( pop )