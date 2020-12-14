// https://oj.leetcode.com/problems/word-break-ii/
// Date: Dec 02, 2014

#include <iostream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> wordBreak(string str, unordered_set<string> &dict)
    {
        str_ = str;
        dict_ = dict;

        vector<string> vec_sentence;
        if (str.size() == 0)
        {
            return vec_sentence;
        }

        // DFS traversal along with dynamic programming
        vector<bool> vecVisited;
        vector<vector<string> > vec_vec_sentence;

        vecVisited.reserve(str.size());
        vec_vec_sentence.reserve(str.size());

        for (int i=0; i != str.size(); ++i)
        {
            vecVisited.push_back(false);
            vec_vec_sentence.push_back(vector<string>());
        }

        stack<vector<int> > stk; // vector of end position
        vector<int> vec_en_pos = possible_words_from_current_position(0);

        for (vector<int>::iterator it = vec_en_pos.begin(); it != vec_en_pos.end(); ++it)
        {
            vector<int> vec;
            vec.push_back(*it);
            stk.push(vec);
        }

        while (!stk.empty())
        {
            vector<int> vec = stk.top();
            stk.pop();
            int st_pos = vec.back() + 1; // start position for words following the current one

            if (st_pos == str_.size())
            {
                string sentence;
                for (int i = vec.size()-1; i > 0; --i)
                {
                    int st_pos_word = vec[i-1] + 1;
                    int en_pos_word = vec[i];
                    string word = str_.substr(st_pos_word, en_pos_word-st_pos_word+1);

                    if (i == vec.size()-1)
                    {
                        sentence = word;
                    }
                    else
                    {
                        sentence = word + " " + sentence;
                    }

                    vec_vec_sentence[st_pos_word].push_back(sentence);
                }

                int st_pos_word = 0;
                int en_pos_word = vec[0];
                string word = str_.substr(st_pos_word, en_pos_word-st_pos_word+1);

                if (vec.size() == 1)
                {
                    sentence = word;
                }
                else
                {
                    sentence = word + " " + sentence;
                }
                vec_vec_sentence[st_pos_word].push_back(sentence);
            }
            else
            {
                if (vecVisited[st_pos])
                {
                    string sub_sentence;
                    for (int i = vec.size()-1; i > 0; --i)
                    {
                        int st_pos_word = vec[i-1] + 1;
                        int en_pos_word = vec[i];
                        string word = str_.substr(st_pos_word, en_pos_word-st_pos_word+1);

                        if (i == vec.size()-1)
                        {
                            sub_sentence = word;
                        }
                        else
                        {
                            sub_sentence = word + " " + sub_sentence;
                        }

                        for (vector<string>::iterator it = vec_vec_sentence[st_pos].begin(); it != vec_vec_sentence[st_pos].end(); ++it)
                        {
                            vec_vec_sentence[st_pos_word].push_back(sub_sentence + " " + *it);
                        }
                    }

                    int st_pos_word = 0;
                    int en_pos_word = vec[0];
                    string word = str_.substr(st_pos_word, en_pos_word-st_pos_word+1);

                    if (vec.size() == 1)
                    {
                        sub_sentence = word;
                    }
                    else
                    {
                        sub_sentence = word + " " + sub_sentence;
                    }

                    for (vector<string>::iterator it = vec_vec_sentence[st_pos].begin(); it != vec_vec_sentence[st_pos].end(); ++it)
                    {
                        vec_vec_sentence[st_pos_word].push_back(sub_sentence + " " + *it);
                    }

                }
                else
                {
                    vecVisited[st_pos] = true;

                    vec_en_pos = possible_words_from_current_position(st_pos);
                    for (vector<int>::iterator it = vec_en_pos.begin(); it != vec_en_pos.end(); ++it)
                    {
                        vector<int> vec_new = vec;
                        vec_new.push_back(*it);
                        stk.push(vec_new);
                    }
                }
            }

        }

        return vec_vec_sentence[0];

    }
private:
    vector<int> possible_words_from_current_position(int st_pos)
    {
        vector<int> vec;
        for (int en_pos = st_pos; en_pos != str_.size(); ++en_pos)
        {
            string word = str_.substr(st_pos, en_pos-st_pos+1);

            if (dict_.find(word) != dict_.end())
            {
                vec.push_back(en_pos);
            }
        }
        return vec;
    }
private:
    string str_;
    unordered_set<string> dict_;
};

int main(int argc, char* argv[])
{
    string str = "catsanddog";
    unordered_set<string> dict;
    dict.insert("cat");
    dict.insert("cats");
    dict.insert("and");
    dict.insert("sand");
    dict.insert("dog");

    Solution sln;
    vector<string> vec_sentence = sln.wordBreak(str, dict);

    for (vector<string>::iterator it = vec_sentence.begin(); it != vec_sentence.end(); ++it)
    {
        cout << *it << endl;
    }
}
