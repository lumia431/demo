#include<iostream>
#include<string>
#include<vector>
#include <map>
using namespace std;
struct MyStruct1
{
	int a;
	int b;
};

struct MyStruct2
{
	int a;
	MyStruct1 ms;
};
int main()
{
	MyStruct1 m{ 1 };
	std::map<int, int> tmp;
	//对于std::map的[]运算符重载函数，在使用[]新增key时，std::map就已经插入了一个新的键值对
	tmp[0] = tmp.size();//此处不知道插入的是{0, 0}还是{0, 1}.答案是0,0
	int ok1, ok2;
	switch (0)
	{
	case 0:
		ok1 = 0;
		[[fallthrough]];//直接跳转到下一条件执行，后面语句直接跳过
	case 1:
		ok2 = 1;
		[[fallthrough]];
	}

	MyStruct1 m1{ 1 };
	system("pause");
	return 0;
}
