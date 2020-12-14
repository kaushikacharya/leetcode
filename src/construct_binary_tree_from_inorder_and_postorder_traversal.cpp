// https://oj.leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
// Date: Nov 16, 2014

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
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        inorder_ = inorder;
        postorder_ = postorder;

        if (inorder.empty())
        {
            return NULL;
        }

        return build_tree(0, inorder.size()-1, 0, postorder.size()-1);
    }
private:
    vector<int> inorder_, postorder_;
private:
    TreeNode* build_tree(int in_i, int in_j, int po_i, int po_j)
    {
        TreeNode* node = new TreeNode(postorder_[po_j]);

        // get the position of root of this subtree in inorder vec
        int pos_root = in_i;
        while (pos_root <= in_j)
        {
            if (inorder_[pos_root] == node->val)
            {
                break;
            }
            else
            {
                ++pos_root;
            }
        }

        int diff = pos_root - in_i;

        if (in_i < pos_root)
        {
            node->left = build_tree(in_i, pos_root-1, po_i, po_i+diff-1);
        }
        if (pos_root < in_j)
        {
            node->right = build_tree(pos_root+1, in_j, po_i+diff, po_j-1);
        }

        return node;
    }

};

int main(int argc, char* argv[])
{
    int inorder_arr[] = {4, 2, 5, 1, 6, 3, 7};
    vector<int> inorder_vec(inorder_arr, inorder_arr + sizeof(inorder_arr)/sizeof(inorder_arr[0]));
    int postorder_arr[] = {4, 5, 2, 6, 7, 3, 1};
    vector<int> postorder_vec(postorder_arr, postorder_arr + sizeof(postorder_arr)/sizeof(postorder_arr[0]));

    Solution sln;
    TreeNode* root = sln.buildTree(inorder_vec, postorder_vec);
    return 0;
}
