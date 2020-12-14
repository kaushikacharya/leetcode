// https://leetcode.com/problems/house-robber/
// May 06, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums)
    {
        if (nums.empty())
        {
            return 0;
        }

        vector<vector<int> > matrix_amount;
        // Notation:
        // matrix_amount[0,i]: max amount robbed till house #i without robbing house #i
        // matrix_amount[1,i]: max amount robbed till house #i with robbing house #i
        // initialize with zeros
        matrix_amount.reserve(2*nums.size());
        for (unsigned int row=0; row != 2; ++row)
        {
            vector<int> vec_amount;
            vec_amount.reserve(nums.size());
            for (unsigned int col=0; col != nums.size(); ++col)
            {
                vec_amount.push_back(0);
            }
            matrix_amount.push_back(vec_amount);
        }

        // Now compute using dynamic programming
        matrix_amount[1][0] = nums[0];

        for (unsigned int col=1; col != nums.size(); ++col)
        {
            matrix_amount[0][col] = max(matrix_amount[0][col-1], matrix_amount[1][col-1]);
            matrix_amount[1][col] = matrix_amount[0][col-1] + nums[col];
        }

        int final_amount_robbed = max(matrix_amount[0][nums.size()-1], matrix_amount[1][nums.size()-1]);
        return final_amount_robbed;
    }
};

int main(int argc, char* argv[])
{
    vector<int> amount_in_street = {};
    Solution sln;
    int final_amount_robbed = sln.rob(amount_in_street);
    cout << "final amount robbed: " << final_amount_robbed << endl;
    return 0;
}

/*
Note: In Tim Roughgarden's part 2 course, its done in a single vector instead of 2*n matrix.
*/
