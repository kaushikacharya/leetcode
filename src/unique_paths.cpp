// https://oj.leetcode.com/problems/unique-paths/
// Date: Nov 14, 2014

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    long uniquePaths(int m, int n)
    {
        row_ = m;
        col_ = n;

        bool flag_is_top_down = false;

        if (flag_is_top_down)
        {
            return compute_paths_top_down(0,0);
        }
        else
        {
            return compute_paths_bottom_up();
        }
    }
private:
    int row_, col_;
private:
    long compute_paths_top_down(int i, int j)
    {
        // Note: This is an inefficient solution as it will take up lot of memory stack.
        if ((i == (row_-1)) || (j == (col_-1)))
        {
            return 1;
        }
        long sum = compute_paths_top_down(i+1,j) + compute_paths_top_down(i,j+1);
        return sum;
    }

    long compute_paths_bottom_up()
    {
        // space complexity O(n)
        vector<long> vec;
        vec.reserve(col_);

        // initializing values for the last row
        for (int j=0; j != col_; ++j)
        {
            vec.push_back(1);
        }

        int i = row_ - 2;

        while (i >= 0)
        {
            int j = col_ - 2;
            while (j >= 0)
            {
                vec[j] += vec[j+1];
                --j;
            }
            --i;
        }

        return vec[0];
    }
};

int main(int argc, char* argv[])
{
    int m = 100;
    int n = 100;
    Solution sln;
    long num_unique_paths = sln.uniquePaths(m,n);
    cout << "Unique Paths: " << num_unique_paths << endl;
    return 0;
}

/*
status: compile error :: though its running properly here in local m/c

space complexity is reduced from O(m*n) to O(n) as suggested here:
https://oj.leetcode.com/discuss/10263/solution-anyone-recursive-solution-without-compromising
*/
