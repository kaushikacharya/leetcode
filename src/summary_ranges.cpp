// https://leetcode.com/problems/summary-ranges/
// July 26, 2016

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums)
    {
        vector<string> vecRanges;
        if (nums.empty())
        {
            return vecRanges;
        }

        int st_range = nums.front();
        int en_range = st_range;

        for (size_t i = 1; i != nums.size(); ++i)
        {
            int cur_num = nums[i];

            if (cur_num == (en_range+1))
            {
                en_range = cur_num;
            }
            else
            {
                // start of new range
                // First add the previous range in output
                string str_range = create_range(st_range, en_range);
                vecRanges.push_back(str_range);

                // Assign the start of new range
                st_range = cur_num;
                en_range = cur_num;
            }
        }

        // add the last range
        string str_range = create_range(st_range, en_range);
        vecRanges.push_back(str_range);

        return vecRanges;
    }
private:
    string create_range(int st_range, int en_range)
    {
        stringstream ss;
        ss << st_range;
        string str_range = ss.str();
        ss.str(string());

        if (st_range < en_range)
        {
            str_range += "->";
            ss << en_range;
            str_range += ss.str();
            ss.str(string());
        }

        return str_range;
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums = {0,4,5,7};
    Solution sln;
    vector<string> summary_ranges = sln.summaryRanges(nums);
    for (vector<string>::iterator it = summary_ranges.begin(); it != summary_ranges.end(); ++it)
    {
        if (it != summary_ranges.begin())
        {
            cout << ",";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
