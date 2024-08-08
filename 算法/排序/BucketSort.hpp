#pragma once
#include "common.hpp"
#include <vector>

void BucketSort(int *arr , int arrLen) {
	int low = arr[0];
	int high = arr[0];
	for (int i = 1; i < arrLen; ++i)
	{
		if (arr[i] < low)
		{
			low = arr[i];
		}
		if (arr[i] > high)
		{
			high = arr[i];
		}
	}

	int n = high - low + 1;
	auto newArr = new int[n] {0};
	std::vector<int> res;
	//下标是数值，value是次数
	for (int i = 0; i < n; ++i)
	{
		++newArr[arr[i] - low];
	}
	for (int i = 0; i < n; ++i) 
	{ //实现了按桶下标从⼩到大输出
		for (int j = 0; j < newArr[i]; ++j)
		{ //᯿复的输出
			res.push_back(i + low);
		}
	}
}