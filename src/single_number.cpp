// https://leetcode.com/problems/single-number/
// June 15, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        int xor_val = nums[0];
        for (vector<int>::iterator it = nums.begin()+1; it != nums.end(); ++it)
        {
            xor_val ^= *it;
        }

        return xor_val;
    }
};

void test_xor(int num1, int num2)
{
    int num3 = num1^num2;
    cout << "xor: " << num3 << endl;
}

int main(int argc, char* argv[])
{
    /*
    int num1 = -2;
    int num2 = 4;
    test_xor(num1, num2);
    */

    vector<int> nums = {-1,-3,2,-1,2};
    Solution sln;
    int single_number = sln.singleNumber(nums);
    cout << "single number: " << single_number << endl;
    return 0;
}

/**
* http://programmers.stackexchange.com/questions/239036/how-are-negative-signed-values-stored#
* http://stackoverflow.com/questions/19067286/xor-operation-in-c
*/
