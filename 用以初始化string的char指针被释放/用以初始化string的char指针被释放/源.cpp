#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
using namespace std;

void test1()
{
	string str;
	auto ch = new char[10];
	sprintf(ch, "12345");
	str = ch;
	cout << "str = " << str << endl;
	cout << "ch = " << ch << endl;
	delete []ch;
	cout << "str = " << str << endl;
	cout << "ch = " << ch << endl;
}

void test2(string &str)
{
	char ch[10] = "12345";
	str = ch;
	cout << "str = " << str << endl;
	cout << "ch = " << ch << endl;
}

void test3(string& str)
{
	const char* ch = "12345";
	str = ch;
	cout << "str = " << str << endl;
	cout << "ch = " << ch << endl;
}

int main() {
	//test1();
	string str;
	//test2(str);
	test3(str);
	cout << "str = " << str << endl;
	system("pause");
	return 0;
}