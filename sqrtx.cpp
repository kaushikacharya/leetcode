// https://leetcode.com/problems/sqrtx/
// May 26, 2016

#include <iostream>

using namespace std;

class Solution {
public:
    int mySqrt(int x)
    {
        if (x == 0)
        {
            return 0;
        }
        int p = 1;
        int q = x;

        while (p < q-1)
        {
            int mid = (p+q)/2;
            int mid_sqr = mid*mid;

            if (mid_sqr == x)
            {
                p = mid;
                q = mid;
            }
            else if (mid_sqr > x)
            {
                q = mid;
            }
            else
            {
                p = mid;
            }
        }

        return p;
    }
};

int main(int argc, char* argv[])
{
    Solution sln;
    int x = 2147395599;
    int sqrt_x = sln.mySqrt(x);
    cout << "sqrt: " << sqrt_x << endl;
    return 0;
}

/*
Status: Time Limit Exceeded
*/
