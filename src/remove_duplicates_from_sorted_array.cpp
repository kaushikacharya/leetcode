// https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// June 16, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        int final_length = 0;

        if (nums.empty())
        {
            return final_length;
        }

        int shift = 0;
        int prevNum = nums[0];
        ++final_length;

        for (int i=1; i != nums.size(); ++i)
        {
            int curNum = nums[i];

            if (prevNum == curNum)
            {
                ++shift;
            }
            else
            {
                ++final_length;
                // shifting
                if (shift > 0)
                {
                    nums[i-shift] = curNum;
                }
                // update prevNum with curNum
                prevNum = curNum;
            }

        }

        return final_length;
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {1,1,1,2};
    Solution sln;
    int final_length = sln.removeDuplicates(nums);
    cout << "post removal of duplicates: final_length: " << final_length << endl;
    for (int i=0; i != final_length; ++i)
    {
        cout << nums[i] << ",";
    }
    cout << endl;
    return 0;
}
