// https://oj.leetcode.com/problems/validate-binary-search-tree/
// Date: Nov 11, 2014

#include <iostream>
#include <tuple>

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
    bool isValidBST(TreeNode *root)
    {
        if (root == NULL)
        {
            return true;
        }
        tuple<bool,int,int> treeValues = checkBST(root);
        return get<0>(treeValues);
    }
private:
    // recursive validation of BST
    // output: <bool, min, max>
    tuple<bool,int,int> checkBST(TreeNode* root)
    {
        if ((root->left == NULL) & (root->right == NULL)) // leaf node
        {
            return make_tuple(true, root->val, root->val);
        }

        bool flagValidBST = true;
        int minSubTree = root->val;
        int maxSubTree = root->val;

        if (root->left)
        {
            tuple<bool,int,int> leftSubTreeValues = checkBST(root->left);

            flagValidBST = get<0>(leftSubTreeValues);
            int minLeftSubTree = get<1>(leftSubTreeValues);
            int maxLeftSubTree = get<2>(leftSubTreeValues);

            if (flagValidBST)
            {
                if (root->val <= maxLeftSubTree)
                {
                    flagValidBST = false;
                }
                else
                {
                    minSubTree = minLeftSubTree;
                }
            }
        }

        if ((root->right != NULL) & flagValidBST)
        {
            tuple<bool,int,int> rightSubTreeValues = checkBST(root->right);

            flagValidBST = get<0>(rightSubTreeValues);
            int minRightSubTree = get<1>(rightSubTreeValues);
            int maxRightSubTree = get<2>(rightSubTreeValues);

            if (flagValidBST)
            {
                if (minRightSubTree <= root->val)
                {
                    flagValidBST = false;
                }
                else
                {
                    maxSubTree = maxRightSubTree;
                }
            }
        }

        return make_tuple(flagValidBST, minSubTree, maxSubTree);
    }
};

TreeNode* create_binary_tree()
{
    TreeNode* root = new TreeNode(9);
    TreeNode* node = new TreeNode(3);
    root->left = node;
    node = new TreeNode(20);
    root->right = node;
    TreeNode* leftNode = new TreeNode(8);
    TreeNode* rightNode = new TreeNode(27);
    node->left = leftNode;
    node->right = rightNode;

    return root;
}


int main(int argc, char* argv[])
{
    TreeNode* root = create_binary_tree();
    Solution sln;
    bool flagValidBST = sln.isValidBST(root);

    return 0;
}

/*
http://stackoverflow.com/questions/17767546/compiler-option-not-working-for-unordered-set-c11-feature
*/
