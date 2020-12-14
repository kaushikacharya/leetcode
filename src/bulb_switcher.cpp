// https://leetcode.com/problems/bulb-switcher/
// May 28, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int bulbSwitch(int n)
    {
        if (n <= 1)
        {
            return n;
        }

        // The problem translates to if a number x has odd number of factors.
        // Odd number => bulb switched on
        vector<bool> vecSwitch;
        vecSwitch.reserve(n);
        // Note: vecSwitch[i-1] represents number i
        for (int i = 0; i != n; ++i)
        {
            vecSwitch.push_back(true);
        }

        for (int i = 2; i != (n+1); ++i)
        {
            int j = 1;
            while (i*j <= n)
            {
                // switching on to off and vice-versa
                vecSwitch[i*j-1] = !vecSwitch[i*j-1];
                ++j;
            }
        }

        int countSwitchOn = 0;
        for (int i=0; i!=n; ++i)
        {
            if (vecSwitch[i])
            {
                ++countSwitchOn;
            }
        }

        return countSwitchOn;
    }
};


int main(int argc, char* argv[])
{
    int n = 1000000;
    Solution sln;
    int countSwitchOn = sln.bulbSwitch(n);
    cout << "Bulbs switch on after n rounds: " << countSwitchOn << endl;
    return 0;
}

/*
Status: Time Limit Exceeded
https://en.wikipedia.org/wiki/Harmonic_number

Based on the harmonic number, my implementation should be O(n)
"The associated harmonic series grows without limit, albeit very slowly, roughly approaching the natural logarithm function"
*/
