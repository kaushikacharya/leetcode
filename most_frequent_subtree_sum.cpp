// https://leetcode.com/problems/most-frequent-subtree-sum/?tab=Description
// Mar 05, 2017

#include <iostream>
#include <unordered_map>
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
    vector<int> findFrequentTreeSum(TreeNode* root) {
        vector<int> vecFrequentTreeSum;
        if (root == NULL)
        {
            return vecFrequentTreeSum;
        }

        vector<int> vecTreeSum;
        computeTreeSum(root, vecTreeSum);

        // compute count for each sum
        unordered_map<int,unsigned int> sumToCountMap;

        for (vector<int>::iterator it = vecTreeSum.begin(); it != vecTreeSum.end(); ++it)
        {
            int treeSum = *it;
            unordered_map<int,unsigned int>::iterator mapIt = sumToCountMap.find(treeSum);
            if (mapIt == sumToCountMap.end())
            {
               sumToCountMap.insert(make_pair(treeSum,1));
            }
            else
            {
                ++((*mapIt).second);
            }
        }

        unsigned int maxCount = 0;
        for (unordered_map<int,unsigned int>::iterator mapIt=sumToCountMap.begin(); mapIt != sumToCountMap.end(); ++mapIt)
        {
            if (maxCount < (*mapIt).second)
            {
                maxCount = (*mapIt).second;
            }
        }

        for (unordered_map<int,unsigned int>::iterator mapIt=sumToCountMap.begin(); mapIt != sumToCountMap.end(); ++mapIt)
        {
            if ((*mapIt).second == maxCount)
            {
                vecFrequentTreeSum.push_back((*mapIt).first);
            }
        }

        return vecFrequentTreeSum;
    }
private:
    void computeTreeSum(TreeNode* rootSubtree, vector<int>& vecTreeSum)
    {
        if ((rootSubtree->left == NULL) && (rootSubtree->right == NULL))
        {
            vecTreeSum.push_back(rootSubtree->val);
            return;
        }

        int subtreeSum = rootSubtree->val;
        if (rootSubtree->left)
        {
            computeTreeSum(rootSubtree->left, vecTreeSum);
            subtreeSum += vecTreeSum.back();
        }
        if (rootSubtree->right)
        {
            computeTreeSum(rootSubtree->right, vecTreeSum);
            subtreeSum += vecTreeSum.back();
        }

        vecTreeSum.push_back(subtreeSum);
    }
};

int main(int argc, char** argv)
{
    int test_case = 2;
    Solution sln;

    switch(test_case)
    {
    case 0:
        {
            TreeNode* node1 = new TreeNode(5);
            TreeNode* node2 = new TreeNode(2);
            TreeNode* node3 = new TreeNode(-3);
            node1->left = node2;
            node1->right = node3;

            vector<int> vecFrequentTreeSum = sln.findFrequentTreeSum(node1);
            cout << "frequent sum: ";
            for (vector<int>::iterator it = vecFrequentTreeSum.begin(); it != vecFrequentTreeSum.end(); ++it)
            {
                cout << *it << " ";
            }
            cout << endl;
            break;
        }
    case 1:
        {
            TreeNode* node1 = new TreeNode(5);
            TreeNode* node2 = new TreeNode(2);
            TreeNode* node3 = new TreeNode(-5);
            node1->left = node2;
            node1->right = node3;

            vector<int> vecFrequentTreeSum = sln.findFrequentTreeSum(node1);
            cout << "frequent sum: ";
            for (vector<int>::iterator it = vecFrequentTreeSum.begin(); it != vecFrequentTreeSum.end(); ++it)
            {
                cout << *it << " ";
            }
            cout << endl;
            break;
        }
    case 2:
        {
            TreeNode* node0 = new TreeNode(-7);
            TreeNode* node1 = new TreeNode(5);
            TreeNode* node2 = new TreeNode(2);
            TreeNode* node3 = new TreeNode(-5);
            node1->left = node2;
            node1->right = node3;
            node0->left = node1;

            vector<int> vecFrequentTreeSum = sln.findFrequentTreeSum(node0);
            cout << "frequent sum: ";
            for (vector<int>::iterator it = vecFrequentTreeSum.begin(); it != vecFrequentTreeSum.end(); ++it)
            {
                cout << *it << " ";
            }
            cout << endl;
            break;
        }
    }
    return 0;
}
