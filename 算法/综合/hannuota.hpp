#pragma once
#include <iostream>
using namespace std;
int count = 0;

int process(int n)
{
	static int count = 0;
	++count;
	cout << "count = " << count << endl;
	if (n == 1) {
		return 1;
	}
	else
	{
		return 2*process(n - 1) + 1;
	}
}

int Hannuota(int n)
{
	auto res = process(5);
	return res;
}