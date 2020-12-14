// https://oj.leetcode.com/problems/linked-list-cycle/
// Date: Nov 09, 2014

#include <iostream>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL) {}
};

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (head == NULL)
        {
            return false;
        }

        ListNode* h1 = head; // single step
        ListNode* h2 = head; // double step

        bool flag_cycle_present = false;
        while ((h2->next != NULL) && (h2->next->next != NULL))
        {
            h2 = h2->next;
            if (h2 == h1)
            {
                flag_cycle_present = true;
                break;
            }

            h2 = h2->next;
            if (h2 == h1)
            {
                flag_cycle_present = true;
                break;
            }

            h1 = h1->next;
        }

        return flag_cycle_present;
    }
};

int main(int argc, char* argv[])
{
    Solution sln;
    return 0;
}
