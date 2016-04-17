// https://oj.leetcode.com/problems/binary-tree-preorder-traversal/
// Date: Nov 10, 2014

#include <iostream>
#include <vector>
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
    // iterative traversal
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> vec;

        if (root == NULL)
        {
            return vec;
        }

        stack<TreeNode* > stk;
        stk.push(root);

        while (!stk.empty())
        {
            TreeNode* node = stk.top();
            stk.pop();
            vec.push_back(node->val);

            if (node->right)
            {
                stk.push(node->right);
            }
            if (node->left)
            {
                stk.push(node->left);
            }
        }

        return vec;
    }
};

TreeNode* create_binary_tree()
{
    TreeNode* root = new TreeNode(3);
    TreeNode* node = new TreeNode(9);
    root->left = node;
    node = new TreeNode(20);
    root->right = node;
    TreeNode* leftNode = new TreeNode(15);
    TreeNode* rightNode = new TreeNode(7);
    node->left = leftNode;
    node->right = rightNode;

    return root;
}

int main(int argc, char* argv[])
{
    TreeNode* root = create_binary_tree();
    Solution sln;
    vector<int> vec = sln.preorderTraversal(root);
    return 0;
}
