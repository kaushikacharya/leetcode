// https://oj.leetcode.com/problems/reverse-nodes-in-k-group/
// Date: Nov 28, 2014

#include <iostream>
#include <stack>
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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (head == NULL)
        {
            return head;
        }

        ListNode* prevNode = NULL;
        while (true)
        {
            ListNode* curNode = NULL;
            if (prevNode)
            {
                curNode = prevNode->next;
            }
            else
            {
                curNode = head;
            }

            // Now reverse the k nodes starting from curNode
            // If not enough nodes then stop
            stack<ListNode*> stk;
            stk.push(curNode);

            while ((curNode->next) && (stk.size() < k))
            {
                curNode = curNode->next;
                stk.push(curNode);
            }
            ListNode* nextNode = curNode->next;

            if (stk.size() < k)
            {
                // case: not enough nodes
                // simply empty the stack
                while (!stk.empty())
                {
                    stk.pop();
                }
            }
            else
            {
                curNode = stk.top();
                stk.pop();

                if (prevNode)
                {
                    prevNode->next = curNode;
                }
                else
                {
                    head = curNode;
                }
                prevNode = curNode;

                while (!stk.empty())
                {
                    curNode = stk.top();
                    stk.pop();
                    prevNode->next = curNode;
                    prevNode = curNode;
                }

                prevNode->next = nextNode; // next iteration will start from nextNode
            }

            if (nextNode == NULL)
            {
                break;
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
    int arr[] = {1,2,3,4};
    int k = 4;
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    ListNode* head = create_list(vec);
    Solution sln;
    head = sln.reverseKGroup(head, k);
    display_list(head);
    return 0;
}
