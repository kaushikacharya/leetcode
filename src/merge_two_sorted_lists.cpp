// https://oj.leetcode.com/problems/merge-two-sorted-lists/
// Date: 07th Nov 2014
// got accepted by Leetcode but I am yet to test the code. currently not compiling.
#include <iostream>
#include <vector>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL){}
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
        // handling special case when atleast one of the list is empty
        if (l1 == NULL)
        {
            return l2;
        }
        else if (l2 == NULL)
        {
            return l1;
        }

        ListNode* l3 = NULL;
        ListNode* h3 = NULL;

        // get the head of the merged list
        if (l1->val <= l2->val)
        {
            l3 = l1;
            l1 = l1->next;
        }
        else
        {
            l3 = l2;
            l2 = l2->next;
        }

        h3 = l3;

        while (l1 && l2)
        {
            if (l1->val <= l2->val)
            {
                l3->next = l1;
                l3 = l1;
                l1 = l1->next;
            }
            else
            {
                l3->next = l2;
                l3 = l2;
                l2 = l2->next;
            }
        }

        if (l1)
        {
           l3->next = l1;
        }
        else
        {
            l3->next = l2;
        }

        return h3;

    }
};

template <typename T>
ListNode* convert_vec_to_list(std::vector<T>& vec)
{
    ListNode* head = NULL;
    ListNode* listNode = NULL;

    for (int i = 0; i != vec.size(); ++i)
    {
        if (i == 0)
        {
            listNode = ListNode(vec[i]);
            head = listNode;
        }
        else
        {
            ListNode curNode = ListNode(vec[i]);
            listNode->next(&curNode);
            listNode = curNode;
        }
    }

    return head;
}

int main(int argc, char* argv[])
{
    ListNode* l2 = NULL;

    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(8);

    ListNode* l1 = convert_vec_to_list(v1);

    return 0;
}

/*
http://www.geeksforgeeks.org/merge-two-sorted-linked-lists/
*/
