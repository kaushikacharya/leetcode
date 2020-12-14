// https://oj.leetcode.com/problems/word-break/
// Date: Nov 12, 2014

#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool wordBreak(string str, unordered_set<string> &dict)
    {
        int n = str.size();
        vector<vector<int> > vec;

        for (int i=0; i != n; ++i)
        {
            vec.push_back(vector<int>());
        }

        stack<int> stk;
        stk.push(0);

        bool flag_word_break = false;
        while (!stk.empty())
        {
            int curPos = stk.top();
            int nextPos;

            if (vec[curPos].size() == 0)
            {
                nextPos = curPos;
            }
            else
            {
                // picking the next of what has been already checked in previous iteration
                int sz = vec[curPos].size();
                nextPos = vec[curPos][sz-1] + 1;
            }

            // str[curPos, .... , nextPos] :: check if this is a word in dict
            bool flag_word_present = false;
            while (nextPos < n)
            {
                string word = str.substr(curPos, nextPos-curPos+1);
                if (dict.find(word) == dict.end())
                {
                    ++nextPos;
                }
                else
                {
                    flag_word_present = true;
                    break;
                }
            }

            if (flag_word_present)
            {
                if (nextPos == (n-1))
                {
                    // word-break is possible
                    flag_word_break = true;
                    break;
                }
                else
                {
                    vec[curPos].push_back(nextPos);
                    stk.push(nextPos+1);
                }
            }
            else
            {
                // No word present in dict which can be formed by chars in str[curPos, ....]
                // storing this info so that we don't need to check in dict again for str[curPos, ...]
                vec[curPos].push_back(n-1);
                stk.pop();
            }
        }

        return flag_word_break;
    }
};

int main(int argc, char* argv[])
{
    string str = "leetcode";
    int sz = str.size();
    string sub_str = str.substr(2,4);
    unordered_set<string> dict;
    dict.insert("le");
    dict.insert("code");

    Solution sln;
    bool flag_word_break = sln.wordBreak(str,dict);
    return 0;
}
