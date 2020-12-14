// https://leetcode.com/problems/minimum-size-subarray-sum/
// June 17, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums)
    {
        if (nums.empty())
        {
            return 0; // 0 represents failure to find the required subarray having sum >= s
        }

        // initialize subarray sum
        int subarray_sum = nums[0];
        int min_subarray_len;
        // Notation: subarray_sum is the sum of sub-array till nums[i]
        // case (a): min_subarray_len is undefined. sum of nums[0,...,i] < s
        // case (b): Its sum of nums[i-min_subarray_len+1,....,i] i.e. sum of sub-array of
        //                                          length min_subarray_len ending at nums[i]
        bool flag_subarray_found = (subarray_sum < s) ? false : true;
        if (flag_subarray_found)
        {
            min_subarray_len = 1;
        }

        for (int i=1; i != nums.size(); ++i)
        {
            if (!flag_subarray_found)
            {
                subarray_sum += nums[i];

                if (subarray_sum >= s)
                {
                    flag_subarray_found = true;
                    min_subarray_len = i+1;
                }
            }
            else
            {
                subarray_sum += (nums[i] - nums[i-min_subarray_len]);
            }

            if (flag_subarray_found)
            {
                // Check if we can have a smaller sub array with sum >= s
                while ( (min_subarray_len > 1) && ((subarray_sum - nums[i-(min_subarray_len-1)]) >= s) )
                {
                    subarray_sum -= nums[i-(min_subarray_len-1)];
                    --min_subarray_len;
                }

                if (min_subarray_len == 1)
                {
                    break; // No need to check further as there can't be a smaller sub-array satisfying the condition sum >= s
                }
            }
        }

        if (flag_subarray_found)
        {
            return min_subarray_len;
        }
        else
        {
            return 0;
        }
    }
};

int main(int argc, char* argv[])
{
    int s = 6;
    vector<int> nums = {10,2,3};
    Solution sln;
    int minSubArrayLen = sln.minSubArrayLen(s, nums);
    cout << "min sub array length: " << minSubArrayLen << endl;
    return 0;
}

/**
* Space complexity: O(1)
* Time complexity: O(n)
*/
