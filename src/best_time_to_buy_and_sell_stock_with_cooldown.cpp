// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
// July 09, 2016

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        if (prices.size() < 2)
        {
            return 0;
        }

        vector<int> max_profit_array;
        for (size_t i=0; i != 3; ++i)
        {
            max_profit_array.push_back(numeric_limits<int>::min());
        }
        // Notation:
        // [0],[1]: Today EOD we don't have any stock.
        // [0]: We haven't sold any stock today. Hence we can buy stock tomorrow.
        // [1]: We have sold stock today. Hence tomorrow is cooldown day.
        // [2]: Today we have bough stock.

        // Initialize for first day.
        max_profit_array[0] = 0;
        max_profit_array[2] = -1*prices.front();

        for (vector<int>::iterator it = prices.begin()+1; it != prices.end(); ++it)
        {
            int cur_price = *it;
            vector<int> max_profit_today_array(3, numeric_limits<int>::min());

            for (size_t pos = 0; pos != 3; ++pos)
            {
                // pos: represents yesterday's max profit in reaching pos
                if (max_profit_array[pos] > numeric_limits<int>::min())
                {
                    switch (pos)
                        {
                        case 0:
                            {
                                // Option #1: No buying of stock today
                                max_profit_today_array[0] = max(max_profit_today_array[0], max_profit_array[0]);
                                // Option #2: Buy stock today
                                max_profit_today_array[2] = max(max_profit_today_array[2], max_profit_array[0] - cur_price);
                                break;
                            }
                        case 1:
                            {
                                // Today cool down but tomorrow no
                                max_profit_today_array[0] = max(max_profit_today_array[0], max_profit_array[1]);
                                break;
                            }
                        case 2:
                            {
                                // Option #1: Sell it today and tomorrow will become cool down day.
                                max_profit_today_array[1] = max(max_profit_today_array[1], max_profit_array[2]+cur_price);
                                // Option #2: Hold it
                                max_profit_today_array[2] = max(max_profit_today_array[2], max_profit_array[2]);
                                break;
                            }
                        }

                }
            }

            max_profit_array = max_profit_today_array;
        }

        int max_profit = max_profit_array.front();
        for (vector<int>::iterator it = max_profit_array.begin()+1; it != max_profit_array.end(); ++it)
        {
            max_profit = max(max_profit, *it);
        }

        return max_profit;
    }
};

int main(int argc, char* argv[])
{
    vector<int> prices = {1, 2, 5, 0, 1, 2};
    Solution sln;
    int max_profit = sln.maxProfit(prices);
    cout << "max profit: " << max_profit << endl;
    return 0;
}

/**
*   My solution is similar to this: (automata)
*   https://discuss.leetcode.com/topic/30680/share-my-dp-solution-by-state-machine-thinking
*
* http://stackoverflow.com/questions/10237751/can-i-initialize-an-stl-vector-with-10-of-the-same-integer-in-an-initializer-lis
*/
