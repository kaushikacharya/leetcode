// https://leetcode.com/problems/decode-ways/
// May 07, 2016

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int numDecodings(string str)
    {
        if (str.empty())
        {
            return 0;
        }
        vector<int> vecCountOfWays;
        vecCountOfWays.reserve(str.size());
        for (unsigned int i=0; i != str.size(); ++i)
        {
            vecCountOfWays.push_back(0);
        }

        // Now compute number of decode ways.
        for (unsigned int i=0; i != str.size(); ++i)
        {
            // cout << "val: " << str[i] - '0' << endl;
            int p = 0;
            int q = 0;

            // First check feasibility of mapping str[i] to char
            int val_single_digit = str[i]-'0';
            // cout << "val: single digit: " << val_single_digit << endl;
            if ((val_single_digit > 0) && (val_single_digit <= 9))
            {
                if (i > 0)
                {
                    p = vecCountOfWays[i-1];
                }
                else
                {
                    p = 1;
                }
            }

            // Now check feasibility of mapping str[i-1,i] to char
            if (i > 0)
            {
                int val_double_digit = 10*int(str[i-1] - '0') + int(str[i] - '0');
                // cout << "val: double digit: " << val_double_digit << endl;
                if ((val_double_digit > 9) && (val_double_digit < 27))
                {
                    if (i > 1)
                    {
                        q = vecCountOfWays[i-2];
                    }
                    else
                    {
                        q = 1;
                    }
                }
            }

            vecCountOfWays[i] = p + q;

            if (vecCountOfWays[i] == 0)
            {
                break; // Not feasible to decode the string. Hence no point in analyzing further chars of str.
            }
        }

        return vecCountOfWays.back();
    }
};

int main(int argc, char* argv[])
{
    string str = "";
    Solution sln;
    int count_of_decode_ways = sln.numDecodings(str);
    cout << "Total number of ways to decode: " << count_of_decode_ways << endl;

    return 0;
}
