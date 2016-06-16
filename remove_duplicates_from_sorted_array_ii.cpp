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

        int max_occurrence_allowed = 2;
        int final_length = 1;
        int shift = 0;
        int prevNum = nums[0];
        int prevCount = 1; // Keeps count of occurrence of previous number

        for (int i=1; i != nums.size(); ++i)
        {
            int curNum = nums[i];

            // bool is_additional_duplicates = false;

            if (prevNum == curNum)
            {
                ++prevCount;
            }
            else
            {
                prevCount = 1;
            }

            if (prevCount > max_occurrence_allowed)
            {
                ++shift;
            }
            else
            {
                ++final_length;

                if (shift > 0)
                {
                    nums[i-shift] = curNum;
                }
            }

            prevNum = curNum;
        }

        return final_length;
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {1,1,1,2,2,3,3,3,4};
    Solution sln;
    int count_post_duplicate_removal = sln.removeDuplicates(nums);
    cout << "count post duplicate removal: " << count_post_duplicate_removal << endl;
    for (int i=0; i != count_post_duplicate_removal; ++i)
    {
        cout << nums[i] << ",";
    }
    cout << endl;
    return 0;
}

/**
* Status: Wrong answer :: Need to remove duplicate from the array
*
* Explanation of question:
*   https://leetcode.com/discuss/76421/weird-answer-why-the-expected-answer-an-array-not-an-integer
*   https://leetcode.com/discuss/55475/what-this-problem-means-doesnt-matter-what-leave-beyond-length?show=55475#q55475
*/
