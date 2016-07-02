// https://leetcode.com/problems/jump-game-ii/
// July 01, 2016

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums)
    {
        // vecJump[i]: min number of jumps from index i to last index
        vector<int> vecJump;
        vecJump.reserve(nums.size());
        for (size_t i = 0; i != nums.size(); ++i)
        {
            vecJump.push_back(numeric_limits<int>::max());
        }

        // initialize for last index
        vecJump[nums.size()-1] = 0;
        /**
        for (size_t i = 0; i != nums.size(); ++i)
        {
            cout << "i: " << i << " :: vecJump[i]: " << vecJump[i] << endl;
        }

        cout << endl;
        */
        size_t i = nums.size()-1;

        while (i > 0)
        {
            --i;

            int min_jump_from_next = numeric_limits<int>::max();
            for (size_t j = i+1; j <= min(i+nums[i], nums.size()-1); ++j)
            {
                if (vecJump[j] < min_jump_from_next)
                {
                    min_jump_from_next = vecJump[j];
                }
            }

            if (min_jump_from_next < numeric_limits<int>::max())
            {
                vecJump[i] = 1 + min_jump_from_next;
            }

            //cout << "i: " << i << " :: vecJump[i]: " << vecJump[i] << endl;
        }

        return vecJump[0];
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {2,1,1,4};
    Solution sln;
    int min_jump = sln.jump(nums);
    cout << "min jump: " << min_jump << endl;
    return 0;
}

/**
*   Status: Time Limit exceeded
*   Time complexity: O(n^2)   Space complexity: O(n)
*
*   http://stackoverflow.com/questions/4849632/vectorintsize-type-in-c#
*   size_type is a (static) member type of the type vector<int>. Usually, it is a typedef for
*   std::size_t, which itself is usually a typedef for unsigned int or unsigned long long.
*/
