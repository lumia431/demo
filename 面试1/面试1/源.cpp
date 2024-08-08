#include<iostream>
#include<vector>
using namespace std;
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    ListNode* merge(ListNode* a, ListNode* b) {
        ListNode* head = new ListNode;
        ListNode* node = head;
        if (a == nullptr && b == nullptr) {
            return nullptr;
        }
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        while (a && b) {
            if (a->val < b->val) {
                node->next = a;
                a = a->next;
            }
            else {
                node->next = b;
                b = b->next;
            }
            node = node->next;
        }
        node->next = a == nullptr ? b : a;
        return head->next;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* res = nullptr;
        for (auto& list : lists) {
            res = merge(list, res);
        }
        return res;
    }
};

int main() {
    Solution s;
    ListNode* list1 = new ListNode;
    ListNode* list2 = new ListNode;
    ListNode* list3 = new ListNode;
    ListNode* list4 = new ListNode;
    ListNode* list5 = new ListNode;
    ListNode* list6 = new ListNode;
    ListNode* list7 = new ListNode;
    ListNode* list8 = new ListNode;
    list1->val = 1;
    list2->val = 4;
    list3->val = 5;
    list4->val = 1;
    list5->val = 3;
    list6->val = 4;
    list7->val = 2;
    list8->val = 6;
    list1->next = list2;
    list2->next = list3;
    list3->next = nullptr;
    list4->next = list5;
    list5->next = list6;
    list6->next = nullptr;
    list7->next = list8;
    list8->next = nullptr;
    vector<ListNode*> v{ list1 ,list4 ,list7 };
    s.mergeKLists(v);
}