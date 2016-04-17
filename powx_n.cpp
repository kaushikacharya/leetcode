// https://oj.leetcode.com/problems/powx-n/
// Date: Dec 27, 2014

#include <iostream>

using namespace std;

class Solution {
public:
    double pow(double x, int n)
    {
        if (n == 0)
        {
            return 1;
        }
        else if (n == 1)
        {
            return x;
        }
        else if (n == -1)
        {
            return 1/x;
        }
        else
        {
            double y = pow(x, n/2);
            double z = y*y;

            if (n%2 == 1)
            {
                z *= x;
            }
            else if (n%2 == -1)
            {
                z *= 1/x;
            }

            return z;
        }
    }
};

int main(int argc, char* argv[])
{
    //cout << -3/2 << endl;
    double x = -1.00000;
    int n = -2147483645;

    Solution sln;
    cout << sln.pow(x, n) << endl;

    return 0;
}

/*
http://www.geeksforgeeks.org/write-a-c-program-to-calculate-powxn/
*/
