#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <queue>
using namespace std;
vector<shared_ptr<string>>v;
string test()
{
	string str("123");
	str.clear();
	return str;
}
int main() 
{
	//queue<int>q;
	//v.swap();
	auto a = "一";
	char c[3] = { 0xE7,0x88,0xb1 };
	auto l = strlen(a);
	memcpy_s(c, strlen(a) + 1, a, strlen(a) + 1);
	cout << c << endl;
	l = strlen(c);
	v.resize(5000000, make_shared<string>("21321432346767978890-8-09djiogjdsofkjhwqioe9221321432346767978890-8-09djiogjdsofkjhwqioe9221321432346767978890-8-09djiogjdsofkjhwqioe92"));
	clock_t cl = clock();
	For(5000000)
	{
		auto str = v[index];
	}
	cout << clock() - cl << endl;
	system("pause");
	return 0;
}