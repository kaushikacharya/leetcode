// https://leetcode.com/problems/unique-binary-search-trees/
// May 19, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numTrees(int n)
    {
        if (n <= 0)
        {
            return 0;
        }

        // initialize
        vecUniqueBSTCount.reserve(n+1);
        for (int i = 0; i != (n+1); ++i)
        {
            vecUniqueBSTCount.push_back(0);
        }
        vecUniqueBSTCount[1] = 1;

        for(int n_nodes=2; n_nodes != (n+1); ++n_nodes)
        {
            int count_unique_BST = 0;

            for (int node_i = 1; node_i != (n_nodes+1); ++node_i)
            {
                int n_nodes_left_subtree = node_i - 1;
                int n_nodes_right_subtree = n_nodes - node_i;

                if ((n_nodes_left_subtree > 0) && (n_nodes_right_subtree > 0))
                {
                    // Both left and right subtree are present
                    int left_subtree_unique_BST_count = vecUniqueBSTCount[n_nodes_left_subtree];
                    int right_subtree_unique_BST_count = vecUniqueBSTCount[n_nodes_right_subtree];

                    count_unique_BST += left_subtree_unique_BST_count*right_subtree_unique_BST_count;
                }
                else if (n_nodes_left_subtree > 0)
                {
                    // Right subtree is empty
                    count_unique_BST += vecUniqueBSTCount[n_nodes_left_subtree];
                }
                else
                {
                    // Left subtree is empty
                    count_unique_BST += vecUniqueBSTCount[n_nodes_right_subtree];
                }

            }

            vecUniqueBSTCount[n_nodes] = count_unique_BST;
        }

        return vecUniqueBSTCount[n];
    }
private:
    vector<int> vecUniqueBSTCount;  // vecUniqueBSTCount[i] represents count of unique BSTs created by nodes 1,...,i
};

int main(int argc, char* argv[])
{
    int n = 4;
    Solution sln;
    int unique_BST_count = sln.numTrees(n);
    cout << "Count of unique BST: " << unique_BST_count << endl;

    return 0;
}

/* Solved using Dynamic Programming
*/
