// https://leetcode.com/problems/minimum-window-substring/
// June 20, 2016

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t)
    {
        if (t == "")
        {
            return "";
        }

        // create map with key as char and value as count of char in the string t
        unordered_map<char,int> t_map;
        for (int t_i=0; t_i != t.size(); ++t_i)
        {
            char t_char = t[t_i];
            unordered_map<char,int>::iterator it = t_map.find(t_char);
            if (it == t_map.end())
            {
                t_map.insert(make_pair(t_char,1));
            }
            else
            {
                ++((*it).second);
            }
        }

        bool flag_window_found = false;
        string min_window = "";

        // create an index array: elements in this array represents indices of string s where s[index] is present in string t
        vector<int> index_array;
        int i = 0;
        int j = -1;
        // substring considered s[index_array[i],....index_array[j]]
        // create two map
        // (a) subarray_map: map of chars belonging to substring. Only chars which are present in t are considered.
        // (b) reqd_subarray_map: map still required for substring to contain string t
        unordered_map<char,int> subarray_map;
        unordered_map<char,int> reqd_subarray_map = t_map;

        for (int s_i = 0; s_i != s.size(); ++s_i)
        {
            char curChar = s[s_i];
            unordered_map<char,int>::iterator it = t_map.find(curChar);
            if (it == t_map.end())
            {
                continue; // we are not interested in this char as its not part of string t
            }
            index_array.push_back(s_i);
            ++j;

            // update the maps
            it = subarray_map.find(curChar);
            if (it == subarray_map.end())
            {
                subarray_map.insert(make_pair(curChar,1));
            }
            else
            {
                ++((*it).second);
            }

            it = reqd_subarray_map.find(curChar);
            if (it != reqd_subarray_map.end())
            {
                if ((*it).second == 1)
                {
                    reqd_subarray_map.erase(it);
                }
                else
                {
                    --((*it).second);
                }
            }

            if (reqd_subarray_map.empty())
            {
                // Found the substring in s which contains all the chars in t
                if (!flag_window_found)
                {
                    // window found for first time
                    flag_window_found = true;
                    min_window = s.substr(index_array[i], index_array[j]-index_array[i]+1);
                }
                else if ( (index_array[j]-index_array[i]+1) < min_window.size())
                {
                    // update only if current window is smaller than the previous window
                    min_window = s.substr(index_array[i], index_array[j]-index_array[i]+1);
                }

                // check if we can increment i for the current j and get a reduced window
                while (i != j)
                {
                    // remove the char at index_array[i] and see if the substring still contain all the chars of string t
                    char prevChar = s[index_array[i]];
                    ++i;
                    // check if the current window contains all the chars in t
                    // i.e. with updated i to existing j
                    unordered_map<char,int>::iterator it_subarray_map = subarray_map.find(prevChar);
                    unordered_map<char,int>::iterator it_t_map = t_map.find(prevChar);

                    // decrementing count of prevChar as we have incremented i
                    --((*it_subarray_map).second);

                    if ( (*it_t_map).second <= (*it_subarray_map).second )
                    {
                        if ( (index_array[j]-index_array[i]+1) < min_window.size())
                        {
                            min_window = s.substr(index_array[i], index_array[j]-index_array[i]+1);
                        }
                    }
                    else
                    {
                        reqd_subarray_map.insert(make_pair(prevChar,1));
                        break;
                    }
                }

                if (t.size() == min_window.size())
                {
                    break; // smaller window is not possible
                }
            }
        }

        return min_window;
    }
};

int main(int argc, char* argv[])
{
    string s = "ADOBECODEBANC";
    string t = "ABCC";

    Solution sln;
    string min_window = sln.minWindow(s, t);
    cout << "min window: " << min_window << endl;

    return 0;
}

/**
* Doubt clearance:
*   https://leetcode.com/discuss/2702/can-t-have-characters-repeating
*
* Solution by others:
*   https://leetcode.com/discuss/18584/sharing-my-straightforward-o-n-solution-with-explanation
*   (index_array used by my solution could be replaced if monaziyi's solution is followed.
*
* c++ tip:
*   value in unordered_map for the keys can be incremented without using the iterator/find
*   http://stackoverflow.com/questions/9900247/how-to-modify-value-in-unorderedmap
*   (It's also there in monaziyi's solution)
*/
