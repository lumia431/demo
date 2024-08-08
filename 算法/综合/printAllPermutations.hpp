#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//第一位数我可以取任意下标，但是这个下标对应的字母用完就要从剩余字母中去除，然后把一位数的都打印出来
//第二位我只能取n-1个下标了
void process(std::string str, std::string& curStr)
{
	if (str.empty())
	{
		cout << curStr << endl;
		return;
	}
	cout << curStr << endl;
	for (int i = 0; i < str.size(); ++i)
	{
		std::string tmpStr = curStr + str[i];
		std::string restStr = str;
		restStr.erase(std::remove(restStr.begin(), restStr.end(), restStr[i]), restStr.end());
		process(restStr, tmpStr);
	}
}

void PrintAllPermutations(std::string str)
{
	std::string res;
	process(str, res);
}