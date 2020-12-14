// https://leetcode.com/problems/combinations/
// June 24, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int> > vecCombination;

        if (k < 1)
        {
            return vecCombination;
        }

        vector<int> nums;
        for (int i=1; i != (n+1); ++i)
        {
            nums.push_back(i);
        }

        int r = k;
        vector<int> indexCombination;
        // dummy initialization
        for (int i = 0; i != k; ++i)
        {
            indexCombination.push_back(0);
        }

        compute_combination(vecCombination, indexCombination, nums, k, r);

        return vecCombination;
    }
private:
    void compute_combination(vector<vector<int> >& vecCombination, vector<int>& indexCombination, vector<int>& nums, int k, int r)
    {
        if (r == 0)
        {
            vector<int> combination;
            combination.reserve(k);
            for (vector<int>::iterator it = indexCombination.begin(); it != indexCombination.end(); ++it)
            {
                combination.push_back(nums[*it]);
            }
            vecCombination.push_back(combination);
            return;
        }

        int n = nums.size();
        int i = (r == k) ? 0 : (indexCombination[k-(r+1)]+1);
        while (i != (n-r+1))
        {
            indexCombination[k-r] = i;
            compute_combination(vecCombination, indexCombination, nums, k, r-1);
            ++i;
        }
    }
};

int main(int argc, char* argv[])
{
    Solution sln;
    int n = 5;
    int k = 3;
    vector<vector<int> > vecCombination = sln.combine(n,k);

    for (vector<vector<int> >::iterator it = vecCombination.begin(); it != vecCombination.end(); ++it)
    {
        vector<int> combination = *it;
        for (vector<int>::iterator cit = combination.begin(); cit != combination.end(); ++cit)
        {
            cout << *cit << ",";
        }
        cout << endl;
    }

    return 0;
}

/**
* TBD:
*   a) Use the formula: C(n,k)=C(n-1,k-1)+C(n-1,k)
*       https://leetcode.com/discuss/32955/a-short-recursive-java-solution-based-on-c-n-k-c-n-1-k-1-c-n-1-k
*   b) Solve iteratively
*/
