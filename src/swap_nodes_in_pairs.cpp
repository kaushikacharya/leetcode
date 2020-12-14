// https://oj.leetcode.com/problems/swap-nodes-in-pairs/
// Date: Nov 25, 2014

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
    ListNode *swapPairs(ListNode *head)
    {
        if (head == NULL)
        {
            return head;
        }

        ListNode* prevNode = NULL;
        ListNode* node1 = head;

        while ((node1) && (node1->next))
        {
            ListNode* node2 = node1->next;
            ListNode* nextNode = node2->next;

            node1->next = nextNode;
            node2->next = node1;

            if (prevNode)
            {
                prevNode->next = node2;
            }
            else
            {
                head = node2;
            }

            // now preparing for next swap of pairs
            prevNode = node1;
            node1 = node1->next;
        }

        return head;
    }
};

ListNode* create_list(vector<int>& vec)
{
    if (vec.size() == 0)
    {
        return NULL;
    }

    ListNode* head = new ListNode(vec.front());
    ListNode* curNode = head;

    for (vector<int>::iterator it = vec.begin()+1; it != vec.end(); ++it)
    {
        ListNode* nextNode = new ListNode(*it);
        curNode->next = nextNode;
        curNode = nextNode;
    }

    return head;
}

void display_list(ListNode* head)
{
    if (head == NULL)
    {
        return;
    }
    ListNode* curNode = head;
    cout << curNode->val;
    curNode = curNode->next;

    while (curNode)
    {
        cout << "," << curNode->val;
        curNode = curNode->next;
    }
}

int main(int argc, char* argv[])
{
    int arr[] = {1,2,3};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    ListNode* head = create_list(vec);
    Solution sln;
    head = sln.swapPairs(head);
    display_list(head);
    return 0;
}

/*
Possibility of odd number of nodes:
https://oj.leetcode.com/discuss/2583/there-any-grantee-that-there-will-always-even-number-of-nodes
*/
