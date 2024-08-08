#pragma once
#include<iostream>
using namespace std;

struct ListNode
{
	int value = 0;
	ListNode *next = nullptr;
	ListNode() = default;
	ListNode(int val) :value(val) {};
	bool operator==(ListNode& node) {
		return (this->value == node.value && this->next == node.next);
	}
};

ListNode* CreateList(int *arr, int arrLen)
{
	auto root = new ListNode;
	auto ptr = root;
	for (int i = 0; i < arrLen - 1; ++i)
	{
		auto node = new ListNode;
		ptr->value = arr[i];
		ptr->next = node;
		ptr = ptr->next;
	}
	ptr->value = arr[arrLen - 1];
	return root;
}

void PrintList(ListNode *root)
{
	auto ptr = root;
	while (ptr)
	{
		cout << ptr->value << "\t";
		ptr = ptr->next;
	}
	cout << endl;
}