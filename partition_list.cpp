// https://oj.leetcode.com/problems/partition-list/
// Date: Nov 23,2014

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
    ListNode *partition(ListNode *head, int pVal)
    {
        if (head == NULL)
        {
            return NULL;
        }

        ListNode* p1 = NULL;
        ListNode* p2 = NULL;

        if (head->val < pVal)
        {
            p1 = head;
        }
        else
        {
            p2 = head;
        }

        while (true)
        {
            if (p2)
            {
                if (p2->next)
                {
                    if (pVal <= p2->next->val)
                    {
                        p2 = p2->next;
                    }
                    else
                    {
                        ListNode* curNode = p2->next;
                        p2->next = curNode->next;

                        // now put curNode in 1st half of partition
                        if (p1)
                        {
                            curNode->next = p1->next;
                            p1->next = curNode;
                            p1 = curNode;
                        }
                        else
                        {
                            p1 = curNode;
                            p1->next = head;
                            head = p1;
                        }
                    }
                }
                else
                {
                    break; // no more nodes available
                }
            }
            else
            {
                // we haven't yet encountered node belonging to 2nd half of partition.
                if (p1->next)
                {
                    if (pVal <= p1->next->val)
                    {
                        p2 = p1->next;
                    }
                    else
                    {
                        p1 = p1->next;
                    }
                }
                else
                {
                    break; // all the nodes belong to first half of partition.
                }
            }
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
    int arr[] = {1,4,3,2,5,2};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    ListNode* head = create_list(vec);
    int pVal = 0;
    Solution sln;
    head = sln.partition(head,pVal);
    display_list(head);
    return 0;
}
