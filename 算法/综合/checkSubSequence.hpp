#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
using namespace std;

bool checkSubSequence(string s, string t)
{
	int m = s.size();
	int n = t.size();
	int i = 0, j = 0;
	while (i < m && j < n)
	{
		if (s[i] == t[j])
		{
			++i;
		}
		++j;
	}
	return i == m;
}