// https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
// June 23, 2016

#include <iostream>

using namespace std;

struct TreeLinkNode
{
    int val;
    TreeLinkNode* left;
    TreeLinkNode* right;
    TreeLinkNode* next;
    TreeLinkNode(int x): val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root)
    {
        if (root == NULL)
        {
            return;
        }

        TreeLinkNode* prevLevelHead = root; // head of the linked list at previous level

        while (prevLevelHead)
        {
            TreeLinkNode* curLevelHead = NULL;
            TreeLinkNode* nodePrevLevel = prevLevelHead;

            // iterate the nodes at previous level
            TreeLinkNode* prevNodeCurLevel = NULL;
            while (nodePrevLevel)
            {
                if (nodePrevLevel->left)
                {
                    TreeLinkNode* curNodeCurLevel = nodePrevLevel->left;

                    if (curLevelHead == NULL)
                    {
                        curLevelHead = nodePrevLevel->left;
                    }
                    else
                    {
                        // prevNodeCurLevel will exist
                        prevNodeCurLevel->next = curNodeCurLevel;
                    }

                    prevNodeCurLevel = curNodeCurLevel;
                }

                if (nodePrevLevel->right)
                {
                    TreeLinkNode* curNodeCurLevel = nodePrevLevel->right;

                    if (curLevelHead == NULL)
                    {
                        curLevelHead = nodePrevLevel->right;
                    }
                    else
                    {
                        // prevNodeCurLevel will exist
                        prevNodeCurLevel->next = curNodeCurLevel;
                    }

                    prevNodeCurLevel = curNodeCurLevel;
                }

                nodePrevLevel = nodePrevLevel->next;
            }

            // storing the current level's head as previous level's head before iterating the next level
            prevLevelHead = curLevelHead;
        }
    }

    void print_levels(TreeLinkNode* root)
    {
        // Outer traverse: Left side view of binary tree
        // Inner traversal: Level traversal using next
        TreeLinkNode* leftMostNodeCurLevel = root;
        while (leftMostNodeCurLevel)
        {
            TreeLinkNode* leftMostNodeNextLevel = NULL;

            // We will print the nodes at current level as well as find the left most for the next level
            TreeLinkNode* nodeCurLevel = leftMostNodeCurLevel;

            while (nodeCurLevel)
            {
                cout << nodeCurLevel->val << ",";

                if (leftMostNodeNextLevel == NULL)
                {
                    if (nodeCurLevel->left)
                    {
                        leftMostNodeNextLevel = nodeCurLevel->left;
                    }
                }
                if (leftMostNodeNextLevel == NULL)
                {
                    if (nodeCurLevel->right)
                    {
                        leftMostNodeNextLevel = nodeCurLevel->right;
                    }
                }

                nodeCurLevel = nodeCurLevel->next;
            }
            cout << endl;

            // assigning for the next iteration
            leftMostNodeCurLevel = leftMostNodeNextLevel;
        }
    }
};

TreeLinkNode* create_tree()
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
    // node2->left = node4;
    node2->right = node5;
    node3->right = node7;

    return node1;
}

int main(int argc, char* argv[])
{
    TreeLinkNode* root = create_tree();
    Solution sln;
    sln.connect(root);
    sln.print_levels(root);
    return 0;
}
