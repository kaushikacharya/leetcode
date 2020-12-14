// https://leetcode.com/problems/add-two-numbers/
// June 15, 2016

#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL){}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        // Handle edge cases when atleast one of the linked list is empty
        if (l2 == NULL)
        {
            return l1;
        }
        if (l1 == NULL)
        {
            return l2;
        }

        int val = l1->val + l2->val;
        int digit = val % 10;
        int carry_over = val / 10;

        ListNode* nodeAdd = new ListNode(digit);
        ListNode* headAdd = nodeAdd;
        l1 = l1->next;
        l2 = l2->next;

        // First do the sum over nodes of length = min(length(l1), length(l2))
        while (l1 && l2)
        {
            val = l1->val + l2->val + carry_over;
            digit = val % 10;
            carry_over = val / 10;
            nodeAdd->next = new ListNode(digit);
            nodeAdd = nodeAdd->next;
            l1 = l1->next;
            l2 = l2->next;
        }

        // Now handle the cases when we have finished one of the linked list but other linked list still has nodes
        if (l1)
        {
            nodeAdd->next = l1;
        }
        else if (l2)
        {
            nodeAdd->next = l2;
        }

        while ( nodeAdd->next && (carry_over > 0) )
        {
            val = nodeAdd->next->val + carry_over;
            digit = val % 10;
            carry_over = val / 10;
            nodeAdd->next->val = digit;
            nodeAdd = nodeAdd->next;
        }

        // Now the case when we have carry_over left and both the linked list's nodes have been considered
        if (carry_over > 0)
        {
            nodeAdd->next = new ListNode(carry_over);
        }

        return headAdd;
    }
};

void display_linked_list(ListNode* head)
{
    ListNode* node = head;
    while(node)
    {
        cout << node->val;
        if (node->next)
        {
            cout << "->";
        }
        node = node->next;
    }
    cout << endl;
}

ListNode* create_linked_list(vector<int> vec)
{
    ListNode* head = NULL;

    if (vec.empty())
    {
        return head;
    }

    head = new ListNode(vec[0]);
    ListNode* node = head;

    for (vector<int>::iterator it = vec.begin()+1; it != vec.end(); ++it)
    {
        node->next = new ListNode(*it);
        node = node->next;
    }

    return head;
}

int main(int argc, char* argv[])
{
    vector<int> v1 = {9,9};
    vector<int> v2 = {9,9,9};

    ListNode* l1 = create_linked_list(v1);
    ListNode* l2 = create_linked_list(v2);

    cout << "linked list #1: ";
    display_linked_list(l1);

    cout << "linked list #2: ";
    display_linked_list(l2);

    Solution sln;
    ListNode* list_add = sln.addTwoNumbers(l1,l2);
    cout << "linked list(add): ";
    display_linked_list(list_add);

    return 0;
}
