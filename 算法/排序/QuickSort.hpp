#pragma once
#include "common.hpp"
#include <vector>

void QuickSort(int *arr, int left, int right) 
{
	if (left >= right) return;
	int lPtr = left;
	int rPtr = right;
	int pos = left;
	while (lPtr < rPtr)
	{
		while (arr[rPtr] >= arr[pos] && rPtr > lPtr)
		{
			--rPtr;
		}
		swap(arr[rPtr], arr[pos]);
		pos = rPtr;
		while (arr[lPtr] <= arr[pos] && rPtr > lPtr)
		{
			++lPtr;
		}
		swap(arr[lPtr], arr[pos]);
		pos = lPtr;
	}
	QuickSort(arr, left, pos);
	QuickSort(arr, pos + 1, right);
}
