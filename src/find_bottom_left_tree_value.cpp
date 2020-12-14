// https://leetcode.com/problems/find-bottom-left-tree-value/?tab=Description
// Mar 04, 2017

#include <iostream>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    int findBottomLeftValue(TreeNode* root)
    {
        TreeNode* leftNode = NULL;
        int prevLayer = -1;

        // BFS traversal
        queue<pair<TreeNode*,int> > Q;
        Q.push(make_pair(root,0));

        while (!Q.empty())
        {
            pair<TreeNode*,int> elem = Q.front();
            Q.pop();
            TreeNode* node = elem.first;
            int curLayer = elem.second;

            if (curLayer != prevLayer)
            {
                // leftmost element of the curLayer
                leftNode = node;
                prevLayer = curLayer;
            }

            if (node->left)
            {
                Q.push(make_pair(node->left, curLayer+1));
            }
            if (node->right)
            {
                Q.push(make_pair(node->right, curLayer+1));
            }
        }

        return leftNode->val;
    }
};

int main(int argc, char* argv[])
{
    int test_case = 2;

    switch (test_case)
    {
        case 1:
            {
                TreeNode* node1 = new TreeNode(1);
                TreeNode* node2 = new TreeNode(2);
                TreeNode* node3 = new TreeNode(3);

                node2->left = node1;
                node2->right = node3;

                Solution sln;
                int leftVal = sln.findBottomLeftValue(node2);
                cout << "left val: " << leftVal << endl;
                break;
            }

        case 2:
            {
                TreeNode* node1 = new TreeNode(1);
                TreeNode* node2 = new TreeNode(2);
                TreeNode* node3 = new TreeNode(3);
                TreeNode* node4 = new TreeNode(4);
                TreeNode* node5 = new TreeNode(5);
                TreeNode* node6 = new TreeNode(6);
                TreeNode* node7 = new TreeNode(7);

                node1->left = node2;
                node1->right = node3;
                node2->left = node4;
                node3->left = node5;
                node3->right = node6;
                node5->left = node7;

                Solution sln;
                int leftVal = sln.findBottomLeftValue(node1);
                cout << "left val: " << leftVal << endl;
                break;
            }
    }


    return 0;
}
