// https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
// June 02, 2016

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeLinkNode
{
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x):val(x),left(NULL),right(NULL),next(NULL){}
};

class Solution {
public:
    void connect(TreeLinkNode *root)
    {
        if (root == NULL)
        {
            return;
        }

        TreeLinkNode* curLevelStart = root; // This will have the left most node at each level of the tree.
        while (curLevelStart->left)
        {
            TreeLinkNode* curLevelNode = curLevelStart;
            TreeLinkNode* nextLevelNode = NULL;
            while (curLevelNode)
            {
                if (nextLevelNode)
                {
                    nextLevelNode->next = curLevelNode->left;
                }
                nextLevelNode = curLevelNode->left;
                nextLevelNode->next = curLevelNode->right;
                nextLevelNode = curLevelNode->right;
                curLevelNode = curLevelNode->next;
            }
            // Now step down to next level
            curLevelStart = curLevelStart->left;
        }
    }

    // Though the solution has been accepted but it violates memory constraint.
    // Method: BFS traversal
    void connect_using_queue(TreeLinkNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        int prevLevel = -1;
        TreeLinkNode* prevNode = NULL;
        queue<pair<TreeLinkNode*,int> > q;
        q.push(make_pair(root,0));

        while (!q.empty())
        {
            pair<TreeLinkNode*,int> elem = q.front();
            q.pop();
            TreeLinkNode* curNode = elem.first;
            int curLevel = elem.second;

            if (prevLevel == curLevel)
            {
                prevNode->next = curNode;
            }

            // push the children in queue
            if (curNode->left)
            {
                q.push(make_pair(curNode->left, curLevel+1));
            }
            if (curNode->right)
            {
                q.push(make_pair(curNode->right, curLevel+1));
            }

            prevNode = curNode;
            prevLevel = curLevel;
        }
    }

    void print_level(TreeLinkNode* root)
    {
        // Here we use the fact that the binary tree is perfect and use the next
        // We will traverse the left side of the binary tree
        TreeLinkNode* nodeLevelLeftMost = root;

        while (nodeLevelLeftMost)
        {
            // print the nodes at the current level
            TreeLinkNode* node = nodeLevelLeftMost;
            while(node)
            {
                cout << node->val << ",";
                node = node->next;
            }
            cout << endl;

            nodeLevelLeftMost = nodeLevelLeftMost->left;
        }
    }
};

TreeLinkNode* create_perfect_binary_tree()
{
    TreeLinkNode* node1 = new TreeLinkNode(1);
    TreeLinkNode* node2 = new TreeLinkNode(2);
    TreeLinkNode* node3 = new TreeLinkNode(3);
    TreeLinkNode* node4 = new TreeLinkNode(4);
    TreeLinkNode* node5 = new TreeLinkNode(5);
    TreeLinkNode* node6 = new TreeLinkNode(6);
    TreeLinkNode* node7 = new TreeLinkNode(7);

    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;

    return node1;
}

int main(int argc, char* argv[])
{
    TreeLinkNode* root = create_perfect_binary_tree();
    Solution sln;
    sln.connect(root);
    sln.print_level(root);
    return 0;
}

/*
    EDIT: Now have implemented solution using O(1) space.

    Though my solution has been accepted, but using queue violates the constraint "You may only use constant extra space."
    Have a look at this solution: https://leetcode.com/discuss/102338/java-solution-traversing-by-level-without-extra-space
*/
