#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
#include "ReverseList.hpp"
#include "GetCrossNode.hpp"
#include "review.hpp"
using namespace std;
int main() 
{
	int arr[9] = {1,2,3,4,5 };
	auto root = CreateList(arr, 5);
	//auto root = new ListNode(1);
	//auto n2 = new ListNode(2);
	//auto n3 = new ListNode(3);
	//auto n4 = new ListNode(4);
	//root->next = n2;
	//n2->next = n3;
	//n3->next = n4;
	//n4->next = n2;
	//auto node = GetStartCircleNode(root);
	//PrintList(root);
	//auto res = ReverseList(root);
	auto res = reverseList(root, 2, 4);
	PrintList(root);
	system("pause");
	return 0;
}