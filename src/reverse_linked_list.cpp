/*  Problem: https://leetcode.com/problems/reverse-linked-list/
    Date: Feb 13, 2023

    Approach:
    --------
    Iterative
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

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prevNode = nullptr;
        ListNode* curNode = head;

        /* Iterate over the nodes. Change the next pointer to the previous node.
            Prior to that store the original next node which wouild be set as the current node for next iteration. 
        */
        while (curNode)
        {
            ListNode* tempNode = curNode->next;
            curNode->next = prevNode;
            prevNode = curNode;
            curNode = tempNode;
        }

        return prevNode; 
    }
};

const lest::test tests[] = {
    {CASE("Five nodes"){
        vector<int> v = {1,2,3,4,5};
        ListNode* head = create_linked_list(v);
        Solution sln;
        vector<int> v_reverse_truth = {5,4,3,2,1};
        EXPECT(create_vector(sln.reverseList(head)) == v_reverse_truth);
    }},
    {CASE("Empty list"){
        vector<int> v = {};
        ListNode* head = create_linked_list(v);
        Solution sln;
        vector<int> v_reverse_truth = {};
        EXPECT(create_vector(sln.reverseList(head)) == v_reverse_truth);
    }}
};

int main(int argc, char** argv)
{
    lest::run(tests, argc, argv);
}
