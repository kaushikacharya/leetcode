// https://oj.leetcode.com/problems/evaluate-reverse-polish-notation/
// Date: Nov 25, 2014

#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string> &tokens)
    {
        stack<int> stk;

        for (int i=0; i != tokens.size(); ++i)
        {
            string token = tokens[i];
            int val;

            if ( (token == "+") || (token == "-") || (token == "*") || (token == "/"))
            {
                int b = stk.top();
                stk.pop();
                int a = stk.top();
                stk.pop();

                if (token == "+")
                {
                    val = a + b;
                }
                else if (token == "-")
                {
                    val = a - b;
                }
                else if (token == "*")
                {
                    val = a * b;
                }
                else if (token == "/")
                {
                    val = a / b;
                }
            }
            else
            {
                // token is int
                val = atoi(token.c_str());
            }

            stk.push(val);
        }

        int result = stk.top();
        stk.pop();
        return result;
    }
};

int main(int argc, char* argv[])
{
    string arr[] = {"4", "13", "5", "/", "+"};
    vector<string> vec(arr, arr+sizeof(arr)/sizeof(arr[0]));
    Solution sln;
    int result = sln.evalRPN(vec);
    return 0;
}

/*
http://stackoverflow.com/questions/650162/why-switch-statement-cannot-be-applied-on-strings
*/
