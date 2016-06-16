// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
// June 16, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        if (nums.empty())
        {
            return 0;
        }

        int final_count = 0;

        int prevElem = nums[0];
        int prevCount = 1;

        for (vector<int>::iterator it = nums.begin()+1; it != nums.end(); ++it)
        {
            int curElem = *it;

            if (prevElem == curElem)
            {
                ++prevCount;
            }
            else
            {
                final_count += min(2,prevCount);
                // reset prev*
                prevElem = curElem;
                prevCount = 1;
            }
        }

        // include count for final element
        final_count += min(2,prevCount);

        return final_count;
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {1,1,1,2};
    Solution sln;
    int count_post_duplicate_removal = sln.removeDuplicates(nums);
    cout << "count post duplicate removal: " << count_post_duplicate_removal << endl;
    return 0;
}

/**
* Status: Wrong answer :: Need to remove duplicate from the array
*
* Explanation of question:
*   https://leetcode.com/discuss/76421/weird-answer-why-the-expected-answer-an-array-not-an-integer
*   https://leetcode.com/discuss/55475/what-this-problem-means-doesnt-matter-what-leave-beyond-length?show=55475#q55475
*/
