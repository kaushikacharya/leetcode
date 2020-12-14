// https://oj.leetcode.com/problems/longest-substring-without-repeating-characters/
// Date: Nov 20, 2014

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string str)
    {
        if (str.size() == 0)
        {
            return 0;
        }

        unordered_set<char> max_set, cur_set;
        int max_begin, cur_begin;

        max_begin = 0;
        cur_begin = 0;
        max_set.insert(str[0]);
        cur_set.insert(str[0]);

        for (int ch_i = 1; ch_i != str.size(); ++ch_i)
        {
            unordered_set<char>::iterator it = cur_set.find(str[ch_i]);
            if (it == cur_set.end())
            {
                cur_set.insert(str[ch_i]);
                if (max_set.size() < cur_set.size())
                {
                    max_set = cur_set;
                    max_begin = cur_begin;
                }
                /*
                if (max_set.size() > 12)
                {
                    cout << "ch_i: " << ch_i << endl;
                }
                */
            }
            else
            {
                // set the cur_set index from the element just after str[ch_i]
                while (true)
                {
                    cur_set.erase(str[cur_begin]);
                    ++cur_begin;
                    if (str[cur_begin-1] == str[ch_i])
                    {
                        break;
                    }
                }
                /*
                if (cur_set.size() == 0)
                {
                    cout << "cur_begin: " << cur_begin << " :: ch_i: " << ch_i << endl;
                }
                */
                cur_set.insert(str[ch_i]);
            }
        }

        return max_set.size();
    }
};

int main(int argc, char* argv[])
{
    //string str = "hnwnkuewhsqmgbbuqcljjivswmdkqtbxixmvtrrbljptnsnfwzqfjmafadrrwsofsbcnuvqhffbsaqxwpqcac";
    string str = "wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco";
    Solution sln;
    int len_longest_substr = sln.lengthOfLongestSubstring(str);
    cout << "len: " << len_longest_substr << endl;
    return 0;
}
