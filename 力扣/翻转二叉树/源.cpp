#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<queue>
#include<vector>
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

TreeNode* CreateTree(TreeNode* root, std::vector<int>& v)
{
	if (!root) {
		return nullptr;
	}
	queue<TreeNode*> que;
	que.push(root);
	TreeNode* tmpNode = nullptr;
	int size = v.size();
	int floorNum = 0;
	int num = 0;

	while (num < size - 1)
	{
		tmpNode = que.front();
		que.pop();
		if (v[++num] >= 0) {
			tmpNode->left = new TreeNode(v[num]);
			que.push(tmpNode->left);
		}
		if (num >= size - 1) {
			break;
		}
		if (v[++num] >= 0) {
			tmpNode->right = new TreeNode(v[num]);
			que.push(tmpNode->right);
		}
	}
	return root;
}

TreeNode* invertTree(TreeNode* root) {
	if (root == nullptr) {
		return nullptr;
	}
	TreeNode* left = invertTree(root->left);
	TreeNode* right = invertTree(root->right);
	root->left = right;
	root->right = left;
	return root;
}


int main() {
	vector<int> v = { 4,2,7,1,3,6,9 };
	TreeNode* root = new TreeNode{4};
	auto head = CreateTree(root, v);
	auto res = invertTree(head);
	//0 1 10 11 100 101 110 111 1000 1001 1010 1011 1100 1101 1110 1111 10000
	//0 1 1  2  1   2   2   3   1    2    2    3    2    3    3    4     1
	//                          0    1    1    2    1    2    2    3
	system("pause");
	return 0;
}