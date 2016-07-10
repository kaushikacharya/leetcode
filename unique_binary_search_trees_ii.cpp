// https://leetcode.com/problems/unique-binary-search-trees-ii/
// July 10, 2016

#include <iostream>
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
    vector<TreeNode*> generateTrees(int n)
    {
        vector<TreeNode*> vecTree;
        if (n < 1)
        {
            return vecTree;
        }

        vector<int> vecNum;
        for (int i = 1; i != (n+1); ++i)
        {
            vecNum.push_back(i);
        }

        vecTree = generateTrees(vecNum, 0, vecNum.size()-1);
        return vecTree;
    }

    void print_vector_subtree_top_two_level(vector<TreeNode*> vecTree)
    {
        for (vector<TreeNode*>::iterator it = vecTree.begin(); it != vecTree.end(); ++it)
        {
            if (*it == NULL)
            {
                cout << "\t\troot: " << "null" << endl;
                continue;
            }
            cout << "\t\troot: " << (*it)->val;
            cout << " :: left: ";
            if ((*it)->left)
            {
                cout << (*it)->left->val;
            }
            else
            {
                cout << "null";
            }
            cout << " :: right: ";
            if ((*it)->right)
            {
                cout << (*it)->right->val;
            }
            else
            {
                cout << "null";
            }
            cout << endl;
        }
    }

    void print_subtree_top_two_level(TreeNode* root)
    {
        if (root == NULL)
        {
            cout << "\t\troot: " << "null" << endl;
            return;
        }
        cout << "\t\troot: " << root->val;
        cout << " :: left: ";
        if (root->left)
        {
            cout << root->left->val;
        }
        else
        {
            cout << "null";
        }
        cout << " :: right: ";
        if (root->right)
        {
            cout << root->right->val;
        }
        else
        {
            cout << "null";
        }
        cout << endl;
    }
private:
    // inclusive of st_index, en_index
    vector<TreeNode*> generateTrees(vector<int>& nums, int st_index, int en_index)
    {
        vector<TreeNode*> vecTree;
        // cout << "st_index: " << st_index << " :: en_index: " << en_index << endl;

        for (int i = st_index; i != (en_index+1); ++i)
        {
            // cout << "\troot index: " << i << " :: st_index: " << st_index << " :: en_index: " << en_index << endl;
            // TreeNode* root_sub_tree = new TreeNode(nums[i]);

            vector<TreeNode*> vecLeftSubTree;
            if (st_index < i)
            {
                vecLeftSubTree = generateTrees(nums, st_index, i-1);
            }
            else
            {
                vecLeftSubTree.push_back(NULL);
            }

            vector<TreeNode*> vecRightSubtree;
            if (i < en_index)
            {
                vecRightSubtree = generateTrees(nums, i+1, en_index);
            }
            else
            {
                vecRightSubtree.push_back(NULL);
            }

            /*
            if (i == 0)
            {
                cout << "\t\tprint right subtree when root index=0" << endl;
                print_vector_subtree_top_two_level(vecRightSubtree);
            }
            */

            /*
            if ((st_index == 0) && (en_index == 2))
            {
                print_vector_subtree_top_two_level(vecRightSubtree);
            }
            */

            // Now create the subtrees with root i
            for (vector<TreeNode*>::iterator it_left = vecLeftSubTree.begin(); it_left != vecLeftSubTree.end(); ++it_left)
            {
                for (vector<TreeNode*>::iterator it_right = vecRightSubtree.begin(); it_right != vecRightSubtree.end(); ++it_right)
                {
                    TreeNode* root_sub_tree = new TreeNode(nums[i]);
                    root_sub_tree->left = *it_left;
                    root_sub_tree->right = *it_right;

                    /*
                    cout << "root: " << root_sub_tree->val << " :: left: ";
                    if (root_sub_tree->left)
                    {
                        cout << root_sub_tree->left->val;
                    }
                    else
                    {
                        cout << "null";
                    }
                    cout << " :: right: ";
                    if (root_sub_tree->right)
                    {
                        cout << root_sub_tree->right->val;
                    }
                    else
                    {
                        cout << "null";
                    }
                    cout << endl;
                    */

                    /*
                    if ((st_index == 0) && (en_index == 2))
                    {
                        // print_subtree_top_two_level(root_sub_tree);
                    }
                    */

                    vecTree.push_back(root_sub_tree);
                }
            }

            /*
            if ((st_index == 0) && (en_index == 2))
            {
                print_vector_subtree_top_two_level(vecTree);
            }
            */
        }

        return vecTree;
    }

};

int main(int argc, char** argv)
{
    int n = 4;
    Solution sln;
    vector<TreeNode*> vecTree = sln.generateTrees(n);
    cout << "number of trees: " << vecTree.size() << endl;
    sln.print_vector_subtree_top_two_level(vecTree);
    return 0;
}

/**
*   Had faced issues as left/right pointer got changed when creating the next tree for vecTree
*   root_sub_tree: This needs to be created every time.
*/
