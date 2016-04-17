// https://oj.leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
// Date: Nov 21, 2014

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
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode* curNode = NULL;
        ListNode* nextNode = head;

        while (nextNode)
        {
            // expecting nextNode to be the 1st elem in the series of nodes having same value
            if ( (nextNode->next == NULL) || (nextNode->next->val != nextNode->val) )
            {
                if (curNode == NULL)
                {
                    head = nextNode;
                }
                else
                {
                    curNode->next = nextNode;
                }
                curNode = nextNode;
                nextNode = nextNode->next;
                curNode->next = NULL;
            }
            else
            {
                int val = nextNode->val;
                // jump over the series of nodes having same value as val
                while ( (nextNode) && (nextNode->val == val) )
                {
                    nextNode = nextNode->next;
                }
            }
        }

        if (curNode == NULL)
        {
            head = NULL;
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
    int arr[] = {1,1,2,3,3,3,4,4,5};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    ListNode* head = create_list(vec);
    Solution sln;
    head = sln.deleteDuplicates(head);
    display_list(head);
    return 0;
}
