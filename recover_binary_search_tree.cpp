// https://oj.leetcode.com/problems/recover-binary-search-tree/
// Date: Nov 26, 2014

#include <iostream>
#include <vector>
#include <tuple>

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
    void recoverTree(TreeNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        // initializing
        root_problematic_subtree_ = NULL;
        max_left_node_problematic_subtree_ = NULL;
        min_right_node_problematic_subtree_ = NULL;

        process_sub_tree(root);

        if (root_problematic_subtree_)
        {
            swap(max_left_node_problematic_subtree_->val, min_right_node_problematic_subtree_->val);
        }

    }
private:
    // <0> root of the subtree
    // <1> min value of the subtree
    // <2> max value of the subtree
    pair<int,int> recover_tree(TreeNode* node)
    {
        if ( (node->left == NULL) && (node->right == NULL) )
        {
            return make_pair(node->val, node->val);
        }

        if (node->left == NULL)
        {
            // only right child is present
            pair<int,int> elem_right = recover_tree(node->right);
            int min_right = elem_right.first;
        }
    }

    // Output: For each subtree, we return nodes with min and max values.
    pair<TreeNode*, TreeNode*> process_sub_tree(TreeNode* node)
    {
        if (node == NULL)
        {
            return make_pair<TreeNode*,TreeNode*>(NULL,NULL);
        }

        if ( (node->left == NULL) && (node->right == NULL) )
        {
            // leaf node
            return make_pair(node, node);
        }

        // initializing min/max with the root of the subtree
        TreeNode* min_subtree = node;
        TreeNode* max_subtree = node;

        TreeNode* min_left_subtree = NULL;
        TreeNode* max_left_subtree = NULL;

        if (node->left)
        {
            pair<TreeNode*, TreeNode*> left_min_max = process_sub_tree(node->left);
            min_left_subtree = left_min_max.first;
            max_left_subtree = left_min_max.second;

            if (min_left_subtree->val < min_subtree->val)
            {
                min_subtree = min_left_subtree;
            }
            if (max_subtree->val < max_left_subtree->val)
            {
                max_subtree = max_left_subtree;
            }
        }

        TreeNode* min_right_subtree = NULL;
        TreeNode* max_right_subtree = NULL;

        if (node->right)
        {
            pair<TreeNode*, TreeNode*> right_min_max = process_sub_tree(node->right);
            min_right_subtree = right_min_max.first;
            max_right_subtree = right_min_max.second;

            if (min_right_subtree->val < min_subtree->val)
            {
                min_subtree = min_right_subtree;
            }
            if (max_subtree->val < max_right_subtree->val)
            {
                max_subtree = max_right_subtree;
            }
        }

        // Now check if this subtree is a BST or not
        bool flag_left_problem_status = false;
        bool flag_right_problem_status = false;

        if (node->left)
        {
            if (node->val < max_left_subtree->val)
            {
                flag_left_problem_status = true;
            }
        }
        if (node->right)
        {
            if (min_right_subtree->val < node->val)
            {
                flag_right_problem_status = true;
            }
        }

        if (flag_left_problem_status || flag_right_problem_status)
        {
            root_problematic_subtree_ = node;
        }

        if (flag_left_problem_status && flag_right_problem_status)
        {
            // swap of (a) node of left subtree and (b) node of right subtree
            max_left_node_problematic_subtree_ = max_left_subtree;
            min_right_node_problematic_subtree_ = min_right_subtree;
        }
        else if (flag_left_problem_status)
        {
            // swap of (a) node of left subtree and (b) root of subtree
            max_left_node_problematic_subtree_ = max_left_subtree;
            min_right_node_problematic_subtree_ = node;
        }
        else if (flag_right_problem_status)
        {
            // swap of (a) root of subtree and (b) node of right subtree
            max_left_node_problematic_subtree_ = node;
            min_right_node_problematic_subtree_ = min_right_subtree;
        }

        return make_pair(min_subtree, max_subtree);
    }
private:
    // This keeps track of subtree whose two nodes have been swapped
    TreeNode* root_problematic_subtree_;
    TreeNode* max_left_node_problematic_subtree_;
    TreeNode* min_right_node_problematic_subtree_;
};

class BST
{
    public:
        TreeNode* create_bst(vector<int> vec)
        {
            if (vec.empty())
            {
                return NULL;
            }

            root_ = new TreeNode(vec[0]);
            for (int i = 1; i != vec.size(); ++i)
            {
                TreeNode* node = root_;

                // append the current element in its proper position in the tree
                while (node)
                {
                    if (vec[i] <= node->val)
                    {
                        if (node->left)
                        {
                            node = node->left;
                        }
                        else
                        {
                            TreeNode* newNode = new TreeNode(vec[i]);
                            node->left = newNode;
                            break;
                        }
                    }
                    else
                    {
                        if (node->right)
                        {
                            node = node->right;
                        }
                        else
                        {
                            TreeNode* newNode = new TreeNode(vec[i]);
                            node->right = newNode;
                            break;
                        }
                    }
                }
            }

            return root_;
        }

        TreeNode* find_node(int elem)
        {
            TreeNode* searched_node = NULL;
            TreeNode* node = root_;

            while (node)
            {
                if (node->val == elem)
                {
                    searched_node = node;
                    break;
                }
                else if (elem < node->val)
                {
                    node = node->left;
                }
                else
                {
                    node = node->right;
                }
            }

            return searched_node;
        }

    private:
        TreeNode* root_;
};

int main(int argc, char* argv[])
{
    int arr[] = {18,16,17,13,15};
    vector<int> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));

    BST bst;
    TreeNode* root = bst.create_bst(vec);
    TreeNode* node = bst.find_node(15);

    swap(root->val, node->val);

    Solution sln;
    sln.recoverTree(root);

    return 0;
}

/*
status: incomplete, couldn't figure out the algo
*/
