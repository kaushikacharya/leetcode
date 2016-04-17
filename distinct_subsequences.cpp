// https://oj.leetcode.com/problems/distinct-subsequences/
// Date: Feb 01, 2015

#include <iostream>
#include <string>
//#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
public:
    // count the number of distinct subsequences of T in S
    int numDistinct(string S, string T)
    {
        if (S.size() < T.size()) // string S is smaller than string T
        {
            return 0;
        }

        vector<int> prevVec(T.size(), 0);

        if (T[0] == S[0])
        {
            prevVec[0] = 1;
        }
        for (int col_i=1; col_i != S.size(); ++col_i)
        {
            vector<int> curVec(T.size(), 0);

            // checking if first element of T matches with S[col_i]
            // i.e. row_i = 0
            if (col_i <= (S.size()-T.size()))
            {
                curVec[0] = prevVec[0];
                if (T[0] == S[col_i])
                {
                    curVec[0] += 1;
                }
            }

            int row_st = max(1, (int)T.size()-((int)S.size()-col_i));
            int row_en = min(row_st+col_i-1, (int)T.size()-1);

            for (int row_i = row_st; row_i != (row_en+1); ++row_i)
            {
                // first if we don't consider matching with S[col_i]
                curVec[row_i] += prevVec[row_i];
                // next if we consider matching with S[col_i]
                if (T[row_i] == S[col_i])
                {
                    curVec[row_i] += prevVec[row_i-1];
                }
            }

            prevVec = curVec;
        }

        return prevVec.back();
    }
};


int main(int argc, char* argv[])
{
    string S = "rrabbbit";
    string T = "rabbit";

    Solution sln;
    int count_distinct_subseq = sln.numDistinct(S,T);
    cout << count_distinct_subseq << endl;
    return 0;
}
