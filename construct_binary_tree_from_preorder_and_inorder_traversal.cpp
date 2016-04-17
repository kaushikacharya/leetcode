// https://oj.leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
// Date: Nov 14, 2014

#include <iostream>
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
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.empty())
        {
            return NULL;
        }
        preorder_ = preorder;
        inorder_ = inorder;

        return build_sub_tree(0, preorder.size()-1, 0, inorder.size()-1);
    }
private:
    vector<int> preorder_, inorder_;
private:
    TreeNode* build_sub_tree(int pre_i, int pre_j, int in_i, int in_j)
    {
        TreeNode* root = new TreeNode(preorder_[pre_i]);

        // Now get the position of this root node in in-order vector
        int pos_root_inorder = in_i;
        while (pos_root_inorder <= in_j)
        {
            if (inorder_[pos_root_inorder] == preorder_[pre_i])
            {
                break;
            }
            else
            {
                ++pos_root_inorder;
            }
        }

        int diff = pos_root_inorder - in_i;
        if (in_i < pos_root_inorder)
        {
            // left sub-tree
            root->left = build_sub_tree(pre_i+1, pre_i+diff, in_i, pos_root_inorder-1);
        }
        if (pos_root_inorder < in_j)
        {
            // right sub-tree
            root->right = build_sub_tree(pre_i+diff+1, pre_j, pos_root_inorder+1, in_j);
        }

        return root;
    }
};

void test_vector(vector<int>& preOrder)
{
    vector<int> vec = preOrder;
    cout << vec[3] << endl;
}

int main(int argc, char* argv[])
{
    vector<int> preOrder = {1, 2, 4, 5, 3, 6, 7};
    vector<int> inOrder = {4, 2, 5, 1, 6, 3, 7};
    //test_vector(preOrder);
    Solution sln;
    TreeNode* root = sln.buildTree(preOrder, inOrder);
    return 0;
}
