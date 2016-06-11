// https://leetcode.com/problems/perfect-squares/
// June 11, 2016

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    int numSquares(int n)
    {
        int i = 1;
        while (i*i <= n)
        {
            vecPerfectSquares_.push_back(i*i);
            ++i;
        }

        // case: n is a perfect square
        if (vecPerfectSquares_.back() == n)
        {
            return 1;
        }

        vecCount_.push_back(1); //vecCount_[0] represents number of perfect squares for number 1
        i = 2;
        int k = 0; // represents: vecPerfectSquares_[0,...,k] <= i
        while (i != (n+1))
        {
            // Check if number i has reached next perfect square
            if ( (k < (vecPerfectSquares_.size()-1)) && (vecPerfectSquares_[k+1] == i) )
            {
                vecCount_.push_back(1);
                ++k;
            }
            else
            {
                int least_numbers = numeric_limits<int>::max();
                for (int j=0; j != (k+1); ++j)
                {
                    // a + b = i
                    // a = vecPerfectSquares_[j]
                    // b = i - a
                    int b = i - vecPerfectSquares_[j];
                    int count_numbers = vecCount_[vecPerfectSquares_[j]-1] + vecCount_[b-1];
                    if (count_numbers < least_numbers)
                    {
                        least_numbers = count_numbers;
                    }
                }
                vecCount_.push_back(least_numbers);
            }


            ++i;
        }

        return vecCount_[n-1];
    }
private:
    vector<int> vecPerfectSquares_; // e.g. {1,4,9,...}
    vector<int> vecCount_; // vecCount_[i-1] : Least number of perfect squares which sum to number i
};

int main(int argc, char* argv[])
{
    int n = 5;
    Solution sln;
    int least_numbers = sln.numSquares(n);
    cout << "least numbers: " << least_numbers << endl;
    return 0;
}
