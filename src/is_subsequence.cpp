// https://leetcode.com/problems/is-subsequence/?tab=Description
// Mar 05, 2017

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (t.size() < s.size())
        {
            return false;
        }

        unsigned int i = 0;
        unsigned int j = 0;
        bool flag_is_subsequence = true;

        while (i < s.size())
        {
            while (j < t.size())
            {
                if (s[i] != t[j])
                {
                    ++j;
                }
                else
                {
                    break;
                }
            }

            if (j == t.size())
            {
                flag_is_subsequence = false;
                break;
            }
            else
            {
                // case: s[i] == t[j]
                ++i;
                ++j;
            }
        }

        return flag_is_subsequence;
    }
};

int main(int argc, char** argv)
{
    unsigned test_case = 1;
    Solution sln;

    switch (test_case)
    {
    case 0:
        {
            string s = "abc";
            string t = "ahbgdc";
            /*
            unsigned int i = 0;
            unsigned int j = 1;
            if (s[i] != t[j])
            {
                cout << "not equal" << endl;
            }
            */
            bool flag_is_subsequence = sln.isSubsequence(s,t);
            cout << "is subsequence: " << flag_is_subsequence << endl;
            break;
        }
    case 1:
        {
            string s = "axc";
            string t = "ahbgdc";
            bool flag_is_subsequence = sln.isSubsequence(s,t);
            cout << "is subsequence: " << flag_is_subsequence << endl;
            break;
        }
    }

    return 0;
}
