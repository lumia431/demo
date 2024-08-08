#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool isValid(string s) {
	uint16_t small = 0;
	uint16_t mid = 0;
	uint16_t big = 0;
	int index = 0;
	int len = s.size();
	while (index < len)
	{
		switch (s[index])
		{
		case '(':
			++small;
			break;
		case '[':
			break;
		case '{':
			break;
		case ')':
			break;
		case ']':
			break;
		case '}':
			break;
		default:
			break;
		}
	}
}

int main() {

	system("pause");
	return 0;
}