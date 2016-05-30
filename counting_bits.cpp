// https://leetcode.com/problems/counting-bits/
// May 28, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> countBits(int num)
    {
        vector<int> vecBitCount;
        // initialize with zeros
        for (int i=0; i != (num+1); ++i)
        {
            vecBitCount.push_back(0);
        }

        // 2^r has single 1 bit
        vecBitCount[0] = 0; // For int i=0
        int r = 1;

        while (r <= num)
        {
            vecBitCount[r] = 1; // r is power of 2
            int i = 1;
            while ((i < r) && ((r+i) <= num))
            {
                vecBitCount[r+i] = vecBitCount[r] + vecBitCount[i];
                ++i;
            }
            r *= 2;
        }

        return vecBitCount;
    }
};

int main(int argc, char* argv[])
{
    int num = 0;
    Solution sln;
    vector<int> vecBitCount = sln.countBits(num);
    for (vector<int>::iterator it = vecBitCount.begin(); it != vecBitCount.end(); ++it)
    {
        cout << *it << ",";
    }
    return 0;
}
