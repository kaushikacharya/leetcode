// https://leetcode.com/problems/count-numbers-with-unique-digits/
// June 14, 2016

#include <iostream>

using namespace std;

class Solution {
public:
    int countNumbersWithUniqueDigits(int n)
    {
        if (n == 0)
        {
            return 1; //case: 0 <= x < 1
        }
        int sum_count = 10; // 1-digit

        int mult = 9;
        // n>10 : unique digits not possible
        for (int i=1; i != min(n,10); ++i)
        {
            mult *= (10-i);
            sum_count += mult;
        }

        return sum_count;
    }
};

int main(int argc, char* argv[])
{
    Solution sln;
    int n = 3;
    int sum_count = sln.countNumbersWithUniqueDigits(n);
    cout << "sum count: " << sum_count << endl;
    return 0;
}
