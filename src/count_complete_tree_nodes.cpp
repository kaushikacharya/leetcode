// https://leetcode.com/problems/count-complete-tree-nodes/
// June 13, 2016

#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(NULL),right(NULL){}
};

class Solution {
public:
    int countNodes(TreeNode* root)
    {
        if (root == NULL)
        {
            return 0;
        }
        compute_tree_height(root);
        // count nodes at lowest level
        int count_nodes_at_lowest_level = 0;
        countNodesAtLowestLevel(root, 0, count_nodes_at_lowest_level);

        // Compute the total number of nodes in the complete tree
        int count_internal_nodes = 0;
        if (height_ > 0)
        {
            int n_nodes_at_current_level = 1;
            count_internal_nodes += n_nodes_at_current_level;
            for (int i=1; i != height_; ++i)
            {
                n_nodes_at_current_level *= 2;
                count_internal_nodes += n_nodes_at_current_level;
            }
        }

        int count_nodes = count_internal_nodes + count_nodes_at_lowest_level;
        return count_nodes;
    }
private:
    void countNodesAtLowestLevel(TreeNode* node, int curLevel, int& count_nodes)
    {
        if (node == NULL)
        {
            // case: node's parent has only left child
            return;
        }
        if (node->left == NULL)
        {
            // Either we have reached rightmost leaf node of perfect tree OR
            // An internal node which doesn't have any child
            if (curLevel == height_)
            {
                ++count_nodes; // rightmost leaf node of perfect tree
            }
            return;
        }

        bool is_left_subtree_perfect = is_perfect_tree(node->left, curLevel+1);

        if (is_left_subtree_perfect)
        {
            // Add number of leaves in left subtree to count_nodes
            int count_leaves_left_subtree = 1;
            for (int i=0; i != (height_-(curLevel+1)); ++i)
            {
                count_leaves_left_subtree *= 2;
            }
            count_nodes += count_leaves_left_subtree;
            countNodesAtLowestLevel(node->right, curLevel+1, count_nodes);
        }
        else
        {
            countNodesAtLowestLevel(node->left, curLevel+1, count_nodes);
        }
    }

    // Checks if the subtree with root is a perfect tree or not
    bool is_perfect_tree(TreeNode* root, int curLevel)
    {
        TreeNode* node = root->right;
        while (node)
        {
            ++curLevel;
            node = node->right;
        }

        return (curLevel == height_);
    }

    void compute_tree_height(TreeNode* root)
    {
        height_ = 0;
        TreeNode* node = root->left;
        while (node)
        {
            ++height_;
            node = node->left;
        }
    }
private:
    int height_; // Height of tree considering root at height=0
};

TreeNode* create_complete_binary_tree()
{
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);
    TreeNode* node7 = new TreeNode(7);

    // node1->left = node2;
    // node1->right = node3;
    /*
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;
    */

    return node1;
}

int main(int argc, char* argv[])
{
    Solution sln;
    TreeNode* root = create_complete_binary_tree();
    int n_nodes = sln.countNodes(root);
    cout << "number of nodes: " << n_nodes << endl;
    return 0;
}
