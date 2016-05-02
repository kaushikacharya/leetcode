// https://leetcode.com/problems/binary-tree-right-side-view/
// Apr 30, 2016

#include <iostream>
#include <queue>
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
    vector<int> rightSideView(TreeNode* root)
    {
        vector<int> vecRightSideView;

        if (root == NULL)
        {
            return vecRightSideView;
        }

        int prev_level = 0;
        TreeNode* node_rightmost_at_prev_level = root;

        queue<pair<TreeNode*, int> > q;
        q.push(make_pair(root,0));

        while (!q.empty())
        {
            pair<TreeNode*, int> elem = q.front();
            q.pop();
            TreeNode* node = elem.first;
            int cur_level = elem.second;

            if (cur_level > prev_level)
            {
                vecRightSideView.push_back(node_rightmost_at_prev_level->val);
            }

            node_rightmost_at_prev_level = node;
            prev_level = cur_level;

            if (node->left)
            {
                q.push(make_pair(node->left, cur_level+1));
            }
            if (node->right)
            {
                q.push(make_pair(node->right, cur_level+1));
            }
        }

        // append the right most node at the lowest level
        vecRightSideView.push_back(node_rightmost_at_prev_level->val);

        return vecRightSideView;
    }
};

TreeNode* create_tree1()
{
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);

    node3->right = node4;
    node2->right = node5;
    node1->left = node2;
    node1->right = node3;

    return node1;
}

TreeNode* create_tree2()
{
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    node1->right = node2;

    return node1;
}

TreeNode* create_tree3()
{
    TreeNode* node1 = new TreeNode(1);
    return node1;
}

int main(int argc, char* argv[])
{
    TreeNode* root = create_tree3();
    Solution sln;
    vector<int> vec_right_side_view = sln.rightSideView(root);

    for (vector<int>::iterator it = vec_right_side_view.begin(); it != vec_right_side_view.end(); ++it)
    {
        cout << *it << " ";
    }

    return 0;
}
