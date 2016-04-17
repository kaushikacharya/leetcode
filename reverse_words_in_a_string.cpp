// https://oj.leetcode.com/problems/reverse-words-in-a-string/
// Date: Nov 19, 2014

#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    // Note: leetcode provides alternate solution which doesn't need stack.
    //       Continental Automotive expected this in the interview.
    void reverseWords(string &str)
    {
        vector<string> vecToken;
        tokenizer(str, vecToken);

        stack<string> stk;
        for (vector<string>::iterator it = vecToken.begin(); it != vecToken.end(); ++it)
        {
            //cout << "stk elem pushed:" << *it << endl;
            stk.push(*it);
        }

        if (stk.empty())
        {
            str = "";
        }
        else
        {
            string outStr;
            //cout << "stk elem:" << stk.top() << endl;
            outStr = stk.top();
            stk.pop();

            while (!stk.empty())
            {
                outStr += " ";
                outStr += stk.top();
                //cout << "stk elem:" << stk.top() << endl;
                stk.pop();
            }

            //cout << "reversed words:" << outStr << endl;
            str = outStr;
        }
    }
private:
    void tokenizer(string& str, vector<string>& vecToken, string delimiters=" ")
    {
        int prevPos = str.find_first_not_of(delimiters);
        int curPos = str.find_first_of(delimiters, prevPos);

        while ( (prevPos != str.npos) || (curPos != str.npos) )
        {
            vecToken.push_back(str.substr(prevPos,curPos-prevPos));
            prevPos = str.find_first_not_of(delimiters, curPos);
            curPos = str.find_first_of(delimiters, prevPos);
        }
    }
};

int main(int argc, char* argv[])
{
    string str = "the sky is blue";
    /*
    vector<string> vecToken;
    tokenizer(str, vecToken);

    for (vector<string>::iterator it = vecToken.begin(); it != vecToken.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Tokenization done" << endl;
    */

    Solution sln;
    sln.reverseWords(str);
    cout << "reversed words in string: " << str << endl;

    return 0;
}

/*
C based tokenizer:
http://www.cplusplus.com/reference/cstring/strtok/

C++ based tokenizer:
http://www.oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
*/
