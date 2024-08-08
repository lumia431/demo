#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
using namespace std;
class String1
{
public:
	String1(const char*str = "")//默认构造参数//可以不用参数
	{
		m_str = new char[strlen(str) + 1];
		strcpy(m_str, str);          
		cout << "create String" << endl;
	}
	// 列如：String1 str3(str1); 我们假如拷贝构造函数参数不是引用类型的话,临时对象会递归出发构造函数
	String1(const String1 &s) {
		m_str = new char[strlen(s.m_str) + 1];         
		strcpy(m_str, s.m_str);        
		cout << "copy String" << endl;
	}
	String1& operator=(const String1& s) {
		delete[] m_str;
		m_str = new char[strlen(s.m_str) + 1];
		strcpy(m_str, s.m_str);        
		cout << "=====" << endl;             
		return *this;
	}
	~String1()
	{
		delete[]m_str;       
		m_str = nullptr;
	}   

	char* m_str;

};
void main()
{
	String1 str1("a");
	String1 str2("b");
	String1 str3(str1);
	String1 str4 = str2;//执行拷贝构造

	//若此时拷贝赋值函数是值传递会因为拷贝临时对象产生一次拷贝构造，同样，返回值若不为引用也会触发拷贝构造
	str4 = str1;
}