#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int process(vector<int> &v, int cur, int rest, vector<vector<int>>& dp)
{
	if (rest < 0)
	{
		return -1;
	}
	if (cur == v.size())
	{
		return rest == 0 ? 0 : -1;
	}
	if (dp[cur][rest] != -2)
	{
		return dp[cur][rest];
	}
	static int a = 0;
	++a;
	cout << "a = " << a << endl;

	if (rest == 0)
	{
		dp[cur][rest] = 0;
		return 0;
	}

	auto res = process(v, cur + 1, rest - v[cur], dp);
	auto resWithoutUse = process(v, cur + 1, rest, dp);
	if (res == -1)
	{
		dp[cur][rest] = resWithoutUse;
		return resWithoutUse;
	}
	if (resWithoutUse == -1)
	{
		dp[cur][rest] = res + 1;
		return res + 1;
	}
	dp[cur][rest] = min(res + 1, resWithoutUse);
	return min(res + 1, resWithoutUse);
}

int UseLeastCoins(vector<int> &v, int sum)
{
	vector<vector<int>> dp;
	dp.resize(v.size());
	for (int i = 0; i < v.size(); ++i)
	{
		dp[i].resize(sum + 1, -2);
	}
	return process(v, 0, sum, dp);
}