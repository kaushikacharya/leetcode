// https://oj.leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
// Date: Nov 10, 2014

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
    TreeNode *sortedArrayToBST(vector<int>& vec)
    {
        if (vec.empty())
        {
            return NULL;
        }

        TreeNode* root = create_BST(vec, 0, vec.size()-1);
        return root;
    }
private:
    TreeNode* create_BST(vector<int>& vec, int i, int j)
    {
        int mid = (i +j)/2;
        TreeNode* root = new TreeNode(vec[mid]);

        if (i < mid)
        {
            TreeNode* leftNode = create_BST(vec, i, mid-1);
            root->left = leftNode;
        }
        if (mid < j)
        {
            TreeNode* rightNode = create_BST(vec, mid+1, j);
            root->right = rightNode;
        }

        return root;
    }
};

int main(int argc, char* argv[])
{
    int arr[] = {5,7,8,10,15,20,23};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    Solution sln;
    TreeNode* root = sln.sortedArrayToBST(vec);

    return 0;
}
