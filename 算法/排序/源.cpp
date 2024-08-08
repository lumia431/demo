#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
#include "BubbleSort.hpp"
#include "InsertSort.hpp"
#include "SelectSort.hpp"
#include "BucketSort.hpp"
#include "QuickSort.hpp"
#include "MergeSort.hpp"
#include "HeapSort.hpp"
using namespace std;
int main() 
{
	srand(time(NULL));
	int arr[10] = { 2,9,4,6,3,7,5,1,8,6 };
	vector<int> v{ 2,9,4,6,3,7,5,1,8,6 };
	For(10)
	{
		cout << v[index] << "\t";
	}
	cout << endl;
	auto randArr = CreateRandomArray(100);
	HeapSort(v,10);
	For(10)
	{
		cout << v[index] << "\t";
	}
	system("pause");
	return 0;
}