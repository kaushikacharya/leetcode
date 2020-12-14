// https://oj.leetcode.com/problems/binary-tree-level-order-traversal/
// Date: Nov 09, 2014

#include <iostream>
#include <queue>
#include <utility>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};

class Solution
{
public:
    std::vector<std::vector<int> > levelOrder(TreeNode *root)
    {
        std::vector<std::vector<int> > vec;

        if (root == NULL)
        {
            return vec;
        }

        std::queue<std::pair<TreeNode*, int> > Q; // pair of (node, node level)
        Q.push(std::make_pair(root, 0));

        while (!Q.empty())
        {
            std::pair<TreeNode*, int> elem = Q.front();
            Q.pop();
            TreeNode* node = elem.first;
            int level = elem.second;

            // add the element in vec according to its level
            if (vec.size() == level)
            {
                // adding first element from this level
                vec.push_back(std::vector<int>());
            }
            vec[level].push_back(node->val);

            if (node->left)
            {
                Q.push(std::make_pair(node->left, level+1));
            }
            if (node->right)
            {
                Q.push(std::make_pair(node->right, level+1));
            }
        }

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

std::vector<std::vector<int> > test_vector()
{
    std::vector<std::vector<int> > vec;

    /*
    [
        [3],
        [9,20],
        [15,7]
    ]
    */
    vec.push_back(std::vector<int>());
    vec[0].push_back(3);

    vec.push_back(std::vector<int>());
    vec[1].push_back(9);
    vec[1].push_back(20);
    int gh = 0;

    return vec;
}

int main(int argc, char* argv[])
{
    // std::vector<std::vector<int> > vec = test_vector();

    TreeNode* root = create_binary_tree();
    Solution sln;
    std::vector<std::vector<int> > vec = sln.levelOrder(root);

    return 0;
}
