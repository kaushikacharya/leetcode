// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
// July 08, 2016

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        int max_profit = 0;

        if (prices.size() < 2)
        {
            return max_profit;
        }

        int min_price = prices.front();
        for (vector<int>::iterator it = prices.begin()+1; it != prices.end(); ++it)
        {
            int cur_price = *it;

            if (cur_price < min_price)
            {
                min_price = cur_price;
            }
            else if (min_price < cur_price)
            {
                max_profit = max(max_profit, cur_price-min_price);
            }
        }

        return max_profit;
    }
};

int main(int argc, char* argv[])
{
    vector<int> prices = {5, 8, 6, 7, 11, 3};
    Solution sln;
    int max_profit = sln.maxProfit(prices);
    cout << "max profit: " << max_profit << endl;
    return 0;
}
