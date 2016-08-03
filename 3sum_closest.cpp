// https://leetcode.com/problems/3sum-closest/
// Aug 03, 2016

#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

class Solution
{
public:
    int threeSumClosest(vector<int>& nums, int target)
    {
        // First sort the elements of nums
        sort(nums.begin(), nums.end());

        int sum_closest = nums[0] + nums[1] + nums[2]; // dummy assignment

        for (size_t i=0; i != nums.size(); ++i)
        {
            // swap nums[i], nums[j]
            swap(nums[0], nums[i]);
            int elem0 = nums[0];

            for (size_t j=1; j != nums.size(); ++j)
            {
                swap(nums[1], nums[j]);
                int elem1 = nums[1];
                int target_for_elem2 = target - (elem0 + elem1);
                int elem2 = closest_element(nums, target_for_elem2, 2, nums.size()-1);
                int cur_sum = elem0 + elem1 + elem2;

                if ( abs(target-cur_sum) < abs(target-sum_closest) )
                {
                    sum_closest = cur_sum;
                }
            }

            // Now put back nums[1:end) in sorted order as it was after the swap in outer for loop
            int temp = nums[1];
            for (size_t j=2; j != nums.size(); ++j)
            {
                nums[j-1] = nums[j];
            }
            nums.back() = temp;
        }

        return sum_closest;
    }
private:
    // Finds the closest elem in nums[p,...q] to target
    int closest_element(vector<int>& nums, int target, size_t p, size_t q)
    {
        if (p == q)
        {
            return nums[p];
        }

        // case: target is beyond the range of nums[p,...,q] or on the boundary
        if (target <= nums[p])
        {
            return nums[p];
        }
        if (nums[q] <= target)
        {
            return nums[q];
        }

        if ((q-p) == 1)
        {
            // select the one which is closest to the target
            if (abs(nums[p]-target) <= abs(nums[q]-target))
            {
                return nums[p];
            }
            else
            {
                return nums[q];
            }
        }
        else
        {
            // reduce the range
            size_t mid_index = (p+q)/2;

            if (target <= nums[mid_index])
            {
                return closest_element(nums, target, p, mid_index);
            }
            else
            {
                return closest_element(nums, target, mid_index, q);
            }
        }
    }
};

void test_swap(vector<int>& nums, size_t p, size_t q)
{
    swap(nums[p], nums[q]);
}

void replace_last_elem(vector<int>& nums, int new_elem)
{
    nums.back() = new_elem;
}

int main(int argc, char** argv)
{
    vector<int> nums = {-1, 2, 1, -4};
    /*
    cout << "Original vector: ";
    for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
    {
        if (it != nums.begin())
        {
            cout << ",";
        }
        cout << *it;
    }
    cout << endl;

    // test_swap(nums, 1, 2);
    // cout << "Post swap vector: ";
    replace_last_elem(nums, 45);
    cout << "POst last elem replace: ";
    for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
    {
        if (it != nums.begin())
        {
            cout << ",";
        }
        cout << *it;
    }
    cout << endl;
    */

    int target = 1;
    Solution sln;
    int closest_sum = sln.threeSumClosest(nums, target);
    cout << "closest 3sum: " << closest_sum << endl;

    return 0;
}

/**
*   Time complexity: O(n^2 * log(n))
*   TBD: Try O(n^2)
*/
