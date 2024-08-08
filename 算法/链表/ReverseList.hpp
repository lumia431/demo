#pragma once
#include "common.hpp"

ListNode* ReverseList(ListNode *root)
{
	auto ptr = root;
	ListNode* pre = NULL; //保存上一个节点
	while (ptr)
	{
		ListNode* next = ptr->next; //保存当前节点的next
		ptr->next = pre;
		pre = ptr;
		ptr = next;
	}
	return pre;
}