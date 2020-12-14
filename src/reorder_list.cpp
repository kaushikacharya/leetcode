// https://oj.leetcode.com/problems/reorder-list/
// Date: O8th Nov, 2014

#include <iostream>
#include <stack>
#include <vector>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution
{
public:
    void reorderList(ListNode *head)
    {
        int size_list = sizeList(head);

        if (size_list <= 2)
        {
            return;
        }

        int count_skip = size_list - (size_list - 1)/2;

        //ListNode* h1 = head;
        //ListNode* h2 = head;
        ListNode* curNode = head;
        ListNode* tail = NULL;

        // skip the elements till we reach the later half of the list which needs to be moved.
        int count_elem = 0;
        while (count_elem < count_skip)
        {
            tail = curNode;
            curNode = curNode->next;
            ++count_elem;
        }

        std::stack<ListNode*> stk;
        while (curNode)
        {
            stk.push(curNode);
            curNode = curNode->next;
        }

        // now pop the stack and re-order the list
        ListNode* prevNode = head;
        while (!stk.empty())
        {
            ListNode* stkNode = stk.top();
            stk.pop();
            ListNode* nextNode = prevNode->next;
            prevNode->next = stkNode;
            stkNode->next = nextNode;
            prevNode = nextNode;
        }
        tail->next = NULL;
    }
private:
    int sizeList(ListNode* head)
    {
        ListNode* node = head;
        int size_list = 0;

        while (node)
        {
            size_list += 1;
            node = node->next;
        }

        return size_list;
    }
};


int main(int argc, char* argv[])
{
    int arr[] = {1,2,3,4};
    std::vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    // build linked list
    ListNode* head = NULL;
    ListNode* curNode = NULL;
    for (int i=0; i != vec.size(); ++i)
    {
        if (head)
        {
            ListNode* newNode = new ListNode(vec[i]);
            curNode->next = newNode;
            curNode = newNode;
        }
        else
        {
            curNode = new ListNode(vec[i]);
            head = curNode;
        }
    }

    Solution sln;
    sln.reorderList(head);

    return 0;
}
