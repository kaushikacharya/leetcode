// https://leetcode.com/problems/missing-number/
// June 23, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums)
    {
        long n = nums.size();
        long sum = 0;

        for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
        {
            sum += *it;
        }

        int missing_number = n*(n+1)/2 - sum;
        return missing_number;
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {1,0,2,3,4};
    Solution sln;
    int missing_number = sln.missingNumber(nums);
    cout << "missing number: " << missing_number << endl;
    return 0;
}

/**
*   TBD: Alternate approach available based on bit manipulation.
*/

