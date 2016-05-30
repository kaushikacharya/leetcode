// https://leetcode.com/problems/maximum-product-subarray/
// May 30, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums)
    {
        int max_product = nums[0];
        // max_product_till_prev: max product of sub-array which includes/ends at previous element
        int max_product_till_prev = nums[0];
        // max_product_in_abs_till_prev: max product in absolute of sub-array which includes/ends at previous element
        // Handles cases: ..2,..,3,..-2,..+ve numbers,..,-3,...
        // i.e. even number of negative numbers contribute to positive product
        int max_product_in_abs_till_prev = nums[0];
        // While computing these we need to handle cases when 0 is present

        // Iterate over the rest of numbers and keep updating (a) max_product_till_prev, (b) max_product_in_abs_till_prev
        for (vector<int>::iterator it = nums.begin()+1; it != nums.end(); ++it)
        {
            int cur_num = *it;

            if (cur_num > 0)
            {
                if (max_product_till_prev > 0)
                {
                    max_product_till_prev *= cur_num;
                }
                else
                {
                    max_product_till_prev = cur_num;
                }
            }
            else
            {
                if (max_product_in_abs_till_prev < 0)
                {
                    max_product_till_prev = cur_num*max_product_in_abs_till_prev;
                }
                else
                {
                    max_product_till_prev = cur_num;
                }
            }

            // Check if max product meeds to be updated
            if (max_product < max_product_till_prev)
            {
                max_product = max_product_till_prev;
            }

            if (max_product_in_abs_till_prev == 0)
            {
                max_product_in_abs_till_prev = cur_num;
            }
            else
            {
                max_product_in_abs_till_prev *= cur_num;
            }
        }

        return max_product;
    }
};


int main(int argc, char* argv[])
{
    vector<int> nums = {2,-5,-2,-4,3};
    Solution sln;
    int maxProduct = sln.maxProduct(nums);
    cout << "max product: " << maxProduct << endl;
    return 0;
}

/*
Status: Incorrect Answer
*/
