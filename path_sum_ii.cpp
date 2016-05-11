// https://leetcode.com/problems/path-sum-ii/
// May 11, 2016

#include <iostream>
#include <stack>
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
    vector<vector<int> > pathSum(TreeNode* root, int sum)
    {
        vector<vector<int> > vecPath;

        if (root == NULL)
        {
            return vecPath;
        }

        stack<pair<TreeNode*,int> > stk;
        stack<TreeNode*> stkPath; // This contains the nodes in the current path
        int sumPath = 0;

        stk.push(make_pair(root,1));

        while (!stk.empty())
        {
            pair<TreeNode*,int> elem = stk.top();
            stk.pop();
            TreeNode* node = elem.first;
            int level = elem.second;

            // remove the nodes from stkPath which are not in the current path
            while (stkPath.size() >= level)
            {
                TreeNode* nodeInPrevPath = stkPath.top();
                stkPath.pop();
                sumPath -= nodeInPrevPath->val;
            }
            // Add the node in stkPath
            stkPath.push(node);
            sumPath += node->val;

            if ((node->left == NULL) && (node->right == NULL))
            {
                // leaf node
                // Check if the sum of this path is same as input sum
                if (sumPath == sum)
                {
                    // Now create path vector from stkPath
                    stack<TreeNode*> stkTemp;
                    while(!stkPath.empty())
                    {
                        TreeNode* nodePath = stkPath.top();
                        stkPath.pop();
                        stkTemp.push(nodePath);
                    }
                    vector<int> path;
                    while(!stkTemp.empty())
                    {
                        TreeNode* nodePath = stkTemp.top();
                        stkTemp.pop();
                        stkPath.push(nodePath);
                        path.push_back(nodePath->val);
                    }
                    vecPath.push_back(path);
                }
            }
            else
            {
                if (node->right)
                {
                    stk.push(make_pair(node->right, level+1));
                }
                if (node->left)
                {
                    stk.push(make_pair(node->left, level+1));
                }
            }

        }

        return vecPath;
    }
};

TreeNode* create_tree()
{
    TreeNode* node1 = new TreeNode(5);
    TreeNode* node2 = new TreeNode(4);
    TreeNode* node3 = new TreeNode(8);
    TreeNode* node4 = new TreeNode(11);
    TreeNode* node5 = new TreeNode(13);
    TreeNode* node6 = new TreeNode(7);

    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node3->left = node5;
    node3->right = node6;

    return node1;
}


int main(int argc, char* argv[])
{
    TreeNode* root = create_tree();
    int sum = 20;
    Solution sln;
    vector<vector<int> > vecPath = sln.pathSum(root, sum);

    cout << "Paths: " << endl;
    for (unsigned int path_i = 0; path_i != vecPath.size(); ++path_i)
    {
        cout << "path #" << path_i << " : ";
        for (vector<int>::iterator it = vecPath[path_i].begin(); it != vecPath[path_i].end(); ++it)
        {
            cout << " " << *it;
        }
        cout << endl;
    }
    return 0;
}
