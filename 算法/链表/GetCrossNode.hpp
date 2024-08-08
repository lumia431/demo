#pragma once
#include "common.hpp"

ListNode* GetStartCircleNode(ListNode* root)
{
	ListNode* slowPtr = root->next;
	ListNode* fastPtr = root->next->next;
	while (slowPtr && fastPtr->next)
	{
		if (slowPtr == fastPtr)
		{
			fastPtr = root;
			while (slowPtr && fastPtr)
			{
				if (slowPtr == fastPtr)
				{
					return slowPtr;
				}
				slowPtr = slowPtr->next;
				fastPtr = fastPtr->next;
			}
		}
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
	}
	return nullptr;
}

//Node* GetCrossNode(Node* node1, Node* node2)
//{
//
//}