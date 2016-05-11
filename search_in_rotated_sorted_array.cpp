// https://leetcode.com/problems/search-in-rotated-sorted-array/
// May 09, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target)
    {
        if (nums.empty())
        {
            return -1;
        }
        unsigned int min_index = find_min_index(nums);

        int search_index;
        if (min_index == 0)
        {
            // Full rotation i.e. rotated sorted array is same as sorted array
            search_index = search_in_range(nums, target, 0, nums.size()-1);
        }
        else
        {
            // Now we will have two sorted portions
            search_index = search_in_range(nums, target, 0, min_index-1);
            if (search_index == -1)
            {
                // Search in right portion as target not found in left portion.
                search_index = search_in_range(nums, target, min_index, nums.size()-1);
            }
        }

        return search_index;
    }
private:
    // Find the index of lowest value in rotated sorted array
    // Time complexity: O(log(n))
    unsigned int find_min_index(vector<int>& nums)
    {
        unsigned int p = 0;
        unsigned int q = nums.size()-1;

        if (nums[p] < nums[q])
        {
            // Full rotation i.e. rotated sorted array is same as sorted array
            return 0;
        }

        // e.g. {0 1 2 4 5 6 7} might become {4 5 6 7 0 1 2}
        // So there are two sorted portions, where the portion on left side is greater than the portion on right side.
        while (p < q)
        {
            unsigned int mid_index = (p+q)/2;

            if (nums[0] <= nums[mid_index])
            {
                // mid_index belongs to left sorted portion
                p = mid_index+1;
            }
            else
            {
                // mid_index belongs to right sorted portion
                q = mid_index;
            }
        }

        return p;
    }

    // search target in nums[p,...,q]
    // return -1 if not found
    int search_in_range(vector<int>& nums, int target, unsigned int p, unsigned int q)
    {
        // First check if target is within range
        if (target < nums[p])
        {
            return -1;
        }
        if (nums[q] < target)
        {
            return -1;
        }

        unsigned int i = p;
        unsigned int j = q;

        while (i < j)
        {
            unsigned int mid_index = (i+j)/2;

            if (target == nums[mid_index])
            {
                i = mid_index;
                j = mid_index;
            }
            else if (target < nums[mid_index])
            {
                j = mid_index - 1;
            }
            else
            {
                i = mid_index + 1;
            }
        }

        if (nums[i] == target)
        {
            return (int)i;
        }
        else
        {
            return -1;
        }
    }
};


int main(int argc, char* argv[])
{
    vector<int> nums = {4,5,6,7,0,1,2};
    int target = 0;

    Solution sln;
    int index_target = sln.search(nums, target);
    cout << "index of target: " << index_target << endl;
    if ((index_target > 0) && (nums[index_target] != target))
    {
        cout << "incorrect solution" << endl;
    }
    return 0;
}
