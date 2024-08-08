#pragma once
#include <iostream>
//#include "common.hpp"

void SelectSort(int *nums, int n) {
	if (n <= 1) return;
	int min;
	//最后一个没必要排序
	for (int i = 0; i < n - 1; ++i) 
	{
		min = i;
		//i+1没必要跟自己比较
		for (int j = i + 1; j < n; ++j)
		{
			if (nums[j] < nums[min])
			{
				min = j;
			}
		}
		if(min != i) swap(nums[min], nums[i]);
	}
}
