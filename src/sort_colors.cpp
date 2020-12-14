// https://leetcode.com/problems/sort-colors/
// June 11, 2016

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums)
    {
        unordered_map<int,int> color_count_map;
        for (int color_i=0; color_i != 3; ++color_i)
        {
            color_count_map.insert(make_pair(color_i,0));
        }

        for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
        {
            unordered_map<int,int>::iterator map_it = color_count_map.find(*it);
            ++((*map_it).second);
        }

        // Now sort the vector nums
        int count_i = 0;
        for (int color_i = 0; color_i != 3; ++color_i)
        {
            unordered_map<int,int>::iterator map_it = color_count_map.find(color_i);

            if (map_it != color_count_map.end())
            {
                int color_count = (*map_it).second;
                for (int i = count_i; i != (count_i+color_count); ++i)
                {
                    nums[i] = color_i;
                }
                count_i += color_count;
            }
        }

    }
};

void display_nums(vector<int>& nums)
{
    for(vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
    {
        cout << *it << ",";
    }
    cout << endl;
}

int main(int argc, char* argv[])
{
    vector<int> nums = {2,0,1,0,1,0};
    cout << "pre-sort: ";
    display_nums(nums);
    Solution sln;
    sln.sortColors(nums);
    cout << "Post sort: ";
    display_nums(nums);

    return 0;
}

/**
* Have a look at https://leetcode.com/discuss/24977/solution-instance-dutch-national-problem-edsger-dijkstra
*/
