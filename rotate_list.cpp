// https://oj.leetcode.com/problems/rotate-list/
// Date: Nov 24, 2014

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
    ListNode *rotateRight(ListNode *head, int k)
    {
        // nothing to do for empty or single node list
        if ((head == NULL) || (head->next == NULL))
        {
            return head;
        }

        // count the number of nodes in the list
        int n = sizeList(head);
        k = k%n;

        if (k == 0)
        {
            return head; // full rotation
        }

        // get the location at which we would be breaking up the list
        ListNode* node1 = head;
        for (int i = 1; i != (n-k); ++i)
        {
            node1 = node1->next;
        }
        ListNode* node2 = node1->next;
        node1->next = NULL;

        node1 = head;
        head = node2;

        for (int i = 1; i != k; ++i)
        {
            node2 = node2->next;
        }
        node2->next = node1;

        return head;
    }
private:
    int sizeList(ListNode* head)
    {
        int n = 0;
        ListNode* node = head;

        while (node)
        {
            ++n;
            node = node->next;
        }

        return n;
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
    int arr[] = {1,2,3,4,5};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    ListNode* head = create_list(vec);
    int k = 2;

    Solution sln;
    head = sln.rotateRight(head, k);
    display_list(head);

    return 0;
}
