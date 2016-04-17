// https://oj.leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
// Date: Nov 10, 2014

#include <iostream>
#include <stack>
#include <utility>
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
    vector<vector<int> > zigzagLevelOrder(TreeNode *root)
    {
        vector<vector<int> > vec;

        if (root == NULL)
        {
            return vec;
        }
        stack<TreeNode*> stk1, stk2;

        // push children in the order (left,right) in one stack and reverse in another stack

        int level;
        stk1.push(root);
        while (!stk1.empty())
        {
            level = vec.size();
            vec.push_back(vector<int>());

            while(!stk1.empty())
            {
                TreeNode* node = stk1.top();
                stk1.pop();
                vec[level].push_back(node->val);

                if (node->left)
                {
                    stk2.push(node->left);
                }
                if (node->right)
                {
                    stk2.push(node->right);
                }
            }

            if (!stk2.empty())
            {
                level = vec.size();
                vec.push_back(vector<int>());

                while (!stk2.empty())
                {
                    TreeNode* node = stk2.top();
                    stk2.pop();
                    vec[level].push_back(node->val);

                    if (node->right)
                    {
                        stk1.push(node->right);
                    }
                    if (node->left)
                    {
                        stk1.push(node->left);
                    }
                }
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
    vector<vector<int> > vec = sln.zigzagLevelOrder(root);

    return 0;
}
