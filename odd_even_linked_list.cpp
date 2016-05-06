// https://leetcode.com/problems/odd-even-linked-list/
// May 04, 2016

#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* oddEvenList(ListNode* head)
    {
        if ((head == NULL) || (head->next == NULL))
        {
            return head;
        }

        ListNode* headEvenList = head->next;
        ListNode* oddListNode = head;
        ListNode* evenListNode = head->next;

        while (evenListNode && evenListNode->next)
        {
            oddListNode->next = evenListNode->next;
            oddListNode = oddListNode->next;

            evenListNode->next = oddListNode->next;
            evenListNode = evenListNode->next;
        }

        oddListNode->next = headEvenList;

        return head;
    }
};

ListNode* create_linked_list(vector<int>& vec)
{
    if (vec.empty())
    {
        return NULL;
    }

    ListNode* head = new ListNode(vec[0]);
    ListNode* prevNode = head;

    for (vector<int>::iterator it = vec.begin()+1; it != vec.end(); ++it)
    {
        ListNode* curNode = new ListNode(*it);
        prevNode->next = curNode;
        prevNode = curNode;
    }

    return head;
}

void print_linkedlist(ListNode* head)
{
    if (head == NULL)
    {
        return;
    }
    ListNode* node = head;
    while (node)
    {
        cout << node->val << " ";
        node = node->next;
    }
}

int main(int argc, char* argv[])
{
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);

    ListNode* head = create_linked_list(vec);
    cout << "initial list: ";
    print_linkedlist(head);
    Solution sln;
    ListNode* headOddEven = sln.oddEvenList(head);
    cout << "\nodd even list: ";
    print_linkedlist(headOddEven);
    return 0;
}
