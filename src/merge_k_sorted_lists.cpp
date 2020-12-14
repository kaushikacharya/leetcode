// https://oj.leetcode.com/problems/merge-k-sorted-lists/
// Date: Dec 09, 2014

#include <iostream>
#include <queue>
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
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        ListNode* head = NULL;

        MinPQ min_pq;
        // push 1st element of the lists into the priority queue
        for (vector<ListNode*>::iterator it = lists.begin(); it != lists.end(); ++it)
        {
            if (*it)
            {
                min_pq.push(*it);
            }
        }
        if (min_pq.empty())
        {
            return head;
        }

        head = min_pq.top();
        min_pq.pop();
        ListNode* prevNode = head;
        if (prevNode->next)
        {
            min_pq.push(prevNode->next);
        }

        while (!min_pq.empty())
        {
            ListNode* curNode = min_pq.top();
            min_pq.pop();
            prevNode->next = curNode;

            if (curNode->next)
            {
                min_pq.push(curNode->next);
            }

            prevNode = curNode;
        }

        return head;
    }
private:
    struct Comp
    {
        bool operator ()(const ListNode* lhs, const ListNode* rhs)
        {
            return rhs->val < lhs->val;
        }
    };

    // min priority queue
    typedef priority_queue<ListNode*, vector<ListNode*>, Comp> MinPQ;
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
    int arr0[] = {1,45,67};
    int arr1[] = {0,46,60};
    int arr2[] = {34};

    vector<int> vec0(arr0, arr0+sizeof(arr0)/sizeof(arr0[0]));
    vector<int> vec1(arr1, arr1+sizeof(arr1)/sizeof(arr1[0]));
    vector<int> vec2(arr2, arr2+sizeof(arr2)/sizeof(arr2[0]));

    ListNode* head0 = create_list(vec0);
    ListNode* head1 = create_list(vec1);
    ListNode* head2 = create_list(vec2);

    vector<ListNode*> vecList;
    vecList.push_back(head0);
    vecList.push_back(head1);
    vecList.push_back(head2);

    Solution sln;
    ListNode* head = sln.mergeKLists(vecList);
    display_list(head);

    return 0;
}
