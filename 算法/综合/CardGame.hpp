//#pragma once
//#include <vector>
//#include <algorithm>
//#include <numeric>
//using namespace std;
//
//
//int inline findMax(vector<int> &v , int left , int right)
//{
//	if (left == v.size() - 1)
//	{
//		return v[left];
//	}
//	if (right == 0)
//	{
//		return v[right];
//	}
//	return max(v[left] + findMin(v, left + 1, right), v[right] + findMin(v, left, right - 1));
//}
//
//int inline findMin(vector<int> &v, int left, int right)
//{
//	if (left == v.size() - 1)
//	{
//		return v[left];
//	}
//	if (right == 0)
//	{
//		return v[right];
//	}
//	return min(v[left] + findMax(v, left + 1, right), v[right] + findMax(v, left, right - 1));
//}
//
//int CardGame(vector<int> v)
//{
//	auto res1 = findMax(v, 0, v.size() - 1);
//}