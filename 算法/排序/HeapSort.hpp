#pragma once
#include "common.hpp"
#include <vector>
using namespace std;

void Heapify(vector<int> &arr, int arrLen)
{
	for (int i = arrLen / 2 - 1; i >= 0; --i)
	{
		if (arr[i] < arr[i * 2 + 1])
		{
			swap(arr[i], arr[i * 2 + 1]);
		}
		if (i * 2 + 2 < arrLen)
		{
			if (arr[i] < arr[i * 2 + 2])
			{
				swap(arr[i], arr[i * 2 + 2]);
			}
		}
	}
}

//堆结构:左孩子的下标是2*i+1，右孩子下标2*i+2)
//满二叉树任意节点下标除以二一定是父节点
void HeapSort(vector<int> &arr, int arrLen)
{
	for (int i = 0; i < arrLen - 1; ++i)
	{
		Heapify(arr, arrLen - i);
		swap(arr[0], arr[arrLen - i - 1]);
		For(10)
		{
			cout << arr[index] << "\t";
		}
		cout << endl;
	}
}
