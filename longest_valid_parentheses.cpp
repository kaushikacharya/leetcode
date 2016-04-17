// https://oj.leetcode.com/problems/longest-valid-parentheses/
// Date: Nov 23, 2014

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string str)
    {
        if (str.size() == 0)
        {
            return 0;
        }
        stack<pair<char,int> > stk;
        vector<int> vec; // keeps length of the longest valid parentheses ending at position i
        for (int i=0; i != str.size(); ++i)
        {
            vec.push_back(0);
        }

        int longest = 0;
        stk.push(make_pair(str[0],0));
        for (int i=1; i != str.size(); ++i)
        {
            if ((str[i] == ')') && (!stk.empty()))
            {
                pair<char,int> elem = stk.top();
                if (elem.first == '(')
                {
                    stk.pop();
                    // first consider the parentheses ending at pos_i
                    vec[i] = i - elem.second + 1;
                    // next consider the parentheses which ended just before starting parentheses
                    // i.e. ()(())
                    if (elem.second > 0)
                    {
                        vec[i] += vec[elem.second-1];
                    }
                    if (longest < vec[i])
                    {
                        longest = vec[i];
                    }
                }
                else
                {
                    stk.push(make_pair(str[i],i));
                }
            }
            else
            {
                stk.push(make_pair(str[i],i));
            }
        }

        return longest;
    }
};

int main(int argc, char* argv[])
{
    string str = "()(()())";
    Solution sln;
    int len_longest_valid_parentheses = sln.longestValidParentheses(str);
    cout << len_longest_valid_parentheses << endl;
    return 0;
}
