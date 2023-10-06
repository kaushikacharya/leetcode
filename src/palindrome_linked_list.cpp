/*
    Problem: https://leetcode.com/problems/palindrome-linked-list/
    Date: Feb 11, 2023

    Approaches:
    ----------
    Solution #1: Push the elements of 1st half into stack.
                Pop the elements from the stack one by one and match with the elements of the 2nd half of the linked list.
                    
                Time complexity: O(n)
                Space complexity: O(n)

    Solution #2: In-place reverse 2nd half of linked list.
                    Iterate both half of linked list and simultaenously compare the values.
*/

#include <lest.hpp>
#include <bits/stdc++.h>

using namespace std;

struct  ListNode
{
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr){}
    ListNode(int x): val(x), next(nullptr){}
    ListNode(int x, ListNode* next): val(x), next(next){}
};

ListNode* create_linked_list(vector<int> vec)
{
    ListNode* head = NULL;

    if (vec.empty())
    {
        return head;
    }

    head = new ListNode(vec[0]);
    ListNode* node = head;

    for (vector<int>::iterator it = vec.begin()+1; it != vec.end(); ++it)
    {
        node->next = new ListNode(*it);
        node = node->next;
    }

    return head;
}

class Solution {
public:
    // Solution #1
    bool isPalindromeSolution1(ListNode* head) {
        // Special case: Single node linked list
        // N.B. Constraint mentioned in the problem statement says that at least there's a single node.
        if (head->next == nullptr){
            return true;
        }

        /*  Step 1: Partition the list into two halves: first half and second half.
                    a. This would require a walkthrough of the entire linked list to identify the length of the list.
                    b. Based on the length of the list identify the range of the two partitions.
                        N.B. For odd length, middle element of the list would not be part of either halves.
            Step 2: Push the elements of the 1st half into a stack.
            Step 3: Simultaneously pop elements of the stack and iterate over the 2nd half.
                    At every step, check whether the values of both the elements are same or not.
                    If not same, that would mean that the list is not a palindrome.
                    If it is same till the end, that would mean that the list is a palindrome.
        */
       ListNode* node = head;
       unsigned int n = 0;

       while (node != nullptr)
       {
            ++n;
            node = node->next;
       }
       
       // Step 2
       node = head;
       unsigned int i = 0;
       stack<int> stk;

       while (i < n/2)
       {
            stk.push(node->val);
            // Move the pointer to the next element
            node = node->next;
            ++i; 
       }

       // Move to the head of the 2nd half of the linked list.
       // For even length list, 2nd half starts immediately after the end of 1st half.
       // For odd length list, 2nd half starts after skipping 1 element after the end of the 1st half.
       while (i < (n+1)/2)
       {
            node = node->next;
            ++i;
       }
       
       // Step 3
        while (node != nullptr)
        {
            assert(!stk.empty() && "imbalanced two halves of the linked list: 2nd half longer than 1st half");
            int cur_top_val = stk.top();
            if (node->val != cur_top_val){
                return false;
            }
            stk.pop();
            node = node->next;
        }
        
       assert(stk.empty() && "imbalanced two halves of the linked list: 1st half longer than 2nd half");

       return true;
    }

    // Solution #2
    bool isPalindrome(ListNode* head) {
        // Step #1: Identify the beginning of the 2nd half of the linked list.
        // Maintain two pointers: slow and fast.
        // Slow one moves one node at a time.
        // Fast one moves two nodes at a time.
        ListNode* slow_ptr = head;
        ListNode* fast_ptr = head->next;

        while (fast_ptr)
        {
            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next;

            if (fast_ptr)
            {
                fast_ptr = fast_ptr->next;
            }
        }

        // Step #2: Reverse the 2nd half of the linked list.
        ListNode* curNode = slow_ptr;
        ListNode* prevNode = nullptr;

        while (curNode)
        {
            ListNode* tempNode = curNode->next;
            curNode->next = prevNode;
            prevNode = curNode;
            curNode = tempNode;
        }
        
        // Step #3: Simultaneously iterate both reversed 2nd half and the original list
        ListNode* cur_node_2nd_half = prevNode; // Head of the reversed 2nd half.
        ListNode* cur_node_1st_half = head;

        while (cur_node_2nd_half)
        {
            if (cur_node_1st_half->val != cur_node_2nd_half->val)
            {
                return false;
            }
            cur_node_1st_half = cur_node_1st_half->next;
            cur_node_2nd_half = cur_node_2nd_half->next;
        }

        return true;
    }
};

const lest::test tests[] = {
    {CASE("palindrome even elements"){
        vector<int> v = {1,2,2,1};
        ListNode* head = create_linked_list(v);
        Solution sln;
        EXPECT(sln.isPalindrome(head) == true);
    }},
    {CASE("non-palindrome even elements"){
        vector<int> v = {1,2};
        ListNode* head = create_linked_list(v);
        Solution sln;
        EXPECT(sln.isPalindrome(head) == false);
    }},
    {CASE("palindrome odd elements"){
        vector<int> v = {1,2,3,2,1};
        ListNode* head = create_linked_list(v);
        Solution sln;
        EXPECT(sln.isPalindrome(head) == true);
    }},
    {CASE("non-palindrome odd elements"){
        vector<int> v = {1,3,2};
        ListNode* head = create_linked_list(v);
        Solution sln;
        EXPECT(sln.isPalindrome(head) == false);
    }}
};

int main(int argc, char** argv){
    lest::run(tests, argc, argv);
}
