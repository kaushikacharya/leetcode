// https://leetcode.com/problems/multiply-strings/
// May 27, 2016

#include <iostream>
#include <string>
#include <sstream>

using namespace std;


class Solution {
public:
    // Approach: Divide and conquer, recursive
    string multiply(string num1, string num2)
    {
        // Decomposition notation is as follows:
        // num1 => AB (A.size() = m1, B.size() = m2)
        // num2 => CD (C.size() = n1, D.size() = n2)
        // result = (A*10^m2 + B)*(C*10^n2 + D)
        //        =  A*C*10^(m2+n2) + A*D*10^m2 + B*C*10^n2 + B*D

        // Boundary case
        if ( (num1.size() == 1) && (num2.size() == 1) )
        {
            int num1_int = int(num1[0]) - int('0');
            int num2_int = int(num2[0]) - int('0');
            int mult_int = num1_int * num2_int;
            // convert the multiplication result into string
            stringstream ss;
            ss << mult_int;
            string result = ss.str();
            // empty the string stream
            ss.str(string());
            return result;
        }

        int m1 = num1.size()/2;
        int m2 = num1.size() - m1;
        int n1 = num2.size()/2;
        int n2 = num2.size() - n1;

        // BD multiplication
        string result = multiply(num1.substr(m1),num2.substr(n1));

        if (num2.size() > 1)
        {
            // BC multiplication
            string str = multiply(num1.substr(m1), num2.substr(0,n1));
            string zeros_str = str_of_zeros(n2);
            str += zeros_str;
            // Now result = result + BC*10^(n2)
            result = addition(result, str);
        }
        if (num1.size() > 1)
        {
            // AD multiplication
            string str = multiply(num1.substr(0,m1), num2.substr(n1));
            string zeros_str = str_of_zeros(m2);
            str += zeros_str;
            // Now result = result + AD*10^(m2)
            result = addition(result, str);
        }
        if ( (num1.size() > 1) && (num2.size() > 1) )
        {
            // AC multiplication
            string str = multiply(num1.substr(0,m1), num2.substr(0,n1));
            string zeros_str = str_of_zeros(m2+n2);
            str += zeros_str;
            // Now result = result + AC*10^(m2+n2)
            result = addition(result, str);
        }

        return result;
    }
private:
    string addition(string num1, string num2)
    {
        // pre-appending zeros to equate number of digits
        if (num1.size() < num2.size())
        {
            int size_num1 = num1.size();
            int size_num2 = num2.size();

            for (int i=size_num1; i != size_num2; ++i)
            {
                num1 = "0" + num1;
            }
        }
        else if (num2.size() < num1.size())
        {
            int size_num1 = num1.size();
            int size_num2 = num2.size();

            for (int i=size_num2; i != size_num1; ++i)
            {
                num2 = "0" + num2;
            }
        }

        // int min_size = min(num1.size(), num2.size());
        string str_add = "";

        stringstream ss;
        int carry_over = 0;
        for (int i=0; i != num1.size(); ++i)
        {
            char ch1 = num1[num1.size()-1-i];
            char ch2 = num2[num2.size()-1-i];
            int ch1_int = int(ch1) - int('0');
            int ch2_int = int(ch2) - int('0');
            int ch_add_int = ch1_int + ch2_int + carry_over;
            carry_over = ch_add_int/10;
            ss << ch_add_int%10;
            str_add = ss.str() + str_add;
            ss.str(string());
        }

        if (carry_over > 0)
        {
            ss << carry_over;
            str_add = ss.str() + str_add;
            ss.str(string());
        }

        return str_add;
    }

    string str_of_zeros(int n)
    {
        string str = "";
        for (int i=0; i != n; ++i)
        {
            str += "0";
        }
        return str;
    }
private:
    string result_;
};

void test_str_to_int(char ch1, char ch2)
{
    cout << "ch1: " << ch1 << " :: ch2: " << ch2 << endl;
    int ch1_int = int(ch1) - int('0');
    cout << "ch1_int: " << ch1_int << endl;
    int ch2_int = int(ch2) - int('0');
    cout << "ch2_int: " << ch2_int << endl;
    int mult_int = ch1_int*ch2_int;
    stringstream ss;
    ss << mult_int;
    cout << "mult_int: " << mult_int << " :: str(mult_int): " << ss.str() << endl;
    ss.str(string());
}

int main(int argc, char* argv[])
{
    /*
    string str = "367";
    char ch1 = str[1];
    char ch2 = str[2];
    test_str_to_int(ch1, ch2);
    */
    string num1 = "34951988787875060539794079748961576784564363070245114613707595672441019547866090721102583434";
    string num2 = "16659770238224335056461144790912689758874618241978614940512513991166165549575662545139401664";
    Solution sln;
    string mult = sln.multiply(num1, num2);
    cout << "multiplication: " << mult << endl;
    return 0;
}

/*
Status: Time Limit Exceeded

Have a look at this:
https://leetcode.com/discuss/89614/clean-efficient-solution-accepted-best-submission-explained
*/
