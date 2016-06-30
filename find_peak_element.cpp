// https://leetcode.com/problems/find-peak-element/
// June 30, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums)
    {
        int peak_index;

        int i = 0;
        while (i < (nums.size()-1))
        {
            if (nums[i+1] < nums[i])
            {
                peak_index = i;
                break;
            }
            ++i;
        }

        if (i == (nums.size()-1))
        {
            peak_index = nums.size()-1;
        }

        return peak_index;
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {1, 0, 2, 3, 4};
    Solution sln;
    int peak_index = sln.findPeakElement(nums);
    cout << "peak_index: " << peak_index << endl;
    return 0;
}

/**
*   Run-time: O(N)
*   TBD: Write O(log N) solution.
*/
