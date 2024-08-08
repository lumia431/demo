#pragma once
#include "common.hpp"

void BubbleSort(int* arr, int arrLen)
{
	for (int i = 0; i < arrLen; ++i)
	{
		for (int j = i + 1; j < arrLen; ++j)
		{
			if (arr[i] > arr[j])
			{
				swap(arr[i], arr[j]);
			}
		}
	}
}
