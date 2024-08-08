#include "common.hpp"

ListNode* reverseList(ListNode* head, int left, int right)
{
	ListNode* root = head;
	ListNode* tmp = head;
	int index = 0;
	while (index != left + 1)
	{
		if (index == left - 1)
		{
			tmp = head; //leftÇ°Ò»¸ö
		}
		head = head->next;
		++index;
	}
	ListNode* le = tmp->next;
	ListNode* pre = le;
	while (index != right + 1)
	{
		ListNode* next = head->next;
		head->next = pre;
		pre = head;
		head = next;
		++index;
	}
	tmp->next = pre;
	le->next = head;
	return root;
}