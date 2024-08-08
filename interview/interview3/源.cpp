#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
string test(const string& str1, const string& str2) {
	if (str1.empty() && str2.empty()) {
		return "";
	}
	string result;
	int size1 = str1.size();
	int size2 = str2.size();
	int index1 = 0;
	int index2 = 0;
	auto ptr1 = str1.rbegin();
	auto ptr2 = str2.rbegin();
	int a1 = 0;
	int a2 = 0;
	int curResult = 0;
	int jinwei = 0;
	while (index1 < size1)
	{
		if (index2 >= size2)
		{
			a1 = static_cast<int>(*ptr1) - 48;
			curResult = (a1 + jinwei) % 10;
			jinwei = a1 + jinwei < 10 ? 0 : 1;
			result.push_back(curResult+'0');
			++ptr1;
			++index1;
			continue;
		}
		a1 = static_cast<int>(*ptr1) - 48;
		a2 = static_cast<int>(*ptr2) - 48;
		curResult = (a1 + a2 + jinwei) % 10;
		jinwei = a1 + a2 < 10 ? 0 : 1;
		result.push_back(curResult + '0');
		++ptr1;
		++ptr2;
		++index1;
		++index2;
	}
	while (index2 < size2)
	{
		a2 = static_cast<int>(*ptr2) - 48;
		curResult = (a2 + jinwei) % 10;
		jinwei = a2 + jinwei < 10 ? 0 : 1;
		result.push_back(curResult + '0');
		++ptr2;
		++index2;
	}
	if (jinwei == 1) {
		result.push_back('1');
	}
	reverse(result.begin(), result.end());
	return result;
}
int main()
{
	string a("9999999");
	string b("99999");
	auto d = 9999999 + 99999;
	auto c = test(a, b);
	cout << "d = " << d << endl;
	cout << "c = " << c << endl;
	//char c = '0';
	//int a = 1;
	//c = a;
	system("pause");
	return 0;
}