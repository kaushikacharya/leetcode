// https://oj.leetcode.com/problems/minimum-path-sum/
// Date: Nov 22, 2014

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int> > &grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        // we will only store the path sum for a single row.
        // we will move from last to first row.
        vector<int> vec;
        // assign zeros
        for (int col=0; col != n; ++col)
        {
            vec.push_back(0);
        }
        // populate the path sum for each cell of the last row i.e. bottom row
        for (int col=n-1; col >= 0; --col)
        {
            if (col == (n-1))
            {
                vec[col] = grid[m-1][col];
            }
            else
            {
                vec[col] = grid[m-1][col] + vec[col+1];
            }
        }

        // now compute min path of other rows in descending order i.e. bottom to top
        for (int row=m-2; row >= 0; --row)
        {
            vec[n-1] += grid[row][n-1];
            for (int col=n-2; col >=0; --col)
            {
                vec[col] = grid[row][col] + min(vec[col], vec[col+1]);
            }
        }

        return vec[0];
    }
};

int main(int argc, char* argv[])
{
    Solution sln;
    return 0;
}
