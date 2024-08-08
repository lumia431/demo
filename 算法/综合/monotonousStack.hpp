#include <iostream>
#include <stack>
#include <vector>

using namespace std;

std::vector<int> findNextSmallerElements(const std::vector<int>& nums) {
	std::vector<int> result(nums.size(), -1); // 默认为 -1，表示找不到更小的元素
	std::stack<int> st; // 单调栈，保存元素的下标

	for (int i = 0; i < nums.size(); i++) {
		while (!st.empty() && nums[st.top()] > nums[i]) {
			result[st.top()] = i; // 更新栈顶元素的下一个更小元素的下标
			st.pop(); // 弹出栈顶元素
		}
		st.push(i); // 将当前元素的下标压入栈中
	}

	return result;
}
//生成左右离自身最近的最大的数的下标
vector<pair<int, int>> monoStack(const std::vector<int>& arrs)
{
	int len = arrs.size();
	stack<int> s;
	vector<pair<int, int>> res;
	res.resize(len);
	for (int i = 0; i < len; ++i)
	{
		while (!s.empty() && arrs[i] > arrs[s.top()])
		{
			//此时，对于被弹出的那个数，左边比他大的是它底下的，右边比它大的是即将进来的
			int curr = s.top();
			res[curr].second = i; //右边
			s.pop();
			res[curr].first = s.empty() ? -1 : s.top(); //左边
		}
		s.push(i);
	}
	while (!s.empty())
	{
		int curr = s.top();
		res[curr].second = -1; //右边
		s.pop();
		res[curr].first = s.empty() ? -1 : s.top(); //左边
	}
	return res;
}