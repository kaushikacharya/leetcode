// https://leetcode.com/problems/number-of-digit-one/
// June 28, 2016

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int countDigitOne(int n)
    {
        if (n < 1)
        {
            return 0;
        }

        vector<int> vec_max_count_of_digit_one = compute_number_of_digits_and_max_count_of_digit_one(n);
        int n_digit = vec_max_count_of_digit_one.size();
        // divisor = power(10, n_digit-1)

        int divisor = 1;
        for (int i = 1; i != n_digit; ++i)
        {
            divisor *= 10;
        }

        int count_digit_one = countDigitOne(n, vec_max_count_of_digit_one, n_digit-1, divisor);
        return count_digit_one;
    }
private:
    // divisor = power(10, n_digit-1)
    // divisor = power(10, power_divisor)
    int countDigitOne(int n, vector<int>& vec_max_count_of_digit_one, int power_divisor, int divisor)
    {
        if (n < 1)
        {
            return 0;
        }
        else if (n < 10)
        {
            return vec_max_count_of_digit_one[0];
        }
        else
        {
            // atleast 2 digits
            int count_digit_one = 0;

            int m = n/divisor - 1;

            if (m < 0)
            {
                // In previous iteration, n was something like 1011
                // In this iteration n is 011 and divisor = 100
            }
            else
            {
                count_digit_one = vec_max_count_of_digit_one[power_divisor-1]; // 0-based indexing

                if (m > 0)
                {
                    count_digit_one += divisor;
                    count_digit_one += m*vec_max_count_of_digit_one[power_divisor-1];
                }
                else
                {
                    // 1st column of power_divisor+1 digits
                    // count the left most digit (which will be always 1)
                    count_digit_one += n%divisor + 1;
                }
            }

            // Now count the digit one for the number without the left-most digit
            n = n%divisor;
            --power_divisor;
            divisor /= 10;

            count_digit_one += countDigitOne(n, vec_max_count_of_digit_one, power_divisor, divisor);

            return count_digit_one;
        }
    }

    vector<int> compute_number_of_digits_and_max_count_of_digit_one(int n)
    {
        int n_digit = 1;
        int divisor = 10;
        vector<int> vec_max_count_of_digit_one;
        // vec_max_count_of_digit_one[i]: max count of digit one for all numbers from 0 to numbers with i+1 digits
        // initialize for n_digit=1
        vec_max_count_of_digit_one.push_back(1); // 0 - 9: count of digit one is 1.

        while (n/divisor > 0)
        {
            ++n_digit;
            // compute max count of digit one for numbers <= max number with n_digit digits
            int cur_max_count_of_digit_one = divisor + 10*vec_max_count_of_digit_one.back();
            vec_max_count_of_digit_one.push_back(cur_max_count_of_digit_one);
            // increasing divisor to next power of 10
            divisor *= 10;
        }

        return vec_max_count_of_digit_one;
    }
};

int main(int argc, char* argv[])
{
    int n = 1000;
    Solution sln;
    int count_digit_one = sln.countDigitOne(n);
    cout << "count digit one: " << count_digit_one << endl;
    return 0;
}

/**
* Status: Wrong Answer
*/
