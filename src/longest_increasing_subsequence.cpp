// https://leetcode.com/problems/longest-increasing-subsequence/
// May 09, 2016

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums)
    {
        // This stores length of longest increasing subsequence till that index
        vector<int> vecLengthLIS;
        vecLengthLIS.reserve(nums.size());

        // initializing with zeros
        for (unsigned int i=0; i != nums.size(); ++i)
        {
            vecLengthLIS.push_back(0);
        }

        for (unsigned int i=0; i != nums.size(); ++i)
        {
            // check the values in [0,...,i-1]
            int max_length = 0;
            for (unsigned int j=0; j != i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    if (vecLengthLIS[j] > max_length)
                    {
                        max_length = vecLengthLIS[j];
                    }
                }
            }

            vecLengthLIS[i] = 1 + max_length;
        }

        int length_LIS = 0;
        for (unsigned int i=0; i != nums.size(); ++i)
        {
            if (length_LIS < vecLengthLIS[i])
            {
                length_LIS = vecLengthLIS[i];
            }
        }

        return length_LIS;
    }
};


int main(int argc, char* argv[])
{
    vector<int> vec = {10, 9, 2, 5, 3, 7, 101, 18};
    Solution sln;
    int length_LIS = sln.lengthOfLIS(vec);
    cout << "length(LIS): " << length_LIS << endl;
    return 0;
}

/*
Current solution's time complexity: O(n^2)
TBD: Improve to O(n log(n))
http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
*/
