// https://leetcode.com/problems/reverse-linked-list-ii/
// July 03, 2016

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
    ListNode* reverseBetween(ListNode* head, int m, int n)
    {
        if ( (head == NULL) && (m == n) )
        {
            return head;
        }

        ListNode* node0 = NULL; // (m-1)'th node in case m > 1
        ListNode* node1 = NULL; // m'th node
        ListNode* node2 = NULL; // (n+1)'th node in case n<size(list)

        ListNode* node = head;
        int i = 1;

        while (node)
        {
            if (i == (m-1))
            {
                node0 = node;
            }
            else if (i == m)
            {
                node1 = node;
            }
            else if (i == (n+1))
            {
                node2 = node;
                break; // No more looping required
            }
            node = node->next;
            ++i;
        }

        i = 0;
        while (i < (n-m))
        {
            ListNode* tempNode = node1->next;
            node1->next = node2;
            node2 = node1;
            node1 = tempNode;
            ++i;
        }

        if (m > 1)
        {
            node0->next = node1;
        }
        else
        {
            head = node1;
        }

        node1->next = node2;

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

void print_linked_list(ListNode* head)
{
    ListNode* node = head;
    cout << node->val;
    node = node->next;

    while (node)
    {
        cout << "," << node->val;
        node = node->next;
    }

    cout << endl;
}

int main(int argc, char* argv[])
{
    vector<int> vec = {1,2};
    ListNode* head = create_linked_list(vec);
    cout << "original linked list: ";
    print_linked_list(head);

    int m = 1;
    int n = 1;

    Solution sln;
    head = sln.reverseBetween(head, m, n);
    cout << "post reversal: ";
    print_linked_list(head);

    return 0;
}

/**
*   Here's another approach:
*   https://discuss.leetcode.com/topic/26799/c-in-14-lines
*   Seems like my approach is batch level and lightmark's approach is online level.
*   In his/her approach, initial portion of the list is reversed and the portion keeps on increasing.
*/
