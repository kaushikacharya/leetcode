// https://leetcode.com/problems/increasing-triplet-subsequence/
// June 26, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool increasingTriplet(vector<int>& nums)
    {
        int n = nums.size();
        if (n < 3)
        {
            return false;
        }
        // is_bigger_num_present_on_right_array[i] :: There exist j > i such that nums[j] > nums[i]
        vector<bool> is_bigger_num_present_on_right_array;
        is_bigger_num_present_on_right_array.reserve(nums.size());
        // initialize dummy value
        for (unsigned i=0; i != nums.size(); ++i)
        {
            is_bigger_num_present_on_right_array.push_back(false);
        }
        int max_num_on_right = nums.back();
        for (int i = n-2; i >= 0; --i)
        {
            if (nums[i] < max_num_on_right)
            {
                is_bigger_num_present_on_right_array[i] = true;
            }
            else
            {
                max_num_on_right = nums[i];
            }
        }

        unsigned int t0 = 0;
        bool triplet_found = false;
        for (unsigned int i=1; i != (n-1); ++i)
        {
            if (nums[i] > nums[t0])
            {
                if (is_bigger_num_present_on_right_array[i])
                {
                    triplet_found = true;
                    break;
                }
            }
            else
            {
                t0 = i;
            }
        }

        return triplet_found;
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {100,90,80,70,78,76,75};
    Solution sln;
    bool triplet_found = sln.increasingTriplet(nums);
    cout << "increasing triplet found: " << triplet_found << endl;
    return 0;
}

/**
*   https://leetcode.com/discuss/86593/clean-and-short-with-comments-c
*   This solution is O(1) in memory unlike mine which is O(n) in memory.
*/
