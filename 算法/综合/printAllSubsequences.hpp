#pragma once
#include <iostream>
#include <string>
using namespace std;

void process(std::string& str , std::string& curStr ,int n)
{
	if (n == str.size())
	{
		cout << curStr << endl;
		return;
	}
	std::string hasStr = curStr + str[n];
	++n;
	process(str, curStr,n);
	process(str, hasStr,n);
}

void PrintAllSubsequences(std::string str)
{
	std::string res;
	process(str, res,0);
}
