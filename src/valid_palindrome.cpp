/*
    Problem: https://leetcode.com/problems/valid-palindrome/
    Date: Feb 10, 2023

    Approach:
    --------
    Two pointers
    - Explained in https://www.educative.io/courses/grokking-coding-interview-patterns-cpp/R1NKJD3XxBq

    Complexity:
    ----------
    Time: O(n)
    Memory: O(n)

    References:
    -----------
    - https://www.geeksforgeeks.org/iswalnum-function-in-c-stl/
        - Definition of alphanumeric characters.
*/

#include <lest.hpp>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        /* Create string from the input string by
            a. converitng upper case to lower case
            b. stripping off non-alphanumeric characters
        */ 
        string s_mod = "";

        for (unsigned int i=0; i != s.size(); ++i){
            char c = s[i];

            if (c >= 'A' && c <= 'Z'){
                s_mod += tolower(c);
            } 
            else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')){
                s_mod += c;
            }
            else {
                continue;
            }
        }

        // cout << "Modified string: " << s_mod << endl;

        // Now check whether the stripped string is palindrome or not
        if (s_mod.empty()){
            return true;
        }

        unsigned int left_ptr_pos = 0;
        unsigned int right_ptr_pos = s_mod.size()-1;

        while (left_ptr_pos < right_ptr_pos)
        {
            if (s_mod[left_ptr_pos] != s_mod[right_ptr_pos]){
                return false;
            }
            ++left_ptr_pos;
            --right_ptr_pos;
        }
        
        return true;
    }
};

const lest::test tests[] = {
    {CASE("Empty String"){
        Solution sln;
        string s = "";
        EXPECT(sln.isPalindrome(s) == true);
    }},
    {CASE("Empty Mod String"){
        Solution sln;
        string s = "& -";
        EXPECT(sln.isPalindrome(s) == true);
    }},
    {CASE("Non palindrome String"){
        Solution sln;
        string s = "race a car";
        EXPECT(sln.isPalindrome(s) == false);
    }},
    {CASE("Palindrome String"){
        Solution sln;
        string s = "A man, a plan, a canal: Panama";
        EXPECT(sln.isPalindrome(s) == true);
    }}
};

int main(int argc, char** argv){
    lest::run(tests, argc, argv);
}
