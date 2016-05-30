// https://leetcode.com/problems/integer-break/
// May 26, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int integerBreak(int n)
    {
        // initialize
        vecMaxProd_.reserve(n);
        vecMaxProd_.push_back(0);

        for (int i=2; i!=(n+1); ++i)
        {
            // compute max product for integer break of int i
            int max_prod = 0;
            for (int j=1; j != i; ++j)
            {
                int val = j*max(i-j, vecMaxProd_[i-j-1]);
                if (max_prod < val)
                {
                    max_prod = val;
                }
            }

            vecMaxProd_[i-1] = max_prod;
        }

        return vecMaxProd_[n-1];
    }
private:
    vector<int> vecMaxProd_; // vecMaxProd_[i-1]: max product for integer break of i
};

int main(int argc, char* argv[])
{
    int n = 3;
    Solution sln;
    int max_prod = sln.integerBreak(n);
    cout << "max prod: " << max_prod << endl;
    return 0;
}

/*
TBD: Acording to Leetcode, there's a O(n) solution.
*/
