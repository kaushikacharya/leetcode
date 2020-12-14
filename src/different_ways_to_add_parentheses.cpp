// https://leetcode.com/problems/different-ways-to-add-parentheses/
// July 15, 2016

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

void test_func()
{
    string str = "2+34*52";
    // int num = atoi(str.substr(2,2).c_str());
    // cout << num << endl;

    // identify the operators and operands
    // First check if there's a unary operator in the beginning
    size_t i = 0;
    if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*'))
    {
        cout << "operator: " << str[i] << endl;
        ++i;
    }
    size_t j = 0;
    // operand str[i,..,i+j]
    while ((i+j) < str.size())
    {
        if ((str[i+j] == '+') || (str[i+j] == '-') || (str[i+j] == '*'))
        {
            cout << "operand: " << str.substr(i,j) << endl;
            cout << "operator: " << str[i+j] << endl;
            i += (j+1);
            j = 0;
        }
        else
        {
            ++j;
        }
    }
    cout << "operand: " << str.substr(i,j) << endl;
}

class Solution {
public:
    vector<int> diffWaysToCompute(string input)
    {
        segment_expression(input);

        pair<vector<int>,vector<int> > result = diffWaysToCompute(0, vecElem_.size()-1);

        if (isNegativeUnaryOperator_)
        {
            return result.second;
        }
        else
        {
            return result.first;
        }
    }
private:
    // [st_index,en_index]
    pair<vector<int>, vector<int> > diffWaysToCompute(size_t st_index, size_t en_index)
    {
        vector<int> vecValue;
        vector<int> vecValueWithUnaryNegative;

        if (st_index == en_index)
        {
            vecValue.push_back(atoi(vecElem_[st_index].c_str()));
            if ((st_index == 0) && isNegativeUnaryOperator_ )
            {
                vecValueWithUnaryNegative.push_back(-1*atoi(vecElem_[st_index].c_str()));
            }

            pair<vector<int>,vector<int> > result = make_pair(vecValue, vecValueWithUnaryNegative);
            return result;
        }

        // i represents position of binary operator
        size_t i = st_index+1;
        while (i < en_index)
        {
            pair<vector<int>, vector<int> > pair1values = diffWaysToCompute(st_index, i-1);
            pair<vector<int>, vector<int> > pair2values = diffWaysToCompute(i+1, en_index);

            vector<int> vec1 = pair1values.first;
            vector<int> vec2 = pair2values.first;

            for (vector<int>::iterator it1 = vec1.begin(); it1 != vec1.end(); ++it1)
            {
                for (vector<int>::iterator it2 = vec2.begin(); it2 != vec2.end(); ++it2)
                {
                    int val = compute(*it1, vecElem_[i][0], *it2);
                    vecValue.push_back(val);
                }
            }

            if ( (st_index == 0) && isNegativeUnaryOperator_ )
            {
                for (vector<int>::iterator it = vecValue.begin(); it != vecValue.end(); ++it)
                {
                    vecValueWithUnaryNegative.push_back(-1*(*it));
                }
                vector<int> vec1b = pair1values.second;
                for (vector<int>::iterator it1 = vec1b.begin(); it1 != vec1b.end(); ++it1)
                {
                    for (vector<int>::iterator it2 = vec2.begin(); it2 != vec2.end(); ++it2)
                    {
                        int val = compute(*it1, vecElem_[i][0], *it2);
                        vecValueWithUnaryNegative.push_back(val);
                    }
                }
            }

            i += 2;
        }

        pair<vector<int>,vector<int> > result = make_pair(vecValue, vecValueWithUnaryNegative);
        return result;
    }

    int compute(int num1, char char_operator, int num2)
    {
        // int num1 = atoi(str_num1.c_str());
        // int num2 = atoi(str_num2.c_str());

        int val;

        switch (char_operator)
        {
        case '*':
            {
                val = num1*num2;
                break;
            }
        case '+':
            {
                val = num1+num2;
                break;
            }
        case '-':
            {
                val = num1-num2;
                break;
            }
        default:
            {
                cout << "unexpected operator: " << char_operator << endl;
            }
        }

        return val;
    }


    void segment_expression(string str)
    {
        isNegativeUnaryOperator_ = false;
        size_t i = 0;
        // First check if there's any unary operator
        if (str[i] == '+')
        {
            ++i;
        }
        else if (str[i] == '-')
        {
            isNegativeUnaryOperator_ = true;
            ++i;
        }

        // Now identify the sequence operand,operator,operand,operator,operand,...
        size_t j = 0;
        // operand str[i,..,i+j]
        while ((i+j) < str.size())
        {
            if ((str[i+j] == '+') || (str[i+j] == '-') || (str[i+j] == '*'))
            {
                vecElem_.push_back(str.substr(i,j));
                vecElem_.push_back(str.substr(i+j,1));
                // cout << "operand: " << str.substr(i,j) << endl;
                // cout << "operator: " << str[i+j] << endl;
                i += (j+1);
                j = 0;
            }
            else
            {
                ++j;
            }
        }
        vecElem_.push_back(str.substr(i,j));
        // cout << "operand: " << str.substr(i,j) << endl;
    }
private:
    vector<string> vecElem_; // elem is either operator or operand
    bool isNegativeUnaryOperator_;
};

int main(int argc, char** argv)
{
    // test_func();
    string input = "-2*3-4*5";
    Solution sln;
    vector<int> vecResult = sln.diffWaysToCompute(input);
    for (vector<int>::iterator it = vecResult.begin(); it != vecResult.end(); ++it)
    {
        if (it != vecResult.begin())
        {
            cout << ",";
        }
        cout << *it;
    }
    cout << endl;
    return 0;
}
