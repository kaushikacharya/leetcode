// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
// June 04, 2016

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits)
    {
        create_map_of_digit_to_letters();
        compute_letter_combinations_iterative(digits);

        return vecLetterCombinations_;
    }
private:
    // Map according to telephone
    void create_map_of_digit_to_letters()
    {
        map_digit_to_letters_['0'] = {' '};
        map_digit_to_letters_['1'] = {};
        map_digit_to_letters_['2'] = {'a','b','c'};
        map_digit_to_letters_['3'] = {'d','e','f'};
        map_digit_to_letters_['4'] = {'g','h','i'};
        map_digit_to_letters_['5'] = {'j','k','l'};
        map_digit_to_letters_['6'] = {'m','n','o'};
        map_digit_to_letters_['7'] = {'p','q','r','s'};
        map_digit_to_letters_['8'] = {'t','u','v'};
        map_digit_to_letters_['9'] = {'w','x','y','z'};
    }

    void compute_letter_combinations_iterative(string digits)
    {
        if (digits == "")
        {
            return;
        }

        string str = "";
        stack<pair<char,int> > stk;

        // Push chars corresponding to 0th digit
        for (vector<char>::reverse_iterator it = map_digit_to_letters_[digits[0]].rbegin(); it != map_digit_to_letters_[digits[0]].rend(); ++it)
        {
            stk.push(make_pair(*it,0));
        }

        while (!stk.empty())
        {
            pair<char,int> elem = stk.top();
            stk.pop();
            char ch = elem.first;
            int curLevel = elem.second;

            if (curLevel == str.size())
            {
                str += ch;
            }
            else if (str.size() > curLevel)
            {
                str[curLevel] = ch;
            }
            else
            {
                cout << "mistake" << endl;
            }

            if (curLevel == (digits.size()-1))
            {
                vecLetterCombinations_.push_back(str);
            }
            else
            {
                int nextLevel = curLevel + 1;
                for (vector<char>::reverse_iterator it = map_digit_to_letters_[digits[nextLevel]].rbegin(); it != map_digit_to_letters_[digits[nextLevel]].rend(); ++it)
                {
                    stk.push(make_pair(*it,nextLevel));
                }
            }
        }
    }
private:
    unordered_map<char,vector<char> > map_digit_to_letters_;
    vector<string> vecLetterCombinations_;
};

void test_char_to_string(char ch)
{
    string str(1,ch);
    // append "1" to str
    str += '1';
    cout << str << endl;
}

void test_map_int_to_vector_chars()
{
    unordered_map<int,vector<char> > test_map;
    test_map[0] = {' '};
    test_map[1] = {'a','b'};
    test_map[2] = {};

    int i = 1;
    while (i < 3)
    {
        cout << "value for key=" << i << ": (" << test_map[i].size() << " chars) :: ";
        for (vector<char>::iterator it = test_map[i].begin(); it != test_map[i].end(); ++it)
        {
            cout << *it << ",";
        }
        cout << endl;
        ++i;
    }

}

int main(int argc, char* argv[])
{
    // char ch = 'a';
    // test_char_to_string(ch);

    // test_map_int_to_vector_chars();

    string digits = "23567";
    Solution sln;
    vector<string> letter_combinations = sln.letterCombinations(digits);
    for (vector<string>::iterator it = letter_combinations.begin(); it != letter_combinations.end(); ++it)
    {
        cout << *it << ",";
    }
    cout << endl;
    return 0;
}

/*
TBD: Try recursive solution.

http://stackoverflow.com/questions/3222572/convert-a-single-character-to-a-string

Alternate option to convert char to string using stringstream
http://www.cplusplus.com/forum/beginner/4967/
*/
