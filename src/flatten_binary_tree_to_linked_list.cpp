// https://oj.leetcode.com/problems/flatten-binary-tree-to-linked-list/
// Date: Nov 21, 2014

#include <iostream>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    void flatten(TreeNode *root)
    {
        //experiment
        //root->left = NULL;
        //return;

        if (root == NULL)
        {
            return;
        }
        //TreeNode* newRoot = new TreeNode(root->val);
        //TreeNode* prevNode = newRoot;
        TreeNode* prevNode = root;
        stack<TreeNode*> stk;

        if (root->right)
        {
            stk.push(root->right);
            root->right = NULL;
        }
        if (root->left)
        {
            stk.push(root->left);
            root->left = NULL;
        }

        while (!stk.empty())
        {
            TreeNode* topNode = stk.top();
            stk.pop();

            /*
            TreeNode* newNode = new TreeNode(topNode->val);
            prevNode->right = newNode;
            prevNode = newNode;
            */

            if (topNode->right)
            {
                stk.push(topNode->right);
                topNode->right = NULL;
            }
            if (topNode->left)
            {
                stk.push(topNode->left);
                topNode->left = NULL;
            }

            prevNode->right = topNode;
            prevNode = topNode;
        }

        //root = &*newRoot;
        int gh = 0;
    }
};

TreeNode* create_binary_tree()
{
    TreeNode* root = new TreeNode(1);
    TreeNode* node = new TreeNode(2);
    root->left = node;

    TreeNode* leftNode = new TreeNode(3);
    TreeNode* rightNode = new TreeNode(4);
    node->left = leftNode;
    node->right = rightNode;

    node = new TreeNode(5);
    root->right = node;
    rightNode = new TreeNode(6);
    node->right = rightNode;

    return root;
}

int main(int argc, char* argv[])
{
    TreeNode* root = create_binary_tree();
    Solution sln;
    sln.flatten(root);
    return 0;
}

/*
  NU: understand why "root = newRoot;" doesn't works as we come out of the function.
  Check if this helps:
  http://stackoverflow.com/questions/416162/assignment-inside-function-that-is-passed-as-pointer
*/
