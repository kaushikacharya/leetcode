// https://leetcode.com/problems/wiggle-subsequence/
// July 25, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums)
    {
        int len_longest_subsequence = 0;
        if (nums.empty())
        {
            return len_longest_subsequence;
        }

        int sign_prev_diff = 0; // This stores the sign(diff) of current and prev element of the subsequence
        for (size_t i = 1; i != nums.size(); ++i)
        {
            int diff = nums[i] - nums[i-1];

            if (diff > 0)
            {
                if (sign_prev_diff != 1)
                {
                    sign_prev_diff = 1;
                    ++len_longest_subsequence;
                }
            }
            else if (diff < 0)
            {
                if (sign_prev_diff != -1)
                {
                    sign_prev_diff = -1;
                    ++len_longest_subsequence;
                }
            }
        }

        ++len_longest_subsequence;

        return len_longest_subsequence;
    }
};

int main(int argc, char** argv)
{
    vector<int> nums = {5,5,5};
    Solution sln;
    int len_longest_subsequence = sln.wiggleMaxLength(nums);
    cout << "length(longest subsequnce): " << len_longest_subsequence << endl;
    return 0;
}
