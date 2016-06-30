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

        vector<int> vec_max_count_of_digit_one = compute_max_count_of_digit_one_for_different_digits(n);
        int n_digit = vec_max_count_of_digit_one.size();
        // cout << "n_digit: " << n_digit << endl;

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
    // Initially:
    // divisor = power(10, n_digit-1)
    // power_divisor = n_digit-1
    // Then on each iteration divisor is decreased 10 times.
    // Recursively we keep collecting digit from left to right one digit at a time. Based on this and
    // the divisor we compute count of digit one.
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
                // Left most digit of n is 0.
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

            // cout << "power_divisor: " << power_divisor << " :: divisor: " << divisor << " :: count_digit_one: " << count_digit_one << endl;

            // Now count the digit one for the number without the left-most digit
            n = n%divisor;
            --power_divisor;
            divisor /= 10;

            count_digit_one += countDigitOne(n, vec_max_count_of_digit_one, power_divisor, divisor);

            return count_digit_one;
        }
    }

    // Here we compute total count of digit one for 0-9, 0-99 and so on.
    vector<int> compute_max_count_of_digit_one_for_different_digits(int n)
    {
        int divisor = 1;
        vector<int> vec_max_count_of_digit_one;
        // vec_max_count_of_digit_one[i]: max count of digit one for all numbers from 0 to numbers with i+1 digits

        while (n > 0)
        {
            // compute max count of digit one for numbers <= max number with n_digit digits
            if (vec_max_count_of_digit_one.empty())
            {
                // initialize for n_digit=1
                vec_max_count_of_digit_one.push_back(1); // 0 - 9: count of digit one is 1.
            }
            else
            {
                int cur_max_count_of_digit_one = divisor + 10*vec_max_count_of_digit_one.back();
                vec_max_count_of_digit_one.push_back(cur_max_count_of_digit_one);
            }

            divisor *= 10;
            // removing right most digit
            n /= 10;
        }

        return vec_max_count_of_digit_one;
    }
};

// This test function shows what happens due to integer over-flow.
void test_divisor(int n)
{
    int divisor = 1;

    for (int i = 0; i != 20; ++i)
    {
        divisor *= 10;
        cout << "i: " << i+1 << " :: divisor: " << divisor << " :: n/divisor: " << n/divisor << endl;
    }
}

int main(int argc, char* argv[])
{
    int n = 1410065408;
    // test_divisor(n);
    Solution sln;
    int count_digit_one = sln.countDigitOne(n);
    cout << "count digit one: " << count_digit_one << endl;
    return 0;
}

/**
* Error in previous solution was due to integer over flow.
*/
