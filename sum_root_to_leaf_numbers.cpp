// https://oj.leetcode.com/problems/sum-root-to-leaf-numbers/
// Date: Nov 11, 2014

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
    int sumNumbers(TreeNode *root)
    {
        int sum = 0;

        if (root == NULL)
        {
            return sum;
        }

        // DFS traversal
        stack<pair<TreeNode*, int> > stk;
        stk.push(make_pair(root, root->val));

        while (!stk.empty())
        {
            pair<TreeNode*,int> elem = stk.top();
            stk.pop();

            TreeNode* node = elem.first;
            int sum_in_path = elem.second;

            if ((node->left == NULL) & (node->right == NULL))
            {
                // leaf node
                sum += sum_in_path;
            }
            else
            {
                if (node->right)
                {
                    stk.push(make_pair(node->right, sum_in_path*10 + node->right->val));
                }
                if (node->left)
                {
                    stk.push(make_pair(node->left, sum_in_path*10 + node->left->val));
                }
            }
        }

        return sum;
    }
};

TreeNode* create_binary_tree()
{
    TreeNode* root = new TreeNode(3);
    TreeNode* node = new TreeNode(9);
    root->left = node;
    node = new TreeNode(2);
    root->right = node;
    TreeNode* leftNode = new TreeNode(1);
    TreeNode* rightNode = new TreeNode(7);
    node->left = leftNode;
    node->right = rightNode;

    return root;
}

int main(int argc, char* argv[])
{
    TreeNode* root = create_binary_tree();
    Solution sln;
    int sum = sln.sumNumbers(root);

    return 0;
}
