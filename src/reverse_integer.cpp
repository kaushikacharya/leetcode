/*  Problem: https://leetcode.com/problems/reverse-integer/
    Statement: Given a signed 32-bit integer x, return x with its digits reversed.
    Date: 06 Oct 2023
    Approach: Extract the integer at unit digit recursively by using modulo 10.
    Time complexity: O(n) where n is the number of digits.
    Space complexity: O(1)
    Status: TODO Take care of integer overflow.
*/

#include <bits/stdc++.h>
#include <lest.hpp>

using namespace std;

class Solution {
public:
    int sign(int x) {
        return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
    }

    int reverse(int x) {
        int result = 0;
        int sign_x = sign(x);

        while (x != 0)
        {
            result = 10*result + ((sign_x*x) % 10) * sign_x;
            x = x / 10;
        }
        
        return result;
    }
};

lest::test tests[] = {
    CASE("Test Case #1"){
        int x = 123;
        Solution sln;
        EXPECT(sln.reverse(x) == 321);
    },
    CASE("Test Case #2"){
        int x = -123;
        Solution sln;
        EXPECT(sln.reverse(x) == -321);
    },
    CASE("Test Case #3"){
        int x = 1;
        Solution sln;
        EXPECT(sln.reverse(x) == 1);
    },
    CASE("Test Case #4"){
        int x = -1;
        Solution sln;
        EXPECT(sln.reverse(x) == -1);
    },
    CASE("Test Case #5"){
        int x = 0;
        Solution sln;
        EXPECT(sln.reverse(x) == 0);
    }
};

int main(int argc, char** argv)
{
    lest::run(tests, argc, argv);
}
