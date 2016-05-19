// https://leetcode.com/problems/coin-change/
// May 18, 2016

#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount)
    {
        initialize_vectors(amount);

        int startVertex = 0;
        int targetVertex = amount;

        queue<int> Q;
        vecMinChange_[startVertex] = 0;
        vecMinChange_[startVertex] = 0;
        Q.push(startVertex);
        vecVisited_[startVertex] = true;

        while (!Q.empty())
        {
            int curVertex = Q.front();
            Q.pop();

            for (vector<int>::iterator it = coins.begin(); it != coins.end(); ++it)
            {
                int coin = *it;
                int nextVertex = curVertex + coin;

                if (nextVertex > targetVertex)
                {
                    continue;
                }
                if (vecVisited_[nextVertex])
                {
                    continue; // already visited
                }

                vecMinChange_[nextVertex] = 1 + vecMinChange_[curVertex];
                vecVisited_[nextVertex] = true;
                Q.push(nextVertex);
            }
        }

        if (vecVisited_[targetVertex])
        {
            return vecMinChange_[targetVertex];
        }
        else
        {
            return -1;
        }
    }
private:
    void initialize_vectors(int amount)
    {
        vecMinChange_.reserve(amount+1);
        vecVisited_.reserve(amount+1);

        for (unsigned int i=0; i != (amount+1); ++i)
        {
            vecMinChange_.push_back(numeric_limits<int>::max());
            vecVisited_.push_back(false);
        }

    }
private:
    // Following vectors will have index: [0,1,...,amount]
    vector<int> vecMinChange_; // Stores the number of coin change for achieve total=index(of the vector)
    vector<bool> vecVisited_;
};

int main(int argc, char* argv[])
{
    Solution sln;
    vector<int> coins = {2};
    int amount = 3;
    int minCoinChange = sln.coinChange(coins, amount);
    cout << "Fewest number of coins to up the amount: " << minCoinChange << endl;

    return 0;
}

/* Solved using shortest paths. This problem can also be solved using dynamic programming.
*/
