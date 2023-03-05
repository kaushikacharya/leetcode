/*  Problem: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
    Statement: Given the head of a linked list, remove the nth node from the end of the list and return its head.
    Date: March 05, 2023\
    Approach: Two pointers (a fast one and a slow one).
                If we maintain a difference of n nodes between the two pointers,
                 then as fast pointer reaches the end of the linked list (i.e. null), the slow pointer would be at the target node.
    Time complexity: O(n) (Single iteration over the linked list)
    Space complexity: O(1) (No additional space)
*/

#include <bits/stdc++.h>
#include <lest.hpp>

using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr) {}
    ListNode(int x): val(x), next(nullptr) {}
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Initialize the slow and fast pointer:
        //  fast pointer should be n nodes ahead of slow pointer.
        ListNode* slowNode = head;
        ListNode* fastNode = head;

        int i = 0;
        while (i < n)
        {
            fastNode = fastNode->next;
            ++i;
        }

        /*
        Case: n = length of linked list
        In this special case, positions of the slow and fast pointers:
            - slow pointer: head of the linked list
            - fast pointer: end of the linked list (i.e. null)
        Hence slow pointer is at the target node.
        Thus we need to make its next node as the head of the linked list and remove the target node.
        */
        if (fastNode == nullptr)
        {
            ListNode* tempNode = head;
            head = head->next;
            delete tempNode;
            return head;
        }

        /* As fastNode reaches end of the list, slowNode would be the nth node from the end of the list.
            As we remove the target node, we need to ensure that its previous node is linked to target node's next node,
            so that the linked list chain is maintained.
            To achieve this, we stop the slow pointer at the target node's previous node.
        */
        while (fastNode->next != nullptr)
        {
            // Move both the pointers one step
            fastNode = fastNode->next;
            slowNode = slowNode->next;
        }

        ListNode* tempNode = slowNode->next;
        slowNode->next = slowNode->next->next;
        delete tempNode;
        return head;
    }
};

ListNode* create_linked_list(vector<int> vec)
{
    ListNode* head = nullptr;
    ListNode* prevNode = nullptr;

    for (auto it=vec.begin(); it != vec.end(); ++it)
    {
        ListNode* node = new ListNode(*it);

        if (it == vec.begin())
        {
            head = node;
        }
        else
        {
            prevNode->next = node;
        }

        // Update prevNode to the current node for the next iteration
        prevNode = node;
    }

    return head;
}

vector<int> create_vector(ListNode* head)
{
    vector<int> vec;
    ListNode* node = head;

    while (node)
    {
        vec.push_back(node->val);
        node = node->next;
    }
    
    return vec;
}

lest::test tests[] = {
    CASE("Test Case #1"){
        vector<int> vec = {1,2,3,4,5};
        ListNode* head = create_linked_list(vec);
        int n = 2;
        vector<int> vec_post_removal = {1,2,3,5};
        Solution sln;
        EXPECT(create_vector(sln.removeNthFromEnd(head, n)) == vec_post_removal);
    },
    CASE("Test Case #2"){
        vector<int> vec = {1,2,3,4,5};
        ListNode* head = create_linked_list(vec);
        int n = 1;
        vector<int> vec_post_removal = {1,2,3,4};
        Solution sln;
        EXPECT(create_vector(sln.removeNthFromEnd(head, n)) == vec_post_removal);
    },
    CASE("Test Case #3"){
        vector<int> vec = {1,2,3,4,5};
        ListNode* head = create_linked_list(vec);
        int n = 5;
        vector<int> vec_post_removal = {2,3,4,5};
        Solution sln;
        EXPECT(create_vector(sln.removeNthFromEnd(head, n)) == vec_post_removal);
    },
    CASE("Test Case #4"){
        vector<int> vec = {1};
        ListNode* head = create_linked_list(vec);
        int n = 1;
        vector<int> vec_post_removal = {};
        Solution sln;
        EXPECT(create_vector(sln.removeNthFromEnd(head, n)) == vec_post_removal);
    },
};

int main(int argc, char** argv)
{
    lest::run(tests, argc, argv);
}
