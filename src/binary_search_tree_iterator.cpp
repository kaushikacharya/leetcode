// https://leetcode.com/problems/binary-search-tree-iterator/
// June 07, 2016

#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(NULL),right(NULL){}
};

class BSTIterator {
public:
    BSTIterator(TreeNode *root)
    {
        head_ = NULL;

        if (root)
        {
            // Keep going left of tree
            // Also populate the linked list so that root is the tail of the linked list i.e. bottom most node is head and
            //      top most node i.e. root is tail
            TreeNode* node = root;
            while (node)
            {
                head_ = new LinkedListNode(node,head_);
                node = node->left;
            }
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext()
    {
        return (head_ != NULL);
    }

    /** @return the next smallest number */
    int next()
    {
        int nextVal = head_->treeNode->val;
        // a) head_ should move to next of current head_
        // b) Also if current head_ have a right subtree then we should traverse left side and push the nodes in the linked list
        TreeNode* node = head_->treeNode->right;
        head_ = head_->next;
        while (node)
        {
            head_ = new LinkedListNode(node,head_);
            node = node->left;
        }

        return nextVal;
    }
private:
    struct LinkedListNode
    {
        TreeNode* treeNode;
        LinkedListNode* next;
        LinkedListNode(TreeNode* node, LinkedListNode* nextNode=NULL): treeNode(node), next(nextNode) {}
    };
private:
    LinkedListNode* head_;
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */

 TreeNode* create_binary_search_tree()
 {
     TreeNode* node0 = new TreeNode(2);
     TreeNode* node1 = new TreeNode(15);
     TreeNode* node2 = new TreeNode(5);
     TreeNode* node5 = new TreeNode(20);
     TreeNode* node3 = new TreeNode(10);
     TreeNode* node4 = new TreeNode(8);

     node0->right = node1;
     node1->left = node2;
     node1->right = node5;
     node2->right = node3;
     node3->left = node4;

     return node1;
 }

 int main(int argc, char* argv[])
 {
     TreeNode* root = create_binary_search_tree();
     //TreeNode* root = NULL;
     BSTIterator i = BSTIterator(root);
     while (i.hasNext()) cout << i.next() << ",";
     return 0;
 }

/*
stack should have been used to make the code compact.

Though haven't used the funda mentioned in the following link:
http://stackoverflow.com/questions/8550711/struct-in-class

Have a look at this too:
http://en.cppreference.com/w/cpp/language/nested_types
*/
