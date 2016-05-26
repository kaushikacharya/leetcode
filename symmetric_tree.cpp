// https://leetcode.com/problems/symmetric-tree/
// May 21, 2016

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {};
};

class Solution {
public:
    bool isSymmetric(TreeNode* root)
    {
        if (root == NULL)
        {
            return true;
        }

        bool flag_symmetry = true;

        // As we do level order traversal, check for symmetry at that level
        queue<pair<TreeNode*,int> > q;
        q.push(make_pair(root,0));
        int prevLevel = 0;
        vector<TreeNode*> vecNodeAtLevel;
        while (!q.empty())
        {
            pair<TreeNode*,int> elem = q.front();
            q.pop();
            TreeNode* node = elem.first;
            int curLevel = elem.second;

            if (curLevel != prevLevel)
            {
                // level change
                // Check symmetry at prevLevel
                flag_symmetry = is_symmetry_at_level(vecNodeAtLevel);
                vecNodeAtLevel.clear();
                prevLevel = curLevel;
            }

            vecNodeAtLevel.push_back(node);

            if (!flag_symmetry)
            {
                break;
            }

            if (node)
            {
                // Push both child into queue even if they are NULL
                q.push(make_pair(node->left, curLevel+1));
                q.push(make_pair(node->right, curLevel+1));
            }
        }

        return flag_symmetry;
    }
private:
    bool is_symmetry_at_level(vector<TreeNode*> vecNodeAtLevel)
    {
        bool flag = true;

        if (vecNodeAtLevel.size() > 1)
        {
            if (vecNodeAtLevel.size() % 2 == 1)
            {
                return false; // odd number of nodes at given level
            }

            unsigned int sizeLevel = vecNodeAtLevel.size();
            for (unsigned int i = 0; i != vecNodeAtLevel.size()/2; ++i)
            {
                TreeNode* leftNode = vecNodeAtLevel[i];
                TreeNode* rightNode = vecNodeAtLevel[sizeLevel-1-i];

                if ((leftNode == NULL) && (rightNode))
                {
                    flag = false;
                }
                else if ( (leftNode) && (rightNode == NULL) )
                {
                    flag = false;
                }
                else if (leftNode && rightNode)
                {
                    if (leftNode->val != rightNode->val)
                    {
                        flag = false;
                    }
                }

                if (!flag)
                {
                    break;
                }
            }
        }

        return flag;
    }
};

TreeNode* create_tree()
{
    TreeNode* root = new TreeNode(1);
    TreeNode* node1 = new TreeNode(2);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(3);

    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node2->right = node4;

    return root;
}


int main(int argc, char* argv[])
{
    TreeNode* root = create_tree();
    Solution sln;
    bool is_symmetry = sln.isSymmetric(root);
    cout << "is symmetry: " << is_symmetry << endl;
    return 0;
}

/* TBD: recursive version
        http://www.geeksforgeeks.org/symmetric-tree-tree-which-is-mirror-image-of-itself/
*/
