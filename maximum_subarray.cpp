// https://oj.leetcode.com/problems/maximum-subarray/
// Date: Nov 12, 2014

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSubArray(int A[], int n)
    {
        // B[i] = max sum of subarray starting from i'th position
        // solved in O(n) using dynamic programming
        vector<int> B(A,A+n);
        int maxSum = B[n-1];

        for (int i = n-2; i >= 0; --i)
        {
            if (B[i+1] > 0)
            {
                B[i] += B[i+1];
            }
            if (B[i] > maxSum)
            {
                maxSum = B[i];
            }
        }

        return maxSum;
    }
};

int main(int argc, char* argv[])
{
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    Solution sln;
    int maxSum = sln.maxSubArray(A, sizeof(A)/sizeof(A[0]));

    return 0;
}

/*
http://stackoverflow.com/questions/20721294/size-of-int-and-sizeof-int-pointer-on-a-64-bit-machine
*/
