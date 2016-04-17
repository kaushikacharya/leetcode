// https://oj.leetcode.com/problems/longest-palindromic-substring/
// Date: Dec 20, 2014

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string longestPalindrome(string str)
    {
        // dynamic programming approach :: O(n^2) time complexity

        if (str.size() <= 1)
        {
            return str;
        }
        // use 2*n sized vec so that memory usage is O(n)
        vector<vector<bool> > vec;
        for (int i=0; i != 2; ++i)
        {
            vec.push_back(vector<bool>());
            vec[i].reserve(str.size());
        }
        int longest_palin_begin = 0;
        int longest_palin_end = 0;
        // single element is palindromic by itself
        vector<bool> vec_flag_any;
        vec_flag_any.push_back(true);
        for (int j=0; j != str.size(); ++j)
        {
            vec[0].push_back(true);
        }
        // checking if two consecutive elements are same
        vec_flag_any.push_back(false);
        for (int j=0; j != (str.size()-1); ++j)
        {
            vec[1].push_back(str[j] == str[j+1]);
            if (str[j] == str[j+1])
            {
                longest_palin_begin = j;
                longest_palin_end = j+1;
                vec_flag_any[1] = true;
            }
        }

        for (int iter_i=2; iter_i != str.size(); ++iter_i)
        {
            int i = iter_i % 2;
            vec_flag_any[i] = false;

            for (int j = 0; j != (str.size()-iter_i); ++j)
            {
                bool flag = false;

                if (vec[i][j+1])
                {
                    if (str[iter_i+j] == str[j])
                    {
                        flag = true;
                        longest_palin_begin = j;
                        longest_palin_end = iter_i+j;
                        vec_flag_any[i] = true;
                    }
                }

                vec[i][j] = flag;
            }

            // check if we need to do any more iteration
            if ((vec_flag_any[0] == false) && (vec_flag_any[1] == false))
            {
                break;
            }
        }

        return str.substr(longest_palin_begin, longest_palin_end-longest_palin_begin+1);

    }
};

int main(int argc, char* argv[])
{
    string str = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    Solution sln;
    cout << sln.longestPalindrome(str) << endl;
    return 0;
}

/*
http://leetcode.com/2011/11/longest-palindromic-substring-part-i.html

status: TLE
https://oj.leetcode.com/discuss/12525/why-my-o-n-2-dp-solution-got-aaaaaa-a-tle
*/
