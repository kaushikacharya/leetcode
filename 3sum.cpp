// https://leetcode.com/problems/3sum/description/
// Oct 11, 2018

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;

        if (nums.size() == 0)
        {
            return result;
        }

        // sort elements in ascending order
        sort(nums.begin(), nums.end());

        unordered_map<int, int> num_count_map;
        for(vector<int>::iterator it=nums.begin(); it != nums.end(); ++it)
        {
            int num = *it;
            unordered_map<int, int>::iterator mapIt = num_count_map.find(num);
            if (mapIt == num_count_map.end())
            {
                num_count_map.insert(make_pair(num, 1));
            }
            else
            {
                ++(*mapIt).second;
            }
        }

        // sorted unique elements
        vector<int> uniq_sorted_nums;
        uniq_sorted_nums.reserve(num_count_map.size());
        uniq_sorted_nums.push_back(nums[0]);

        for(int i=1; i != nums.size(); ++i)
        {
            if (nums[i] != nums[i-1])
            {
                uniq_sorted_nums.push_back(nums[i]);
            }
        }

        // since we have to create unique triplets, we will create triplets in such a way that i'th element <= (i+1)'th element
        int i = 0;
        while (i < uniq_sorted_nums.size())
        {
            // We are considering to create triplet with first_elem as its first element
            int first_elem = uniq_sorted_nums[i];
            if (first_elem > 0)
            {
                // Not possible to form any further triplet considering the constraint mentioned above
                break;
            }

            // get count of i'th element
            unordered_map<int, int>::iterator mapIt = num_count_map.find(first_elem);
            int n_instance_ith_element = (*mapIt).second;

            // check for triplet with same value for each of the 3 elements
            if ((first_elem==0) && (n_instance_ith_element > 2))
            {
                vector<int> result_elem(3,0);
                result.push_back(result_elem);
            }

            // check for triplet with 1st two elements as the current num and 3rd element as > current num
            if (n_instance_ith_element > 1)
            {
                if (first_elem < 0) // check if required to avoid case where first_elem=0 as that has been covered above.
                {
                    int third_elem = 0 - 2*first_elem;
                    assert((third_elem>first_elem) && "third_elem should be greater than first_elem");

                    unordered_map<int, int>::iterator mapIt = num_count_map.find(third_elem);

                    if (mapIt != num_count_map.end())
                    {
                        vector<int> result_elem{first_elem, first_elem, third_elem};
                        result.push_back(result_elem);
                    }
                }

            }

            // check for the triplet where 1st element is the current num and the rest elements > current num
            // case a: 2nd and 3rd elements are same. Possible if 2nd element have multiple instances.
            // case b: 3rd element > 2nd element
            int j = i+1;
            while (j < uniq_sorted_nums.size())
            {
                int second_elem = uniq_sorted_nums[j];
                int third_elem = 0 - (first_elem + second_elem);

                if (third_elem < second_elem)
                {
                    // triplet won't satisfy the constraint
                    break;
                }
                else if (second_elem == third_elem)
                {
                    // second_elem should have > 1 instance
                    unordered_map<int, int>::iterator mapIt = num_count_map.find(second_elem);
                    if ((*mapIt).second > 1)
                    {
                        vector<int> result_elem{first_elem, second_elem, third_elem};
                        result.push_back(result_elem);
                    }
                }
                else
                {
                    // case: third_elem > second_elem
                    unordered_map<int, int>::iterator mapIt = num_count_map.find(third_elem);

                    if (mapIt != num_count_map.end())
                    {
                        vector<int> result_elem{first_elem, second_elem, third_elem};
                        result.push_back(result_elem);
                    }
                }

                ++j;
            }

            // updating i so that we attempt to create triplet with 1st element as the next bigger element
            ++i;
        }

        return result;
    }
};

int main(int argc, char ** argv)
{
    Solution sln;

    int arr[6] = {-1, 0, 1, 2, -1, -4};
    // int arr[4] = {0,0,0,0};
    vector<int> nums(arr, arr+sizeof(arr)/sizeof(arr[0]));
    vector<vector<int>> result = sln.threeSum(nums);

    for (int i=0; i != result.size(); ++i)
    {
        cout << "triple #" << i << ": ";
        cout << result[i][0];
        for (int j=1; j != result[i].size(); ++j)
        {
            cout << "," << result[i][j];
        }
        cout << endl;
    }
}


/**
Time complexity: O(n^2) worst case
*/
