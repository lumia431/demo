#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct MyStruct
{
	int a;
	string b;
};
int main() {
	cout << sizeof(MyStruct) << endl;
	int a = -1;
	unsigned int b = 2;
	cout << (a + b > a) << endl;
	system("pause");
	return 0;
}