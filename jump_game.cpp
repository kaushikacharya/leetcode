// https://leetcode.com/problems/jump-game/
// July 01, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums)
    {
        int n = nums.size();
        int max_index = 0;
        int i = 0;
        bool can_jump = true;

        while ( (i < nums.size()) && (max_index < (n-1)) )
        {
            if (max_index < i)
            {
                // we won't be able to jump i'th and onwards index
                can_jump = false;
                break;
            }

            max_index = max(max_index, min(i+nums[i], n-1));
            ++i;
        }

        return can_jump;
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {3,2,1,0,4};
    Solution sln;
    bool can_jump = sln.canJump(nums);
    if (can_jump)
    {
        cout << "can jump" << endl;
    }
    else
    {
        cout << "cannot jump" << endl;
    }
    return 0;
}

/**
*   Approach: Greedy  Time Complexity: O(n)   Space Complexity: O(1)
*   My solution is similar to: https://leetcode.com/discuss/15567/linear-and-simple-solution-in-c
*
*   TBD: Understand the various approaches
*   https://leetcode.com/articles/jump-game/
*/
