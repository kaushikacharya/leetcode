// https://leetcode.com/problems/largest-number/
// May 21, 2016

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string test_str_order(string str1, string str2)
{
    return min(str1, str2);
}

class Solution {
public:
    string largestNumber(vector<int>& nums)
    {
        vector<string> vecNumStr;
        vecNumStr.reserve(nums.size());

        stringstream ss;
        for (vector<int>::iterator it = nums.begin(); it != nums.end(); ++it)
        {
            ss << *it;
            string str = ss.str();
            ss.str(string()); // clearing the stream
            vecNumStr.push_back(str);
        }

        /*
        cout << "Before sort: " << endl;
        for (vector<string>::iterator it = vecNumStr.begin(); it != vecNumStr.end(); ++it)
        {
            cout << *it << ",";
        }
        cout << endl;
        */
        sort(vecNumStr.begin(), vecNumStr.end(), comp);
        /*
        cout << "After sort: " << endl;
        for (vector<string>::iterator it = vecNumStr.begin(); it != vecNumStr.end(); ++it)
        {
            cout << *it << ",";
        }
        cout << endl;
        */

        // Now create the largest number string
        string largest_number_str = "";
        for (vector<string>::iterator it = vecNumStr.begin(); it != vecNumStr.end(); ++it)
        {
            largest_number_str += *it;
        }

        return largest_number_str;
    }
private:
    static bool comp(string str1, string str2)
    {
        // returns True if str1 >= str2

        // "9" > "95" since "995" > "959"
        // "68" > "6" since "686" > "668"
        int n1 = str1.size();
        int n2 = str2.size();
        int m = (n1<=n2)?n1:n2;
        int flag_compare = 0; // 0 => equal, -1 => str1 < str2, +1 => str1 > str2

        int j = 0;
        while ( (flag_compare==0) && ((m*j < n1) || (m*j < n2)) )
        {
            // strings are equal till now and there are still more chars to be compared
            if (n1 <= n2)
            {
                int i = 0;
                while ( (i < m) && ((j*m+i) < n2))
                {
                    if (str1[i] < str2[j*m+i])
                    {
                        flag_compare = -1;
                        break;
                    }
                    else if (str1[i] > str2[j*m+i])
                    {
                        flag_compare = 1;
                        break;
                    }
                    ++i;
                }
            }
            else
            {
                int i = 0;
                while ( (i < m) && ((j*m+i) < n1) )
                {
                    if (str1[j*m+i] < str2[i])
                    {
                        flag_compare = -1;
                        break;
                    }
                    else if (str1[j*m+i] > str2[i])
                    {
                        flag_compare = 1;
                        break;
                    }
                    ++i;
                }

            }

            ++j;
        }


        bool flag_greater_than_equal_to = (flag_compare >=0) ? true : false;

        return flag_greater_than_equal_to;
    }
};

int main(int argc, char* argv[])
{
    /*
    Had to use stringstream since to_string() isn't available in the version of g++ I am using.
    */
    /*
    stringstream  ss;
    ss << 95;
    string str1 = ss.str();
    ss.str(string());

    ss << 9;
    string str2 = ss.str();
    ss.str(string());

    cout << "str1: " << str1 << " :: str2: " << str2 << endl;

    string min_str = test_str_order(str2, str1);
    cout << "min string: " << min_str << endl;
    */

    vector<int> nums = {0,0,0,0,0,0};
    Solution sln;
    string largest_number_str = sln.largestNumber(nums);
    cout << "largest number: " << largest_number_str << endl;

    return 0;
}

/*
Status: Runtime error

http://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-so-g
http://stackoverflow.com/questions/5590381/easiest-way-to-convert-int-to-string-in-c
http://stackoverflow.com/questions/20731/how-do-you-clear-a-stringstream-variable

ybungalobill's answer on using static for comparison function which is part of class.
http://stackoverflow.com/questions/4288439/problem-using-a-compare-function-inside-of-a-class-for-sort
*/
