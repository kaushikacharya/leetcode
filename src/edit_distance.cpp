// https://oj.leetcode.com/problems/edit-distance/
// Date: Dec 23, 2014

#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size();
        int n = word2.size();

        if (m == 0)
        {
            return n;
        }
        else if (n == 0)
        {
            return m;
        }

        // penalty matrix
        // instead of O(m*n) space we use O(n) space
        vector<vector<int> > matrix(2, vector<int>(n+1, numeric_limits<int>::max()));

        // populate 1st row
        for (int j=0; j != (n+1); ++j)
        {
            matrix[0][j] = j;
        }

        for (int i = 1; i != (m+1); ++i)
        {
            int prev_row = (i+1) % 2;
            int cur_row = i % 2;

            matrix[cur_row][0] = i;

            for (int j=1; j != (n+1); ++j)
            {
                int val0 = matrix[prev_row][j-1] + ((word1[i-1] == word2[j-1]) ? 0 : 1);
                int val1 = matrix[prev_row][j] + 1; //penalty for gap
                int val2 = matrix[cur_row][j-1] + 1; //penalty for gap

                int val = val0;
                if (val1 < val)
                {
                    val = val1;
                }
                if (val2 < val)
                {
                    val = val2;
                }

                matrix[cur_row][j] = val;
            }
        }

        return matrix[m%2][n];
    }
};

int main(int argc, char* argv[])
{
    string word1 = "AGGGCT";
    string word2 = "AGGCA";

    Solution sln;
    int edist = sln.minDistance(word2, word1);
    cout << edist << endl;

    return 0;
}

/*
http://stackoverflow.com/questions/13121469/initializing-a-vector-of-vectors-having-a-fixed-size-with-boost-assign
*/
