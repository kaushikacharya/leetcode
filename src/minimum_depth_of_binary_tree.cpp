// https://leetcode.com/problems/minimum-depth-of-binary-tree/
// May 10, 2016

#include <iostream>
#include <limits>
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

// Method: DFS traversal
class Solution {
public:
    int minDepth(TreeNode* root)
    {
        if (root == NULL)
        {
            return 0;
        }

        int min_depth = numeric_limits<int>::max();
        stack<pair<TreeNode*,int> > stk;
        stk.push(make_pair(root,1));

        while (!stk.empty())
        {
            pair<TreeNode*,int> elem = stk.top();
            stk.pop();
            TreeNode* u = elem.first;
            int level = elem.second;

            if ((u->left == NULL) && (u->right == NULL))
            {
                // leaf node
                // Check if depth of this leaf node is lower than the depth of previously visited leaf nodes
                if (level < min_depth)
                {
                    min_depth = level;
                }
            }
            else
            {
                if (u->left)
                {
                    stk.push(make_pair(u->left, level+1));
                }
                if (u->right)
                {
                    stk.push(make_pair(u->right, level+1));
                }
            }
        }

        return min_depth;
    }
};

TreeNode* create_tree()
{
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);

    node1->left = node2;
    node1->right = node3;
    node3->right = node4;

    return node1;
}

void test_vector()
{
    vector<int> vec = {1, NULL, 2, 3};
    if (vec[2] == NULL)
    {
        cout << "null" << endl;
    }
    cout << vec[2] << endl;
}

int main(int argc, char* argv[])
{
    // test_vector();
    TreeNode* root = create_tree();
    Solution sln;
    int min_length_of_tree = sln.minDepth(root);
    cout << "Min length of tree: " << min_length_of_tree << endl;

    return 0;
}

/**
TBD: Create tree from array:
     https://leetcode.com/faq/#binary-tree
     https://leetcode.com/discuss/41182/tree-deserializer-and-visualizer-for-python

*/
