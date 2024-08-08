#pragma once
#include "common.hpp"
#include <vector>
using namespace std;

void MergeSort(int *arr, int left, int right)
{
	if (right - left < 1)
	{
		return;
	}
	int mid = left + (right - left + 1) / 2;
	MergeSort(arr, left, mid - 1);
	MergeSort(arr, mid, right);
	int lPtr = left;
	int rPtr = mid;
	vector<int> tmp;
	while (lPtr < mid && rPtr <= right)
	{
		if (arr[lPtr] < arr[rPtr])
		{
			tmp.emplace_back(arr[lPtr]);
			++lPtr;
		}
		else
		{
			tmp.emplace_back(arr[rPtr]);
			++rPtr;
		}
	}
	while (lPtr < mid)
	{
		tmp.emplace_back(arr[lPtr]);
		++lPtr;
	}
	while (rPtr <= right)
	{
		tmp.emplace_back(arr[rPtr]);
		++rPtr;
	}
	for (int i = 0; i < tmp.size(); ++i)
	{
		arr[left + i] = tmp[i];
	}
}