#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include "TreeNode.h"
#include <string>
#include <vector>
using namespace std;
//在二叉树的递归中，上层的节点调用下层的节点，如果一个节点不是另一个的祖先，它们不会在一个调用链
//建立一个结构体作为状态机，每次递归中返回信息给上一层使用
TreeNode *ancestor = nullptr;
struct ResType {
	bool panc = false;
	bool qanc = false;
	ResType(bool lan, bool ran) :panc(lan), qanc(ran) {}
};
ResType dfs(TreeNode* node, TreeNode* p, TreeNode* q) {
	if (node == nullptr || ancestor) {
		return ResType(false, false);
	}
	if (node == p) {
		return ResType(true, false);
	}
	if (node == q) {
		return ResType(false, true);
	}
	ResType lres = dfs(node->left, p, q);
	ResType rres = dfs(node->right, p, q);

	if ((lres.panc && rres.qanc) || (lres.qanc && rres.panc)) {
		ancestor = node;
		return ResType(true, true);
	}
	if (lres.panc || rres.panc) {
		return ResType(true, false);
	}
	if (lres.qanc || rres.qanc) {
		return ResType(false, true);
	}
	return ResType(false, false);
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	dfs(root, p, q);
	return ancestor;
}

int main()
{
	//std::vector<int> v{ 1,2,3,-1,4,5,-1,6,7,-1,8,9,-1,10,-1,11,12,14,15 };
	std::vector<int> v{ 4,2,7,1,3,6,9 };
	TreeNode *root = new TreeNode(4);
	int index = 0;
	root = CreateTree(root, v);
	PrintTree(root);
	//TreeNode *p = root->left->left->left->left;
	//TreeNode *q = root->left->right->left->left;
	//lowestCommonAncestor(root, p, q);
	//PrintTree(root);
	system("pause");
	return 0;
}

