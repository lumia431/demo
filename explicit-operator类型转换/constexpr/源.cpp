#include <iostream>
#include <string>
#include <vector>
#include <time.h>
using namespace std;
class CArea
{
	float area;
public:
	explicit CArea(float a= 1.0)
	{
		area = a;
	}
	void GetArea()
	{
		cout << area << endl;
	}
	void SetArea(float a)
	{
		area = a;
	}
	operator float()
	{
		return area;
	}
};
class CCircle
{
	float R;
public:
	CCircle(float r)
	{
		R = r;
	}
	void getR()
	{
		cout << R << endl;
	}
	void setR(float r)
	{
		R = r;
	}
	operator CArea()   //类型转换函数
	{                                 //将圆类对象转为面积类对象
		float area = 3.1415926*R*R;
		return (CArea(area));
	}
};
template<class T>
constexpr T pi = T(3.145926);
template<typename T, typename U>
struct A {
	T t;
	U u;
};
template<typename T>
using B = A<T, int>;
struct[[deprecated]] C{ };//被弃用
int main() 
{
	//B<double> b;
	//b.t = 10;
	//b.u = 20;
	//cout << b.t << endl;
	//cout << b.u << endl;
	//cout << pi<int> << endl; // 3  
	//cout << pi<double> << endl; // 3.14159 
	//C c;
	//const double c = 1;
	//remove_const<decltype(c)>::type b = 2;
	//CArea are = 1;//隐式转换被禁止
	CArea are (1.0);
	CCircle cir(5.0);
	cir.setR(5);
	are = cir;
	float qual(are);//隐式类型转换是将系统类型转换成自定义类型,operator则提供将自定义类型转成其他类型
	cout << qual << endl;
	return 0;
}