#pragma once
#include <string>
#include <deque>
#include <queue>
#include <vector>
using namespace std;
//维护一个优先队列，判断堆顶元素是否在窗口中，若不在窗口中说明已经在窗口左侧了
//此时将其永久移除，直到堆顶在窗口中位置，此时堆顶就是窗口的最大值
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	int n = nums.size();
	vector<int> ans;
	if (n < k || k < 1)
	{
		return ans;
	}
	priority_queue<pair<int, int>> q;
	for (int i = 0; i < k; ++i) {
		q.emplace(nums[i], i);
	}
	ans = { q.top().first };
	for (int i = k; i < n; ++i) {
		q.emplace(nums[i], i);
		while (q.top().second <= i - k) {
			q.pop();
		}
		ans.push_back(q.top().first);
	}
	return ans;
}
//单调队列是一个双端队列,里面存放的是下标,这个队列的大小不是固定的会一直变化
//新元素进来的时候从底部开始比较，比底部元素大就让它从底部弹出
vector<int> dandiaoQueue(vector<int>& nums, int k) {
	int n = nums.size();
	vector<int> res;
	if (n < k || k < 1)
	{
		return res;
	}
	deque<int> q;
	for (int i = 0; i < k; ++i) {
		while (!q.empty()&&nums[i] >= nums[q.back()])
		{
			q.pop_back();
		}
		q.push_back(i);
	}
	vector<int> ans = { nums[q.front()]};
	for (int i = k; i < n; ++i) {
		while (!q.empty() && nums[i] >= nums[q.back()])
		{
			q.pop_back();
		}
		q.push_back(i);
		while (q.front() <= i - k) {
			q.pop_front();
		}
		ans.push_back(nums[q.front()]);
	}
	return ans;
}