// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
// Apr 20, 2016
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x):val(x), next(NULL){};
};

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){};
};

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        create_vec_treenode(head);
        TreeNode* root = populate_BST();
        return root;
    }
private:
    // traverse list and populate vector of tree nodes
    void create_vec_treenode(ListNode* head){
        ListNode* curListNode = head;
        while(curListNode != NULL)
        {
            TreeNode* curTreeNode = new TreeNode(curListNode->val);
            vecTreeNode_.push_back(curTreeNode);
            curListNode = curListNode->next;
        }
    }

    // create a height balanced BST
    TreeNode* populate_BST()
    {
        if (vecTreeNode_.empty())
        {
            return NULL;
        }

        // Push the mid element of the vector of tree nodes into stack
        int left_index = 0;
        int right_index = vecTreeNode_.size()-1;
        int mid_index = (left_index + right_index)/2;
        TreeInfo rootInfo = TreeInfo(mid_index, left_index, right_index);
        stk_.push(rootInfo);

        // we will traverse in a way similar to pre-order traversal of tree
        while (!stk_.empty())
        {
            TreeInfo curNodeInfo = stk_.top();
            stk_.pop();

            // a. Identify the root of left and right subtree
            // b. Assign left and right fields of current tree node to these roots respectively
            // c. Put in stack the corresponding node info for the root of subtrees in (a)

            //  These define the subtree rooted as current node
            int curIndex = curNodeInfo.index;
            int left_index = curNodeInfo.leftIndex;
            int right_index = curNodeInfo.rightIndex;

            TreeNode* curNode = vecTreeNode_[curIndex];

            if (curIndex < right_index)
            {
                // assigning right field of curNode
                mid_index = (curIndex + 1 + right_index)/2;
                TreeNode* rightNode = vecTreeNode_[mid_index];
                curNode->right = rightNode;

                // push right subtree info into stack
                TreeInfo rightInfo = TreeInfo(mid_index, curIndex+1, right_index);
                stk_.push(rightInfo);
            }

            if (left_index < curIndex)
            {
                // assigning left field of curNode
                mid_index = (left_index + curIndex - 1)/2;
                TreeNode* leftNode = vecTreeNode_[mid_index];
                curNode->left = leftNode;

                // push left subtree info into stack
                TreeInfo leftInfo = TreeInfo(mid_index, left_index, curIndex-1);
                stk_.push(leftInfo);
            }
        }

        mid_index = (0 + vecTreeNode_.size() - 1)/2;
        TreeNode* root = vecTreeNode_[mid_index];
        return root;
    }
private:
    struct TreeInfo
    {
        int index; // represents index in vecTreeNode_
        int leftIndex;
        int rightIndex;
        TreeInfo(int i, int l, int r): index(i), leftIndex(l), rightIndex(r){};
    };
private:
    vector<TreeNode*> vecTreeNode_;
    stack<TreeInfo> stk_;
};

ListNode* create_sorted_list(int n)
{
    ListNode* prevNode = NULL;
    ListNode* curNode = NULL;

    stack<int> stk;
    for (int i=0; i != n; ++i)
    {
        stk.push(i);
    }

    while (!stk.empty())
    {
        int i = stk.top();
        stk.pop();
        curNode = new ListNode(i);
        curNode->next = prevNode;
        prevNode = curNode;
    }

    ListNode* head = curNode;
    return head;
}

int main(int argc, char* argv[])
{
    int n = 7;
    ListNode* head = create_sorted_list(n);
    Solution sln;
    TreeNode* root = sln.sortedListToBST(head);
    return 0;
}

/*
http://www.geeksforgeeks.org/sorted-linked-list-to-balanced-bst/

My method: O(n) time complexity as well as O(n) memory
Constructed tree from root to leaves.
TBD: Try leaves to root method.
*/
