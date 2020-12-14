// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
// May 05, 2016

#include <iostream>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k)
    {
        TreeNode* currentNode = root;
        int kth_val;
        int elem_index = 0;
        bool found = false;
        stack<TreeNode*> stk;

        while ((currentNode != NULL) && (!found))
        {
            // Keep going left and pushing into stack
            while (currentNode != NULL)
            {
                stk.push(currentNode);
                currentNode = currentNode->left;
            }

            while (!stk.empty())
            {
                currentNode = stk.top();
                stk.pop();
                ++elem_index;

                if (elem_index == k)
                {
                    kth_val = currentNode->val;
                    found = true;;
                    break;
                }

                // If right subtree is present for the currentNode, then we should traverse the right subtree before traversing
                // rest of the elements in the stack i.e. elements which should be after in the in-order traversal.
                currentNode = currentNode->right;
                if (currentNode != NULL)
                {
                    break;
                }
            }
        }

        // empty the stack
        while (!stk.empty())
        {
            stk.pop();
        }

        return kth_val;
    }
};

TreeNode* create_tree()
{
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);

    node2->left = node1;
    node2->right = node4;
    node4->left = node3;
    node5->left = node2;
    node5->right = node6;

    return node5;
}

int main(int argc, char* argv[])
{
    TreeNode* root = create_tree();
    Solution sln;

    for (int k = 1; k != 7; ++k)
    {
        int kth_val = sln.kthSmallest(root, k);
        cout << "elem #" << k << " : " << kth_val << endl;
    }

    return 0;
}

/**
https://en.wikipedia.org/wiki/Tree_traversal#In-order
Here the iterative in-order code is more concise than mine.
*/
