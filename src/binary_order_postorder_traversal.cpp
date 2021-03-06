// https://oj.leetcode.com/problems/binary-tree-postorder-traversal/
// Date: Nov 15, 2014

#include <iostream>
#include <stack>
#include <vector>

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
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> vec;
        if (root == NULL)
        {
            return vec;
        }

        stack<pair<TreeNode*, int> > stk;
        stk.push(make_pair(root,0));

        while (!stk.empty())
        {
            pair<TreeNode*,int> elem = stk.top();
            stk.pop();
            TreeNode* node = elem.first;
            int cnt = elem.second;

            if (cnt == 0)
            {
                if ( (node->left == NULL) & (node->right == NULL) )
                {
                    vec.push_back(node->val);
                }
                else
                {
                    stk.push(make_pair(node,1));
                    if (node->right)
                    {
                        stk.push(make_pair(node->right,0));
                    }
                    if (node->left)
                    {
                        stk.push(make_pair(node->left,0));
                    }
                }
            }
            else
            {
                // left and right subtree nodes have been appended in vec
                vec.push_back(node->val);
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
    vector<int> vec = sln.postorderTraversal(root);
    return 0;
}
