// https://leetcode.com/problems/permutations-ii/
// June 22, 2016

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int> > permuteUnique(vector<int>& nums)
    {
        unordered_map<int,int> num_map;
        for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
        {
            int num = *it;
            ++num_map[num];
        }

        vector<vector<int> > vecPermutation = permute_unique(num_map);
        return vecPermutation;
    }
private:
    vector<vector<int> > permute_unique(unordered_map<int,int> num_map)
    {
        vector<vector<int> > vecPermutation;

        if (num_map.empty())
        {
            return vecPermutation;
        }
        if (num_map.size() == 1)
        {
            unordered_map<int,int>::iterator it = num_map.begin();
            int num = (*it).first;
            int num_count = (*it).second;
            vector<int> permute;
            for (int i=0; i != num_count; ++i)
            {
                permute.push_back(num);
            }
            vecPermutation.push_back(permute);
            return vecPermutation;
        }

        for (unordered_map<int,int>::iterator it = num_map.begin(); it != num_map.end(); ++it)
        {
            int num = (*it).first;
            int num_count = (*it).second;

            unordered_map<int,int> num_sub_map = num_map;

            if (num_count > 1)
            {
                --num_sub_map[num];
            }
            else
            {
                num_sub_map.erase(num);
            }

            vector<vector<int> > vecSubPermutation = permute_unique(num_sub_map);
            for (vector<vector<int> >::iterator vecIt = vecSubPermutation.begin(); vecIt != vecSubPermutation.end(); ++vecIt)
            {
                vector<int> sub_permutation = *vecIt;
                sub_permutation.push_back(num);
                vecPermutation.push_back(sub_permutation);
            }
        }

        return vecPermutation;
    }
};


int main(int argc, char* argv[])
{
    vector<int> nums = {1,1,2,3,3};
    Solution sln;
    vector<vector<int> > vecPermutation = sln.permuteUnique(nums);
    int count_permutation = 0;
    for (vector<vector<int> >::iterator it = vecPermutation.begin(); it != vecPermutation.end(); ++it)
    {
        ++count_permutation;
        vector<int> permutation = *it;
        cout << count_permutation << ": " ;
        for (vector<int>::iterator pit = permutation.begin(); pit != permutation.end(); ++pit)
        {
            cout << *pit << ",";
        }
        cout << endl;
    }
    return 0;
}

/**
*   Approach: using swap of elements in vector. This doesn't use any extra memory. Its also recursive solution.
*   https://leetcode.com/discuss/25279/a-simple-c-solution-in-only-20-lines
*
*   Have a look at the solution provided in geeksforgeeks:
*   http://www.geeksforgeeks.org/print-all-permutations-of-a-string-with-duplicates-allowed-in-input-string/
*
*   Following is a method similar to mine but he/she has avoided creating of extra map: num_sub_map
*   https://leetcode.com/discuss/20598/accepted-backtracking-c-solution-by-using-map-28ms
*
*/
