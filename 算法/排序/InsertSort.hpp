#pragma once
#include "common.hpp"

void InsertSort(int* arr, int arrLen)
{
	//算法描述：分为已排序和未排序 初始已排序区间只有⼀个元素 就是数组第⼀个遍历未排序的
	//每⼀个元素在已排序区间⾥找到合适的位置插⼊并保证数据⼀直有序。
	for (int i = 0; i < arrLen; ++i)
	{
		//注意要插入的数据要从离它最近的开始比较
		//这里的&& arr[j] < arr[i]可以避免无效比较
		for (int j = i - 1; j >= 0 && arr[j] > arr[j+1]; --j)
		{
			swap(arr[j + 1], arr[j]);
		}
	}
}