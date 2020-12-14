// https://leetcode.com/problems/sqrtx/
// May 26, 2016

#include <iostream>

using namespace std;

class Solution {
public:
    int mySqrt(int x)
    {
        if (x <= 1)
        {
            return x;
        }

        int p = 0;
        int q = x;
        int res = x;
        while (true)
        {
            p = (p+q)/2;
            q = x/p;

            int min_pq = min(p,q);
            if (min_pq == res)
            {
                break;
            }
            else
            {
                res = min_pq;
            }
        }

        return res;
        /*
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
        */
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
https://leetcode.com/discuss/72319/very-easy-java-method-using-binary-search-with-explanation
My initial attempt should have been like this.

https://en.wikipedia.org/wiki/Integer_square_root
https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Babylonian_method
*/
