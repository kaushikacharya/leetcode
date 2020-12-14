// https://leetcode.com/problems/combination-sum/
// June 06, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        // initialize
        vecCount_.reserve(candidates.size());
        vecCandidate_.reserve(candidates.size());
        for (vector<int>::iterator it = candidates.begin(); it != candidates.end(); ++it)
        {
            vecCount_.push_back(0);
            vecCandidate_.push_back(*it);
        }

        target_ = target;
        sum_ = 0;

        compute_combination_recursive(0);

        return vecCombination_;
    }
private:
    void compute_combination_recursive(int cand_i)
    {
        if (cand_i == vecCandidate_.size())
        {
            return;
        }

        int maxCountForCurCandidate = target_/vecCandidate_[cand_i];

        bool flag = true;
        for (int count_i=0; ((count_i <= maxCountForCurCandidate) && flag); ++count_i)
        {
            sum_ += vecCandidate_[cand_i]*count_i;
            vecCount_[cand_i] = count_i;

            if (sum_ == target_)
            {
                // record the combination
                vector<int> combination;
                for (int cand_j=0; cand_j <= cand_i; ++cand_j)
                {
                    int countForCandidate = vecCount_[cand_j];
                    for (int count_j=0; count_j < countForCandidate; ++count_j)
                    {
                        combination.push_back(vecCandidate_[cand_j]);
                    }
                }
                vecCombination_.push_back(combination);
            }
            else if (sum_ < target_)
            {
                compute_combination_recursive(cand_i+1);
            }
            else
            {
                flag = false; // No point in trying higher count of cand_i
            }

            sum_ -= vecCandidate_[cand_i]*count_i;
        }
        vecCount_[cand_i] = 0;
    }
private:
    vector<vector<int> > vecCombination_;
    vector<int> vecCandidate_;
    vector<int> vecCount_; // Each index i represents count of vecCandidate_[i] in the combination
    int target_;
    int sum_;
};

int main(int argc, char* argv[])
{
    vector<int> candidates = {2,3,6,7};
    int target = 5;
    Solution sln;
    vector<vector<int> > vecCombination = sln.combinationSum(candidates, target);

    for (vector<vector<int> >::iterator it=vecCombination.begin(); it != vecCombination.end(); ++it)
    {
        vector<int> combination = *it;
        for (vector<int>::iterator eit=combination.begin(); eit != combination.end(); ++eit)
        {
            cout << *eit << ",";
        }
        cout << endl;
    }
    return 0;
}

/*
    https://leetcode.com/discuss/104331/approach-backtracking-questions-permutations-combination
    Solution provided by issac3 is compact.
    1. maxCountForCurCandidate is redundant in my solution compared to his.
    2. Also combination comes directly whereas in my solution I am populating vecCount_ and then creating combination.
*/
