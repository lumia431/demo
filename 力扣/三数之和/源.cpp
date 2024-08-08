#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using namespace std;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() = default;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
struct ListNode
{
	int value = 0;
	ListNode* next = nullptr;
	ListNode() = default;
	ListNode(int val) :value(val) {};
	bool operator==(ListNode& node) {
		return (this->value == node.value && this->next == node.next);
	}
};
struct Edge {
	int weight;
	int aimNode;//指向的节点
	Edge* nextEdge;
};
typedef struct Node {
	char data; //点名 
	Edge* firstEdge; //从该点出去的第一条边，该点出去的其他的边串在后面
};
//定义图的邻接表存储结构 
typedef struct {
	Node nodeList[127]; //节点数组 
	int n; //图的顶点数
	int e; //图的边数 
}Graph;

struct Type {
	int x;
	int y;
	int z;
	Type(int a, int b, int c) :x(a), y(b), z(c) {}
};

struct TypeHash {
	std::size_t operator()(const Type& obj) const {
		std::size_t h1 = std::hash<int>{}(obj.x);
		std::size_t h2 = std::hash<int>{}(obj.y);
		std::size_t h3 = std::hash<int>{}(obj.z);
		return h1 ^ h2 ^ h3;
	}
};

struct TypeEqual {
	bool operator()(const Type& obj1, const Type& obj2) const {
		unordered_set<int> u1{ obj1.x,obj1.y,obj1.z };
		unordered_set<int> u2{ obj2.x,obj2.y,obj2.z };
		return u1 == u2;
	}
};

vector<vector<int>> threeSum(vector<int>& nums) {
	unordered_set<Type, TypeHash, TypeEqual> res;
	vector<vector<int>> result;
	unordered_map<int, unordered_set<Type, TypeHash, TypeEqual>> um;
	int len = nums.size();
	if (len < 3)
	{
		return result;
	}
	um[nums[0] + nums[1]].insert({ nums[0] ,nums[1],0 - nums[0] - nums[1] });
	for (int i = 2; i < len; ++i)
	{
		if (um.count(0 - nums[i]))
		{
			for (auto& rs : um[0 - nums[i]])
			{
				res.insert(rs);
			}
		}
		for (int j = 0; j < i; ++j)
		{
			um[nums[j] + nums[i]].insert({ nums[j] ,nums[i],0 - nums[j] - nums[i] });
		}
	}
	for (auto& rs : res)
	{
		result.push_back({ rs.x,rs.y,rs.z });
	}
	return result;
}

int main() {

	vector<int> nums{ -1,0,1,2,-1,-4 };
	auto rs = threeSum(nums);
	system("pause");
	return 0;
}