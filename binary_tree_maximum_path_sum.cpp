// https://oj.leetcode.com/problems/binary-tree-maximum-path-sum/
// Date: Nov 13, 2014

#include <iostream>
#include <limits>

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
    int maxPathSum(TreeNode *root)
    {
        max_path_sum_ = numeric_limits<int>::min();
        max_path_sum_downwards_from_node(root);

        return max_path_sum_;
    }
private:
    int max_path_sum_;
private:
    int max_path_sum_downwards_from_node(TreeNode* node)
    {
        if ((node->left == NULL) && (node->right == NULL))
        {
            // leaf node
            if (max_path_sum_ < node->val)
            {
                max_path_sum_ = node->val;
            }
            return node->val;
        }

        int left_subtree_val = numeric_limits<int>::min();
        if (node->left)
        {
            left_subtree_val = max_path_sum_downwards_from_node(node->left);
        }
        int right_subtree_val = numeric_limits<int>::min();
        if (node->right)
        {
            right_subtree_val = max_path_sum_downwards_from_node(node->right);
        }

        int max_path_sum = node->val;
        if (left_subtree_val > 0)
        {
            max_path_sum += left_subtree_val;
        }
        if (right_subtree_val > 0)
        {
            max_path_sum += right_subtree_val;
        }

        if (max_path_sum_ < max_path_sum)
        {
            max_path_sum_ = max_path_sum;
        }

        int max_subtree_val = max(left_subtree_val, right_subtree_val);

        if (max_subtree_val < 0)
        {
            return node->val;
        }
        else
        {
            return node->val + max_subtree_val;
        }
    }
};

TreeNode* create_binary_tree()
{
    TreeNode* root = new TreeNode(3);
    TreeNode* node = new TreeNode(13);
    root->left = node;
    node = new TreeNode(-20);
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
    int max_path_sum = sln.maxPathSum(root);
    return 0;
}
